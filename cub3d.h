/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/12 10:34:18 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

int             parse_map(char *file_name);
int             count_line_map(int fd);
char            **read_map();
int get_first_line_map(const char *line);
#endif