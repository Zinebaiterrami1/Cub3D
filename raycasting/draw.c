/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:15:09 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/30 09:59:44 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_dda(t_game *game, int color)
{
	int		steps;
	float	x;
	float	y;
	int		i;

	game->dx = game->ray.end_x - game->player.x;
	game->dy = game->ray.end_x - game->player.y;
	if (fabs(game->dx) > fabs(game->dy))
		steps = fabs(game->dx);
	else
		steps = fabs(game->dy);
	if (steps == 0)
		return ;
	game->x_inc = game->dx / steps;
	game->y_inc = game->dy / steps;
	x = game->player.x;
	y = game->player.y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(&game->gfx, (int)x, (int)y, color);
		x += game->x_inc;
		y += game->y_inc;
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
