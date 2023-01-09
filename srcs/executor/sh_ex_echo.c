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

void	sh_ex_echoarray(t_commands *command)
{
	int		i;
	int		len;
	char	**cmd;
	char	**echo;

	len = sh_ex_doublelen(command->cmd_args);
	cmd = command->cmd_args;
	if (ft_strcmp(cmd[0], "-n") == 0)
	{
		echo = &cmd[1];
		len--;
	}
	else
		echo = cmd;
	i = 0;
	while (echo[i])
	{
		ft_putstr_fd(echo[i], 1);
		if (i < len - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	sh_ex_echoflag(t_shell_s *shell, t_commands *command)
{
	char	**args;

	args = command->cmd_args;
	if (*args != NULL)
	{
		if (ft_strcmp(args[0], "-n") == 0)
			shell->echoflag = 1;
	}
}

void	sh_ex_displayecho(t_shell_s *shell, t_commands *command)
{
	if (ft_strcmp(command->cmd_args[0], "$?") == 0)
		ft_putnbr_fd((unsigned char)shell->exit_info.exit_code, shell->fdout);
	else
	{
		sh_ex_echoarray(command);
		shell->exit_info.exit_code = 0;
	}
}

int	sh_ex_echo(t_shell_s *shell, t_commands *command)
{
	shell->echoflag = 0;
	if (*(command->cmd_args) != NULL)
	{
		sh_ex_echoflag(shell, command);
		sh_ex_displayecho(shell, command);
		if (!shell->echoflag)
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}
