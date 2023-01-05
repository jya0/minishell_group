/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:47:27 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/05 22:54:14 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	sh_ex_view_env(t_shell_s *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->envp.env_size)
	{
		if (shell->envp.val_chain[i] != NULL)
		{
			printf(WHITE"%s=%s\n", \
			shell->envp.key_chain[i], shell->envp.val_chain[i]);
		}
		i++;
	}
	return (0);
} */

int	sh_ex_view_env(t_shell_s *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->envp.env_size)
	{
		if (shell->envp.vars[i].val != NULL)
		{
			printf(WHITE"%s=%s\n", \
			shell->envp.vars[i].key, shell->envp.vars[i].val);
		}
		i++;
	}
	return (0);
}
