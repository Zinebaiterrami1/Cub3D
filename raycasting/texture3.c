/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:26:40 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/31 15:27:35 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_wall_x(t_game *game, t_ray *ray, t_cast_ray *data)
{
	if (data->side == 0)
		data->wallx = (game->player.y / TILE_SIZE + data->perpwalldist
				* ray->raydy) - floor(game->player.y / TILE_SIZE
				+ data->perpwalldist * ray->raydy);
	else
		data->wallx = (game->player.x / TILE_SIZE + data->perpwalldist
				* ray->raydx) - floor(game->player.x / TILE_SIZE
				+ data->perpwalldist * ray->raydx);
	ray->wall_x = data->wallx;
	ray->dist = data->perpwalldist * TILE_SIZE;
	ray->side = data->side;
}

t_cast_ray	init_cast_ray(void)
{
	t_cast_ray	data;

	data.wallx = 0;
	data.angle_step = 0;
	data.mapx = 0;
	data.mapy = 0;
	data.perpwalldist = 0;
	data.side = 0;
	data.start_angle = 0;
	return (data);
}

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.angle = 0;
	ray.deltadistx = 0;
	ray.deltadisty = 0;
	ray.dist = 0;
	ray.raydx = 0;
	ray.raydy = 0;
	ray.wall_type = 0;
	return (ray);
}

int	determine_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydx > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->raydy > 0)
			return (3);
		else
			return (2);
	}
}
