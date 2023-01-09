/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:44:37 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/10 00:21:50 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_isbuiltin(t_commands *command)
{
	if (ft_strcmp(command->cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(command->cmd_name, "cd") == 0)
		return (2);
	if (ft_strcmp(command->cmd_name, "pwd") == 0)
		return (3);
	if (ft_strcmp(command->cmd_name, "export") == 0)
		return (4);
	if (ft_strcmp(command->cmd_name, "unset") == 0)
		return (5);
	if (ft_strcmp(command->cmd_name, "env") == 0)
		return (6);
	if (ft_strcmp(command->cmd_name, "exit") == 0)
		return (7);
	return (0);
}

int	sh_ex_builtin(t_shell_s *shell, t_commands *command)
{
	if (sh_ex_isbuiltin(command) == 1)
		return (sh_ex_echo(shell, command));
	else if (sh_ex_isbuiltin(command) == 2)
		return (sh_ex_cd(shell, command));
	else if (sh_ex_isbuiltin(command) == 3)
		return (sh_ex_showpwd());
	else if (sh_ex_isbuiltin(command) == 4)
		return (sh_ex_export(shell, command->cmd_args));
	else if (sh_ex_isbuiltin(command) == 5)
		return (sh_ex_unset(shell, command->cmd_args));
	else if (sh_ex_isbuiltin(command) == 6)
		return (sh_ex_view_env(shell));
	else if (sh_ex_isbuiltin(command) == 7)
		return (sh_ex_exit(shell, command, 1));
	return (0);
}
