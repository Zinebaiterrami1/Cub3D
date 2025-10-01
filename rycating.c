#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 70
#define PLAYER_SIZE 10
#define SPEED 5
#define ROT_SPEED 0.1

// Position du joueur
float px, py; // position
float pa;     // angle du joueur
float pdx, pdy; // vecteur direction

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

// MLX
void *mlx;
void *win;
void *img;
char *img_addr;
int bpp, line_len, endian;

// --------- UTILITAIRES ----------
void my_mlx_pixel_put(int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    int pixel = y * line_len + x * (bpp / 8);
    *(unsigned int *)(img_addr + pixel) = color;
}

void draw_tile(int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            my_mlx_pixel_put(x + i, y + j, color);
}

void draw_map2d()
{
    int border = 2;
    for (int i = 0; i < mapy; i++)
    {
        for (int j = 0; j < mapx; j++)
        {
            int color = map[i * mapx + j] ? 0x808080 : 0xFFFFFF;
            draw_tile(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE - border, color);
        }
    }
}

void draw_line(int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_player()
{
    draw_tile((int)px - PLAYER_SIZE/2, (int)py - PLAYER_SIZE/2, PLAYER_SIZE, 0xFF0000);
    int line_length = 40;
    int x_end = px + pdx * line_length;
    int y_end = py + pdy * line_length;
    draw_line(px, py, x_end, y_end, 0x0000FF);
}

void clear_screen()
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            my_mlx_pixel_put(x, y, 0x000000);
}

// --------- COLLISION ----------
int is_wall(float x, float y)
{
    int mx = (int)(x / TILE_SIZE);
    int my = (int)(y / TILE_SIZE);
    if (mx < 0 || mx >= mapx || my < 0 || my >= mapy)
        return 1;
    return map[my * mapx + mx];
}

// --------- CLAVIER ----------
int key_hook(int keycode, void *param)
{
    (void)param;
    float next_px = px;
    float next_py = py;

    if (keycode == 65307) // ESC
        exit(0);
    else if (keycode == 119) // W
    {
        next_px = px + pdx;
        next_py = py + pdy;
    }
    else if (keycode == 115) // S
    {
        next_px = px - pdx;
        next_py = py - pdy;
    }
    else if (keycode == 97) // A tourner gauche
    {
        pa -= ROT_SPEED;
        if (pa < 0) pa += 2 * M_PI;
        pdx = cos(pa) * SPEED;
        pdy = sin(pa) * SPEED;
    }
    else if (keycode == 100) // D tourner droite
    {
        pa += ROT_SPEED;
        if (pa > 2 * M_PI) pa -= 2 * M_PI;
        pdx = cos(pa) * SPEED;
        pdy = sin(pa) * SPEED;
    }

    // Collision avant déplacement
    if (!is_wall(next_px, next_py))
    {
        px = next_px;
        py = next_py;
    }

    clear_screen();
    draw_map2d();
    draw_player();
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    return 0;
}

// ---------- MAIN ----------
int main()
{
    mlx = mlx_init();
    if (!mlx) return 1;

    win = mlx_new_window(mlx, WIDTH, HEIGHT, "Cub3D 2D Map");

    // Création du buffer image
    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img_addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

    // Position initiale dans une case libre
    px = TILE_SIZE + TILE_SIZE/2; 
    py = TILE_SIZE + TILE_SIZE/2;
    pa = 0;
    pdx = cos(pa) * SPEED;
    pdy = sin(pa) * SPEED;

    clear_screen();
    draw_map2d();
    draw_player();
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    mlx_key_hook(win, key_hook, NULL);
    mlx_loop(mlx);

    return 0;
}
