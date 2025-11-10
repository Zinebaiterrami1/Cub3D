/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_inside.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/10 21:52:25 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

int	is_player(char c)
{
	return (c == 'W' || c == 'E' || c == 'N' || c == 'S');
}

int	check_zero(t_map map, int x, int y)
{
	if (map.grid[x - 1][y] == ' ' || map.grid[x + 1][y] == ' '
		|| map.grid[x][y - 1] == ' ' || map.grid[x][y + 1] == ' '
		|| map.grid[x][y + 1] == '\0' || map.grid[x][y - 1] == '\0'
		|| map.grid[x - 1][y] == '\0' || map.grid[x + 1][y] == '\0')
	{
		return (0);
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

// Helper to skip leading spaces
static int	skip_leading_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

// Helper to find the actual end of content (excluding trailing spaces)
static int	find_content_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t' || line[i
				- 1] == '\0'))
		i--;
	return (i);
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

int	check_space_map(t_map map)
{
	int	x;
	int	y;
	int	start_y;
	int	end_y;

	x = 1;
	y = 1;
	while (x < map.rows - 1)
	{
		start_y = skip_leading_spaces(map.grid[x]);
		end_y = find_content_end(map.grid[x]);
		y = start_y;
		while (y < end_y && map.grid[x][y])
		{
			if (!check_one(map, x, y))
			{
				printf("Invalid map\nSpace must be surrounded by '1'\n");
				printf("line : %s\n", map.grid[x]);
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
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
