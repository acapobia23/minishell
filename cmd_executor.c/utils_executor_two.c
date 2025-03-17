#include "../mini.h"

void	ft_free_cpy(t_mini **mini)
{
	ft_free_env(&(*mini)->env);
	ft_free_cmd(&(*mini));
	free((*mini)->process);
	free((*mini));
}

int	ft_free_pipe(int **pipes, const char *error, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(pipes[i]);
	free(pipes);
	printf("%s", error);
	return (-1);
}

int ft_isbuiltin(char *cmd)
{
	if (ft_strcmp((const char *)cmd, "cd") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "echo") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "env") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "exit") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "export") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp((const char *)cmd, "unset") == 0)
		return (0);
	return (-1);
}

void	close_pipe(int **pipes, int n_cmd)
{
	int	i;

	i = -1;
	while ( ++i < n_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

int	check_redirect_copy(t_mini **copy)
{
	if (!(*copy)->cmd->file)
	{
		ft_free_env(&(*copy)->env);
		ft_free_cmd(&(*copy));
		return (-1);
	}
	if (!(*copy)->cmd->redirect)
	{
		ft_free_env(&(*copy)->env);
		ft_free_cmd(&(*copy));
		return (-1);
	}
	return (0);
}
