#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

int	is_metachar2(char *s)
{
	return (!ft_strcmp(s, "'<'") || !ft_strcmp(s, "'>'") || !ft_strcmp(s,
			"'>>'") || !ft_strcmp(s, "'<<'"));
}

int	is_metachar(char *s)
{
	return (!ft_strcmp(s, "'|'") || !ft_strcmp(s, "'<'") || !ft_strcmp(s, "'>'")
		|| !ft_strcmp(s, "'>>'") || !ft_strcmp(s, "'<<'") || !ft_strcmp(s, "&&")
		|| !ft_strcmp(s, "||") || !ft_strcmp(s, "&") || !ft_strcmp(s, ";")
		|| !ft_strcmp(s, ";;"));
}

int	is_character(char s)
{
	if (s == '>' || s == '<' || s == '&' || s == ';' || s == '|' || s == '('
		|| s == ')')
	{
		return (1);
	}
	return (0);
}

char	*is_valid_input(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (tokens[0]);
	if ((tokens[1] == NULL && is_metachar2(tokens[0])))
		return ("newline");
	i = 0;
	while (tokens[i])
	{
		if (is_metachar(tokens[i]))
		{
			if (!tokens[i + 1])
				return (tokens[i]);
			if (is_metachar(tokens[i + 1]))
				return (tokens[i + 1]);
		}
		if (is_character(tokens[i][0]) == 1)
			return (tokens[i]);
		if ((tokens[1] == NULL && is_character(tokens[0][0]) == 1))
			return (tokens[i]);
		if(ft_strcmp(tokens[i], "';'") == 0)
			return(";");
		i++;
	}
	return (NULL);
}
