/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:14:57 by yonas             #+#    #+#             */
/*   Updated: 2021/10/12 09:58:53 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *s1, const void *s2, unsigned int n)
{
	const unsigned char		*sc1;
	const unsigned char		*sc2;
	unsigned int			i;

	i = 0;
	sc1 = (const unsigned char *)s1;
	sc2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (sc1[i] != sc2[i])
			return (sc1[i] - sc2[i]);
		i++;
	}
	return (0);
}
