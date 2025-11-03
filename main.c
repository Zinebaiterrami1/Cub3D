/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:41:25 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/03 14:12:00 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->s = 0;
	keys->a = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}


static int	process_line(char *line, int i, t_ctx *ctx)
{
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (global_color(line + i, ctx->game) == 0)
		return (0);
	if (tex_global(line + i, ctx->tex) == 0)
		return (0);
	if (line[i] == '1')
	{
		ctx->map->grid = get_map(line, ctx->fd);
		return (1);
	}
	return (-1);
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
		free(line);
		if (ret == 1)
			break ;
		else if (ret == -1)
			print_error();
		line = get_next_line(fd);
	}
	return (map);
}

// static void	init_game(t_game *game, t_map map, t_textures tex)
// {
// 	init_keys(&game->keys);
// 	init_win(game);
// 	game->map = map;
// 	load_textures(game, &tex);
// 	line_free(tex);
// 	game->gun = init_gun();
// 	load_texture_gun(game);
// 	init_player(&game->player, map.player);
// 	hook_init(game);
// }
void	init_draw(t_draw *draw)
{
	draw->tile = 0;
	draw->color = 0;
	draw->yy = 0;
	draw->xx = 0;
	draw->px = 0;
	draw->py = 0;
	draw->size = 0;
	draw->x = 0;
	draw->y = 0;
	draw->dx = 0;
	draw->dy = 0;
}
void	init_all_rays(t_ray rays[NUM_RAYS])
{
	for (int i = 0; i < NUM_RAYS; i++)
		init_ray(&rays[i]);
}
void	init_textures(t_texture textures[NUM_TEXTURES])
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		textures[i].img = NULL;
		textures[i].addr = NULL;
		textures[i].width = 0;
		textures[i].height = 0;
		textures[i].bpp = 0;
		textures[i].line_len = 0;
		textures[i].endian = 0;
	}
}

static void	init_game(t_game *game, t_map map, t_textures tex)
{
	memset(game, 0, sizeof(t_game));

	init_keys(&game->keys);
	init_win(game); // suppose que tu ouvres la fenêtre ici
	init_draw(&game->draw);
	init_all_rays(game->rays); // initialise chaque rayon à 0
	init_textures(game->textures);
	game->floor_color = 0;
	game->ceiling_color = 0;

	// 3️⃣ Charger la map et les textures
	game->map = map;
	load_textures(game, &tex);
	line_free(tex);

	// 4️⃣ Initialiser les armes et autres éléments
	game->gun = init_gun();
	load_texture_gun(game);

	// 5️⃣ Initialiser le joueur (à partir de la map)
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
	parse_args(ac, av);
	fd = open_map_file(av[1]);
	map = read_map_file(fd, &game, &tex);
	close(fd);
	trim_newline(map.grid);
	map.cols = find_big_line(map.grid);
	map.grid = square_map(map.grid, map.cols);
	while (map.grid[map.rows])
		map.rows++;
	valid_map(&map);
	init_ray(&game.ray);
	validate_textures(&tex);
	init_game(&game, map, tex);
	free(map.grid);
	return (0);
}
