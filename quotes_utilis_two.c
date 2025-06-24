/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utilis_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:07:37 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/24 20:32:53 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_variable_token(const char *str, t_token_variables *var,
	t_variables *env)
{
	t_process_var	v;

	v.j = var->i + 1;
	if (str[v.j] == '?')
	{
		v.g_num_str = ft_itoa(g_terminate_program);
		ft_memcpy(var->result + var->ri, v.g_num_str, ft_strlen(v.g_num_str));
		var->ri += ft_strlen(v.g_num_str);
		var->i += 2;
		free(v.g_num_str);
		return ;
	}
	while (str[v.j] && (ft_isalnum(str[v.j]) || str[v.j] == '_'))
		v.j++;
	ft_memcpy(v.temp, str + var->i + 1, v.j - var->i - 1);
	v.temp[v.j - var->i - 1] = '\0';
	v.rep = get_env_variable(env, v.temp);
	if (v.rep)
	{
		ft_memcpy(var->result + var->ri, v.rep, ft_strlen(v.rep));
		var->ri += ft_strlen(v.rep);
	}
	var->i = v.j - 1;
}

char	*replace_token(const char *str, t_variables *env)
{
	t_token_variables	var;

	var.ri = 0;
	var.i = 0;
	var.result = (char *)ft_malloc(get_size(str, env) + 1, 'A');
	if (!var.result)
		return (NULL);
	while (str[var.i])
	{
		if (str[var.i] == '$' && (ft_isalnum(str[var.i + 1])
				|| str[var.i + 1] == '_'
				|| str[var.i + 1] == '?') && !ft_isdigit(str[var.i + 1]))
			process_variable_token(str, &var, env);
		else
			var.result[var.ri++] = str[var.i];
		var.i++;
	}
	var.result[var.ri] = '\0';
	return (var.result);
}

char	*handel_special_characters(char *str)
{
	char	*ret;

	int len, (i), (j);
	len = ft_strlen(str);
	ret = ft_malloc((len + 3) * sizeof(char), 'A');
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	ret[i++] = '\'';
	while (j < len)
	{
		ret[i++] = str[j];
		j++;
	}
	ret[i++] = '\'';
	ret[i] = '\0';
	return (ret);
}
