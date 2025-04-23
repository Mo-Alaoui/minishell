#include "minishell.h"

char *var_value(char *str)
{
    char *value ;
    char *s;
    if(ft_strcmp(str, "$?") == 0)
        return(ft_strdup("0\n"));
    s = str + 1;
    value = getenv(s);
    if(!value)
        return(ft_strdup(""));
    return (value);
}

void free_char_array(char **ptr)
{
    int i = 0;

    if (!ptr)
        return;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}
