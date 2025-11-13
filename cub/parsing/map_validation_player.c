/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:19:50 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/12 11:04:14 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dx = 0;
		p->dy = -1;
		p->angle = 3 * M_PI / 2;
	}
	else if (c == 'S')
	{
		p->dx = 0;
		p->dy = 1;
		p->angle = M_PI / 2;
	}
	else if (c == 'E')
	{
		p->dx = 1;
		p->dy = 0;
		p->angle = 0;
	}
	else if (c == 'W')
	{
		p->dx = -1;
		p->dy = 0;
		p->angle = M_PI;
	}
}

int	check_player_pos(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x < map->rows - 1)
	{
		y = 1;
		while (y < (int)ft_strlen(map->grid[x]) - 1)
		{
			if (map->grid[x][y] == 'N' || map->grid[x][y] == 'S'
				|| map->grid[x][y] == 'E' || map->grid[x][y] == 'W')
			{
				map->player.x = x;
				map->player.y = y;
				set_player_dir(&map->player, map->grid[x][y]);
				map->grid[x][y] = '0';
				map->count_pos++;
			}
			y++;
		}
		x++;
	}
	return (count_pos(map));
}

int	count_pos(t_map *map)
{
	if (map->count_pos != 1)
	{
		printf("count: %d\n", map->count_pos);
		return (printf("Invalid map\nmust be only one player position\n"), 0);
	}
	return (1);
}

void	valid_map(t_map *map)
{
	while (map->grid[map->rows])
		map->rows++;
	if (!check_new_line(*map))
		print_error_map(map);
	if (!check_first_last_line(map->grid))
		print_error_map(map);
	if (!check_left_right(map->grid))
		print_error_map(map);
	if (!check_map2(map->grid))
		print_error_map(map);
	if (!check_inside(*map))
		print_error_map(map);
	if (!check_inside_2(*map))
		print_error_map(map);
	if (!check_player_pos(map))
		print_error_map(map);
}

void	print_valid(void)
{
	printf("\nValid map✅✅\n");
}
