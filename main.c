/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:37:32 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/21 15:32:14 by mohalaou         ###   ########.fr       */
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
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	first_call(t_all *parser , t_gc *gc)
{
	pid_t	pid;

	parser->token = ft_runing(parser, parser->input);
	if (!parser->token)
		return (1);
	parser->envp_p = variables_to_array(parser->env, gc);
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		ft_child(parser, parser->token, parser->flag, parser->envp_p);
	else
		ft_seg(pid, parser);
	gc_free_all(&parser->gc);
	if (WIFEXITED(parser->status))
		g_terminate_program = WEXITSTATUS(parser->status);
	else
		g_terminate_program = 1;
	return (0);
}


void	ft_propt(char **envp)
{
	t_all	*parser;
	parser = malloc(sizeof(t_all));
	parser = gc_malloc(&parser->gc,sizeof(t_all));
	ft_init_init(parser, envp , &parser->gc);
	while (1)
	{
		parser->input = readline("minishell>$ ");
		if (ft_ver(parser, &parser->gc) == 1)
			continue ;
		if (*parser->input)
		{
			if (first_call(parser, &parser->gc) == 1)
			{
				gc_free_all(&parser->gc);
				continue ;
			}
		}
		printf("\n++++++++++++++++++++++++++++++++\n");
		if (parser->token)
			ft_check_builtin(parser->token, parser, parser->envp_p , &parser->gc);
		gc_free_all(&parser->gc);
	}
	printf("\n++++++++++++++++++++++++++++++++\n");
	gc_free_all(&parser->gc);
	parser->gc.head = NULL;
	ft_for_leaks(parser, parser->token);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	setup_signals();
	ft_propt(envp);
	return (0);
}
