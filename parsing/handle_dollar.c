#include "../mini.h"

char	*cut_value_to_replace(char *arg, int start)
{
	int		end;
	char	*value;

	end = start;
	if (arg[end] == '?')
		end++;
	else
	{
		while (arg[end] != '$' && ft_isalnum(arg[end]) != 0)
			end++;
	}
	value = ft_strcut(start, end, arg);
	if (!value)
		return (NULL);
	return (value);	
}

char	*new_dollar_value(char *arg, int *i, t_mini *mini)
{
	char	*value_rp;
	char	*new;

	value_rp = cut_value_to_replace(arg, ((*i) + 1));
	if (!value_rp)
		return (NULL);
	new = replace_value(value_rp, mini);
	free(value_rp);
	if (!new)
		return (NULL);
	while (arg[(*i)] && arg[(*i)] != '$' && (ft_isalnum(arg[(*i)]) != 0))
		(*i)++;
	return (new);
}

static char	**ft_dollar_mtx(char *arg, int size, t_mini *mini)
{
	char	**mtx;
	int		j;
	int		i;

	mtx = ft_calloc((size + 1), sizeof(char *));
	if (!mtx)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1] != '$')
		{
			mtx[j] = new_dollar_value(arg, &i, mini);
			if (!mtx)
			{
				ft_free_mtx(mtx);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (mtx);
}
int	ft_count_dollar(char *arg)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1] != '$')
			size++;
		i++;
	}
	return (size);
}

int	handle_dollar(t_token *curr, t_mini *mini)
{
	char	**dollar_mtx;
	int		size;
	int		j;
	int		i;

	if (!curr || !curr->arg)
		return (-1);
	size = ft_count_dollar(curr->arg);
	i = 0;
	j = 0;
	dollar_mtx = ft_dollar_mtx(curr->arg, (size), mini);
	if (!dollar_mtx)
		return (-1);
	while (i != -1 && dollar_mtx[j])
	{
		ft_join_dollar(curr, &i, dollar_mtx[j]);//TODO porta i alla fine del value del dollar
		j++;
	}
	return (i);
}
