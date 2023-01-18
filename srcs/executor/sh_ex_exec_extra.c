/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:02:20 by marvin            #+#    #+#             */
/*   Updated: 2022/12/27 09:02:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// duplicate stdin and stdout so to restore them after using

void	sh_ex_stdstatus(int status)
{
	static int	fdin;
	static int	fdout;

	if (status)
	{
		fdin = dup(STDIN_FILENO);
		fdout = dup(STDOUT_FILENO);
	}
	else if (!status)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		// close(fdin);
		// close(fdout);
	}
}

int	sh_ex_valid_exec(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	file_name = NULL;
	if (command->cmd_name == NULL)
		return (0);
	if (command->cmd_name != NULL && *(command->cmd_name) != '\0')
		file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
	if (file_name == NULL)
	{
		shell->exit_info.exit_code = 1;
		if (errno == ENOTDIR)
			shell->exit_info.exit_code = EXT_NOT_DIRECTORY;
		else if (errno == ENOENT || *(command->cmd_name) == '\0')
			shell->exit_info.exit_code = EXT_CMD_NOT_FOUND_ERR;
		ft_putstr_fd(sh_get_error_msg(\
		shell->exit_info.exit_code), STDERR_FILENO);
		return (shell->exit_info.exit_code);
	}
	free(file_name);
	return (0);
}

int	sh_ex_exec_cmd(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	if (command->cmd_name == NULL)
		return (0);
	file_name = sh_ex_bindir(shell, command->cmd_name);
	if (execve(file_name, command->cmd_argv, \
	(char **)shell->envp.envp_chain) == -1)
	{
		shell->exit_info.exit_code = 126;
		ft_putstr_fd("CAN'T EXECUTE ERROR!\n", STDERR_FILENO);
		free(file_name);
		exit(shell->exit_info.exit_code);
	}
	free(file_name);
	return (shell->exit_info.exit_code);
}
