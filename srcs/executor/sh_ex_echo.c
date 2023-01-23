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

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_array(t_shell_s *shell, t_commands *command)
{
	int		i;
	int		len;
	char	**cmd;
	char	**echo;

	i = 0;
	cmd = command->cmd_args;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0 \
	&& (check_flag(&cmd[i][1])))
	{
		shell->echoflag = 1;
		i++;
	}
	echo = &cmd[i];
	i = 0;
	len = sh_ex_doublelen(echo);
	while (echo[i])
	{
		ft_putstr_fd(echo[i], 1);
		if (i < len - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	sh_ex_echo(t_shell_s *shell, t_commands *command)
{
	shell->echoflag = 0;
	if (*(command->cmd_args) != NULL)
	{
		echo_array(shell, command);
		if (!shell->echoflag)
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}

void	display_all(t_shell_s *shell)
{
	int	i;

	i = 0;
	while (shell->head_command)
	{
		printf("%s\n", shell->head_command->cmd_name);
		shell->head_command = shell->head_command->next;
	}
}
