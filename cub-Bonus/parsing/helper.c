/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:05:59 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/11 11:11:45 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_player(char c)
{
	return (c == 'W' || c == 'E' || c == 'N' || c == 'S');
}

int	check_zero(t_map map, int x, int y)
{
	if (map.grid[x - 1][y] == ' ' || map.grid[x + 1][y] == ' ' || map.grid[x][y
		- 1] == ' ' || map.grid[x][y + 1] == ' ' || map.grid[x][y + 1] == '\0'
		|| map.grid[x][y - 1] == '\0' || map.grid[x - 1][y] == '\0'
		|| map.grid[x + 1][y] == '\0')
	{
		return (0);
	}
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
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
