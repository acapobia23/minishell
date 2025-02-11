/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:36:20 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/11 21:55:44 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *return_var_value(char *str, char delimiter)
{
    int     i;
    char    *result;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != delimiter)
        i++;
    result = (char *)malloc(sizeof(char) * (i + 1));
    if (!result)
        return (NULL);
    ft_strlcpy(result, str, i + 1);
    return (result);
}

int    setenv_export(char *str, t_env *environ)
{
    char    *var;
    char    *value;
    int     i;

    if (!str || !ft_isalpha(str[0]) || str[0] == '=')
        return (1);
    i = 0;
    while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    if (str[i] == '=')
    {
        var = return_var_value(str, '=');
        if (!var)
            return (1);
        value = return_var_value(str + i + 1, '\0');
        if (!value)
            return (free(var), 1);
        setenv_builtin(var, value, 1, &environ);
        free(var);
        free(value);
    }
    return (0);
}

static char	*ft_strchr_local(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

void    concatenate_value(char *value, char *equal, size_t total_len)
{
    if (!value || !equal)
        return;
    ft_strlcat(value, "=\"", total_len);
	ft_strlcat(value, equal + 1, total_len);
	ft_strlcat(value, "\"", total_len);
    return ;
}

char	*ret_value(const char *prefix, const char *env)
{
	char		*value;
	const char	*equal;
	size_t		key_len;
	size_t		total_len;

	if (!prefix || !env)
		return (NULL);
	equal = ft_strchr_local(env, '=');
	key_len = 0;
	if (equal)
		key_len = (size_t)(equal - env);
	else
		key_len = ft_strlen(env);
	total_len = ft_strlen(prefix) + key_len + 4;
	if (equal)
		total_len += ft_strlen(equal + 1);
	value = (char *)malloc(total_len);
	if (!value)
		return (NULL);
	ft_strlcpy(value, prefix, total_len);
	ft_strlcat(value, env, ft_strlen(prefix) + key_len + 1);
	if (equal)
        concatenate_value(value, equal, total_len);
	return (value);
}


int    print_declare_x_var(t_env *env)
{
    char    *result;
    t_env   *current;

    current = env;
    if (!current)
        return (1);
    while (current)
    {
        result = ret_value("declare -x ", current->value);
        if (!result)
            return (1);
        printf("%s\n", result);
        free(result);
        current = current->next;
    }
    return (0);
}

int    export_builtin(t_mini * mini)
{
    char    **argu;
    size_t  i;

    argu = mini->cmd->arg;
    i = 0;
    if (!argu || !argu[0])
        return (print_declare_x_var(mini->env));
    i = 0;
    while (argu[i])
    {
        if (setenv_export(argu[i], mini->env))
        {
            write(2, "export: not a valid identifier\n", 31);
            return (1);
        }
        i++;
    }
    return (0);
}
