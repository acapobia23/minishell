#include "../mini.h"
//toglie il segmento da input e crea il token o due a seconda del caso
static t_token	*new_token(int start, int end, const char **input)
{
	t_token	*new;

	new = NULL;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		free((*input));
		return (NULL);
	}
	if (ft_only_operators_word((*input, start, end)) == -1)//TODO
	{
		new->type_token = find_token_type((*input));//TODO
		new->arg = ft_strcut(start, end, &(*input));//TODO
		new->flag = active_flag(new->arg, new->token);//TODO
		new->next = NULL;
	}
	else
		multiple_token_str(&new, &(*input));//TODO se !new->next qui fa free di new e lo setta a null
	return (new);
}

static int	add_token(t_token **tokens, int start, int end, char **input)//DA aggiunge se trova redirect o pipe
{
	t_token	*new;
	t_token	*current;

	current = NULL;
	new = new_token(start, end, &(*input));//TODO crea qui in caso i piu token
	if (!new)
	{
		clear_tokens(&(*tokens));//TODO
		return (-1);
	}
	if (!(*tokens))
		(*tokens) = new;
	else
	{
		current = (*tokens);
		while (current->next != NULL)
			current = current->next;
		current = new;
	}
	return (0);
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
		if (!input[i])
			break;
		i = jump_token(i, input);//TODO
		if (i == -1 || add_token(&token, start, i, &input) == -1)//TOCOMPLETE tronca quel segmento e vede se è solo o sono due, check se esiste token, se non esiste crea la testa senno aggiunge in coda in caso di errore libera token
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

	tokens = setup_tokens(input);//TODO crea i token e setta flag
	if (!tokens)
		ft_exit(2, "tokens setup error", &(*mini));
	// if (lexer_tokens(tokens) == -1)//TODO attua l'exspander
	// {
	// 	clear_tokens(&tokens);
	// 	ft_exit(2, "lexer tokens error", &(*mini));
	// }
	// (*mini)->cmd = set_cmds(tokens);//TODO trasferisce i token in cmd dividendoli
	// if (!(*mini)->cmd)
	// {
	// 	clear_tokens(&tokens);
	// 	ft_exit(2, "set_cmd error", &(*mini));
	// }
	// set_process((*mini)->process, (*mini)->cmd);
	// ft_test(tokens, (*mini));//TODO DEBUG ONLY stampa tutti i campi delle due struct
	// clear_tokens(&tokens);//free tokens
	// check_signal();//TODO
	return (0);
}
