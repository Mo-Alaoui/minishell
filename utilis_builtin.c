#include "minishell.h"

int is_builtin_functions(char *str)
{
    if (  !ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) 
       || !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd")
       || !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
       || !ft_strncmp(str, "exit", 4)) 
    {
        return (1);
    }
     return (0);
}

int  run_builtin_funciton(char **command, t_variables **env, t_variables **local_env)
{
    if (ft_strcmp(command[0], "echo") == 0)
        ft_echo(command, env, local_env);
    else if (ft_strcmp(command[0], "cd") == 0)
        ft_cd(*(command + 1));
    else if (ft_strcmp(command[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command[0], "export") == 0)
    {
        if (command[1])
            ft_export(env, local_env, command[1]);
    }
    else if (ft_strcmp(command[0], "unset") == 0)
    {
        if (command[1])
            ft_unset(env, command);
    }
    else if (ft_strcmp(command[0], "env") == 0)
        ft_env(env);
    else if (ft_strcmp(command[0], "exit") == 0)
        ft_exit(command);
    else
        return(0);
    return(1);
}

char *get_string_before_char(const char *input_str, char c) 
{
    const char *pos;
    pos = ft_strchr(input_str, c);

    if (pos != NULL) 
    {
        size_t length;
        length = pos - input_str;
        char *result = (char *)malloc(length + 1);
        if (result != NULL)
        {
            ft_memcpy(result, input_str, length);
            result[length] = '\0';
        }
        return result;
    } 
    return (NULL);
}

int is_metachar2(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") ||
	        !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<") );
}

int is_metachar(char *s)
{
	return (!ft_strcmp(s, "|") || !ft_strcmp(s, "<") || !ft_strcmp(s, ">") ||
	        !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<") || !ft_strcmp(s, "&&") ||
	        !ft_strcmp(s, "||") || !ft_strcmp(s, "&") ||!ft_strcmp(s, ";") || !ft_strcmp(s, ";;"));
}
int is_character(char s)
{
    if(s == '>' || s == '<' ||  s == '&' || s == ';' || s == '|' || s == '(' || s == ')') 
    {
        return (1);
    }
    return (0);
	    
}

char *is_valid_input(char **tokens)
{
    int i ;
	if (!tokens || !tokens[0])
        return (tokens[0]);
	if ((tokens[1] == NULL && is_metachar2(tokens[0])))
        return ("newline");
    i = 0;
	while (tokens[i])
	{
		if (is_metachar(tokens[i]))
		{
			if (!tokens[i + 1])
				return (tokens[i]);
			if (is_metachar(tokens[i + 1]))
                return (tokens[i + 1]);
		}
        if(is_character(tokens[i][2]) == 1)
                return(tokens[i]);
        if((tokens[1] == NULL && is_character(tokens[0][0]) == 1))
                return(tokens[i]);
	i++;
	}
	return NULL; 
}
