/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_shellinit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 07:44:15 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/04 19:59:13 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(t_ter *ter)
{
	ter->shell_terminal = STDIN_FILENO;
	ter->shell_is_interactive = isatty (ter->shell_terminal);
	if (ter->shell_is_interactive)
	{
		ter->shell_pgid = getpgrp ();
		while (tcgetpgrp (ter->shell_terminal) != ter->shell_pgid)
		{
			ter->shell_pgid = getpgrp ();
			kill(-ter->shell_pgid, SIGTTIN);
		}
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);
		ter->shell_pgid = getpid ();
		if (setpgid (ter->shell_pgid, ter->shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in it's own process group.");
			exit(1);
		}
		tcsetpgrp (ter->shell_terminal, ter->shell_pgid);
		tcgetattr (ter->shell_terminal, &ter->shell_tmodes);
	}
}

void	save_mode(void)
{
	tcgetattr(STDIN_FILENO, &old_term);
}

void	set_mode(void)
{
	int	t_mode;

	tcgetattr (STDIN_FILENO, &old_term);
	atexit (reset_mode);
	t_mode = isatty (STDIN_FILENO);
	{
		if (t_mode == 1)
		{
			tcgetattr (STDIN_FILENO, &new_term);
			new_term.c_lflag &= ~(ICANON | ECHOCTL);
			tcsetattr (STDIN_FILENO, TCSANOW, &new_term);
		}
	}
}

void	reset_mode(void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &old_term);
}
