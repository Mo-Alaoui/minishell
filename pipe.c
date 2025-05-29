#include "minishell.h"

int if_its_pipe(t_list *new_pip,char **token,  t_variables *env, t_variables *local_env, t_history *history, char **envp)
{
    int fd[2];
    int i ;
    int  j;
    int k ;
    int prev_fd = -1;
    pid_t pid;
    int status ;
    char **segment;
    int last_status ;
    last_status = 0;
    int pids[ft_lstsize(new_pip)];
    i = 0;
    j = 0;
    k = 0;
    while (new_pip)
    {
        j = k;
		while (token[j] && strcmp(token[j], "|") != 0)
			j++;
		segment = ft_subarray(token, k, j);
        pipe(fd);
        pid = fork();
        if (pid == 0)
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
            ft_execute(new_pip->content, segment, env, local_env, history, envp);
        }
        pids[i++] = pid;
        if (prev_fd != -1)
            close(prev_fd); 
        close(fd[1]);       
        prev_fd = fd[0];    
        new_pip = new_pip->next;
        if (token[j])
			k = j + 1;
		else
			k = j;
    }
    j = 0;
    while (j <= i)
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

int check_input_type(char **token)
{
    int has_pipe = 0;
    int has_redir = 0;
    int i = 0;

    while (token[i])
    {
        if (ft_strcmp(token[i], "|") == 0)
            has_pipe = 1;
        else if (
            ft_strcmp(token[i], "<") == 0 ||
            ft_strcmp(token[i], "<<") == 0 ||
            ft_strcmp(token[i], ">") == 0 ||
            ft_strcmp(token[i], ">>") == 0
        )
            has_redir = 1;
        i++;
    }

    if (has_pipe && has_redir)
        return 3; // pipes + redirections
    else if (has_pipe)
        return 2; // only pipes
    else if (has_redir)
        return 0; // only redirection
    return 0;     // pure command with no pipe/redir
}

void ft_helper1(char **token)
{
    int i = 0 ;
    while(token[i])
    {
        if(ft_strcmp(token[i], ">") == 0)
            redirect_output(token[i + 1], 0);
        if(ft_strcmp(token[i], ">>") == 0)
            redirect_output(token[i + 1], 1);
        i++;
    }
}

void ft_helper(char **token)
{
    int i = 0 ;
    while(token[i])
    {
        if(ft_strcmp(token[i], "<") == 0)
            redirect_input(token[i + 1]);
        i++;
    }
}
