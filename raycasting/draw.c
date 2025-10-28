/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:15:09 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/28 11:43:54 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_tile(t_mlx *mlx, int x, int y, int size, int color)
{
	int	j;
	int	i;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(mlx, x + i, y + j, color);
			j++;
		}
		i++;
	}
}


void	draw_line_dda(t_mlx *mlx, float x0, float y0, float x1, float y1,
		int color)
{
	float	dx;
	float	dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;

	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps == 0)
		return ;
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = x0;
	y = y0;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(mlx, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}




void	draw_minimap(t_game *game)
{
	int	tile;
	int	color;
	int	yy;
	int	xx;
	int	px;
	int	py;
	int	size;
	int	x;
	int	y;
	int	dy;
	int	dx;

	tile = 8;
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.cols)
		{
			if (game->map.grid[y][x] == '1')
				color = 0x444444;
			else if (game->map.grid[y][x] == '0')
				color = 0xDDDDDD;
			yy = 0;
			while (yy < tile)
			{
				xx = 0;
				while (xx < tile)
				{
					my_mlx_pixel_put(&game->gfx,
						x * tile + xx,
						y * tile + yy,
						color);
					xx++;
				}
				yy++;
			}
			x++;
		}
		y++;
	}
	px =  (int)((game->player.x / TILE_SIZE) * tile);
	py =  (int)((game->player.y / TILE_SIZE) * tile);
	size = 4;
	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			my_mlx_pixel_put(&game->gfx, px + dx, py + dy, 0xFF3333);
			dx++;
		}
		dy++;
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
