/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:44:15 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 08:25:03 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_get_exit_code(int status)
{
	int	val;

	val = 0;
	if (WIFSIGNALED(status) != 0)
	{
		val = WTERMSIG(status);
		if (val == SIGQUIT)
			ft_putstr_fd("CHILD QUITED!\n", STDERR_FILENO);
		return (128 + val);
	}
	else if (WIFEXITED(status) != 0)
	{
		return (WEXITSTATUS(status));
	}
	return (1);
}

int	sh_ex_close_fd(t_shell_s *shell)
{
	int	i;

	i = 0;
	while (i < (shell->num_commands * 2))
		close(shell->fd[i++]);
	i = 0;
	while (i < (shell->num_commands + 1))
	{
		waitpid(shell->pid[i], &(shell->exit_info.exit_code), 0);
		i++;
	}
	shell->exit_info.exit_code = \
	sh_ex_get_exit_code(shell->exit_info.exit_code);
	free_fd_pid(&shell);
	return (shell->exit_info.exit_code);
}
