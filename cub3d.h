/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/29 10:46:07 by fakoukou         ###   ########.fr       */
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

typedef struct s_player
{
    int x;          // player row (map index)
    int y;          // player col (map index)
    char dir;       // 'N', 'S', 'E', 'W'
}   t_player;

typedef struct s_map
{
    char    **grid;     // the 2D map itself
    int     rows;       // number of rows
    int     cols;       // number of columns (after squaring)
    t_player player;    // player position & direction
}   t_map;

typedef struct s_config
{
    char    *no_tex;    // path to North texture
    char    *so_tex;    // South
    char    *we_tex;    // West
    char    *ea_tex;    // East
    int     floor[3];   // RGB values
    int     ceil[3];    // RGB values
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
void            valid_map(char **full_map);
int             check_top_border(char **map, int cols);
int             check_bottom_border(char **map, int rows, int cols);
int             check_left_right_border(char **map, int rows, int cols);
int             check_inside(char **map, int rows, int cols);
int             check_inside_2(char **map, int rows, int cols);
int             check_player_pos(char **map, int rows, int cols);
int             check_space_map(char **map, int rows, int cols);
void            print_valid();
int white_spaces(char *line, int i);
#endif