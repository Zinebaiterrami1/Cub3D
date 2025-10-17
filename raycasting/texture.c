/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:47:11 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/17 11:35:05 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


//-----------TEXTURES----------
void load_textures(t_game *game)
{
    char *texture_files[NUM_TEXTURES] = {
        "textures/bluestone.xpm",
        "textures/wall2.xpm", 
        "textures/wall1.xpm",
        "textures/wood.xpm"
    };
    
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        game->textures[i].img = mlx_xpm_file_to_image(game->gfx.mlx, 
            texture_files[i], &game->textures[i].width, &game->textures[i].height);
        if (!game->textures[i].img)
        {
            printf("Error: Could not load texture %s\n", texture_files[i]);
            game->textures[i].img = mlx_new_image(game->gfx.mlx, TEX_WIDTH, TEX_HEIGHT);
            game->textures[i].width = TEX_WIDTH;
            game->textures[i].height = TEX_HEIGHT;
        }
        game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
            &game->textures[i].bpp, &game->textures[i].line_len, &game->textures[i].endian);
    }
}

unsigned int get_texture_pixel(t_texture *tex, int x, int y)
{
    // Wrap texture coordinates if they're out of bounds
    if (x < 0) x = 0;
    if (x >= tex->width) x = tex->width - 1;
    if (y < 0) y = 0;
    if (y >= tex->height) y = tex->height - 1;
    
    // Calculate pixel position in texture data
    int pixel = y * tex->line_len + x * (tex->bpp / 8);
    return *(unsigned int *)(tex->addr + pixel);
}

void draw_sky_and_floor(t_game *game)
{
    int (y), (x);

    x = 0;
    y = 0;
    while(y < HEIGHT / 2)
    {
        x = 0;
        while(x < WIDTH)
        {
            my_mlx_pixel_put(&game->gfx, x, y, 0x87CEEB); // Sky blue
            x++;
        }
        y++;
    }
    y = HEIGHT / 2;
    while(y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            my_mlx_pixel_put(&game->gfx, x, y, 0x228B22); // Forest green
            x++;
        }
        y++;
    }
}

// Draw a vertical slice of textured wall
void draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray, int wall_height)
{
    int screen_y;
    unsigned int color;

    float wall_top = (HEIGHT / 2) - (wall_height / 2);
    float wall_bottom = (HEIGHT / 2) + (wall_height / 2);
    if (wall_top < 0) wall_top = 0;
    if (wall_bottom > HEIGHT) wall_bottom = HEIGHT;
    
    // Calculate texture X coordinate (where we hit the wall)
    int tex_x = (int)(ray->wall_x * TEX_WIDTH);
    
    // Choose texture based on wall type and side
    int tex_num = determine_texture(ray);
    t_texture *texture = &game->textures[tex_num];
    float step = 1.0 * TEX_HEIGHT / wall_height;
    float tex_pos = (wall_top - HEIGHT / 2 + wall_height / 2) * step;
    
    screen_y = wall_top;
    // Draw each pixel of the wall slice
    while(screen_y < wall_bottom)
    {
        int tex_y = (int)tex_pos;
        tex_pos += step;
        color = get_texture_pixel(texture, tex_x, tex_y);
        my_mlx_pixel_put(&game->gfx, screen_x, screen_y, color);
        screen_y++;
    }
}

// Determine which texture to use based on wall side and type
int determine_texture(t_ray *ray)
{
    // Corrected logic:
    if (ray->side == 0) { // Vertical wall hit (East/West), North/South facing wall
        if (ray->rayDX > 0)
            return (0); // East wall, texture
        else
            return (1); // West wall
    } else { // Horizontal wall hit (North/South), East/West facing wall
        if (ray->rayDY > 0)
            return (3); // South wall
        else
            return (2); // North wall
    }
}

void render_3d_textured(t_game *game)
{
    // Clear screen
    clear_screen(&game->gfx);
    
    // Draw sky and floor
    draw_sky_and_floor(game);
    
    float start_angle = game->player.angle - FOV / 2;
    float angle_step = FOV / NUM_RAYS;

    // Draw textured walls
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float ray_angle = start_angle + i * angle_step;
        float dist = game->ray_distances[i];
        float corrected_dist = dist * cos(ray_angle - game->player.angle);
        
        // Calculate wall height
        float proj_plane = (WIDTH / 2) / tan(FOV / 2);
        int wall_height = (TILE_SIZE / corrected_dist) * proj_plane;
        
        // Create a temporary ray with the data we have
        t_ray temp_ray = game->rays[i];
        temp_ray.dist = dist;
        temp_ray.angle = ray_angle;
        temp_ray.rayDX = cos(ray_angle);
        temp_ray.rayDY = sin(ray_angle);
        
        // Draw this slice of textured wall WITH CORRECTED DISTANCE
        draw_textured_wall_slice(game, i, &temp_ray, wall_height);
    }
}

t_ray cast_ray_textured(t_game *game, float ray_angle)
{
    t_ray ray;

    // direction vector
    ray.rayDX = cos(ray_angle);
    ray.rayDY = sin(ray_angle);
    ray.angle = ray_angle;

    int mapX = (int)(game->player.x / TILE_SIZE);
    int mapY = (int)(game->player.y / TILE_SIZE);

    float deltaDistX = fabs(1 / ray.rayDX);
    float deltaDistY = fabs(1 / ray.rayDY);
    float sideDistX, sideDistY;
    int stepX, stepY;
    int hit = 0;

    if (ray.rayDX < 0)
    {
        stepX = -1;
        sideDistX = (game->player.x / TILE_SIZE - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player.x / TILE_SIZE) * deltaDistX;
    }

    if (ray.rayDY < 0)
    {
        stepY = -1;
        sideDistY = (game->player.y / TILE_SIZE - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player.y / TILE_SIZE) * deltaDistY;
    }

    int side = 0;
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (map[mapY][mapX] > 0)
            hit = 1;
    }

    float perpWallDist;
    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    // Calculate where the wall was hit (0-1)
    float wallX;
    if (side == 0)
        wallX = (game->player.y / TILE_SIZE + perpWallDist * ray.rayDY) - floor(game->player.y / TILE_SIZE + perpWallDist * ray.rayDY);
    else
        wallX = (game->player.x / TILE_SIZE + perpWallDist * ray.rayDX) - floor(game->player.x / TILE_SIZE + perpWallDist * ray.rayDX);

    ray.wall_x = wallX;
    ray.dist = perpWallDist * TILE_SIZE;
    ray.side = side;
    ray.wall_type = map[mapY][mapX];

    return ray;
}