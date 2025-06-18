/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:28:03 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/18 14:57:27 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(const char *input, t_token_data *data)
{
	if (input[data->i] == '"' || input[data->i] == '\'')
	{
		if (data->in_quotes && input[data->i] == data->quote_char)
			data->in_quotes = 0;
		else if (!data->in_quotes)
		{
			data->in_quotes = 1;
			data->quote_char = input[data->i];
		}
	}
}

static void	add_token(t_token_data *data, const char *input, int start, int end)
{
	if (end > start)
	{
		data->tokens[data->token_count] = strndup(input + start, end - start);
		if (!data->tokens[data->token_count])
		{
			while (data->token_count--)
				free(data->tokens[data->token_count]);
			free(data->tokens);
			exit(EXIT_FAILURE);
		}
		data->token_count++;
	}
}

static void	handle_separator_token(const char *input, t_token_data *data)
{
	char	check_sepa;
	int		j;

	check_sepa = input[data->i];
	if (ft_isseparator(check_sepa))
	{
		j = 0;
		while (input[data->i + 1] == check_sepa)
		{
			j++;
			data->i++;
		}
		add_token(data, input, data->i - j, data->i + 1);
	}
}

static char	**finalize_tokens(t_token_data *data, const char *input)
{
	if (data->in_quotes)
	{
		printf("Error : unclosed quotes\n");
		return (NULL);
	}
	add_token(data, input, data->start, data->i);
	data->tokens[data->token_count] = NULL;
	return (data->tokens);
}

char	**ft_tokenize(const char *input)
{
	t_token_data	data;
	int				len;

	len = ft_count_token(input);
	ft_memset(&data, 0, sizeof(t_token_data));
	data.tokens = malloc(sizeof(char *) * (len + 1));
	if (!data.tokens)
		return (NULL);
	while (input[data.i])
	{
		handle_quotes(input, &data);
		if (!data.in_quotes && is_delimiter(input[data.i]))
		{
			if (input[data.i] == '\'' || input[data.i] == '"')
				add_token(&data, input, data.start, data.i + 1);
			else
				add_token(&data, input, data.start, data.i);
			handle_separator_token(input, &data);
			data.start = data.i + 1;
		}
		data.i++;
	}
	return (finalize_tokens(&data, input));
}
