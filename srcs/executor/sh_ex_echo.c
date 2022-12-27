/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:45:04 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 06:33:03 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

 void sh_ex_echoarray(t_shell_s *shell, t_commands *command)
{
	int i;

	char **cmd;
	cmd = command->cmd_args;

	i = 0;
	// if (!cmd)
	// 	ft_putchar_fd('\n', shell->fdout);
	while (cmd[i])
	{
		if (ft_strcmp(cmd[0], "-n") == 0)
			continue;
		ft_putstr_fd(cmd[i], shell->fdout);
		i++;
	}
}

void sh_ex_displayecho(t_shell_s *shell, t_commands *command)
{
	if (command->cmd_args[0] != NULL)
	{
		if (ft_strncmp(command->cmd_args[0], "$?", 2) == 0)
			ft_putnbr_fd(sh_ex_exitstatus, shell->fdout);
		else if (shell->echoflag)
		{
			sh_ex_echoarray(shell, command);
			sh_ex_exitstatus = 0;
		}
	}
}

void sh_ex_echoflag(t_shell_s *shell, t_commands *command)
{

	if (command->cmd_args[0] != NULL)
	{
		if (ft_strncmp(command->cmd_args[0], "-n", 2) == 0)
		{
			shell->echoflag = 1;
			return;
		}
		else
			shell->echoflag = 0;
	}
}

void sh_ex_echo(t_shell_s *shell, t_commands *command)
{
 	sh_ex_echoflag(shell, command);
	if (command->cmd_args[0] == NULL)
		ft_putstr_fd("\n", shell->fdout);
	else
	{	
		sh_ex_displayecho(shell, command);
		if (!shell->echoflag)
			ft_putstr_fd("\n", shell->fdout);
			}
} 
