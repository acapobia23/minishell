#include "../mini.h"

static int	ft_new_len(char *old, char c)
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
	printf("new len %i | old len %i\n", len, i);
	return (len);
}

static char	*ft_mystrtrim(char *old, char c)
{
	char	*new;
	int		len;
	int		j;
	int		i;

	i = 0;
	j = 0;
	len = ft_new_len(old, c);
	new = ft_calloc((len + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (old[i])
	{
		if (old[i] != c)
		{
			new[j] = old[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

static int	trim_quote(t_token **curr, char quote)
{
	char	*tmp;

	tmp = ft_strdup((const char *)(*curr)->arg);
	if (!tmp)
		return (-1);
	free((*curr)->arg);
	(*curr)->arg = ft_mystrtrim(tmp, quote);
	free(tmp);
	if (!(*curr)->arg)
		return (-1);
	return (0);
}

static int	count_quote(char *str, char quote)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == quote)
			counter++;
	}
	if (counter % 2 != 0)
		return (-1);
	return (0);
}

static int	handle_quote(t_token **curr, char quote)
{
	if (count_quote((*curr)->arg, quote) == -1)
	{
		if (quote == '\'')
			printf("single quote error, i can't process the input\n");
		if (quote == '"')
			printf("double quote error, i can't process the input\n");
		return(-1);	
	}
	if (quote == '\'')
	{
		if (trim_quote(&(*curr), quote) == -1)
			return (-1);
	}
	else if (quote == '"')
	{
		if (trim_quote(&(*curr), quote) == -1)
			return (-1);
	}
	return (0);
}

int	lexer_tokens(t_token **tokens)
{
	t_token	*curr;

	curr = (*tokens);
	while (curr)
	{
		if (curr->flag->double_quotes == true)
		{
			if (handle_quote(&curr, '"') == -1)
				return (-1);
		}
		if (curr->flag->singol_quotes == true)
		{
			if (handle_quote(&curr, '\'') == -1)//sono invertiti da risolvere pero done 
				return (-1);
		}
		// if (find_flag(curr->flag, '$') && find_flag(curr->flag, '\'') == -1)
		// {
		// 	if (handle_dollar(curr) == -1)
		// 		return (-1);
		// }
		curr = curr->next;
	}
	return (0);
}
