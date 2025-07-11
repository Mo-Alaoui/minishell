/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 23:39:48 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 17:10:40 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef G_VARS_H
#  define G_VARS_H

extern int				g_terminate_program;
# endif

typedef struct s_variables
{
	char				*variable_name;
	char				*value;
	struct s_variables	*next;
}						t_variables;

typedef struct s_split_variables
{
	int					i;
	int					start;
	int					ret_count;

}						t_split_variables;

typedef struct s_token_variables
{
	int					i;
	int					ri;
	char				*result;
}						t_token_variables;

typedef struct s_process_var
{
	char				*g_num_str;
	char				temp[256];
	char				*rep;
	int					j;
}						t_process_var;

typedef struct s_token_data
{
	char				quote_char;
	char				**tokens;
	int					token_count;
	int					in_quotes;
	int					start;
	int					i;
}						t_token_data;

typedef struct s_history
{
	char				**cmds;
	int					size;
	int					capacity;
}						t_history;

typedef struct s_all
{
	t_list				*new_pip;
	t_list				*new_her;
	t_list				*new_red_in;
	t_list				*new_red_out_a;
	t_list				*new_red_out;
	t_list				*new_in_out;
	char				**clean;
	char				*joined;
	char				**segment;
	char				**token;
	char				*input;
	char				**envp_p;
	int					flag;
	int					status;
	int					flag1;

	t_variables			*env;
	t_variables			*local_env;
	t_history			*history;
}						t_all;
// struct for pipes nourminette//
typedef struct s_norm
{
	int					fd[2];
	int					i;
	int					j;
	int					k;
	int					prev_fd;
	pid_t				pid;
	int					*pids;
	int					last_heredoc_fd;
}						t_norm;

typedef struct s_norm1
{
	char				*line;
	char				*heredoc_delim;
	int					heredoc_fd[2];
	int					last_heredoc_fd;

}						t_norm1;

int						check_red(char **tokenize);
int						redirect_output(const char *filename, int append);
int						redirect_input(char *filename);
int	check_herdoc(t_all *parser, char **toknize, char **envp);
void					ft_execute(char *argv, char **token, t_all *parser,
							char **envp);
void					ft_execute_2(char **token, char **envp);
int						check_his(char *token, t_history *history);
void					ft_child(t_all *parser, char **token, int flag,
							char **envp);
void					error(void);
char					*find_path(char *cmd, char **envp);
t_list					*ft_parser(char **tokenize, char *s);
t_list					*ft_parser2(char **tokenize);
t_history				*init_history(void);
int						ft_strcmp(char *s1, char *s2);
void					add_to_history(t_history *history, char *line);
void					print_history(t_history *history);
void					free_history(t_history *history);
void					sigint_handler(int sig);
void					setup_signals(void);
void					ft_propt(char **envp);
void					free_char_array(char **tokens);
char					**ft_tokenize(const char *input);

// handle_pipe//
void					init_all(t_all *parser, char **token);
int						if_its_pipe(t_list *new_pip, char **token,
							t_all *parser, char **envp);
char					**remove_redir_tokens(char **tokens);
int						check_parser(char **token);
int						if_its_pipe_red(char **tokens, t_list *new_pip,
							t_all *parser, char **envp);
// builtin functions//
void					ft_exit(char **args);
void					ft_pwd(void);
int						ft_cd(const char *path);
void					print_array_char(const char **arr);
char					**variables_to_array(t_variables *head);
void					ft_env(t_variables **env);
void					ft_export(t_variables **env, t_variables **local_env,
							char *command);
void					ft_unset(t_variables **env, char **name);
void					ft_echo(char **arg);

// env_var funciton //
void					free_env_variables(t_variables *env_list);
t_variables				*init_env_variables(char **envp);
char					*get_env_variable(t_variables *env_list, char *name);
int						add_variable(t_variables **env_list, char *input);
t_variables				*add_new_var(char *input);
int						is_valid_var_name(char *name);
int						is_alnum_underscore(char c);
int						is_alpha(char c);
char					*variable_value(char *input);
char					*var_name(char *input);

// utilis_builtin//
char					*get_string_before_char(const char *input_str, char c);
int						run_builtin_function(char **command, t_variables **env,
							t_variables **local_env);
int						is_builtin_functions(char *str);
t_variables				*ft_check_export(char **token, t_variables *env);
// valide_input//
char					*is_valid_input(char **tokens);
int						is_metachar(char *s);
int						is_metachar2(char *s);
int						is_directory(const char *path);
// quotes//
char					*handel_quotes(char *input, t_variables *env);
int						is_special_characters(char *str);
void					replacement_strings(char **words, t_variables *env);
char					*handel_special_characters(char *str);
char					*replace_token(const char *str, t_variables *env);
// for norminette ///
void					ft_ft(char *check);
int						ft_ft1(char **toknize, int last_fd);
int						ft_ft2(char **tokenize, int i, int flag);
int						ft_ft3(char **tokenize, int i);
void					ft_ft6(char **tokenize, int j);
int						ft_stor_status(int *pids, int i);
void					init(t_norm *norm, t_list *new_pip, int flag,
							char **tokens);
void					ft_ft4(char **token, t_all *parser, t_norm *norm);
void					ft_call(t_all *parser, int flag, char **envp);
void					ft_call1(t_all *parser, int flag, char **envp);
void					ft_call2(t_all *parser, int flag, char **envp);
void					ft_call3(t_all *parser, int flag, char **envp);
void					ft_call4(t_all *parser, int flag, char **envp);
char					**ft_runing(t_all *parser, char *input);
int						ft_ver(t_all *parser);
void					ft_for_leaks(t_all *parser, char **token);
void					ft_check_builtin(char **token, t_all *parser,
							char **envp_p);
int						get_size(const char *str, t_variables *env);
char					*join_strings(char **words);
void					add_token(t_token_data *data, const char *input,
							int start, int end);
void					process_token_character(const char *input,
							t_token_data *data);
void					sort_ascii(char **arr);
char					**ft_subarray(char **tokens, int start, int end);
char					*ft_join_with_space(char **tokens);
int						count_tok_size(char **tokens);
int						wait_loop1(char *line, char *heredoc_delim);
void					ft_seg(pid_t pid, t_all *parser);
int						ft_close(int last_heredoc_fd, int *heredoc_fd);
char					**force_quote(char **token, t_all *parser);
void					ft_free(char **str);
void					ft_helper(char **token);
void					ft_helper1(char **token);
int						check_input_type(char **token);
void					ft_init_init(t_all *parser, char **envp);
int	is_only_spaces(char *str);
void	ft_ex(char **cmd, int flag);

#endif
