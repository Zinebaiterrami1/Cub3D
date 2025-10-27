/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:15 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/27 20:47:17 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_fov_rays(t_game *game)
{
	t_ray		ray;
	t_cast_ray	data;
	int			i;

	data.start_angle = game->player.angle - FOV / 2;
	data.angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray.ray_angle = data.start_angle + i * data.angle_step;
		ray = cast_ray_textured(game, ray.ray_angle);
		game->rays[i] = ray;
		game->ray_distances[i] = ray.dist;
		ray.end_x = game->player.x + cos(ray.ray_angle) * ray.dist;
		ray.end_y = game->player.y + sin(ray.ray_angle) * ray.dist;
		draw_line_dda(&game->gfx, game->player.x, game->player.y, ray.end_x,
			ray.end_y, 0x00FF00);
		i++;
	}
}

float	cast_ray(t_game *game, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	ray_dx;
	float	ray_dy;

	ray_x = game->player.x;
	ray_y = game->player.y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	while (!is_wall(game, ray_x, ray_y))
	{
		ray_x += ray_dx * 0.1f;
		ray_y += ray_dy * 0.1f;
	}
	return (sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y,
				2)));
}

void	render_3d(t_game *game)
{
	int			i;
	t_rend_t	rend;

	i = 0;
	while (i < NUM_RAYS)
	{
		rend.ray_angle = (game->player.angle - (FOV / 2.0f)) + ((float)i
				/ NUM_RAYS) * FOV;
		rend.dist = game->ray_distances[i];
		rend.corrected_dist = rend.dist * cos(rend.ray_angle
				- game->player.angle);
		rend.proj_plane = (WIDTH / 2) / tan(FOV / 2);
		rend.wall_height = (TILE_SIZE / rend.corrected_dist) * rend.proj_plane;
		rend.wall_top = (HEIGHT / 2) - (rend.wall_height / 2);
		rend.wall_bottom = (HEIGHT / 2) + (rend.wall_height / 2);
		if (rend.wall_top < 0)
			rend.wall_top = 0;
		if (rend.wall_bottom > HEIGHT)
			rend.wall_bottom = HEIGHT;
		i++;
	}
}

double	ray_correct(double ray_angle)
{
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * M_PI);
	if (ray_angle >= (2 * M_PI))
		ray_angle = ray_angle - (2 * M_PI);
	return (ray_angle);
}

int	mouse_move(int x, int y, t_game *win)
{
	double	dx;
	double	dy;
	double	angle;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	angle = atan2(dx, dy);
	win->player.angle = angle;
	win->player.angle = ray_correct(win->player.angle);
	return (0);
}
