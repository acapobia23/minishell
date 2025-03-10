/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:38:20 by ltrento           #+#    #+#             */
/*   Updated: 2025/03/10 17:52:53 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char *get_path_root(char **path, char *cmd)
{
    char *result;
    char *tmp;
    char *tmp_slash;
    int len;

    if (!path || !(*path) || !cmd)
        return (NULL);
    len = 0;
    while ((*path)[len] && (*path)[len] != ':')  
        len++;
    tmp = ft_strcut(0, len, *path);
    if (!tmp)
        return (NULL);
    tmp_slash = ft_strjoin(tmp, "/");
    free(tmp);
    if (!tmp_slash)
        return (NULL);
    result = ft_strjoin(tmp_slash, cmd);
    free(tmp_slash);
    if (!result)
        return (NULL);
    if ((*path)[len] == ':')
        *path += (len + 1);
    else
        *path += len;
    return (result);
}

t_env *path_node(t_mini *mini)
{
    t_env *current;

    if (!mini || !mini->env)
        return (NULL);

    current = mini->env;
    while (current)
    {
        if (ft_strncmp(current->value, "PATH", 4) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

int check_syscmd(t_mini **mini)
{
    t_env *path;
    char *path_value;
    char *path_iter;

    if (!mini || !(*mini) || !(*mini)->cmd || !(*mini)->cmd->cmd)
        return (-1);
    path = path_node(*mini);
    if (!path || !path->value)
        return (-1);
    path_value = ft_strdup(path->value + 5);
    if (!path_value)
        return (-1);
    path_iter = path_value;
    while (*path_iter)
    {
        char *path_root = get_path_root(&path_iter, (*mini)->cmd->cmd);
        if (path_root)
        {
            if (access(path_root, X_OK) == 0)
            {
                free(path_root);
                free(path_value);
                return (0);
            }
            free(path_root);
        }
    }
    free(path_value);
    return (-1);
}


int check_builtin(char *cmd, t_mini **mini)
{
    if (!cmd || !mini || !(*mini))
        return (0);

    if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
        return (1);
    if (check_syscmd(mini) == 0)
        return (1);
    return (0);
}

int exec_cmd(t_mini **mini, char *cmd)
{
    if (!mini || !(*mini) || !cmd)
        return (1);

    if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
        return (cd_builtin((*mini)));
    if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
        return (echo_builtin((*mini)));
    if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
        return (env_builtin(mini));
    if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
        return (exit_builtin(mini));
    if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
        return (export_builtin((*mini)));
    if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
        return (pwd_builtin());
    if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
        return (unset_builtin(mini));
    return (syscommand(mini));
}

int cmd_executor(t_mini **mini)
{
    int i;

    if (!mini || !(*mini) || !(*mini)->cmd || !(*mini)->cmd->cmd)
        return (-1);

    i = 0;
    while (i < (*mini)->process->n_pid)
    {
        // if (check_pipe(mini) == 0)
        //     pipe_case((*mini));//TODO
        if (check_builtin((*mini)->cmd->cmd, mini) == 0)
        {
            printf("%s: command not found (pid = %d)\n", (*mini)->cmd->cmd, (*mini)->process->n_pid);
            ft_free_cmd(mini);
            return (-1);
        }
        i++;
    }
    return (exec_cmd(mini, (*mini)->cmd->cmd));
}
