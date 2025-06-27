/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:07:43 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 17:08:03 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_init(t_all *parser, char **envp)
{
	parser->flag1 = 0;
	parser->env = init_env_variables(envp);
	parser->envp_p = variables_to_array(parser->env);
}

char	**ft_runing(t_all *parser, char *input)
{
	char	**token;
	char	*check;

	token = ft_tokenize(input);
	if (!token)
	{
		g_terminate_program = 1;
		return (NULL);
	}
	check = is_valid_input(token);
	token = force_quote(token, parser);
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
		return (3);
	else if (has_pipe)
		return (2);
	else if (has_redir)
		return (0);
	return (0);
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
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "'<'") == 0)
			redirect_input(token[i + 1]);
		i++;
	}
}
