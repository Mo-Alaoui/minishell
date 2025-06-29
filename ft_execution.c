/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:38:39 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 16:34:15 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**path_part;
	char	*path1;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || !envp[i])
		return (cmd);
	path_part = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_part[i] != 0)
	{
		path1 = ft_strjoin(path_part[i], "/");
		path = ft_strjoin(path1, cmd);
		free(path1);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	ft_free(path_part);
	return (cmd);
}

void	ft_ex(char **cmd, int flag)
{
	int	i;

	if (flag == 1)
	{
		i = 0;
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		while (cmd[i] != 0)
			free(cmd[i++]);
		free(cmd);
		exit(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
}

void	ft_execute(char *argv, char **token, t_all *parser, char **envp)
{
	char	*path;

	if (!argv || argv[0] == '\0')
		exit(0);
	if (!token || !token[0])
		exit(0);
	if(is_only_spaces(token[0]) == 1 || (token[0][0] == '\0' && token[1] == NULL))
	    ft_ex(token, 1);
	if (ft_strcmp(token[0], "touch") == 0 || ft_strcmp(token[0], "awk") == 0)
		ft_execute_2(token, envp);
	if (is_builtin_functions(argv) || is_builtin_functions(token[0]))
	{
		if (ft_strcmp(token[0], "exit") == 0 || ft_strcmp(token[0],
				"unset") == 0 || ft_strcmp(token[0], "cd") == 0)
			exit(0);
		if (run_builtin_function(token, &parser->env, &parser->local_env) != 0)
			exit(0);
	}
	path = find_path(token[0], envp);
	if (is_directory(token[0]) == 1 && ft_strcmp(token[0], "..") != 0)
		ft_ex(&token[0], 0);
	if (execve(path, &token[0], envp) == -1)
		ft_ex(&token[0], 1);
}

void	ft_execute_2(char **token, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = find_path(token[0], envp);
	if (execve(path, token, envp) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(token[0], 2);
		while (token[i] != 0)
			free(token[i++]);
		free(token);
		exit(127);
	}
}
