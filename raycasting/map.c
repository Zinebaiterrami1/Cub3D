/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:59:23 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 15:38:17 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_tile(t_game *game, int color)
{
	int	yy;
	int	xx;

	yy = 0;
	while (yy < game->draw.tile)
	{
		xx = 0;
		while (xx < game->draw.tile)
		{
			my_mlx_pixel_put(&game->gfx,
				game->draw.x * game->draw.tile + xx,
				game->draw.y * game->draw.tile + yy,
				color);
			xx++;
		}
		yy++;
	}
}

static void	draw_map(t_game *game)
{
	game->draw.tile = 8;
	game->draw.y = 0;
	while (game->draw.y < game->map.rows)
	{
		game->draw.x = 0;
		while (game->draw.x < game->map.cols)
		{
			if (game->map.grid[game->draw.y][game->draw.x] == '1')
				draw_tile(game, 0x000000);
			else if (game->map.grid[game->draw.y][game->draw.x] == '0')
				draw_tile(game, 0xDDDDDD);
			game->draw.x++;
		}
		game->draw.y++;
	}
}

static void	draw_player_on_minimap(t_game *game)
{
	int	dx;
	int	dy;

	game->draw.px = (int)((game->player.x / TILE_SIZE) * game->draw.tile);
	game->draw.py = (int)((game->player.y / TILE_SIZE) * game->draw.tile);
	game->draw.size = 4;
	dy = 0;
	while (dy < game->draw.size)
	{
		dx = 0;
		while (dx < game->draw.size)
		{
			my_mlx_pixel_put(&game->gfx,
				game->draw.px + dx,
				game->draw.py + dy,
				0xFF3333);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_map(game);
	draw_player_on_minimap(game);
}
