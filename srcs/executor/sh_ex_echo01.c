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

/* void	sh_ex_displayecho(t_shell_s *shell, t_commands *command, char *arg)
{
	if (ft_strncmp (shell->echo_print, "$?", 2) == 0)
		ft_putnbr_fd (sh_ex_exitstatus, shell->fdout);
	else
	{
		ft_putstr_fd (arg, shell->fdout);
		sh_ex_exitstatus = 0;
	}
} 

void	sh_ex_echoflag(t_shell_s *shell, t_commands *command)
{
	char	*tmp;
	char	*tmp1;

	shell->char_count = ft_strlen (shell->cmd_line);
	if (shell->char_count > 4)
	{
		tmp1 = ft_substr (shell->cmd_line, 4, shell->char_count - 4);
		tmp = sh_ps_trimspace (tmp1);
		free (tmp1);
		if (ft_strncmp (tmp, "-n", 2) == 0)
		{
			shell->echoflag = 1;
			shell->echo_print = ft_substr (tmp, 2, ft_strlen (tmp) - 2);
			return ;
		}
		else
			shell->echoflag = 0;
	}
	shell->echo_print = tmp;
}

void	sh_ex_echo(t_shell_s *shell, t_commands *command)
{
	sh_ex_echoflag (shell, command);
	if (shell->echo_print)
	{
		sh_ex_displayecho (shell, command, shell->echo_print);
		if (!shell->echoflag)
			ft_putstr_fd ("\n", shell->fdout);
	}
	else
		ft_putstr_fd ("\n", shell->fdout);
}
*/

void	sh_ex_echoarray(t_shell_s *shell, char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		ft_putstr_fd (commands[i], shell->fdout);
		ft_putchar_fd('\n', shell->fdout);
		i++;
	}
	printf("\n");
}

void	sh_ex_displayecho(t_shell_s *shell, t_commands *command)
{
	if (command->cmd_args)
	{
		if (ft_strncmp(command->cmd_args[0], "$?", 2) == 0)
			ft_putnbr_fd (sh_ex_exitstatus, shell->fdout);
		else
		{
			sh_ex_echoarray(shell, command->cmd_args);
			sh_ex_exitstatus = 0;
		}
	}
}

void	sh_ex_echoflag(t_shell_s *shell, t_commands *command)
{
	char	**args;

	args = command->cmd_args;
	if (command->cmd_name)
	{
		if (args && (ft_strncmp (args[0], "-n", 2) == 0))
		{
			shell->echoflag = 1;
			command->cmd_args = &args[1];
			return ;
		}
		else
			shell->echoflag = 0;
	}
}

void	sh_ex_echo(t_shell_s *shell, t_commands *command)
{
	sh_ex_echoflag (shell, command);
	if (command->cmd_args)
	{
		sh_ex_displayecho (shell, command);
		if (!shell->echoflag)
			ft_putstr_fd ("\n", shell->fdout);
	}
	else
		ft_putstr_fd ("\n", shell->fdout);
}
