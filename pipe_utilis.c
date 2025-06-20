/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:07:43 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/20 19:07:47 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_init(t_all *parser, char **envp)
{
	parser->flag1 = 0;
	parser->history = init_history();
	parser->env = init_env_variables(envp);
	parser->envp_p = variables_to_array(parser->env);
}

char	**ft_runing(t_all *parser, char *input)
{
	char	**token;
	char	*check;

	add_history(input);
	add_to_history(parser->history, input);
	token = ft_tokenize(input);
	if (!token)
	{
		g_terminate_program = 1;
		return (NULL);
	}
	token = force_quote(token, parser);
	check = is_valid_input(token);
	if (check != NULL)
	{
		ft_ft(check);
		g_terminate_program = 2;
		return (NULL);
	}
	init_all(parser, token);
	parser->flag = check_parser(token);
	parser->local_env = ft_check_export(token, parser->env);
	return (token);
}

int	check_input_type(char **token)
{
	int	has_pipe;
	int	has_redir;
	int	i;

	has_pipe = 0;
	has_redir = 0;
	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "'|'") == 0)
			has_pipe = 1;
		else if (ft_strcmp(token[i], "'<'") == 0 || ft_strcmp(token[i],
				"'<<'") == 0 || ft_strcmp(token[i], "'>'") == 0
			|| ft_strcmp(token[i], "'>>'") == 0)
			has_redir = 1;
		i++;
	}
	if (has_pipe && has_redir)
		return (3); // pipes + redirections
	else if (has_pipe)
		return (2); // only pipes
	else if (has_redir)
		return (0); // only redirection
	return (0);     // pure command with no pipe/redir
}

void	ft_helper1(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "'>'") == 0)
			redirect_output(token[i + 1], 0);
		if (ft_strcmp(token[i], "'>>'") == 0)
			redirect_output(token[i + 1], 1);
		i++;
	}
}

void	ft_helper(char **token)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "'<'") == 0)
			redirect_input(token[i + 1]);
		i++;
	}
}
