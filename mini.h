#ifndef MINI_H
# define MNI_H
#endif

#include "libft/libft.h"
#include "struct.h"
#include <stddef.h>
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

/*void print_cmds(t_cmd *cmds, int size);
void print_tokens(t_token *token);//test only*/
int				make_cmd(t_cmd *cmd, t_token **curr);
void			set_cmds(t_token *tokens, t_mini **mini);
void			put_arg_cmd(t_token **curr, t_cmd *cmd);
void			ft_free_cmd(t_mini **mini);
int				check_cmd(t_cmd *cmd);
/*token*/
int				handle_dollar_quoted(t_token *curr, t_mini *mini);
char			*new_dollar_value(char *arg, int *i, t_mini *mini);
char			*cut_value_to_replace(char *arg, int start);
int	    		ft_count_dollar(char *arg);
int				handle_dollar(t_token *curr, t_mini *mini);
char			*replace_value(char *value_rp,t_mini *mini);
void			ft_join_dollar(t_token *curr, int *i, char *value);
void			ft_free_mtx(char **matrix);
char			*ft_mystrjoin(char **mtx);
int 			handle_both(t_token *curr);
char			**ft_split_quote(char *arg);
int				skip_quote(char *arg, int start);
int				ft_new_len(char *old, char c);
char			*ft_mystrtrim(char *old, char c);
int	    		trim_quote(t_token **curr, char quote);
int 			count_quote(char *str, char quote);
int	    		handle_quote(t_token **curr, char quote);
int	    		handle_quotes_managar(t_token *curr);
int	    		lexer_tokens(t_token **tokens, t_mini *mini);
int	    		find_flag(t_flag *flag, char *c);
int	    		find_word_end(int start, char *input);
int	    		find_op_end(int start, char *input);
int	    		find_token_end(int start, char *str, int end);
void			clear_tokens(t_token **tokens);
int	    		jump_token(int i,const char *input);
t_token			*new_token(int start, int end, char *input);
t_flag			*active_flag(char *arg);
char 			*ft_strcut(int start, int end, char *input);
t_token_type	find_token_type(char c);
int				parsing(t_mini **mini, const char *input);
/*init*/
void			ft_free_env(t_env **env);
int				setup_mini(t_mini **mini,char **envp);
void			ft_clear_mini(t_mini **mini);
void			ft_exit(int	exit_code, char	*s, t_mini **mini);
void			case_sigint(int sig);
void			setup_signal();
/*check_execute_cmd*/
int	cmd_executor(t_mini **mini);
int	check_cmnd(char *cmd, t_mini **mini);
int    check_syscmd(t_mini **mini);
char    *get_path_root(char **path, char *cmd);
int	cd_builtin(t_mini *mini);
int	echo_builtin(t_mini *mini);
int env_builtin(t_mini **mini);
int    export_builtin(t_mini *mini);
int    print_declare_x_var(t_env *env);
char	*ret_value(const char *prefix, const char *env);
void    concatenate_value(char *value, char *equal, size_t total_len);
int    setenv_export(char *str, t_env *environ);
char    *return_var_value(char *str, char delimiter);
int    pwd_builtin(void);
int	scan_str(const char *str, char c);
int ft_strcmp_until(char *s1, char *s2, char c);
int	setenv_builtin(const char *name, const char *value, int overwrite, t_env **environ);
int add_env(t_env **environ, char *new_entry);
int replace_env(t_env *environ, char *name, char *new_entry);
char *join_env_var(const char *name, const char *value);
int unset_builtin(t_mini **mini);
int remove_env_var(t_env **env, char *arg);
int check_var_name(char *str);
int	scan_environ(t_env **environ, char *name);
int syscommand(t_mini **mini);
int process_command(char *path_value, t_mini *mini);
int	exec_cmd(t_mini **mini, char *cmd);
int    execute_syscommand(char *path_root, t_mini *mini);
char    *next_path_segment(char *path_value);
char    *get_path_root_cmd(char *path, char *cmd);
int exit_builtin(t_mini **mini);
void    free_matrix(char **matrix);