/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:22:38 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/13 09:32:38 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>

static t_gc	**get_gc_head(void)
{
	static t_gc	*head = NULL;
	return (&head);
}

void	*gc_malloc(size_t size)
{
	void	*mem;
	t_gc	*node;
	t_gc	**head;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	node = malloc(sizeof(t_gc));
	if (!node)
	{
		free(mem);
		return (NULL);
	}
	head = get_gc_head();
	node->ptr = mem;
	node->next = *head;
	*head = node;
	return (mem);
}

void	gc_free_all(void)
{
	t_gc	**head;
	t_gc	*tmp;

	head = get_gc_head();
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->ptr);
		free(tmp);
	}
}
