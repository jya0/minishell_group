/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:18:27 by jyao              #+#    #+#             */
/*   Updated: 2023/01/09 22:11:25 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_commands	*get_next_command(t_words **head_word)
{
	t_commands	*command;

	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	command = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (command == NULL)
		return (NULL);
	if (sh_ps_parser_get_redirs(command, head_word) != 0 \
	|| sh_ps_parser_get_cmd_argv(command, head_word) != 0)
		return (NULL);
	sh_ps_lexer_word_del_word(head_word, *head_word, FREE_ALL);
	return (command);
}

t_commands	*sh_ps_parser_commands(t_words	*head_word)
{
	t_commands	*head_command;
	t_commands	*command;

	if (head_word == NULL)
		return (NULL);
	command = get_next_command(&head_word);
	head_command = command;
	while (command != NULL)
	{
		command->next = get_next_command(&head_word);
		command = command->next;
	}
	return (head_command);
}
