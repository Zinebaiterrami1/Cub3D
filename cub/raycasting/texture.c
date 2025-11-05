/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:47:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/05 14:33:39 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	setup_draw_texture(t_game *game, t_ray *ray, int wall_height)
{
	t_texture	*texture;
	int			tex_num;

	game->dt.wall_top = (HEIGHT / 2) - (wall_height / 2);
	game->dt.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	if (game->dt.wall_top < 0)
		game->dt.wall_top = 0;
	if (game->dt.wall_bottom > HEIGHT)
		game->dt.wall_bottom = HEIGHT;
	tex_num = determine_texture(ray);
	if (tex_num < 0 || tex_num >= NUM_TEXTURES)
		tex_num = 0;
	texture = &game->textures[tex_num];
	game->dt.tex_x = (int)(ray->wall_x * texture->width);
	if (game->dt.tex_x < 0)
		game->dt.tex_x = 0;
	if (game->dt.tex_x >= texture->width)
		game->dt.tex_x = texture->width - 1;
	game->dt.step = (float)texture->height / (float)wall_height;
	game->dt.tex_pos = (game->dt.wall_top - HEIGHT / 2 + wall_height / 2)
		* game->dt.step;
	game->dt.texture = *texture;
}

void	draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray,
		int wall_height)
{
	setup_draw_texture(game, ray, wall_height);
	game->dt.screen_y = game->dt.wall_top;
	while (game->dt.screen_y < game->dt.wall_bottom)
	{
		game->dt.tex_y = (int)game->dt.tex_pos;
		if (game->dt.tex_y < 0)
			game->dt.tex_y = 0;
		if (game->dt.tex_y >= game->dt.texture.height)
			game->dt.tex_y = game->dt.texture.height - 1;
		game->dt.tex_pos += game->dt.step;
		game->dt.color = get_texture_pixel(&game->dt.texture,
				game->dt.tex_x, game->dt.tex_y);
		my_mlx_pixel_put(&game->gfx, screen_x, game->dt.screen_y,
			game->dt.color);
		game->dt.screen_y++;
	}
}
