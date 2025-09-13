#include "cub3d.h"
int main()
{
    int fd = open("map.cub", O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur ouverture fichier");
        return 1;
    }

    t_textures tex = {0};
    char *line;
    int error = 0;

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
        else
        {
            check_texture_line(&tex, line);
        }

        free(line);
    }
    close(fd);

    if (tex.NO) check_path(tex.NO); else { printf("❌ Texture NO manquante\n"); error = 1; }
    if (tex.SO) check_path(tex.SO); else { printf("❌ Texture SO manquante\n"); error = 1; }
    if (tex.EA) check_path(tex.EA); else { printf("❌ Texture EA manquante\n"); error = 1; }
    if (tex.WE) check_path(tex.WE); else { printf("❌ Texture WE manquante\n"); error = 1; }

    free(tex.NO);
    free(tex.SO);
    free(tex.EA);
    free(tex.WE);

    if (error)
        printf("\n❌ La map contient des erreurs.\n");
    else
        printf("\n✅ Map valide, toutes les textures et couleurs sont correctes.\n");

    return error;
}
