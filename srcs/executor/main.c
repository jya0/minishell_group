/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:23:36 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/06 03:14:19 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sh_ex_readline(t_shell_s *shell)
{
	char *prompt_line;

	prompt_line = sh_ex_createprompt(shell);
	sh_ex_sighandle(1);
	shell->cmd_line = NULL;
	// if (shell->cmd_line)
	// {
	// 	free(shell->cmd_line);
	// 	shell->cmd_line = (char *)NULL;
	// }
	shell->cmd_line = readline(prompt_line);
	free(prompt_line);
	if (shell->cmd_line == NULL)
		sh_ex_sighandle(3);
}

char *sh_ex_createprompt(t_shell_s *shell)
{
	char *prompt;
	char *color;

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


/* static void	sh_ps_parser_commands_print_list(t_commands	*head_command)
{
	int				i;
	t_redirections	*redir;

	if (head_command == NULL)
	{
		printf("\n------empty command list!-------\n");		
		return ;
	}
	printf("\n------printing commands!-------\n");
	while (head_command != NULL)
	{
		printf("\n-------\n");
		printf("\ncommand_name = %s", head_command->cmd_name);
		printf("\ncommand_args = ");
		if (head_command->cmd_args != NULL)
		{
			i = 0;
			while (head_command->cmd_args[i] != NULL)
				printf("<%s>", head_command->cmd_args[i++]);
		}
		printf("\nredirs = ");
		// redir = head_command->redirs_in;
		redir = head_command->redirs;
		while (redir != NULL)
		{
			printf("<%s %d> ", redir->redir_file, redir->redir_term_type);
			redir = redir->next;
		}
		head_command = head_command->next;
	}
} */


int main(int argc, char **argv, char **envp)
{
	t_shell_s	shell;
	t_commands	*head_command;

	(void)argc;
	(void)argv;
	sh_ex_exitstatus = 0;
	// sh_ex_wcmessage();
	// init_shell (void);
	shell = (t_shell_s){0};
	sh_ex_initshell(&shell, envp);
	while (1)
	{
		head_command = NULL;
		sh_ex_readline(&shell);
		if (shell.cmd_line != NULL && *(shell.cmd_line) != '\0')
		{
			add_history(shell.cmd_line);
			head_command = sh_ps_parser(&shell, shell.cmd_line);
			// sh_ps_parser_commands_print_list(head_command);
			if (head_command != NULL)
				sh_ex_exec(&shell, head_command);
		}
		sh_ex_free_loop(&shell);
		// sh_ps_parser_commands_free_list(command);
	}
	printf("HEY I AM STILL ALIVE\n");
	// sh_ex_free_all(&shell, head_command);
	return (0);
}
