/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:37:56 by yonas             #+#    #+#             */
/*   Updated: 2021/10/11 03:50:03 by yonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (tofind[i] == '\0' || tofind == NULL)
		return ((char *)(str));
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while ((str[i + j] == tofind[j]) && (i + j) < n)
		{
			if (tofind[j + 1] == '\0')
				return ((char *)(&str[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}
