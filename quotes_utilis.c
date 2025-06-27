/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:33:02 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/26 16:38:30 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_characters(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	if (str[0] == '\'')
		i++;
	if (ft_isseparator(str[i]))
	{
		c = str[i];
		while ((str[i] && c == str[i]) || str[i] == '\'')
			i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

static int	get_variable_value_length(const char *str, int *index,
		t_variables *env)
{
	char	*env_value;
	char	tmp[256];
	int		var_len;
	int		j;

	j = *index + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (j == *index + 1)
	{
		(*index)++;
		return (1);
	}
	var_len = j - *index - 1;
	ft_memcpy(tmp, str + *index + 1, var_len);
	tmp[var_len] = '\0';
	env_value = get_env_variable(env, tmp);
	*index = j;
	if (env_value)
		return (ft_strlen(env_value));
	return (0);
}

int	get_size(const char *str, t_variables *env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			len += get_variable_value_length(str, &i, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*join_strings(char **words)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (words[i])
	{
		res = ft_strjoin(res, words[i]);
		i++;
	}
	return (res);
}
