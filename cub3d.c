#include "cub3d.h"

int main()
{
    int fd;
    // char *map;
    fd = open("map.cub", O_RDONLY);
    // parse_map("map.cub");
    // int i;

    // i = 0;
    // map = read_map(fd);
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
