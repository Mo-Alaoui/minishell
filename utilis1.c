/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:55:14 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 16:40:32 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

int is_redir(char *s)
{
    return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") ||
            !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

int is_pipe(char *s)
{
    return (!ft_strcmp(s, "|"));
}

int is_invalid_token(char *s)
{
    return (!ft_strncmp(s, "||",2) || !ft_strcmp(s, "><") ||
    	 !ft_strncmp(s, ">>>",3));
}

char *is_valid_input(char **tokens)
{
    int i = 0;

    if (!tokens || !tokens[0])
        return NULL;

    if (is_pipe(tokens[0]) || (tokens[i + 1] == NULL && is_pipe(tokens[i])))
        return tokens[i];

    while (tokens[i])
    {
        if (is_invalid_token(tokens[i]))
            return tokens[i];

        if (is_pipe(tokens[i]))
        {
            if (!tokens[i + 1] || is_pipe(tokens[i + 1]))
                return tokens[i];
        }

        if (is_redir(tokens[i]))
        {
            if (!tokens[i + 1] || is_redir(tokens[i + 1]) || is_pipe(tokens[i + 1]))
                return tokens[i];
        }

        i++;
    }
    return NULL;
}