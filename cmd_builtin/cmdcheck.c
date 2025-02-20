/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:38:20 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/21 00:38:22 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strcut(int start, int end, char *input)
{
	char	*s;
	int		i;
	int		len;

	i = start;
	if (!input)
		return (NULL);
	len = 0;
	while (i < end)
	{
		len++;
		i++;
	}
	i = start;
	s = NULL;
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	len = 0;
	while (i < end)
	{
		s[len++] = input[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

char    *get_path_root(char **path, char *cmd)
{
    char    *result;
	char	*tmp;
    int     start;
	int		end;
	int		len;

    if (!(*path) || !cmd)
        return (NULL);
	len = 0;
    while ((*path)[len] && (*path)[len] != ':')
        len++;
	end = len + 1;
    if (len)
    {
		tmp = ft_strcut(0, end, (*path));
		if (!tmp)
			return (NULL);
		tmp[end - 1] = '/';
		result = ft_strjoin((*const char)tmp, (*const char)cmd);
		free(tmp)
		(*path) += end;
		if (!result)
			return (NULL);
		else
			return (result);
    }
}

t_env   *path_node(t_mini *mini)
{
    t_env   *current;

    current = mini->env;
    if (!mini->env || !mini->env[0] || !current)
        return (NULL);
    while (current)
    {
        if (ft_strncmp(current->value, "PATH", 4) == 0)
            return (current)
        current = current->next;
    }
    return (NULL);
}

void    check_syscmd(t_mini **mini)
{
    t_env   *path;
    char    *path_root;
	int		start;
	int		end;

    path = path_node(*mini);
    if (!path || path->value)
        return (-1);
    while ((*path)->valu != '=')
        path->value++;
	path->value += 1;
    while ((*path)->value)
    {
        path_root = get_path_root(&path->value, mini->cmd);
        if (path_root)
        {
            if (access(path_root, X_OK) == 0)
            return (0);
        }
        free(path_root);
    }
    return (-1);
}

int	check_cmd(char *cmd)
{
	if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0);
		return (0);
	if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0);
		return (0);
	return (check_syscmd(cmd));
}

void	cmd_executor(t_mini **mini)
{
	int	i;
	
	i = 0;
	while (i < mini->process->n_pid)
	{
		if (check_cmd(mini->cmd->cmd) != 0)
		{
			printf("%s: command not valid pid = %d", mini->cmd->cmd, mini->process->n_pid);
			free_cmd()
			return(-1;)
		}
		i++;
	//exec_cmd
}