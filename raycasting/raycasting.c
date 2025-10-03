/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:15 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/02 15:11:38 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


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

// ---------- Map ----------
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

// ---------- Lignes avec DDA ----------
void draw_line_dda(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    int steps;
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    if (steps == 0)
        return;

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        int mapX = (int)x / TILE_SIZE;
        int mapY = (int)y / TILE_SIZE;
        
        // Check bounds properly - mapX and mapY should be within [0, mapx-1] and [0, mapy-1]
        if (mapX >= 0 && mapX < mapx && mapY >= 0 && mapY < mapy)
        {
            if (map[mapY * mapx + mapX] == 1)
            {
                break;
            }
        }
        // else
        // {
        //     // Out of bounds, treat as wall
        //     break;
        // }
        
        my_mlx_pixel_put(mlx, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }    
}

// ---------- Joueur ----------
void draw_player(t_game *game)
{
    draw_tile(&game->gfx, (int)game->player.x - PLAYER_SIZE/2,
              (int)game->player.y - PLAYER_SIZE/2,
              PLAYER_SIZE, 0xFF0000);

    int line_length = 200;
    int x_end = game->player.x + game->player.dx * line_length;
    int y_end = game->player.y + game->player.dy * line_length;

    draw_line_dda(&game->gfx, game->player.x, game->player.y, x_end, y_end, 0x0000FF);
}

// ---------- Clear ----------
void clear_screen(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            my_mlx_pixel_put(mlx, x, y, 0x000000);
}

// ---------- Collision ----------
int is_wall(float x, float y)
{
    int mx = (int)(x / TILE_SIZE);
    int my = (int)(y / TILE_SIZE);
    if (mx < 0 || mx >= mapx || my < 0 || my >= mapy)
        return 1;
    return map[my * mapx + mx];
}

// ---------- Clavier ----------
int key_hook(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    float next_x = game->player.x;
    float next_y = game->player.y;

    if (keycode == 65307) // ESC
        exit(0);

    // Avancer / Reculer
    if (keycode == 119) { next_x += game->player.dx; next_y += game->player.dy; }
    if (keycode == 115) { next_x -= game->player.dx; next_y -= game->player.dy; }

    // Strafe gauche / droite
    if (keycode == 97)  { next_x += -game->player.dy; next_y += game->player.dx; }
    if (keycode == 100) { next_x += game->player.dy; next_y += -game->player.dx; }

    // Rotation gauche/droite
    if (keycode == 65361)
    {
        game->player.angle -= ROT_SPEED;
        if (game->player.angle < 0) game->player.angle += 2 * M_PI;
        game->player.dx = cos(game->player.angle) * SPEED;
        game->player.dy = sin(game->player.angle) * SPEED;
    }
    if (keycode == 65363)
    {
        game->player.angle += ROT_SPEED;
        if (game->player.angle > 2 * M_PI) game->player.angle -= 2 * M_PI;
        game->player.dx = cos(game->player.angle) * SPEED;
        game->player.dy = sin(game->player.angle) * SPEED;
    }

    if (!is_wall(next_x, next_y))
    {
        game->player.x = next_x;
        game->player.y = next_y;
    }

    clear_screen(&game->gfx);
    draw_map2d(game);
    draw_player(game);
    mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);

    return 0;
}

int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

// ---------- Main ----------
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

    mlx_hook(game.gfx.win, 2, 1L<<0, key_hook, &game);
    mlx_hook(game.gfx.win, 17, 0, close_window, NULL);
    mlx_loop(game.gfx.mlx);

    return 0;
}


// int close_window(void *param)
// {
//     t_game *game = (t_game *)param;

//     // Free textures, map, etc. if you stored them in game
//     if (game->gfx.win)
//         mlx_destroy_window(game->gfx.mlx, game->gfx.win);
//     if (game->gfx.mlx)
//         free(game->gfx.mlx); // careful: sometimes mlx handles this internally

//     exit(0);
//     return (0);
// }
