/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:10:46 by jyao              #+#    #+#             */
/*   Updated: 2023/01/09 14:00:08 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_commands	*sh_ps_parser(t_shell_s *shell, char *buf_src)
{
	t_words		*head_word;
	t_commands	*head_command;

	head_word = sh_ps_lexer(shell, buf_src);
	if (head_word == NULL)
		return (NULL);
	head_command = sh_ps_parser_commands(head_word);
	if (head_command == NULL)
		sh_ps_lexer_word_free_list(head_word);
	return (head_command);
}
