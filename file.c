/* Add this to your cub3d.h */
void	cleanup_game(t_game *game);

/* Add this new file or put in an existing cleanup file */

#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	int	i;

	// Free textures
	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->gfx.mlx, game->textures[i].img);
		i++;
	}

	// Free gun textures
	i = 0;
	while (i < 2)
	{
		if (game->gun.gun_texture[i].img)
			mlx_destroy_image(game->gfx.mlx, game->gun.gun_texture[i].img);
		i++;
	}

	// Free MLX resources
	if (game->gfx.img)
		mlx_destroy_image(game->gfx.mlx, game->gfx.img);
	if (game->gfx.win)
		mlx_destroy_window(game->gfx.mlx, game->gfx.win);
	if (game->gfx.mlx)
	{
		mlx_destroy_display(game->gfx.mlx);
		free(game->gfx.mlx);
	}
}

/* Update destroy_mlx function in Cub3D.c */
int	destroy_mlx(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

/* Update close_window in win.c */
int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game)
		cleanup_game(game);
	exit(0);
	return (0);
}

/* Update key_press in key_hook.c */
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_SPC)
		shoot(game);
	return (0);
}