/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:56:47 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 15:54:11 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map init_map()
{
    t_map map;

    map.grid = NULL;
    map.cols = 0;
    map.rows = 0;
    map.player.x = 0;
    map.player.y = 0;
    map.player.dx = 0;
    map.player.dy = -1;
    map.player.angle = 1.5 * 3.14;
    return (map);
}
void	init_win(t_game *game)
{
	game->gfx.mlx = mlx_init();
	game->gfx.win = mlx_new_window(game->gfx.mlx, WIDTH, HEIGHT, "Cub3D");
	game->gfx.img = mlx_new_image(game->gfx.mlx, WIDTH, HEIGHT);
	game->gfx.addr = mlx_get_data_addr(game->gfx.img, &game->gfx.bpp,
			&game->gfx.line_len, &game->gfx.endian);
}

void	hook_init(t_game *game)
{
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
	mlx_hook(game->gfx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->gfx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->gfx.win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hide(game->gfx.mlx, game->gfx.win);
	mlx_hook(game->gfx.win, 17, 0, close_window, NULL);
	mlx_loop_hook(game->gfx.mlx, game_loop, game);
	mlx_loop(game->gfx.mlx);
}

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}