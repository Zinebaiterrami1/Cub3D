/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:46:50 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/27 12:38:08 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	render_3d_textured(t_game *game)
{
	t_draw_texture	draw_tex;
	t_ray			temp_ray;
	t_ray			ray;

	clear_screen(&game->gfx);
	draw_sky_and_floor(game);
	ray.start_angle = game->player.angle - FOV / 2;
	ray.angle_step = FOV / NUM_RAYS;
	draw_tex.screen_x = 0;
	while (draw_tex.screen_x++ < NUM_RAYS)
	{
		ray.ray_angle = ray.start_angle + draw_tex.screen_x * ray.angle_step;
		ray.dist = game->ray_distances[draw_tex.screen_x];
		ray.corrected_dist = ray.dist * cos(ray.ray_angle - game->player.angle);
		ray.proj_plane = (WIDTH / 2) / tan(FOV / 2);
		draw_tex.wall_height = (TILE_SIZE / ray.corrected_dist)
			* ray.proj_plane;
		temp_ray = game->rays[draw_tex.screen_x];
		temp_ray.dist = ray.dist;
		temp_ray.angle = ray.ray_angle;
		temp_ray.rayDX = cos(ray.ray_angle);
		temp_ray.rayDY = sin(ray.ray_angle);
		draw_textured_wall_slice(game, draw_tex.screen_x, &temp_ray,
			draw_tex.wall_height);
	}
}

void	init_ray_data(t_cast_ray *data, t_game *game, t_ray *ray)
{
	ray->hit = 0;
	if (ray->rayDX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.x / TILE_SIZE - data->mapX)
			* ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (data->mapX + 1.0 - game->player.x / TILE_SIZE)
			* ray->deltaDistX;
	}
	if (ray->rayDY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.y / TILE_SIZE - data->mapY)
			* ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (data->mapY + 1.0 - game->player.y / TILE_SIZE)
			* ray->deltaDistY;
	}
}

void	performe_dda(t_ray *ray, t_cast_ray *data, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			data->mapX += ray->stepX;
			data->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			data->mapY += ray->stepY;
			data->side = 1;
		}
		if (game->map.grid[data->mapY][data->mapX] > '0')
			ray->hit = 1;
	}
	if (data->side == 0)
		data->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		data->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

t_ray	cast_ray_textured(t_game *game, float ray_angle)
{
	t_ray ray = {0};
	t_cast_ray data = {0};


	ray.angle = ray_angle;
	ray.rayDX = cos(ray.angle);
	ray.rayDY = sin(ray.angle);
	data.mapX = (int)(game->player.x / TILE_SIZE);
	data.mapY = (int)(game->player.y / TILE_SIZE);
	ray.deltaDistX = fabs(1 / ray.rayDX);
	ray.deltaDistY = fabs(1 / ray.rayDY);
	init_ray_data(&data, game, &ray);
	performe_dda(&ray, &data, game);
	if (data.side == 0)
		data.wallX = (game->player.y / TILE_SIZE + data.perpWallDist
				* ray.rayDY) - floor(game->player.y / TILE_SIZE
				+ data.perpWallDist * ray.rayDY);
	else
		data.wallX = (game->player.x / TILE_SIZE + data.perpWallDist
				* ray.rayDX) - floor(game->player.x / TILE_SIZE
				+ data.perpWallDist * ray.rayDX);
	ray.wall_x = data.wallX;
	ray.dist = data.perpWallDist * TILE_SIZE;
	ray.side = data.side;
	ray.wall_type = game->map.grid[data.mapY][data.mapX];
	return (ray);
}
