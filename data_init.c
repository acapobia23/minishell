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

	if (!envp || !envp[0])
		return (NULL);
	env = ft_new_env(envp[0]);
	if (!env)
		return (NULL);
	tmp = env;
	i = 1;
	while (envp[i] != NULL)
	{
		tmp->next = ft_new_env(envp[i]);
		if (!tmp->next)
		{
			ft_free_env(&env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	return (env);
}

int	setup_mini(t_mini **mini, char **envp)
{
    if (!mini || !(*mini))
        return (-1);

    (*mini)->exit_code = 0;
    (*mini)->cmd = NULL;
    (*mini)->env = env_init(envp);
    if (!(*mini)->env)
        return (-1);

    (*mini)->process = ft_calloc(1, sizeof(t_pid));
    if (!(*mini)->process)
    {
        ft_free_env(&(*mini)->env);
        return (-1);
    }

    (*mini)->process->id_current = NULL;
    (*mini)->process->n_pid = 0;
    return (0);
}
