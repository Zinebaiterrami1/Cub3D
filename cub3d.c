#include "cub3d.h"


int main()
{
    int fd;
    char **map;
    fd = open("map.cub", O_RDONLY);
    // parse_map("map.cub");
    // int i;

    // i = 0;
    map = read_map(fd);
    // printf("%s", map[4]);
    // while(i < count_line_map(fd))
    // {
    //     printf("%s", map[i]);
    //     i++;
    // }
}