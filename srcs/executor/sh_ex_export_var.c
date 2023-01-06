/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_export_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:10:17 by jyao              #+#    #+#             */
/*   Updated: 2023/01/06 22:39:15 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** returns char ** that is newly allocated with new_arr_size,
** and it automatically adds 
** one space for the NULL string and then copies old arr
*/
t_var_s	*sh_ex_realloc_vars(t_var_s *old_vars, size_t new_vars_size)
{
	t_var_s		*new_vars;
	size_t		i;

	new_vars = (t_var_s *)ft_calloc(new_vars_size + 1, sizeof(t_var_s));
	if (new_vars == NULL)
		return (NULL);
	i = 0;
	while (i < new_vars_size && old_vars[i].key != NULL)
	{
		new_vars[i].key = old_vars[i].key;
		new_vars[i].val = old_vars[i].val;
		i++;
	}
	free(old_vars);
	return (new_vars);
}

t_var_s	*sh_ex_dup_vars(t_var_s *vars)
{
	t_var_s	*new_vars;
	size_t	i;

	if (vars == NULL)
		return (NULL);
	i = 0;
	while (vars[i].key != NULL)
		i++;
	new_vars = (t_var_s *)ft_calloc(i + 1, sizeof(t_var_s));
	if (new_vars == NULL)
		return (NULL);
	i = 0;
	while (vars[i].key != NULL)
	{
		new_vars[i].key = vars[i].key;
		new_vars[i].val = vars[i].val;
		i++;
	}
	return (new_vars);
}

int	sh_ex_is_valid_key(char *key)
{
	int		i;

	if (key == NULL)
		return (-1);
	i = 0;
	while (key[i] != '\0')
	{
		if (ft_strchr(\
		UNDERSCORE D_DIGITS A_LOWER A_UPPER, key[i]) == NULL)
			return (-1);
		i++;
	}
	return (0);
}
