/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:14:50 by ltrento           #+#    #+#             */
/*   Updated: 2025/02/21 17:53:41 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int    pwd_builtin(void)
{
    char    pwd[4096];

    if (!getcwd(pwd, sizeof(pwd)))
    {
        perror("pwd");
        return (1);
    }
    else
        printf("%s\n", pwd);
    return (0);
}