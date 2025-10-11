/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/11 11:48:04 by zait-err         ###   ########.fr       */
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
#include <math.h>


// #define WIDTH 512        // largeur fenêtre
// #define HEIGHT 512       // hauteur fenêtre
// #define TILE_SIZE 64
// #define PLAYER_SIZE 8
// #define SPEED 5
// #define ROT_SPEED 0.1
// #define FOV (M_PI / 3) //60degree
// #define NUM_RAYS 50

#define WIDTH 800
#define HEIGHT 800
#define TILE_SIZE 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define FOV (60 * (M_PI / 180))
#define NUM_RAYS WIDTH
#define SPEED 5.0
#define ROT_SPEED 0.05
#define PLAYER_SIZE 8
#define NUM_TEXTURES 4
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

// typedef struct s_mlx
// {
//     void    *mlx;
//     void    *win;
//     void    *img;
//     char    *img_addr;
//     int     bpp;
//     int     line_len;
//     int     endian;
// }   t_mlx;

// typedef struct s_texture {
//     void    *img;
//     char    *addr;
//     int     bpp;
//     int     line_len;
//     int     endian;
//     int     width;
//     int     height;
// } t_texture;

typedef struct s_player
{
    float   x;
    float   y;
    float   angle;
    float   dx;
    float   dy;
}   t_player;

// typedef struct s_game
// {
//     t_mlx       gfx;
//     t_player    player;
//     int key_w;
//     int key_s;
//     int key_a;
//     int key_d;
//     int mapX, mapY;  // current map square of the ray
//     int stepX, stepY; // direction to step (+1 or -1)
//     int side;         // 0 = vertical wall hit, 1 = horizontal wall hit
//     float perpWallDist;
// }   t_game;
typedef struct s_textures {
    char *NO;
    char *SO;
    char *EA;
    char *WE;
    char *S;
} t_textures;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
} t_texture;

typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
} t_mlx;

// Update your ray struct to include the missing fields
typedef struct s_ray
{
    float rayX;
    float rayY;
    float ray_angle;
    float rayDX;
    float rayDY;
    float sideDirX;
    float sideDirY;
    int wall_type;
    float dist;
    float hit_x;
    float hit_y;
    float wall_x;       // X position where ray hit the wall (0-1)
    int side;           // 0: NS wall, 1: EW wall
    float angle;        // Ray angle
    float ray_dir_x;    // Add this missing field
    float ray_dir_y;    // Add this missing field
} t_ray;

typedef struct s_game {
    t_mlx gfx;
    t_player player;
    float ray_distances[NUM_RAYS];
     t_ray rays[NUM_RAYS];  // Add this for storing ray info
    t_texture textures[NUM_TEXTURES];  // Use t_texture, not t_textures
} t_game;

// typedef struct s_ray
// {
//     float rayX;
//     float rayY;
//     float ray_angle;
//     float rayDX;
//     float rayDY;
//     float sideDirX;
//     float sideDirY;
//     int wall_type;
//     float dist;
//     float hit_x;
//     float hit_y;
//     float wall_x;       // X position where ray hit the wall (0-1)
//     int side;           // 0: NS wall, 1: EW wall
//     float angle;        // Ray angle
// }t_ray;

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
void            valid_map(t_map map);
int             check_top_border(t_map map);
int             check_bottom_border(t_map map);
int             check_left_right_border(t_map map);
int             check_inside(t_map map);
int             check_inside_2(t_map map);
int             check_player_pos(t_map map);
int             check_space_map(t_map map);
void            print_valid();
t_map           init_map();
void render_3d_map(t_game *game, t_ray *ray, int i);
void render_3d_textured(t_game *game);
void draw_fov_rays(t_game *game);
#endif
