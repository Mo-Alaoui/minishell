/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:54:20 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/26 17:11:05 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*force_check(char **tokenize, char *str, char *tmp, int i)
{
	if (tokenize[i + 1] && ft_strcmp(tokenize[i + 1], "'<'") != 0
		&& ft_strcmp(tokenize[i + 1], "'>'") != 0 && ft_strcmp(tokenize[i + 1],
			"'|'") != 0)
	{
		tmp = str;
		str = ft_strjoin(str, " ");
		free(tmp);
		tmp = NULL;
	}
	return (str);
}

void	handle_last_chunk(char *str, t_list **head)
{
	t_list	*new;

	if (str && *str)
	{
		new = ft_lstnew(str);
		if (!new)
		{
			free(str);
			return ;
		}
		ft_lstadd_back(head, new);
	}
	else
	{
		free(str);
	}
}

void	handle_chunk(char *str, t_list **head)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
	{
		free(str);
		return ;
	}
	ft_lstadd_back(head, new);
}

t_list	*ft_parser(char **tokenize, char *s)
{
	int		i;
	char	*tmp;
	char	*str;
	t_list	*head;

	i = 0;
	str = ft_strdup("");
	head = NULL;
	while (tokenize[i])
	{
		if (ft_strcmp(tokenize[i], s) == 0)
		{
			handle_chunk(str, &head);
			str = ft_strdup("");
			i++;
		}
		tmp = str;
		str = ft_strjoin(str, tokenize[i]);
		str = force_check(tokenize, str, tmp, i);
		i++;
	}
	handle_last_chunk(str, &head);
	return (head);
}

t_list	*ft_parser2(char **tokenize)
{
	int		i;
	char	*str;
	t_list	*head;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	head = NULL;
	while (tokenize[i])
	{
		if (ft_strcmp(tokenize[i], "'<'") == 0 || ft_strcmp(tokenize[i],
				"'>'") == 0 || ft_strcmp(tokenize[i], "'|'") == 0)
		{
			handle_chunk(str, &head);
			str = ft_strdup("");
			i++;
		}
		tmp = str;
		str = ft_strjoin(str, tokenize[i]);
		free(tmp);
		str = force_check(tokenize, str, tmp, i);
		i++;
	}
	handle_last_chunk(str, &head);
	return (head);
}
