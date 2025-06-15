#include "minishell.h"

char	**ft_subarray(char **tokens, int start, int end)
{
	char	**sub;
	int		i;

	sub = malloc(sizeof(char *) * (end - start + 1));
	i = 0;
	while (start < end)
		sub[i++] = ft_strdup(tokens[start++]);
	sub[i] = NULL;
	return (sub);
}

char	*ft_join_with_space(char **tokens)
{
	char	*res;
	char	*tmp;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (tokens[i])
	{
		tmp = res;
		res = ft_strjoin(res, tokens[i]);
		free(tmp);
		if (tokens[i + 1])
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
		}
		i++;
	}
	return (res);
}

char	**remove_redir_tokens(char **tokens)
{
	int		count;
	char	**args;
	int		i;
	int		j;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0
			|| strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
			i++;
		else
			count++;
		i++;
	}
	args = malloc(sizeof(char *) * (count + 1));
	j = 0;
	i = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0
			|| strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
			i++;
		else
			args[j++] = ft_strdup(tokens[i]);
		i++;
	}
	args[j] = NULL;
	return (args);
}

int	wait_loop(char **segment)
{
	int		s;
	char	*line;
	char	*heredoc_delim;
	int		heredoc_fd[2];
	int		last_heredoc_fd;

	last_heredoc_fd = -1;
	s = 0;
	while (segment[s])
	{
		if (ft_strcmp(segment[s], "'<<'") == 0 && segment[s + 1])
		{
			if (pipe(heredoc_fd) == -1)
				error();
			heredoc_delim = segment[s + 1];
			while (1)
			{
				line = readline("heredoc> ");
				if (!line || ft_strcmp(line, heredoc_delim) == 0)
				{
					free(line);
					break ;
				}
				write(heredoc_fd[1], line, ft_strlen(line));
				write(heredoc_fd[1], "\n", 1);
				free(line);
			}
			close(heredoc_fd[1]);
			if (last_heredoc_fd != -1)
				close(last_heredoc_fd);
			last_heredoc_fd = heredoc_fd[0];
			s += 1;
		}
		s++;
	}
	return (last_heredoc_fd);
}

int	ft_ft5(char **tokens, t_all *parser, t_norm *norm)
{
	int	last_heredoc_fd;

	last_heredoc_fd = -1;
	norm->j = norm->k;
	while (tokens[norm->j] && ft_strcmp(tokens[norm->j], "'|'") != 0)
		norm->j++;
	parser->segment = ft_subarray(tokens, norm->k, norm->j);
	parser->clean = remove_redir_tokens(parser->segment);
	parser->joined = ft_join_with_space(parser->clean);
	last_heredoc_fd = wait_loop(parser->segment);
	if (pipe(norm->fd) == -1)
		error();
	norm->pid = fork();
	if (norm->pid == -1)
		error();
	return (last_heredoc_fd);
}

void	ft_child2(char **tokens, int last_heredoc_fd, t_norm *norm)
{
	ft_helper(tokens);
	ft_helper1(tokens);
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

	norm = malloc(sizeof(t_norm));
	init(norm, new_pip, 0, tokens);
	while (tokens[norm->k])
	{
		norm->last_heredoc_fd = ft_ft5(tokens, parser, norm);
		if (norm->pid == 0)
		{
			ft_child2(tokens, norm->last_heredoc_fd, norm);
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
