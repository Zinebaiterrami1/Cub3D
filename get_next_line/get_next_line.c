/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:48:18 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/11 16:36:15 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// gnl
char	*get_next_line(int fd)
{
	char		*lines;
	static char	*stash;

	lines = NULL;
	
	// ═══ LIBÉRER STASH SI fd == -1 ═══
	if (fd == -1)
	{
		if (stash)
		{
			stash = NULL;
		}
		return (NULL);
	}
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = _fill_line_buffer(fd, stash);
	if (!stash)
		return (NULL);
	lines = _set_line(stash);
	stash = _helper_function(stash);
	return (lines);
}

char	*_fill_line_buffer(int fd, char *str)
{
	ssize_t	r;
	char	*buffer;

	r = 1;
	buffer = gc_malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	if (fd == -1)
		return (NULL);
	while (!ft_strchr(str, '\n') && r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			return (NULL);
		}
		buffer[r] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
	}
	(void)buffer;
	return (str);
}

char	*_helper_function(char *line)
{
	ssize_t	i;
	char	*left_c;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		return (NULL);
	}
	if (line[i] == '\n')
		i++;
	left_c = ft_substr(line, i, ft_strlen(line) - i);
	if (!left_c)
	{
		return (NULL);
	}
	return (left_c);
}

char	*_set_line(char *line_buffer)
{
	ssize_t	i;
	char	*line;
	ssize_t	j;

	j = 0;
	i = 0;
	if (!ft_strlen(line_buffer))
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\n')
		line = gc_malloc(sizeof(char) * (i + 2));
	else
		line = gc_malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j <= i && line_buffer[j])
	{
		line[j] = line_buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}
