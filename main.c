/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:37:32 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/25 17:48:08 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_terminate_program = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	//g_terminate_program = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

}

int	first_call(t_all *parser)
{
	pid_t	pid;

	parser->token = ft_runing(parser, parser->input);
	if (!parser->token)
	{
		return (1);
	}
	parser->envp_p = variables_to_array(parser->env);
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		ft_child(parser, parser->token, parser->flag, parser->envp_p);
		//ft_malloc(0, 'F');
	}
	else
		ft_seg(pid, parser);
	if (WIFEXITED(parser->status))
		g_terminate_program = WEXITSTATUS(parser->status);
	else
		g_terminate_program = 1;

	// ft_malloc(0, 'F');
	return (0);
}

void	ft_propt(char **envp)
{
	t_all	*parser;

	parser = ft_malloc(sizeof(t_all), 'A');
	ft_init_init(parser, envp);
	while (1)
	{
		parser->input = readline("minishell>$ ");
		add_history(parser->input);
		// if (!parser->input)
		// 	break ;
		if (ft_ver(parser) == 1)
			continue ;
		if (*parser->input)
		{
			if (first_call(parser) == 1)
				continue ;
		}
		if (parser->token)
			ft_check_builtin(parser->token, parser, parser->envp_p);
		free(parser->input);
		parser->input = NULL;
	}
	clear_history();
	///ft_malloc(0, 'F');
	//ft_malloc(0, 'P');
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	setup_signals();
	ft_propt(envp);
	//ft_malloc(0, 'F');
	return (0);
}
