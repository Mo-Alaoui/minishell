/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:54:46 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/21 15:42:26 by mohalaou         ###   ########.fr       */
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

void    ft_for_leaks(t_all *parser, char **token)
{
    printf("\n=========================================================\n");
    printf("the fucntion ft_for_leaks runs\n");
    printf("\n=========================================================\n");

    if (parser->new_pip)
        ft_lstclear(&parser->new_pip, free);
    if (parser->new_her)
        ft_lstclear(&parser->new_her, free);
    if (parser->new_red_in)
        ft_lstclear(&parser->new_red_in, free);
    if (parser->new_red_out)
        ft_lstclear(&parser->new_red_out, free);
    if (parser->new_red_out_a)
        ft_lstclear(&parser->new_red_out_a, free);
    if (parser->new_in_out)
        ft_lstclear(&parser->new_in_out, free);
    if (parser->clean)
        free_char_array(parser->clean);
    if (parser->segment)
        free_char_array(parser->segment);
    if (parser->joined)
        free(parser->joined);
    if (parser->token)
        free_char_array(token);
    if (parser->input)
        free(parser->input);
    
    if (parser->envp_p)
        free_char_array(parser->envp_p);
    
    if (parser->env)
        free_env_variables(parser->env);
    if (parser->local_env)
        free_env_variables(parser->local_env);
        
    //ft_lstclear(&parser->new_pip, free);
    free_history(parser->history);
}

int	ft_ver(t_all *parser)
{
	if (!parser->input)
	{
		printf("exit\n");
		ft_for_leaks(parser, parser->token);
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
		run_builtin_function(token, &parser->env, &parser->local_env);
	if ((ft_strcmp(token[0], "exit") == 0 && token[1] == NULL)
		|| (ft_strcmp(token[0], "unset") == 0 && check_input_type(token) == 0))
	{
		run_builtin_function(token, &parser->env, &parser->local_env);
			ft_for_leaks(parser, parser->token);
		if ((ft_strcmp(token[0], "unset") == 0 && check_input_type(token) == 0))
			envp_p = variables_to_array(parser->env);
			
	}
	if (ft_strcmp(token[0], "exit") == 0 && token[1] != NULL
		&& ft_strcmp(token[1], "'|'"))
		run_builtin_function(token, &parser->env, &parser->env);
			ft_for_leaks(parser, parser->token);
}
