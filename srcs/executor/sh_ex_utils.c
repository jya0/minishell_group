/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 08:23:28 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/23 08:33:46 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sh_ex_wcmessage(void)
{
	char *term;

	term = getenv("SHELL");
	printf(RED "The default interactive shell is now %s.\n", term);
	printf("To update your account to use %s\n", term);
	printf("please run 'chsh -s /bin/zsh'.\n");
	printf("For more details, please contact Yao and Yonas.\n" WHITE);
}

int sh_ex_doublelen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void sh_ex_freeall(char **str)
{
	int i;

	if (!str && !(*str))
		return;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void sh_ex_freeallin(char **str)
{
	int i;

	if (!str && !(*str))
		return;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
}

void sh_ex_freeallvar(t_shell_s *shell, t_commands *command)
{
	sh_ex_freeall(shell->envp.key);
	sh_ex_freeall(shell->envp.value);
	sh_ex_freeall(shell->path);
	// free(shell->echovar);
	// sh_ex_freeall(shell->tokens);
	// free(shell->home);
	// sh_ex_freeall(shell->commands);
	// free(shell->cwd);
	// free(shell->echo_print);
	// free(shell->cmd_line);
	sh_ps_parser_commands_free_list(command);
	// sh_ps_lexer_word_free_list(words);
}

void display_rd(t_redirections *redir_h)
{
	t_redirections *redir;
	redir = redir_h;
	while (redir)
	{
		printf("redir file = %s redir termtype = %d\n", redir->redir_file, redir->redir_term_type);
		redir = redir->next;
	}
}