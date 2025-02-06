#include "mini.h"

int	main(int ac, char **arg, char **envp)
{
	t_mini	*mini;
	char	*input;

	if (ac != 1 && arg)
		ft_exit(0, "no addictional argument required", &mini);
	mini = NULL;
	if (setup_mini(&mini, envp) == -1)
		ft_exit(-1, "setup mini error", &mini);
	setup_signal();
	while (1)
	{
		input = NULL;
		input = readline("capo-mini->");
		if(!input)
			ft_exit(0, "capo-mini exit", &mini);
		add_history(input);
		if (parsing(&mini, input) == 0)//TODO at the end check cmd o operetors
			printf("parsing done\n");
		// 	cmd_executor(&mini);//TODO check se i comandi esistono, esegue libera dentro di se i campi necessari
		free(input);
	}
	return (0);
}
