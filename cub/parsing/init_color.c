/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:47:13 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/14 09:48:59 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	color_test(t_game *game)
{
	if (game->floor_set == 0)
	{
		printf("Warning: floor color not set\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	if (game->ceiling_set == 0)
	{
		printf("Warning: ceiling color not set\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
}

void	init_color_set(t_game *game)
{
	game->floor_set = 0;
	game->ceiling_set = 0;
}
