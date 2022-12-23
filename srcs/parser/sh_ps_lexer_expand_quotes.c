/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_expand_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:14:04 by jyao              #+#    #+#             */
/*   Updated: 2022/12/23 15:01:41 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_word_quote(t_words *word)
{
	if (word == NULL)
		return (-1);
	return (word->term_type == TT_QUOTE_D || word->term_type == TT_QUOTE_S);
}

/*part of get_word_from_quote*/
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

/*part of get_word_from_quote*/
static void	copy_words_to_new_string(t_words *new_word, t_words *start)
{
	size_t	i;

	i = 0;
	while (start != NULL && start->term_type == TT_JUST_WORD)
	{
		ft_strlcpy(new_word->str + (i * sizeof(char)), \
		start->str, start->str_len + 1);
		i += start->str_len;
		start = start->next;
	}
}

static t_words	*get_word_from_quote(t_words *start)
{
	t_words	*word;
	size_t	str_len;

	if (start == NULL || is_word_quote(start) != 0)
		return (NULL);
	str_len = new_word_str_len(start);
	if (str_len <= start->str_len)
		return (start);
	word = (t_words *)ft_calloc(1, sizeof(t_words));
	if (word == NULL)
		return (NULL);
	word->str_len = str_len;
	word->str = (char *)ft_calloc(word->str_len + 1, sizeof(char));
	if (word->str == NULL)
	{
		free(word);
		return (NULL);
	}
	copy_words_to_new_string(word, start);
	word->str_start = start->str_start;
	word->term_type = TT_JUST_WORD;
	return (word);
}

void	sh_ps_lexer_expand_quotes(t_words **head_word)
{
	t_words	*word;
	t_words	*new_word;

	if (head_word == NULL)
		return ;
	word = *head_word;
	while (word != NULL)
	{
		if (is_word_quote(word) != 0)
		{
			new_word = get_word_from_quote(word->next);
			word = sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
			if (new_word != word)
			{
				while (word != NULL && word->term_type == TT_JUST_WORD)
					word = sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
				sh_ps_lexer_word_add_after(word, new_word);
			}
			else
				word = word->next;
			word = sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
		}
		else
			word = word->next;
	}
}

/*================ALREADY tested for memory leaks!==================*/
/*gcc -Wall -Wextra -Werror -g sh_ps_lexer*.c sh_ps_parser*.c -L../../libft -lft*/
/*
int	main(int argc, char	*argv[])
{
	t_words		*head_word;
	t_commands	*head_command;

	if (argc == 1)
		return (0);
	head_word = sh_ps_lexer(argv[1]);
	printf("\n>>original words<<\n");
	sh_ps_lexer_word_print_list(head_word);
	sh_ps_lexer_add_missing(head_word);
	printf("\n>>add missing spaces & missing env values<<\n");
	sh_ps_lexer_word_print_list(head_word);
	sh_ps_lexer_expand_quotes(&head_word);
	printf("\n>>connect all words in quotes<<\n");
	sh_ps_lexer_word_print_list(head_word);
	head_command = sh_ps_parser_commands(head_word);
	sh_ps_parser_commands_print_list(head_command);
	sh_ps_parser_commands_free_list(head_command);
	return (0);
}
*/
