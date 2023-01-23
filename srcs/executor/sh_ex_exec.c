/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:37:34 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 07:40:30 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_begin_exec(t_shell_s *shell)
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
		sh_ex_run_simple_cmd(shell, shell->head_command);
	}
	sh_ex_stdstatus(0);
	return (shell->exit_info.exit_code);
}

/*
** check the command with both builtin and non builtin commands 
*/

int	sh_ex_valid_exec(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	file_name = NULL;
	if (command->cmd_name == NULL)
		return (0);
	if (sh_ex_isbuiltin(command))
		file_name = ft_strdup(command->cmd_argv[0]);
	else if (command->cmd_name != NULL && *(command->cmd_name) != '\0')
			file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
	if (file_name == NULL)
	{
		if (errno == ENOENT)
			shell->exit_info.exit_code = 127;
		else if (errno == EACCES)
			shell->exit_info.exit_code = 126;
		return (shell->exit_info.exit_code);
	}
	free(file_name);
	return (0);
}

int	sh_ex_exec_command(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	if (command->cmd_name == NULL)
		return (0);
	file_name = sh_ex_bindir(shell, command->cmd_name);
	if (execve(file_name, command->cmd_argv, \
	(char **)shell->envp.envp_chain) == -1)
	{
		shell->exit_info.exit_code = 126;
		free(file_name);
		sh_ex_exit_all(shell, 0);
	}
	free(file_name);
	return (shell->exit_info.exit_code);
}
