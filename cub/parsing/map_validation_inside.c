/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_inside.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/10 15:41:43 by zait-err         ###   ########.fr       */
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
	// Move backwards to skip trailing spaces
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	return (i);
}

int	check_space_map(t_map map)
{
	int	x;
	int	y;
	int	start_y;
	int end_y;

	x = 1;
	y = 1;
	while (x < map.rows - 1)
	{printf("dssssadsa\n");
		start_y = skip_leading_spaces(map.grid[x]);
		end_y = find_content_end(map.grid[x]);
		y = start_y;
		while (y < end_y && map.grid[x][y])
		{
			if (map.grid[x][y] == ' ' || map.grid[x][y] == '\t')
			{
				if (map.grid[x - 1][y] != '1' || map.grid[x + 1][y] != '1'
					|| map.grid[x][y - 1] != '1' || map.grid[x][y + 1] != '1')
				{
					printf("Invalid map\nSpace must be surrounded by '1'\n");
					printf("line: %s, %d, %d\n", map.grid[x], x, y);
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	return (1);
}


// int check_new_line(t_map map)
// {
// 	int x;
// 	int y;
	
// 	x = 1;
// 	y = 1;
// 	while (x < map.rows - 1)
// 	{
// 		y = 1;
// 		while(y < map.cols - 1)
// 		{
// 			if(map.grid[x][0] == '\n' || map.grid[x][0] == '\0')
// 			{
// 				printf("Invalid map\n");
// 				printf("line: %s\n", map.grid[x]);
// 				return (0);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (1);
// }

int	check_new_line(t_map map)
{
	int	x;
	int	has_started;
	int	has_ended;

	x = 0;
	has_started = 0;
	has_ended = 0;

	while (x < map.rows)
	{
		// Skip lines that contain only spaces or tabs or are empty
		int	i = 0;
		while (map.grid[x][i] == ' ' || map.grid[x][i] == '\t')
			i++;

		if (map.grid[x][i] == '\n' || map.grid[x][i] == '\0')
		{
			// Empty line
			if (has_started)
				has_ended = 1;
		}
		else
		{
			// Non-empty line
			if (has_ended)
			{
				printf("Invalid map: content found after empty line.\n");
				printf("line: %s\n", map.grid[x]);
				return (0);
			}
			has_started = 1;
		}
		x++;
	}
	return (1);
}
