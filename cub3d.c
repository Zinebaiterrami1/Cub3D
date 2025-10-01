/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/01 15:23:12 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

t_map init_map()
{
    t_map map;

    map.grid = NULL;
    map.cols = 0;
    map.rows = 0;
    map.player.x = 0;
    map.player.y = 0;
    map.player.dir_x = 0;
    map.player.dir_y = -1;
    map.player.plane_x = 0;
    map.player.plane_y = 0.66;
    return (map);
}

