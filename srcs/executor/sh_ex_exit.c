/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/08 08:43:42 by jyao             ###   ########.fr       */
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
		if (!isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	sh_ex_exit_all(t_shell_s *shell, int flag)
{
	rl_clear_history();
	sh_ex_free_all(shell);
	if (flag == 1)
	{
		write (1, "exit\n", 5);
		open(HEREDOC_FILE, O_TRUNC | O_CREAT, 0777);
		unlink(HEREDOC_FILE);
	}
	exit(shell->exit_info.exit_code);
}

int	sh_ex_exit(t_shell_s *shell, int flag)
{
	int	len;

	len = sh_ex_doublelen(shell->head_command->cmd_args);
	if (len == 0)
		sh_ex_exit_all(shell, 1);
	if (len >= 1)
	{
		if (len == 1 && exit_one_arg(shell->head_command->cmd_args[0]) != 0)
			sh_ex_exit_all(shell, flag);
		else if (len >= 1 && \
		exit_one_arg(shell->head_command->cmd_args[0]) == 0)
		{
			printf("exit : numeric argument required\n");
			sh_ex_exit_all(shell, 0);
		}
		else
		{
			printf("exit : too many arugument\n");
			shell->exit_info.exit_code = 1;
		}
	}
	return (shell->exit_info.exit_code);
}
