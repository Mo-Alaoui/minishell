/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:27:00 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/18 15:27:01 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_functions(char *str)
{
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2)
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strncmp(str, "exit", 4))
	{
		return (1);
	}
	return (0);
}

static int	list_size(t_variables *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**variables_to_array(t_variables *head)
{
	int		total_len;
	char	**array;
	char	*tmp;
	int		size;
	int		i;

	size = list_size(head);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (head)
	{
		total_len = ft_strlen(head->variable_name) + ft_strlen(head->value) + 2;
		tmp = malloc(total_len);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, head->variable_name, total_len);
		ft_strlcat(tmp, "=", total_len);
		ft_strlcat(tmp, head->value, total_len);
		array[i++] = tmp;
		head = head->next;
	}
	array[i] = NULL;
	return (array);
}

void	sort_ascii(char **arr)
{
	char	*temp;
	int		i;
	int		j;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	while (i > 1)
	{
		j = 0;
		while (arr[j + 1])
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i--;
	}
}
