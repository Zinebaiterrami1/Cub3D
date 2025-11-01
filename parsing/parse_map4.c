/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:37 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/31 15:44:52 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**square_map(char **map, int max_len)
{
	int		i;
	char	*new_line;
	int		len_line;

	i = 0;
	while (map[i])
	{
		len_line = (int)ft_strlen(map[i]);
		if (len_line < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return (NULL);
			ft_memcpy(new_line, map[i], len_line);
			while (len_line < max_len)
				new_line[len_line++] = '\0';
			new_line[max_len] = '\0';
			free(map[i]);
			map[i] = new_line;
		}
		i++;
	}
	return (map);
}

void	trim_newline(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
}
