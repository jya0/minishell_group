/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:38:53 by yonas             #+#    #+#             */
/*   Updated: 2023/01/13 23:27:28 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
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
