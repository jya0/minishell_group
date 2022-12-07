/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:01:08 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 11:53:24 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned int		i;
	unsigned char		*dst;
	const unsigned char	*sc;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst = (unsigned char *)dest;
	sc = (unsigned char *)src;
	while (i < n)
	{
		dst[i] = sc[i];
		i++;
	}
	return (dest);
}
