/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_shellinit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 07:44:15 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 23:36:50 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(t_terminal *term)
{
	term->shell_terminal = STDIN_FILENO;
	term->shell_is_interactive = isatty (term->shell_terminal);
	if (term->shell_is_interactive)
	{
		term->shell_pgid = getpgrp ();
		while (tcgetpgrp (term->shell_terminal) != term->shell_pgid)
		{
			term->shell_pgid = getpgrp ();
			kill(-term->shell_pgid, SIGTTIN);
		}
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);
		term->shell_pgid = getpid ();
		if (setpgid (term->shell_pgid, term->shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in it's own process group.");
			exit(1);
		}
		tcsetpgrp (term->shell_terminal, term->shell_pgid);
		tcgetattr (term->shell_terminal, &term->shell_tmodes);
	}
}

void	save_mode(void)
{
	tcgetattr(STDIN_FILENO, &g_shell.mini_terminal.old_term);
}

void	set_mode(void)
{
	int		t_mode;

	tcgetattr (STDIN_FILENO, &g_shell.mini_terminal.new_term);
	atexit (reset_mode);
	t_mode = isatty (STDIN_FILENO);
	{
		if (t_mode == 1)
		{
			tcgetattr (STDIN_FILENO, &g_shell.mini_terminal.new_term);
			g_shell.mini_terminal.shell_tmodes.c_lflag &= ~(ICANON | ECHOCTL);
			tcsetattr (STDIN_FILENO, TCSANOW, &g_shell.mini_terminal.new_term);
		}
	}
}

void	reset_mode(void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &g_shell.mini_terminal.old_term);
}
