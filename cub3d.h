/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/30 21:31:49 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <X11/X.h>

#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include <math.h>
#include <stdlib.h>
#include<limits.h>
#include <stdio.h>
#include <unistd.h>
// #include<mlx.h>
#include <string.h>  // ✅ Ajout nécessaire


#define COLLISION_RADIUS 2
# define WIDTH 1000
# define HEIGHT 1000
# define TILE_SIZE 64
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define FOV (60 * (M_PI / 180))
# define NUM_RAYS WIDTH
# define SPEED 5
# define ROT_SPEED 0.05
# define PLAYER_SIZE 8
# define NUM_TEXTURES 4
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define DIST_EDGE_MOUSE_WRAP 20


#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_SPC 32
extern int map[MAP_HEIGHT][MAP_WIDTH];
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	space;
}	t_keys;


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
       double view_angle;
    int move_dir;
    int rot_dir;
    double move_speed;
    double rot_speed;
    double right_x;
    int strafe_dir;
    double left_y;
    // int		strafe_dir; 
}   t_player;

typedef struct s_textures {
    char *NO;
    char *SO;
    char *EA;
    char *WE;
    char *S;
} t_textures;
typedef struct s_rend_t
{
	float ray_angle ;
	float dist ;
	float corrected_dist ;
	float proj_plane ;
	int wall_height;
	int wall_top ;
	int wall_bottom ;
} t_rend_t;

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

typedef struct s_gun
{
    t_texture gun_texture[2];
    int current_frame;  // 0 = idle, 1 = shooting
    int shooting;       // flag: 1 when shooting animation active
    int frame_timer;    // optional, for timing the shot animation
    int pos_x;
    int pos_y;
    int gun_width;
    int gun_height;
    int screen_x;
    int screen_y;
    unsigned color;
}t_gun;


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
typedef struct s_draw
{
	int	tile;
	int	color;
	int	yy;
	int	xx;
	int	px;
	int	py;
	int	size;
	int	x;
	int	y;
	int	dy;
	int	dx;
}t_draw;

typedef struct s_game {
    t_mlx gfx;
    t_player player;
    float ray_distances[NUM_RAYS];
    t_ray rays[NUM_RAYS];  // Add this for storing ray info
    t_texture textures[NUM_TEXTURES];  // Use t_texture, not t_textures
    t_ray ray;
    t_texture tex_wall;
    t_map map;
    t_keys		keys;   // <--- Ajoute ça ici
    t_gun gun;
    t_draw draw;
    int floor_color;   // couleur F
    int ceiling_color; // couleur C
    // t_keys keys;
	float	x_inc;
	float	y_inc;
	float	dx;
	float	dy;
    t_textures	tex;
    
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

unsigned int	get_texture_pixel(t_texture *tex, int x, int y);
void shoot(t_game *game);
t_gun init_gun();
void load_texture_gun(t_game *game);
void draw_gun(t_game *game);
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
// void load_textures(t_game *game);
void draw_sky_and_floor(t_game *game);
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void clear_screen(t_mlx *mlx);
void	draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray,
		int wall_height);
void print_error();
// int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
int parse_color(char *line, int *out_color);
void check_texture_line(t_textures *tex, char *line);
void check_path(char *path);
int	key_hook(int keycode, void *param);
int	mouse_move(int x, int y, t_game *win);
int	close_window(void *param);
// void	draw_line_dda(t_mlx *mlx, float x0, float y0, float x1, float y1,
// 		int color);
void	draw_minimap(t_game *game);
int	extra_number(const char *a, int i, int num);
void	free_split(char **tokens);
char	*ft_strdup_trim(char *src);
int	rotate_left_right(t_game *game, double rotspeed);
int	is_wall(t_game *game, float x, float y);
void update_gun(t_game *game);
void calculate_wall_x(t_game *game, t_ray *ray, t_cast_ray *data);
t_ray	init_ray(void);
t_cast_ray	init_cast_ray(void);
void	draw_line_dda(t_game *game, int color);
void	wrap_mouse_position(int x, int y, t_game *game);
int	extra_number(const char *a, int i, int num);
int	rotate_left_right(t_game *game, double rotspeed);
int	rotate_player(t_game *game, int rotdir);
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
int	loop_hook(t_game *game);
void handle_movement(t_game *game);
int    press_key(int keysem, t_game *game);
int press_x(t_game *game);
int moves_loop(t_game *data);
int release_key(int keysem, t_game *data);
int	game_loop(t_game *game);
void load_textures(t_game *game , t_textures *tex);
#endif
