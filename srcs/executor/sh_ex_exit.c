/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/23 19:52:55 by jyao             ###   ########.fr       */
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
	ssize_t	result;

	i = 0;
	while (strchr(DELIM_SPACES, nbr[i]) != NULL)
		i++;
	i += (nbr[i] == '-' || nbr[i] == '+');
	sign = 1 - ((nbr[i - (1 * (i > 0))] == '-') * 2);
	result = 0;
	while (ft_isdigit(nbr[i]) == 1)
	{
		result = result * 10 + ((nbr[i] - '0') * sign);
		i++;
	}
	return ((int)result);
}

/*
** exit 9223372036854775808
** exit -9223372036854775809
*/
int	is_atoi_proper_format(char *arg)
{
	int		i;
	ssize_t	cmp;
	ssize_t	old;
	int		nve;

	if (arg == NULL || *arg == '\0')
		return (1);
	i = 0;
	while (strchr(DELIM_SPACES, arg[i]) != NULL)
		i++;
	i += (arg[i] == '-' || arg[i] == '+');
	nve = arg[i - (1 * (i > 0))] == '-';
	cmp = 0;
	while (ft_isdigit(arg[i]) == 1)
	{
		old = cmp;
		cmp = cmp * 10 + (arg[i] - '0') * (1 - nve * 2);
		if ((nve == 1 && cmp > old) || (nve != 1 && cmp < old))
			return (1);
		i++;
	}
	if (arg[i] != '\0')
		return (1);
	return (0);
}

void	free_fd_pid(t_shell_s **shell)
{
	if (shell == NULL || *shell == NULL)
		return ;
	if ((*shell)->fd != NULL && (*shell)->pid != NULL)
	{
		free((*shell)->fd);
		free((*shell)->pid);
		(*shell)->fd = NULL;
		(*shell)->pid = NULL;
	}
	sh_ex_stdstatus(0);
}

int	sh_ex_exit_all(t_shell_s *shell, int flag)
{
	free_fd_pid(&shell);
	sh_ex_free_all(shell);
	if (flag == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
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
		ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
		sh_ex_exit_all(shell, 0);
	}
	else if (len == 1)
	{
		shell->exit_info.exit_code = shell_atoi(command->cmd_args[0]);
		sh_ex_exit_all(shell, 0);
	}
	else if (len > 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		shell->exit_info.exit_code = 1;
	}
	return (shell->exit_info.exit_code);
}
