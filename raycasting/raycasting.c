/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:55:15 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/24 11:08:49 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
};

// ---------- FONCTIONS GRAPHIQUES ----------
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = y * mlx->line_len + x * (mlx->bpp / 8);
	*(unsigned int *)(mlx->addr + pixel) = color;
}

void	draw_tile(t_mlx *mlx, int x, int y, int size, int color)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			my_mlx_pixel_put(mlx, x + i, y + j, color);
}

void	clear_screen(t_mlx *mlx)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(mlx, x, y, 0x000000);
}

// ---------- MAP 2D ----------
void	draw_map2d(t_game *game)
{
	int	color;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			color = game->map.grid[i][j] ? 0x808080 : 0xFFFFFF;
			draw_tile(&game->gfx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE - 1,
				color);
		}
	}
}

// ---------- COLLISIONS ----------
int	is_wall(t_game *game,float x, float y)
{
	int	mx;
	int	my;
	char c;

	mx = (int)(x / TILE_SIZE);
	my = (int)(y / TILE_SIZE);
	if (mx < 0 || mx >= game->map.cols || my < 0 || my >= game->map.rows)
		return (1);
	c = game->map.grid[my][mx];
	return (c != '0');
}

// ---------- LIGNES ----------
void	draw_line_dda(t_mlx *mlx, float x0, float y0, float x1, float y1,
		int color)
{
	float	dx;
	float	dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	if (steps == 0)
		return ;
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = x0;
	y = y0;
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(mlx, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

// ---------- CALCUL DU RAYON ----------
float	cast_ray(t_game *game, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	ray_dx;
	float	ray_dy;

	ray_x = game->player.x;
	ray_y = game->player.y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	while (!is_wall(game,ray_x, ray_y))
	{
		ray_x += ray_dx * 0.1f; // modified here , graphic issues fixed
		ray_y += ray_dy * 0.1f;
	}
	return (sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y,
				2)));
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
//         draw_line_dda(&game->gfx, game->player.x, game->player.y, end_x,end_y, 0x00FF00);
//     }
// }

// ---------- JOUEUR ----------
void	draw_player(t_game *game)
{
	draw_tile(&game->gfx, game->player.x - PLAYER_SIZE / 2, game->player.y
		- PLAYER_SIZE / 2, PLAYER_SIZE, 0xFF0000);
}

// ---------- 3D ----------
void	draw_vertical_line(t_game *game, int x, int wall_top, int wall_bottom,
		int color)
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

void	render_3d(t_game *game)
{
	float	ray_angle;
	float	dist;
	float	corrected_dist;
	float	proj_plane;
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		shade;
	int		color;

	for (int i = 0; i < NUM_RAYS; i++)
	{
		ray_angle = (game->player.angle - (FOV / 2.0f)) + ((float)i / NUM_RAYS)
			* FOV;
		dist = game->ray_distances[i];
		corrected_dist = dist * cos(ray_angle - game->player.angle);
		proj_plane = (WIDTH / 2) / tan(FOV / 2);
		wall_height = (TILE_SIZE / corrected_dist) * proj_plane;
		wall_top = (HEIGHT / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT / 2) + (wall_height / 2);
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom > HEIGHT)
			wall_bottom = HEIGHT;
		shade = 255 - (int)(dist / 3);
		if (shade < 50)
			shade = 50;
		color = (shade << 16) | (shade << 8) | shade;
		draw_vertical_line(game, i, wall_top, wall_bottom, color);
	}
}

// ---------- CLAVIER ----------
int	key_hook(int keycode, void *param)
{
	t_game	*game;
	float	next_x;
	float	next_y;

	game = (t_game *)param;
	next_x = game->player.x;
	next_y = game->player.y;
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
	{
		next_x += game->player.dx;
		next_y += game->player.dy;
	}
	if (keycode == 115)
	{
		next_x -= game->player.dx;
		next_y -= game->player.dy;
	}
	if (keycode == 100)
	{
		next_x += -game->player.dy;
		next_y += game->player.dx;
	}
	if (keycode == 97)
	{
		next_x += game->player.dy;
		next_y += -game->player.dx;
	}
	if (keycode == 65361)
		game->player.angle -= ROT_SPEED;
	if (keycode == 65363)
		game->player.angle += ROT_SPEED;
	game->player.dx = cos(game->player.angle) * SPEED;
	game->player.dy = sin(game->player.angle) * SPEED;
	if (!is_wall(game ,next_x, next_y))
	{
		game->player.x = next_x;
		game->player.y = next_y;
	}
	clear_screen(&game->gfx);
	// draw_map2d(game);
	draw_player(game);
	draw_fov_rays(game);
	// render_3d(game);
	render_3d_textured(game); // CHANGE THIS LINE
	// clear_screen(&game->gfx);
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.img, 0, 0);
	return (0);
}

int rotate_left_right(t_game *game, double rotspeed)
{
	t_player	*p;
	double		tmp_x;

	p = &game->player;
	tmp_x = p->dx;
	p->dx = p->dx * cos(rotspeed) - p->dy * sin(rotspeed);
	p->dy = tmp_x * sin(rotspeed) + p->dy * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

int rotate_player(t_game *game, int rotdir)
{
	int moved;
	double rotspeed;
	
	moved = 0;
	rotspeed = ROT_SPEED * rotdir;
	moved += rotate_left_right(game, rotspeed);
	return (moved);
}

void wrap_mouse_position(int x, int y, t_game *game)
{
	if(x > WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
	if(x < DIST_EDGE_MOUSE_WRAP)
	{
		x = WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
}

int	mouse_motion_handler(int x, int y, t_game *game)
{
	static int old_x;

	old_x = WIDTH / 2;
	wrap_mouse_position(x, y, game);
	if(x == old_x)
		return (0);
	else if(x < old_x)
		game->player.has_moved += rotate_player(game, -1);
	else if(x > old_x)
		game->player.has_moved += rotate_player(game, 1);
	old_x = x;
	return (0);
}

// ---------- FERMETURE ----------
int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	draw_fov_rays(t_game *game)
{
	t_ray		ray;
	t_cast_ray	data;
	int			i;

	data.start_angle = game->player.angle - FOV / 2;
	data.angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray.ray_angle = data.start_angle + i * data.angle_step;
		ray = cast_ray_textured(game, ray.ray_angle);
		game->rays[i] = ray;
		game->ray_distances[i] = ray.dist;
		ray.end_x = game->player.x + cos(ray.ray_angle) * ray.dist;
		ray.end_y = game->player.y + sin(ray.ray_angle) * ray.dist;
		draw_line_dda(&game->gfx, game->player.x, game->player.y, ray.end_x,
			ray.end_y, 0x00FF00);
		i++;
	}
}

int parse_color(char *line, int print_color)
{
    char *copy = strdup(line);
    if (!copy) return 1;

    int values[3];
    int i = 0;
    char *token = strtok(copy, ",");

    while (token && i < 3)
    {
        while (*token == ' ' || *token == '\t')
            token++;
        values[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
    }
    free(copy);

    if (i != 3)
    {
        printf("❌ Erreur : mauvaise syntaxe pour la couleur (%s)\n", line);
        return 1;
    }
    if (values[0] < 0 || values[0] > 255 ||
        values[1] < 0 || values[1] > 255 ||
        values[2] < 0 || values[2] > 255)
    {
        printf("❌ Erreur : valeur RGB hors intervalle (0-255)\n");
        return 1;
    }

    if (print_color)
        printf("✅ Couleur valide : %d,%d,%d\n", values[0], values[1], values[2]);

    return 0;
}

// ------------------- UTILITAIRE -------------------
char *ft_strdup_trim(char *src)
{
    int len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '\n'))
        src[--len] = '\0';
    while (*src == ' ' || *src == '\t')
        src++;
    return strdup(src);
}

int is_map_line(char *line)
{
    int i = 0;

    // Skip leading spaces and tabs
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    // Now check characters
    while (line[i])
    {
        if (line[i] != '0'
            && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != ' ' && line[i] != '\t'
            && line[i] != '\n')
            return (0); // found something not allowed in map
        i++;
    }
    return (1); // valid map line
}

void check_path(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("❌ Erreur : le fichier %s n'existe pas ou ne peut pas être ouvert\n", path);
        exit(1);
    }
    close(fd);
    printf("✅ Texture trouvée : %s\n", path);
}

void check_texture_line(t_textures *tex, char *line)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    if (strncmp(line + i, "NO ", 3) == 0)
        tex->NO = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "SO ", 3) == 0)
        tex->SO = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "EA ", 3) == 0)
        tex->EA = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "WE ", 3) == 0)
        tex->WE = ft_strdup_trim(line + i + 3);
    
}

void print_error()
{
	printf("errooooor\n");
	exit(EXIT_FAILURE);
}
// ---------- MAIN ----------

int	main(int ac, char **av)
{
	t_game	game;
    t_map map;

    if (ac != 2)
		print_error();
	if (ft_strncmp(av[1] + (ft_strlen(av[1] - 4)), ".cub", 4))
		print_error();
    int fd = open("map.cub", O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur ouverture fichier");
        return 1;
    }

    t_textures tex = {0};
    char *line;
    int error = 0;

    map = init_map();
    while ((line = get_next_line(fd)))
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;

        // ligne vide => skip
        if (line[i] == '\0' || line[i] == '\n')
        {
            free(line);
            continue;
        }

        // parse couleur
        if (line[i] == 'F' || line[i] == 'C')
        {
            if (parse_color(line + i + 1, 1))
                error = 1;
        }
        //parse texture
        else if ((line[i] == 'N' && line[i + 1] == 'O') || 
                (line[i] == 'S' && line[i + 1] == 'O') ||
                (line[i] == 'W' && line[i + 1] == 'E') ||
                (line[i] == 'E' && line[i + 1] == 'A'))
        {
            check_texture_line(&tex, line);
        }
        //  else if(is_map_line(line))
        //     {
        //         printf("here map\n");
        //         map->grid = get_map(line, fd);
        //         break;
        //     }
        // map détectée : ligne commence par '1'
        else if (line[i] == '1')
        {
            map.grid = get_map(line, fd);
            break; // on sort, map est lue par get_map
        }
        else
        {
            printf("❌ Ligne invalide détectée : %s\n", line);
            error = 1;
        }
        free(line);
}

    close(fd);
    // int max_len = find_big_line(map);
    // map = square_map(map, max_len);

    // Debug print
    trim_newline(map.grid);
    map.cols = find_big_line(map.grid);
    map.grid = square_map(map.grid, map.cols);
    while (map.grid[map.rows])
        map.rows++;

    // Debug print
    for (int i = 0; map.grid[i]; i++)
    {
        printf("[%s], len: %d\n", map.grid[i], (int)ft_strlen(map.grid[i]));
    }

    valid_map(map);
    // Vérification des textures
    if (tex.NO) check_path(tex.NO); else { printf("❌ Texture NO manquante\n"); error = 1; }
    if (tex.SO) check_path(tex.SO); else { printf("❌ Texture SO manquante\n"); error = 1; }
    if (tex.EA) check_path(tex.EA); else { printf("❌ Texture EA manquante\n"); error = 1; }
    if (tex.WE) check_path(tex.WE); else { printf("❌ Texture WE manquante\n"); error = 1; }

    // Libération mémoire
    free(tex.NO);
    free(tex.SO);
    free(tex.EA);
    free(tex.WE);
    free(tex.S);

    if (error)
	{
        printf("\n❌ La map contient des erreurs.\n");
		return error;
	}
    else
	{
        printf("\n✅ Map valide, toutes les textures et couleurs sont correctes.\n");
	}
	// Init window and image
	
	game.gfx.mlx = mlx_init();
	game.gfx.win = mlx_new_window(game.gfx.mlx, WIDTH, HEIGHT, "Cub3D");
	game.gfx.img = mlx_new_image(game.gfx.mlx, WIDTH, HEIGHT);
	game.gfx.addr = mlx_get_data_addr(game.gfx.img, &game.gfx.bpp,
			&game.gfx.line_len, &game.gfx.endian);
	game.map = map;
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
	mlx_hook(game.gfx.win, 6, 1L << 6, mouse_motion_handler, &game);
	mlx_hook(game.gfx.win, 17, 0, close_window, NULL);
	mlx_loop(game.gfx.mlx);
    free(map.grid);
	return (0);
}
