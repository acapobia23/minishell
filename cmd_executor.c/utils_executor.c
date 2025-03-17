#include "../mini.h"

static t_env	*env_copy(t_env *env)
{
	t_env	*copy;
	char	**envp;

	envp = convert_env_list_to_array(env);
	if (!envp)
		return (NULL);
	copy = env_init(envp);
	ft_free_mtx(envp);
	if (!copy)
		return (NULL);
	return (copy);
}

static int	check_copy(t_mini **copy)
{
	if (!copy || !(*copy))
		return (-1);
	if (!(*copy)->cmd->cmd)
	{
		ft_free_env(&(*copy)->env);
		ft_free_cmd(&(*copy));
		return (-1);
	}
	if (!(*copy)->cmd->arg)
	{
		ft_clear_mini(&(*copy));
		return (-1);
	}
	if (!(*copy)->cmd->cmd)
	{
		ft_clear_mini(&(*copy));
		return (-1);
	}
	if ((*copy)->cmd->flag_cmd == true)
		return (check_redirect_copy(&(*copy)));
	return (0);
}

static t_pid	*ft_cpy_process(void)
{
	t_pid	*new;

	new = NULL;
	new = (t_pid *)malloc(sizeof(t_pid));
	new->id_current = NULL;
	if (!new)
		return (NULL);
	new->n_pid = 1;
	return (new);
}

t_mini	*ft_copy_mini(t_mini *mini, int curr_cmd)
{
	t_mini	*copy;

	copy = NULL;
	copy = (t_mini *)malloc(sizeof(t_mini));
	if (!copy)
		return (NULL);
	
	copy->cmd = ft_cpy_cmd(mini->cmd[curr_cmd]);
	if (!copy->cmd)
	{
		free(copy);
		return (NULL);
	}
	copy->env = env_copy(mini->env);
	copy->process = ft_cpy_process();
	if (check_copy(&copy) == -1)
		return (NULL);
	return (copy);
}

void	process_exec(t_mini **mini, int curr_cmd)
{
	t_mini	*cpy_mini;
	int		code_exit;

	cpy_mini = ft_copy_mini((*mini), curr_cmd);
	if (!cpy_mini)
		return ;
	code_exit = syscommand(&cpy_mini);
	ft_clear_mini(&cpy_mini);
	if (code_exit != 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

