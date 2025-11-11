/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_inside.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/11 19:56:56 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_map2(char **maze)
{
	int	x;
	int	y;

	y = 0;
	while (maze[y] != NULL)
	{
		x = 0;
		while (maze[y][x])
		{
			if (maze[y][x] == '1' || maze[y][x] == '0' || maze[y][x] == ' '
				|| maze[y][x] == '\t' || maze[y][x] == 'N' || maze[y][x] == 'S'
				|| maze[y][x] == 'E' || maze[y][x] == 'W')
				x++;
			else
			{
				printf("line : %s\n", maze[y]);
				return (printf("Invalid character in the maze :/\n"), 0);
			}
		}
		y++;
	}
	return (1);
}

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
					|| map.grid[x][y + 1] == '\0' || map.grid[x][y - 1] == '\0'
					|| map.grid[x - 1][y] == '\0' || map.grid[x + 1][y] == '\0')
					return (printf("Invalid map\n '0' next to space or \\0 \n"),
						0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	check_inside_2(t_map map)
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
			if (is_player(map.grid[x][y]))
			{
				if (!check_zero(map, x, y))
				{
					printf("Invalid map\n player next to space or \\0 \n");
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}
