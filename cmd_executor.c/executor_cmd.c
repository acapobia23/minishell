#include "../mini.h"
// int exit_code = (status >> 8) % 256; all'ultimo waitpid per exit code

static void	wait_take_exit_code(t_mini **mini, int *pid, int n_cmd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n_cmd)
	{
		waitpid(pid[i], &status, 0);
		(*mini)->exit_code = (status >> 8) % 256;
	}
}

static void	pipe_exec(int n_cmd, int **pipes, t_mini **mini, int curr_cmd)
{
	int	i;

	i = -1;
	while (++i < n_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	if (ft_isbuiltin((*mini)->cmd[curr_cmd].cmd) == 0)
		builtin_exec(&(*mini), curr_cmd);
	else
		process_exec(&(*mini), curr_cmd);//crea copia di mini e la passa a syscommand in cui in cmd[0] c'è il comando corrente di cuur_cmd
}

int	pipe_loop(int n_cmd, int **pipes, t_mini **mini)
{
	int	*pid;
	int	i;

	i = -1;
	pid = ft_calloc((n_cmd), sizeof(int));
	while (++i < n_cmd)//test
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			perror("fork error");
			return (-1);
		}
		if (pid[i] == 0)//figlio
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < n_cmd - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			pipe_exec(n_cmd, pipes, &(*mini), i);
		}
	}
	close_pipe(pipes, n_cmd);
	wait_take_exit_code(&(*mini), pid, n_cmd);
	free(pid);
	return (0);
}

int	pipe_case(t_mini **mini)
{
	int	i;
	int	n_cmd;
	int	**pipes;

	n_cmd = (*mini)->process->n_pid;
	pipes = (int **)malloc(sizeof(int *) * (n_cmd - 1));
	if (!pipes)
		return (-1);
	i = 0;
	while (i < n_cmd - 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (!pipes[i])
			return (ft_free_pipe(pipes, "malloc error\n", i));
		if (pipe(pipes[i]) == -1)
			return (ft_free_pipe(pipes, "pipe create error\n", i));
		i++;
	}
	if (pipe_loop(n_cmd, pipes, &(*mini)) != 0)//setta dentro exit code
	{
		free(pipes);
		return ((*mini)->exit_code);
	}
	ft_free_pipes(pipes, (n_cmd - 1));
	return (0);
}
void	builtin_exec(t_mini **orig, int curr_cmd)
{
	int		code_exit;
	char	*cmd;
	t_mini	*mini;

	mini = ft_copy_mini((*orig), curr_cmd);
	cmd = ft_strdup((const char *)(*orig)->cmd[curr_cmd].cmd);
    if (!mini || !cmd)
        return ;
    if (ft_strcmp((const char *)cmd, "cd") == 0)
        code_exit = cd_builtin(mini);
    if (ft_strcmp((const char *)cmd, "echo") == 0)
        code_exit = echo_builtin(mini);
    if (ft_strcmp((const char *)cmd, "env") == 0)
        code_exit = env_builtin(&mini);
    if (ft_strcmp((const char *)cmd, "exit") == 0)
        code_exit = exit_builtin(&mini);
    if (ft_strcmp((const char *)cmd, "export") == 0)
        code_exit = export_builtin(mini);
    if (ft_strcmp((const char *)cmd, "pwd") == 0)
        code_exit = pwd_builtin();
	else if (ft_strcmp((const char *)cmd, "unset") == 0)
		code_exit = unset_builtin(&mini);
	(*orig)->exit_code = code_exit;
	free(cmd);
	ft_clear_mini(&mini);
	if (code_exit != 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}




