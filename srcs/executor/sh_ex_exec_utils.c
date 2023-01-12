/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:05:00 by marvin            #+#    #+#             */
/*   Updated: 2022/12/26 18:05:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_init_pipe_fork(t_shell_s *shell)
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

// initialize the fork
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
			sh_ex_dup_pipe(shell, cmd, &index_fd);
		cmd = cmd->next;
		index_fd += 2;
		sh_ex_stdstatus(0);
		i++;
	}
	return (sh_ex_close_fd(shell));
}
// use dup to duplicate the read and write end of the pipe

void	free_fd_pid(t_shell_s **shell)
{
	if (shell == NULL || *shell == NULL)
		return ;
	if ((*shell)->fd != NULL && (*shell)->pid != NULL)
	{
		free((*shell)->fd);
		free((*shell)->pid);
		(*shell)->fd = NULL;
		(*shell)->pid = NULL;
	}
}

int	sh_ex_dup_pipe(t_shell_s *shell, t_commands *command, int *index_fd)
{
	int	i;

	i = 0;
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
		if (sh_ex_check_redirect(shell, command->redirs))
			return (ft_putstr_fd("NO SUCH FILE ERROR!\n", STDERR_FILENO), 1);
	}
	while (i < (shell->num_commands * 2))
		close(shell->fd[i++]);
	if (sh_ex_valid_exec(shell, command) == 0)
		shell->exit_info.exit_code = sh_ex_simplecmd_exec(shell, command);
	free_fd_pid(&shell);
	sh_ex_exit_all(shell, 0);
	return (shell->exit_info.exit_code);
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
