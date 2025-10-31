/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:51:39 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 15:52:24 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	line_free(t_textures tex)
{
	free(tex.no);
	free(tex.so);
	free(tex.ea);
	free(tex.we);
}
