/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:23:36 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/07 21:21:05 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ex_readline(t_shell_s *shell)
{
	char	*prompt_line;

	prompt_line = sh_ex_createprompt(shell);
	sh_ex_sighandle(1);
	shell->cmd_line = NULL;
	shell->cmd_line = readline(prompt_line);
	free(prompt_line);
	if (shell->cmd_line == NULL)
		sh_ex_sighandle(3);
}

char	*sh_ex_createprompt(t_shell_s *shell)
{
	char	*prompt;
	char	*color;

	shell->cwd = sh_ex_cwd();
	color = ft_strdup(GREEN);
	prompt = ft_strjoin(color, shell->cwd);
	free(shell->cwd);
	free(color);
	color = ft_strdup(WHITE);
	shell->cwd = ft_strjoin(prompt, color);
	free(color);
	free(prompt);
	prompt = ft_strjoin(shell->cwd, " >> ");
	free(shell->cwd);
	return (prompt);
}

void	sh_ex_initshell(t_shell_s *shell, char **envp)
{
	int		i;
	char	*all_path;
	char	**path;
	char	*home;

	sh_ex_envp_init(shell, envp);
	home = sh_ex_searchenvvar(shell, "HOME");
	shell->home = ft_strdup(home);
	all_path = sh_ex_searchenvvar(shell, "PATH");
	path = ft_split(all_path, ':');
	shell->path = malloc(sizeof(char *) * (shell->envp.env_size + 1));
	if (!shell->path)
		return ;
	i = 0;
	while (path[i])
	{
		shell->path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	shell->path[i] = NULL;
	sh_ex_free_arr(path);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_s	shell;

	(void)argc;
	(void)argv;
	sh_ex_exitstatus = 0;
	shell = (t_shell_s){0};
	sh_ex_initshell(&shell, envp);
	while (1)
	{
		shell.head_command = NULL;
		sh_ex_readline(&shell);
		if (shell.cmd_line != NULL && *(shell.cmd_line) != '\0')
		{
			add_history(shell.cmd_line);
			shell.head_command = sh_ps_parser(&shell, shell.cmd_line);
			if (shell.head_command != NULL)
				sh_ex_exec(&shell);
		}
		sh_ex_free_loop(&shell);
	}
	return (0);
}
