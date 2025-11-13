/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:41:25 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 09:14:40 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	process_line(char *line, int i, t_ctx *ctx)
{
	// Ignorer les lignes vides
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (line[i] == 'F' || line[i] == 'C')
	{
		global_color(line + i, ctx->game);
		return (0);
	}
	if (tex_global(line + i, ctx->tex) == 0)
		return (0);
	if (ft_strnstr(line, "1111", ft_strlen(line)))
	{
		ctx->map->grid = get_map(line, ctx->fd);
		return (1);
	}
	return (0);
}

static t_map	read_map_file(int fd, t_game *game, t_textures *tex)
{
	t_map	map;
	t_ctx	ctx;
	char	*line;
	int		i;
	int		ret;

	map = init_map();
	ctx.game = game;
	ctx.tex = tex;
	ctx.map = &map;
	ctx.fd = fd;
	line = get_next_line(fd);
	while (line)
	{
		i = skip_whitespace(line);
		ret = process_line(line, i, &ctx);
		(void)line;
		if (ret == 1)
			break ;
		else if (ret == -1)
			print_error();
		line = get_next_line(fd);
	}
	get_next_line(-1);
	return (map);
}

static void	init_game(t_game *game, t_map map, t_textures tex)
{
	init_keys(&game->keys);
	init_win(game);
	init_draw(&game->draw);
	init_all_rays(game->rays);
	init_textures(game->textures);
	game->ceiling_set = 0;
	game->floor_set = 0;
	game->map = map;
	load_textures(game, &tex);
	line_free(tex);
	game->gun = init_gun();
	load_texture_gun(game);
	init_player(&game->player, map.player);
	hook_init(game);
}

void	init_draw_texture(t_draw_texture *dt)
{
	dt->screen_y = 0;
	dt->screen_x = 0;
	dt->color = 0;
	dt->wall_top = 0.0f;
	dt->wall_bottom = 0.0f;
	dt->tex_x = 0;
	dt->tex_num = 0;
	dt->step = 0.0f;
	dt->tex_pos = 0.0f;
	dt->tex_y = 0;
	dt->wall_height = 0;
}

int	main(int ac, char **av)
{
	t_game		game;
	t_map		map;
	int			fd;
	t_textures	tex;

	game.ceiling_set = 0;
	game.floor_set = 0;
	parse_args(ac, av);
	check_tex(&tex);
	fd = open_map_file(av[1]);
	map = read_map_file(fd, &game, &tex);
	if (!map.grid)
		print_error();
	close(fd);
	trim_newline(map.grid);
	map.cols = find_big_line(map.grid);
	map.grid = square_map(map.grid, map.cols);
	print_cub3d_logo();
	valid_map(&map);
	init_draw_texture(&game.dt);
	init_all_rays(game.rays);
	validate_textures(&tex);
	if (game.floor_set == 0)
	{
		printf("Warning: floor color not set, using default (black)\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	if (game.ceiling_set == 0)
	{
		printf("Warning: ceiling color not set, using default (white)\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	init_game(&game, map, tex);
	free_map_grid(map.grid);
	return (0);
}
