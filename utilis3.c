/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:06:47 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/20 19:06:48 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close(int last_heredoc_fd, int *heredoc_fd)
{
	close(heredoc_fd[1]);
	if (last_heredoc_fd != -1)
		close(last_heredoc_fd);
	last_heredoc_fd = heredoc_fd[0];
	return (last_heredoc_fd);
}

char	**force_quote(char **token, t_all *parser)
{
	int	i;

	i = 0;
	while (token[i])
	{
		token[i] = handel_quotes(token[i], parser->env);
		i++;
	}
	return (token);
}

void	error(void)
{
	perror("error found");
	exit(1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		free(str[i++]);
	free(str);
}

void	ft_seg(pid_t pid, t_all *parser)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &parser->status, 0);
	signal(SIGINT, sigint_handler);
}
