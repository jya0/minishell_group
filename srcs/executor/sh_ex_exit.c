/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 02:51:59 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/04 20:53:02 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ex_exit(t_shell_s *shell, t_commands *command, int flag)
{
	printf("called exit!\n");
	rl_clear_history();
	sh_ex_free_all(shell, command);
	if (flag == 1)
		write (1, "exit\n", 5);
	exit(sh_ex_exitstatus);
}
