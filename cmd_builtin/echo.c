/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:31:22 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/27 16:10:55 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	check_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

static void	print_arguments(char **arg, int i)
{
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

int	echo_builtin(t_mini *mini)
{
	int	no_newline;
	int	i;

	i = 0;
	no_newline = 0;
	if (!mini->cmd->arg || !mini->cmd->arg[0])
		return (-1);
	while (mini->cmd->arg[i] && check_n_option(mini->cmd->arg[i]))
	{
		no_newline = 1;
		i++;
	}
	print_arguments(mini->cmd->arg, i);
	if (!no_newline)
		printf("\n");
	return (0);
}
