/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 09:56:20 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 10:04:31 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	while ((src[i] != '\0') && (i < (n - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	if (src[i] != '\0')
		i = ft_strlen(src);
	return (i);
}
