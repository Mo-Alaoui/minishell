#include "minishell.h"


void	gc_add(t_gc *gc, void *ptr)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = gc->head;
	gc->head = new;
	//printf("[GC] Added pointer: %p\n", ptr);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(gc, ptr);
	return (ptr);
}

void	gc_free_all(t_gc *gc)
{
	t_garbage	*tmp;
	printf("----------------------[     ]------------------------\n");
	/*while (gc->head)
		{
				printf("from ft_check... : %p\n", gc->head->ptr);
				gc->head = gc->head->next;
		}*/
	while (gc->head)
	{
		free(gc->head->ptr);
		tmp = gc->head;
		gc->head = gc->head->next;
		free(tmp);
	}
}