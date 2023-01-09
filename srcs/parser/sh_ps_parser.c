/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:10:46 by jyao              #+#    #+#             */
/*   Updated: 2023/01/10 01:47:16 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_commands	*sh_ps_parser(t_shell_s *shell, char *buf_src)
{
	t_words		*head_word;
	t_commands	*head_command;
	int			lexer_error_code;

	lexer_error_code = 0;
	head_word = sh_ps_lexer(shell, buf_src, &lexer_error_code);
	if (lexer_error_code != 0)
		ft_putstr_fd(\
		sh_get_error_msg(shell->exit_info.exit_code), STDERR_FILENO);
	if (head_word == NULL)
		return (NULL);
	head_command = sh_ps_parser_commands(head_word);
	if (head_command == NULL)
		sh_ps_lexer_word_free_list(head_word);
	return (head_command);
}
