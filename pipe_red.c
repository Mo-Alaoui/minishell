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

int	wait_loop2(t_norm1 *norm1)
{
	norm1->line = readline("heredoc> ");
	if (wait_loop1(norm1->line, norm1->heredoc_delim) == 1)
		return (1);
	write(norm1->heredoc_fd[1], norm1->line, ft_strlen(norm1->line));
	write(norm1->heredoc_fd[1], "\n", 1);
	free(norm1->line);
	return (0);
}

int	wait_loop(char **segment , t_gc *gc)
{
	int		s;
	t_norm1	*norm1;
	norm1 = gc_malloc(gc,sizeof(t_norm1));
	norm1->last_heredoc_fd = -1;
	s = 0;
	while (segment[s])
	{
		if (ft_strcmp(segment[s], "'<<'") == 0 && segment[s + 1])
		{
			if (pipe(norm1->heredoc_fd) == -1)
				error();
			norm1->heredoc_delim = segment[s + 1];
			while (1)
			{
				if (wait_loop2(norm1) == 1)
					break ;
			}
			norm1->last_heredoc_fd = ft_close(norm1->last_heredoc_fd,
					norm1->heredoc_fd);
			s += 1;
		}
		s++;
	}
	return (norm1->last_heredoc_fd);
}

int	ft_ft5(char **tokens, t_all *parser, t_norm *norm)
{
	int	last_heredoc_fd;

	last_heredoc_fd = -1;
	norm->j = norm->k;
	while (tokens[norm->j] && ft_strcmp(tokens[norm->j], "'|'") != 0)
		norm->j++;
	parser->segment = ft_subarray(tokens, norm->k, norm->j, &parser->gc);
	parser->clean = remove_redir_tokens(parser->segment, &parser->gc);
	parser->joined = ft_join_with_space(parser->clean);
	last_heredoc_fd = wait_loop(parser->segment, &parser->gc);
	if (pipe(norm->fd) == -1)
		error();
	norm->pid = fork();
	if (norm->pid == -1)
		error();
	return (last_heredoc_fd);
}

void	ft_child2(char **tokens, t_all *parser, int last_heredoc_fd,
		t_norm *norm)
{
	ft_helper(parser->segment);
	ft_helper1(parser->segment);
	if (last_heredoc_fd != -1)
		dup2(last_heredoc_fd, 0);
	if (norm->prev_fd != -1)
	{
		dup2(norm->prev_fd, 0);
		close(norm->prev_fd);
	}
	if (tokens[norm->j])
		dup2(norm->fd[1], 1);
	close(norm->fd[0]);
	close(norm->fd[1]);
	if (last_heredoc_fd != 1)
		close(last_heredoc_fd);
}

int	if_its_pipe_red(char **tokens, t_list *new_pip, t_all *parser, char **envp)
{
	t_norm	*norm;
	norm = gc_malloc(&parser->gc,sizeof(t_norm));
	init(norm, new_pip, 0, tokens, &parser->gc);
	while (tokens[norm->k])
	{
		norm->last_heredoc_fd = ft_ft5(tokens, parser, norm);
		if (norm->pid == 0)
		{
			ft_child2(tokens, parser, norm->last_heredoc_fd, norm);
			ft_execute(parser->joined, parser->clean, parser, envp);
		}
		norm->pids[norm->i++] = norm->pid;
		if (norm->prev_fd != -1)
			close(norm->prev_fd);
		if (norm->last_heredoc_fd != 1)
			close(norm->last_heredoc_fd);
		close(norm->fd[1]);
		norm->prev_fd = norm->fd[0];
		if (tokens[norm->j])
			norm->k = norm->j + 1;
		else
			norm->k = norm->j;
	}
	return (ft_stor_status(norm->pids, norm->i));
}
