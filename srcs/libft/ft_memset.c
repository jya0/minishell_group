/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:49:37 by yonas             #+#    #+#             */
/*   Updated: 2021/10/10 23:47:19 by yonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned int		i;
	unsigned char		*sc;

	i = 0;
	sc = (unsigned char *)s;
	while (i < n)
	{
		sc[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
