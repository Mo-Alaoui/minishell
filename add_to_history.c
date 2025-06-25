/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:45:02 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/25 17:11:24 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_history	*init_history(void)
// {
// 	t_history	*history;

// 	history = malloc(sizeof(t_history));
// 	if (!history)
// 		return (NULL);
// 	history->capacity = 500;
// 	history->size = 0;
// 	history->cmds = malloc(sizeof(char *) * history->capacity);
// 	if (!history->cmds)
// 	{
// 		free(history);
// 		return (NULL);
// 	}
// 	return (history);
// }

void	add_to_history(t_history *history, char *line)
{
	if (!line || history->size >= history->capacity)
		return ;
	history->cmds[history->size++] = ft_strdup(line);
}

void	print_history(t_history *history)
{
	int	i;

	i = 0;
	while (i < history->size)
	{
		printf("%d %s\n", i + 1, history->cmds[i]);
		i++;
	}
}

void	free_history(t_history *history)
{
	int	i;

	i = 0;
	while (i < history->size)
	{
		free(history->cmds[i]);
		history->cmds[i] = NULL;
		i++;
	}
	free(history->cmds);
	history->cmds = NULL;
	free(history);
	history = NULL;
}
