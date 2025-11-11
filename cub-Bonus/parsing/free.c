/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:36:33 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/11 18:20:15 by fakoukou         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		(void)tokens[i];
		i++;
	}
	(void)tokens;
}

void	line_free(t_textures tex)
{
	(void)tex.no;
	(void)tex.so;
	(void)tex.ea;
	(void)tex.we;
}
