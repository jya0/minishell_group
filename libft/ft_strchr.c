/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:37:28 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/13 23:29:01 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)(&str[i]));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(&str[i]));
	return (NULL);
}
