/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:05:14 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/30 11:27:04 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	extra_number(const char *a, int i, int num)
{
	while (a[i])
	{
		if (a[i] == 32 || (a[i] >= 9 && a[i] <= 13))
			i++;
		else
			return (1);
	}
	return (num);
}

void	wrap_mouse_position(int x, int y, t_game *game)
{
	if (x > WIDTH - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = WIDTH - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(game->gfx.mlx, game->gfx.win, x, y);
	}
}

int	rotate_left_right(t_game *game, double rotspeed)
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

int	rotate_player(t_game *game, int rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROT_SPEED * rotdir;
	moved += rotate_left_right(game, rotspeed);
	return (moved);
}
