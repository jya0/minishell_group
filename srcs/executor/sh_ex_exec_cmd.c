/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:56:28 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 21:22:51 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_fork(t_shell_s *shell, t_commands *command)
{
	int	fid;

	fid = fork();
	if (fid == -1)
		return (1);
	if (fid == 0)
		sh_ex_exec_cmd(shell, command);
	else
	{
		waitpid(fid, &sh_ex_exitstatus, 0);
		if (WIFEXITED(sh_ex_exitstatus))
			sh_ex_exitstatus = WEXITSTATUS(sh_ex_exitstatus);
	}
	return (sh_ex_exitstatus);
}

int	sh_ex_simplecmd(t_shell_s *shell, t_commands *command)
{
	if (command->redirs != NULL)
	{
		if (sh_ex_check_redirect(shell, command->redirs))
			return (1);
	}
	if (command->cmd_argv == NULL)
		return (0);
	if (sh_ex_isbuiltin(command))
		sh_ex_exitstatus = sh_ex_builtin(shell, command);
	else if (!sh_ex_valid_exec(shell, command))
		sh_ex_exitstatus = sh_ex_fork(shell, command);
	else
		sh_ex_exitstatus = 1;
	return (sh_ex_exitstatus);
}

int	sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command)
{
	if (sh_ex_isbuiltin(command))
		sh_ex_exitstatus = sh_ex_builtin(shell, command);
	else
		sh_ex_exitstatus = sh_ex_exec_cmd(shell, command);
	return (sh_ex_exitstatus);
}

int	sh_ex_exec(t_shell_s *shell)
{
	shell->num_commands = sh_ex_listlen(shell->head_command);
	sh_ex_stdstatus(1);
	if (shell->head_command == NULL && shell->head_command->redirs == NULL)
		return (1);
	if (shell->num_commands > 1)
	sh_ex_exitstatus = sh_ex_init_fork(shell);
	else
		sh_ex_simplecmd(shell, shell->head_command);
	sh_ex_stdstatus(0);
	return (sh_ex_exitstatus);
}
