// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mlx.h                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/11/13 21:05:28 by zait-err          #+#    #+#             */
// /*   Updated: 2025/11/13 21:05:29 by zait-err         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef MLX_H
// # define MLX_H

// typedef void	*mlx_ptr_t;
// typedef void	*mlx_win_t;
// typedef void	*mlx_img_t;

// void			*mlx_init(void);
// void			*mlx_new_window(void *mlx_ptr, int size_x, int size_y,
// 					char *title);
// void			*mlx_new_image(void *mlx_ptr, int width, int height);
// char			*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
// 					int *size_line, int *endian);
// void			*mlx_xpm_file_to_image(void *mlx_ptr, char *file, int *width,
// 					int *height);
// void			mlx_destroy_image(void *mlx_ptr, void *img_ptr);
// void			mlx_destroy_window(void *mlx_ptr, void *win_ptr);
// void			mlx_destroy_display(void *mlx_ptr);
// int				mlx_put_image_to_window(void *mlx_ptr, void *win_ptr,
// 					void *img_ptr, int x, int y);
// int				mlx_loop(void *mlx_ptr);
// int				mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param);
// int				mlx_hook(void *win_ptr, int x_event, int x_mask, int (*f)(),
// 					void *param);
// int				mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);

// #endif /* MLX_H */
