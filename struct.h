#ifndef STRUCT_H
# define STRUCT_H
#endif

#include <stdbool.h>

typedef struct	s_dollar
{
	char	**mtx;
	int		new_len;
}			t_dollar;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
}			t_token_type;

typedef struct s_flag
{
	bool	singol_quotes;
	bool	double_quotes;
	bool	dollar;
	bool	redirect_input;
	bool	redirect_output;
	bool	append_mode;
	bool	pipe;
	bool	delimiter;
}			t_flag;

typedef struct s_token
{
	t_token_type	type_token;
	char			*arg;
	t_flag			*flag;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	char	*redirect;
	char	*file;
	bool	flag_cmd;//vede se è un cmd o una redirect
}			t_cmd;

typedef struct s_pid
{
	int	n_pid;
	int	*id_current;
}			t_pid;

typedef struct s_export
{
	char			*exspander;
	char			*values;
	struct s_export	*next;
}			t_export;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_mini
{
	t_pid		*process;
	t_cmd		*cmd;
	int			exit_code;
	t_env		*env;
}			t_mini;