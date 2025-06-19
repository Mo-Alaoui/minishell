/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:54:46 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/19 16:54:48 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	ft_for_leaks(t_all *parser, char **token)
{
	ft_lstclear(&parser->new_pip, free);
	free_history(parser->history);
	free_char_array(token);
}
int	ft_ver(t_all *parser)
{
	if (!parser->input)
	{
		printf("exit\n");
		printf("hna ah\n");
		exit(0);
	}
	if (is_only_spaces(parser->input))
		return (1);
	return (0);
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
void	ft_check_builtin(char **token, t_all *parser, char **envp_p)
{
	if (ft_strcmp(token[0], "cd") == 0 && check_input_type(token) == 0)
		run_builtin_funciton(token, &parser->env, &parser->local_env);
	if ((ft_strcmp(token[0], "exit") == 0 && token[1] == NULL) || (ft_strcmp(token[0], "unset") == 0
			&& check_input_type(token) == 0))
	{
		run_builtin_funciton(token, &parser->env, &parser->local_env);
		if ((ft_strcmp(token[0], "unset") == 0 && check_input_type(token) == 0))
			envp_p = variables_to_array(parser->env);
	}
	if (ft_strcmp(token[0], "exit") == 0 && token[1] != NULL
		&& ft_strcmp(token[1], "'|'"))
		run_builtin_funciton(token, &parser->env, &parser->env);
}
char	**force_quote(char **token, t_all *parser)
{
	int	i;

	i = 0;
	while (token[i])
	{
		token[i] = handel_quotes(token[i], parser->env, parser->local_env);
		i++;
	}
	return (token);
}
