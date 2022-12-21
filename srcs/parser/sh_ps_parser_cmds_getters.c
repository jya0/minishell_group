/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds_getters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:01:08 by jyao              #+#    #+#             */
/*   Updated: 2022/12/19 22:09:29 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_ps_parser_get_cmd_args(\
t_commands *command, t_words **head_word, t_words **word)
{
	int		i;
	t_words	*ptr_word;

	i = 0;
	ptr_word = *word;
	while (ptr_word != NULL && ptr_word->term_type == TT_JUST_WORD)
	{
		ptr_word = ptr_word->next;
		i++;
	}
	if (i == 0)
		return (0);
	command->cmd_args = (char **)ft_calloc(i + 1, sizeof(char *));
	if (command->cmd_args == NULL)
		return (-1);
	i = 0;
	while (*head_word != ptr_word)
	{
		command->cmd_args[i] = (*head_word)->str;
		i++;
		sh_ps_lexer_word_del_word(head_word, *head_word, FREE_DEFAULT);
	}
	*word = *head_word;
	return (0);
}

int	sh_ps_parser_get_cmd_name(\
t_commands *command, t_words **head_word, t_words	**word)
{
	command->cmd_name = (*word)->str;
	sh_ps_lexer_word_del_word(head_word, *word, FREE_DEFAULT);
	*word = *head_word;
	return (0);
}

static void	add_redirection(\
t_redirections **head_redir, t_redirections *redir)
{
	t_redirections	*redirection;

	if (head_redir == NULL || redir == NULL)
		return ;
	if (*head_redir == NULL)
	{
		*head_redir = redir;
		return ;
	}
	redirection = *head_redir;
	while (redirection->next != NULL)
		redirection = redirection->next;
	redirection->next = redir;
}

int	sh_ps_parser_get_redirs(\
t_commands *command, t_words **head_word, t_words	**word)
{
	t_redirections	*redirection;

	if ((*word)->next == NULL || (*word)->next->term_type != TT_JUST_WORD)
		return (-1);
	redirection = (t_redirections *)ft_calloc(1, sizeof(t_redirections));
	if (redirection == NULL)
		return (-1);
	redirection->redir_file = (*word)->next->str;
	sh_ps_lexer_word_del_word(head_word, (*word)->next, FREE_DEFAULT);
	redirection->redir_term_type = (*word)->term_type;
	if (redirection->redir_term_type == TT_REDIR_IN \
	|| redirection->redir_term_type == TT_APPND_IN)
		add_redirection(&(command->redirs_in), redirection);
	else
		add_redirection(&(command->redirs_out), redirection);
	sh_ps_lexer_word_del_word(head_word, *word, FREE_ALL);
	*word = *head_word;
	return (0);
}
