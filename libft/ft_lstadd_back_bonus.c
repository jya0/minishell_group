/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:46:19 by yoyohann          #+#    #+#             */
/*   Updated: 2021/10/12 13:35:24 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list	**lst, t_list *new)
{
	t_list	*t_node;

	t_node = *lst;
	if (new == NULL)
		return ;
	if (lst && t_node)
	{
		if (t_node == NULL)
			t_node = new;
		else
		{
			while (t_node->next)
				t_node = t_node->next;
			t_node->next = new;
		}
	}
}
