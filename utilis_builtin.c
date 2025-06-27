/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:27:00 by mohalaou          #+#    #+#             */
/*   Updated: 2025/06/26 16:40:13 by mohalaou         ###   ########.fr       */
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

void	ft_child(t_all *parser, char **token, int flag, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (token[0][0] == '\0' && token[1] == NULL)
		ft_ex(token, 1);
	if (check_input_type(token) == 3)
		exit(if_its_pipe_red(token, parser->new_pip, parser, envp));
	if (check_input_type(token) == 2)
		exit(if_its_pipe(parser->new_pip, token, parser, envp));
	if (check_input_type(token) == 0)
	{
		if (check_herdoc(token, envp) == 1)
			ft_call(parser, flag, envp);
		else if (check_red(token) == 1)
			ft_call1(parser, flag, envp);
		else if (check_red(token) == 2)
			ft_call2(parser, flag, envp);
		else if (check_red(token) == 3)
			ft_call3(parser, flag, envp);
		else if (check_red(token) == 4)
			ft_call4(parser, flag, envp);
		else
			ft_execute(parser->new_pip->content, parser->clean, parser, envp);
	}
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
	array = ft_malloc(sizeof(char *) * (size + 1), 'A');
	if (!array)
		return (NULL);
	i = 0;
	while (head)
	{
		total_len = ft_strlen(head->variable_name) + ft_strlen(head->value) + 2;
		tmp = ft_malloc(total_len, 'A');
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
