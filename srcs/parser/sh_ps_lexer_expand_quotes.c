/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_expand_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:14:04 by jyao              #+#    #+#             */
/*   Updated: 2022/12/22 19:44:53 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	new_word_str_len(t_words *start)
{
	size_t	str_len;

	str_len = 0;
	while (start != NULL && start->term_type == TT_JUST_WORD)
	{
		str_len += start->str_len;
		start = start->next;
	}
	return (str_len);
}

static t_words	*get_word_from_quote(t_words *start)
{
	t_words	*word;
	size_t	i;

	if (start == NULL)
		return (NULL);
	word = (t_words *)ft_calloc(1, sizeof(t_words));
	if (word == NULL)
		return (NULL);
	word->str = (char *)ft_calloc(word->str_len + 1, sizeof(char));
	if (word->str == NULL)
	{
		free(word);
		return (NULL);
	}
	word->str_len = new_word_str_len(start);
	word->str_start = start->str_start;
	word->term_type = TT_JUST_WORD;
	i = 0;
	while (start != NULL && start->term_type == TT_JUST_WORD)
	{
		// printf("start = |%c|\n", *(word->str + (i * sizeof(char))));
		ft_strncpy(word->str + (i * sizeof(char)), start->str, start->str_len);
		// ft_strlcat(word->str, start->str, start->str_len);
		i += start->str_len;
		start = start->next;
	}
	return (word);
}

int	sh_ps_lexer_expand_quotes(t_words **head_word)
{
	t_words	*word;
	t_words	*new_word;

	if (head_word == NULL || *head_word == NULL)
		return (-1);
	word = *head_word;
	while (word != NULL)
	{
		if (word->term_type == TT_QUOTE_D || word->term_type == TT_QUOTE_S)
		{
			new_word = get_word_from_quote(word->next);
			printf("%s %ld %d\n", new_word->str, new_word->str_len, new_word->term_type);
			exit(1);
			while (word != NULL && word->term_type == TT_JUST_WORD)
			{
				sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
				word = word->next;
			}
			sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
		}
	}
	return (0);
}
