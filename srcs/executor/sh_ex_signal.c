/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:02:34 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/06 00:56:54 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../../includes/minishell.h"

void	sh_ex_sighandle(int sig)
{
	set_mode ();
	if (sig == 1)
	{
		signal (SIGINT, sh_ex_newprompt);
		signal (SIGQUIT, SIG_IGN);
	}
	if (sig == 3)
	{
		sh_ex_exitshell (3);
	}
}

void	sh_ex_newprompt(int sig)
{
	set_mode ();
	sh_ex_exitstatus = 130;
	write (1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line ();
	rl_redisplay ();
	(void)sig;
}

void	sh_ex_exitshell(int sig)
{
	(void)sig;
	set_mode ();
	exit(0);
}
