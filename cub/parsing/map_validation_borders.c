/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_borders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:42:04 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/07 14:22:52 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_top_border(t_map map)
{
	int	y;

	y = 0;
	while (y < map.cols && map.grid[0][y] != '\0')
	{
		if (map.grid[0][y] != '1' && map.grid[0][y] != ' '
			&& map.grid[0][y] != '\t')
		{
			printf("Invalid map: Top border must be only '1', ' ' or '\\t'\n");
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_bottom_border(t_map map)
{
	int	y;

	y = 0;
	while (y < map.cols && map.grid[map.rows - 1][y] != '\0')
	{
		if (map.grid[map.rows - 1][y] != '1' && map.grid[map.rows - 1][y] != ' '
			&& map.grid[map.rows - 1][y] != '\t')
		{
			printf("%c(%d, %d)\n", map.grid[map.rows - 1][y], map.rows - 1, y);
			printf("Invalid map: ");
			printf("Bottom border must be only '1', ' ' or '\\t'\n");
			return (0);
		}
		y++;
	}
	return (1);
}

// int	check_left_right_border(t_map map)
// {
// 	int	x;
// 	int y;
	
// 	x = 0;
// 	y = 0;
// 	while (x < map.rows)
// 	{
// 		if(map.grid[x][0] == ' ' || map.grid[x][0] == '\t')
// 		{
// 			y = 0;
// 			while((map.grid[x][y] == ' ' || map.grid[x][y] == '\t') && map.grid[x][y] != '\0') 
// 			{
// 				y++;
// 				if (map.grid[x][y] != '1')
// 				{
// 					printf("Invalid map\nOpen At left border\n");
// 					printf("char :%c\n", map.grid[x][y]);
// 					return (0);
// 				}
// 			}
// 		}
// 		else if (map.grid[x][0] != '1')
// 		{
// 			printf("Invalid map\nOpen At left border\n");
// 			printf("char :%c\n", map.grid[x][0]);
// 			return (0);
// 		}
// 		if (map.grid[x][map.cols - 1] != '1')
// 		{
// 			printf("Invalid map\nOpen at right border\n");
// 			printf("char :%c\n", map.grid[x][map.cols - 1]);
// 			return (0);
// 		}
// 		x++;
// 	}
// 	return (1);
// }

// int	check_left_right_border(char **maze)
// {
// 	int	x;
// 	int y;
	
// 	x = 0;
// 	y = 0;
// 	while(maze[y])
// 	{
// 		while(maze[y][x])
// 		{
// 			x = 0;
// 			while(maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '\n')
// 				x++;
// 			if((x == 0 && map[y][x] != '1') || map[y][x] != '1')
// 			{
// 				printf("error left is open\n");
// 				return (0);
// 			}
// 			x++;
// 		}
// 		while(maze[y][x])
// 		{
// 			if(maze[y][x + 1] == '\0' && map[y][x] != '1')
// 			{
// 				printf("error right is open\n");
// 				return (0);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }
