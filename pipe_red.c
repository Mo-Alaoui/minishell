#include "minishell.h"

char **ft_subarray(char **tokens, int start, int end)
{
	char **sub = malloc(sizeof(char *) * (end - start + 1));
	int i = 0;
	while (start < end)
		sub[i++] = ft_strdup(tokens[start++]);
	sub[i] = NULL;
	return sub;
}

char *ft_join_with_space(char **tokens)
{
	char *res = ft_strdup("");
	char *tmp;
	int  i = 0;
	while(tokens[i])
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
	return res;
}

char **remove_redir_tokens(char **tokens)
{
	int count;
	char **args ;
	int  i ;
	int j;
	count = 0;
	i = 0;
	while(tokens[i])
	{
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0 || strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
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
		if (strcmp(tokens[i], "'<'") == 0 || strcmp(tokens[i], "'<<'") == 0 || strcmp(tokens[i], "'>'") == 0 || strcmp(tokens[i], "'>>'") == 0)
			i++;
		else
			args[j++] = ft_strdup(tokens[i]);
	i++;
	}
	args[j] = NULL;
	return args;
}

int wait_loop(char **segment)
{
			int s ;
			char *line;
			char *heredoc_delim ;
			int heredoc_fd[2];
			int last_heredoc_fd = -1;
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
							break;
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

int if_its_pipe_red(char **tokens, t_all *parser, char **envp)
{
	int fd[2];
	int status ;
	int last_heredoc_fd = -1;
	int last_status ;
	int prev_fd = -1;
	pid_t pid;
	int pids[ft_len(tokens)];
	int i ;
	int  k ;
	int j;
	i = 0;
	k = 0;
	last_status = 0;
	while (tokens[i])
	{  
		j = i;
		while (tokens[j] && strcmp(tokens[j], "'|'") != 0)
			j++;
		parser->segment = ft_subarray(tokens, i, j);
		parser->clean = remove_redir_tokens(parser->segment);
		parser->joined = ft_join_with_space(parser->clean);
		last_heredoc_fd = wait_loop(parser->segment);
		if(pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == 0)
		{
            ft_helper(tokens);
            ft_helper1(tokens);
			if (last_heredoc_fd != -1)
				dup2(last_heredoc_fd, 0);
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (tokens[j])
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if (last_heredoc_fd != 1)
				close(last_heredoc_fd); 
			ft_execute(parser->joined , parser->clean, parser, envp);
		}
		pids[k++] = pid ;
		if (prev_fd != -1)
			close(prev_fd);
		if (last_heredoc_fd != 1)
			close(last_heredoc_fd);
		close(fd[1]);
		prev_fd = fd[0];
		free(parser->joined);
		free_char_array(parser->segment);
		free_char_array(parser->clean);

		if (tokens[j])
			i = j + 1;
		else
			i = j;
	}
	j = 0;
    while (j <= k)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        else
            last_status = 1;
    j++;
    }
    return (last_status);
} 
