/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/11 13:31:21 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int parse_map(char *file_name)
{
    int fd;
    char *line;

    fd = open(file_name, O_RDONLY);
    if(fd < 0)
        return (printf("Error, Invalid file!\n"), 0);
    while(((line = get_next_line(fd))))
    {
        printf("%s", line);
    }
    close(fd);
    return (1);
}

int count_line_map(int fd)
{
    int count;
    char *line;
    
    count = 0;
    if(fd < 0)
        return (printf("Error, Invalid file!\n"), 0);
    while((line = get_next_line(fd)))
    {
        count++;
    }
    return (count);
}

char    **read_map()
{
    char    **map;
    int     count_lines;
    char    *line;
    int fd = open("map.cub", O_RDONLY);
    count_lines = count_line_map(fd);
    map = malloc(sizeof(char *) * (count_lines + 1));
    count_lines = 0;
    while((line = get_next_line(fd)))
    {
        map[count_lines++] = line;
        printf("line %s", line);
        // free(line);
    }
    map[count_lines] = NULL;
    close(fd);
    return (map);
}