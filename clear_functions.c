#include "mini.h"

void ft_free_cmd(t_mini **mini)
{
    t_cmd *cmd;
    int j;
	int i;

    if (!mini || !(*mini) || !(*mini)->cmd)
        return;
    cmd = (*mini)->cmd;
	i = 0;
	while (cmd[i].cmd)
	{
    	if (cmd->cmd)
		{
        	free(cmd->cmd);
        	cmd->cmd = NULL;
    	}
    	if (cmd->arg)
		{
        	j = 0;
        	while (cmd->arg[j])
			{
            	free(cmd->arg[j]);
            	cmd->arg[j] = NULL;
            	j++;
        	}
        	free(cmd->arg);
    		cmd->arg = NULL;
    	}
    	if (cmd->redirect)
		{
        	free(cmd->redirect);
        	cmd->redirect = NULL;
    	}
    	if (cmd->file)
		{
    	    free(cmd->file);
        	cmd->file = NULL;
		}
		i++;
	}
	free(cmd);
    (*mini)->cmd = NULL;

}


void	clear_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	if (!tokens || !(*tokens))
		return;

	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->arg)
		{
			free(tmp->arg);
			tmp->arg = NULL;
		}
		if (tmp->flag)
		{
			free(tmp->flag);
			tmp->flag = NULL;
		}
		free(tmp);
		tmp = next;
	}
	*tokens = NULL;
}


void	ft_free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	if (!env || !(*env))
		return ;
	tmp = (*env);
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
		tmp = next;
	}
	(*env) = NULL;
}

void	ft_clear_mini(t_mini **mini)
{
	if (!mini || !(*mini))
		return;
	if ((*mini)->env)
	{
		ft_free_env(&(*mini)->env);
		(*mini)->env = NULL;
	}
	if ((*mini)->process)
	{
		if ((*mini)->process->id_current)
		{
			free((*mini)->process->id_current);
			(*mini)->process->id_current = NULL;
		}
		free((*mini)->process);
		(*mini)->process = NULL;
	}
	if ((*mini)->cmd)
	{
		ft_free_cmd(mini);
		(*mini)->cmd = NULL;
	}
	free((*mini));
	(*mini) = NULL;
}


void ft_exit(int exit_code, char *s, t_mini **mini)
{
	if (s)
		printf("%s\n", s);
	if (mini && (*mini))
	{
		ft_clear_mini(mini);
		(*mini) = NULL;
	}
	rl_clear_history();
	exit(exit_code);
}