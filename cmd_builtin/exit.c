/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:20:49 by ltrento           #+#    #+#             */
/*   Updated: 2025/03/04 22:26:23 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int is_numeric(char *num)
{
    int i;

    i = 0;
    if (num[i] == '-' || num[i] == '+')
        i++;
    while (num[i])
    {
        if (!ft_isdigit(num[i]))
            return (1);
        i++;
    }
    return (0);
}

int exit_builtin(t_mini **mini)
{
    int exit_code;

    if (!mini || !(*mini))
		return (1);
    if (!(*mini)->cmd || !(*mini)->cmd->arg)
        exit_code = (*mini)->exit_code;
    else
    {
        if ((*mini)->cmd->arg[0] && !is_numeric((*mini)->cmd->arg[0]))
            exit_code = 255;
        if ((*mini)->cmd->arg[0] && (*mini)->cmd->arg[1])
        {
            printf("minishell: exit: too many arguments\n");
            (*mini)->exit_code = 1;
            return (1);
        }
        else if ((*mini)->cmd->arg[0])
            exit_code = ft_atoi((*mini)->cmd->arg[0]) % 256;
    }
    ft_exit(exit_code, "minishell exiting...", mini);
    return (0);
}