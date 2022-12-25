/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:06:23 by jyao              #+#    #+#             */
/*   Updated: 2022/12/25 18:21:12 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmd_argv(char **cmd_argv)
{
	int	i;

	if (cmd_argv == NULL)
		return ;
	i = 0;
	while (cmd_argv[i] != NULL)
	{
		free(cmd_argv[i]);
		cmd_argv[i] = NULL;
		i++;
	}
	free(cmd_argv);
}

static void	free_redirs(t_redirections	*head_redir)
{
	t_redirections	*redir;

	while (head_redir != NULL)
	{
		redir = head_redir;
		head_redir = head_redir->next;
		if (redir->redir_file != NULL)
		{
			free(redir->redir_file);
			redir->redir_file = NULL;
		}
		free(redir);
	}
}

void	sh_ps_parser_commands_free(\
t_commands *command, enum e_free_option flag)
{
	if (command == NULL)
		return ;
	if (flag == FREE_ALL)
	{
		free_cmd_argv(command->cmd_argv);
		free_redirs(command->redirs_in);
		free_redirs(command->redirs_out);
	}
	free(command);
}

void	sh_ps_parser_commands_free_list(t_commands *head_command)
{
	t_commands	*command;

	printf("\nfreeing commands list\n");
	while (head_command != NULL)
	{
		command = head_command;
		head_command = head_command->next;
		sh_ps_parser_commands_free(command, FREE_ALL);
	}
}
