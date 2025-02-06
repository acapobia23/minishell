#include "mini.h"

static t_env	*ft_new_env(const char	*str)
{
	t_env	*new;

	new = NULL;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(str);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static t_env	*env_init(char **envp)
{
	t_env	*tmp;
	t_env	*env;
	int		i;

	i = 0;
	env = ft_new_env(envp[i]);
	tmp = env;
	while (envp[++i] != NULL)
	{
		tmp->next = ft_new_env(envp[i]);
		if (!tmp->next)
		{
			ft_free_env(&env);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (env);
}

int	setup_mini(t_mini **mini, char **envp)
{
	(*mini) = ft_calloc(1, sizeof(t_mini));
	if (!(*mini))
		return (-1);
	(*mini)->exit_code = 0;
	(*mini)->cmd = NULL;
	(*mini)->env = env_init(envp);//TODO
	if (!(*mini)->env)
		return (-1);
	(*mini)->process = ft_calloc(1, sizeof(t_pid));
	(*mini)->process->id_current = NULL;
	if (!(*mini)->process)
		return (-1);
	return (0);
}
