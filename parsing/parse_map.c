/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:27 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/29 22:40:00 by zait-err         ###   ########.fr       */
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

// void valid_map(char **full_map)
// {
//     int rows;
//     int cols;
//     int x;
//     int y;

//     x = 0;
//     y = 0;
//     rows = 0;
//     cols = find_big_line(full_map);

//     while(full_map[rows])
//         rows++;
//     //check the top row
//     while(y < cols)
//     {
//         if(full_map[0][y] == '0')
//         {
//             printf("Invalid map\nOpen At top border\n");
//             return ;
//         }
//         y++;
//     }
//     //check bottom row
//     y = 0;
//     while(y < cols)
//     {
//         if(full_map[rows - 1][y] == '0')
//         {
//             printf("Invalid map\nOpen At bottom border\n");
//             return;
//         }
//         y++;
//     }
//     //check left and right borders
//     while(x < rows)
//     {
//         if(full_map[x][0] == '0')
//         {
//             printf("Invalid map\nOpen At left border\n");
//             return;
//         }
//         if(full_map[x][cols - 1] == '0')
//         {
//             printf("Invalid map\nOpen At right border\n");
//             return ;
//         }
//         x++;
//     }
//     x = 0;
//     y = 0;
//     printf("am here \n");
//     while(y < cols)
//     {   
//         x = 0;
//        while(x < rows)
//        {
//             if(full_map[x][y] == '0' && (full_map[x+1][y+1] == '\0' || full_map[x+1][y+1] == ' '))
//             {
//                 printf("Invalid map\nSpace or Null next to '0'\n");
//                 return ;
//             }
//             x++;
//        }
//        y++;
//     }
//     x = 0;
//     y = 0;
//     //check that map surrounded by 1
//     while(y < cols)
//     {
//         if(full_map[0][y] == '1')
//         {
//             printf("top only 1\n");
//             return ;
//         }
//         y++;
//     }
//     //check left and right borders
//     while(x < rows)
//     {
//         if(full_map[x][0] != '1')
//         {
//             printf("Invalid map\nOpen At left border\n");
//             return;
//         }
//         if(full_map[x][cols - 1] != '1')
//         {
//             printf("Invalid map\nOpen At right border\n");
//             return ;
//         }
//         if(full_map[x][rows] == 1)
//         {
//             printf("only 1\ngood\n");
//             return;
//         }
//         x++;
//     }
//     //check pos
//     y = 0;
//     x = 0;
//     while(y < cols)
//     {
//         x = 0;
//         while(x < rows)
//         {
//             if(full_map[x][y] == 'N' || full_map[x][y] == 'S' || full_map[x][y] == 'E' || full_map[x][y] == 'W')
//             {
//                 printf("player pos\n");
//                 return ;
//             }
//             else
//                 printf("must be only N S W E, and not duplicated\n");
//             x++;
//         }
//         y++;
//     }
//     //check about space also
//     y = 0;
//     x = 0;
//     //space inside the map must be surrounded by 11111
//     while(y < cols)
//     {
//         x = 0;
//         while(x < rows)
//         {
//             if(full_map[x][y] == ' ')
//             {
//                 x ++;
//                 if(full_map[x][y] == '0' || full_map[x][y] == '1')
//                 {
//                     if(full_map[x][rows - 1] == '1' && full_map[x][rows + 1] == '1')
//                     {
//                         printf("space surrounded by 1\n");
//                         return ;
//                     }
//                 }
//                 else
//                     printf("error\n");
//             }
//             x++;
//         }
//         y++;
//     }
//     print_valid();
// }


int check_top_border(t_map *map)
{
    int y = 0;
    while (y < map->cols && map->grid[0][y] != '\0')
    {
        if (map->grid[0][y] != '1' && map->grid[0][y] != ' ' && map->grid[0][y] != '\t')
        {
            printf("Invalid map: Top border must be only '1', ' ' or '\\t'\n");
            return (0);
        }
        y++;
    }
    return (1);
}

int check_bottom_border(t_map *map)
{
    int y = 0;

    while (y < map->cols && map->grid[map->rows - 1][y] != '\0')
    {
        if (map->grid[map->rows - 1][y] != '1' && map->grid[map->rows - 1][y] != ' ' && map->grid[map->rows - 1][y] != '\t')
        {
            printf("%c(%d, %d)\n", map->grid[map->rows - 1][y], map->rows - 1, y);
            printf("Invalid map: Bottom border must be only '1', ' ' or '\\t'\n");
            return (0);
        }
        y++;
    }
    return (1);
}

int check_left_right_border(t_map *map)
{
    int x;

    x = 0;
    while(x < map->rows)
    {
        if(map->grid[x][0] == '0')
        {
            printf("Invalid map\nOpen At left border\n");
            return (0);
        }
        if(map->grid[x][map->cols - 1] == '0')
        {
            printf("Invalid map\nOpen at right border\n");
            return (0);
        }
        x++;
    }
    x = 0;
    while(x < map->rows)
    {
        if(map->grid[x][0] == '1' && map->grid[x][map->cols - 1] == '1')
            printf("dsfsfd");
        return (1);
        x++;
    }
    return (0);
}

int check_inside(t_map *map)
{
    int x;
    int y;

    x = 1;
    y = 1;
    printf("sjfkhsdjkfhjdshfjdshfj");
    while(x < map->rows - 1)
    {
        y = 1;
        while(y < map->cols - 1)
        {
            if(map->grid[x][y] == '0')
            {
                if(map->grid[x - 1][y] == ' ' || map->grid[x + 1][y] == ' ' ||
                    map->grid[x][y - 1] == ' ' || map->grid[x][y + 1] == ' ' ||
                    map->grid[x][y + 1] == '\0')
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
                    count_pos++;
            y++;
        }
        x++;
    }
    if(count_pos != 1)
    {
        return (printf("Invalid map\nmust be only one player position\n"), 0);
    }
    return (1);
}

int check_inside_2(t_map *map)
{
    int x;
    int y;
    char c;
    x = 0;
    y = 0;
    while(x < map->rows && map->grid[x][y] != '\0')
    {
        y = 0;
        while(y < map->cols && map->grid[x][y] != '\0')
        {
            c = map->grid[x][y];
            if(c != 'N' && c != 'S' &&
                c != 'E' && c != 'W' &&
                c != '1' && c != '0' &&
                c != ' ' && c != '\t' && c == '\0')
            {
                printf("Invalid map\nWrong character %c at (%d, %d)\n", c , x, y);
                printf("line %s\n", map->grid[x]);
                return (0);
            }
            y++;
        }
        x++;
    }
    return (1);
}

int check_space_map(t_map *map)
{
    int x;
    int y;
    
    x = 1;
    y = 1;
    while(x < map->rows - 1)
    {
        y = 1;
        while(y < map->cols - 1)
        {
            if(map->grid[x][y] == ' ')
            {
                if(map->grid[x - 1][y] != '1' && map->grid[x + 1][y] != '1' &&
                    map->grid[x][y - 1] != '1' && map->grid[x][y + 1] != '1')
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
    if (!check_top_border(map))  return;
    if (!check_bottom_border(map)) return;
    if (!check_left_right_border(map)) return;
    if (!check_inside(map))    return;
    if (!check_inside_2(map))  return;
    if (!check_player_pos(map))    return;
    if (!check_space_map(map)) return;
    printf("✅ Map is valid!\n");
}

void print_valid()
{
    printf("\nValid map✅✅\n");
}
