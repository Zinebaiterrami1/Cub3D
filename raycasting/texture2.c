/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:46:50 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/31 15:40:41 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_3d_textured(t_game *game)
{
	float			fov_radians;
	t_draw_texture	draw_tex;
	t_ray			temp_ray;
	t_ray			ray;

	fov_radians = FOV_DEGREES * (M_PI / 180.0f);
	clear_screen(&game->gfx);
	draw_sky_and_floor(game);
	ray.start_angle = game->player.angle - fov_radians / 2;
	ray.angle_step = fov_radians / NUM_RAYS;
	draw_tex.screen_x = 0;
	while (draw_tex.screen_x < NUM_RAYS)
	{
		ray.ray_angle = ray.start_angle + draw_tex.screen_x * ray.angle_step;
		ray.dist = game->ray_distances[draw_tex.screen_x];
		ray.corrected_dist = ray.dist * cos(ray.ray_angle - game->player.angle);
		ray.proj_plane = (WIDTH / 2) / tan(fov_radians / 2);
		draw_tex.wall_height = (TILE_SIZE / ray.corrected_dist)
			* ray.proj_plane;
		temp_ray = game->rays[draw_tex.screen_x];
		temp_ray.dist = ray.dist;
		temp_ray.angle = ray.ray_angle;
		temp_ray.raydx = cos(ray.ray_angle);
		temp_ray.raydy = sin(ray.ray_angle);
		draw_textured_wall_slice(game, draw_tex.screen_x, &temp_ray,
			draw_tex.wall_height);
		draw_tex.screen_x++;
	}
}

void	init_ray_data(t_cast_ray *data, t_game *game, t_ray *ray)
{
	ray->hit = 0;
	if (ray->raydx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (game->player.x / TILE_SIZE - data->mapx)
			* ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (data->mapx + 1.0 - game->player.x / TILE_SIZE)
			* ray->deltadistx;
	}
	if (ray->raydy < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (game->player.y / TILE_SIZE - data->mapy)
			* ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (data->mapy + 1.0 - game->player.y / TILE_SIZE)
			* ray->deltadisty;
	}
}

void	calculation_dda(t_ray *ray, t_cast_ray *data, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			data->mapx += ray->stepx;
			data->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			data->mapy += ray->stepy;
			data->side = 1;
		}
		if (data->mapx < 0 || data->mapx >= game->map.cols || data->mapy < 0
			|| data->mapy >= game->map.rows)
		{
			ray->hit = 1;
			break ;
		}
		if (game->map.grid[data->mapy][data->mapx] > '0')
			ray->hit = 1;
	}
}

void	performe_dda(t_ray *ray, t_cast_ray *data, t_game *game)
{
	calculation_dda(ray, data, game);
	if (data->side == 0)
		data->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		data->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

t_ray	cast_ray_textured(t_game *game, float ray_angle)
{
	t_ray		ray;
	t_cast_ray	data;

	ray = init_ray();
	data = init_cast_ray();
	ray.angle = ray_angle;
	ray.raydx = cos(ray.angle);
	ray.raydy = sin(ray.angle);
	data.mapx = (int)(game->player.x / TILE_SIZE);
	data.mapy = (int)(game->player.y / TILE_SIZE);
	ray.deltadistx = fabs(1 / ray.raydx);
	ray.deltadisty = fabs(1 / ray.raydy);
	init_ray_data(&data, game, &ray);
	performe_dda(&ray, &data, game);
	calculate_wall_x(game, &ray, &data);
	if (data.mapx >= 0 && data.mapx < game->map.cols && data.mapy >= 0
		&& data.mapy < game->map.rows)
		ray.wall_type = game->map.grid[data.mapy][data.mapx];
	else
		ray.wall_type = '1';
	return (ray);
}
