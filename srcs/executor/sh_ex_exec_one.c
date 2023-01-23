/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:40:17 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/20 07:08:04 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sh_ex_fork(t_shell_s *shell, t_commands *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		sh_ex_exec_command(shell, command);
	else
	{
		wait(&(shell->exit_info.exit_code));
		shell->exit_info.exit_code = \
		sh_ex_get_exit_code(shell->exit_info.exit_code);
	}
	return (shell->exit_info.exit_code);
}
/*
** check first if the command is valid or not
** if valid check if it is builtin if true execute it
** if not fork and execute it in the child process.
*/

int	sh_ex_run_simple_cmd(t_shell_s *shell, t_commands *command)
{
	if (command->redirs != NULL)
	{
		if (sh_ex_check_redirect(shell, command->redirs))
		{
			if (errno == EACCES)
				ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
			else
				ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
			return (1);
		}
	}
	if (command->cmd_argv == NULL)
		return (0);
	if (sh_ex_valid_exec(shell, command) == 0)
	{
		if (sh_ex_isbuiltin(command))
			shell->exit_info.exit_code = sh_ex_builtin(shell, command);
		else
		{
			signal(SIGQUIT, sh_ex_child_handler);
			shell->exit_info.exit_code = sh_ex_fork(shell, command);
		}
	}
	return (shell->exit_info.exit_code);
}
