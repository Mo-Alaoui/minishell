#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include "minishell.h"

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

 void replacement_strings(char **words, t_variables *env, t_variables *local_env)
 {
     
     if (!words)
        return ;

    int i = 0;
    
    while (words[i])
    {
        if (words[i][0] != '\'')
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



static void free_words(char **ret, int count)
{
    while (count--)
        free(ret[count]);
    free(ret);
}

static void add_word(char **ret, int *ret_count, char *input, int start, int end)
{
    if (end > start)
    {
        ret[*ret_count] = strndup(input + start, end - start);
        if (!ret[*ret_count])
        {
            free_words(ret, *ret_count);
            exit(1);
        }
        (*ret_count)++;
    }
}

char **split_by_quotes(char *token, int max_parts)
{
    char **ret = malloc((max_parts + 1) * sizeof(char *));
    if (!ret)
        return NULL;

    int i = 0;
    int start = 0;
    int ret_count = 0;

    while (token[i])
    {
        if (token[i] == '\'' || token[i] == '"')
        {
            if (i > start)
                add_word(ret, &ret_count, token, start, i);

            char quote = token[i];
            int quote_start = i;
            i++;

            while (token[i] && token[i] != quote)
                i++;

            if (token[i] == quote)
                i++;

            add_word(ret, &ret_count, token, quote_start, i);
            start = i;
        }
        else
        {
            i++;
        }
    }

    if (i > start)
        add_word(ret, &ret_count, token, start, i);

    ret[ret_count] = NULL;
    return ret;
}

// void print_array_char(char **arr)
// {
//     for (int i = 0; arr && arr[i]; i++)
//         printf("%s\n", arr[i]);
// }

char *join_strings(char **words)
{
    char *res = "";
    int i  = 0; 

    while (words[i])
    {
        res = ft_strjoin(res, words[i]);
        i++;
    }
    return (res);
}

char *handel_quotes(char *input, t_variables *env, t_variables *local_env)
{
    int i;
    char **words = split_by_quotes(input, 10);
    replacement_strings(words, env, local_env);
    input = join_strings(words);

    i = 0;
    while (words[i])
    {
        free(words[i]);
        i++;
    }    
    free(words);
    
    return (input);
}

