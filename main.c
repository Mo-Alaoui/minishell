/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:37:32 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/18 00:37:41 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_terminate_program = 0;

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

t_variables	*ft_check_export(char **token, t_variables *env)
{
	char		*var_name;
	t_variables	*local_env;
	int			i;

	local_env = NULL;
	i = 0;
	while (token[i])
	{
		var_name = get_string_before_char(token[i], '=');
		if (var_name != NULL)
		{
			if (ft_strcmp(token[0], "export") == 0 || get_env_variable(env,
					var_name) != NULL)
				add_variable(&env, token[i]);
			add_variable(&local_env, token[i]);
		}
		i++;
	}
	if (var_name == NULL)
		return (NULL);
	return (local_env);
}

void	ft_child(t_all *parser, char **token, int flag, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_input_type(token) == 3)
		exit(if_its_pipe_red(token, parser->new_pip, parser, envp));
	if (check_input_type(token) == 2)
		exit(if_its_pipe(parser->new_pip, token, parser, envp));
	if (check_input_type(token) == 0)
	{
		if (check_herdoc(token, envp) == 1)
			ft_call(parser, flag, envp);
		else if (check_red(token) == 1)
			ft_call1(parser, flag, envp);
		else if (check_red(token) == 2)
			ft_call2(parser, flag, envp);
		else if (check_red(token) == 3)
			ft_call3(parser, flag, envp);
		else if (check_red(token) == 4)
			ft_call4(parser, flag, envp);
		else
			ft_execute(parser->new_pip->content, parser->clean, parser, envp);
	}
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

void	ft_init_init(t_all *parser, char **envp)
{
	parser->flag1 = 0;
	parser->history = init_history();
	parser->env = init_env_variables(envp);
	parser->envp_p = variables_to_array(parser->env);
}

void ft_seg(pid_t pid, t_all *parser)
				{
					signal(SIGINT, SIG_IGN);
					waitpid(pid, &parser->status, 0);
					signal(SIGINT, sigint_handler);
				}
void	ft_propt(char **envp)
{
	pid_t	pid;
	t_all	*parser;

	parser = malloc(sizeof(t_all));
	ft_init_init(parser, envp);
	while (1)
	{
		parser->input = readline("minishell>$ ");
		if (ft_ver(parser) == 1)
			continue ;
		if (*parser->input)
		{
			parser->token = ft_runing(parser, parser->input);
			if (!parser->token)
				continue ;
			parser->envp_p = variables_to_array(parser->env);
			pid = fork();
			if (pid == 0)
				ft_child(parser, parser->token, parser->flag, parser->envp_p);
			else
				ft_seg(pid, parser);
			if (WIFEXITED(parser->status))
				g_terminate_program = WEXITSTATUS(parser->status);
			else
				g_terminate_program = 1;
		}
		if (parser->token)
			ft_check_builtin(parser->token, parser, parser->envp_p);
	}
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
