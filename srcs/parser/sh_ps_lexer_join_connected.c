/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_join_connected.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:51:23 by jyao              #+#    #+#             */
/*   Updated: 2023/01/11 21:41:02 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** joins the strs of the first and the second words and saves it to the
** first word, then it returns the second_word's ptr for deletion later
*/
static t_words	*join_str_two_words(t_words *first_word, t_words *second_word)
{
	char	*new_str;

	if (first_word == NULL || second_word == NULL)
		return (NULL);
	new_str = ft_strjoin(first_word->str, second_word->str);
	if (new_str == NULL)
		return (NULL);
	free(first_word->str);
	first_word->str = new_str;
	first_word->str_len = ft_strlen(new_str);
	return (second_word);
}

/*
** this function joins the words originally written next to each other
** on the command line but was separated due to this minishell parser
** this minishell parser splits everything by special chars and spaces
** and so this function aims to join back words that are next to each other
**
** to do this, simply check if the next word's previous character is a ' or "
** the only scenario for when two words are meant to be next to each other
** but are separated due to the parser.
*/
int	sh_ps_lexer_join_connected(t_words	**head_word)
{
	t_words	*word;

	if (head_word == NULL || (*head_word) == NULL)
		return (0);
	word = *head_word;
	while (word != NULL)
	{
		if (word->next != NULL && word->next->term_type == TT_JUST_WORD \
		&& ft_strchr(S_D_QUOTES, \
		*(word->next->str_start - sizeof(char))) != NULL \
		&& word->term_type == TT_JUST_WORD)
		{
			join_str_two_words(word, word->next);
			word->next = \
			sh_ps_lexer_word_del_word(head_word, word->next, FREE_ALL);
			if (word->next != NULL)
				word->next->prev = word;
		}
		else
			word = word->next;
	}
	return (0);
}
