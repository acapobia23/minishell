#ifndef MINI_H
# define MNI_H
#endif

#include "Libft/libft.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <readline/readline.h>
#include <readline/history.h>
//aggiungere segnali se trova ctlr c ctrl \ ctrl d in mezzo ai processi figli
extern volatile sig_atomic_t	g_received_signal;

void print_tokens(t_token *token);//test only
int				handle_dollar_quoted(t_token *curr, t_mini *mini);
char			*new_dollar_value(char *arg, int *i, t_mini *mini);
char			*cut_value_to_replace(char *arg, int start);
int	            ft_count_dollar(char *arg);
int	            handle_dollar(t_token *curr, t_mini *mini);
char	        *replace_value(char *value_rp,t_mini *mini);
void	        ft_join_dollar(t_token *curr, int *i, char *value);
void        	ft_free_mtx(char **matrix);
char	        *ft_mystrjoin(char **mtx);
int         	handle_both(t_token *curr);
char	        **ft_split_quote(char *arg);
int	            skip_quote(char *arg, int start);
int             ft_new_len(char *old, char c);
char	        *ft_mystrtrim(char *old, char c);
int	            trim_quote(t_token **curr, char quote);
int         	count_quote(char *str, char quote);
int	            handle_quote(t_token **curr, char quote);
int	            handle_quotes_managar(t_token *curr);

int	            lexer_tokens(t_token **tokens, t_mini *mini);
int	            find_flag(t_flag *flag, char *c);
int	            find_word_end(int start, char *input);
int	            find_op_end(int start, char *input);
int	            find_token_end(int start, char *str, int end);
void			clear_tokens(t_token **tokens);
int	            jump_token(int i,const char *input);
t_token			*new_token(int start, int end, char *input);
t_flag			*active_flag(char *arg);
char 			*ft_strcut(int start, int end, char *input);
t_token_type	find_token_type(char c);
int				parsing(t_mini **mini, const char *input);
void			ft_free_env(t_env **env);
int				setup_mini(t_mini **mini,char **envp);
void			ft_clear_mini(t_mini **mini);
void			ft_exit(int	exit_code, char	*s, t_mini **mini);
void			case_sigint(int sig);
void			setup_signal();

