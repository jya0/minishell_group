/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_add_missing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:12:23 by jyao              #+#    #+#             */
/*   Updated: 2022/12/22 17:21:29 by jyao             ###   ########.fr       */
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
	word->str = function_search_env();
	free(ptr_str);
	word->str_len = ft_strlen(word->str);
	word->str_start = NULL;
	word->term_type = TT_JUST_WORD;
}
*/

// /*
static t_words	*get_word_missing_space(\
const char *spc_start, const char *spc_end)
{
	t_words	*word;
	char	*str;
	int		str_len;

	if (spc_start == NULL || spc_end == NULL || spc_start == spc_end)
		return (NULL);
	str_len = (spc_end - spc_start) / sizeof(char);
	// printf("start |%c| end |%c| len |%d|\n", *spc_start, *spc_end, str_len);
	str = ft_substr((const char *)spc_start, 0, str_len);
	if (str == NULL)
		return (NULL);
	// printf("str = |%s|\n", str);
	// exit(1);
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

/*
** returns the pointer to the new_word
*/
// /*
t_words	*sh_ps_lexer_word_add_after(t_words *word, t_words *new_word)
{
	t_words	*next;

	if (new_word == NULL)
		return (NULL);
	next = word->next;
	if (next != NULL)
	{
		new_word->next = next;
		next->prev = new_word;
	}
	word->next = new_word;
	new_word->prev = word;
	return (new_word);
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
			return (word->term_type);
		else if (quote_state == (int)word->term_type)
			return (IN_NULL);
		else
			word->term_type = TT_JUST_WORD;
	}
	return (quote_state);
}

/*
** this function searches for quotes and fills in missing spaces
** also expands variables then add the value from env directly
*/

// /*
int	sh_ps_lexer_add_missing(t_words	*head_word)
{
	t_words				*word;
	enum e_quote_state	quote_state;

	if (head_word == NULL)
		return (-1);
	word = head_word;
	quote_state = IN_NULL;
	while (word != NULL)
	{
		quote_state = get_quote_state(word, quote_state);
		if (quote_state != IN_NULL)
		{
			sh_ps_lexer_word_add_after(word, get_word_missing_space(\
			word->str_start + word->str_len * sizeof(char), \
			word->next->str_start));
			if (word->term_type == TT_VAR)
			{
				// if (quote_state == IN_QUOTE_D)
				// 	expand_variable(word);
				word->term_type = TT_JUST_WORD;
			}
		}
		word = word->next;
	}
	if (quote_state != IN_NULL)
	{
		return (printf("ERROR UNCLOSED QUOTES!\n"));
		//heredoc_function to read from standard input
		sh_ps_lexer_add_missing(word);
	}
	return (0);
}
// */