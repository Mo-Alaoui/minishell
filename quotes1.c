#include "minishell.h"

int ft_len(char **s)
{
    int i;
    i = 0 ;
    while(s[i])
        i++;
    return (i);
}

char *replace_token(const char *str, t_variables *env, t_variables *local_env) 
{
    // int final_size = get_size(str, env, local_env);
    int final_size = 2097152;

    char *result = (char *)malloc(final_size + 1);
    if (!result) 
        return NULL;

    int ri = 0;
    int i = 0;
    int j;
    while (str[i])
    {
        if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?') && !ft_isdigit(str[i + 1])) 
        {
            j = i + 1;
            
            if (str[j] == '?')
            {
                char *g_num_str = ft_itoa(g_terminate_program);
                int len = ft_strlen(g_num_str);
                ft_memcpy(result + ri, g_num_str, len);
                ri += len;
                i += 2;
                continue;
            }

            while (ft_isalnum(str[j]) || str[j] == '_')
                j++;

            char temp[256];
            ft_memcpy(temp, str + i + 1, j - i - 1);
            temp[j - i - 1] = '\0';


            char *rep;
            rep = get_env_variable(local_env, temp);
            if (!rep)
            {
                rep = get_env_variable(env, temp);
            }

            if (rep) 
            {
                int len = ft_strlen(rep);
                ft_memcpy(result + ri, rep, len);
                ri += len;
            } 
            i = j - 1;
        } 
        else 
        {
            result[ri++] = str[i];
        }
        i++;
    }
    result[ri] = '\0';
    return result;
}

int is_special_characters(char *str)
{
    if (!ft_strcmp(str, "$") || !ft_strcmp(str, "\\") || !ft_strcmp(str, "#") 
         || !ft_strcmp(str, "=") || !ft_strcmp(str, "[") || !ft_strcmp(str, "]") 
         || !ft_strcmp(str, "!") || !ft_strcmp(str, ">") || !ft_strcmp(str, "<") 
         || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<") || !ft_strcmp(str, "|")
         || !ft_strcmp(str, ";") || !ft_strcmp(str, "{") || !ft_strcmp(str, "}")
         || !ft_strcmp(str, "(") || !ft_strcmp(str, ")")
         || !ft_strcmp(str, "~") || !ft_strcmp(str, "&") || !ft_strcmp(str, "?"))
    {
        return (1);
    }
    return (0);
}

char *handel_special_characters(char *str)
{
    int len = ft_strlen(str);
    char *ret = malloc((len + 3) * sizeof(char));
    if (!ret)
        return NULL;

    int i = 0;
    int j = 0;
    ret[i++] = '\'';
    while (j < len)
    {
        ret[i++] = str[j];       
        j++;
    }
    ret[i++] = '\'';  
    ret[i] = '\0';
    return ret;
}

void replacement_strings(char **words, t_variables *env, t_variables *local_env)
{
     
     if (!words)
        return ;

    int i = 0;
    
    while (words[i])
    {
        if (is_special_characters(words[i]))
        {
            words[i] = handel_special_characters(words[i]);
        }
        else if (words[i][0] != '\'')
        {
            if (words[i][0] == '"')
            {
                words[i] = ft_strtrim(words[i], "\"");
            }
            words[i] = replace_token(words[i], env, local_env);
        }
        else
        {
            words[i] = ft_strtrim(words[i], "'");
        }
        i++;
    }
}