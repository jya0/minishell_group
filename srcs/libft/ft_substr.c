/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:38:53 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 10:06:11 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;
	unsigned int	j;

	j = 0;
	i = 0;
	sub = (char *) malloc(sizeof(char) * (len + 1));
	if (sub == 0)
		return (NULL);
	while (s[j])
	{
		if (j >= start && i < len)
		{
			sub[i] = s[j];
			i++;
		}
		j++;
	}
	sub[i] = '\0';
	return (sub);
}
