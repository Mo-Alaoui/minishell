#include "libft.h"

int ft_isseparator(char c)
{
    return (c == ';' || c == '|' || c == '>' 
        || c == '<' || c == '&' || c == '!');
}