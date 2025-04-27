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

void ft_propt(char **envp)
{
    t_list *new ;
    int i ;
    t_history *history;
    char **token;
    pid_t pid ;
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
            add_history(input);
            add_to_history(history, input);
            token = ft_tokenize(input);
            pid = fork();
            if(pid == 0)
               ft_execute(input, history, envp);
            else 
               waitpid(pid, NULL, 0);

            new = ft_parser(token);
            i = 0;
            while(new)
            {
              printf("%s\n", new->content);
              new = new->next;
            }
        }
        free(input); 
    }

    free_history(history);
    free_char_array(token);
}
