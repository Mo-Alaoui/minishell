#include "minishell.h"

int check_herdoc(char **toknize, char **envp)
{
    (void) envp;
    int i = 0;
    char *line;
    char *delimiter;
    int fd[2];
    int last_fd ;
    last_fd = -1;

    while (toknize[i])
    {
        if (ft_strcmp(toknize[i], "'<<'") == 0 && toknize[i + 1])
        {
            if (pipe(fd) == -1)
                return (1);

            char *delimiter = toknize[i + 1];

            while (1)
            {
                line = readline("heredoc> ");
                if (!line || ft_strcmp(line, delimiter) == 0)
                {
                    free(line);
                    break;
                }
                write(fd[1], line, ft_strlen(line));
                write(fd[1], "\n", 1);
                free(line);
            }
            close(fd[1]);
            if (last_fd != -1)
                close(last_fd);

           
            last_fd = fd[0];

            i += 1;
        }
    i++;
    }
    i = 0;
    while(toknize[i])
        i++;
    i--;
    while(i >= 0)
    {
            if(ft_strcmp(toknize[i], "'>'") == 0 || ft_strcmp(toknize[i], "'>>'") == 0)
            {
                redirect_output(toknize[i + 1], 0);
                break;
            }
    i--;
    }
    // Connect last heredoc pipe to stdin
    if (last_fd != -1)
    {
        dup2(last_fd, STDIN_FILENO);
        close(last_fd);
        return 1;
    }
    return 0;
}

int check_red(char **tokenize)
{
    int i ;
    int j ;
    i = 0;
    while(tokenize[i])
    {
        if(ft_strcmp(tokenize[i] ,"'<'") == 0)
        {
            redirect_input(tokenize[i + 1]);
            j = i;
            while(tokenize[j])
            {
                if(ft_strcmp(tokenize[j], "'>'") == 0)
                {
                    redirect_output(tokenize[j + 1], 0);
                    return (4);
                }
                else if(ft_strcmp(tokenize[j], "'>>'") == 0)
                {
                    redirect_output(tokenize[j + 1] , 1);
                    return (4);
                }
                j++;
            }
            return (1);
        }
        else if(ft_strcmp(tokenize[i], "'>'") == 0)
        {
            while(tokenize[i])
                i++;
            i--;
            while(i >= 0)
            {
                if(ft_strcmp(tokenize[i], "'>'") == 0)
                {
                    redirect_output(tokenize[i + 1], 0);
                    break;
                }
            i--;
            }
            return (2);
        }
        else if(ft_strcmp(tokenize[i], "'>>'") == 0)
        {
            redirect_output(tokenize[i + 1], 1);
            return (3);
        }
    i++;
    }
return (0);
}

int check_parser(char **token)
{
    if(ft_strcmp(token[0] , "'<'") ||  ft_strcmp(token[0] , "'>'") || ft_strcmp(token[0] , "'>>'"))
        return (-1) ;
    else
        return (0);
}