#include "minishell.h"

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