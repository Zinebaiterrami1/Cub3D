/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:15:09 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/04 12:59:17 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_dda(t_game *game, int color)
{
	int		steps;
	float	x;
	float	y;
	int		i;
	float	x_inc;
	float	y_inc;
	float	dx;
	float	dy;

	steps = 0;
	dx = game->ray.end_x - game->player.x;
	dy = game->ray.end_x - game->player.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps == 0)
		return ;
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = game->player.x;
	y = game->player.y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(&game->gfx, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
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
