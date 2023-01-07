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
		printf("commnad not found: %s\n", command->cmd_argv[0]);
		return (127);
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
		perror("commnad not found\n");
		free(file_name);
		return (127);
	}
	else
	{
		if (execve(file_name, command->cmd_argv, \
		(char **)shell->envp.envp_chain) == -1)
		{
			shell->exit_info.exit_code = 127;
			free(file_name);
			exit(EXIT_FAILURE);
		}
	}
	free(file_name);
	return (0);
}
