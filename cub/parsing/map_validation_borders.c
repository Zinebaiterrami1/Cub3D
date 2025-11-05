/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_borders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:42:04 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/05 14:03:15 by zait-err         ###   ########.fr       */
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

int	check_left_right_border(t_map map)
{
	int	x;

	x = 0;
	while (x < map.rows)
	{
		if (map.grid[x][0] == '0')
		{
			printf("Invalid map\nOpen At left border\n");
			return (0);
		}
		if (map.grid[x][map.cols - 1] == '0')
		{
			printf("Invalid map\nOpen at right border\n");
			return (0);
		}
		x++;
	}
	return (1);
}
