#include "mini.h"

volatile sig_atomic_t	g_received_signal = 0;

void	case_sigint(int sig)
{
	g_received_signal = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal()
{
	struct sigaction signal;

	signal.sa_handler = case_sigint;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	sigaction(SIGINT, &signal, NULL);
	signal.sa_handler = SIG_IGN;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	sigaction(SIGQUIT, &signal, NULL);
}
