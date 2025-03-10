/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:38:34 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/23 21:23:36 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int env_builtin(t_mini **mini)
{
    t_env   *current;

    current = (*mini)->env;
    if (!current || !current->value)
    {
        write(2, "env: No environment available\n", 31);
        return (1);
    }
    if ((*mini)->cmd->arg && (*mini)->cmd->arg[0])
    {
        write(2, "env: No arguments allowed\n", 26);
        return (127);
    }
    while(current)
    {
        printf("%s\n", current->value);
        current = current->next;
    }
    return (0);
}