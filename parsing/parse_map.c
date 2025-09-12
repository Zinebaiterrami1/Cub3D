/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/12 10:48:48 by zait-err         ###   ########.fr       */
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

int get_first_line_map(const char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(line[i] != '1' && line[i] != '0' &&
            line[i] != ' ' && line[i] != '\t' &&
            line[i] != 'S' && line[i] != 'E' &&
            line[i] != 'N' && line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}

int count_line_map(int fd)
{
    int count;
    char *line;
    
    count = 0;
    if(fd < 0)
        return (printf("Error, Invalid file!\n"), 0);
    line = get_next_line(fd);
    while(line && !get_first_line_map(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    while(line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    return (count);
}

char    **read_map()
{
    char    **map;
    int     count_lines;
    char    *line;
    int     fd;
    int     i;

    fd = open("map.cub", O_RDONLY);
    count_lines = count_line_map(fd);
    close(fd);

    map = malloc(sizeof(char *) * (count_lines + 1));
    if (!map)
        return NULL;

    fd = open("map.cub", O_RDONLY);
    i = 0;
    // Skip config lines
    line = get_next_line(fd);
    while (line && !get_first_line_map(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    // Now line is the first map line
    while (line)
    {
        map[i++] = line;
        printf("line %s", line);
        line = get_next_line(fd);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}


// char *read_map(int fd)
// {
//     char *tmp;
//     char *old_str;
//     char *new_str;
//     // int i = 0;
    
//     tmp = get_next_line(fd);
//     // new_str = malloc(1);
//     // if(!new_str)
//     //     return(NULL);
//     // new_str[0] = '\0';
//     // printf("First map line: %s", tmp);
//     while(tmp && !get_first_line_map(tmp))
//     {
//         // printf("First map line: %s", tmp);
//         // printf("TMP: %s", tmp);
//         free(tmp);
//         tmp = get_next_line(fd);
//     }
//     // printf("TMP: %s", tmp); // See what get_next_line returns
//     while(tmp)
//     {
//         old_str = new_str;
//         printf("Appending line: %s", tmp);
//         new_str = ft_strjoin(old_str, tmp);
//         free(old_str);
//         free(tmp);
//         tmp = get_next_line(fd);
//     }
//     // printf("%s", new_str);
//     // while(new_str[i])
//     // {
//     //     printf("%c", new_str[i]);
//     //     i++;
//     // }
//     return (new_str);
// }
