/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:51:39 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/11 16:44:50 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
//change
void duplicate_tex(t_textures *tex)
{
    if (tex)
        free_textures_strings(tex); // libère toutes les textures déjà assignées
    printf("Error: Duplicate texture\n");
   
	get_next_line(-1);
	gc_free_all();
	exit(EXIT_FAILURE);
}




static void assign_texture(char **tex_ptr, char *value, t_textures *tex)
{
    char *new_value;

    if (*tex_ptr != NULL)
    {
        // On ne fait pas free ici
        duplicate_tex(tex);  // va libérer toutes les textures et quitter
    }
    new_value = ft_strdup_trim(value);
    if (!new_value)
        print_error();  // gérer l'erreur si malloc échoue
    *tex_ptr = new_value;
}




void free_textures_strings(t_textures *tex)
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

void	validate_textures(t_textures *tex)
{
	if (tex->no)
		check_path(tex->no);
	else
		print_error();
	if (tex->so)
		check_path(tex->so);
	else
		print_error();
	if (tex->ea)
		check_path(tex->ea);
	else
		print_error();
	if (tex->we)
		check_path(tex->we);
	else
		print_error();
}

int	parse_color(char *line, int *out_color)
{
	char	**tokens;
	int		values[3];
	int		i;
	int		error;

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
		printf("❌ Erreur : le fichier%s n'existe pas \n",
			path);
		gc_free_all();
		exit(1);
	}
	close(fd);
}
