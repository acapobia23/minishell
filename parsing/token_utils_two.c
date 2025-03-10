#include "../mini.h"

int	find_word_end(int start, char *input)
{
	int		i;
	char	quotes;

	quotes = '\0';
	i = start;
	if (input[start] == '\0')
		return (start);
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quotes == '\0')
				quotes = input[i];
			else if (quotes == input[i])
				quotes = '\0';
		}
		if (input[i] == '|' && quotes == '\0')
			break ;
		if (ft_isspace(input[i]) == 0 && quotes == '\0')
			break ;
		i++;
	}
	return (i);
}

char *ft_strcut(int start, int end, char *input)
{
    char    *s;
    int     i;
    int     len;

    if (!input || start < 0 || end <= start || end > ft_strlen(input))
        return (NULL);

    len = end - start;
    s = (char *)malloc((len + 1) * sizeof(char));
    if (!s)
        return (NULL);
    i = 0;
    while (i < len)
    {
        s[i] = input[start + i];
        i++;
    }
    s[len] = '\0';
    return (s);
}


int	find_op_end(int start, char *input)
{
	int	i;

	i = start;
	if (input[i] == '|')
		i++;
	else if (input[i] == '<')
	{
		while (input[i] == '<')
			i++;
	}
	else if (input[i] == '>')
	{
		while (input[i] == '>')
			i++;
	}
	return (i);
}

int	find_token_end(int start, char *str, int end)
{
	if (find_token_type(str[start]) == TOKEN_WORD)
		return (end);
	else
		return (find_op_end(start, str));
	return (start);
}
