/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:50:34 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/05 14:06:16 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_draw(t_draw *draw)
{
	draw->tile = 0;
	draw->color = 0;
	draw->yy = 0;
	draw->xx = 0;
	draw->px = 0;
	draw->py = 0;
	draw->size = 0;
	draw->x = 0;
	draw->y = 0;
	draw->dx = 0;
	draw->dy = 0;
}

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->s = 0;
	keys->a = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_all_rays(t_ray rays[NUM_RAYS])
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		init_ray(&rays[i]);
		i++;
	}
}

void	init_textures(t_texture textures[NUM_TEXTURES])
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		textures[i].img = NULL;
		textures[i].addr = NULL;
		textures[i].width = 0;
		textures[i].height = 0;
		textures[i].bpp = 0;
		textures[i].line_len = 0;
		textures[i].endian = 0;
		i++;
	}
}

void	f(t_game *game)
{
	mlx_destroy_display(game->gfx.mlx);
	free(game->gfx.mlx);
}
