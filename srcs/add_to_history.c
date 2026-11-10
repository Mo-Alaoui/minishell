/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:45:02 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 16:27:39 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
