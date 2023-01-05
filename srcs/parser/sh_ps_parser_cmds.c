/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:18:27 by jyao              #+#    #+#             */
/*   Updated: 2023/01/06 01:06:03 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	pipe_error_check(t_words *word, enum e_pipe_error_check flag)
{
	if (word == NULL)
		return (0);
	if (flag == CHECK_BEFORE)
		return (word->term_type == TT_PIPE \
		&& word->prev == NULL);
	else if (flag == CHECK_AFTER)
		return (word->term_type == TT_PIPE \
		&& word->next == NULL);
	return (0);
}

/* static t_commands	*get_next_command(t_words **head_word)
{
	t_commands	*command;

	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	if (pipe_error_check(*head_word, CHECK_BEFORE) != 0)
	{
		printf("PIPE ERROR!\n");
		return (NULL);
	}
	command = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (command == NULL)
		return (NULL);
	if (sh_ps_parser_get_redirs(command, head_word) != 0 \
	|| sh_ps_parser_get_cmd_argv(command, head_word) != 0)
		return (NULL);
	if (pipe_error_check(*head_word, CHECK_AFTER) != 0)
	{
		// get_more_words()
		printf("PIPE ERROR!\n");
	}
	// sh_ps_lexer_word_print_list(*head_word);
	sh_ps_lexer_word_del_word(head_word, *head_word, FREE_ALL);
	return (command);
} */

static void	str_to_lowercase(char *cmd_name)
{
	int	i;

	if (cmd_name == NULL)
		return ;
	i = 0;
	while (cmd_name[i] != '\0')
	{
		if (cmd_name[i] >= 'A' && cmd_name[i] <= 'Z')
			cmd_name[i] += 'a' - 'A';
		i++;
	}
}

static t_commands	*get_next_command(t_words **head_word)
{
	t_commands	*command;

	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	if (pipe_error_check(*head_word, CHECK_BEFORE) != 0)
	{
		printf("PIPE ERROR!\n");
		return (NULL);
	}
	command = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (command == NULL)
		return (NULL);
	if (sh_ps_parser_get_redirs(command, head_word) != 0 \
	|| sh_ps_parser_get_cmd_argv(command, head_word) != 0)
		return (NULL);
	if (pipe_error_check(*head_word, CHECK_AFTER) != 0)
	{
		// get_more_words()
		printf("PIPE ERROR!\n");
	}
	// sh_ps_lexer_word_print_list(*head_word);
	str_to_lowercase(command->cmd_name);
	sh_ps_lexer_word_del_word(head_word, *head_word, FREE_ALL);
	return (command);
}

t_commands	*sh_ps_parser_commands(t_words	*head_word)
{
	t_commands	*head_command;
	t_commands	*command;

	if (head_word == NULL)
		return (NULL);
	command = get_next_command(&head_word);
	head_command = command;
	while (command != NULL)
	{
		command->next = get_next_command(&head_word);
		command = command->next;
	}
	return (head_command);
}

/*
static void	sh_ps_parser_commands_print_list(t_commands	*head_command)
{
	int				i;
	t_redirections	*redir;

	if (head_command == NULL)
	{
		printf("\n------empty command list!-------\n");		
		return ;
	}
	printf("\n------printing commands!-------\n");
	while (head_command != NULL)
	{
		printf("\n-------\n");
		printf("\ncommand_name = %s", head_command->cmd_name);
		printf("\ncommand_args = ");
		if (head_command->cmd_args != NULL)
		{
			i = 0;
			while (head_command->cmd_args[i] != NULL)
				printf("<%s>", head_command->cmd_args[i++]);
		}
		printf("\nredirs_in = ");
		redir = head_command->redirs_in;
		while (redir != NULL)
		{
			printf("%s ", redir->redir_file);
			redir = redir->next;
		}
		printf("\nredirs_out = ");
		redir = head_command->redirs_out;
		while (redir != NULL)
		{
			printf("%s ", redir->redir_file);
			redir = redir->next;
		}
		head_command = head_command->next;
	}
}
*/

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
	head_command = sh_ps_parser_commands(head_word);
	sh_ps_parser_commands_print_list(head_command);
	sh_ps_parser_commands_free_list(head_command);
	return (0);
}
*/
