#include "minishell.h"

static void handle_quotes(const char *input, t_token_data *data)
{
    if (input[data->i] == '"' || input[data->i] == '\'')
    {
        if (data->in_quotes && input[data->i] == data->quote_char)
            data->in_quotes = 0;
        else if (!data->in_quotes)
        {
            data->in_quotes = 1;
            data->quote_char = input[data->i];
        }
    }
}

static void add_token(t_token_data *data, const char *input, int start, int end)
{
    if (end > start)
    {
        data->tokens[data->token_count] = strndup(input + start, end - start);
        if (!data->tokens[data->token_count])
        {
            while (data->token_count--)
                free(data->tokens[data->token_count]);
            free(data->tokens);
            exit(EXIT_FAILURE);
        }
        data->token_count++;
    }
}

static int ft_count_token(const char *input)
{
    int count, i, in_quotes;
    char quote_char;

    count = 0;
    i = 0;
    in_quotes = 0;
    quote_char = '\0';
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            if (in_quotes && input[i] == quote_char)
                in_quotes = 0;
            else if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = input[i];
            }
        }
        else if (!in_quotes && (ft_isspace(input[i]) || ft_isseparator(input[i])))
            count++;
        i++;
    }
    if (i > 0 && !ft_isspace(input[i - 1]))
        count++;
    return (count);
}

char **ft_tokenize(const char *input)
{
    t_token_data data;

    data.tokens = malloc(sizeof(char *) * (ft_count_token(input) + 1));
    if (!data.tokens)
        return (NULL);

    data.token_count = 0;
    data.in_quotes = 0;
    data.quote_char = '\0';
    data.start = 0;
    data.i = 0;
    
    while (input[data.i])
    {
        handle_quotes(input, &data);
        if (!data.in_quotes && (ft_isspace(input[data.i])))
        {
            add_token(&data, input, data.start, data.i);
            // if (ft_isseparator(input[data.i]))
            //     add_token(&data, input, data.i, data.i + 1);
            data.start = data.i + 1;
        }
        data.i++;
    }
    add_token(&data, input, data.start, data.i);
    data.tokens[data.token_count] = NULL;
    return (data.tokens);
}

