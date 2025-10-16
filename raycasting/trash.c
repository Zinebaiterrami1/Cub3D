/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:15 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/16 14:33:25 by zait-err         ###   ########.fr       */
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
    if(steps == 0)
        return;
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        int mapX = (int)x / TILE_SIZE;
        int mapY = (int)y / TILE_SIZE;
        if((mapX >= 0 && mapX < mapx) && (mapY >= 0 && mapY < mapy))
        {
            if(map[mapY * mapx + mapX] == 1)
            {
                break;
            }
        }
        my_mlx_pixel_put(mlx, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }    
}

// ---------- FOV Raycasting ----------
void draw_fov_rays(t_game *game)
{
    t_ray ray;

    float angle_step = FOV / NUM_RAYS;
    float start_angle = game->player.angle - FOV / 2;
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        ray.ray_angle = start_angle + i * angle_step;
        
        // Cast ray until it hits a wall
        ray.rayX = game->player.x;
        ray.rayY = game->player.y;
        ray.rayDX = cos(ray.ray_angle) * 2;
        ray.rayDY = sin(ray.ray_angle) * 2;
        
        render_3d_map(game, &ray, i);
        int hit_wall = 0;
        int max_distance = 300; // Maximum ray distance
        int steps = 0;
        
        while (!hit_wall && steps < max_distance)
        {
            ray.rayX += ray.rayDX;
            ray.rayY += ray.rayDY;
            steps++;
            // Check if ray hit a wall
            int mapX = (int)(ray.rayX / TILE_SIZE);
            int mapY = (int)(ray.rayY / TILE_SIZE);
            
            if (mapX < 0 || mapX >= mapx || mapY < 0 || mapY >= mapy || map[mapY * mapx + mapX] == 1)
            {
                hit_wall = 1;
            }
        }
        // Draw the ray
        draw_line_dda(&game->gfx, game->player.x, game->player.y, ray.rayX,  ray.rayY, 0x00FF00);
    }
}

// ---------- Joueur ----------
void draw_player(t_game *game)
{
    draw_tile(&game->gfx, (int)game->player.x - PLAYER_SIZE/2,
              (int)game->player.y - PLAYER_SIZE/2,
              PLAYER_SIZE, 0xFF0000);

    // Draw FOV rays instead of single ray
    draw_fov_rays(game);
}
//lets render to 3D map

// void verLine(int i, int drawStart, int drawEnd, t_game game)
// {
//     if (drawStart < 0)
//     {
//         drawStart = 0;
//         my_mlx_pixel_put(&game.gfx, drawStart, drawEnd, #33FFDA);
//     }

//     if (drawEnd >= HEIGHT)
//     {
//         drawEnd = HEIGHT - 1;
//         my_mlx_pixel_put(&game.gfx, drawStart, drawEnd, #FF5733);
//     }
// }

void verLine(t_mlx *mlx, int x, int drawStart, int drawEnd, int color)
{
    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    for (int y = drawStart; y < drawEnd; y++)
        my_mlx_pixel_put(mlx, x, y, color);
}

void render_3d_map(t_game *game, t_ray *ray, int i)
{
    // Current map square
    int mapX = (int)(game->player.x / TILE_SIZE);
    int mapY = (int)(game->player.y / TILE_SIZE);

    // Direction step (+1 or -1)
    int stepX;
    int stepY;

    // Distance to next x or y side
    float sideDistX;
    float sideDistY;

    // How far we must travel to cross one tile horizontally/vertically
    float deltaDistX = fabs(1 / ray->rayDX);
    float deltaDistY = fabs(1 / ray->rayDY);
    float perpWallDist;
    int hit = 0;
    int side;

    // Choose direction of stepX / stepY
    if (ray->rayDX < 0)
    {
        stepX = -1;
        sideDistX = (game->player.x / TILE_SIZE - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player.x / TILE_SIZE) * deltaDistX;
    }
    if (ray->rayDY < 0)
    {
        stepY = -1;
        sideDistY = (game->player.y / TILE_SIZE - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player.y / TILE_SIZE) * deltaDistY;
    }

    // --- Perform DDA ---
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // hit vertical wall
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // hit horizontal wall
        }

        if (map[mapY * mapx + mapX] == 1)
            hit = 1;
    }

    // --- Calculate distance to wall ---
    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    // Save the distance (for wall height)
    ray->sideDirX = sideDistX;
    ray->sideDirY = sideDistY;
    ray->rayX = perpWallDist;

    int lineHeight = (int)(HEIGHT / perpWallDist);
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;

    // Then draw a vertical stripe (a column of pixels)
    // verLine(i, drawStart, drawEnd, game->gfx);
    int color = (side == 1) ? 0x00AAFF : 0x0099DD; // darker if horizontal
    verLine(&game->gfx, i, drawStart, drawEnd, color);
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


// // Draw a vertical slice of textured wall 
/*first implementation of draw_text_fct that cause the stretch of the text when the wall height increase*/
void draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray, int wall_height)
{
    int wall_top = (HEIGHT / 2) - (wall_height / 2);
    int wall_bottom = (HEIGHT / 2) + (wall_height / 2);
    
    if (wall_top < 0) wall_top = 0;
    if (wall_bottom > HEIGHT) wall_bottom = HEIGHT;
    
    // Calculate texture X coordinate (where we hit the wall)
    int tex_x = (int)(ray->wall_x * TEX_WIDTH);
    
    // Choose texture based on wall type and side
    int tex_num = determine_texture(ray);
    t_texture *texture = &game->textures[tex_num];
        // Calculate corrected distance for this specific ray
    // float corrected_dist = ray->dist * cos(ray->angle - game->player.angle);
    // Draw each pixel of the wall slice
    for (int screen_y = wall_top; screen_y < wall_bottom; screen_y++)
    {
        // Calculate texture Y coordinate
        int tex_y = (screen_y - wall_top) * TEX_HEIGHT / wall_height;
        
        // Get color from texture
        unsigned int color = get_texture_pixel(texture, tex_x, tex_y);
        
        // Apply shading based on distance and wall side
        color = apply_shading(color, ray->dist, ray->side);
        
        // Put the pixel on screen
        my_mlx_pixel_put(&game->gfx, screen_x, screen_y, color);
    }
}


// Apply distance-based shading
unsigned int apply_shading(unsigned int color, float dist, int side)
{
    float shade = 1.0f - (dist / 15.0f); // Darken with distance
    if (shade < 0.3f) shade = 0.3f;
    
    // Darken one side for better 3D effect
    if (side == 1) 
        shade *= 0.8f;
    
    // Extract RGB components
    int r = ((color >> 16) & 0xFF) * shade;
    int g = ((color >> 8) & 0xFF) * shade;
    int b = (color & 0xFF) * shade;
    
    return (r << 16) | (g << 8) | b;
}