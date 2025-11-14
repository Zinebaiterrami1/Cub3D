/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:08:04 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/14 09:37:51 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	validate_textures(t_textures *tex)
{
	if (tex->no != NULL)
		check_path(tex->no);
	else
		print_error();
	if (tex->so != NULL)
		check_path(tex->so);
	else
		print_error();
	if (tex->ea != NULL)
		check_path(tex->ea);
	else
		print_error();
	if (tex->we != NULL)
		check_path(tex->we);
	else
		print_error();
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	ft_erreur(void)
{
	printf("Error\nInvalid color format in F/C element (expected R,G,B)\n");
	gc_free_all();
	exit(EXIT_FAILURE);
}

void	is_rgb_valid(char *line)
{
	char	*tmp;
	int		i;
	int		comma;

	tmp = ft_strtrim(line, " \t\r\n");
	if (!tmp)
		return ;
	i = 0;
	comma = 0;
	while (tmp[i])
	{
		if (tmp[i] == ',')
			comma++;
		else if (!ft_isdigit(tmp[i]))
		{
			printf("Error\nInvalid character in color\n");
			gc_free_all();
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (comma != 2)
	{
		ft_erreur();
	}
}
