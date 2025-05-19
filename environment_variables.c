#include "minishell.h"

char *var_name(char *input)
{
    int i;

    i = 0;
    while (input[i] && input[i] != '=')
        i++;

    return (ft_substr(input, 0, i));
}

char *variable_value(char *input)
{
    int i;

    i = 0;
    while (input[i] && input[i] != '=')
        i++;
    
    if (input[i] == '=')
        return (ft_substr(input, i + 1, ft_strlen(input) - i - 1));
    return (ft_strdup(""));
}

int is_alnum_underscore(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') || c == '_');
}

int is_valid_var_name(char *name)
{
    int i;

    if (!name || !*name)
        return (0);
    
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    
    i = 1;
    while (name[i])
    {
        if (!is_alnum_underscore(name[i]))
            return (0);
        i++;
    }
    return (1);
}

t_variables *add_new_var(char *input)
{
    t_variables *new_var;
    char *name;

    if (!input)
        return (NULL);
    
    name = var_name(input);
    if (!is_valid_var_name(name))
    {
        free(name);
        return (NULL);
    }

    new_var = (t_variables *)malloc(sizeof(t_variables));
    if (!new_var)
    {
        free(name);
        return (NULL);
    }
    
    new_var->variable_name = name;
    new_var->value = variable_value(input);
    new_var->next = NULL;
    
    return (new_var);
}

int add_variable(t_variables **env_list, char *input)
{
    t_variables *new_var;
    t_variables *current;
    
    new_var = add_new_var(input);
    if (!new_var)
        return (-1);
    
    if (!*env_list)
    {
        *env_list = new_var;
        return (0);
    }
    
    current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->variable_name, new_var->variable_name) == 0)
        {
            free(current->value);
            current->value = new_var->value;
            free(new_var->variable_name);
            free(new_var);
            return (0);
        }
        
        if (!current->next)
            break;
        current = current->next;
    }
    
    current->next = new_var;
    return (0);
}

char *get_env_variable(t_variables *env_list, char *name)
{
    t_variables *current;
    
    current = env_list;
    while (current)
    {
        if (ft_strcmp(current->variable_name, name) == 0)
            return (ft_strdup(current->value));
        current = current->next;
    }
    
    return (NULL);
}

t_variables *init_env_variables(char **envp)
{
    t_variables *env_list;
    int i;
    
    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        add_variable(&env_list, envp[i]);
        i++;
    }
    
    return (env_list);
}

void free_env_variables(t_variables *env_list)
{
    t_variables *current;
    t_variables *next;
    
    current = env_list;
    while (current)
    {
        next = current->next;
        free(current->variable_name);
        free(current->value);
        free(current);
        current = next;
    }
}