/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:23:36 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/24 01:02:52 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sh_ex_createprompt(void)
{
	char	*prompt;
	char	*color;
	char	*cwd;

	cwd = sh_ex_cwd();
	if (cwd == NULL)
		cwd = ft_strdup("BASH");
	color = ft_strdup(GREEN);
	prompt = ft_strjoin(color, cwd);
	free(cwd);
	free(color);
	color = ft_strdup(WHITE);
	cwd = ft_strjoin(prompt, color);
	free(color);
	free(prompt);
	prompt = ft_strjoin(cwd, ">> ");
	free(cwd);
	return (prompt);
}

void	sh_ex_readline(t_shell_s *shell)
{
	char	*prompt_line;

	prompt_line = sh_ex_createprompt();
	sh_ex_sighandle(1);
	shell->cmd_line = NULL;
	shell->cmd_line = readline(prompt_line);
	free(prompt_line);
	if (shell->cmd_line == NULL)
		sh_ex_sighandle(3);
}

void	sh_ex_initshell(t_shell_s *shell, char **envp)
{
	char	*oldpwd[2];

	sh_ex_envp_init(shell, envp);
	oldpwd[0] = "OLDPWD";
	oldpwd[1] = NULL;
	sh_ex_export(shell, oldpwd);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_shell = (t_shell_s){0};
	sh_ex_initshell(&g_shell, envp);
	while (1)
	{
		g_shell.head_command = NULL;
		sh_ex_readline(&g_shell);
		if (g_shell.cmd_line != NULL && *(g_shell.cmd_line) != '\0')
		{
			add_history(g_shell.cmd_line);
			g_shell.head_command = sh_ps_parser(&g_shell, g_shell.cmd_line);
			if (g_shell.head_command != NULL)
				sh_ex_begin_exec(&g_shell);
		}
		sh_ex_free_loop(&g_shell);
		unlink(HEREDOC_FILE);
	}
	return (0);
}
