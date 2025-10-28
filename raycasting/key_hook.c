/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:24:24 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/28 10:43:21 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	wrap_mouse_position(int x, int y, t_game *game)
{
	if (x > WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
}

int	rotate_left_right(t_game *game, double rotspeed)
{
	t_player	*p;
	double		tmp_x;

	p = &game->player;
	tmp_x = p->dx;
	p->dx = p->dx * cos(rotspeed) - p->dy * sin(rotspeed);
	p->dy = tmp_x * sin(rotspeed) + p->dy * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
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
int	key_hook(int keycode, void *param)
{
	t_game	*game;
	float	next_x;
	float	next_y;

	game = (t_game *)param;
	next_x = game->player.x;
	next_y = game->player.y;
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
	{
		next_x += game->player.dx;
		next_y += game->player.dy;
	}
	if (keycode == 115)
	{
		next_x -= game->player.dx;
		next_y -= game->player.dy;
	}
	if (keycode == 100)
	{
		next_x += -game->player.dy;
		next_y += game->player.dx;
	}
	if (keycode == 97)
	{
		next_x += game->player.dy;
		next_y += -game->player.dx;
	}
	if (keycode == 65361)
		game->player.angle -= ROT_SPEED;
	if (keycode == 65363)
		game->player.angle += ROT_SPEED;

	 if (keycode == KEY_SPC)  // Space bar for shooting
    {
        shoot(game);
    }
	game->player.dx = cos(game->player.angle) * SPEED;
	game->player.dy = sin(game->player.angle) * SPEED;
	if (!is_wall(game, next_x + (game->player.dx * COLLISION_RADIUS),
			game->player.y))
		game->player.x = next_x;
	if (!is_wall(game, game->player.x, next_y + (game->player.dy
				* COLLISION_RADIUS)))
		game->player.y = next_y;
	update_gun(game);
	clear_screen(&game->gfx);
	draw_fov_rays(game);
	render_3d_textured(game);
	draw_minimap(game);
	draw_gun(game);
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
int	extra_number(const char *a, int i, int num)
{
	while (a[i])
	{
		if (a[i] == 32 || (a[i] >= 9 && a[i] <= 13))
			i++;
		else
			return (1);
	}
	return (num);
}


int	rotate_player(t_game *game, int rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROT_SPEED * rotdir;
	moved += rotate_left_right(game, rotspeed);
	return (moved);
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


