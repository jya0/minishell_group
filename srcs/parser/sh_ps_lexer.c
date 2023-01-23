/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:37:03 by jyao              #+#    #+#             */
/*   Updated: 2023/01/19 03:07:14 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_words	*create_just_word(char *str)
{
	t_words	*new_word;

	if (str == NULL)
		return (NULL);
	new_word = ft_calloc(1, sizeof(t_words));
	if (new_word == NULL)
		return (NULL);
	new_word->str = str;
	new_word->str_len = ft_strlen(str);
	new_word->term_type = TT_JUST_WORD;
	return (new_word);
}

/*
** returns the head of the pair of splitted words
*/
static t_words	*split_one_word(t_words	*og_word, char *delims)
{
	size_t	i;
	t_words	*new_word_1;
	t_words	*new_word_2;

	if (og_word == NULL)
		return (NULL);
	i = 0;
	while ((og_word->str)[i] != 0)
	{
		if (ft_strchr(delims, (og_word->str)[i]) != NULL)
			break ;
		i++;
	}
	if ((og_word->str)[i] == 0)
		return (NULL);
	new_word_1 = create_just_word(ft_substr(og_word->str, 0, i));
	new_word_2 = create_just_word(\
	ft_substr(og_word->str, i + 1, og_word->str_len));
	sh_ps_lexer_word_add_after(new_word_1, new_word_2);
	sh_ps_lexer_word_add_after(new_word_2, og_word->next);
	og_word->next = new_word_1;
	new_word_1->prev = og_word;
	return (new_word_1);
}

static void	split_head_word(t_words **head_word)
{
	t_words	*split_head;

	if (head_word == NULL || *head_word == NULL)
		return ;
	split_head = split_one_word(*head_word, DELIM_SPACES);
	if (split_head == NULL)
		return ;
	sh_ps_lexer_word_del_word(head_word, *head_word, FREE_ALL);
}

static void	prune_null_words(t_words **head_word)
{
	t_words	*word;

	if (head_word == NULL || *head_word == NULL)
		return ;
	word = *head_word;
	while (word)
	{
		if (word->str == NULL && word->term_type == TT_JUST_WORD)
			word = sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
		else
			word = word->next;
	}
}

/* // void	sh_ps_lexer_word_print_list(t_words *head_word)
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
} */

t_words	*sh_ps_lexer(\
t_shell_s *shell, const char *buf_src, int *lexer_error_code)
{
	t_words				*head_word;

	head_word = sh_ps_lexer_words_gen(buf_src);
	sh_ps_lexer_heredoc_mark_variable(head_word);
	*lexer_error_code = sh_ps_lexer_add_missing(shell, &head_word);
	if (*lexer_error_code != 0)
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	sh_ps_lexer_expand_quotes(&head_word);
	sh_ps_lexer_join_connected(&head_word);
	prune_null_words(&head_word);
	*lexer_error_code = sh_ps_lexer_check_error(head_word);
	if (*lexer_error_code != 0)
	{
		shell->exit_info.exit_code = *lexer_error_code;
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	}
	split_head_word(&head_word);
	return (head_word);
}
