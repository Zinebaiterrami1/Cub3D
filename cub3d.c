/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/29 15:20:33 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

t_map *init_map(char *line, int fd)
{
    int i;
    t_map *map;

    i = 0;
    map =  malloc(sizeof(t_map));
    if(!map)
        return (NULL);
    map->grid = get_map(line, fd);
    map->cols = find_big_line(map->grid);
    map->rows = 0;
    while(map->grid[map->rows])
        map->rows++;
    map->player.x = 0;
    map->player.y = 0;
    map->player.dir = 0;
    map->player.dir_x = 0;
    map->player.dir_y = -1;
    map->player.plane_x = 0;
    map->player.plane_y = 0.66;
    return (map);
}

