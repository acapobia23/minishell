#include "../mini.h"

char *ft_strcut(int start, int end, char *input)
{
	char	*s;
	int		i;
	int		len;

	i = start;
	if (!input)
		return (NULL);
	while (i < end)
	{
		len++;
		i++;
	}
	i = start;
	s = NULL;
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	len = 0;
	while (i < end)
	{
		s[len++] = input[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

static int	find_end(int start, char *input)
{
	if (input[start] == '|')
		return (start + 1);
	else if (input[start] == '<')
	{
		if (input[start + 1] == '<')
			return (start + 2);
		else
			return (start + 1);
	}
	else if (input[start] == '>')
	{
		if (input[start + 1] == '>')
			return (start + 2);
		else
			return (start + 1);
	}
	return (start + 1);
}

static int	find_token_end(int start, char *str)
{
	int	i;

	i = start;
	if (find_token_type(str[start]) == TOKEN_WORD)
	{
		while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>')
			i++;
		return (i);
	}
	else
		return (find_end(start, str));
	return (start);
}

void	multiple_token(t_token **new, char *input, int start, int end)
{
	t_token	*tmp;
	int		to_end;
	int		to_start;

	to_end = find_token_end(start, input);
	(*new)->type_token = find_token_type(input[start]);
	(*new)->arg = ft_strcut(start, to_end, input);
	(*new)->flag = active_flag((*new)->arg);
	(*new)->next = NULL;
	tmp = (*new);
	to_start = to_end;
	while (to_start < end)
	{
		to_end = find_token_end(to_start, input);
		tmp->next = new_token(to_start, to_end, input);
		if (!tmp)
			return ;
		to_start = to_end;
		tmp = tmp->next;
	}
}
