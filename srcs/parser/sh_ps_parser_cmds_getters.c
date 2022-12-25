/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds_getters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:01:08 by jyao              #+#    #+#             */
/*   Updated: 2022/12/25 18:22:04 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
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
*/

static void	assign_command_name_args(t_commands	*command)
{
	if (command->cmd_argv == NULL)
		return ;
	command->cmd_name = command->cmd_argv[0];
	command->cmd_args = &(command->cmd_argv[1]);
}

static char	**allocate_argv(t_words *head_word, t_words **ptr_word)
{
	int		i;
	char	**argv;

	if (head_word == NULL)
		return (NULL);
	i = 0;
	*ptr_word = head_word;
	while (*ptr_word != NULL && (*ptr_word)->term_type == TT_JUST_WORD)
	{
		*ptr_word = (*ptr_word)->next;
		i++;
	}
	if (i == 0)
		return (NULL);
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	return (argv);
}

int	sh_ps_parser_get_cmd_argv(\
t_commands *command, t_words **head_word)
{
	int		i;
	t_words	*ptr_word;

	command->cmd_argv = allocate_argv(*head_word, &ptr_word);
	if (command->cmd_argv == NULL)
	{
		sh_ps_lexer_word_free_list(*head_word);
		sh_ps_parser_commands_free(command, FREE_ALL);
		printf("ERROR ARGV!\n");
		return (-1);
	}
	i = 0;
	while (*head_word != ptr_word)
	{
		command->cmd_argv[i] = (*head_word)->str;
		i++;
		sh_ps_lexer_word_del_word(head_word, *head_word, FREE_DEFAULT);
	}
	assign_command_name_args(command);
	return (0);
}

/*
int	sh_ps_parser_get_cmd_name(\
t_commands *command, t_words **head_word, t_words	**word)
{
	command->cmd_name = (*word)->str;
	sh_ps_lexer_word_del_word(head_word, *word, FREE_DEFAULT);
	*word = *head_word;
	return (0);
}
*/

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

static int	get_redir(\
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

int	sh_ps_parser_get_redirs(\
t_commands *command, t_words **head_word)
{
	t_words	*word;

	if (head_word == NULL || *head_word == NULL)
		return (-1);
	word = *head_word;
	while (word != NULL && word->term_type != TT_PIPE)
	{
		if (*(word->str) == '<' || *(word->str) == '>')
		{
			if (get_redir(command, head_word, &word) != 0)
			{
				sh_ps_lexer_word_free_list(*head_word);
				sh_ps_parser_commands_free(command, FREE_ALL);
				printf("ERROR REDIRECTION!\n");
				return (-1);
			}
		}
		else
			word = word->next;
	}
	return (0);
}
