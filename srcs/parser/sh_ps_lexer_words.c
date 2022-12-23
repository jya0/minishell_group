/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:57:36 by jyao              #+#    #+#             */
/*   Updated: 2022/12/22 22:36:55 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*frees mem allocated members and the word itself
**if flag is FREE_ALL, it will delete members
** else it will only free the t_word word
*/
static void	sh_ps_lexer_word_free(t_words *word, enum e_free_option flag)
{
	if (word == NULL)
		return ;
	if (flag == FREE_ALL)
	{
		if (word->str != NULL)
		{
			free(word->str);
			word->str = NULL;
		}
	}
	free(word);
}

void	sh_ps_lexer_word_free_list(t_words	*head_word)
{
	t_words	*current;
	t_words	*next;

	printf("\nfreeing words list\n");
	if (head_word == NULL)
		return ;
	current = head_word;
	while (current != NULL)
	{
		next = current->next;
		sh_ps_lexer_word_free(current, FREE_ALL);
		current = next;
	}
}

/*adds the word at the end of the list
** returns the pointer of the word added
*/
t_words	*sh_ps_lexer_word_add_end(\
t_words	*head_word, t_words	*word)
{
	t_words	*current;

	if (head_word == NULL || word == NULL)
		return (NULL);
	current = head_word;
	while (current->next != NULL)
		current = current->next;
	current->next = word;
	word->prev = current;
	return (word);
}

/*deletes the word node at index and always returns the location of the new
head_word if neccessary 
** and also frees all of its members*/
t_words	*sh_ps_lexer_word_del_at(\
t_words	*head_word, size_t index, enum e_free_option flag)
{
	t_words	*prev;
	t_words	*current;
	t_words	*next;
	size_t	i;

	if (head_word == NULL)
		return (NULL);
	current = head_word;
	i = 0;
	while (i++ < index && current->next != NULL)
		current = current->next;
	prev = current->prev;
	next = current->next;
	if (prev != NULL)
		prev->next = next;
	else
		head_word = next;
	if (next != NULL)
		next->prev = prev;
	sh_ps_lexer_word_free(current, flag);
	return (head_word);
}

/*
** head_word is passed in so that if the head is deleted, it will be 
** automatically updated accordingly!
** returns the pointer to the next word of the deleted word;
*/
t_words	*sh_ps_lexer_word_del_word(\
t_words **head_word, t_words *word, enum e_free_option flag)
{
	t_words	*prev;
	t_words	*next;

	if (head_word == NULL || word == NULL)
		return (NULL);
	prev = word->prev;
	next = word->next;
	if (prev != NULL)
		prev->next = next;
	else
		*head_word = next;
	if (next != NULL)
		next->prev = prev;
	sh_ps_lexer_word_free(word, flag);
	return (next);
}

void	sh_ps_lexer_word_print_list(t_words *head_word)
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
}
