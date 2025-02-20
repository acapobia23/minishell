/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:15:41 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/20 22:16:04 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *get_path_root(char *path, char *cmd)
{
    char    *result;
    int     len;

    if (!path || !cmd)
        return (NULL);
    len = 0;
    while (path[len] && path[len] != ':')
        len++;
    if (len)
    {
        result = malloc(sizeof(char) * len + ft_strlen(cmd) + 1);
        ft_strlcpy(result, path, len);
        ft_strlcat()
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

void    syscommand(t_mini **mini)
{
    t_env   *path;
    char    *path_root;

    path = path_node(*mini);
    if (!path || path->value)
        return ;
    while (path->(*value) != '=')
        path->value++;
    while (path->(*value))
    {
        path_root = get_path_root(path->value + 1, mini->cmd);
        if (path_root)
        {
            if (execve(path_root, mini->cmd->args, NULL) == -1)
                perror("execve");
            return ;
        }
        path->value += 1;
        free(path_root);
    }
    return ;
}