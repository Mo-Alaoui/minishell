/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_utilis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:34:02 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/17 18:34:12 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variables	*ft_check_export(char **token, t_variables *env)
{
	char		*var_name;
	t_variables	*local_env;
	int			i;

	local_env = NULL;
	i = 0;
	while (token[i])
	{
		var_name = get_string_before_char(token[i], '=');
		if (var_name != NULL)
		{
			if (ft_strcmp(token[0], "export") == 0 || get_env_variable(env,
					var_name) != NULL)
				add_variable(&env, token[i]);
			add_variable(&local_env, token[i]);
		}
		i++;
	}
	if (var_name == NULL)
		return (NULL);
	return (local_env);
}

void	ft_env(t_variables **env)
{
	t_variables	*current;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->variable_name, current->value);
		current = current->next;
	}
}

void	ft_export(t_variables **env, t_variables **local_env, char *command)
{
	char	*value;
	char	*res;

	value = get_env_variable(*local_env, command);
	if (value != NULL)
	{
		res = ft_strjoin(ft_strjoin(command, "="), value);
		add_variable(env, res);
	}
}

void	ft_unset(t_variables **env, char **name)
{
	t_variables	*current;
	t_variables	*previous;

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
				break ;
			}
			previous = current;
			current = current->next;
		}
	}
}

void	ft_echo(char **arg)
{
	int newline;
	int i;
	int j;

	newline = 1;
	i = 1;
	j = 0;
	while (arg[i] && arg[i][0] == '-')
	{
		j = 1;
		while (arg[i][j] && arg[i][j] == 'n')
			j++;
		if (arg[i][j] == '\0')
			newline = 0;
		else
			break ;
		i++;
	}
	if (arg[i])
		printf("%s", arg[i++]);
	while (arg[i])
		printf(" %s", arg[i++]);
	if (newline)
		printf("\n");
}