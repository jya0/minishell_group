/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_pipelines_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:03:18 by jyao              #+#    #+#             */
/*   Updated: 2022/12/28 19:54:33 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_commands	*set_word_end_for_pipeline(t_words **head_word, t_words *end)
{
	
}

/*
** Gets buf_src from readline and gives a single pipeline of commands
*/
t_pipelines	*sh_ps_parser_pipelines(t_shell_s *shell, t_words *head_word)
{
	t_words	*word;
	t_words	*null_word;

	if (head_word == NULL)
		return (NULL);
	
}
