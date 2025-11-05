/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:56:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/05 14:05:54 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

//----------------LOAD TEXTURE----------------------//
void	load_texture_gun(t_game *game)
{
	int		i;
	char	*gun_path[2];

	i = 0;
	gun_path[0] = "textures/sprites/gun-_2_.xpm";
	gun_path[1] = "textures/sprites/gun_shoot-_1_.xpm";
	while (i < 2)
	{
		game->gun.gun_texture[i].img = mlx_xpm_file_to_image(game->gfx.mlx,
				gun_path[i],
				&game->gun.gun_texture[i].width,
				&game->gun.gun_texture[i].height);
		if (!game->gun.gun_texture[i].img)
		{
			printf("Error: Could not load gun texture! : %s\n", gun_path[i]);
			exit(EXIT_FAILURE);
		}
		game->gun.gun_texture[i].addr = mlx_get_data_addr(
				game->gun.gun_texture[i].img,
				&game->gun.gun_texture[i].bpp,
				&game->gun.gun_texture[i].line_len,
				&game->gun.gun_texture[i].endian);
		i++;
	}
}

//----------------DRAW PLAYER WITH GUN----------------------//
t_gun	init_gun(void)
{
	t_gun	gun;

	gun.current_frame = 0;
	gun.frame_timer = 0;
	gun.shooting = 0;
	gun.gun_height = 300;
	gun.gun_width = 400;
	gun.pos_x = (WIDTH / 2) - (gun.gun_width / 2);
	gun.pos_y = HEIGHT - gun.gun_height;
	gun.screen_x = 0;
	gun.screen_y = 0;
	gun.color = 0;
	return (gun);
}

void	draw_gun(t_game *game)
{
	t_texture	*current_texture;

	int (x);
	int (y);
	x = 0;
	y = 0;
	current_texture = &game->gun.gun_texture[game->gun.current_frame];
	while (y < game->gun.gun_height)
	{
		x = 0;
		while (x < game->gun.gun_width)
		{
			game->gun.color = get_texture_pixel(current_texture, x, y);
			if ((game->gun.color & 0x00FFFFFF) != 0x000000)
			{
				game->gun.screen_x = game->gun.pos_x + x;
				game->gun.screen_y = game->gun.pos_y + y;
				my_mlx_pixel_put(&game->gfx, game->gun.screen_x,
					game->gun.screen_y, game->gun.color);
			}
			x++;
		}
		y++;
	}
}

//--------------------shot_Gun
void	update_gun(t_game *game)
{
	if (game->gun.shooting)
	{
		game->gun.frame_timer--;
		if (game->gun.frame_timer <= 0)
		{
			game->gun.current_frame = 0;
			game->gun.shooting = 0;
		}
	}
}

void	shoot(t_game *game)
{
	if (!game->gun.shooting)
	{
		game->gun.shooting = 1;
		game->gun.current_frame = 1;
		game->gun.frame_timer = 2;
	}
}
