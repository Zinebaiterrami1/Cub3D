/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:42:04 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/01 10:22:33 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			printf("Bottom border must be only '1',' ' or '\\t'\n");
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
					printf("%d, %d\n", x , y);
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

void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dx = 0;
		p->dy = -1;
		p->angle = 3 * M_PI / 2;
	}
	else if (c == 'S')
	{
		p->dx = 0;
		p->dy = 1;
		p->angle = M_PI / 2;
	}
	else if (c == 'E')
	{
		p->dx = 1;
		p->dy = 0;
		p->angle = 0;
	}
	else if (c == 'W')
	{
		p->dx = -1;
		p->dy = 0;
		p->angle = M_PI;
	}
}
