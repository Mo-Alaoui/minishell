#include "minishell.h"

void	error(void)
{
	perror("error found");
	exit(1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		free(str[i++]);
	free(str);
}

t_list	*ft_parser(char **tokenize, char *s)
{
	int		i;
	char	*tmp;
	char	*str;
	t_list	*head;
	t_list	*new;

	i = 0;
	str = ft_strdup("");
	head = NULL;
	while (tokenize[i])
	{
		if (ft_strcmp(tokenize[i], s) == 0)
		{
			new = ft_lstnew(str);
			ft_lstadd_back(&head, new);
			str = ft_strdup("");
			i++;
		}
		tmp = str;
		str = ft_strjoin(str, tokenize[i]);
		free(tmp);
		if (tokenize[i + 1] && ft_strcmp(tokenize[i + 1], s) != 0)
		{
			tmp = str;
			str = ft_strjoin(str, " ");
			free(tmp);
		}
		i++;
	}
	if (str && *str)
	{
		new = ft_lstnew(str);
		ft_lstadd_back(&head, new);
	}
	return (head);
}
char	*force_check(char **tokenize, char *str, char *tmp, int i)
{
	if (tokenize[i + 1] && ft_strcmp(tokenize[i + 1], "'<'") != 0
		&& ft_strcmp(tokenize[i + 1], "'>'") != 0 && ft_strcmp(tokenize[i + 1],
			"'|'") != 0)
	{
		tmp = str;
		str = ft_strjoin(str, " ");
		free(tmp);
	}
	return (str);
}

void	add_add(t_list *head, t_list *new, char *str)
{
	if (str && *str)
	{
		new = ft_lstnew(str);
		ft_lstadd_back(&head, new);
	}
}

          void	add_add1(t_list *head, t_list *new, char *str)
            {
			    new = ft_lstnew(str);
			    ft_lstadd_back(&head, new);
			    str = ft_strdup("");
            }

t_list	*ft_parser2(char **tokenize)
{
	int		i;
	char	*str;
	t_list	*head;
	t_list	*new = NULL;
	char	*tmp;

	i = 0;
	str = ft_strdup("");
	head = NULL;
	while (tokenize[i])
	{
		if (ft_strcmp(tokenize[i], "'<'") == 0 || ft_strcmp(tokenize[i],
				"'>'") == 0 || ft_strcmp(tokenize[i], "'|'") == 0)
		{
            add_add1(head, new, str);
			i++;
		}
		tmp = str;
		str = ft_strjoin(str, tokenize[i]);
		free(tmp);
		str = force_check(tokenize, str, tmp, i);
		i++;
	}
	add_add(head, new, str);
	return (head);
}
