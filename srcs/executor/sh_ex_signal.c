/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:02:34 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/08 00:21:51 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../../includes/minishell.h"

static void	killchild_handler(int sig)
{
	if (sig == SIGQUIT && g_shell.exit_info.if_pid_fork != 0)
	{
		perror("quited");
		kill(g_shell.exit_info.if_pid_fork, SIGQUIT);
		g_shell.exit_info.if_pid_fork = 0;
	}
}

static void	newprompt_handler(int sig)
{
	set_mode();
	if (sig == SIGINT)
	{
		g_shell.exit_info.exit_code = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	exitshell(void)
{
	set_mode();
	sh_ex_exit(&g_shell, 1);
	// sh_ex_free_all(&g_shell);
	exit(0);
}

void	sh_ex_sighandle(int sig)
{
	set_mode();
	if (sig == 1)
	{
		signal(SIGINT, newprompt_handler);
		signal(SIGQUIT, killchild_handler);
	}
	if (sig == 3)
		exitshell();
}

