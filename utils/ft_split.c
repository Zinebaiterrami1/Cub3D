/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:01:38 by zait-err          #+#    #+#             */
/*   Updated: 2025/10/27 20:51:46 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_word(char const *s, char c)
{
	int	count_word;
	int	i;
	int	check;

	count_word = 0;
	i = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] == c)
			check = 0;
		else if (check == 0)
		{
			check = 1;
			count_word++;
		}
		i++;
	}
	return (count_word);
}

static int	len_word(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	*fill_word(const char *s, char c)
{
	char	*arr;
	size_t	len_src;

	len_src = len_word(s, c);
	arr = (char *)malloc((len_src + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, (char *)s, len_src);
	arr[len_src] = '\0';
	return (arr);
}

static char	**ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

void	free_split(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**ft_split(char  *s, char c)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			str[j] = fill_word(s + i, c);
			if (str[j++] == NULL)
				return (ft_free(str));
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (str[j] = NULL, str);
}
