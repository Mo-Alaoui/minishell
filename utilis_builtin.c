#include "minishell.h"

int is_builtin_functions(char *str)
{
    if (  !ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) 
       || !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd")
       || !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
       || !ft_strncmp(str, "exit", 4)) 
    {
        return (1);
    }
     return (0);
}

static int list_size(t_variables *head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

char **variables_to_array(t_variables *head)
{
    int size = list_size(head);
    char **array = malloc(sizeof(char *) * (size + 1));
    int i = 0;
    char *tmp;

    if (!array)
        return NULL;

    while (head)
    {
        tmp = malloc(strlen(head->variable_name) + 1 + strlen(head->value) + 1);
        if (!tmp)
        {
            // optional: free previously allocated array[i]
            return NULL;
        }

        strcpy(tmp, head->variable_name); // fill with name
        strcat(tmp, "=");                 // append '='
        strcat(tmp, head->value);         // append value

        array[i++] = tmp;                 // store in array
        head = head->next;                // move to next node
    }

    array[i] = NULL; // NULL-terminate
    return array;
}

void sort_ascii(char **arr)
{
    int i, j;
    char *temp;

    if (!arr)
        return;

    i = 0;
    while (arr[i])
        i++; // count number of elements

    while (i > 1)
    {
        j = 0;
        while (arr[j + 1])
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i--; // reduce pass count
    }
}

void print_exported_env_vars(t_variables **env)
{
    if (!env || !*env)
        return ;

    char **env_arr = variables_to_array(*env);
    sort_ascii(env_arr);

    while (*env_arr)
    {
        printf("declare -x %s\n", *env_arr);
        env_arr++;
    }
}

int  run_builtin_funciton(char **command, t_variables **env, t_variables **local_env)
{
    int i;

    if (ft_strcmp(command[0], "echo") == 0)
        ft_echo(command, env, local_env);
    else if (ft_strcmp(command[0], "cd") == 0)
    {
        //printf("------[%s]\n", *(command + 1));
        ft_cd(*(command + 1));
    }
    else if (ft_strcmp(command[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command[0], "export") == 0)
    {
        i = 1;
        if (command[i])
        {
            while (command[i])
            {
                ft_export(env, local_env, command[i]);
                i++;
            }
        }
        else
        {
            print_exported_env_vars(env);
        }
    }
    else if (ft_strcmp(command[0], "unset") == 0)
    {
        if (command[1])
            ft_unset(env, command);
    }
    else if (ft_strcmp(command[0], "env") == 0)
        ft_env(env);
    else if (ft_strcmp(command[0], "exit") == 0)
        ft_exit(command);
    else
        return(0);
    return(1);
}

char *get_string_before_char(const char *input_str, char c) 
{
    const char *pos;
    pos = ft_strchr(input_str, c);

    if (pos != NULL) 
    {
        size_t length;
        length = pos - input_str;
        char *result = (char *)malloc(length + 1);
        if (result != NULL)
        {
            ft_memcpy(result, input_str, length);
            result[length] = '\0';
        }
        return result;
    } 
    return (NULL);
}
