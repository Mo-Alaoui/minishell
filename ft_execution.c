#include "minishell.h"

void	error(void)
{
	perror("error found");
	exit(127);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		free(str[i++]);
	free(str);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path_part;
	char	*path1;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || !envp[i])
		return (cmd);
	path_part = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_part[i] != 0)
	{
		path1 = ft_strjoin(path_part[i], "/");
		path = ft_strjoin(path1, cmd);
		free(path1);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	ft_free(path_part);
	return (cmd);
}

void	ft_execute(char *argv, t_history *history ,char **envp)
{
	char	**cmd;
	char	*path;
	int		i;
    if(check_his(argv, history) == 1)
	     exit(0);
	i = 0;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (path == 0)
	{
		ft_free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		while (cmd[i] != 0)
			free(cmd[i++]);
		free(cmd);
		exit(127);
	}
}
