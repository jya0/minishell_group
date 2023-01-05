/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/06 03:14:56 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_exit(t_shell_s *shell, int flag)
{
	rl_clear_history();
	sh_ex_free_all(shell);
	if (flag == 1)
		write (1, "exit\n", 5);
	exit(sh_ex_exitstatus);
}
