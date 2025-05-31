#include "minishell.h"

int g_terminate_program = 0;

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

t_variables *ft_check_export(char **token, t_variables *env)
{
    char *var_name ;
    t_variables *local_env = NULL;
    int i ;
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
    if (var_name == NULL)
        return (NULL);
    return (local_env);
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
    pid_t pid ;
    t_variables *env;
    t_variables *local_env;
    t_history *history;
    t_all *parser ;
    char  **token ;
    int flag;
    int i;
    int status = 0;
    char *check;
    history = init_history();
    env = init_env_variables(envp);
    while (1)
    {
        char *input ;
        input = readline("minishell>$ ");
        if (!input )
        {
            printf("exit\n");
            exit(0);
        }
        if (is_only_spaces(input))
            continue;
        if (*input)
        {
            add_history(input);
            add_to_history(history, input);
            token = ft_tokenize(input);
            i = 0;
            while(token[i])
            {
                token[i] = handel_quotes(token[i], env, local_env);
                i++;
            }
            check = is_valid_input(token);
            if(check != NULL)
            {
                write(2,"minishell: syntax error near unexpected token ",46);
                i = 0;
                while(check[i] != 0)
                {
                    if(check[i] == '\'')
                        i++;
                    write(2,&check[i],1);
                i++;
                }
                write(2,"\n",1);
                g_terminate_program = 2;
                continue;
            }
            flag = check_parser(token);
            parser = init_all(token);
            local_env = ft_check_export(token, env);
            pid = fork();
            if(pid == 0)
            {
                if(check_input_type(token) == 3)
                    exit(if_its_pipe_red(token, env, local_env, history,envp));
                if(check_input_type(token) == 2)
                    exit(if_its_pipe(parser->new_pip, token, env, local_env, history, envp));
                if(check_input_type(token) == 0)
                {
                    printf("-> 3 hna\n");
                    if(check_herdoc(token, envp) == 1)
                    {
                       if(flag != 0)
                            ft_execute(parser->joined, token, env, local_env, history, envp);
                        else
                            ft_execute(parser->new_her->content, token, env, local_env, history, envp);
                    }
                    else if(check_red(token) == 1)
                    {
                        if(flag != 0)
                            ft_execute(parser->joined, token, env, local_env, history, envp);
                        else
                            ft_execute(parser->new_red_in->content, token, env, local_env, history, envp);
                    }
                    else if(check_red(token) == 2)
                    {
                        if(flag != 0)
                            ft_execute(parser->joined, parser->clean, env, local_env, history, envp);
                        else
                            ft_execute(parser->new_red_out->content, parser->clean, env, local_env, history, envp);
                    }
                    else if(check_red(token) == 3)
                    {
                        if(flag != 0)
                            ft_execute(parser->joined, parser->clean, env, local_env, history, envp);
                        else
                            ft_execute(parser->new_red_outA->content, parser->clean, env, local_env, history, envp);
                    }
                    else if(check_red(token) == 4)
                    {
                        if(flag != 0)
                            ft_execute(parser->joined, parser->clean, env, local_env, history, envp);
                        else
                            ft_execute(parser->new_in_out->content,  parser->clean, env, local_env, history, envp);
                    }
                    else
                    {
                        if(ft_strcmp(token[0], "exit") == 0)
                            exit(0);
                        ft_execute(parser->new_pip->content, token, env, local_env, history, envp);
                    }
                }
            }
            else
                waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                g_terminate_program = WEXITSTATUS(status);
            else
                g_terminate_program = 1;
        }
        if(ft_strcmp(token[0], "exit") == 0)
            run_builtin_funciton(token, &env, &local_env);
    }
    ft_lstclear(&parser->new_pip, free);
    free_history(history);
    free_char_array(token);
}

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    setup_signals();
    ft_propt(envp);
    return 0;
}
