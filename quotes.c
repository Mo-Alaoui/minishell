/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:26:42 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/25 16:26:26 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replacement_strings(char **words, t_variables *env)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		if (is_special_characters(words[i]))
		{
			//printf("[%s]\n", words[i]);
			words[i] = handel_special_characters(words[i]);
		}
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

static void	add_word(char **ret, char *input, t_split_variables *var)
{
	int	start;
	int	end;

	start = var->start;
	end = var->i;
	if (end > start)
	{
		ret[var->ret_count] = ft_strndup(input + start, end - start);
		if (!ret[var->ret_count])
		{
			//free_words(ret, var->ret_count);
			exit(1);
		}
		(var->ret_count)++;
	}
}

static void	parse_quoted_part(char **ret, char *token, t_split_variables *var)
{
	char	quote;

	var->start = var->i;
	quote = token[var->i];
	var->i++;
	while (token[var->i] && token[var->i] != quote)
		var->i++;
	if (token[var->i] == quote)
		var->i++;
	add_word(ret, token, var);
}

char	**split_by_quotes(char *token, int max_parts)
{
	t_split_variables	var;
	char				**ret;

	ft_memset(&var, 0, sizeof(var));
	ret = ft_malloc((max_parts + 1) * sizeof(char *), 'A');
	if (!ret)
		return (NULL);
	while (token[var.i])
	{
		if (token[var.i] == '\'' || token[var.i] == '"')
		{
			if (var.i > var.start)
				add_word(ret, token, &var);
			parse_quoted_part(ret, token, &var);
			var.start = var.i;
		}
		else
			var.i++;
	}
	if (var.i > var.start)
		add_word(ret, token, &var);
	ret[var.ret_count] = NULL;
	return (ret);
}

char	*handel_quotes(char *input, t_variables *env)
{
	char	**words;
	int		i;

	words = split_by_quotes(input, 250);
	replacement_strings(words, env);
	input = join_strings(words);
	i = 0;
	// while (words[i])
	// {
	// 	free(words[i]);
	// 	i++;
	// }
	// free(words);
	return (input);
}
