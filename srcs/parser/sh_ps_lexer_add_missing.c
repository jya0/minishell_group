/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_add_missing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:12:23 by jyao              #+#    #+#             */
/*   Updated: 2022/12/27 15:06:11 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Adds the word at target's location
** i.e if the target is the head/tail, the word becomes the new head/tail.
** else the target is 
*/

/*
static void	expand_variable(t_words *word)
{
	char	*ptr_str;

	if (word == NULL)
		return ;
	ptr_str = word->str;
	// word->str = ft_strdup(sh_ex_searchenvvar(shell, &(ptr_str[1])));
	// free(ptr_str);
	word->str_len = ft_strlen(word->str);
	word->str_start = NULL;
	word->term_type = TT_JUST_WORD;
}
*/

// /*
static t_words	*get_word_missing_space(\
const char *spc_start, t_words *word_next)
{
	t_words	*word;
	char	*str;
	int		str_len;

	if (spc_start == NULL || \
	word_next == NULL || spc_start == word_next->str_start)
		return (NULL);
	str_len = (word_next->str_start - spc_start) / sizeof(char);
	str = ft_substr((const char *)spc_start, 0, str_len);
	if (str == NULL)
		return (NULL);
	word = (t_words *)ft_calloc(1, sizeof(t_words));
	if (word == NULL)
	{
		free(str);
		return (NULL);
	}
	word->str = str;
	word->str_start = spc_start;
	word->str_len = str_len;
	word->term_type = TT_JUST_WORD;
	return (word);
}
// */

static enum e_quote_state	get_quote_state(\
t_words *word, enum e_quote_state quote_state)
{
	if (word == NULL)
		return (quote_state);
	if (word->term_type == TT_QUOTE_D || word->term_type == TT_QUOTE_S)
	{
		if (quote_state == IN_NULL)
			return ((int)word->term_type);
		else if (quote_state == (int)word->term_type)
			return (IN_NULL);
		else
			word->term_type = TT_JUST_WORD;
	}
	return (quote_state);
}

static t_words	*word_term_type_change(\
t_words *word, enum e_quote_state quote_state)
{
	if (word == NULL \
	|| (word->term_type != TT_QUOTE_D && word->term_type != TT_QUOTE_S))
		return (word->next);
	if (word->term_type == TT_VAR)
	{
		word->term_type == TT_JUST_WORD;
		if (quote_state != IN_QUOTE_S)
		{
			if (//expandvariable == NULL)
			{
				sh_ps_lexer_word_del_word(&word, word, FREE_ALL);
				return (word);
			}
		}
	}
	else if (quote_state != NULL)
		word->term_type = TT_JUST_WORD;
	return (word->next);
}

/*
** this function searches for quotes and fills in missing spaces
** also expands variables then add the value from env directly
*/
// /*
int	sh_ps_lexer_add_missing(t_words *head_word)
{
	t_words				*word;
	enum e_quote_state	quote_state;

	if (head_word == NULL)
		return (-1);
	word = head_word;
	quote_state = IN_NULL;
	while (word != NULL)
	{
		printf("hey\n");
		quote_state = get_quote_state(word, quote_state);
		if (quote_state != IN_NULL)
		{
			sh_ps_lexer_word_add_after(word, get_word_missing_space(\
			word->str_start + word->str_len * sizeof(char), \
			word->next));
		}
		word = word_term_type_change(word, quote_state);
	}
	if (quote_state != IN_NULL)
	{
		return (printf("ERROR UNCLOSED QUOTES!\n"));
		//heredoc_function to read from standard input
		// sh_ps_lexer_add_missing(word);
	}
	return (0);
}
// */