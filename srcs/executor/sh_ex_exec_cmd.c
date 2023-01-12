/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 20:56:28 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/12 17:56:00 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_get_exit_code(int status)
{
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("CHILD QUITED!\n", STDERR_FILENO);
			return (131);
		}
	}
	else if (WIFEXITED(status) != 0)
	{
		return (WEXITSTATUS(status));
	}
	return (1);
}

static int	sh_ex_fork(t_shell_s *shell, t_commands *command)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		sh_ex_exec_cmd(shell, command);
	else
	{
		wait(&(shell->exit_info.exit_code));
		shell->exit_info.exit_code = \
		sh_ex_get_exit_code(shell->exit_info.exit_code);
	}
	return (shell->exit_info.exit_code);
}

int	sh_ex_simplecmd(t_shell_s *shell, t_commands *command)
{
	if (command->redirs != NULL)
	{
		if (sh_ex_check_redirect(shell, command->redirs))
			return (ft_putstr_fd("NO SUCH FILE ERROR!\n", STDERR_FILENO), 1);
	}
	if (command->cmd_argv == NULL)
		return (0);
	if (sh_ex_isbuiltin(command))
		shell->exit_info.exit_code = sh_ex_builtin(shell, command);
	else if (sh_ex_valid_exec(shell, command) == 0)
	{
		signal(SIGQUIT, sh_ex_child_handler);
		shell->exit_info.exit_code = sh_ex_fork(shell, command);
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
	signal(SIGINT, sh_ex_child_handler);
	shell->num_commands = sh_ex_listlen(shell->head_command);
	sh_ex_stdstatus(1);
	shell->fd = NULL;
	shell->pid = NULL;
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
