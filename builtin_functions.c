#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "libft/libft.h"
#include "minishell.h"

// void ft_exit(void)
// {
//     g_terminate_program = 0;
// }

void ft_pwd(void)
{
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

int ft_cd(const char *path)
{
    const char *target;
    target = path;

    if (!target)
    {
        target = getenv("HOME");
        if (!target)
        {
            printf("cd: HOME not set\n");
            return -1;
        }
    }
    if (chdir(target) != 0)
    {
        perror("cd");
        return -1;
    }
    return 0;
}

void ft_env(t_variables **env)
{
    t_variables *current;

    if (!env || !*env)
        return;

    current = *env;
    while (current)
    {
        printf("%s=%s\n", current->variable_name, current->value);
        current = current->next;
    }
}

void ft_export(t_variables **env, t_variables **local_env, char *command)
{
    char *value;
    char *res;

    value = get_env_variable(*local_env, command);
    if (value != NULL)
    {
        res = ft_strjoin(ft_strjoin(command, "="), value);
        add_variable(env, res);   
    }
}

void ft_unset(t_variables **env, char **name)
{
    t_variables *current;
    t_variables *previous;

    while ((*++name))
    {           
        current = *env;
        previous = NULL;

        while (current)
        {
            if (ft_strcmp(current->variable_name, *name) == 0)
            {
                if (previous)
                    previous->next = current->next;
                else
                    *env = current->next;

                free(current->variable_name);
                free(current->value);
                free(current);
                break;
            }

            previous = current;
            current = current->next;
        }
    }
}

void ft_echo(char **arg, t_variables **env, t_variables **local_env)
{
    int newline = 1;
    int first = 1;
    int i = 1;
    char *val;

    if (arg[i] && ft_strcmp(arg[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }

    while (arg[i])
    {
        if (!first)
            printf(" ");
        first = 0;

        if (arg[i][0] == '$')
        {
            val = get_env_variable(*local_env, ++arg[i]);
            if (val == NULL)
                val = get_env_variable(*env, arg[i]);
            if (val)
                printf("%s", val);
        }
        else
        {
            printf("%s", arg[i]);
        }
        i++;
    }
    if (newline)
        printf("\n");
}
