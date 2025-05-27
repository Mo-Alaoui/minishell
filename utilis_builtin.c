#include "minishell.h"

int is_builtin_functions(char *str)
{
    if (  !ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") 
       || !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd")
       || !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
       || !ft_strcmp(str, "exit")) 
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

void run_builtin_funciton(char **argv, t_variables **env, t_variables **local_env)
{
    int i;

    if (ft_strcmp(*argv, "echo") == 0)
        ft_echo(argv, env, local_env);
    if (ft_strcmp(*argv, "cd") == 0)
    {
        ft_cd(*(argv + 1));
    }
    if (ft_strcmp(*argv, "pwd") == 0)
        ft_pwd();
    if (ft_strcmp(*argv, "export") == 0)
    {
        i = 1;
        if (argv[i])
        {
            while (argv[i])
            {
                ft_export(env, local_env, argv[i]);
                i++;
            }
        }
        else
        {
            print_exported_env_vars(env);
        }
        
    }
    if (ft_strcmp(*argv, "unset") == 0)
    {
        if (*argv)
            ft_unset(env, argv);
    }
    if (ft_strcmp(*argv, "env") == 0)
        ft_env(env);
    if (ft_strcmp(*argv, "exit") == 0)
    {
        ft_exit(argv);
    }
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
