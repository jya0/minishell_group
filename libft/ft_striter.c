/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:11:00 by yoyohann          #+#    #+#             */
/*   Updated: 2021/10/10 12:11:47 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	int				len;

	len = ft_strlen(s);
	i = 0;
	while (s[i])
	{
		f(i, s);
		i++;
	}
}
