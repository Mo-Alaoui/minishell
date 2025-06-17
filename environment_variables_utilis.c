/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables_utilis.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:00:13 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/17 19:00:18 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_name(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	return (ft_substr(input, 0, i));
}

char	*variable_value(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	if (input[i] == '=')
		return (ft_substr(input, i + 1, ft_strlen(input) - i - 1));
	return (ft_strdup(""));
}

int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalpha(name[i]) || ft_isdigit(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	free_env_variables(t_variables *env_list)
{
	t_variables	*current;
	t_variables	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->variable_name);
		free(current->value);
		free(current);
		current = next;
	}
}
