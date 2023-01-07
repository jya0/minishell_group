/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:27:00 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/06 21:46:54 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_exec_cmd(t_shell_s *shell, t_commands *command)
{
	char	*file_name;

	file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
	if (file_name == NULL)
	{
		printf("commnad not found: %s\n", command->cmd_argv[0]);
		free(file_name);
		return (127);
	}
	else
	{
		if (execve(file_name, command->cmd_argv, \
			(char **)shell->envp.envp_chain) == -1)
		{
			g_sh_ex_exitstatus = 127;
			free(file_name);
			exit(EXIT_FAILURE);
		}
	}
	free(file_name);
	return (0);
}

static int	exec_cmd(t_shell_s *shell, t_commands *command)
{
	int	fid;

	fid = fork();
	if (fid == -1)
		return (1);
	if (fid == 0)
		sh_ex_exec_cmd(shell, command);
	else
	{
		waitpid(fid, &g_sh_ex_exitstatus, 0);
		if (WIFEXITED(g_sh_ex_exitstatus))
			g_sh_ex_exitstatus = WEXITSTATUS(g_sh_ex_exitstatus);
	}
	return (g_sh_ex_exitstatus);
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
		g_sh_ex_exitstatus = sh_ex_builtin(shell, command);
	else if (!sh_ex_valid_exec(shell, command))
		g_sh_ex_exitstatus = exec_cmd(shell, command);
	else
		g_sh_ex_exitstatus = 1;
	return (g_sh_ex_exitstatus);
}

int	sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command)
{
	if (sh_ex_isbuiltin(command))
	{
		g_sh_ex_exitstatus = sh_ex_builtin(shell, command);
		free(shell->fd);
		free(shell->pid);
		sh_ex_exit(shell, 0);
	}
	else
		g_sh_ex_exitstatus = sh_ex_exec_cmd(shell, command);
	return (g_sh_ex_exitstatus);
}

int	sh_ex_exec(t_shell_s *shell)
{
	sh_ex_stdstatus(1);
	shell->num_commands = sh_ex_listlen(shell->head_command);
	if (shell->head_command == NULL && shell->head_command->redirs == NULL)
		return (1);
	if (shell->num_commands > 1)
		g_sh_ex_exitstatus = sh_ex_init_fork(shell);
	else
		sh_ex_simplecmd(shell, shell->head_command);
	sh_ex_stdstatus(0);
	return (g_sh_ex_exitstatus);
}
