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
	}
}

int	sh_ex_valid_exec(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
	if (file_name == NULL)
	{
		shell->exit_info.exit_code = EXT_CMD_NOT_FOUND_ERR;
		ft_putstr_fd(sh_get_error_msg(\
		shell->exit_info.exit_code), STDERR_FILENO);
		return (EXT_CMD_NOT_FOUND_ERR);
	}
	free(file_name);
	return (0);
}

int	sh_ex_exec_cmd(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
	if (file_name == NULL)
	{
		shell->exit_info.exit_code = EXT_CMD_NOT_FOUND_ERR;
		ft_putstr_fd(sh_get_error_msg(\
		shell->exit_info.exit_code), STDERR_FILENO);
		free(file_name);
		return (EXT_CMD_NOT_FOUND_ERR);
	}
	else
	{
		printf("hey\n");
		if (execve(file_name, command->cmd_argv, \
		(char **)shell->envp.envp_chain) == -1)
		{
			printf("DIDNT HANDLE THIS YET\n");
			free(file_name);
			exit(EXIT_FAILURE);
		}
	}
	free(file_name);
	return (shell->exit_info.exit_code);
}
