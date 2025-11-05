/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:41:25 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/05 15:20:58 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void	init_game(t_game *game, t_map map, t_textures tex)
{
	init_keys(&game->keys);
	init_win(game);
	init_draw(&game->draw);
	init_all_rays(game->rays);
	init_textures(game->textures);
	game->map = map;
	load_textures(game, &tex);
	line_free(tex);
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
	print_cub3d_logo();
	valid_map(&map);
	init_draw_texture(&game.dt);
	init_all_rays(game.rays);
	validate_textures(&tex);
	init_game(&game, map, tex);
	free_map_grid(map.grid);
	return (0);
}
