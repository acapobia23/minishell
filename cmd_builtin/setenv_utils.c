/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:14:31 by ltrento           #+#    #+#             */
/*   Updated: 2025/03/10 16:39:34 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_strcmp_until(char *s1, char *s2, char c)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 != c)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if ((*s1 == c || *s1 == '\0') && (*s2 == c || *s2 == '\0'))
		return (0);
	return (1);
}

int	scan_str(const char *str, char c)
{
	while (str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
