/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_builtin_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:24:21 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/21 15:37:59 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_env_vars(t_variables **env)
{
	char	**env_arr;

	if (!env || !*env)
		return ;
	env_arr = variables_to_array(*env);
	sort_ascii(env_arr);
	while (*env_arr)
	{
		printf("declare -x %s\n", *env_arr);
		env_arr++;
	}
}

static void	run_export(char **cmd, t_variables **env, t_variables **local_env)
{
	int	i;

	i = 1;
	if (cmd[i])
		while (cmd[i])
			ft_export(env, local_env, cmd[i++]);
	else
		print_exported_env_vars(env);
}

static void	run_unset(char **cmd, t_variables **env)
{
	if (cmd[1])
		ft_unset(env, cmd);
}

int	run_builtin_function(char **cmd, t_variables **env, t_variables **local_env)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1]);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		run_export(cmd, env, local_env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		run_unset(cmd, env);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	else
		return (0);
	return (1);
}

char	*get_string_before_char(const char *input_str, char c)
{
	const char	*pos;
	char		*result;
	size_t		length;

	pos = ft_strchr(input_str, c);
	if (pos != NULL)
	{
		length = pos - input_str;
		result = (char *)malloc(length + 1);
		if (result != NULL)
		{
			ft_memcpy(result, input_str, length);
			result[length] = '\0';
		}
		return (result);
	}
	return (NULL);
}
