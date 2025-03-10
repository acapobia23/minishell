#include "../mini.h"



t_token	*new_token(int start, int end, char *input)
{
	t_token	*new;

	new = NULL;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type_token = find_token_type(input[start]);
	new->arg = ft_strcut(start, end, input);
	if (!new->arg)
	{
		free(new);
		return (NULL);
	}
	new->flag = active_flag(new->arg);
	new->next = NULL;
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

int	jump_token(int i,const char *input)
{
	int	j;

	if (find_token_type(input[i]) == TOKEN_WORD)
		j = find_word_end(i, (char *)input);
	else
		j = find_op_end(i, (char *)input);
	return (j);
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
		return (1);
	if (lexer_tokens(&tokens, (*mini)) == -1)
	{
		clear_tokens(&tokens);
		return (-1);
	}
	set_cmds(tokens, &(*mini));// trasferisce i token in cmd dividendoli
	if (!(*mini)->cmd)
	{
		clear_tokens(&tokens);
		printf("set_cmd error\n");
		return (1);
	}
	//print_cmds((*mini)->cmd, (*mini)->process->n_pid);
	// set_process((*mini)->process, (*mini)->cmd);
	// ft_test(tokens, (*mini));//TODO DEBUG ONLY stampa tutti i campi delle due struct
	clear_tokens(&tokens);// TODOfree tokens
	// check_signal();//TODO
	return (0);
}
