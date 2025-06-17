#include "minishell.h"

t_list *ft_parser(char **tokenize, char *s)
{
    int i = 0;
    char *str = ft_strdup("");
    t_list *head = NULL;
    t_list *new;

    while (tokenize[i])
    {
        if (ft_strcmp(tokenize[i], s) == 0)
        {
            new = ft_lstnew(str);
            ft_lstadd_back(&head, new);
            str = ft_strdup("");     
            i++;
        }
        char *tmp = str;
        str = ft_strjoin(str, tokenize[i]); 
        free(tmp);

        if (tokenize[i + 1] && ft_strcmp(tokenize[i + 1], s) != 0)
        {
            tmp = str;
            str = ft_strjoin(str, " ");
            free(tmp);
        }
        i++;
    }
    if (str && *str)
    {
        new = ft_lstnew(str);
        ft_lstadd_back(&head, new);
    }
    return head;
}

t_list *ft_parser2(char **tokenize)
{
    int i = 0;
    char *str = ft_strdup("");
    t_list *head = NULL;
    t_list *new;

    while (tokenize[i])
    {
        if (ft_strcmp(tokenize[i], "'<'") == 0 || ft_strcmp(tokenize[i] , "'>'") == 0 || ft_strcmp(tokenize[i] , "'|'") == 0)
        {
            new = ft_lstnew(str);
            ft_lstadd_back(&head, new);
            str = ft_strdup("");     
            i++;
        }
        char *tmp = str;
        str = ft_strjoin(str, tokenize[i]); 
        free(tmp);


        if (tokenize[i + 1] && ft_strcmp(tokenize[i + 1], "'<'") != 0 && ft_strcmp(tokenize[i + 1], "'>'") != 0 && ft_strcmp(tokenize[i + 1], "'|'") != 0 )
        {
            tmp = str;
            str = ft_strjoin(str, " ");
            free(tmp);
        }
        i++;
    }
    if (str && *str)
    {
        new = ft_lstnew(str);
        ft_lstadd_back(&head, new);
    }
    return head;
}
