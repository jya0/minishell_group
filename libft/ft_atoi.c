/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:03:54 by yonas             #+#    #+#             */
/*   Updated: 2021/10/11 04:13:15 by yonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nbr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nbr[i] == ' ') || (nbr[i] == '\f') || (nbr[i] == '\n')
		|| (nbr[i] == '\r') || (nbr[i] == '\t') || (nbr[i] == '\v'))
		i++;
	if ((nbr[i] == '-') || (nbr[i] == '+'))
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nbr[i] >= 48) && (nbr[i] <= 57))
	{
		result = (result * 10) + ((int )nbr[i] - 48);
		i++;
	}
	return ((int)(result * sign));
}
