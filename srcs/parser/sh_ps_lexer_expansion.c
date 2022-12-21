/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:12:23 by jyao              #+#    #+#             */
/*   Updated: 2022/12/21 21:17:09 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Adds the word at target's location
** i.e if the target is the head/tail, the word becomes the new head/tail.
** else the target is 
*/

/*
t_words	*sh_ps_lexer_word_create(\
char *str, const char *str_start, int str_len, enum e_term_type term_type)
{
	t_words	*word;

	word = (t_word *)ft_calloc(1, sizeof(word));
	if (word == NULL)
		return (NULL);
	word->str = str;
	word->str_start = str_start;
	word->str_len = str_len;
	word->term_type = term_type;
	return (word);
}
*/

/*
static void	expand_variables(t_words *start, t_words *end)
{
	char	*ptr_str;
	t_words	*word;

	if (start == NULL)
		return ;
	word = start;
	while (word != end)
	{
		if (word->term_type == TT_VAR)
		{
			ptr_str = word->str;
			// word->str = expand_variable();
			// free(ptr_str);
			word->str_len = ft_strlen(word->str);
			word->str_start = NULL;
			word->term_type = TT_JUST_WORD;
		}
		word = word->next;
	}
}
*/

/*
static void	expand_variable(t_words *word)
{
	char	*ptr_str;
	t_words	*word;

	if (word == NULL)
		return ;
	ptr_str = word->str;
	// word->str = function_search_env();
	// free(ptr_str);
	word->str_len = ft_strlen(word->str);
	word->str_start = NULL;
	word->term_type = TT_JUST_WORD;
}
*/

/*
static int	is_word_quote(t_words *word)
{
	if (word == NULL)
		return (0);
	return (word->term_type == TT_QUOTE_D || word->term_type == TT_QUOTE_S);
}
*/

/*
static t_words	*get_missing_space(char *spc_start, char *spc_end)
{
	t_words	*word;
	char	*str;
	int		str_len;

	if (spc_start == NULL || spc_end == NULL || spc_start == spc_end)
		return (NULL);
	str_len = (*spc_end - *spc_start) / sizeof(char);
	str = ft_substr((const char *)spc_start, 0, str_len);
	if (str == NULL)
		return (NULL);
	word = sh_ps_lexer_word_create(str, spc_start, str_len, TT_JUST_WORD);
	if (word == NULL)
		return (NULL);
	return (word);
}
*/

/*
** returns the pointer to the new_word
*/
/*
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
*/

/*
** this function searches for quotes and fills in missing spaces
** also expands variables from env directly
*/

/*
int	sh_ps_lexer_expansion(t_words	**head_word)
{
	t_words				*word;
	enum e_quote_state	quote_state;

	if (head_word == NULL || *head_word == NULL)
		return (-1);
	word = *head_word;
	quote_state = IN_NULL;
	while (word != NULL)
	{
		if (is_word_quote(word) == 1)
			quote_state = word->term_type;
		if (quote_state != IN_NULL)
		{
			if (sh_ps_lexer_word_add_after(word, get_missing_space(\
			word->str_start + word->str_len * sizeof(char), \
			word->next->str_start)) != NULL)
				word = word->next->next;
		}
		if (word->term_type == TT_VAR)
		{
			if (quote_state == IN_QUOTE_D)
	
			word->term_type == TT_JUST_WORD;
		}
	}
	return (0);
}
*/