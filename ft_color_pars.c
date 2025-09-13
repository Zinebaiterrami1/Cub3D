#include "cub3d.h"
char *ft_strdup_trim(char *src)
{
    int len = strlen(src);
    while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '\n' || src[len - 1] == '\t'))
        src[--len] = '\0';
    while (*src == ' ' || *src == '\t')
        src++;
    return strdup(src);
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

int is_number(char *s)
{
    if (!s || !*s)
        return 0;
    for (int i = 0; s[i]; i++)
        if (s[i] < '0' || s[i] > '9')
            return 0;
    return 1;
}




int count_commas(char *line)
{
    int count = 0;
    for (int i = 0; line[i]; i++)
        if (line[i] == ',')
            count++;
    return count;
}

int parse_color(char *line, int print_color)
{
    char **parts = ft_split(line, ',');
    if (!parts)
        return 1;

    int values[3];
    int i = 0;
    if (count_commas(line) != 2)
    {
        printf("❌ Erreur : nombre incorrect de virgules dans la couleur (%s)\n", line);
        return 1;
    }
    while (parts[i] && i < 3)
    {
        char *tmp = ft_strdup_trim(parts[i]);

        if (*tmp == '\0')
        {
            printf("❌ Erreur : valeur manquante dans la couleur (%s)\n", line);
            for (int j = 0; parts[j]; j++) free(parts[j]);
            free(parts);
            return 1;
        }

        if (!is_number(tmp))
        {
            printf("❌ Erreur : valeur non numérique dans la couleur (%s)\n", line);
            for (int j = 0; parts[j]; j++) free(parts[j]);
            free(parts);
            return 1;
        }

        values[i] = atoi(tmp);
        i++;
    }

     if (i != 3)
    {
        printf("❌ Erreur : nombre incorrect de valeurs dans la couleur (%s)\n", line);
        int j = 0;
        while( parts[j]) 
        {
            free(parts[j]);
            j++;
        }
        free(parts[j]);
        return 1;
    }
    int j = 0;
    while(j < 3)
    {
        free(parts[j]);
        j++;
    }
    free(parts);
    j = 0;
    while(j < 3)
    {
         if (values[j] < 0 || values[j] > 255)
        {
            printf("❌ Erreur : valeur RGB hors intervalle (0-255) (%s)\n", line);
            return 1;
        }
        j++;
    }
    if (print_color)
        printf("✅ Couleur valide : %d,%d,%d\n", values[0], values[1], values[2]);

    return 0;
}