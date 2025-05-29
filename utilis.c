#include "minishell.h"

t_all *init_all(char **token)
{
    t_all *parser = malloc(sizeof(t_all));
    if (!parser)
        return NULL;
    parser->clean = remove_redir_tokens(token);
    parser->joined = ft_join_with_space(parser->clean);
    parser->new_pip = ft_parser(token, "|");
    parser->new_her = ft_parser(token, "<<");
    parser->new_red_in = ft_parser(token, "<");
    parser->new_red_out = ft_parser(token, ">");
    parser->new_red_outA = ft_parser(token, ">>");
    parser->new_in_out = ft_parser2(token);
    return parser;
}

void free_char_array(char **ptr)
{
    int i = 0;

    if (!ptr)
        return;
    while (ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}

int check_his(char *token, t_history *history)
{
   if(ft_strcmp(token, "history") == 0)
   {
        print_history(history);
        return (1);
   }
   return (0);
}

int redirect_input(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open input");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2 input");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int redirect_output(const char *filename, int append)
{
    int fd;
    
    if (append)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open output");
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

int is_directory(const char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) == 0)
		return S_ISDIR(path_stat.st_mode);
	return 0;
}