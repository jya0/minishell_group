/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:51:59 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 09:58:01 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	char			*sc;
	unsigned int	i;
	char			ch;

	ch = (char )c;
	i = 0;
	sc = (char *)s;
	while (i < n)
	{
		if (sc[i] == ch)
			return ((void *)&sc[i]);
		else
			i++;
	}
	return (NULL);
}
