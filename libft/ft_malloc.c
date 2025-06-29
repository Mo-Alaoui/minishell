/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:05:38 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/29 18:43:29 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_malloc_free(t_gc_node *head)
{
	t_gc_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->ptr)
		{
			free(tmp->ptr);
			tmp->ptr = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	*ft_malloc(size_t size, char c)
{
	static t_gc_node	*head;
	t_gc_node			*node;
	void				*ptr;

	if (size && c == 'A')
	{
		ptr = ft_calloc(size, 1);
		if (!ptr)
			return (NULL);
		else
			ft_memset(ptr, 0, size);
		node = ft_calloc(sizeof(t_gc_node), 1);
		if (!node)
			return (NULL);
		else
			ft_memset(ptr, 0, size);
		node->ptr = ptr;
		node->next = head;
		head = node;
		return (ptr);
	}
	else if (!size && c == 'F')
		ft_malloc_free(head);
	return (NULL);
}
