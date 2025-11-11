/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:54:30 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/11 16:36:23 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoinn(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (0);
	if (!s1)
	{
		return (ft_strdup(s2));
	}
	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	new_str = (char *)gc_malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
					+ 1)));
	if (!new_str)
		return (NULL);
	while (s1[i])
		new_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	return (new_str);
}
