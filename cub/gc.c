/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:22:38 by fakoukou          #+#    #+#             */
/*   Updated: 2025/11/11 16:22:40 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_gc
{
    void            *ptr;
    struct s_gc     *next;
}   t_gc;

static t_gc *g_head = NULL; // global list head

void *gc_malloc(size_t size)
{
    void *mem = malloc(size);
    if (!mem)
        return (NULL);

    t_gc *node = malloc(sizeof(t_gc));
    if (!node)
    {
        free(mem);
        return (NULL);
    }
    node->ptr = mem;
    node->next = g_head;
    g_head = node;
    return (mem);
}

void gc_free_all(void)
{
    t_gc *tmp;

    while (g_head)
    {
        tmp = g_head;
        g_head = g_head->next;
        free(tmp->ptr);
        free(tmp);
    }
}
