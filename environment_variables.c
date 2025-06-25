/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:52:34 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/25 17:12:48 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variables	*add_new_var(char *input)
{
	t_variables	*new_var;
	char		*name;

	if (!input)
		return (NULL);
	name = var_name(input);
	if (!is_valid_var_name(name))
	{
		//free(name);
		return (NULL);
	}
	new_var = (t_variables *)ft_malloc(sizeof(t_variables), 'A');
	if (!new_var)
	{
		//free(name);
		return (NULL);
	}
	new_var->variable_name = name;
	new_var->value = variable_value(input);
	new_var->next = NULL;
	return (new_var);
}

int	insert_or_update_variable(t_variables **env_list, t_variables *new_var)
{
	t_variables	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->variable_name, new_var->variable_name) == 0)
		{
			free(current->value);
			current->value = NULL;
			current->value = new_var->value;
			free(new_var->variable_name);
			new_var->variable_name = NULL;
			free(new_var);
			    new_var = NULL;
			return (0);
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	current->next = new_var;
	return (0);
}

int	add_variable(t_variables **env_list, char *input)
{
	t_variables	*new_var;

	new_var = add_new_var(input);
	if (!new_var)
		return (-1);
	if (!*env_list)
	{
		*env_list = new_var;
		return (0);
	}
	return (insert_or_update_variable(env_list, new_var));
}

char	*get_env_variable(t_variables *env_list, char *name)
{
	t_variables	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->variable_name, name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

t_variables	*init_env_variables(char **envp)
{
	t_variables	*env_list;
	int			i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		add_variable(&env_list, envp[i]);
		i++;
	}
	return (env_list);
}
