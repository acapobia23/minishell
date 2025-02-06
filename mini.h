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

int	    parsing(t_mini **mini, const char *input);
void	ft_free_env(t_env **env);
int	    setup_mini(t_mini **mini,char **envp);
void	ft_clear_mini(t_mini **mini);
void    ft_exit(int	exit_code, char	*s, t_mini **mini);
void	case_sigint(int sig);
void	setup_signal();

