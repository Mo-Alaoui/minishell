#include "minishell.h"
int g_terminate_program = 0;

void handel_redirection(char **token);

void sigint_handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    write(1, "\n", 1);
    rl_replace_line("",0);
    rl_redisplay();
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);  
}

int is_only_spaces(char *str)
{
    int i = 0;
    while (str[i] != '\0' )
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_propt(char **envp)
{
    int i;
    t_variables *env;
    t_variables *local_env = NULL;
    t_history *history;
    t_list *new = NULL;
    pid_t pid;
    char **token;
    char *var_name;
    history = init_history();
    env = init_env_variables(envp);

    while (1)
    {
        char *input;
        
        input = readline("minishell$ ");
        if (!input)
        {
            break;
        }
        
        if (is_only_spaces(input))
        continue;
        
        if (*input)
        {
            add_history(input);
            add_to_history(history, input);
            token = ft_tokenize(input);
            
            i = 0;
            while (token[i])
            {
                var_name = get_string_before_char(token[i], '=');
                if (var_name != NULL)
                {
                    if (ft_strcmp(token[0], "export") == 0 || get_env_variable(env, var_name) != NULL)
                        add_variable(&env, token[i]);                
                    add_variable(&local_env, token[i]); 
                }
                i++;
            } 
            
            i = 0;
            while(token[i])
            {
                token[i] = handel_quotes(token[i], env, local_env);
                i++;
            }

            if (is_builtin_functions(token[0]))
            {
                run_builtin_funciton(token, &env, &local_env);
            }
            else
            {
                pid = fork();
                if(pid == 0)
                    ft_execute(input, history, envp);
                else 
                    waitpid(pid, NULL, 0);

                new = ft_parser(token);
                if (!new)
                {
                    (void)new;
                }
            }
        }
        free(input); 
    }

    free_history(history);
    free_char_array(token);
}
