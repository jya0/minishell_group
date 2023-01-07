/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 14:57:36 by jyao              #+#    #+#             */
/*   Updated: 2023/01/07 20:38:35 by yoyohann         ###   ########.fr       */
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

/*
** returns the pointer to the new_word
*/
// /*
t_words	*sh_ps_lexer_word_add_after(t_words *word, t_words *new_word)
{
	t_words	*next;

	if (word == NULL || new_word == NULL)
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
