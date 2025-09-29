/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/29 21:07:47 by zait-err         ###   ########.fr       */
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


typedef struct s_player
{
    double x;          // player row (map index)
    double y;          // player col (map index)
    char dir;       // 'N', 'S', 'E', 'W'
    double dir_x; // direction vector (unit vector) x
    double dir_y; // dir vector y
    double plane_x; // camera plane vector (perpendicular to dir) x
    double plane_y; //camera plane vector y
}   t_player;

typedef struct s_map
{
    char    **grid;     // the 2D map itself
    int     rows;       // number of rows
    int     cols;       // number of columns (after squaring)
    t_player player;    // player position & direction
}   t_map;

typedef struct s_color
{
    int r;
    int g;
    int b;
}t_color;

typedef struct s_config
{
    char    *no_tex;    // path to North texture
    char    *so_tex;    // South
    char    *we_tex;    // West
    char    *ea_tex;    // East
    t_map   map;        // the map info
}   t_config;


int             parse_map(char *file_name);
int             count_line_map(int fd);
char            *read_map(int fd);
int             get_first_line_map(const char *line);
char	        *ft_strjoinn(char *s1, char *s2);
void	        *ft_memcpy(void *dest, const void *src, size_t n);
char            **get_map(char *line, int fd);
int             find_big_line(char **map);
char            **square_map(char **map, int len);
size_t	        ft_strlcpy(char *dest, const char *src, size_t dstsize);
void            trim_newline(char **map);
void            valid_map(t_map *map);
int             check_top_border(t_map *map);
int             check_bottom_border(t_map *map);
int             check_left_right_border(t_map *map);
int             check_inside(t_map *map);
int             check_inside_2(t_map *map);
int             check_player_pos(t_map *map);
int             check_space_map(t_map *map);
void            print_valid();
t_map *init_map();

#endif