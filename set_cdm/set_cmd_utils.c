#include "../mini.h"

int	check_cmd(t_cmd *cmd)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (cmd->flag_cmd == true)
	{
		if (!cmd->redirect)
			return (-1);
		if (!cmd->file)
			return (-1);
	}
	if (!cmd->cmd)
		return (-1);
	if (cmd->arg)
	{
		while (cmd->arg[i] != NULL)
			i++;
		if (i != 0)
		{
			while (c < i)
			{
				if (!cmd->arg[c])
					return (-1);
				c++;
			}
		}
	}
	return (0);
}

static	int	ft_count_arg(t_token *curr)
{
	t_token	*tmp;
	int		size;

	size = 0;
	tmp = curr;
	while (tmp && tmp->type_token != TOKEN_OPERATOR)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	put_arg_cmd(t_token **curr, t_cmd *cmd)
{
	int		i;
	int		size;
	i = 0;
	size = ft_count_arg((*curr));
	cmd->arg = ft_calloc((size + 1), sizeof(char *));
	if (!cmd->arg)
		return ;
	while (i < size)
	{
		cmd->arg[i] = ft_strdup((const char *)(*curr)->arg);
		if (!cmd->arg[i])
			return ;
		i++;
		(*curr) = (*curr)->next;
	}
}
