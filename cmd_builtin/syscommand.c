/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:15:41 by ltrento           #+#    #+#             */
/*   Updated: 2025/03/10 17:10:35 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void    free_matrix(char **matrix)
{
    int i = 0;
    
    if (!matrix)
        return ;
    while (matrix[i])
    {
        free(matrix[i++]);
    }
    free(matrix);
}

void	ft_path_join(char *dst, const char *path, const char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (path[i])
	{
		dst[i] = path[i];
		i++;
	}
	dst[i++] = '/';
	j = 0;
	while (cmd[j])
	{
		dst[i] = cmd[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char **convert_env_list_to_array(t_env *env_list)
{
    int i = 0;
    t_env *temp;
    char **envp;

    temp = env_list;
    envp = NULL;
    while (temp)
    {
        i++;
        temp = temp->next;
    }
    envp = malloc((i + 1) * sizeof(char *));
    if (!envp)
        return (NULL);
    i = 0;
    while (env_list)
    {
        envp[i] = ft_strdup(env_list->value);
        if (!envp[i])
        {
            free_matrix(envp);
            return (NULL);
        }
        env_list = env_list->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}

char *get_path_root_cmd(char *path, char *cmd)
{
    char *result;
    int len;

    if (!path || !cmd)
        return (NULL);
    if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    len = ft_strlen(path) + ft_strlen(cmd) + 2;
    result = (char *)malloc(len);
    if (!result)
        return (NULL);
    ft_path_join(result, path, cmd);
    if (access(result, X_OK) == 0)
        return (result);
    free(result);
    return (NULL);
}

static t_env *path_node(t_mini *mini)
{
    t_env *current;

    if (!mini || !mini->env)
        return (NULL);
    current = mini->env;
    while (current)
    {
        if (strncmp(current->value, "PATH=", 5) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

char *next_path_segment(char *path)
{
    char *colon_pos;
    size_t segment_len;
    char *segment;
    
    colon_pos = strchr(path, ':');
    if (!colon_pos)
        return NULL;
    segment_len = colon_pos - path;
    segment = malloc(segment_len + 1);
    if (!segment)
        return NULL;
    strncpy(segment, path, segment_len);
    segment[segment_len] = '\0';
    return (segment);
}

char    **get_exec_args(t_mini *mini)
{
    char **args;
    int i;
    int j;
    int len;

    if (!mini || !mini->cmd)
        return (NULL);
    len = 0;
    if (mini->cmd->cmd && mini->cmd->cmd[0])
        len = 1;
    i = 0;
    if (mini->cmd->arg)
    {
        while (mini->cmd->arg[i])
        {
            i++;
        }
    }
    len += i;
    args = (char **)malloc(sizeof(char *) * (len + 1));
    if (!args)
        return (NULL);
    i = 0;
    if (mini->cmd->cmd && mini->cmd->cmd[0])
        args[i++] = ft_strdup(mini->cmd->cmd);
    j = 0;
    if (mini->cmd->arg)
    {
        while (mini->cmd->arg[j])
        {
            args[i++] = ft_strdup(mini->cmd->arg[j++]);
        }
    }
    args[i] = NULL;
    return (args);
}

int execute_syscommand(char *path_root, t_mini *mini)
{
    char **envp;
    char **exec_argv;
    pid_t  pid;
    int  status;

    if (!mini->cmd->cmd)
        return (-1);
    if (path_root && access(path_root, X_OK) == 0)
    {
        envp = convert_env_list_to_array(mini->env);
        if (!envp)
            return (-1);
        exec_argv = get_exec_args(mini);
        if (!exec_argv)
            return (-1);
        pid = fork();
        if (pid == -1)
            return (-1);
        if (pid == 0)
        {
            if (mini->cmd->flag_cmd == true && mini->cmd->file != NULL)
            {
                if (do_redirect_one_cmd(mini) != 0)
                    return (-1);
            }
            execve(path_root, exec_argv, envp);
            exit(EXIT_FAILURE);
        }
        else
            waitpid(pid, &status, 0);
        free_matrix(exec_argv);
        free_matrix(envp);
        free(path_root);
        return (0);
    }
    return (-1);
}

int process_command(char *path_value, t_mini *mini)
{
    char *path_root;
    char *next_colon;
    char *temp;

    temp = path_value;
    while (temp && (*temp))  
    {
        next_colon = next_path_segment(temp);
        path_root = get_path_root_cmd(temp, mini->cmd->cmd);
        if (path_root)
        {
            execute_syscommand(path_root, mini);
            return (0);
        }
        free(path_root);
        if (next_colon) 
            temp = next_colon;
        else 
            break;
    }
    return (-1);
}

int syscommand(t_mini **mini)
{
    t_env *path;
    char *path_value;
    char *path_copy;
    int exec_status;
    char *path_segment;

    path = path_node(*mini);
    if (!path || !path->value)
        return (-1);
    path_copy = ft_strdup(path->value + 5);
    if (!path_copy)
        return (-1);
    path_value = path_copy;
    while (path_value && *path_value)
    {
        path_segment = next_path_segment(path_value);
        if (!path_segment)
            break;
        exec_status = process_command(path_segment, (*mini));
        free(path_segment);
        if (exec_status == 0)
        {
            free(path_copy);
            return 0;
        }
        path_value = strchr(path_value, ':');
        if (path_value)
            path_value++;
    }
    free(path_copy);
    return (exec_status);
}
