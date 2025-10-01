/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/01 15:09:05 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

t_map *init_map()
{
    t_map *map;

    map =  malloc(sizeof(t_map));
    if(!map)
        return (NULL);
    map->grid = NULL;
    map->cols = 0;
    map->rows = 0;
    map->player.x = 0;
    map->player.y = 0;
    map->player.dx = 0;
    map->player.dy = -1;
    map->player.angle = 1.5 * 3.14; // facing up
    return (map);
}

