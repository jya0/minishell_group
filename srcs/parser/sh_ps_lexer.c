/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:37:03 by jyao              #+#    #+#             */
/*   Updated: 2023/01/11 15:21:25 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*why do we need this when we already have ft_split????
**because ft_split only takes one delim char and moreover this strtok
implementation is in my opinion cleaner*/

/*returns term_type depending on the word*/
static enum e_term_type	get_term_type(t_words	*word)
{
	int	i;
	int	sum;

	if (word == NULL || word->str_len <= 0)
		return (TT_ERROR);
	if (ft_strrchr(DELIM_TERMS_ALL, *(word->str)) == NULL)
		return (TT_JUST_WORD);
	if (*(word->str) == '$' && word->str_len > 1)
		return (TT_VAR);
	if (word->str_len > 2)
		return (TT_ERROR);
	sum = word->str[0];
	if (word->str[1] != '\0')
		sum *= word->str[1];
	i = 0;
	while (DELIM_TERMS_ALL[i] != '\0')
	{
		if (sum == DELIM_TERMS_ALL[i] \
		|| sum == DELIM_TERMS_ALL[i] * DELIM_TERMS_ALL[i])
			return (sum);
		i++;
	}
	return (TT_ERROR);
}

/*functions increments the index of char in buf_stored 
**while it is still a char from char_set.
**if flag is not 0 that would mean the function will negate
**and inturn forward while a char is not a part of the char_set*/
static size_t	forward_while_char_set(\
const char *buf_stored, const char *char_set, int flag)
{
	int		i;
	char	*strchr_return;

	if (buf_stored == NULL || char_set == NULL)
		return (printf("no input!\n"));
	i = 0;
	while (buf_stored[i] != '\0')
	{
		strchr_return = ft_strrchr(char_set, buf_stored[i]);
		if ((flag == 0 && strchr_return == NULL) \
		|| (flag != 0 && strchr_return != NULL))
			break ;
		i++;
	}
	return (i);
}

static t_words	*make_word(const char *buf_stored, size_t start, size_t *end)
{
	t_words	*word;
	char	*c;

	word = (t_words *)ft_calloc(1, sizeof(t_words));
	if (word == NULL)
		return (NULL);
	c = ft_strrchr(DELIM_TERMS_ALL, buf_stored[start]);
	if (c != NULL)
	{
		(*end)++;
		if (*c == '$')
		{
			if (buf_stored[*end] == '$')
				(*end)++;
			else
				(*end) += forward_while_char_set(\
				&buf_stored[*end], UNDERSCORE D_DIGITS A_LOWER A_UPPER "?", 0);
		}
		else if ((*c != '\"' && *c != '\'' && *c != '|') && buf_stored[*end] != \
		'\0' && ft_strrchr(DELIM_TERMS_COMBINEABLE, buf_stored[*end]) != NULL)
			(*end)++;
	}
	word->str_len = *end - start;
	word->str = ft_substr(buf_stored, start, word->str_len);
	return (word);
}

/*static function to simplify sh_ps_lexer*/
static t_words	*get_next_word(const char *buf_src)
{
	static const char	*buf_stored;
	size_t				start;
	size_t				end;
	t_words				*word;

	if (buf_src == NULL && buf_stored == NULL)
		return (NULL);
	else if (buf_src != NULL)
		buf_stored = buf_src;
	start = forward_while_char_set(buf_stored, DELIM_SPACES, 0);
	if (buf_stored[start] == '\0')
	{
		buf_stored = NULL;
		return (NULL);
	}
	end = start + forward_while_char_set(\
	&buf_stored[start], DELIM_SPACES DELIM_TERMS_ALL, -1);
	word = make_word(buf_stored, start, &end);
	word->term_type = get_term_type(word);
	word->str_start = &(buf_stored[start]);
	if (buf_stored[end] == '\0')
		buf_stored = NULL;
	else
		buf_stored = &buf_stored[end];
	return (word);
}

/* static void	sh_ps_lexer_word_print_list(t_words *head_word)
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
		printf("%s %ld %d\n", head_word->str, head_word->str_len, head_word->term_type);
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

/*
** Gets the input from readline, then returns a words each time it is called!
** lexer_error_code is added later to get the error code if any;
*/
t_words	*sh_ps_lexer(\
t_shell_s *shell, const char *buf_src, int *lexer_error_code)
{
	t_words				*head_word;
	t_words				*word;

	(void)shell;
	word = get_next_word(buf_src);
	head_word = word;
	while (word != NULL)
	{
		word = get_next_word(NULL);
		sh_ps_lexer_word_add_end(head_word, word);
	}
	sh_ps_lexer_heredoc_mark_variable(head_word);
	if (sh_ps_lexer_add_missing(shell, &head_word) != 0)
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	sh_ps_lexer_expand_quotes(&head_word);
	sh_ps_lexer_join_connected(&head_word);
	*lexer_error_code = sh_ps_lexer_check_error(head_word);
	if (*lexer_error_code != 0)
	{
		shell->exit_info.exit_code = *lexer_error_code;
		return (sh_ps_lexer_word_free_list(head_word), NULL);
	}
	return (head_word);
}
