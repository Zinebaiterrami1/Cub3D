/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:24:24 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/05 14:04:18 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define KEY_SPC 32

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

static void	move_player(t_game *game, float *next_x, float *next_y)
{
	if (game->keys.w)
	{
		*next_x += game->player.dx;
		*next_y += game->player.dy;
	}
	if (game->keys.s)
	{
		*next_x -= game->player.dx;
		*next_y -= game->player.dy;
	}
	if (game->keys.a)
	{
		*next_x += game->player.dy;
		*next_y -= game->player.dx;
	}
	if (game->keys.d)
	{
		*next_x -= game->player.dy;
		*next_y += game->player.dx;
	}
}

void	handle_keys(t_game *game)
{
	float	next_x;
	float	next_y;

	next_x = game->player.x;
	next_y = game->player.y;
	if (game->keys.left)
		game->player.angle -= ROT_SPEED;
	if (game->keys.right)
		game->player.angle += ROT_SPEED;
	game->player.dx = cos(game->player.angle) * SPEED;
	game->player.dy = sin(game->player.angle) * SPEED;
	move_player(game, &next_x, &next_y);
	if (!check_collision(game, next_x, game->player.y))
		game->player.x = next_x;
	if (!check_collision(game, game->player.x, next_y))
		game->player.y = next_y;
}

int	game_loop(t_game *game)
{
	handle_keys(game);
	clear_screen(&game->gfx);
	draw_fov_rays(game);
	render_3d_textured(game);
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
	return (0);
}
