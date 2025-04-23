#include "minishell.h"

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

void ft_propt(void)
{
    t_history *history;
    char **token;

    history = init_history();
    while (1)
    {
        char *input;

        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            int i ;
            add_history(input);
            add_to_history(history, input);
            token = ft_tokenize(input);
            
        }
        if(ft_strcmp(input,"history") == 0)
            print_history(history);
       // printf("You entered: %s\n", input);
        free(input); 
    }

    free_history(history);
    free_char_array(token);
}
