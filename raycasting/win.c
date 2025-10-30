/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:50:14 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/30 21:38:20 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	clear_screen(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	is_wall(t_game *game, float x, float y)
{
	int		mx;
	int		my;
	char	c;

	mx = (int)(x / TILE_SIZE);
	my = (int)(y / TILE_SIZE);
	if (mx < 0 || mx >= game->map.cols || my < 0 || my >= game->map.rows)
		return (1);
	c = game->map.grid[my][mx];
	return (c != '0');
}
