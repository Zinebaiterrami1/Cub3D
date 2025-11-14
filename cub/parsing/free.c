/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:36:33 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 22:34:30 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	t_fil(char **tokens)
{
	free_split(tokens);
	print_error();
}

void	free_split(char **tokens)
{
	if (!tokens)
		return ;
}

void	line_free(t_textures tex)
{
	(void)tex.no;
	(void)tex.so;
	(void)tex.ea;
	(void)tex.we;
}

// void	duplicate_tex(void)
// {
// 	printf("Error: Duplicate texture\n");
// 	exit(EXIT_FAILURE);
// }

// void	assign_texture(char **tex_ptr, char *value)
// {
// 	if (*tex_ptr != NULL)
// 		duplicate_tex();
// 	*tex_ptr = ft_strdup_trim(value);
// }
