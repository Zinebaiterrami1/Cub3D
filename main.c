/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:41:25 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 14:29:44 by fakoukou         ###   ########.fr       */
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
	init_keys(game);
	init_win(game);
	game->map = map;
	load_textures(game, &tex);
	line_free(tex);
	game->gun = init_gun();
	load_texture_gun(game);
	init_player(&game->player, map.player);
	hook_init(game);
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
	validate_textures(&tex);
	init_game(&game, map, tex);
	free(map.grid);
	return (0);
}
