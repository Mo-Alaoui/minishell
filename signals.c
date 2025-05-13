#include "minishell.h"

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

void ft_propt(char **envp)
{
    int i;
    t_variables *env;
    t_variables *local_env;
    t_history *history;
    t_list *new;
    pid_t pid;
    char **token;
    char *var_name;
    history = init_history();
    env = init_env_variables(envp);

    while (1)
    {
        char *input;

        input = readline("minishell$ ");
        if (!input || ft_strcmp(input, "exit") == 0)
        {
            if (ft_strcmp(input, "exit") == 0)
            {
                free_history(history);
                free_char_array(token);
                printf("exit\n");
                exit(0);
            }
            printf("exit\n");
            break;
        }

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
            }
        }
        free(input); 
    }

    free_history(history);
    free_char_array(token);
}
