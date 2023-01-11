/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:02:34 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/11 16:24:48 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../../includes/minishell.h"

void	sh_ex_child_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "", 0);
	else if (sig == SIGQUIT)
		write(1, "", 0);
}

static void	newprompt_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_shell.exit_info.exit_code = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sh_ex_sighandle(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, newprompt_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 3)
		sh_ex_exit_all(&g_shell, 1);
}
