/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:15:05 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/23 21:10:35 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	cd_builtin(t_mini *mini)
{
	char	old_pwd[4096];
	char	new_pwd[4096];
	
	if (!mini->cmd->arg[0] || mini->cmd->arg[1])
	{
		if (!mini->cmd->arg)
			perror("Error: cd: missing argument");
		else
			perror("Error: cd: too many arguments");
		return (1);
	}
	if(!getcwd(old_pwd, 4096))
		perror("error: cd: getcwd failed");
	if (chdir(mini->cmd->arg[0]) != 0)
	{
		perror("Error: cd");
		return (1);
	}
	if(!getcwd(new_pwd, 4096))
		perror("Error: cd: getcwd failed");
	setenv_builtin("OLDPWD", old_pwd, 1, &mini->env);
	setenv_builtin("PWD", new_pwd, 1, &mini->env);
	return (0);
}
//~ TILDE ???