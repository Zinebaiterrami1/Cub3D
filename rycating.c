#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include "cub3d.h"

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

// ---------- Pixel ----------
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    int pixel = y * mlx->line_len + x * (mlx->bpp / 8);
    *(unsigned int *)(mlx->img_addr + pixel) = color;
}

void draw_tile(t_mlx *mlx, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (x + i >= 0 && x + i < WIDTH && y + j >= 0 && y + j < HEIGHT)
                my_mlx_pixel_put(mlx, x + i, y + j, color);
}


void draw_map2d(t_game *game)
{
    int border = 1;
    for (int i = 0; i < mapy; i++)
    {
        for (int j = 0; j < mapx; j++)
        {
            int color = map[i * mapx + j] ? 0x808080 : 0xFFFFFF;
            draw_tile(&game->gfx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE - border, color);
        }
    }
}

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        my_mlx_pixel_put(mlx, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_player(t_game *game)
{
    draw_tile(&game->gfx, (int)game->player.x - PLAYER_SIZE/2,
              (int)game->player.y - PLAYER_SIZE/2,
              PLAYER_SIZE, 0xFF0000);
    int line_length = 40;
    int x_end = game->player.x + game->player.dx * line_length;
    int y_end = game->player.y + game->player.dy * line_length;
    draw_line(&game->gfx, game->player.x, game->player.y, x_end, y_end, 0x0000FF);
}

void clear_screen(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            my_mlx_pixel_put(mlx, x, y, 0x000000);
}

// ---------- COLLISION ----------
int is_wall(float x, float y)
{
    int mx = (int)(x / TILE_SIZE);
    int my = (int)(y / TILE_SIZE);
    if (mx < 0 || mx >= mapx || my < 0 || my >= mapy)
        return 1;
    return map[my * mapx + mx];
}

// ---------- CLAVIER ----------
// ---------- CLAVIER ----------
int key_hook(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    float next_x = game->player.x;
    float next_y = game->player.y;

    // Quitter
    if (keycode == 65307) // ESC
        exit(0);

    // Déplacement avant/arrière
    else if (keycode == 119) // W
    {
        next_x += game->player.dx;
        next_y += game->player.dy;
    }
    else if (keycode == 115) // S
    {
        next_x -= game->player.dx;
        next_y -= game->player.dy;
    }

    // Strafe gauche/droite
    else if (keycode == 97) // A (strafe gauche)
    {
        next_x += -game->player.dy; // perpendiculaire à dx/dy
        next_y += game->player.dx;
    }
    else if (keycode == 100) // D (strafe droite)
    {
        next_x += game->player.dy; // perpendiculaire à dx/dy
        next_y += -game->player.dx;
    }

    // Rotation gauche/droite
    else if (keycode == 65361) // Flèche gauche
    {
        game->player.angle -= ROT_SPEED;
        if (game->player.angle < 0) game->player.angle += 2 * M_PI;
        game->player.dx = cos(game->player.angle) * SPEED;
        game->player.dy = sin(game->player.angle) * SPEED;
    }
    else if (keycode == 65363) // Flèche droite
    {
        game->player.angle += ROT_SPEED;
        if (game->player.angle > 2 * M_PI) game->player.angle -= 2 * M_PI;
        game->player.dx = cos(game->player.angle) * SPEED;
        game->player.dy = sin(game->player.angle) * SPEED;
    }

    // Collision
    if (!is_wall(next_x, next_y))
    {
        game->player.x = next_x;
        game->player.y = next_y;
    }

    // Rafraîchissement de l'écran
    clear_screen(&game->gfx);
    draw_map2d(game);
    draw_player(game);
    mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);

    return 0;
}


// ---------- MAIN ----------
int main()
{
    t_game game;

    game.gfx.mlx = mlx_init();
    game.gfx.win = mlx_new_window(game.gfx.mlx, WIDTH, HEIGHT, "Cub3D 2D Map");
    game.gfx.img = mlx_new_image(game.gfx.mlx, WIDTH, HEIGHT);
    game.gfx.img_addr = mlx_get_data_addr(game.gfx.img,
                                          &game.gfx.bpp,
                                          &game.gfx.line_len,
                                          &game.gfx.endian);

    game.player.x = TILE_SIZE + TILE_SIZE/2;
    game.player.y = TILE_SIZE + TILE_SIZE/2;
    game.player.angle = 0;
    game.player.dx = cos(game.player.angle) * SPEED;
    game.player.dy = sin(game.player.angle) * SPEED;

    clear_screen(&game.gfx);
    draw_map2d(&game);
    draw_player(&game);
    mlx_put_image_to_window(game.gfx.mlx, game.gfx.win, game.gfx.img, 0, 0);

    mlx_hook(game.gfx.win, 2, 1L<<0, key_hook,  &game);

    mlx_loop(game.gfx.mlx);

    return 0;
}


