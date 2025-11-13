/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:08:04 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 23:18:48 by zait-err         ###   ########.fr       */
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
void    is_rgb_valid(char *line)
{
    char    *tmp;
    int     i;
    int     comma;

    tmp = ft_strtrim(line, " \t\r\n");   // <-- FIX
    if (!tmp)
        return;

    i = 0;
    comma = 0;
    while (tmp[i])
    {
        if (tmp[i] == ',')
            comma++;
        else if (!ft_isdigit(tmp[i]))
        {
            printf("Error\nInvalid character in color\n");
            exit(1);
        }
        i++;
    }
    if (comma != 2)
    {
        printf("Error\nInvalid color format in F/C element (expected R,G,B)\n");
        exit(1);
    }
}


int	parse_color(char *line, int *out_color)
{
	char	**tokens;
	int		values[3];
	int		i;
	int		error;
	is_rgb_valid(line);
	tokens = ft_split(line, ',');
	if (!tokens)
		return (1);
	i = 0;
	while (tokens[i] && i < 3)
	{
		error = str_to_int_strict(tokens[i], &values[i]);
		if (error)
			t_fil(tokens);
		i++;
	}
	if (i != 3)
	{
		free_split(tokens);
		print_error();
	}
	free_split(tokens);
	*out_color = (values[0] << 16) | (values[1] << 8) | values[2];
	return (0);
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erreur : le fichier%s n'existe pas \n", path);
		gc_free_all();
		exit(1);
	}
	close(fd);
}

void	init_draw_texture(t_draw_texture *dt)
{
	dt->screen_y = 0;
	dt->screen_x = 0;
	dt->color = 0;
	dt->wall_top = 0.0f;
	dt->wall_bottom = 0.0f;
	dt->tex_x = 0;
	dt->tex_num = 0;
	dt->step = 0.0f;
	dt->tex_pos = 0.0f;
	dt->tex_y = 0;
	dt->wall_height = 0;
}
