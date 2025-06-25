#include "libft.h"
#include <stdio.h>

void *ft_malloc(size_t size, char c)
{
    static t_gc_node *head;
    t_gc_node *node;
    void *ptr;

    if (size && c == 'A')
    {
        ptr = malloc(size);
        if (!ptr)
            return NULL;
        else
            ft_memset(ptr, 0, size);
        node = malloc(sizeof(t_gc_node));
        if (!node)
            return NULL;
        else
            ft_memset(ptr, 0, size);
        node->ptr = ptr;
        node->next = head;
        head = node;
        return ptr;
    }
    else if (!size && c == 'F')
    {
        while (head)
        {
            t_gc_node *tmp = head;
            head = head->next;

            if (tmp->ptr)
            {
               // printf("------------> %p\n", tmp->ptr);
                free(tmp->ptr);   // Still safe to call free(NULL), but this avoids unnecessary calls
                tmp->ptr = NULL;  // Prevent dangling pointer (good if reused elsewhere)
            }

            free(tmp);
            tmp = NULL;
        }
    }
    else if (!size && c == 'P')
    {
       // int i = 0;
        node = head;
        while (node)
        {
            node = node->next;
        }
    }
    return NULL;
}

// char *fun(char *str, int size)
// {
//     char *s = ft_malloc(size, 'A');
//     if (s) {
//         strcpy(s, str);
//     }
//     return s;
// }

// int main()
// {
	
// 	char *n = fun("hi", 10);
// 	char *b = fun("ho", 5);	
	
// 	if (n && b)
// 		printf("[%s, %s]\n", n, b);
	
//     ft_malloc(0, 'F');
// }