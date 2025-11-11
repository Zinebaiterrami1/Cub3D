/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-err <zait-err@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:36:53 by zait-err          #+#    #+#             */
/*   Updated: 2025/11/11 09:57:57 by zait-err         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*substr)
		return ((char *)str);
	if (!str && len == 0)
		return (NULL);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (substr[j] == str[i + j] && (i + j) < len && str[i + j])
		{
			j++;
		}
		if (substr[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
