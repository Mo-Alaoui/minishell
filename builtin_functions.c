/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:06:29 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/25 17:24:19 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	exit_n;

	if (len_args == 2 && ft_strcmp(args[1], "'|'") != 0)
	{
		exit_n = (ft_atoi(args[1]) % 256);
		if (exit_n < 0)
			exit_n = exit_n + 256;
		printf("exit\n");
		exit(exit_n);
	}
	else if (ft_strcmp(args[1], "'|'") != 0)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_terminate_program = 1;
		return ;
	}
	return ;
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
		//ft_malloc(0,'F');
		exit(g_terminate_program);
	}
	else
	{
		if (numeric_argument(args[1]) == 1 && ft_strcmp(args[1], "'|'") != 0)
		{
			if (args[1])
				printf("exit\nminishell: exit: ");
			printf("%s", args[1]);
			printf(": numeric argument required\n");
			g_terminate_program = 2;
				//ft_malloc(0,'F');	
			exit(g_terminate_program);
		}
		exit_utils(args, len_args);
	}
}

void	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}

int	ft_cd(const char *path)
{
	const char	*target;

	target = path;
	if (!target)
	{
		target = getenv("HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return (-1);
		}
	}
	if (target[0] == '\0')
	{
		return (0);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
