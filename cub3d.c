#include "cub3d.h"


int main()
{
    int fd;
    char **map;
    fd = open("map.cub", O_RDONLY);
    // parse_map("map.cub");
    // int i;

    // i = 0;
    map = read_map();
    printf("%s", map[10]);
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