/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_borders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:42:04 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/11 11:07:25 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_first(char **maze)
{
	int	x;

	x = 0;
	if (!maze[0] || maze[0][0] == '\0' || maze[0][0] != '1')
		return (0);
	while (maze[0][x])
	{
		if (maze[0][x] != ' ' && maze[0][x] != '\t' && maze[0][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_last(char **maze)
{
	int	x;
	int	y;

	y = 0;
	while (maze[y])
	{
		if (maze[y][0] == '\0')
			break ;
		y++;
	}
	y--;
	x = 0;
	while (maze[y][x])
	{
		if (maze[y][x] != ' ' && maze[y][x] != '\t' && maze[y][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	check_first_last_line(char **maze)
{
	if (!check_first(maze))
	{
		printf("First line should contain just 1s and spaces!\n");
		return (0);
	}
	if (!check_last(maze))
	{
		printf("Last line should contain just 1s and spaces!\n");
		return (0);
	}
	return (1);
}

int	check_left_right(char **maze)
{
	int	y;
	int	x;

	y = 0;
	while (maze[y])
	{
		x = 0;
		while (maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '\n')
			x++;
		if (maze[y][x] != '\0' && maze[y][x] != '1')
			return (printf("Error: left border open at line %d\n", y), 0);
		x = 0;
		while (maze[y][x])
			x++;
		x--;
		while (x > 0 && (maze[y][x] == ' ' || maze[y][x] == '\t'
				|| maze[y][x] == '\n'))
			x--;
		if (x >= 0 && maze[y][x] != '1')
			return (printf("Error: right border open at line %d\n", y), 0);
		y++;
	}
	return (1);
}

int	check_new_line(t_map map)
{
	int	x;
	int	empty_found;

	x = 0;
	empty_found = 0;
	while (x < map.rows)
	{
		if (is_line_empty(map.grid[x]))
			empty_found = 1;
		else if (empty_found)
		{
			printf("Invalid map: content found after empty line.\n");
			return (0);
		}
		x++;
	}
	return (1);
}
