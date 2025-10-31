/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:46:21 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/31 15:52:04 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	global_color(char *line, t_game *game)
{
	if (line[0] == 'F')
		parse_color(line + 1, &game->floor_color);
	else if (line[0] == 'C')
		parse_color(line + 1, &game->ceiling_color);
	else
		return (1);
	return (0);
}

void	init_player(t_player *player, t_player map_player)
{
	player->x = (map_player.y + 0.5) * TILE_SIZE;
	player->y = (map_player.x + 0.5) * TILE_SIZE;
	player->angle = map_player.angle;
	player->dx = cos(player->angle) * SPEED;
	player->dy = sin(player->angle) * SPEED;
}

void	parse_args(int ac, char **av)
{
	if (ac != 2)
		print_error();
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		print_error();
}

int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur ouverture fichier");
		exit(1);
	}
	return (fd);
}

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}
