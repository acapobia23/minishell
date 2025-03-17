#include "../mini.h"

void	ft_free_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static char	**ft_copy_mtx(char **mtx)
{
	char	**copy;
	int		size;
	int		i;

	copy = NULL;
	size = 0;
	i = -1;
	while (mtx[size] != NULL)
		size++;
	copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (++i < size)
	{
		copy[i] = ft_strdup((const char*)mtx[i]);
		if (!copy[i])
		{
			size = -1;
			while (++size < i)
				free(copy[size]);
			free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

t_cmd	*ft_cpy_cmd(t_cmd cmd)
{
	t_cmd	*new;

	new = NULL;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup((const char *)cmd.cmd);
	new->arg = ft_copy_mtx(cmd.arg);
	if (cmd.flag_cmd == true)
	{
		new->redirect = ft_strdup((const char*)cmd.redirect);
		new->file = ft_strdup((const char*)cmd.file);
		new->flag_cmd = cmd.flag_cmd;
	}
	else
	{
		new->redirect = NULL;
		new->file = NULL;
		new->flag_cmd = false;
	}
	return (new);
}