/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:26:40 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/28 11:27:20 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_wall_x(t_game *game, t_ray *ray, t_cast_ray *data)
{
	if (data->side == 0)
		data->wallX = (game->player.y / TILE_SIZE + data->perpWallDist
				* ray->rayDY) - floor(game->player.y / TILE_SIZE
				+ data->perpWallDist * ray->rayDY);
	else
		data->wallX = (game->player.x / TILE_SIZE + data->perpWallDist
				* ray->rayDX) - floor(game->player.x / TILE_SIZE
				+ data->perpWallDist * ray->rayDX);
	ray->wall_x = data->wallX;
	ray->dist = data->perpWallDist * TILE_SIZE;
	ray->side = data->side;
}

t_cast_ray	init_cast_ray(void)
{
	t_cast_ray	data;

	data.wallX = 0;
	data.angle_step = 0;
	data.mapX = 0;
	data.mapY = 0;
	data.perpWallDist = 0;
	data.side = 0;
	data.start_angle = 0;
	return (data);
}

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.angle = 0;
	ray.deltaDistX = 0;
	ray.deltaDistY = 0;
	ray.dist = 0;
	ray.rayDX = 0;
	ray.rayDY = 0;
	ray.wall_type = 0;
	return (ray);
}

int	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDX > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->rayDY > 0)
			return (3);
		else
			return (2);
	}
}
