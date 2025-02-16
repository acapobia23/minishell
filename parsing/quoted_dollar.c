#include "../mini.h"

static int	case_dollar_normal(int pos,t_token *curr, t_mini *mini)
{
	char	*value;

	value = new_dollar_value(curr->arg, &pos, mini);
	if (!value)
		return (-1);
	ft_join_dollar(curr, &pos, value);
	printf("value to replace : %s\n", value);
	printf("new str : %s\n", curr->arg);
	free(value);
	if (pos == -1)
		return (-1);
	return (0);
}

static int	handle_dollar_limit(t_token *curr, int pos)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = ft_strdup((const char *)curr->arg);
	if (!tmp)
		return (-1);
	free(curr->arg);
	len = ft_strlen((const char *)tmp) - 1;
	curr->arg = ft_calloc((len + 1), sizeof(char));
	if (!curr->arg)
	{
		free(tmp);
		return (-1);
	}
	while (++i < pos)
		curr->arg[i] = tmp[i];
	j = i;
	i++;
	while (j < len)
	{
		curr->arg[j] = tmp[i];
		j++;
		i++;
	}
	free(tmp);
	printf("new str : %s\n", curr->arg);
	return (0);
}

static int	inside_single(int pos, char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i] && i < pos)
	{
		if (input[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (0);
	return (-1);
}

static int	find_pos(int count, char *input)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			c++;
			if (c == count)
				return (i);
		}
		i++;
	}
	if (c == 0)
		return (-1);
	return (i);
}
static int	quoted_dollar(int count, t_token *curr, t_mini *mini)
{
	int	pos;

	pos = find_pos(count, curr->arg);//-1 se non trova nada ma non deve tornare in handle errore
	if (pos == -1)
		return (0);
	printf("pos trovata : %c\n", curr->arg[pos]);
	if (inside_single(pos, curr->arg) == 0)// 0 il dollaro corrente è dentro le singole
		return (0);
	else if (curr->arg[pos + 1] == '\'' || curr->arg[pos + 1] == '"')
	{
		if (handle_dollar_limit(curr, pos) == -1)// toglie il dollaro e basta
			return (-1);
		else
			return (1);
	}
	else
	{
		if (case_dollar_normal(pos, curr, mini) == -1)//TODO gestisce normalmente il caso
			return (-1);
		else
			return (1);
	}
	return (0);
}

int	handle_dollar_quoted(t_token *curr, t_mini *mini)
{
	int		count;
	int		check;
	int		i;

	count = ft_count_dollar(curr->arg);
	printf("count : %i\n", count);
	if (count == 0)
		return (0);
	i = 1;
	while (i <= count)
	{
		printf("i count : %i\n", i);
		check = quoted_dollar(i, curr, mini);// 1 stringa modificata quindi rifare il conteggio
		if (check == 1)
		{
			count = ft_count_dollar(curr->arg);
			i = 0;
		}
		else if (check == -1)
			return (-1);
		i++;
	}
	return (0);
}
