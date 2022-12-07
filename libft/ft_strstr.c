/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:32:27 by yonas             #+#    #+#             */
/*   Updated: 2021/10/09 14:07:31 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, const char *to_find)
{
	int	i;
	int	n;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		n = 0;
		while ((str[i + n] == to_find[n] && str[i + n] != '\0'))
		{
			if (to_find[n + 1] == '\0')
				return (&str[i]);
			n++;
		}
		i++;
	}
	return (0);
}
