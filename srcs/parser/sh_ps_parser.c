/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:10:46 by jyao              #+#    #+#             */
/*   Updated: 2022/12/27 15:16:00 by yoyohann         ###   ########.fr       */
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
	// sh_ps_parser_commands_print_list(head_command);
	return (head_command);
}

/*================ALREADY tested for memory leaks!==================*/
/*gcc -Wall -Wextra -Werror -g sh_ps_lexer*.c sh_ps_parser*.c -L../../libft -lft*/
/*
int	main(int argc, char	*argv[])
{
	t_commands	*head_command;

	if (argc == 1)
		return (0);
	head_command = sh_ps_parser(argv[1]);
	sh_ps_parser_commands_free_list(head_command);
	return (0);
}
*/