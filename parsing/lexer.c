#include "../mini.h"
//TO SEE IF IS NECESSARY
int	find_flag(t_flag *flag, char *c)
{
	printf("char c find %s \n", c);
	if (c[0] == '"' && flag->double_quotes == true)
	return (0);
	else if (c[0] == '\'' && flag->singol_quotes == true)
		return (0);
	else if (c[0] == '$' && flag->dollar == true)
		return (0);
	else if (c[0] == '<' && flag->redirect_input == true)
		return (0);
	else if (c[0] == '>' && flag->redirect_output == true)
		return (0);
	else if (c[0] == '>' && c[1] == '>' && flag->append_mode == true)
		return (0);
	else if (c[0] == '|' && flag->pipe == true)
		return (0);
	else if (c[0] == '<' && c[1] == '<' && flag->delimiter == true)
		return (0);
	return (-1);
}

static int	ft_check_double_pipe(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (!curr)
		return (-1);
	while (curr)
	{
		if (curr->flag->pipe == true)
		{
			if (curr->next == NULL || curr->next->flag->pipe == true)
			{
				printf("double pipe i can't process the input\n");
				return (-1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	lexer_tokens(t_token **tokens, t_mini *mini)
{
	t_token	*curr;

	if (ft_check_double_pipe((*tokens)) == -1)
		return (-1);
	curr = (*tokens);
	while (curr)
	{
		if ((curr->flag->singol_quotes == true || curr->flag->double_quotes == true) || (curr->flag->singol_quotes == true && curr->flag->double_quotes == true))
		{
			if (curr->flag->dollar == true)
			{
				if (handle_dollar_quoted(curr, mini) == -1)
				return (-1);
			}				
			if (handle_quotes_managar(curr) == -1)
			return (-1);
		}
		else if (curr->flag->dollar == true)
		{
			if (handle_dollar(curr, mini) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}
