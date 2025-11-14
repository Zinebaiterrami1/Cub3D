/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:50:14 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 09:26:59 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	close_window(void *param)
{
	t_game	*game;

	if (!param)
	{
		printf("Error: close_window called with NULL\n");
		gc_free_all();
		exit(1);
	}
	game = (t_game *)param;
	cleanup_game(game);
	gc_free_all();
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

int	check_collision(t_game *game, float x, float y)
{
	float	radius;
	float	points[4][2];
	int		i;

	radius = COLLISION_RADIUS;
	points[0][0] = x + radius;
	points[0][1] = y + radius;
	points[1][0] = x - radius;
	points[1][1] = y + radius;
	points[2][0] = x + radius;
	points[2][1] = y - radius;
	points[3][0] = x - radius;
	points[3][1] = y - radius;
	i = 0;
	while (i < 4)
	{
		if (is_wall(game, points[i][0], points[i][1]))
			return (1);
		i++;
	}
	return (is_wall(game, x, y));
}
