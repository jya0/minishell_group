/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:37:03 by jyao              #+#    #+#             */
/*   Updated: 2023/01/13 14:35:26 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_ps_lexer_word_print_list(t_words *head_word)
{
	t_words	*last;

	if (head_word == NULL)
	{
		printf("\n-------NO MORE WORDS IN LIST!------\n");
		return ;
	}
	printf("\n------going forwards-------\n");
	while (head_word != NULL)
	{
		printf("%s %ld %d\n", \
		head_word->str, head_word->str_len, head_word->term_type);
		if (head_word->next == NULL)
			last = head_word;
		head_word = head_word->next;
	}
	printf("\n------going backwards-------\n");
	while (last != NULL)
	{
		printf("%s %ld %d\n", last->str, last->str_len, last->term_type);
		last = last->prev;
	}
}

t_words	*sh_ps_lexer(\
t_shell_s *shell, const char *buf_src, int *lexer_error_code)
{
	t_words				*head_word;

	head_word = sh_ps_lexer_words_gen(buf_src);
	sh_ps_lexer_word_print_list(head_word);
	sh_ps_lexer_heredoc_mark_variable(head_word);
	*lexer_error_code = sh_ps_lexer_add_missing(shell, &head_word);
	if (*lexer_error_code != 0)
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	printf("after add missing space!\n");
	sh_ps_lexer_word_print_list(head_word);
	sh_ps_lexer_expand_quotes(&head_word);
	sh_ps_lexer_word_print_list(head_word);
	sh_ps_lexer_join_connected(&head_word);
	sh_ps_lexer_word_print_list(head_word);
	*lexer_error_code = sh_ps_lexer_check_error(head_word);
	if (*lexer_error_code != 0)
	{
		shell->exit_info.exit_code = *lexer_error_code;
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	}
	return (head_word);
}
