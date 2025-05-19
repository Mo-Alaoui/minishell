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

void run_builtin_funciton(char **command, t_variables **env, t_variables **local_env)
{
    if (ft_strcmp(command[0], "echo") == 0)
        ft_echo(command, env, local_env);
    if (ft_strcmp(command[0], "cd") == 0)
    {
        ft_cd(*(command + 1));
    }
    if (ft_strcmp(command[0], "pwd") == 0)
        ft_pwd();
    if (ft_strcmp(command[0], "export") == 0)
    {
        if (command[1])
            ft_export(env, local_env, command[1]);
    }
    if (ft_strcmp(command[0], "unset") == 0)
    {
        if (command[1])
            ft_unset(env, command);
    }
    if (ft_strcmp(command[0], "env") == 0)
        ft_env(env);
    if (ft_strcmp(command[0], "exit") == 0)
    {
        // printf("---------------------------\n");
        // print_array_char(command);
        // printf("\n---------------------------\n");
        ft_exit(command);
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
