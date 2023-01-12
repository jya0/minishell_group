/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/11 23:23:35 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static int	exit_one_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (isdigit(arg[i]) == 0 && arg[i] != '-')
			return (1);
		i++;
	}
	return (0);
} */

int	shell_atoi(const char *nbr)
{
	int		i;
	int		sign;
	size_t	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nbr[i] == ' ') || (nbr[i] == '\f') || (nbr[i] == '\n')
		|| (nbr[i] == '\r') || (nbr[i] == '\t') || (nbr[i] == '\v'))
		i++;
	if ((nbr[i] == '-') || (nbr[i] == '+'))
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nbr[i] >= 48) && (nbr[i] <= 57))
	{
		result = (result * 10) + ((int )nbr[i] - 48);
		i++;
	}
	return ((int)(result * sign));
}

int	is_atoi_proper_format(char *arg)
{
	int		i;
	size_t	cmp;

	if (arg == NULL || *arg == '\0')
	i = 0;
		return (1);
	while ((arg[i] == ' ') || (arg[i] == '\f') || (arg[i] == '\n')
		|| (arg[i] == '\r') || (arg[i] == '\t') || (arg[i] == '\v'))
		i++;
	if ((arg[i] == '-') || (arg[i] == '+'))
		i++;
	while ((arg[i] >= 48) && (arg[i] <= 57))
		i++;
	if (arg[i] != '\0')
		return (1);
	return (0);
}

int	sh_ex_exit_all(t_shell_s *shell, int flag)
{
	free_fd_pid(&shell);
	sh_ex_free_all(shell);
	if (flag == 1)
		write(1, "exit\n", 5);
	open(HEREDOC_FILE, O_TRUNC | O_CREAT, 0777);
	unlink(HEREDOC_FILE);
	exit(shell->exit_info.exit_code);
}

int	sh_ex_exit(t_shell_s *shell, t_commands *command, int flag)
{
	int	len;

	len = sh_ex_doublelen(command->cmd_args);
	if (len == 0)
		sh_ex_exit_all(shell, flag);
	else if (is_atoi_proper_format(command->cmd_args[0]) != 0)
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
