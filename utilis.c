/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:55:23 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/21 11:46:32 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *parser, char **token)
{
	parser->flag = 0;
	parser->status = 0;
	parser->clean = remove_redir_tokens(token , &parser->gc);
	parser->joined = ft_join_with_space(parser->clean);
	parser->new_pip = ft_parser(token, "'|'");
	parser->new_her = ft_parser(token, "'<<'");
	parser->new_red_in = ft_parser(token, "'<'");
	parser->new_red_out = ft_parser(token, "'>'");
	parser->new_red_out_a = ft_parser(token, "'>>'");
	parser->new_in_out = ft_parser2(token);
}

void	free_char_array(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	check_his(char *token, t_history *history)
{
	if (ft_strcmp(token, "history") == 0)
	{
		print_history(history);
		return (1);
	}
	return (0);
}

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		ft_putendl_fd(filename, 2);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(fd);
		exit(1);
	}
	close(fd);
	return (0);
}

int	redirect_output(const char *filename, int append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		error();
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
