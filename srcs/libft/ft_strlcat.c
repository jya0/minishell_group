/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:05:39 by yonas             #+#    #+#             */
/*   Updated: 2021/10/13 03:32:54 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	value;

	i = 0;
	j = 0;
	if (!src && !dest)
		return (0);
	if (n == 0)
		return (ft_strlen(src));
	if (n < (unsigned int)ft_strlen(dest))
		value = ft_strlen(src) + n;
	else
		value = ft_strlen(src) + ft_strlen(dest);
	while (dest[i])
		i++;
	while (src[j] && i + 1 < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (value);
}
