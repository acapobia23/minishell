#include "../mini.h"

static int	find_both_case(char *arg)
{
	int	sing;
	int	doub;
	int	i;

	i = 0;
	sing = 0;
	doub = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			sing = 1;
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
		}
		if (arg[i] == '"')
		{
			doub = 1;
			i++;
			while (arg[i] && arg[i] != '"')
				i++;
		}
		i++;
	}
	if (sing == 1 && doub == 1)
		return (0);
	else
		return (-1);
}

static void	active_other_case(t_flag *new, char *arg)
{
	int	i;

	i = 0;

	if (arg[i] == '|')
		new->pipe = true;
	if (arg[i] == '<')
	{
		if (arg[i + 1] == '<')
			new->delimiter = true;
		else
			new->redirect_input = true;
	}
	if (arg[i] == '>')
	{
		if (arg[i + 1] == '>')
			new->append_mode = true;
		else
			new->redirect_output = true;
	}
}


static int	find_quotes(char *arg)
{
	int	q_single;
	int	q_double;
	int	i;

	q_single = 0;
	q_double = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' && q_single == 0)
			q_double++;
		if (arg[i] == '\'' && q_double == 0)
			q_single++;
		i++;
	}
	if (q_double != 0 && q_single == 0)
		return (2);
	else if (q_single != 0 && q_double != 0)
		return (1);
	else if (q_single == 1 && q_double == 0)
		return (-1);
	else if (q_double == 1 && q_single == 0)
		return (-1);
	else if (find_both_case(arg) == 0)
		return (3);
	return (0);
}

static void	flag_init(t_flag *new)
{
	new->singol_quotes = false;
	new->double_quotes = false;
	new->dollar = false;
	new->redirect_input = false;
	new->redirect_output = false;
	new->append_mode = false;
	new->pipe = false;
	new->delimiter = false;	
}

t_flag	*active_flag(char *arg)
{
	t_flag	*new;
	int	i;
	int	quotes;

	new = ft_calloc(1, sizeof(t_flag));
	if (!new)
		return (NULL);
	flag_init(new);
	quotes = find_quotes(arg);//TODO 0 = nessuna, 1 = singole, 2 = doppie 3 = entrmabe ma separate
	if (quotes == 1)
		new->singol_quotes = true;
	else if (quotes == 2)
		new->double_quotes = true;
	else if (quotes == 3)
	{
		new->singol_quotes = true;
		new->double_quotes = true;
	}
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '$' && (new->singol_quotes == false || (new->singol_quotes == true && new->double_quotes == true)))
		{
			new->dollar = true;
			break ;
		}
	}
	active_other_case(new, arg);
	return (new);
}

t_token_type	find_token_type(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TOKEN_OPERATOR);
	return (TOKEN_WORD);
}

