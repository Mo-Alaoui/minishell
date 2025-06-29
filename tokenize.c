/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:20:05 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/29 18:54:46 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token_data *data, const char *input, int start, int end)
{
	int	num;

	num = end - start;
	if (end > start)
	{
		data->tokens[data->token_count] = ft_strndup(input + start, num);
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

static void skip_quote(const char *input, int *i)
{
	char quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
		(*i)++;
}

static int handle_whitespace_separator(const char *input, int *i, int *count)
{
	char sep;

	if (ft_isspace(input[*i]))
	{
		while (ft_isspace(input[*i]))
			(*i)++;
		return (1);
	}
	if (ft_isseparator(input[*i]))
	{
		sep = input[*i];
		(*count) += 2;
		while (input[++(*i)] == sep)
			;
		return (1);
	}
	return (0);
}

static int ft_count_token(const char *input)
{
	int i, (count), (in_token);
	
	i = 0;
	count = 0;
	in_token = 0;
	while (input[i])
	{
		if (handle_whitespace_separator(input, &i, &count))
		{
			in_token = 0;
			continue;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			skip_quote(input, &i);
			count++;
			in_token = 1;
			continue;
		}
		if (!ft_isspace(input[i]) && !ft_isseparator(input[i]))
		{
			if (!in_token)
			{
				count++;
				in_token = 1;
			}
		}
		else
			in_token = 0;
		i++;
	}
	return count;
}



char	**ft_tokenize(const char *input)
{
	t_token_data	data;
	int				len;

	ft_memset(&data, 0, sizeof(t_token_data));
	len = ft_count_token(input);
	
	data.tokens = ft_malloc(sizeof(char *) * (len * 2), 'A');
	if (!data.tokens)
		return (NULL);
	while (input[data.i])
	{
		process_token_character(input, &data);
		data.i++;
	}
	if (data.in_quotes == 1)
	{
		printf("Error : unclosed quotes\n");
		return (NULL);
	}
	add_token(&data, input, data.start, data.i);
	data.tokens[data.token_count] = NULL;
	return (data.tokens);
}
