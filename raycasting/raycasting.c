/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:15 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/18 15:21:35 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"


int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,0,1},
    {1,0,1,0,0,1,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
};

// ---------- FONCTIONS GRAPHIQUES ----------
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    int pixel = y * mlx->line_len + x * (mlx->bpp / 8);
    *(unsigned int *)(mlx->addr + pixel) = color;
}

void draw_tile(t_mlx *mlx, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            my_mlx_pixel_put(mlx, x + i, y + j, color);
}

void clear_screen(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            my_mlx_pixel_put(mlx, x, y, 0x000000);
}

// ---------- MAP 2D ----------
void draw_map2d(t_game *game)
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            int color = map[i][j] ? 0x808080 : 0xFFFFFF;
            draw_tile(&game->gfx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE - 1, color);
        }
    }
}

// ---------- COLLISIONS ----------
int is_wall(float x, float y)
{
    int mx = (int)(x / TILE_SIZE);
    int my = (int)(y / TILE_SIZE);
    if (mx < 0 || mx >= MAP_WIDTH || my < 0 || my >= MAP_HEIGHT)
        return 1;
    return map[my][mx];
}

// ---------- LIGNES ----------
void draw_line_dda(t_mlx *mlx, float x0, float y0, float x1, float y1, int color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    if (steps == 0)
        return;
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(mlx, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

// ---------- CALCUL DU RAYON ----------
float cast_ray(t_game *game, float ray_angle)
{
    float ray_x = game->player.x;
    float ray_y = game->player.y;
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);

    while (!is_wall(ray_x, ray_y))
    {
        ray_x += ray_dx * 0.1f; //modified here , graphic issues fixed
        ray_y += ray_dy * 0.1f;
    }
    return sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y, 2));
}

// ---------- RAYONNEMENT ET STOCKAGE DES DISTANCES ----------
// void draw_fov_rays(t_game *game)
// {
//     float start_angle = game->player.angle - FOV / 2;
//     float angle_step = FOV / NUM_RAYS;

//     for (int i = 0; i < NUM_RAYS; i++)
//     {
//         float ray_angle = start_angle + i * angle_step;
//         float dist = cast_ray(game, ray_angle);
//         game->ray_distances[i] = dist;

//         // Dessin 2D des rayons verts sur la carte
//         float end_x = game->player.x + cos(ray_angle) * dist;
//         float end_y = game->player.y + sin(ray_angle) * dist;
//         draw_line_dda(&game->gfx, game->player.x, game->player.y, end_x, end_y, 0x00FF00);
//     }
// }

// ---------- JOUEUR ----------
void draw_player(t_game *game)
{
    draw_tile(&game->gfx, game->player.x - PLAYER_SIZE / 2,
              game->player.y - PLAYER_SIZE / 2, PLAYER_SIZE, 0xFF0000);
}

// ---------- 3D ----------
void draw_vertical_line(t_game *game, int x, int wall_top, int wall_bottom, int color)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        if (y < wall_top)
            my_mlx_pixel_put(&game->gfx, x, y, 0x87CEEB); // ciel
        else if (y >= wall_top && y <= wall_bottom)
            my_mlx_pixel_put(&game->gfx, x, y, color); // mur
        else
            my_mlx_pixel_put(&game->gfx, x, y, 0x228B22); // sol
    }
}

void render_3d(t_game *game)
{
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float ray_angle = (game->player.angle - (FOV / 2.0f)) + ((float)i / NUM_RAYS) * FOV;
        float dist = game->ray_distances[i];
        float corrected_dist = dist * cos(ray_angle - game->player.angle);

        float proj_plane = (WIDTH / 2) / tan(FOV / 2);
        int wall_height = (TILE_SIZE / corrected_dist) * proj_plane;
        int wall_top = (HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (HEIGHT / 2) + (wall_height / 2);

        if (wall_top < 0) wall_top = 0;
        if (wall_bottom > HEIGHT) wall_bottom = HEIGHT;

        int shade = 255 - (int)(dist / 3);
        if (shade < 50) shade = 50;
        int color = (shade << 16) | (shade << 8) | shade;

        draw_vertical_line(game, i, wall_top, wall_bottom, color);
    }
}

// ---------- CLAVIER ----------
int key_hook(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    float next_x = game->player.x;
    float next_y = game->player.y;

    if (keycode == 65307)
        exit(0);
    if (keycode == 119) { next_x += game->player.dx; next_y += game->player.dy; }
    if (keycode == 115) { next_x -= game->player.dx; next_y -= game->player.dy; }
    if (keycode == 100)  { next_x += -game->player.dy; next_y += game->player.dx; }
    if (keycode == 97) { next_x += game->player.dy; next_y += -game->player.dx; }

    if (keycode == 65361)
        game->player.angle -= ROT_SPEED;
    if (keycode == 65363)
        game->player.angle += ROT_SPEED;

    game->player.dx = cos(game->player.angle) * SPEED;
    game->player.dy = sin(game->player.angle) * SPEED;

    if (!is_wall(next_x, next_y))
    {
        game->player.x = next_x;
        game->player.y = next_y;
    }

    clear_screen(&game->gfx);
    // draw_map2d(game);
    draw_player(game);
    draw_fov_rays(game);
    // render_3d(game);
    render_3d_textured(game);  // CHANGE THIS LINE
    // clear_screen(&game->gfx);

    mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
    return 0;
}

// ---------- FERMETURE ----------
int close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

void draw_fov_rays(t_game *game)
{
    t_ray ray;
    t_cast_ray data;
    int i;

    data.start_angle = game->player.angle - FOV / 2;
    data.angle_step = FOV / NUM_RAYS;
    i = 0;
    while(i < NUM_RAYS)
    {
        ray.ray_angle = data.start_angle + i * data.angle_step;
        ray = cast_ray_textured(game, ray.ray_angle);
        game->rays[i] = ray;
        game->ray_distances[i] = ray.dist;
        ray.end_x = game->player.x + cos(ray.ray_angle) * ray.dist;
        ray.end_y = game->player.y + sin(ray.ray_angle) * ray.dist;
        draw_line_dda(&game->gfx, game->player.x, game->player.y, ray.end_x, ray.end_y, 0x00FF00);
        i++;
    }
}

// ---------- MAIN ----------

int main(void)
{
    t_game game;

    // Init window and image
    game.gfx.mlx = mlx_init();
    game.gfx.win = mlx_new_window(game.gfx.mlx, WIDTH, HEIGHT, "Cub3D - Textured Raycasting");
    game.gfx.img = mlx_new_image(game.gfx.mlx, WIDTH, HEIGHT);
    game.gfx.addr = mlx_get_data_addr(game.gfx.img, &game.gfx.bpp, &game.gfx.line_len, &game.gfx.endian);

    // Load textures
    load_textures(&game);

    // Initialize player
    game.player.x = TILE_SIZE * 1.5;
    game.player.y = TILE_SIZE * 1.5;
    game.player.angle = 0;
    game.player.dx = cos(game.player.angle) * SPEED;
    game.player.dy = sin(game.player.angle) * SPEED;

    // First render
    draw_sky_and_floor(&game);
    draw_fov_rays(&game);
    render_3d_textured(&game);
    mlx_put_image_to_window(game.gfx.mlx, game.gfx.win, game.gfx.img, 0, 0);

    // Hooks
    mlx_hook(game.gfx.win, 2, 1L << 0, key_hook, &game);
    mlx_hook(game.gfx.win, 17, 0, close_window, NULL);
    mlx_loop(game.gfx.mlx);

    return 0;
}
