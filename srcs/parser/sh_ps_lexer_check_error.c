/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_check_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:39:57 by jyao              #+#    #+#             */
/*   Updated: 2023/01/03 20:21:48 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redirection(t_words *word)
{
	if (word == NULL || \
	(word->term_type != TT_APPND_IN && word->term_type != TT_APPND_OUT \
	&& word->term_type != TT_REDIR_IN && word->term_type != TT_REDIR_OUT))
		return (0);
	if (word->next == NULL || word->next->term_type != TT_JUST_WORD)
		return (perror("LEXER: ERROR REDIRECTION\n"), -1);
	return (0);
}

static int	check_pipe(t_words *word)
{
	if (word == NULL || word->term_type != TT_PIPE)
		return (0);
	if (word->prev == NULL || word->next == NULL)
	{
		//call heredoc function to add more
		//check_pipe(new_word_chain)
		return (perror("LEXER: ERROR PIPE!\n"), -1);
	}
	return (0);
}

int	sh_ps_lexer_check_error(t_words *head_word)
{
	t_words	*word;

	word = head_word;
	while (word != NULL)
	{
		if (word->term_type == TT_ERROR)
			return (perror("LEXER: SYNTAX ERROR!\n"), -1);
		else if (word->term_type != TT_JUST_WORD)
		{
			if (check_pipe(word) != 0)
				return (-1);
			if (check_redirection(word) != 0)
				return (-1);
		}
		word = word->next;
	}
	return (0);
}
