/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:47:27 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 04:32:52 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_view_env(t_shell_s *shell)
{
	size_t	i;

	i = 0;
	while (i < shell->envp.env_size)
	{
		if (shell->envp.vars[i].val != NULL)
		{
			ft_putstr_fd(shell->envp.vars[i].key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(shell->envp.vars[i].val, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

int	sh_ex_listlen(t_commands *command)
{
	int	i;

	i = 0;
	while (command)
	{
		command = command->next;
		i++;
	}
	return (i);
}
