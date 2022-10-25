/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:51:30 by yoyohann          #+#    #+#             */
/*   Updated: 2021/10/13 04:34:29 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*entry;

	entry = *lst;
	while (entry)
	{
		tmp = entry->next;
		if (del)
		{
			del(entry->content);
		}
		free(entry);
		entry = tmp;
	}
	*lst = NULL;
}
