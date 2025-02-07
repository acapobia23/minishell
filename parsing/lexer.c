#include "../mini.h"

static void	dollar_case(t_token *token)
{

}

static int	trim_quotes(t_token *token, char c)
{
	int		i;
	int		quotes;
	char	*tmp;

	i = -1;
	quotes = 0;
	while(token->arg[++i])
	{
		if (token->arg[i] == c)
			quotes++;
	}
	if (quotes < 2 || quotes % 2 != 0)
		return (-1);
	tmp = ft_strtrim((const char*)token->arg, c);
	if (!tmp)
		return (-1);
	free(token->arg);
	token->arg = ft_strdup((const char*)tmp);
	if (!token->arg)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

static	int	find_flag(t_flag flag, const char *str)
{
	if (str[0] == '\'')
	{
		if (flag.singol_quotes == true)
			return (0);
		else
			return (-1);
	}
	if (str[0] == '"')
	{
		if (flag.double_quotes == true)
			return (0);
		else
			return (-1);
	}
	if (str[0] == '$')
	{
		if (flag.dollar == true)
			return (0);
		else
			return (-1);
	}
}

int	lexer_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (find_flag(tmp->flag, "'") == 0)
		{
			if (trim_quotes(tmp, '\'') == -1)// check se sono doppie senno return -1
			{
				printf("quotes ' sorry i can't go for the execution\n");
				return (-1);
			}
		}
		if(find_flag(tmp->flag, "\"") == 0)
		{
			if (trim_quotes(tmp, '"') == -1)// check se sono doppie senno return -1
			{
				printf("only one \" sorry i can't go for the execution\n");
				return (-1);
			}
		}
		if (find_flag(tmp->flag, "$") == 0 && find_flag(tmp->flag, "\"") == 0)
			dollar_case(tmp);//TODO
		tmp = tmp->next;
	}
	return (0);
}