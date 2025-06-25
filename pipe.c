/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:07:22 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/25 14:59:25 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child1(t_list *new_pip, int prev_fd, int *fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (new_pip->next)
	{
		dup2(fd[1], 1);
	}
	close(fd[0]);
	close(fd[1]);
}

int	ft_stor_status(int *pids, int i)
{
	int	j;
	int	status;
	int	last_status;

	j = 0;
	while (j <= i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else
			last_status = 1;
		j++;
	}
	return (last_status);
}

void	init(t_norm *norm, t_list *new_pip, int flag, char **tokens)
{
	if (flag == 1)
	{
		norm->pids = malloc(sizeof(ft_lstsize(new_pip)));
	}
	else
	{
		norm->pids = malloc(sizeof(ft_total_strings(tokens)));
	}
	norm->last_heredoc_fd = -1;
	norm->prev_fd = -1;
	norm->i = 0;
	norm->j = 0;
	norm->k = 0;
}

void	ft_ft4(char **token, t_all *parser, t_norm *norm)
{
	norm->j = norm->k;
	while (token[norm->j] && ft_strcmp(token[norm->j], "'|'") != 0)
		norm->j++;
	parser->segment = ft_subarray(token, norm->k, norm->j);
	parser->clean = remove_redir_tokens(parser->segment);
	if (pipe(norm->fd) == -1)
		error();
	norm->pid = fork();
	if (norm->pid == -1)
		error();
}

int	if_its_pipe(t_list *new_pip, char **token, t_all *parser, char **envp)
{
	t_norm	*norm;

	norm = ft_malloc(sizeof(t_norm), 'A');
	init(norm, new_pip, 1, token);
	while (new_pip)
	{
		ft_ft4(token, parser, norm);
		if (norm->pid == 0)
		{
			ft_child1(new_pip, norm->prev_fd, norm->fd);
			ft_execute(new_pip->content, parser->clean, parser, envp);
		}
		norm->pids[norm->i++] = norm->pid;
		if (norm->prev_fd != -1)
			close(norm->prev_fd);
		close(norm->fd[1]);
		norm->prev_fd = norm->fd[0];
		new_pip = new_pip->next;
		if (token[norm->j])
			norm->k = norm->j + 1;
		else
			norm->k = norm->j;
	}
	return (ft_stor_status(norm->pids, norm->i));
}
