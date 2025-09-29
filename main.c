#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line/get_next_line.h"
#include "cub3d.h"

typedef struct s_textures {
    char *NO;
    char *SO;
    char *EA;
    char *WE;
    char *S;
} t_textures;

// ------------------- UTILITAIRE -------------------
char *ft_strdup_trim(char *src)
{
    int len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '\n'))
        src[--len] = '\0';
    while (*src == ' ' || *src == '\t')
        src++;
    return strdup(src);
}

int is_map_line(char *line)
{
    int i = 0;

    // Skip leading spaces and tabs
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    // Now check characters
    while (line[i])
    {
        if (line[i] != '0'
            && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != ' ' && line[i] != '\t'
            && line[i] != '\n')
            return (0); // found something not allowed in map
        i++;
    }
    return (1); // valid map line
}

void check_path(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("❌ Erreur : le fichier %s n'existe pas ou ne peut pas être ouvert\n", path);
        exit(1);
    }
    close(fd);
    printf("✅ Texture trouvée : %s\n", path);
}

void check_texture_line(t_textures *tex, char *line)
{
    int i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    if (strncmp(line + i, "NO ", 3) == 0)
        tex->NO = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "SO ", 3) == 0)
        tex->SO = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "EA ", 3) == 0)
        tex->EA = ft_strdup_trim(line + i + 3);
    else if (strncmp(line + i, "WE ", 3) == 0)
        tex->WE = ft_strdup_trim(line + i + 3);
    
}

// ------------------- PARSING COULEURS -------------------
int parse_color(char *line, int print_color)
{
    char *copy = strdup(line);
    if (!copy) return 1;

    int values[3];
    int i = 0;
    char *token = strtok(copy, ",");

    while (token && i < 3)
    {
        while (*token == ' ' || *token == '\t')
            token++;
        values[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
    }
    free(copy);

    if (i != 3)
    {
        printf("❌ Erreur : mauvaise syntaxe pour la couleur (%s)\n", line);
        return 1;
    }
    if (values[0] < 0 || values[0] > 255 ||
        values[1] < 0 || values[1] > 255 ||
        values[2] < 0 || values[2] > 255)
    {
        printf("❌ Erreur : valeur RGB hors intervalle (0-255)\n");
        return 1;
    }

    if (print_color)
        printf("✅ Couleur valide : %d,%d,%d\n", values[0], values[1], values[2]);

    return 0;
}

// ------------------- MAIN -------------------
int main()
{
    t_map *map;

    int fd = open("map.cub", O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur ouverture fichier");
        return 1;
    }

    t_textures tex = {0};
    char *line;
    int error = 0;

    map = init_map();
    while ((line = get_next_line(fd)))
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;

        if (line[i] == 'F' || line[i] == 'C')
        {
            if (parse_color(line + i + 1, 1))
                error = 1;
        }
        else if ((line[i] == 'N' && line[i + 1] == 'O') || 
                 (line[i] == 'S' && line[i + 1] == 'O') ||
                 (line[i] == 'W' && line[i + 1] == 'E') ||
                 (line[i] == 'E' && line[i + 1] == 'A'))
        {
            check_texture_line(&tex, line);
        }
        else if(is_map_line(line))
        {
            map->grid = get_map(line, fd);
        }
        else
        {
            printf("❌ Aucune map détectée.\n");
            return 1;
        }
        free(line);
    }
    close(fd);
    // int max_len = find_big_line(map);
    // map = square_map(map, max_len);

    // Debug print
    trim_newline(map->grid);
    map->cols = find_big_line(map->grid);
    map->grid = square_map(map->grid, map->cols);
    while (map->grid[map->rows])
        map->rows++;

    // Debug print
    for (int i = 0; map->grid[i]; i++)
    {
        printf("[%s], len: %d\n", map->grid[i], (int)ft_strlen(map->grid[i]));
    }

    valid_map(map);
    // Vérification des textures
    if (tex.NO) check_path(tex.NO); else { printf("❌ Texture NO manquante\n"); error = 1; }
    if (tex.SO) check_path(tex.SO); else { printf("❌ Texture SO manquante\n"); error = 1; }
    if (tex.EA) check_path(tex.EA); else { printf("❌ Texture EA manquante\n"); error = 1; }
    if (tex.WE) check_path(tex.WE); else { printf("❌ Texture WE manquante\n"); error = 1; }

    // Libération mémoire
    free(tex.NO);
    free(tex.SO);
    free(tex.EA);
    free(tex.WE);
    free(tex.S);

    if (error)
        printf("\n❌ La map contient des erreurs.\n");
    else
        printf("\n✅ Map valide, toutes les textures et couleurs sont correctes.\n");
    // int k;
    // k = 0;
    // while(map[k])
    // {
    //     printf("%s\n", map[k]);
    //     k++;
    // }
    return error;
}
