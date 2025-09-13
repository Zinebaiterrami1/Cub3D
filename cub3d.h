/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/12 17:02:23 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


// #include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include "get_next_line/get_next_line.h"
// #include "libft/libft.h"

typedef struct s_textures {
    char *NO;
    char *SO;
    char *EA;
    char *WE;
    char *S;
} t_textures;


int parse_color(char *line, int print_color);
void check_texture_line(t_textures *tex, char *line);
void check_path(char *path);
int             parse_map(char *file_name);
int             count_line_map(int fd);
char            *read_map(int fd);
int get_first_line_map(const char *line);
char	*ft_strjoinn(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
#endif