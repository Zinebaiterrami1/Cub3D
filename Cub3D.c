/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:56:47 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/03 16:43:49 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map(void)
{
	t_map	map;

	map.grid = NULL;
	map.cols = 0;
	map.rows = 0;
	map.player.x = 0;
	map.player.y = 0;
	map.player.dx = 0;
	map.player.dy = -1;
	map.player.angle = 1.5 * 3.14;
	map.count_pos = 0;
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

void	cleanup_game(t_game *game)
{
	int	i;

	// Free textures
	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->gfx.mlx, game->textures[i].img);
		i++;
	}

	// Free gun textures
	i = 0;
	while (i < 2)
	{
		if (game->gun.gun_texture[i].img)
			mlx_destroy_image(game->gfx.mlx, game->gun.gun_texture[i].img);
		i++;
	}

	// Free MLX resources
	if (game->gfx.img)
		mlx_destroy_image(game->gfx.mlx, game->gfx.img);
	if (game->gfx.win)
		mlx_destroy_window(game->gfx.mlx, game->gfx.win);
	if (game->gfx.mlx)
	{
		mlx_destroy_display(game->gfx.mlx);
		free(game->gfx.mlx);
	}
}

// int	destroy_mlx(t_game *game)
// {
// 	mlx_destroy_image(game->gfx.mlx, game->gfx.img);
// 	mlx_destroy_window(game->gfx.mlx, game->gfx.win);
// 	mlx_destroy_display(game->gfx.mlx);
// 	free(game->gfx.mlx);
// 	exit(0);
// }

int	destroy_mlx(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void	hook_init(t_game *game)
{
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
	mlx_hook(game->gfx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->gfx.win, 3, 1L << 1, key_release, game);
	mlx_hook(game->gfx.win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->gfx.win, 17, 0, close_window, NULL);
	mlx_loop_hook(game->gfx.mlx, game_loop, game);
	mlx_loop(game->gfx.mlx);
	destroy_mlx(game);
}
