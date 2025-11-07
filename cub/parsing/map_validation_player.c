/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:19:50 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/07 15:38:24 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

int	check_player_pos(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (x < map->rows - 1)
	{
		y = 1;
		while (y < (int)ft_strlen(map->grid[x]) - 1)
		{
			if (map->grid[x][y] == 'N' || map->grid[x][y] == 'S'
				|| map->grid[x][y] == 'E' || map->grid[x][y] == 'W')
			{
				map->player.x = x;
				map->player.y = y;
				set_player_dir(&map->player, map->grid[x][y]);
				map->grid[x][y] = '0';
				map->count_pos++;
			}
			y++;
		}
		x++;
	}
	return (count_pos(map));
}

int	count_pos(t_map *map)
{
	if (map->count_pos != 1)
	{
		printf("count: %d\n", map->count_pos);
		return (printf("Invalid map\nmust be only one player position\n"), 0);
	}
	return (1);
}

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
			if (maze[y][x] == '1' || maze[y][x] == '0'
				|| maze[y][x] == ' ' || maze[y][x] == '\t'
				|| maze[y][x] == 'N' || maze[y][x] == 'S'
				|| maze[y][x] == 'E' || maze[y][x] == 'W')
					x++;
			else
				return (printf("Invalid character in the maze :/\n"), 0);
		}
		y++;
	}
	return (1);
}

int	check_first_last_line(char **maze)
{
	int	x;
	int	y;

	x = 0;
	while (maze[0][x])
	{
		if (maze[0][x] == ' ' || maze[0][x] == '\t' || maze[0][x] == '1')
			x++;
		else
		{
			printf("First line should contain just 1s and spaces!\n");
			return (0);
		}
	}
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
		if (maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '1')
			x++;
		else
		{
			printf("Last line should contain just 1s and spaces!\n");
			return (0);
		}
	}
	return (1);
}

// int check_left_right(char **maze)
// {
// 	int x;
// 	int y;
	
// 	x = 0;
// 	y = 0;
// 	while(maze[x][y])
// 	{
// 		if(maze[x][0] == '0')
// 		{
// 			printf("Invalid map\nOpen At left border\n");
// 			return (0);
// 		}
// 		while(maze[x][y])
// 			y++;
// 		if(maze[x][y - 1] == '0')
// 		{
// 			printf("Invalid map\nOpen at right border\n");
// 			return (0);
// 		}
// 		x++;
// 	}
// 	return (1);
// }

// int	check_left_right(char **maze)
// {
// 	int	x;
// 	int y;
	
// 	x = 0;
// 	y = 0;
// 	while(maze[y])
// 	{
// 		x = 0;
// 		while(maze[y][x])
// 		{
// 			while(maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '\n')
// 				x++;
// 			if((x == 0 && maze[y][x] != '1') || maze[y][x] != '1')
// 			{
// 				printf("error left is open\n");
// 				printf("line %s, char %c\n", maze[y], maze[y][x]);
// 				return (0);
// 			}
// 			x++;
// 		}
// 		while(maze[y][x])
// 		{
// 			if(maze[y][x + 1] == '\0' && maze[y][x] != '1')
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

int	check_left_right(char **maze)
{
	int	y;
	int	x;

	y = 0;
	while (maze[y])
	{
		// --- Check left border ---
		x = 0;
		while (maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '\n')
			x++;
		if (maze[y][x] != '\0' && maze[y][x] != '1')
		{
			printf("Error: left border open at line %d\n", y);
			return (0);
		}

		// --- Check right border ---
		x = 0;
		while (maze[y][x])
			x++;
		x--; // Move to last valid char
		while (x > 0 && (maze[y][x] == ' ' || maze[y][x] == '\t' || maze[y][x] == '\n'))
			x--;
		if (x >= 0 && maze[y][x] != '1')
		{
			printf("Error: right border open at line %d\n", y);
			return (0);
		}
		y++;
	}
	return (1);
}


void	valid_map(t_map *map)
{
	if (!check_map2(map->grid))//checked check on characters
		print_error();
	if (!check_first_last_line(map->grid))//checked
		print_error();
	if(!check_left_right(map->grid))//checked
		print_error();
	// if (!check_top_border(*map))
	// 	print_error();
	// if (!check_bottom_border(*map))
	// 	print_error();
	// if (!check_left_right_border(*map))
	// 	print_error();
	if (!check_inside(*map))//checked, check on 0
		print_error();
	// if (!check_inside_2(*map))
	// 	print_error();
	if (!check_player_pos(map))//checked
		print_error();
	// if(!check_new_line(*map))
	// 	print_error();
	if (!check_space_map(*map))//checked
		print_error();
}


void	print_valid(void)
{
	printf("\nValid map✅✅\n");
}
