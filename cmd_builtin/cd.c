/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:15:05 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/20 22:18:56 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	cd_builtin(t_mini *mini)
{
	char	old_pwd[4096];
	char	new_pwd[4096];
	
	if (!mini->cmd->args[0] || mini->cmd->args[1])
	{
		if (!mini->cmd->args)
			perror("Error: cd: missing argument");
		else
			perrror("Error: cd: too many arguments");
		return (1);
	}
	if(!getcwd(old_pwd, 4096))
		perror("error: cd: getcwd failed");
	if (chdir(mini->cmd->args[0]) != 0)
	{
		perror("Error: cd");
		return (1);
	}
	if(!getcwd(new_cwd, 4096))
		perror("Error: cd: getcwd failed");
	setenv_builtin("OLDPWD", old_pwd, 1, mini->env);
	setenv_builtin("PWD", new_pwd, 1);
	return (0);
}
//~ TILDE ???