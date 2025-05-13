#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
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

typedef struct s_variables
{
    char *variable_name;
    char *value;
    struct s_variables *next;
}   t_variables;

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

int redirect_input(const char *filename);
int redirect_output(const char *filename, int append);


// builtin functions
/* void exit() */
void ft_pwd(void);
int ft_cd(const char *path);
void print_array_char(const char **arr);
void ft_env(t_variables **env);
void ft_export(t_variables **env, t_variables **local_env, char *command);
void ft_unset(t_variables **env, char **name);
void ft_echo(char **arg, t_variables **env, t_variables **local_env);


// env_var funciton
void free_env_variables(t_variables *env_list);
t_variables *init_env_variables(char **envp);
char *get_env_variable(t_variables *env_list, char *name);
int add_variable(t_variables **env_list, char *input);
t_variables *add_new_var(char *input);
int is_valid_var_name(char *name);
int is_alnum_underscore(char c);
int is_alpha(char c);
char *variable_value(char *input);
char *var_name(char *input);


// utilis_builtin
char *get_string_before_char(const char *input_str, char c);
void run_builtin_funciton(char **command, t_variables **env, t_variables **local_env);
int is_builtin_functions(char *str);

#endif
