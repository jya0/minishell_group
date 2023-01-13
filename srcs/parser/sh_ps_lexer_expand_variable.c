/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_lexer_expand_variable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:38:55 by jyao              #+#    #+#             */
/*   Updated: 2023/01/13 16:24:19 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_var_exit_status(t_shell_s *shell, t_words *word)
{
	char	*value;

	value = ft_itoa(shell->exit_info.exit_code);
	free(word->str);
	word->str = value;
	word->str_len = ft_strlen(word->str);
	word->term_type = TT_JUST_WORD;
}

static t_words	*expand_env_var(t_shell_s *shell, t_words *word)
{
	char	*value;
	t_words	*head_env_word;

	value = sh_ex_searchenvvar(shell, &((word->str)[1]));
	if (value == NULL)
		return (word);
	head_env_word = sh_ps_lexer_words_gen(value);
	if (head_env_word != NULL)
		sh_ps_lexer_word_add_after(word, head_env_word);
	return (word);
}

t_words	*sh_ps_lexer_expand_variable(\
t_shell_s *shell, t_words *word, enum e_quote_state quote_state)
{
	if (word == NULL)
		return (NULL);
	if (word->str_len <= 1)
	{
		if ((word->str)[1] == '\0' \
		&& *(word->str_start + sizeof(char)) != '\0' \
		&& ft_strchr("\'\"", *(word->str_start + sizeof(char))) != NULL \
		&& quote_state == IN_NULL)
			return (word);
		else
			return (NULL);
	}
	if (ft_strcmp(word->str, "$?") == 0)
	{
		expand_var_exit_status(shell, word);
		return (NULL);
	}
	return (expand_env_var(shell, word));
}
