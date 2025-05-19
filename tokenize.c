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
            {
                count++;
                in_quotes = 0;
            }
            else if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = input[i];
            }
        }
        if (!in_quotes && (ft_isspace(input[i]) || ft_isseparator(input[i])))
            count++;
        i++;
    }
    if (i > 0 && !ft_isspace(input[i - 1]))
        count++;

    return (count);
}

int is_delimiter(char c)
{
    if (ft_isspace(c) || ft_isseparator(c) || c == '\'' || c == '"')
        return (1);
    return (0);
}

char **ft_tokenize(const char *input)
{
    t_token_data data;
    ft_memset(&data, 0, sizeof(t_token_data));

    data.tokens = malloc(sizeof(char *) * (ft_count_token(input) + 2));
    if (!data.tokens)
        return (NULL);

    while (input[data.i])
    {
        handle_quotes(input, &data);
        if (!data.in_quotes)
        {
            if (is_delimiter(input[data.i]))
            {
                if (input[data.i] == '\'' || input[data.i] == '"')
                    add_token(&data, input, data.start, data.i + 1);
                else
                    add_token(&data, input, data.start, data.i);
                char check_sepa = input[data.i];
                if (ft_isseparator(check_sepa))
                {
                    int j = 0;
                    while (input[data.i + 1] == check_sepa)
                    {
                        j++;
                        data.i++;
                    }
                    add_token(&data, input, data.i - j, data.i + 1);
                }
                data.start = data.i + 1;
            }
        }
        data.i++;
    }
    add_token(&data, input, data.start, data.i);
    data.tokens[data.token_count] = NULL;
    return (data.tokens);
}

