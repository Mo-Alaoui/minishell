/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:26:42 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/18 11:36:54 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_variable_token(const char *str, int *i, char *result,
		int *ri, t_variables *env)
{
	char	*g_num_str, (*rep);
	char	temp[256];
	int		j;

	j = *i + 1;
	if (str[j] == '?')
	{
		g_num_str = ft_itoa(g_terminate_program);
		ft_memcpy(result + *ri, g_num_str, ft_strlen(g_num_str));
		*ri += ft_strlen(g_num_str);
		*i += 2;
		free(g_num_str);
		return ;
	}
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	ft_memcpy(temp, str + *i + 1, j - *i - 1);
	temp[j - *i - 1] = '\0';
	rep = get_env_variable(env, temp);
	if (rep)
	{
		ft_memcpy(result + *ri, rep, ft_strlen(rep));
		*ri += ft_strlen(rep);
	}
	*i = j - 1;
}

char	*replace_token(const char *str, t_variables *env)
{
	char	*result;
	int		ri;
	int		i;

	ri = 0;
	i = 0;
	result = (char *)malloc(get_size(str, env) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?') && !ft_isdigit(str[i + 1]))
			process_variable_token(str, &i, result, &ri, env);
		else
			result[ri++] = str[i];
		i++;
	}
	result[ri] = '\0';
	return (result);
}

char	*handel_special_characters(char *str)
{
	char	*ret;

	int len, (i), (j);
	len = ft_strlen(str);
	ret = malloc((len + 3) * sizeof(char));
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

void	replacement_strings(char **words, t_variables *env)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		if (is_special_characters(words[i]))
			words[i] = handel_special_characters(words[i]);
		else if (words[i][0] != '\'')
		{
			if (words[i][0] == '"')
			{
				words[i] = ft_strtrim(words[i], "\"");
			}
			words[i] = replace_token(words[i], env);
		}
		else
			words[i] = ft_strtrim(words[i], "'");
		i++;
	}
}


static void	add_word(char **ret, int *ret_count, char *input, int start,
		int end)
{
	if (end > start)
	{
		ret[*ret_count] = ft_strndup(input + start, end - start);
		if (!ret[*ret_count])
		{
			free_words(ret, *ret_count);
			exit(1);
		}
		(*ret_count)++;
	}
}

static void	parse_quoted_part(char *token, int *i, char **ret, int *ret_count)
{
	int		quote_start;
	char	quote;

	quote_start = *i;
	quote = token[*i];
	(*i)++;
	while (token[*i] && token[*i] != quote)
		(*i)++;
	if (token[*i] == quote)
		(*i)++;
	add_word(ret, ret_count, token, quote_start, *i);
}

char	**split_by_quotes(char *token, int max_parts)
{
	char	**ret;

	int i, (start), (ret_count);
	ret_count = 0;
	start = 0;
	i = 0;
	ret = malloc((max_parts + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			if (i > start)
				add_word(ret, &ret_count, token, start, i);
			parse_quoted_part(token, &i, ret, &ret_count);
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		add_word(ret, &ret_count, token, start, i);
	ret[ret_count] = NULL;
	return (ret);
}

char	*handel_quotes(char *input, t_variables *env)
{
	char	**words;
	int		i;

	words = split_by_quotes(input, 10);
	replacement_strings(words, env);
	input = join_strings(words);
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (input);
}
