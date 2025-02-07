#include "../mini.h"

t_token	*new_token(int start, int end, char *input)
{
	t_token	*new;

	new = NULL;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		free(input);
		return (NULL);
	}
	if (ft_only_operators_word(input, start, end) == 0)
	{
		new->type_token = find_token_type(input[start]);
		new->arg = ft_strcut(start, end, input);
		new->flag = active_flag(new->arg);
		new->next = NULL;
	}
	else
		multiple_token(&new, input, start, end);
	return (new);
}

static int	add_token(t_token **tokens, int start, int end, char *input)
{
	t_token	*new;
	t_token	*current;

	current = NULL;
	new = new_token(start, end, input);
	if (!new)
	{
		clear_tokens(&(*tokens));
		return (-1);
	}
	if (!(*tokens))
		(*tokens) = new;
	else
	{
		current = (*tokens);
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (0);
}

static int	jump_token(int i,const char *input)
{
	int	single;
	int	doubles;
	int	res;

	single = 0;
	doubles = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '\'' && doubles == 0)
			single += 1;
		if (input[i] == '"' && single == 0)
			doubles += 1;
		if (single == 2)
			single = 0;
		if (doubles == 2)
			doubles = 0;
		if (ft_isspace(input[i]) == 0 && single == 0 && doubles == 0)
			break ;
		i++;
	}
	res = i;
	return (res);
}

static t_token	*setup_tokens(const char *input_promt)
{
	t_token	*token;
	int		i;
	int		start;
	char	*input;

	i = 0;
	token = NULL;
	input = ft_strdup(input_promt);
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]) == 0)
			i++;
		start = i;
		i = jump_token(i, input);
		if (add_token(&token, start, i, input) == -1)
		{
			clear_tokens(&token);
			free(input);
			return (NULL);
		}
	}
	free(input);
	return (token);
}

int	parsing(t_mini **mini, const char *input)
{
	t_token	*tokens;

	tokens = setup_tokens(input);
	if (!tokens)
		ft_exit(2, "tokens setup error", &(*mini));
	print_tokens(tokens);
	// if (lexer_tokens(tokens) == -1)//TODO attua l'exspander
	// {
	// 	clear_tokens(&tokens);
	// 	ft_exit(2, "input error", &(*mini));
	// }
	// printf("\n\nAFTER LEXER\n\n");
	// print_tokens(tokens);
	// (*mini)->cmd = set_cmds(tokens);//TODO trasferisce i token in cmd dividendoli
	// if (!(*mini)->cmd)
	// {
	// 	clear_tokens(&tokens);
	// 	ft_exit(2, "set_cmd error", &(*mini));
	// }
	// set_process((*mini)->process, (*mini)->cmd);
	// ft_test(tokens, (*mini));//TODO DEBUG ONLY stampa tutti i campi delle due struct
	clear_tokens(&tokens);// TODOfree tokens
	// check_signal();//TODO
	return (0);
}
