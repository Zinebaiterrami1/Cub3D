/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/21 08:32:55 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


// #include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
// #include "libft/libft.h"


typedef struct s_map
{
    int i;
    int flag;
    char **map;
    char **valid_map;
}t_map;

int             parse_map(char *file_name);
int             count_line_map(int fd);
char            *read_map(int fd);
int get_first_line_map(const char *line);
char	*ft_strjoinn(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char **get_map(char *line, int fd);
int find_big_line(char **map);
char **square_map(char **map, int len);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void trim_newline(char **map);

void valid_map(char **full_map);
void print_valid();
#endif