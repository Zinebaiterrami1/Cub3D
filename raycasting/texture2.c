/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:46:50 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/04 13:28:42 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	process_single_ray(t_game *game, t_draw_texture *draw_tex)
{
	t_ray	temp_ray;

	game->ray.ray_angle = game->ray.start_angle + draw_tex->screen_x
		* game->ray.angle_step;
	game->ray.dist = game->ray_distances[draw_tex->screen_x];
	game->ray.corrected_dist = game->ray.dist * cos(game->ray.ray_angle
			- game->player.angle);
	game->ray.proj_plane = (WIDTH / 2) / tan(FOV_DEGREES * (M_PI / 180.0f) / 2);
	draw_tex->wall_height = (TILE_SIZE / game->ray.corrected_dist)
		* game->ray.proj_plane;
	temp_ray = game->rays[draw_tex->screen_x];
	temp_ray.dist = game->ray.dist;
	temp_ray.angle = game->ray.ray_angle;
	temp_ray.raydx = cos(game->ray.ray_angle);
	temp_ray.raydy = sin(game->ray.ray_angle);
	draw_textured_wall_slice(game, draw_tex->screen_x, &temp_ray,
		draw_tex->wall_height);
}

void	render_3d_textured(t_game *game)
{
	t_draw_texture	draw_tex;

	clear_screen(&game->gfx);
	draw_sky_and_floor(game);
	game->ray.start_angle = game->player.angle - FOV_DEGREES * (M_PI / 180.0f)
		/ 2;
	game->ray.angle_step = FOV_DEGREES * (M_PI / 180.0f) / NUM_RAYS;
	draw_tex.screen_x = 0;
	while (draw_tex.screen_x < NUM_RAYS)
	{
		process_single_ray(game, &draw_tex);
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
