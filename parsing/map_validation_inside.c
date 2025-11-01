/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_inside.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/01 11:21:30 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_inside(t_map map)
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
			if (map.grid[x][y] == '0')
			{
				if (map.grid[x - 1][y] == ' ' || map.grid[x + 1][y] == ' '
					|| map.grid[x][y - 1] == ' ' || map.grid[x][y + 1] == ' '
					|| map.grid[x][y + 1] == '\0')
				{
					return (printf("Invalid map\n '0' next to space or \\0 \n"),
						0);
				}
			}
			y++;
		}
		x++;
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
