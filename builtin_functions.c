#include "minishell.h"

int	numeric_argument(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

void	exit_utils(char **args, int len_args)
{
    int exit_n;
	if (len_args == 2)
	{
		exit_n = (ft_atoi(args[1]) % 256);
		if (exit_n < 0)
			exit_n = exit_n + 256;
		printf("exit\n");
		exit(exit_n);
	}
	else
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_terminate_program = 1;
		return ;
	}
}

void	ft_exit(char **args)
{
	int	len_args;

	len_args = 1;
	if (args)
		while (args[len_args])
			len_args++;
	if (len_args == 1)
	{
		printf("exit\n");
        exit(g_terminate_program);
	}
	else
	{    
		if (numeric_argument(args[1]) == 1)
		{
            if(args[1])
            printf("exit\nminishell: exit: ");
            printf("%s", args[1]);
            printf(": numeric argument required\n");

			g_terminate_program = 2;
			exit(g_terminate_program);
		}
		exit_utils(args, len_args);
	}
}


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

int is_separitor(char c)
{
    return (c == '>' || c == '<' || c == '|');
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
    while (arg[i] && !is_separitor(arg[i][0]))
    {
        if (!first)
            printf(" ");
        first = 0;

        if (arg[i][0] == '$')
        {
            if(arg[i][1] == '?')
                printf("%d",g_terminate_program);
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
