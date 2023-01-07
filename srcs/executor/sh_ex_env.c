/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:47:27 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 21:18:17 by yoyohann         ###   ########.fr       */
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
			printf(WHITE"%s=%s\n", \
			shell->envp.vars[i].key, shell->envp.vars[i].val);
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
