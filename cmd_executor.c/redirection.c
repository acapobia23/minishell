#include "../mini.h"

static int	red_out(t_mini *mini)
{
	int	fd;

	fd = open(mini->cmd->file ,O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("redirection error: fd invalid\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		printf("dup2 error: fd invalid\n");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	red_append(t_mini *mini)
{
	int	fd;

	fd = open(mini->cmd->file ,O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("redirection error: fd invalid\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		printf("dup2 error: fd invalid\n");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	red_input(t_mini *mini)
{
	int	fd;

	fd = open(mini->cmd->file ,O_RDONLY);
	if (fd < 0)
	{
		printf("redirection error: fd invalid\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		printf("dup2 error: fd invalid\n");
		return (-1);
	}
	close(fd);
	return (0);
}

int	do_redirect_one_cmd(t_mini *mini)
{
	if (mini->cmd->redirect[0] == '<')
		return (red_input(mini));
	else if(mini->cmd->redirect[1] == '>')
		return (red_append(mini));
	else
		return (red_out(mini));
	return (0);
}