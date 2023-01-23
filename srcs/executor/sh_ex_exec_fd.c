/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:47:50 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/20 01:45:30 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_stdstatus(int status)
{
	static int	fdin;
	static int	fdout;

	if (status)
	{
		fdin = dup(STDIN_FILENO);
		fdout = dup(STDOUT_FILENO);
	}
	else if (!status)
	{
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fdin);
		close(fdout);
	}
}
