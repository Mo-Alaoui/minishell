#include "libft.h"
#include <stdio.h>

void print_array_char(const char **arr)
{
    if (!arr)
        return ;
    while (*arr)
    {
        printf("%s\n", *arr++);
    }
}