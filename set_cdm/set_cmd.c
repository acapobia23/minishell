#include "../mini.h"

static void	put_cmd(t_token **curr, t_cmd *command)
{
	command->cmd = ft_strdup((const char *)(*curr)->arg);
	(*curr) = (*curr)->next;
}

static void	put_redirect(t_token **curr, t_cmd *cmd)
{
	cmd->flag_cmd = true;
	cmd->redirect = ft_strdup((const char *)(*curr)->arg);
	(*curr) = (*curr)->next;
	if (!(*curr))
	{
		printf("error on redirect sorry: missing namefile after\n");
		return ;
	}
	cmd->file = ft_strdup((const char *)(*curr)->arg);
	(*curr) = (*curr)->next;
}

int	make_cmd(t_cmd *cmd, t_token **curr)
{
	int	counter;

	if (!(*curr))
		return (0);
	counter = 1;
	while ((*curr) && (*curr)->flag->pipe == false)
	{
		if ((*curr)->type_token == TOKEN_OPERATOR)
			put_redirect(&(*curr), cmd);
		else if (counter == 1)
			put_cmd(&(*curr), cmd);
		else if (counter > 1)
			put_arg_cmd(&(*curr), cmd);
		counter++;
	}//in put.. scorrrere curr
	// if (check_cmd(cmd) == -1)
	// 	return (-1);
	if ((*curr))
		(*curr) = (*curr)->next;
	return (0);
}

static int	ft_count_cmd(t_token *tokens)
{
	t_token	*curr;
	int		size;

	curr = tokens;
	size = 0;

	while (curr)
	{
		size++;
		while (curr && curr->flag->pipe == false)
			curr = curr->next;
		if (curr)
			curr = curr->next;
	}
	return (size);
}

static t_cmd	*ft_init_ar_cmd(t_token *tokens, t_mini *mini)
{
	t_cmd	*cmd;
	int		size;

	size = ft_count_cmd(tokens);
	mini->process->n_pid = size;
	cmd = ft_calloc(size, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	set_cmds(t_token *tokens, t_mini **mini)
{
	int		i;
	t_token	*curr;

	curr = tokens;
	i = -1;
	(*mini)->cmd = ft_init_ar_cmd(tokens, (*mini));//conta i cmd e li alloca, setta pid
	if (!(*mini)->cmd)
		return ;
	while (++i < (*mini)->process->n_pid)
	{
		if (make_cmd(&(*mini)->cmd[i], &curr) == -1)//TODO setta i comandi e scorre curr per i prossimi cmd se curr !NULL
		{
			ft_free_cmd((*mini));
			return ;
		}
	}
}
