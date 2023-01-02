/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_pipelines_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:03:18 by jyao              #+#    #+#             */
/*   Updated: 2022/12/29 18:10:51 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_word_conditional_delim(t_words *word)
{
	return (word == NULL || word->term_type == TT_COND_AND \
	|| word->term_type == TT_COND_OR || word->term_type == TT_BKT_RND_R);
}

/*finds the word_delim to mark the end_word of the pipeline
** and updates the head_word
** returns the old head to pass it to parse for the head_command
** of the pipeline
*/
static t_words	*find_delim_word_pipeline(t_words **head_word)
{
	t_words	*head_word_old;
	t_words	*word_delim;

	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	head_word_old = *head_word;
	word_delim = *head_word;
	while (word_delim != NULL \
	&& word_delim->term_type != TT_COND_AND \
	&& word_delim->term_type != TT_COND_OR)
		word_delim = word_delim->next;
	*head_word = word_delim;
	if (word_delim != NULL)
	{
		word_delim->prev->next = NULL;
		word_delim->prev = NULL;
	}
	return (head_word_old);
}

/*
** Gets buf_src from readline and gives a single pipeline of commands
*/
t_pipelines	*sh_ps_parser_pipelines(t_shell_s *shell, t_words **head_word)
{
	t_pipelines	*pipeline;

	printf("%p\n", shell);
	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	pipeline = (t_pipelines *)ft_calloc(1, sizeof(t_pipelines));
	if (pipeline == NULL)
		return (NULL);
	pipeline->words = find_delim_word_pipeline(head_word);
	pipeline->commands = sh_ps_parser_commands(pipeline->words);
	if (*head_word != NULL)
	{
		pipeline->cond_term_type = (*head_word)->term_type;
		sh_ps_lexer_word_del_word(head_word, *head_word, FREE_ALL);
	}
	return (pipeline);
}

/*================NOT YET tested for memory leaks!==================*/
