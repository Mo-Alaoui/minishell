/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:22:23 by saamouss          #+#    #+#             */
/*   Updated: 2025/06/17 23:22:25 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ft3(char **tokenize, int i)
{
	if (ft_strcmp(tokenize[i], "'<'") == 0)
	{
		redirect_input(tokenize[i + 1]);
		return (2); 
	}
	if (ft_strcmp(tokenize[i], "'>'") == 0)
	{
		redirect_output(tokenize[i + 1], 0);
		return (1);
	}
	else if (ft_strcmp(tokenize[i], "'>>'") == 0)
	{
		redirect_output(tokenize[i + 1], 1);
		return (1);
	}
	return (0);
}

int	ft_ft1(char **toknize, int last_fd)
{
	int	i;

	i = 0;
	while (toknize[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (ft_ft3(toknize, i) == 1)
				break ;
		if(ft_ft3(toknize, i) == 2)
			return (1);
		i--;
	}
	if (last_fd != -1 )
	{
		dup2(last_fd, STDIN_FILENO);
		close(last_fd);
		return (1);
	}
	return (0);
}

void	ft_ft6(char **tokenize, int j)
{
	while (tokenize[j])
		j++;
	j--;
	while (j >= 0)
	{
		if (ft_strcmp(tokenize[j], "'<'") == 0)
		{
			redirect_input(tokenize[j + 1]);
			break ;
		}
		j--;
	}
}

int	ft_ft7(char **tokenize, int j)
{
	redirect_output(tokenize[j + 1], 1);
	while (j >= 0)
	{
		if (ft_strcmp(tokenize[j], "'<'") == 0)
		{
			redirect_input(tokenize[j + 1]);
			break ;
		}
		j--;
	}
	return (4);
}

int	ft_ft2(char **tokenize, int i, int flag)
{
	int	j;

	j = i;
	if (flag == 1)
		ft_ft6(tokenize, j);
	while (tokenize[j])
		j++;
	j--;
	while (j >= 0)
	{
		if (ft_strcmp(tokenize[j], "'>'") == 0)
			return (ft_ft7(tokenize, j));
		else if (ft_strcmp(tokenize[j], "'>>'") == 0)
			return (ft_ft7(tokenize, j));
		--j;
	}
	return (1);
}
