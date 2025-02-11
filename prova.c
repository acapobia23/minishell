/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:32:23 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/11 16:06:15 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"

typedef struct s_env
{
    char            *value;
    struct s_env    *next;
}   t_env;

//check if s1 is the same as s2 until delimiter
int	ft_strcmp_until(char *s1, char *s2, char c)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 != c)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if ((*s1 == c || *s1 == '\0') && (*s2 == c || *s2 == '\0'))
		return (0);
	return (1);
}

//check if string has character inside, if it does return 0, if not 1
int	scan_str(const char *str, char c)
{
	while (str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	scan_environ(t_env **environ, char *name)
{
	t_env	*current;

	current = (*environ);
	while (current)
	{
		if (ft_strcmp_until(current->value, name, "=") == 0)// NEED TO IMPLEMENT UNTIL "="
			return (1);
		current = current->next;
	}
	return (0);
}

char *join_env_var(const char *name, const char *value)
{
    char *joined;
    char *temp;

    temp = ft_strjoin(name, "=");
    if (!temp)
        return (NULL);
    joined = ft_strjoin(temp, value);
    free(temp);
    return (joined);
}

int replace_env(t_env *environ, char *name, char *new_entry)
{
    t_env *current;

    current = environ;
    while (current)
    {
        if (ft_strcmp_until(current->value, name, '=') == 0)
        {
            free(current->value);
            current->value = new_entry;
            return (1);
        }
        current = current->next;
    }
    return (0);
}

int add_env(t_env **environ, char *new_entry)
{
    t_env *current;
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (0);
    new_node->value = new_entry;
    new_node->next = NULL;
    if (!(*environ))
    {
        *environ = new_node;
        return (1);
    }
    current = *environ;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return (1);
}

int	manual_setenv(const char *name, const char *value, int overwrite, t_env **environ)
{
	char	*new_entry;
	
	if (!value || !name || *name == '\0' || !scan_str(name, "="))
		return (-1);
	new_entry = join_env_var(name, value);
	if (!new_entry)
		return (-1);
	if (scan_environ(environ, (char *)name))
	{
		if (overwrite)
			return (replace_env((*environ), (char *)name, new_entry));
		free(new_entry);
		return (0);
	}
	return (add_env(environ, new_entry));
}

int	cd(t_mini **mini)
{
	char	old_pwd[4096];
	char	new_pwd[4096];
	
	args = get_args()//CHECK WITH STRUCT
	if (!args[0] || args[1])//replace with t_mini->t_cmd
	{
		if (!args)
			perror("Error: cd: missing argument");
		else
			perrror("Error: cd: too many arguments");
		return (1);
	}
	if(!getcwd(old_pwd, 4096))
		perror("error: cd: getcwd failed");
	if (chdir(args[0]) != 0)//replace with t_mini->t_cmd
	{
		perror("Error: cd");
		return (1);
	}
	if(!getcwd(new_cwd, 4096))
		perror("Error: cd: getcwd failed");
	manual_setenv("OLDPWD", old_pwd, 1, mini->env);
	manual_setenv("PWD", new_pwd, 1);
	return (0);
}

/*int	check_empty_input(t_token *tokens)
{
	if (!tokens)
		return (1);
	while (tokens)
	{
		if (tokens->type != TOKEN_WHITESPACE)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	check_operator_placement(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_OPERATOR)
		return (1);
	while (tokens->next)
	{
		if (tokens->type == TOKEN_OPERATOR && tokens->next->type == TOKEN_OPERATOR)
			return (1);
		tokens = tokens->next;
	}
	if (tokens->type == TOKEN_OPERATOR)
		return (1);
	return (0);
}

int	check_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_OPERATOR)
		{
			if (tokens->operator == '>' || tokens->operator == '<' ||
				tokens->operator == D_GREATER || tokens->operator == D_LESS)
			{
				if (!tokens->next || tokens->next->type != TOKEN_WORD)
					return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

int	check_quotes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_UNCLOSEDQ)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	check_pipes(t_token *tokens)
{
	if (!tokens || tokens->type == TOKEN_OPERATOR)
		return (1);
	while (tokens->next)
	{
		if (tokens->type == TOKEN_OPERATOR && tokens->operator == '|')
		{
			if (!tokens->next || tokens->next->type == TOKEN_OPERATOR)
				return (1);
		}
		tokens = tokens->next;
	}
	if (tokens->type == TOKEN_OPERATOR && tokens->operator == '|')
		return (1);
	return (0);
}

int	validate_syntax(t_token *tokens)
{
	if (check_empty_input(tokens))
		return (1);
	if (check_operator_placement(tokens))
		return (ft_putstr_fd("Syntax error: misplaced operator\n", 2), 1);
	if (check_redirections(tokens))
		return (ft_putstr_fd("Syntax error: invalid redirection\n", 2), 1);
	if (check_quotes(tokens))
		return (ft_putstr_fd("Syntax error: unclosed quotes\n", 2), 1);
	if (check_pipes(tokens))
		return (ft_putstr_fd("Syntax error: invalid pipe usage\n", 2), 1);
	return (0);
}


void	check_filename_after_redirection(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_OPERATOR)
		{
			if (tokens->operator == '>' || tokens->operator == '<' ||
				tokens->operator == D_GREATER || tokens->operator == D_LESS)
			{
				tokens = tokens->next;
				if (!tokens || (tokens->type != TOKEN_WORD &&
					tokens->type != TOKEN_VARIABLE &&
					tokens->type != TOKEN_SQUOTE &&
					tokens->type != TOKEN_DQUOTE))
				{
					ft_putstr_fd("Syntax error: expected filename after redirection\n", 2);
					return ;
				}
				tokens->type = TOKEN_FILENAME;
			}
		}
		tokens = tokens->next;
	}
}

void	check_command_and_arguments(t_token *tokens)
{
	int	is_command;

	is_command = 1;
	while (tokens)
	{
		if (tokens->type == TOKEN_WHITESPACE || tokens->type == TOKEN_EOL)
		{
			tokens = tokens->next;
			continue ;
		}
		if (tokens->type == TOKEN_OPERATOR)
			is_command = 1;
		else if (is_command)
		{
			if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_SQUOTE ||
				tokens->type == TOKEN_DQUOTE)
				tokens->type = TOKEN_COMMAND;
			else if (tokens->type == TOKEN_VARIABLE || tokens->type == TOKEN_EXIT_STATUS)
				tokens->type = TOKEN_ARGUMENT;
			is_command = 0;
		}
		else
		{
			if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_VARIABLE ||
				tokens->type == TOKEN_EXIT_STATUS)
				tokens->type = TOKEN_ARGUMENT;
		}
		tokens = tokens->next;
	}
}

void	validate_tokens(t_token *tokens)
{
	check_command_and_arguments(tokens);
	check_filename_after_redirection(tokens);
}
*/