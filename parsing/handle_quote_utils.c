#include "../mini.h"

int	skip_quote(char *arg, int start)
{
	int		i;
	char	c;

	if (arg[start] != '\'' && arg[start] != '"')
	{
		while (arg[start] != '\'' && arg[start] != '"')
			start++;
	}
	i = start + 1;
	c = arg[start];
	while (arg[i] && arg[i] != c)
		i++;
	i++;
	return (i);
}

static int	check_quote(char *arg, int start)
{
	int		i;
	char	c;

	i = start + 1;
	c = arg[start];
	while (arg[i] && arg[i] != c)
		i++;
	if (arg[i] != c)
		return (-1);
	return(0);
}

static int	count_quote_both(char *arg)
{
	int	start;
	int	i;

	i = 0;

	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			start = i;
			if (check_quote(arg, start) != 0)
				return (-1);
			i = skip_quote(arg, start);
		}
		else
			i++;
	}
	return (0);
}

int	handle_both(t_token *curr)
{
	char	**quote_mtx;

	if (count_quote_both(curr->arg) == -1)
	{
		printf("quote error, sorry\n");
		return (-1);
	}
	quote_mtx = ft_split_quote(curr->arg);
	if (!quote_mtx)
		return (-1);
	free(curr->arg);
	curr->arg = ft_mystrjoin(quote_mtx);
	if (!curr->arg)
	{
		ft_free_mtx(quote_mtx);
		return (-1);
	}
	ft_free_mtx(quote_mtx);
	return (0);
}

int	ft_new_len(char *old, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (old[i])
	{
		if (old[i] == c)
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
