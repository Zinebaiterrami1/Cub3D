/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/12 11:45:54 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_first_line_map(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != '\t' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static char	**fill_lines(char **map, char *line, int count)
{
	int		i;
	char	**full_map;

	full_map = gc_malloc(sizeof(char *) * (count + 2));
	if (!full_map)
		return (NULL);
	i = 0;
	while (i < count)
	{
		full_map[i] = map[i];
		i++;
	}
	full_map[i] = ft_strdup(line);
	if (!full_map)
		return (NULL);
	full_map[i + 1] = NULL;
	(void)map;
	return (full_map);
}

char	**get_map(char *line, int fd)
{
	int		count;
	char	**map;

	count = 0;
	map = NULL;
	map = fill_lines(map, line, count++);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map = fill_lines(map, line, count++);
		if (!map)
			return (NULL);
		(void)line;
		line = get_next_line(fd);
	}
	print_map(map);
	return (map);
}

char	*read_map(int fd)
{
	char	*tmp;
	char	*old_str;
	char	*new_str;

	tmp = get_next_line(fd);
	new_str = gc_malloc(1);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	while (tmp && !get_first_line_map(tmp))
	{
		(void)tmp;
		tmp = get_next_line(fd);
	}
	while (tmp)
	{
		old_str = new_str;
		new_str = ft_strjoinn(old_str, tmp);
		(void)old_str;
		(void)tmp;
		tmp = get_next_line(fd);
	}
	return (new_str);
}

void	print_error_map(t_map *map)
{
	printf("Error\n");
	free_map_grid(map->grid);
	gc_free_all();
	exit(EXIT_FAILURE);
}
