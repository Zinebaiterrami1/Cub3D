/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:47:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/25 12:04:02 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_game *game)
{
	char	*texture_files[NUM_TEXTURES];
	int		i;

	i = 0;
	texture_files[0] = "textures/redbrick.xpm";
	texture_files[1] = "textures/colorstone.xpm";
	texture_files[2] = "textures/eagle.xpm";
	texture_files[3] = "textures/purplestone.xpm";
	while (i < NUM_TEXTURES)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->gfx.mlx,
				texture_files[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Error: Could not load texture %s\n", texture_files[i]);
			exit(EXIT_FAILURE);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
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
	int (y), (x);
	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->gfx, x, y, 0x000000);
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
			my_mlx_pixel_put(&game->gfx, x, y, 0x303030);
			x++;
		}
		y++;
	}
}

t_draw_texture	init_draw_texture(t_draw_texture draw_tex)
{
	draw_tex.wall_top = 0;
	draw_tex.wall_bottom = 0;
	draw_tex.screen_x = 0;
	draw_tex.screen_y = 0;
	draw_tex.tex_x = 0;
	draw_tex.tex_y = 0;
	draw_tex.tex_num = 0;
	draw_tex.tex_pos = 0;
	draw_tex.step = 0;
	draw_tex.color = 0;
	draw_tex.wall_height = 0;
	return (draw_tex);
}

void	draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray,
		int wall_height)
{
	t_draw_texture	draw_tex;
	t_texture		*texture;

	draw_tex.wall_top = (HEIGHT / 2) - (wall_height / 2);
	draw_tex.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	if (draw_tex.wall_top < 0)
		draw_tex.wall_top = 0;
	if (draw_tex.wall_bottom > HEIGHT)
		draw_tex.wall_bottom = HEIGHT;
	draw_tex.tex_x = (int)(ray->wall_x * TEX_WIDTH);
	draw_tex.tex_num = determine_texture(ray);
	texture = &game->textures[draw_tex.tex_num];
	draw_tex.step = 1.0 * TEX_HEIGHT / wall_height;
	draw_tex.tex_pos = (draw_tex.wall_top - HEIGHT / 2 + wall_height / 2)
		* draw_tex.step;
	draw_tex.screen_y = draw_tex.wall_top;
	while (draw_tex.screen_y++ < draw_tex.wall_bottom)
	{
		draw_tex.tex_y = (int)draw_tex.tex_pos;
		draw_tex.tex_pos += draw_tex.step;
		draw_tex.color = get_texture_pixel(texture, draw_tex.tex_x,
				draw_tex.tex_y);
		my_mlx_pixel_put(&game->gfx, screen_x, draw_tex.screen_y,
			draw_tex.color);
	}
}
