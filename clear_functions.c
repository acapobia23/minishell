#include "mini.h"

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
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	(*env) = NULL;
}

void	ft_clear_mini(t_mini **mini)
{
	if (!(*mini))
		return ;
	if ((*mini)->env)
		ft_free_env(&(*mini)->env);
	if ((*mini)->process)
	{
		if ((*mini)->process->id_current)
			free((*mini)->process->id_current);
		free((*mini)->process);
	}
	// if ((*mini)->cmd)
	// 	ft_free_cmd(&(*mini)->cmd)//TODO da vedere quando assegno cmd la struct completa
	free((*mini));
}

void ft_exit(int exit_code, char *s, t_mini **mini)
{
	if ((*mini))
		ft_clear_mini(&(*mini));
	printf("%s\n", s);
	rl_clear_history();
	exit(exit_code);
}