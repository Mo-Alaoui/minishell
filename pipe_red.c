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

char *check_herdoc1(char **segment)
{
		char *heredoc_delim = NULL;
		int i;
		i = 0;
		while(segment[i])
			i++;
		i--;
		while(i >= 0)
		{
			if((ft_strcmp(segment[i], "'<<'")) == 0)
			{
				heredoc_delim = segment[i + 1];
				break;
			}
			i--;
		}
		return (heredoc_delim);
}

void wait_loop(char *line , char *heredoc_delim , int heredoc_fd[2])
{
	pipe(heredoc_fd);
	while(1)
	{
		line = readline("heredoc> ");
		if(!line || ft_strcmp(line, heredoc_delim) == 0)
		{
			free(line);
			break;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
	close(heredoc_fd[1]);
}

int ft_len(char **s)
{
    int i;
    i = 0 ;
    while(s[i])
        i++;
    return (i);
}

int if_its_pipe_red(char **tokens, t_variables *env, t_variables *local_env, t_history *history, char **envp)
{
	int fd[2];
	int heredoc_fd[2];
	int has_herdoc ;
	int status ;
	int last_status ;
	char *line = NULL;
	char *heredoc_delim ;
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
		has_herdoc = 0;   
		j = i;
		while (tokens[j] && strcmp(tokens[j], "'|'") != 0)
			j++;
		char **segment = ft_subarray(tokens, i, j);
		char **cleaned = remove_redir_tokens(segment);
		char *joined = ft_join_with_space(cleaned);
		heredoc_delim = check_herdoc1(segment);
		if(heredoc_delim != NULL)
			has_herdoc = 1;
		if(has_herdoc)
			wait_loop(line, heredoc_delim, heredoc_fd);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
            ft_helper(tokens);
            ft_helper1(tokens);
			if (has_herdoc)
        		dup2(heredoc_fd[0], 0);
			if (prev_fd != -1 && !has_herdoc)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (tokens[j])
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if (has_herdoc)
				close(heredoc_fd[0]); 
			ft_execute(joined , cleaned, env, local_env, history, envp);
		}
		pids[k++] = pid ;
		if (prev_fd != -1)
			close(prev_fd);
		if (has_herdoc)
			close(heredoc_fd[0]);
		close(fd[1]);
		prev_fd = fd[0];
		free(joined);

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
