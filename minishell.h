#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_token_data
{
    char quote_char;
    char **tokens;
    int token_count;
    int in_quotes;
    int start;
    int i;
}   t_token_data;

typedef struct s_history
{
	char **cmds;
	int size;
	int capacity;
}	t_history;

void	ft_execute(char *argv, t_history *history ,char **envp);
int check_his(char *token, t_history *history);
void	error(void);
void	ft_free(char **str);
char	*find_path(char *cmd, char **envp);
t_list *ft_parser(char **toknize);
t_history	*init_history(void);
int			ft_strcmp(char *s1, char *s2);
void		add_to_history(t_history *history, char *line);
void		print_history(t_history *history);
void		free_history(t_history *history);
void sigint_handler(int sig);
void setup_signals(void);
void ft_propt(char **envp);
void free_char_array(char **tokens);
char **ft_tokenize(const char *input);

#endif
