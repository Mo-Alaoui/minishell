/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:29:40 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/21 11:46:32 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call(t_all *parser, int flag, char **envp)
{
	if (flag != 0)
		ft_execute(parser->joined, parser->clean, parser, envp);
	else
		ft_execute(parser->new_her->content, parser->clean, parser, envp);
}

void	ft_call1(t_all *parser, int flag, char **envp)
{
	if (flag != 0)
		ft_execute(parser->joined, parser->clean, parser, envp);
	else
		ft_execute(parser->new_red_in->content, parser->clean, parser, envp);
}

void	ft_call2(t_all *parser, int flag, char **envp)
{
	if (flag != 0)
		ft_execute(parser->joined, parser->clean, parser, envp);
	else
		ft_execute(parser->new_red_out->content, parser->clean, parser, envp);
}

void	ft_call3(t_all *parser, int flag, char **envp)
{
	if (flag != 0)
		ft_execute(parser->joined, parser->clean, parser, envp);
	else
		ft_execute(parser->new_red_out_a->content, parser->clean, parser, envp);
}

void	ft_call4(t_all *parser, int flag, char **envp)
{
	if (flag != 0)
		ft_execute(parser->joined, parser->clean, parser, envp);
	else
		ft_execute(parser->new_in_out->content, parser->clean, parser, envp);
}
