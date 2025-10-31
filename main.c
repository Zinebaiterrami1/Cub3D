/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:41:25 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 11:16:19 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	init_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

int	main(int ac, char **av)
{
	t_game		game;
	t_map		map;
	int			fd;
	t_textures	tex;
	char		*line;
	int			error;
	int			i;

	if (ac != 2)
		print_error();
	if (ft_strncmp(av[1] + (ft_strlen(av[1] - 4)), ".cub", 4))
		print_error();
	fd = open("map.cub", O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur ouverture fichier");
		return (1);
	}
	// tex = {0};
	error = 0;
	map = init_map();
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
		{
			free(line);
			continue ;
		}
		if (line[i] == 'F')
			parse_color(line + i + 1, &game.floor_color);
		else if (line[i] == 'C')
			parse_color(line + i + 1, &game.ceiling_color);
		else if ((line[i] == 'N' && line[i + 1] == 'O') ||
					(line[i] == 'S' && line[i + 1] == 'O') ||
					(line[i] == 'W' && line[i + 1] == 'E') ||
					(line[i] == 'E' && line[i + 1] == 'A'))
		{
			check_texture_line(&tex, line);
		}
		else if (line[i] == '1')
		{
			map.grid = get_map(line, fd);
			break ;
		}
		else
		{
			printf("❌ Ligne invalide détectée : %s\n", line);
			error = 1;
		}
		free(line);
	}
	close(fd);
	trim_newline(map.grid);
	map.cols = find_big_line(map.grid);
	map.grid = square_map(map.grid, map.cols);
	while (map.grid[map.rows])
		map.rows++;
	i = 0;
	while (map.grid[i])
	{
		printf("[%s], len: %d\n", map.grid[i], (int)ft_strlen(map.grid[i]));
		i++;
	}
	valid_map(&map);
	if (tex.NO)
		check_path(tex.NO);
	else
	{
		printf("❌ Texture NO manquante\n");
		error = 1;
	}
	if (tex.SO)
		check_path(tex.SO);
	else
	{
		printf("❌ Texture SO manquante\n");
		error = 1;
	}
	if (tex.EA)
		check_path(tex.EA);
	else
	{
		printf("❌ Texture EA manquante\n");
		error = 1;
	}
	if (tex.WE)
		check_path(tex.WE);
	else
	{
		printf("❌ Texture WE manquante\n");
		error = 1;
	}

	if (error)
	{
		printf("\n❌ La map contient des erreurs.\n");
		return (error);
	}
	else
	{
		printf("\n✅ Map valide,toutes les textures et couleurs sont correctes.\n");
	}
	init_keys(&game);

	game.gfx.mlx = mlx_init();
	game.gfx.win = mlx_new_window(game.gfx.mlx, WIDTH, HEIGHT, "Cub3D");
	game.gfx.img = mlx_new_image(game.gfx.mlx, WIDTH, HEIGHT);
	game.gfx.addr = mlx_get_data_addr(game.gfx.img, &game.gfx.bpp,
			&game.gfx.line_len, &game.gfx.endian);
	game.map = map;
	load_textures(&game , &tex);
	free(tex.NO);
	free(tex.SO);
	free(tex.EA);
	free(tex.WE);
	free(tex.S);
	game.gun = init_gun();
    load_texture_gun(&game);
printf("main player x: %f y: %f\n: --------------", map.player.x, map.player.y);
    game.player.x = (map.player.y + 0.5) * TILE_SIZE;
    game.player.y = (map.player.x + 0.5) * TILE_SIZE;
    game.player.angle = map.player.angle;
    game.player.dx = cos(game.player.angle) * SPEED;
    game.player.dy = sin(game.player.angle) * SPEED;
	draw_sky_and_floor(&game);
	draw_fov_rays(&game);
	render_3d_textured(&game);
		draw_gun(&game);

	mlx_put_image_to_window(game.gfx.mlx, game.gfx.win, game.gfx.img, 0, 0);
	mlx_hook(game.gfx.win, 2, 1L << 0, key_press, &game);     // KeyPress
	mlx_hook(game.gfx.win, 3, 1L << 1, key_release, &game);   // KeyRelease
		// mlx_hook(game.gfx.win, 6, 1L << 6, mouse_move, &game);

	mlx_hook(game.gfx.win, 17, 0, close_window, NULL);

	mlx_loop_hook(game.gfx.mlx, game_loop, &game);            // main loop	mlx_hook(game.gfx.win, 6, 1L << 6, mouse_move, &game);
	mlx_loop(game.gfx.mlx);
	free(map.grid);
	return (0);
}
