/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:40:19 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/01 10:19:42 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			}
			y++;
		}
		x++;
	}
	count_pos(map);
	return (1);
}

int	count_pos(t_map *map)
{
	int	count_pos;
	int	x;
	int	y;

	count_pos = 0;
	x = 1;
	y = 1;
	while (x < map->rows - 1)
	{
		y = 1;
		while (y < (int)ft_strlen(map->grid[x]) - 1)
		{
			if (map->grid[x][y] == 'N' || map->grid[x][y] == 'S'
				|| map->grid[x][y] == 'E' || map->grid[x][y] == 'W')
				count_pos++;
			y++;
		}
		x++;
	}
	if (count_pos != 1)
	{
		return (printf("Invalid map\nmust be only one player position\n"), 0);
	}
	return (1);
}

int	check_inside_2(t_map map)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	y = 0;
	while (x < map.rows && map.grid[x][y] != '\0')
	{
		y = 0;
		while (y < map.cols && map.grid[x][y] != '\0')
		{
			c = map.grid[x][y];
			if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1'
				&& c != '0' && c != ' ' && c != '\t' && c == '\0')
			{
				printf("Invalid map\nWrong character %c at (%d, %d)\n", c, x,
					y);
				printf("line %s\n", map.grid[x]);
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	check_space_map(t_map map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x < map.rows - 1)
	{
		y = 1;
		while (y < map.cols - 1)
		{
			if (map.grid[x][y] == ' ')
			{
				if (map.grid[x - 1][y] != '1' && map.grid[x + 1][y] != '1'
					&& map.grid[x][y - 1] != '1' && map.grid[x][y + 1] != '1')
				{
					printf("Invalid map\nSpace must be surrounded by '1'\n");
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}

void	valid_map(t_map *map)
{
	if (!check_top_border(*map))
		print_error();
	if (!check_bottom_border(*map))
		print_error();
	if (!check_left_right_border(*map))
		print_error();
	if (!check_inside(*map))
		print_error();
	if (!check_inside_2(*map))
		print_error();
	if (!check_player_pos(map))
		print_error();
	if (!check_space_map(*map))
		print_error();
	printf("✅ Map is valid!\n");
}
