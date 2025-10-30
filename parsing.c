/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:19:12 by fakoukou          #+#    #+#             */
/*   Updated: 2025/10/30 12:55:46 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_line(t_textures *tex, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		tex->NO = ft_strdup_trim(line + i + 3);
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		tex->SO = ft_strdup_trim(line + i + 3);
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		tex->EA = ft_strdup_trim(line + i + 3);
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		tex->WE = ft_strdup_trim(line + i + 3);
}

void	print_error(void)
{
	printf("errooooor\n");
	exit(EXIT_FAILURE);
}
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
char	*ft_strdup_trim(char *src)
{
	int	len;

	len = ft_strlen(src);
	while (len > 0 && (src[len - 1] == ' ' || src[len - 1] == '\n'))
		src[--len] = '\0';
	while (*src == ' ' || *src == '\t')
		src++;
	return (ft_strdup(src));
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erreur : le fichier%s n'existe pas \n",
			path);
		exit(1);
	}
	close(fd);
	printf("✅ Texture trouvée : %s\n", path);
}





int	str_to_int(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > LONG_MAX && sign == 1)
			return (-1);
		if (res > LONG_MAX && sign == -1)
			return (0);
		i++;
	}
	return (extra_number(str, i, sign * res));
}
int	parse_color(char *line, int *out_color)
{
	char	*copy;
	int		values[3];
	int		i;
	char	**tokens;
	char	*token;

	copy = ft_strdup(line);
	if (!copy)
		return (1);
	i = 0;
	tokens = ft_split(copy, ',');
	while (tokens && tokens[i] && i < 3)
	{
		token = tokens[i];
		while (*token == ' ' || *token == '\t')
			token++;
		values[i] = str_to_int(token);
		i++;
	}
	free_split(tokens);
	free(copy);
	if (i != 3)
	{
		printf("❌ Erreur : mauvaise syntaxe pour la couleur (%s)\n", line);
		return (1);
	}
	if (i != 3)
	{
		return (1);
	}
	*out_color = (values[0] << 16) | (values[1] << 8) | values[2];
	return (0);
}
