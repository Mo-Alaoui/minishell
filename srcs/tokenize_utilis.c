/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:58:08 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/26 09:49:51 by mohalaou         ###   ########.fr       */
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

int	is_delimiter(char c)
{
	if (ft_isspace(c) || ft_isseparator(c))
		return (1);
	return (0);
}

static void	handle_delimiter_logic(const char *input, t_token_data *data)
{
	if (input[data->i] == '\'' || input[data->i] == '"')
		add_token(data, input, data->start, data->i + 1);
	else
		add_token(data, input, data->start, data->i);
}

static void	handle_separator_sequence(const char *input, t_token_data *data)
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

void	process_token_character(const char *input, t_token_data *data)
{
	handle_quotes(input, data);
	if (!data->in_quotes)
	{
		if (is_delimiter(input[data->i]))
		{
			handle_delimiter_logic(input, data);
			handle_separator_sequence(input, data);
			data->start = data->i + 1;
		}
	}
}
