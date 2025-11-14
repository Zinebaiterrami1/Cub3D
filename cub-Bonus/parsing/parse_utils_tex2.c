/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_tex2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:13:44 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/14 10:17:00 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	handle_floor_color(char *line, t_game *game)
{
	if (game->floor_set == 1)
	{
		printf("Error: Duplicate F (floor) color\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	if (line[1] != ' ' && line[1] != '\t')
	{
		printf("Error: Invalid floor color format (expected 'F R,G,B')\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	parse_color(line + 2, &game->floor_color);
	game->floor_set = 1;
}

void	handle_ceiling_color(char *line, t_game *game)
{
	if (game->ceiling_set == 1)
	{
		printf("Error: Duplicate C (ceiling) color\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	if (line[1] != ' ' && line[1] != '\t')
	{
		printf("Error: Invalid ceiling color format\n");
		gc_free_all();
		exit(EXIT_FAILURE);
	}
	parse_color(line + 2, &game->ceiling_color);
	game->ceiling_set = 1;
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
