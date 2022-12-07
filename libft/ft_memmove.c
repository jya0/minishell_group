/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:53:57 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 12:50:58 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, unsigned int n)
{
	char			*sc1;
	char			*sc2;
	unsigned int	i;

	sc1 = (char *)s1;
	sc2 = (char *)s2;
	if (sc1 == NULL && sc2 == NULL)
		return (NULL);
	if (sc1 > sc2)
	{
		while (n-- > 0)
			sc1[n] = sc2[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			sc1[i] = sc2[i];
			i++;
		}
	}
	return (s1);
}
