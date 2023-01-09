/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/10 00:36:51 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int	sh_ex_exit(t_shell_s *shell, int flag)
{
	rl_clear_history();
	sh_ex_free_all(shell);
	if (flag == 1)
		write (1, "exit\n", 5);
	exit(shell->exit_info.exit_code);
} */

static int	exit_one_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	sh_ex_exit_all(t_shell_s *shell, int flag)
{
	rl_clear_history();
	sh_ex_free_all(shell);
	if (flag == 1)
	{
		write(1, "exit\n", 5);
		open(HEREDOC_FILE, O_TRUNC | O_CREAT, 0777);
		unlink(HEREDOC_FILE);
	}
	exit(shell->exit_info.exit_code);
}

int	sh_ex_exit(t_shell_s *shell, t_commands *command, int flag)
{
	int	len;

	len = sh_ex_doublelen(command->cmd_args);
	if (len == 0)
		sh_ex_exit_all(shell, flag);
	else if (exit_one_arg(command->cmd_args[0]) != 0)
	{
		shell->exit_info.exit_code = 255;
		ft_putstr_fd("NUMERIC ARGUMENT EXIT ERROR\n", STDERR_FILENO);
		sh_ex_exit_all(shell, 0);
	}
	else if (len == 1)
	{
		shell->exit_info.exit_code = ft_atoi(command->cmd_args[0]);
		sh_ex_exit_all(shell, 0);
	}
	else if (len > 1)
	{
		write(1, "exit\n", 5);
		ft_putstr_fd("TOO MANY ARGUMENT EXIT ERROR\n", STDERR_FILENO);
		shell->exit_info.exit_code = 1;
	}
	return (shell->exit_info.exit_code);
}
