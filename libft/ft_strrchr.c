/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:26:22 by yoyohann          #+#    #+#             */
/*   Updated: 2021/10/11 01:32:06 by yonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if ((char)c == '\0')
		return ((char *)(&str[i]));
	while (i-- > 0)
	{
		if (str[i] == (char)c)
			return ((char *)(&str[i]));
	}
	return (NULL);
}
