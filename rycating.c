#include "mlx.h"
#include <stdlib.h>

int screenWidth = 800;
int screenHeight = 600;

// Position du joueur
float px = 200, py = 200;
int player_size = 10;
float speed = 10;

// MLX
void *mlx;
void *win;

// Map 2D
int mapx = 8, mapy = 8;
int map[] =
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,1,1,0,1,
    1,1,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,1,0,0,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,1,1,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

// Fonction pour mettre un pixel
void my_mlx_pixel_put(void *mlx, void *win, int x, int y, int color)
{
    mlx_pixel_put(mlx, win, x, y, color);
}

// Dessiner un carré (case)
void draw_tile(int x, int y, int size, int color)
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            my_mlx_pixel_put(mlx, win, x + i, y + j, color);
}

// Dessiner la map 2D
void draw_map2d()
{
    int i, j;
    int tile_size = 70; // taille d'une case
    int border = 2;     // bordure pour séparer les cases
    for (i = 0; i < mapy; i++)
    {
        for (j = 0; j < mapx; j++)
        {
            int color = map[i * mapx + j] ? 0x808080 : 0xFFFFFF;
            draw_tile(j * tile_size, i * tile_size, tile_size - border, color);
        }
    }
}

// Dessiner le joueur
void draw_player()
{
    draw_tile((int)px, (int)py, player_size, 0xFF0000);
}

// Effacer tout l'écran (fond noir)
void clear_screen()
{
    int x, y;
    for (y = 0; y < screenHeight; y++)
        for (x = 0; x < screenWidth; x++)
            my_mlx_pixel_put(mlx, win, x, y, 0x000000);
}

// Gestion des touches
int key_hook(int keycode, void *param)
{
    (void)param;

    if (keycode == 65307) // ESC
        exit(0);
    else if (keycode == 119) // W
        py -= speed;
    else if (keycode == 115) // S
        py += speed;
    else if (keycode == 97) // A
        px -= speed;
    else if (keycode == 100) // D
        px += speed;

    clear_screen();
    draw_map2d();
    draw_player();

    return 0;
}

int main()
{
    mlx = mlx_init();
    if (!mlx) return 1;

    win = mlx_new_window(mlx, screenWidth, screenHeight, "Cub3D 2D Map");
    if (!win) return 1;

    draw_map2d();
    draw_player();

    mlx_key_hook(win, key_hook, NULL);
    mlx_loop(mlx);

    return 0;
}
