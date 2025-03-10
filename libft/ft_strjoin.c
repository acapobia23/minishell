/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:24:18 by acapobia          #+#    #+#             */
/*   Updated: 2025/03/06 16:22:50 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
    char	*ptr;
    size_t	len_1;
    size_t	len_2;
    size_t	i;
    size_t	j;

    if (!s1 || !s2)
        return (NULL);

    len_1 = ft_strlen(s1);
    len_2 = ft_strlen(s2);
    ptr = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
    if (!ptr)
        return (NULL);

    i = 0;
    j = 0;
    while (s1[j])
        ptr[i++] = s1[j++];
    j = 0;
    while (s2[j])
        ptr[i++] = s2[j++];
    ptr[i] = '\0';

    return (ptr);
}
