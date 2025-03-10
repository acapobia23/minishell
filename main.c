#include "mini.h"

int	main(int ac, char **arg, char **envp)
{
	t_mini	*mini = NULL;
	char	*input;
	(void)arg;
	if (ac != 1)
		ft_exit(0, "no addictional argument required", &mini);
	mini = ft_calloc(1, sizeof(t_mini));
	if (!mini)
		ft_exit(-1, "memory allocation failed", &mini);
	mini->env = NULL;
	mini->cmd = NULL;
	mini->process = NULL;
	if (setup_mini(&mini, envp) == -1)// ARRAY DI T_CMD??? IN MODOD DA GESTIRE PIU COMANDI ????
		ft_exit(-1, "setup mini error", &mini);
	setup_signal();
	while (1)
	{
		input = NULL;
		input = readline("capo-mini->");
		if(!input)
			ft_exit(0, "capo-mini exit", &mini);
		add_history(input);
		parsing(&mini, input);
		cmd_executor(&mini);
		ft_free_cmd(&mini);
		free(input);
	}
	return (0);
}
