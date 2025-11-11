/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:19:12 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/11 16:44:50 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	print_error(void)
{
	printf("Error\n");
	gc_free_all();
	exit(EXIT_FAILURE);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup_trim(char *src)
{
	int	len;

	len = ft_strlen(src);
	while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '\n'))
		src[--len] = '\0';
	while (*src == ' ' || *src == '\t')
		src++;
	return (ft_strdup(src));
}

int	ft_isdigit1(char c)
{
	return (c >= '0' && c <= '9');
}

int	str_to_int_strict(const char *s, int *out)
{
	long	n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '+' || s[i] == '-' || !ft_isdigit1(s[i]))
		return (1);
	while (ft_isdigit1(s[i]))
	{
		n = n * 10 + (s[i] - '0');
		if (n > 255)
			return (1);
		i++;
	}
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (1);
		i++;
	}
	*out = (int)n;
	return (0);
}
