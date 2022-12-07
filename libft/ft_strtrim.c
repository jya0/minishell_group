/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:02:55 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 10:05:34 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chrmatch(char const s1, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s2[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s;
	int		e;
	char	*trim;

	s = 0;
	while (s1[s] && ft_chrmatch(s1[s], set))
		s++;
	e = ft_strlen(s1);
	while (e > s && ft_chrmatch(s1[e - 1], set))
		e--;
	trim = (char *) malloc(sizeof(char) * ((e - s) + 1));
	if (trim == 0)
		return (NULL);
	i = 0;
	while (s < e)
		trim[i++] = s1[s++];
	trim[i] = '\0';
	return (trim);
}
