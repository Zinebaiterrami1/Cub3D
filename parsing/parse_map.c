/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/31 14:15:36 by fakoukou         ###   ########.fr       */
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
    if(!map)
        return (-1);
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
    int i;
    char *new_line;
    int len_line;

    i = 0;
    while (map[i])
    {
        len_line = (int)ft_strlen(map[i]);
        if(len_line < max_len)
        {
            new_line = malloc(max_len + 1);
            if(!new_line)
                return (NULL);
            ft_memcpy(new_line, map[i], len_line);
            while(len_line < max_len)
                new_line[len_line++] = '\0';
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

int check_top_border(t_map map)
{
    int y = 0;
    while (y < map.cols && map.grid[0][y] != '\0')
    {
        if (map.grid[0][y] != '1' && map.grid[0][y] != ' ' && map.grid[0][y] != '\t')
        {
            printf("Invalid map: Top border must be only '1', ' ' or '\\t'\n");
            return (0);
        }
        y++;
    }
    return (1);
}

int check_bottom_border(t_map map)
{
    int y = 0;

    while (y < map.cols && map.grid[map.rows - 1][y] != '\0')
    {
        if (map.grid[map.rows - 1][y] != '1' && map.grid[map.rows - 1][y] != ' ' && map.grid[map.rows - 1][y] != '\t')
        {
            printf("%c(%d, %d)\n", map.grid[map.rows - 1][y], map.rows - 1, y);
            printf("Invalid map: Bottom border must be only '1', ' ' or '\\t'\n");
            return (0);
        }
        y++;
    }
    return (1);
}

int check_left_right_border(t_map map)
{
    int x;

    x = 0;
    while(x < map.rows)
    {
        if(map.grid[x][0] == '0')
        {
            printf("Invalid map\nOpen At left border\n");
            return (0);
        }
        if(map.grid[x][map.cols - 1] == '0')
        {
            printf("Invalid map\nOpen at right border\n");
            return (0);
        }
        x++;
    }//TODO: not fixed if 1 is on the left right border
    x = 0;
    while(x < map.rows)
    {
        if(map.grid[x][0] == '1' && map.grid[x][map.cols - 1] == '1')
            printf("dsfsfd");
        return (1);
        x++;
    }
    return (0);
}

int check_inside(t_map map)
{
    int x;
    int y;

    x = 1;
    y = 1;
    while(x < map.rows - 1)
    {
        y = 1;
        while(y < map.cols - 1)
        {
            if(map.grid[x][y] == '0')
            {
                if(map.grid[x - 1][y] == ' ' || map.grid[x + 1][y] == ' ' ||
                    map.grid[x][y - 1] == ' ' || map.grid[x][y + 1] == ' ' ||
                    map.grid[x][y + 1] == '\0')
                {
                    return (printf("Invalid map\n '0' next to space or \\0 \n"), 0);
                }
            }
            y++;
        }
        x++;
    }
    return (1);
}

void set_player_dir(t_player *p, char c)
{
    if (c == 'N')  // North - facing up (negative Y in screen coords)
    {
        p->dx = 0;
        p->dy = -1;
        p->angle = 3 * M_PI / 2;  // 270 degrees
    }
    else if (c == 'S')  // South - facing down (positive Y)
    {
        p->dx = 0;
        p->dy = 1;
        p->angle = M_PI / 2;      // 90 degrees
    }
    else if (c == 'E')  // East - facing right (positive X)
    {
        p->dx = 1;
        p->dy = 0;
        p->angle = 0;             // 0 degrees
    }
    else if (c == 'W')  // West - facing left (negative X)
    {
        p->dx = -1;
        p->dy = 0;
        p->angle = M_PI;          // 180 degrees
    }
}
int check_player_pos(t_map *map)
{
    int count_pos;
    int x;
    int y;

    count_pos = 0;
    x = 1;
    y = 1;

    while(x < map->rows - 1)
    {
        y = 1;
        while(y < (int)ft_strlen(map->grid[x]) - 1)
        {
            if(map->grid[x][y] == 'N' || map->grid[x][y] == 'S' ||
                map->grid[x][y] == 'E' || map->grid[x][y] == 'W')
                {
                    map->player.x = x;
                    map->player.y = y;
                    set_player_dir(&map->player, map->grid[x][y]);
                    map->grid[x][y] = '0';
                    count_pos++;
                }
                y++;
            }
            x++;
    }
    // printf("Found player at grid[%d][%d] -> x: %f, y: %f\n", 
        //    x, y, map->player.x, map->player.y);
    if(count_pos != 1)
    {
        return (printf("Invalid map\nmust be only one player position\n"), 0);
    }
    return (1);
}

int check_inside_2(t_map map)
{
    int x;
    int y;
    char c;
    x = 0;
    y = 0;
    while(x < map.rows && map.grid[x][y] != '\0')
    {
        y = 0;
        while(y < map.cols && map.grid[x][y] != '\0')
        {
            c = map.grid[x][y];
            if(c != 'N' && c != 'S' &&
                c != 'E' && c != 'W' &&
                c != '1' && c != '0' &&
                c != ' ' && c != '\t' && c == '\0')
            {
                printf("Invalid map\nWrong character %c at (%d, %d)\n", c , x, y);
                printf("line %s\n", map.grid[x]);
                return (0);
            }
            y++;
        }
        x++;
    }
    return (1);
}

int check_space_map(t_map map)
{
    int x;
    int y;
    
    x = 1;
    y = 1;
    while(x < map.rows - 1)
    {
        y = 1;
        while(y < map.cols - 1)
        {
            if(map.grid[x][y] == ' ')
            {
                if(map.grid[x - 1][y] != '1' && map.grid[x + 1][y] != '1' &&
                    map.grid[x][y - 1] != '1' && map.grid[x][y + 1] != '1')
                {
                    printf("Invalid map\nSpace must be surrounded by '1'\n");
                    return (0);
                }
            }
            y++;
        }
        x++;
    }
    return (1);
}

void valid_map(t_map *map)
{
    if (!check_top_border(*map))  return;
    if (!check_bottom_border(*map)) return;
    if (!check_left_right_border(*map)) return;
    if (!check_inside(*map))    return;
    if (!check_inside_2(*map))  return;
    if (!check_player_pos(map))    return;
    if (!check_space_map(*map)) return;
}

void print_valid()
{
    printf("\nValid map✅✅\n");
}
