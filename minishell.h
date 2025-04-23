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

t_history	*init_history(void);
int			ft_strcmp(char *s1, char *s2);
void		add_to_history(t_history *history, char *line);
void		print_history(t_history *history);
void		free_history(t_history *history);
void sigint_handler(int sig);
void setup_signals(void);
void ft_propt(void);

void free_char_array(char **tokens);
char **ft_tokenize(const char *input);

#endif
