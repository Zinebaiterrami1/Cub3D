/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/15 19:20:23 by zait-err         ###   ########.fr       */
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
    int i = 0;

    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' &&
            line[i] != ' ' && line[i] != '\t' &&
            line[i] != 'N' && line[i] != 'S' &&
            line[i] != 'E' && line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}


/*int count_line_map(int fd)
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
}*/


char *read_map(int fd)
{
    char *tmp;
    char *old_str;
    char *new_str;
    // int i = 0;
    
    tmp = get_next_line(fd);
    new_str = malloc(1);
    if(!new_str)
        return(NULL);
    new_str[0] = '\0';
    // printf("First map line: %s", tmp);
    while(tmp && !get_first_line_map(tmp))
    {
        // printf("First map line: %s", tmp);
        // printf("TMP: %s", tmp);
        free(tmp);
        tmp = get_next_line(fd);
    }
    printf("TMP: %s\n", tmp); // See what get_next_line returns
    while(tmp)
    {
        old_str = new_str;
        // printf("Appending line: %s", tmp);
        new_str = ft_strjoinn(old_str, tmp);
        free(old_str);
        free(tmp);
        tmp = get_next_line(fd);
    }
    // printf("%s", new_str);
    // while(new_str[i])
    // {
    //     printf("%c", new_str[i]);
    //     i++;
    // }
    return (new_str);
}

static char **fill_lines(char **map, char *line, int count)
{
    int i;
    char **full_map;

    full_map = malloc(sizeof(char *) * (count + 2));
    if(!full_map)
        return (NULL);
    i = 0;
    while(i < count)
    {
        full_map[i] = map[i]; //copy old lines
        i++;
    }
    full_map[i] = ft_strdup(line);
    if(!full_map)
        return (NULL);
    full_map[i+1] = NULL;
    free(map);
    return (full_map);
}

char **get_map(char *line, int fd)
{
    int count;
    char **map;

    count = 0;
    map = NULL;
    map = fill_lines(map, line, count++);
    if(!map)
        return (NULL);
    line = get_next_line(fd);
    while(line)
    {
        map = fill_lines(map, line, count++);
        if(!map)
            return (NULL);
        line = get_next_line(fd);
    }
    return (map);
}

int find_big_line(char **map)
{
    int i;
    int count;
    int big;
 
    count = 0;
    i = 0;
    big = 0;
    while(map[i])
    {
        count = ft_strlen(map[i]);
        if(big < count)
        {
            big = count;
        }
        i++;
    }
    return (big);
}


char  **square_map(char **map, int max_len)
{
    //hna khasni nchof ila kant map deja square 
    //ghatkon return map nit
    //else khas loopi 3la kola line w nzid fih \0 
    //hta ywli line, bhallo bhal atwaal line f map
    //hka ghaywli 3ndi square w nbda n parsi fih
    int i;
    char *new_line;
    int len_line;
    printf("\nhna wst fct %s", map[0]);
    i = 0;
    while (map[i])
    {
        printf("\nmap 0: \n%s, i: %d\n", map[i], i);
        len_line = (int)ft_strlen(map[i]);
        if(len_line < max_len)
        {
            new_line = malloc(max_len + 1);
            if(!new_line)
                return (NULL);
            ft_memcpy(new_line, map[i], len_line + 1);
            while(len_line < max_len)
                new_line[len_line++] = ' ';
            new_line[max_len] = '\0';
            free(map[i]);
            map[i] = new_line;
        }
        i++;
    }
    return (map);
}

void trim_newline(char **map)
{
    int i;
    int len;

    i = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > 0 && map[i][len - 1] == '\n')
            map[i][len - 1] = '\0';
        i++;
    }
}

// char **valid_map(char **full_map)
// {
//     int x;
//     int y;

//     x = 0;
//     y = 0;

    
// }