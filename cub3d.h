/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/24 14:30:29 by zait-err         ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 800
# define TILE_SIZE 64
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define FOV (60 * (M_PI / 180))
# define NUM_RAYS WIDTH
# define SPEED 5.0
# define ROT_SPEED 0.05
# define PLAYER_SIZE 8
# define NUM_TEXTURES 4
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define DIST_EDGE_MOUSE_WRAP 20
# define MINIMAP_SCALE 0.2
extern int map[MAP_HEIGHT][MAP_WIDTH];

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
    int     has_moved;
    int plane_x;
    int plane_y;
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

typedef struct s_texture
{
    void            *img;
    char            *addr;
    int             bpp;
    int             line_len;
    int             endian;
    int             width;
    int             height;
    int             wall_top;
    int             wall_bottom;
    int             tex_x;
    int             tex_y; 
    int             tex_num;
    float           step;
    float           tex_pos;
}                   t_texture;

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
    float start_angle;
    float angle_step;
    float	corrected_dist;
    float	proj_plane;
    float deltaDistX;
    float deltaDistY;
    float sideDistX;
    float sideDistY;
    int stepX;
    int stepY;
    int hit;
    float end_x;
    float end_y;
} t_ray;

typedef struct s_map
{
    char    **grid;     // the 2D map itself
    int     rows;       // number of rows
    int     cols;       // number of columns (after squaring)
    t_player player;    // player position & direction
}   t_map;


typedef struct s_game {
    t_mlx gfx;
    t_player player;
    float ray_distances[NUM_RAYS];
    t_ray rays[NUM_RAYS];  // Add this for storing ray info
    t_texture textures[NUM_TEXTURES];  // Use t_texture, not t_textures
    t_ray ray;
    t_texture tex_wall;
    t_map map;
} t_game;

typedef struct s_cast_ray
{
    int mapX;
    int mapY;
    int side;
    float perpWallDist;
    float wallX;
    float start_angle;
    float angle_step;
}t_cast_ray;
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


typedef struct s_color
{
    int r;
    int g;
    int b;
}t_color;

typedef struct s_draw_texture
{
	int				screen_y;//
    int             screen_x;//
	unsigned int	color;//
	float			wall_top;//
	float			wall_bottom;//
	int				tex_x;//
	int				tex_num;//
	float			step;//
	float			tex_pos;//
	int				tex_y;//
    int		        wall_height;
}t_draw_texture;

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
int	ft_strncmp(const char *s1, const char *s2, size_t n);
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
void            render_3d_map(t_game *game, t_ray *ray, int i);
void            render_3d_textured(t_game *game);
void            draw_fov_rays(t_game *game);
t_ray           cast_ray_textured(t_game *game, float ray_angle);
int             determine_texture(t_ray *ray);
void load_textures(t_game *game);
void draw_sky_and_floor(t_game *game);
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void clear_screen(t_mlx *mlx);
void	draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray,
		int wall_height);
void draw_miniplayer(t_game *game);
void draw_minimap(t_game *game);
#endif


/*


| Theme       | Sky Color  | Floor Color |
| :---------- | :--------- | :---------- |
| ☀️ Daylight | `0x87CEEB` | `0x228B22`  |
| 🌇 Sunset   | `0xFF9966` | `0x553311`  |
| 🌙 Night    | `0x001133` | `0x111111`  |
| 🧊 Ice cave | `0xCCEFFF` | `0x99CCFF`  |
| 🔥 Hellish  | `0x660000` | `0x330000`  |

*/
