/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:33:55 by yonas             #+#    #+#             */
/*   Updated: 2022/12/21 02:02:15 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		l_s1;
	int		l_s2;
	char	*join;

	if (s1 == NULL)
	{
		l_s1 = 0;
		l_s2 = ft_strlen(s2);
		join = (char *) malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	
		if (join == 0)
			return (NULL);
		i = -1;
		while (s2[++i])
			join[i] = s2[i];
		join[i] = '\0';
		return (join);
	}
	if (s1 && s2)
	{
		i = 0;
		l_s1 = ft_strlen(s1);
		l_s2 = ft_strlen(s2);
		join = (char *) malloc(sizeof(char) * (l_s1 + l_s2 + 1));
		if (join == 0)
			return (NULL);
		i = -1;
		while (s1[++i])
			join[i] = s1[i];
		i = -1;
		while (s2[++i])
			join[l_s1++] = s2[i];
		join[l_s1] = '\0';
		return (join);
	}
	return (NULL);
}
