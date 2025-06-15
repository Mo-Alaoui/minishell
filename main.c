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

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
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
		{
			if (flag != 0)
				ft_execute(parser->joined, token, parser, envp);
			else
				ft_execute(parser->new_her->content, token, parser, envp);
		}
		else if (check_red(token) == 1)
		{
			if (flag != 0)
				ft_execute(parser->joined, token, parser, envp);
			else
				ft_execute(parser->new_red_in->content, token, parser, envp);
		}
		else if (check_red(token) == 2)
		{
			if (flag != 0)
				ft_execute(parser->joined, parser->clean, parser, envp);
			else
				ft_execute(parser->new_red_out->content, parser->clean, parser,
					envp);
		}
		else if (check_red(token) == 3)
		{
			if (flag != 0)
				ft_execute(parser->joined, parser->clean, parser, envp);
			else
				ft_execute(parser->new_red_outA->content, parser->clean, parser,
					envp);
		}
		else if (check_red(token) == 4)
		{
			if (flag != 0)
				ft_execute(parser->joined, parser->clean, parser, envp);
			else
				ft_execute(parser->new_in_out->content, parser->clean, parser,
					envp);
		}
		else
		{
			if (ft_strcmp(token[0], "exit") == 0)
				exit(0);
			ft_execute(parser->new_pip->content, parser->clean, parser, envp);
		}
	}
}
void	ft_ft(char *check)
{
	int	i;

	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	i = 0;
	while (check[i] != 0)
	{
		if (check[i] == '\'')
			i++;
		if (check[i] == 0)
			break ;
		write(2, &check[i], 1);
		i++;
	}
	write(2, "\n", 1);
}
void	ft_propt(char **envp)
{
	pid_t	pid;
	t_all	*parser;
	char	**token;
	char	*input;
	int		flag;
	char	**envp_p;
	int		i;
	int		status;
	char	*check;

	flag = 0;
	status = 0;
	parser = malloc(sizeof(t_all));
	parser->history = init_history();
	parser->env = init_env_variables(envp);
	envp_p = variables_to_array(parser->env);
	while (1)
	{
		input = readline("minishell>$ ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		if (is_only_spaces(input))
			continue ;
		if (*input)
		{
			add_history(input);
			add_to_history(parser->history, input);
			token = ft_tokenize(input);
			i = 0;
			while (token[i])
			{
				token[i] = handel_quotes(token[i], parser->env,
						parser->local_env);
				i++;
			}
			check = is_valid_input(token);
			if (check != NULL)
			{
				ft_ft(check);
				g_terminate_program = 2;
				continue ;
			}
			flag = check_parser(token);
			init_all(parser, token);
			parser->local_env = ft_check_export(token, parser->env);
			pid = fork();
			if (pid == 0)
				ft_child(parser, token, flag, envp_p);
			else
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				signal(SIGINT, sigint_handler);
			}
			if (WIFEXITED(status))
				g_terminate_program = WEXITSTATUS(status);
			else
				g_terminate_program = 1;
		}
		if (ft_strcmp(token[0], "exit") == 0)
			run_builtin_funciton(token, &parser->env, &parser->local_env);
		if (ft_strcmp(token[0], "exit") == 0 && token[1] != NULL
			&& ft_strcmp(token[1], "'|'"))
			run_builtin_funciton(token, &parser->env, &parser->env);
	}
	ft_lstclear(&parser->new_pip, free);
	free_history(parser->history);
	free_char_array(token);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	setup_signals();
	ft_propt(envp);
	return (0);
}
