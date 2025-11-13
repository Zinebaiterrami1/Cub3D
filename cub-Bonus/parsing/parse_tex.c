/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:51:39 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 09:26:59 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	duplicate_tex(t_textures *tex)
{
	if (tex)
		free_textures_strings(tex);
	printf("Error: Duplicate texture\n");
	get_next_line(-1);
	gc_free_all();
	exit(EXIT_FAILURE);
}
static void	assign_texture(char **tex_ptr, char *value, t_textures *tex)
{
	char	*new_value;
	char	*trimmed;

	if (*tex_ptr != NULL)
		duplicate_tex(tex);

	trimmed = ft_strdup_trim(value);
	if (!trimmed)
		print_error();

	int len = ft_strlen(trimmed);
	if (len > 0 && (trimmed[len - 1] == '\n' || trimmed[len - 1] == '\r'))
		trimmed[len - 1] = '\0';

	
if (!ft_strnstr(trimmed, ".xpm", ft_strlen(trimmed)))
{
    printf("❌ Erreur : le fichier '%s' n'est pas une texture .xpm\n", trimmed);
	(void)trimmed;
	gc_free_all();
	exit(EXIT_FAILURE);
}

	new_value = trimmed;
	*tex_ptr = new_value;
}


void	free_textures_strings(t_textures *tex)
{
	if (!tex)
		return ;
	if (tex->no)
	{
		(void)tex->no;
		tex->no = NULL;
	}
	if (tex->so)
	{
		(void)tex->so;
		tex->so = NULL;
	}
	if (tex->ea)
	{
		(void)tex->ea;
		tex->ea = NULL;
	}
	if (tex->we)
	{
		(void)tex->we;
		tex->we = NULL;
	}
}

void	check_texture_line(t_textures *tex, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		assign_texture(&tex->no, line + i + 3, tex);
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		assign_texture(&tex->so, line + i + 3, tex);
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		assign_texture(&tex->ea, line + i + 3, tex);
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		assign_texture(&tex->we, line + i + 3, tex);
}

int	tex_global(char *line, t_textures *tex)
{
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
	{
		check_texture_line(tex, line);
		return (0);
	}
	return (1);
}
