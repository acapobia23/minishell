#include "../mini.h"

// int	pipe_case(t_mini **mini)
// {
// 	int	i;
// 	int	pid;
// 	int	n_cmd;
// 	int	*pipes[2];

// 	n_cmd = (*mini)->process->n_pid;
// 	pipes = malloc(sizeof(int[2]) * (n_cmd - 1));
// 	if (!pipes)
// 		return (-1);
// 	i = 0;
// 	while (i < n_cmd)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			free(pipes);
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < n_cmd)
// 	{
// 		pid = fork()
// 	}
	
	

// }

static int check_builtin(char *cmd, t_mini **mini)
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

int	one_cmd(t_mini **mini)
{
	int	exit_code;
	if (check_builtin((*mini)->cmd->cmd, &(*mini)) == 1)
	{
		exit_code = exec_cmd(mini, (*mini)->cmd->cmd);
		return (exit_code);
	}
	else
	{
		printf("%s: command not found (pid = %d)\n", (*mini)->cmd->cmd, (*mini)->process->n_pid);
		return (-1);
	}
	return (0);
}