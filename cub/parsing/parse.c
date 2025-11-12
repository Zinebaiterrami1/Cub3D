#include "../../cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_borders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:42:04 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/12 10:07:09 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* 
** Normalize map by replacing leading/trailing spaces with '1' (walls)
** This ensures consistent boundaries for validation
*/
void	normalize_map_line(char *line, int max_len)
{
	int	i;
	int	first_content;
	int	last_content;
    (void)max_len;
	i = 0;
	first_content = -1;
	last_content = -1;
	
	// Find first and last non-space/tab character
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			if (first_content == -1)
				first_content = i;
			last_content = i;
		}
		i++;
	}
	
	// Replace leading spaces with '1'
	if (first_content > 0)
	{
		i = 0;
		while (i < first_content)
		{
			if (line[i] == ' ' || line[i] == '\t')
				line[i] = '1';
			i++;
		}
	}
	
	// Replace trailing spaces with '1' (up to last_content)
	if (last_content >= 0)
	{
		i = last_content + 1;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		{
			line[i] = '1';
			i++;
		}
	}
}

/* 
** Normalize entire map before validation
** Call this after reading the map but before validation
*/
void	normalize_map(t_map *map)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = map->cols;
	
	while (i < map->rows)
	{
		if (map->grid[i] && !is_line_empty(map->grid[i]))
			normalize_map_line(map->grid[i], max_len);
		i++;
	}
}

int	check_first(char **maze)
{
	int	x;

	x = 0;
	while (maze[0][x])
	{
		if (maze[0][x] != ' ' && maze[0][x] != '\t' && maze[0][x] != '1'
			&& maze[0][x] != '\n')
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
		if (maze[y][x] != ' ' && maze[y][x] != '\t' && maze[y][x] != '1'
			&& maze[y][x] != '\n')
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

/* ************************************************************************** */
/*                                                                            */
/*   helper.c - UPDATED VERSION                                              */
/*                                                                            */
/* ************************************************************************** */

int	is_player(char c)
{
	return (c == 'W' || c == 'E' || c == 'N' || c == 'S');
}

/* 
** Enhanced check_zero that handles map boundaries properly
** Now checks if indices are within valid bounds
*/
int	check_zero(t_map map, int x, int y)
{
	int	len_current;
	int	len_above;
	int	len_below;

	len_current = ft_strlen(map.grid[x]);
	
	// Check vertical boundaries
	if (x - 1 >= 0)
	{
		len_above = ft_strlen(map.grid[x - 1]);
		if (y >= len_above || map.grid[x - 1][y] == ' ' 
			|| map.grid[x - 1][y] == '\0' || map.grid[x - 1][y] == '\n')
			return (0);
	}
	
	if (x + 1 < map.rows)
	{
		len_below = ft_strlen(map.grid[x + 1]);
		if (y >= len_below || map.grid[x + 1][y] == ' ' 
			|| map.grid[x + 1][y] == '\0' || map.grid[x + 1][y] == '\n')
			return (0);
	}
	
	// Check horizontal boundaries
	if (y - 1 < 0 || y - 1 >= len_current || map.grid[x][y - 1] == ' ' 
		|| map.grid[x][y - 1] == '\0' || map.grid[x][y - 1] == '\n')
		return (0);
	
	if (y + 1 >= len_current || map.grid[x][y + 1] == ' ' 
		|| map.grid[x][y + 1] == '\0' || map.grid[x][y + 1] == '\n')
		return (0);
	
	return (1);
}

int	check_one(t_map map, int x, int y)
{
	if (map.grid[x][y] == ' ' || map.grid[x][y] == '\t')
	{
		if (map.grid[x - 1][y] != '1' || map.grid[x + 1][y] != '1'
			|| map.grid[x][y - 1] != '1' || map.grid[x][y + 1] != '1')
			return (0);
	}
	return (1);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	duplicate_color(void)
{
	printf("Error: Duplicate F (floor) color\n");
	gc_free_all();
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*   check_inside.c - UPDATED VERSION                                        */
/*                                                                            */
/* ************************************************************************** */

int	check_inside(t_map map)
{
	int	x;
	int	y;

	x = 1;
	while (x < map.rows - 1)
	{
		y = 1;
		while (y < map.cols - 1 && map.grid[x][y])
		{
			if (map.grid[x][y] == '0' || is_player(map.grid[x][y]))
			{
				if (!check_zero(map, x, y))
				{
					printf("Invalid map at line %d, col %d\n", x, y);
					printf("'0' or player next to space or boundary\n");
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*   USAGE IN YOUR MAIN VALIDATION FUNCTION                                  */
/*                                                                            */
/* ************************************************************************** */

int	valid_map(t_map *map)
{
	// 1. First, normalize the map to handle spaces properly
	normalize_map(map);
	
	// 2. Check for empty lines in the middle
	if (!check_new_line(*map))
		return (0);
	
	// 3. Check first and last lines
	if (!check_first_last_line(map->grid))
		return (0);
	
	// 4. Check left and right borders
	if (!check_left_right(map->grid))
		return (0);
	
	// 5. Check inside the map (0s and player positions)
	if (!check_inside(*map))
		return (0);
	
	return (1);
}