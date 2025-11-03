/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:47:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/03 14:12:26 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_game *game, t_textures *tex)
{
	char	*texture_files[NUM_TEXTURES];
	int		i;

	i = 0;
	texture_files[0] = tex->no;
	texture_files[1] = tex->so;
	texture_files[2] = tex->ea;
	texture_files[3] = tex->we;
	while (i < NUM_TEXTURES)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->gfx.mlx,
				texture_files[i],
				&game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Error: Could not load texture %s\n", texture_files[i]);
			exit(EXIT_FAILURE);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp,
				&game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

unsigned int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)(tex->addr + pixel));
}

void	draw_sky_and_floor(t_game *game)
{
	int (y);
	int (x);
	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->gfx, x, y, game->floor_color);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->gfx, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
}


void draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray, int wall_height)
{
    t_draw_texture dt;
    t_texture *texture;

    init_draw_texture(&dt);  
    dt.wall_top = (HEIGHT / 2) - (wall_height / 2);
    dt.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
    if (dt.wall_top < 0) dt.wall_top = 0;
    if (dt.wall_bottom > HEIGHT) dt.wall_bottom = HEIGHT;

    dt.tex_x = (int)(ray->wall_x * TEX_WIDTH);
    dt.tex_num = determine_texture(ray);

    if (dt.tex_num < 0 || dt.tex_num >= NUM_TEXTURES)
        dt.tex_num = 0;

    texture = &game->textures[dt.tex_num];
    dt.step = (float)TEX_HEIGHT / (float)wall_height;
    dt.tex_pos = (dt.wall_top - HEIGHT / 2 + wall_height / 2) * dt.step;
    dt.screen_y = dt.wall_top;

    while (dt.screen_y < dt.wall_bottom)
    {
        dt.tex_y = (int)dt.tex_pos & (TEX_HEIGHT - 1);
        dt.tex_pos += dt.step;
        dt.color = get_texture_pixel(texture, dt.tex_x, dt.tex_y);
        my_mlx_pixel_put(&game->gfx, screen_x, dt.screen_y, dt.color);
        dt.screen_y++;
    }
}

