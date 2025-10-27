/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:56:56 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/27 21:26:47 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//----------------LOAD TEXTURE----------------------//
void load_texture_gun(t_game *game)
{
    int i;
    char *gun_path[2];

    i = 0;
    gun_path[0] = "textures/sprites/gun-_2_.xpm";
    gun_path[1] = "textures/sprites/gun_shoot-_1_.xpm";
    while(i < 2)
    {
        game->gun.gun_texture[i].img = mlx_xpm_file_to_image(game->gfx.mlx,
            gun_path[i], &game->gun.gun_texture[i].width,
				&game->gun.gun_texture[i].height);
        if(!game->gun.gun_texture[i].img)
        {
            printf("Error: Could not load gun texture! : %s\n", gun_path[i]);
            exit(EXIT_FAILURE);
        }
        game->gun.gun_texture[i].addr = mlx_get_data_addr(game->gun.gun_texture[i].img,
				&game->gun.gun_texture[i].bpp, &game->gun.gun_texture[i].line_len,
				&game->gun.gun_texture[i].endian);
        i++;
    }
}

//----------------DRAW PLAYER WITH GUN----------------------//
t_gun init_gun()
{
    t_gun gun;

    gun.current_frame = 0;
    gun.frame_timer = 0;
    gun.shooting = 0;
    gun.gun_height = 300;
    gun.gun_width = 400;
    gun.pos_x = (WIDTH / 2) - (gun.gun_width / 2);
    gun.pos_y = HEIGHT - gun.gun_height;
	return (gun);
}

// void draw_gun(t_game *game)
// {
//     t_gun gun;
//     // int x;
//     // int y;

//     // x = 0;
//     // y = 0;
//     gun = init_gun();
//     while(gun.pos_y < gun.gun_height)
//     {
//         x = 0;
//         while(gun.pos_x < gun.gun_width)
//         {
//             my_mlx_pixel_put(game->gfx.mlx, x, y, &game->gun.gun_texture[game->gun.current_frame]);
//             gun.pos_x++;
//         }
//         gun.pos_y++;
//     }
// }

void draw_gun(t_game *game)
{
    t_texture *current_texture = &game->gun.gun_texture[game->gun.current_frame];
    int x, y;
    
    // Draw the gun texture
    for (y = 0; y < game->gun.gun_height; y++)
    {
        for (x = 0; x < game->gun.gun_width; x++)
        {
            // Get pixel from gun texture (with transparency handling)
            unsigned int color = get_texture_pixel(current_texture, x, y);
            
            // Skip transparent pixels (assuming 0x000000 is transparent)
            if ((color & 0x00FFFFFF) != 0x000000)
            {
                int screen_x = game->gun.pos_x + x;
                int screen_y = game->gun.pos_y + y;
                my_mlx_pixel_put(&game->gfx, screen_x, screen_y, color);
            }
        }
    }
}

//--------------------shot_Gun

void update_gun(t_game *game)
{
	if (game->gun.shooting)
	{
		game->gun.frame_timer--;
		if (game->gun.frame_timer <= 0)
		{
			game->gun.current_frame = 0; // back to idle
			game->gun.shooting = 0;
		}
	}
}

void shoot(t_game *game)
{
    if (!game->gun.shooting)
    {
        game->gun.shooting = 1;
        game->gun.current_frame = 1;  // Switch to shooting texture
        game->gun.frame_timer = 2;   // Show shooting frame for 10 frames
        
        // Add shooting logic here (raycast to check if enemy hit, etc.)
        printf("BANG!\n");
    }
}

