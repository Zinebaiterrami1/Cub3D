/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/12 09:20:02 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define COLLISION_RADIUS 2
# define WIDTH 1000
# define HEIGHT 1000
# define TILE_SIZE 64
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define FOV_DEGREES 60
# define NUM_RAYS WIDTH
# define SPEED 8
# define ROT_SPEED 0.05
# define PLAYER_SIZE 8
# define NUM_TEXTURES 4
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define DIST_EDGE_MOUSE_WRAP 20
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPC 32

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				space;
}					t_keys;

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float			dx;
	float			dy;
	int				has_moved;
	int				plane_x;
	int				plane_y;
	double			view_angle;
	int				move_dir;
	int				rot_dir;
	double			move_speed;
	double			rot_speed;
	double			right_x;
	int				strafe_dir;
	double			left_y;
}					t_player;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
}					t_textures;
typedef struct s_rend_t
{
	float			ray_angle;
	float			dist;
	float			corrected_dist;
	float			proj_plane;
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
}					t_rend_t;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	int				wall_top;
	int				wall_bottom;
	int				tex_x;
	int				tex_y;
	int				tex_num;
	float			step;
	float			tex_pos;
}					t_texture;

typedef struct s_gun
{
	t_texture		gun_texture[2];
	int				current_frame;
	int				shooting;
	int				frame_timer;
	int				pos_x;
	int				pos_y;
	int				gun_width;
	int				gun_height;
	int				screen_x;
	int				screen_y;
	int				color;
}					t_gun;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mlx;

typedef struct s_ray
{
	float			ray_angle;
	float			raydx;
	float			raydy;
	int				wall_type;
	float			dist;
	float			hit_x;
	float			hit_y;
	float			wall_x;
	int				side;
	float			angle;
	float			ray_dir_x;
	float			ray_dir_y;
	float			start_angle;
	float			angle_step;
	float			corrected_dist;
	float			proj_plane;
	float			deltadistx;
	float			deltadisty;
	float			sidedistx;
	float			sidedisty;
	int				stepx;
	int				stepy;
	int				hit;
	float			end_x;
	float			end_y;
}					t_ray;

typedef struct s_map
{
	char			**grid;
	int				rows;
	int				cols;
	t_player		player;
	int				count_pos;
}					t_map;
typedef struct s_d
{
	int				steps;
	float			x;
	float			y;
	int				i;
	float			x_inc;
	float			y_inc;
	float			dx;
	float			dy;
}					t_d;
typedef struct s_draw
{
	int				tile;
	int				color;
	int				yy;
	int				xx;
	int				px;
	int				py;
	int				size;
	int				x;
	int				y;
	int				dy;
	int				dx;
}					t_draw;
typedef struct s_draw_texture
{
	int				screen_y;
	int				screen_x;
	unsigned int	color;
	float			wall_top;
	float			wall_bottom;
	int				tex_x;
	int				tex_num;
	float			step;
	float			tex_pos;
	int				tex_y;
	int				wall_height;
	t_texture		texture;
}					t_draw_texture;
typedef struct s_game
{
	t_mlx			gfx;
	t_player		player;
	float			ray_distances[NUM_RAYS];
	t_ray			rays[NUM_RAYS];
	t_texture		textures[NUM_TEXTURES];
	t_ray			ray;
	t_texture		tex_wall;
	t_map			map;
	t_keys			keys;
	t_gun			gun;
	t_draw			draw;
	t_draw_texture	dt;
	t_d				d;
	int				floor_set;
	int				ceiling_set;
	int				floor_color;
	int				ceiling_color;
	t_textures		tex;
}					t_game;

typedef struct s_cast_ray
{
	int				mapx;
	int				mapy;
	int				side;
	float			perpwalldist;
	float			wallx;
	float			start_angle;
	float			angle_step;
}					t_cast_ray;

typedef struct s_ctx
{
	t_game			*game;
	t_textures		*tex;
	t_map			*map;
	int				fd;
}					t_ctx;

unsigned int		get_texture_pixel(t_texture *tex, int x, int y);
void				shoot(t_game *game);
t_gun				init_gun(void);
void				load_texture_gun(t_game *game);
void				draw_gun(t_game *game);
int					parse_map(char *file_name);
int					count_line_map(int fd);
char				*read_map(int fd);
int					get_first_line_map(const char *line);
char				*ft_strjoinn(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**get_map(char *line, int fd);
int					find_big_line(char **map);
char				**square_map(char **map, int len);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
void				trim_newline(char **map);
void				valid_map(t_map *map);
int					check_top_border(t_map map);
int					check_bottom_border(t_map map);
int					check_left_right_border(t_map map);
int					check_inside(t_map map);
int					check_inside_2(t_map map);
int					check_space_map(t_map map);
void				print_valid(void);
t_map				init_map(void);
void				render_3d_map(t_game *game, t_ray *ray, int i);
void				render_3d_textured(t_game *game);
void				draw_fov_rays(t_game *game);
t_ray				cast_ray_textured(t_game *game, float ray_angle);
int					determine_texture(t_ray *ray);
void				draw_sky_and_floor(t_game *game);
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void				clear_screen(t_mlx *mlx);
void				draw_textured_wall_slice(t_game *game, int screen_x,
						t_ray *ray, int wall_height);
char				**ft_split(char *s, char c);
int					parse_color(char *line, int *out_color);
void				check_texture_line(t_textures *tex, char *line);
void				check_path(char *path);
int					key_hook(int keycode, void *param);
int					close_window(void *param);
void				draw_minimap(t_game *game);
int					extra_number(const char *a, int i, int num);
void				free_split(char **tokens);
char				*ft_strdup_trim(char *src);
int					rotate_left_right(t_game *game, double rotspeed);
int					is_wall(t_game *game, float x, float y);
void				update_gun(t_game *game);
void				calculate_wall_x(t_game *game, t_ray *ray,
						t_cast_ray *data);
void				init_ray(t_ray *ray);
t_cast_ray			init_cast_ray(void);
void				draw_line_dda(t_game *game, int color);
void				wrap_mouse_position(int x, int y, t_game *game);
int					extra_number(const char *a, int i, int num);
int					rotate_left_right(t_game *game, double rotspeed);
int					rotate_player(t_game *game, int rotdir);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
int					loop_hook(t_game *game);
void				handle_movement(t_game *game);
int					press_key(int keysem, t_game *game);
int					press_x(t_game *game);
int					moves_loop(t_game *data);
int					release_key(int keysem, t_game *data);
int					game_loop(t_game *game);
void				load_textures(t_game *game, t_textures *tex);
int					mouse_move(int x, int y, t_game *game);
int					check_player_pos(t_map *map);
int					global_color(char *line, t_game *game);
int					tex_global(char *line, t_textures *tex);
void				validate_textures(t_textures *tex);
void				hook_init(t_game *game);
void				line_free(t_textures tex);
void				init_win(t_game *game);
void				init_player(t_player *player, t_player map_player);
void				parse_args(int ac, char **av);
int					open_map_file(char *file_name);
int					skip_whitespace(char *line);
void				print_error(void);
void				t_fil(char **tokens);
int					str_to_int_strict(const char *str, int *out);
int					count_pos(t_map *map);
void				set_player_dir(t_player *p, char c);
int					find_big_line(char **map);
void				init_draw_texture(t_draw_texture *dt);
char				**get_map(char *line, int fd);
int					check_collision(t_game *game, float x, float y);
void				cleanup_game(t_game *game);
void				free_map_grid(char **grid);
void				setup_draw_texture(t_game *game, t_ray *ray,
						int wall_height);
void				init_ray_data(t_cast_ray *data, t_game *game, t_ray *ray);
void				init_draw(t_draw *draw);
void				init_keys(t_keys *keys);
void				init_all_rays(t_ray rays[NUM_RAYS]);
void				init_textures(t_texture textures[NUM_TEXTURES]);
void				f(t_game *game);
void				performe_dda(t_ray *ray, t_cast_ray *data, t_game *game);
void				color_logo(const char **logo);
void				print_cub3d_logo(void);
int					check_new_line(t_map map);
char				*ft_strnstr(const char *str, const char *substr,
						size_t len);
int					is_line_empty(char *line);
int					is_player(char c);
int					check_zero(t_map map, int x, int y);
int					check_one(t_map map, int x, int y);
int					check_first(char **maze);
int					check_last(char **maze);
int					check_first_last_line(char **maze);
int					check_left_right(char **maze);
int					check_map2(char **maze);
void				duplicate_color(void);
void				check_tex(t_textures	*tex);
void				print_error_map(t_map *map);
void				free_textures_strings(t_textures *tex);
void				*gc_malloc(size_t size);
void				gc_free_all(void);
void				gc_free_all(void);
void				init_draw_texture(t_draw_texture *dt);
void	validate_textures(t_textures *tex);
#endif
