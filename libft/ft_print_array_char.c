#include "libft.h"
#include <stdio.h>

void print_array_char( char **arr)
{
    int i;
    i = 0;
    if (!arr)
        return ;
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        i++;
    }
}