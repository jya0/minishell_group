/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:56:28 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/10 01:54:37 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sh_ex_fork(t_shell_s *shell, t_commands *command)
{
	int	fid;

	fid = fork();
	if (fid == -1)
		return (1);
	if (fid == 0)
		sh_ex_exec_cmd(shell, command);
	else
	{
		waitpid(fid, &(shell->exit_info.exit_code), 0);
		if (WIFEXITED(shell->exit_info.exit_code))
		{
			shell->exit_info.exit_code = \
			WEXITSTATUS(shell->exit_info.exit_code);
		}
	}
	return (shell->exit_info.exit_code);
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
		shell->exit_info.exit_code = sh_ex_builtin(shell, command);
	else if (sh_ex_valid_exec(shell, command) == 0)
	{
		printf("running\n");
		signal(SIGQUIT, sh_ex_killchild_handler);
		shell->exit_info.exit_code = sh_ex_fork(shell, command);
	}
	else
	{
		printf("didnt run\n");
		shell->exit_info.exit_code = 1;
	}
	return (shell->exit_info.exit_code);
}

int	sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command)
{
	if (sh_ex_isbuiltin(command))
		shell->exit_info.exit_code = sh_ex_builtin(shell, command);
	else
		shell->exit_info.exit_code = sh_ex_exec_cmd(shell, command);
	return (shell->exit_info.exit_code);
}

int	sh_ex_exec(t_shell_s *shell)
{
	signal(SIGINT, sh_ex_nl_sigint_handler);
	shell->num_commands = sh_ex_listlen(shell->head_command);
	sh_ex_stdstatus(1);
	if (shell->head_command == NULL && shell->head_command->redirs == NULL)
		return (1);
	if (shell->num_commands > 1)
		shell->exit_info.exit_code = sh_ex_init_fork(shell);
	else
	{
		shell->exit_info.exit_code = \
		sh_ex_simplecmd(shell, shell->head_command);
	}
	sh_ex_stdstatus(0);
	return (shell->exit_info.exit_code);
}
