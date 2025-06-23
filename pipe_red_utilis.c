/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:24:09 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/20 18:24:10 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_subarray(char **tokens, int start, int end)
{
	char	**sub;
	int		i;

	sub = malloc(sizeof(char *) * (end - start + 1));
	i = 0;
	while (start < end)
		sub[i++] = ft_strdup(tokens[start++]);
	sub[i] = NULL;
	return (sub);
}

char	*ft_join_with_space(char **tokens)
{
	char	*res;
	char	*tmp;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (tokens[i])
	{
		tmp = res;
		res = ft_strjoin(res, tokens[i]);
		free(tmp);
		if (tokens[i + 1])
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
		}
		i++;
	}
	return (res);
}

int	count_tok_size(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0
			|| strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

char	**remove_redir_tokens(char **tokens)
{
	int		count;
	char	**args;
	int		i;
	int		j;

	count = 0;
	count = count_tok_size(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	j = 0;
	i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0
			|| strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
			i++;
		else
			args[j++] = ft_strdup(tokens[i]);
		i++;
	}
	args[j] = NULL;
	return (args);
}

int	wait_loop1(char *line, char *heredoc_delim)
{
	if (!line || ft_strcmp(line, heredoc_delim) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}
