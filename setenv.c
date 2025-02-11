/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:14:44 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/09 16:50:07 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	scan_environ(t_env **environ, char *name)
{
	t_env	*current;

	current = (*environ);
	while (current)
	{
		if (ft_strcmp_until(current->value, name, "=") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

char *join_env_var(const char *name, const char *value)
{
    char *joined;
    char *temp;

    temp = ft_strjoin(name, "=");
    if (!temp)
        return (NULL);
    joined = ft_strjoin(temp, value);
    free(temp);
    return (joined);
}

int replace_env(t_env *environ, char *name, char *new_entry)
{
    t_env *current;

    current = environ;
    while (current)
    {
        if (ft_strcmp_until(current->value, name, '=') == 0)
        {
            free(current->value);
            current->value = new_entry;
            return (1);
        }
        current = current->next;
    }
    return (0);
}

int add_env(t_env **environ, char *new_entry)
{
    t_env *current;
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (0);
    new_node->value = new_entry;
    new_node->next = NULL;
    if (!(*environ))
    {
        *environ = new_node;
        return (1);
    }
    current = *environ;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return (1);
}

int	setenv_builtin(const char *name, const char *value, int overwrite, t_env **environ)
{
	char	*new_entry;
	
	if (!value || !name || *name == '\0' || !scan_str(name, "="))
		return (-1);
	new_entry = join_env_var(name, value);
	if (!new_entry)
		return (-1);
	if (scan_environ(environ, (char *)name))
	{
		if (overwrite)
			return (replace_env((*environ), (char *)name, new_entry));
		free(new_entry);
		return (0);
	}
	return (add_env(environ, new_entry));
}