/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 10:58:33 by yoyohann          #+#    #+#             */
/*   Updated: 2021/10/12 11:14:32 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_root;

	t_root = (t_list *) malloc(sizeof(t_list));
	if (t_root == NULL)
		return (NULL);
	t_root->content = content;
	t_root->next = NULL;
	return (t_root);
}
