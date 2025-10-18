void	load_textures(t_game *game)
{
	char	*texture_files[NUM_TEXTURES] = {"textures/bluestone.xpm",
			"textures/wall2.xpm", "textures/wall1.xpm", "textures/wood.xpm"};

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->gfx.mlx,
				texture_files[i], &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Error: Could not load texture %s\n", texture_files[i]);
			game->textures[i].img = mlx_new_image(game->gfx.mlx, TEX_WIDTH,
					TEX_HEIGHT);
			game->textures[i].width = TEX_WIDTH;
			game->textures[i].height = TEX_HEIGHT;
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
	}
}

unsigned int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	pixel;

	// Wrap texture coordinates if they're out of bounds
	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	// Calculate pixel position in texture data
	pixel = y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)(tex->addr + pixel));
}

void	draw_sky_and_floor(t_game *game)
{
	int(y), (x);
	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->gfx, x, y, 0x87CEEB); // Sky blue
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->gfx, x, y, 0x228B22); // Forest green
			x++;
		}
		y++;
	}
}

t_draw_texture init_draw_texture(t_draw_texture draw_tex)
{
    draw_tex.wall_top = 0;
    draw_tex.wall_bottom = 0;
    draw_tex.screen_x = 0;
    draw_tex.screen_y = 0;
    draw_tex.tex_x = 0;
    draw_tex.tex_y = 0;
    draw_tex.tex_num = 0;
    draw_tex.tex_pos = 0;
    draw_tex.step = 0;
    draw_tex.color = 0;
    draw_tex.wall_height = 0;
    return (draw_tex);
}

// Draw a vertical slice of textured wall
void	draw_textured_wall_slice(t_game *game, int screen_x, t_ray *ray,
		int wall_height)
{
    t_draw_texture draw_tex;
    t_texture      *texture;

    // draw_tex = init_draw_texture(draw_tex);
	draw_tex.wall_top = (HEIGHT / 2) - (wall_height / 2);
	draw_tex.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	if (draw_tex.wall_top < 0)
		draw_tex.wall_top = 0;
	if (draw_tex.wall_bottom > HEIGHT)
		draw_tex.wall_bottom = HEIGHT;
	// Calculate texture X coordinate (where we hit the wall)
	draw_tex.tex_x = (int)(ray->wall_x * TEX_WIDTH);
	// Choose texture based on wall type and side
	draw_tex.tex_num = determine_texture(ray);
	texture = &game->textures[draw_tex.tex_num];
	draw_tex.step = 1.0 * TEX_HEIGHT / wall_height;
	draw_tex.tex_pos = (draw_tex.wall_top - HEIGHT / 2 + wall_height / 2) * draw_tex.step;
	draw_tex.screen_y = draw_tex.wall_top;
	// Draw each pixel of the wall slice
	while (draw_tex.screen_y < draw_tex.wall_bottom)
	{
		draw_tex.tex_y = (int)draw_tex.tex_pos;
		draw_tex.tex_pos +=  draw_tex.step;
		draw_tex.color = get_texture_pixel(texture, draw_tex.tex_x, draw_tex.tex_y);
		my_mlx_pixel_put(&game->gfx, screen_x, draw_tex.screen_y, draw_tex.color);
		draw_tex.screen_y++;
	}
}

// Determine which texture to use based on wall side and type
int	determine_texture(t_ray *ray)
{
	// Corrected logic:
	if (ray->side == 0)
	{ // Vertical wall hit (East/West), North/South facing wall
		if (ray->rayDX > 0)
			return (0); // East wall, texture
		else
			return (1); // West wall
	}
	else
	{ // Horizontal wall hit (North/South), East/West facing wall
		if (ray->rayDY > 0)
			return (3); // South wall
		else
			return (2); // North wall
	}
}

void	render_3d_textured(t_game *game)
{
	t_draw_texture draw_tex;
	t_ray	temp_ray;
    t_ray ray;
	// Clear screen
	clear_screen(&game->gfx);
	// Draw sky and floor
	draw_sky_and_floor(game);
    // draw_tex = init_draw_texture(draw_tex);
	ray.start_angle = game->player.angle - FOV / 2;
	ray.angle_step = FOV / NUM_RAYS;
	// Draw textured walls
	for (draw_tex.screen_x = 0; draw_tex.screen_x < NUM_RAYS; draw_tex.screen_x++)
	{
		ray.ray_angle = ray.start_angle + draw_tex.screen_x * ray.angle_step;
		ray.dist = game->ray_distances[draw_tex.screen_x];
		ray.corrected_dist = ray.dist * cos(ray.ray_angle - game->player.angle);
		// Calculate wall height
		ray.proj_plane = (WIDTH / 2) / tan(FOV / 2);
		draw_tex.wall_height = (TILE_SIZE / ray.corrected_dist) * ray.proj_plane;
		// Create a temporary ray with the data we have
		temp_ray = game->rays[draw_tex.screen_x];
		temp_ray.dist = ray.dist;
		temp_ray.angle = ray.ray_angle;
		temp_ray.rayDX = cos(ray.ray_angle);
		temp_ray.rayDY = sin(ray.ray_angle);
		// Draw this slice of textured wall WITH CORRECTED DISTANCE
		draw_textured_wall_slice(game, draw_tex.screen_x, &temp_ray, draw_tex.wall_height);
	}
}

t_ray	cast_ray_textured(t_game *game, float ray_angle)
{
	t_ray ray;
	t_cast_ray data;
	// direction vector
	ray.rayDX = cos(ray_angle);
	ray.rayDY = sin(ray_angle);
	ray.angle = ray_angle;

	data.mapX = (int)(game->player.x / TILE_SIZE);
	data.mapY = (int)(game->player.y / TILE_SIZE);

	ray.deltaDistX = fabs(1 / ray.rayDX);
	ray.deltaDistY = fabs(1 / ray.rayDY);
	ray.hit = 0;

	if (ray.rayDX < 0)
	{
		ray.stepX = -1;
		ray.sideDistX = (game->player.x / TILE_SIZE - data.mapX) * ray.deltaDistX;
	}
	else
	{
		ray.stepX = 1;
		ray.sideDistX = (data.mapX + 1.0 - game->player.x / TILE_SIZE) * ray.deltaDistX;
	}

	if (ray.rayDY < 0)
	{
		ray.stepY = -1;
		ray.sideDistY = (game->player.y / TILE_SIZE - data.mapY) * ray.deltaDistY;
	}
	else
	{
		ray.stepY = 1;
		ray.sideDistY = (data.mapY + 1.0 - game->player.y / TILE_SIZE) * ray.deltaDistY;
	}
	while (ray.hit == 0)
	{
		if (ray.sideDistX < ray.sideDistY)
		{
			ray.sideDistX += ray.deltaDistX;
			data.mapX += ray.stepX;
			data.side = 0;
		}
		else
		{
			ray.sideDistY += ray.deltaDistY;
			data.mapY += ray.stepY;
			data.side = 1;
		}
		if (map[data.mapY][data.mapX] > 0)
			ray.hit = 1;
	}
	if (data.side == 0)
		data.perpWallDist = (ray.sideDistX - ray.deltaDistX);
	else
		data.perpWallDist = (ray.sideDistY - ray.deltaDistY);

	// Calculate where the wall was hit (0-1)
	if (data.side == 0)
		data.wallX = (game->player.y / TILE_SIZE + data.perpWallDist * ray.rayDY)
			- floor(game->player.y / TILE_SIZE + data.perpWallDist * ray.rayDY);
	else
		data.wallX = (game->player.x / TILE_SIZE + data.perpWallDist * ray.rayDX)
			- floor(game->player.x / TILE_SIZE + data.perpWallDist * ray.rayDX);

	ray.wall_x = data.wallX;
	ray.dist = data.perpWallDist * TILE_SIZE;
	ray.side = data.side;
	ray.wall_type = map[data.mapY][data.mapX];

	return (ray);
}