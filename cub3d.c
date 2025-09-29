/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:49:39 by zait-err          #+#    #+#             */
/*   Updated: 2025/09/29 10:46:02 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

char **init_map()
{
    int fd;
    fd = open("map.cub", O_RDONLY);
  


    char *raw_map;
    char **map;

    raw_map = read_map(fd);      // big string: "1111\n1001\n1111\n"
    map = ft_split(raw_map, '\n');  // split into array of lines
    free(raw_map);

    // Test
    for (int i = 0; map[i]; i++)
        printf("line[%d] = %s\n", i, map[i]);

    //     char *a = "111\n";
    // char *b = "000\n";
    // char *c = ft_strjoin(a, b);
    // printf("\nRESULT: %s", c);

    // printf("%s", map[4]);
    // while(i < count_line_map(fd))
    // {
    //     printf("%s", map[i]);
    //     i++;
    // }
}
>>>>>>> main
