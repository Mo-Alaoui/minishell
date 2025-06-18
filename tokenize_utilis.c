/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:58:08 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/18 15:31:55 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quote(const char *input, int *i, int *count)
{
	char	quote;

	quote = input[*i];
	while (input[++(*i)] != quote)
	{
		if (input[*i] == '\0')
		{
			(*count)++;
			return ;
		}
	}
}

static int	handle_whitespace(const char *input, int *i, int *count)
{
	if (!ft_isspace(input[*i]))
		return (0);
	while (ft_isspace(input[*i]))
		(*i)++;
	(*count)++;
	return (1);
}

static int	handle_separator(const char *input, int *i, int *count)
{
	char	sep;

	sep = input[*i];
	if (!ft_isseparator(sep))
		return (0);
	(*i)++;
	while (input[*i] == sep)
		(*i)++;
	*count += 2;
	return (1);
}

int	ft_count_token(const char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	input = ft_strtrim(input, " ");
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			skip_quote(input, &i, &count);
		else
		{
			if (handle_whitespace(input, &i, &count))
				continue ;
			if (handle_separator(input, &i, &count))
				continue ;
			i++;
		}
	}
	if (i > 0 && !ft_isspace(input[i - 1]))
		count++;
	return (count);
}

int	is_delimiter(char c)
{
	if (ft_isspace(c) || ft_isseparator(c))
		return (1);
	return (0);
}
