/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:15:09 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/05 14:04:49 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_d(t_d d)
{
	d.steps = 0;
	d.x = 0.0;
	d.y = 0.0;
	d.i = 0;
	d.x_inc = 0.0;
	d.y_inc = 0.0;
	d.dx = 0.0;
	d.dy = 0.0;
}

void	draw_line_dda(t_game *game, int color)
{
	init_d(game->d);
	game->d.steps = 0;
	game->d.dx = game->ray.end_x - game->player.x;
	game->d.dy = game->ray.end_x - game->player.y;
	if (fabs(game->d.dx) > fabs(game->d.dy))
		game->d.steps = fabs(game->d.dx);
	else
		game->d.steps = fabs(game->d.dy);
	if (game->d.steps == 0)
		return ;
	game->d.x_inc = game->d.dx / game->d.steps;
	game->d.y_inc = game->d.dy / game->d.steps;
	game->d.x = game->player.x;
	game->d.y = game->player.y;
	game->d.i = 0;
	while (game->d.i <= game->d.steps)
	{
		my_mlx_pixel_put(&game->gfx, (int)game->d.x, (int)game->d.y, color);
		game->d.x += game->d.x_inc;
		game->d.y += game->d.y_inc;
		game->d.i++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = y * mlx->line_len + x * (mlx->bpp / 8);
	*(unsigned int *)(mlx->addr + pixel) = color;
}
