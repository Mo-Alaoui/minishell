/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:00:10 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 16:32:50 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_loop(char **toknize, int *fd, int i)
{
	int		last_fd;
	char	*delimiter;
	char	*line;

	if (pipe(fd) == -1)
		return (1);
	delimiter = toknize[i + 1];
	last_fd = -1;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			line = NULL;
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		line = NULL;
	}
	close(fd[1]);
	if (last_fd != -1)
		close(last_fd);
	last_fd = fd[0];
	return (last_fd);
}

int	check_herdoc(char **toknize, char **envp)
{
	int	i;
	int	fd[2];
	int	last_fd;

	(void)envp;
	last_fd = -1;
	i = 0;
	while (toknize[i])
	{
		if (ft_strcmp(toknize[i], "'<<'") == 0 && toknize[i + 1])
		{
			last_fd = ft_loop(toknize, fd, i);
			i += 1;
		}
		i++;
	}
	return (ft_ft1(toknize, last_fd));
}

int	check_red(char **tokenize)
{
	int	i;

	i = 0;
	while (tokenize[i])
	{
		if (ft_strcmp(tokenize[i], "'<'") == 0)
			return (ft_ft2(tokenize, i, 1));
		else if (ft_strcmp(tokenize[i], "'>'") == 0)
		{
			if (ft_ft2(tokenize, i, 0) == 4)
				return (2);
		}
		else if (ft_strcmp(tokenize[i], "'>>'") == 0)
		{
			if (ft_ft2(tokenize, i, 0) == 4)
				return (3);
		}
		i++;
	}
	return (0);
}

int	check_parser(char **token)
{
	if (ft_strcmp(token[0], "'<'") || ft_strcmp(token[0], "'>'")
		|| ft_strcmp(token[0], "'>>'"))
		return (-1);
	else
		return (0);
}
