/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sh_ps_lexer_check_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:39:57 by jyao              #+#    #+#             */
/*   Updated: 2022/12/27 13:37:37 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_bracket(t_words *word)
{
	static int			bracket_stack[BKT_STK_MAX];
	static unsigned int	index;

	if (word == NULL && index != 0)
		return (perror("ERROR BRACKET!\n"), -1);
	if (word->term_type == TT_BKT_RND_L)
	{
		if (index == 0)
			bracket_stack[index++] = TT_BKT_RND_L;
		else if (bracket_stack[index] == TT_BKT_RND_L)
		{
			index++;
			if (index >= BKT_STK_MAX)
				return (perror("ERROR BRACKET!\n"), -1);
			bracket_stack[index] = TT_BKT_RND_L;
		}
	}
	if (word->term_type == TT_BKT_RND_R)
	{
		if (index == 0)
			return (perror("ERROR BRACKET!\n"), -1);
		else if (bracket_stack[index] == TT_BKT_RND_L)
			bracket_stack[index--] == 0;
	}
	return (0);
}

static int	check_redirection(t_words *word)
{
	if (word == NULL || \
	(word->term_type != TT_APPND_IN && word->term_type != TT_APPND_OUT \
	&& word->term_type != TT_REDIR_IN && word->term_type != TT_REDIR_OUT))
		return (0);
	if (word->next == NULL || word->next->term_type != TT_JUST_WORD)
		return (perror("ERROR REDIRECTION!\n"), -1);
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
		return (perror("ERROR PIPE!\n"), -1);
	}
	return (0);
}

static int	check_conditional(t_words *word)
{
	if (word == NULL || \
	(word->term_type != TT_COND_AND && word->term_type != TT_COND_OR))
		return (0);
	if (word->prev == NULL || word->next == NULL)
	{
		return (perror("ERROR COND!\n"), -1);
	}
	else if (word->prev != NULL || word->prev->term_type != TT_JUST_WORD)
		return (perror("ERROR COND!\n"), -1);
	return (0);
}

int	sh_ps_lexer_check_error(t_words *head_word)
{
	t_words	*word;

	word = head_word;
	while (word != NULL)
	{
		if (word->term_type != TT_JUST_WORD)
		{
			if (check_pipe(word) != 0)
				return (-1);
			if (check_bracket(word) != 0)
				return (-1);
			if (check_redirection(word) != 0)
				return (-1);
			if (check_conditional(word) != 0)
				return (-1);
		}
		word = word->next;
	}
	if (check_bracket(word) != 0)
		return (-1);
	return (0);
}
