/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_many.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:42:52 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 08:21:34 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sh_ex_init_pipe_fork(t_shell_s *shell)
{
	int	i;

	i = 0;
	shell->pid = (int *)malloc(sizeof(int) * (shell->num_commands + 1));
	shell->fd = (int *)malloc(sizeof(int) * (shell->num_commands * 2));
	if (shell->pid == NULL || shell->fd == NULL)
		return (free(shell->pid), free(shell->fd), 1);
	while (i < shell->num_commands)
	{
		if (pipe(shell->fd + i * 2) < 0)
			return (1);
		i++;
	}
	return (0);
}

static int	sh_ex_dup_pipe(t_shell_s *shell, t_commands *command, int *index_fd)
{
	if (command->next)
	{
		if (dup2(shell->fd[*index_fd + 1], STDOUT_FILENO) < 0)
			return (1);
	}
	if (*index_fd != 0)
	{
		if (dup2(shell->fd[*index_fd - 2], STDIN_FILENO) < 0)
			return (1);
	}
	if (command->redirs != NULL)
	{
		if (sh_ex_check_redirect(shell, command->redirs) != 0)
		{
			shell->exit_info.exit_code = 1;
			return (1);
		}
	}
	return (0);
}

static int	sh_ex_run_single_cmd_exec(\
t_shell_s *shell, t_commands *command)
{
	if (sh_ex_isbuiltin(command))
		shell->exit_info.exit_code = sh_ex_builtin(shell, command);
	else
		shell->exit_info.exit_code = sh_ex_exec_command(shell, command);
	return (shell->exit_info.exit_code);
}
/*
** remove shell_exit_info.exit_code from the sh_ex_valid_exec
** if the previous command is error it wont run the next command.
** unless shell_exit_info.exit_code becomes 0
*/

static int	in_child_process(\
t_shell_s *shell, t_commands *command, int *index_fd)
{
	int	i;

	if (sh_ex_dup_pipe(shell, command, index_fd) == 0)
		shell->exit_info.exit_code = 0;
	i = 0;
	while (i < (shell->num_commands * 2))
		close(shell->fd[i++]);
	if (shell->exit_info.exit_code == 0)
	{
		if (sh_ex_valid_exec(shell, command) == 0)
			shell->exit_info.exit_code = \
			sh_ex_run_single_cmd_exec(shell, command);
	}
	else
	{
		if (errno == EACCES)
			ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	free_fd_pid(&shell);
	sh_ex_exit_all(shell, 0);
	return (shell->exit_info.exit_code);
}

int	sh_ex_init_fork(t_shell_s *shell)
{
	int			i;
	int			index_fd;
	t_commands	*cmd;

	cmd = shell->head_command;
	i = 0;
	index_fd = 0;
	shell->num_commands--;
	if (sh_ex_init_pipe_fork(shell))
		return (1);
	signal(SIGQUIT, sh_ex_child_handler);
	while (cmd)
	{
		shell->pid[i] = fork();
		if (shell->pid[i] == -1)
			return (1);
		else if (shell->pid[i] == 0)
			in_child_process(shell, cmd, &index_fd);
		cmd = cmd->next;
		index_fd += 2;
		sh_ex_stdstatus(0);
		i++;
	}
	return (sh_ex_close_fd(shell));
}
