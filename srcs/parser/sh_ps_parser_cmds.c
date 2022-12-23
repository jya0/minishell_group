/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_parser_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:18:27 by jyao              #+#    #+#             */
/*   Updated: 2022/12/23 15:05:05 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	run_cmds_getter(\
t_commands *command, t_words **head_word, t_words **word)
{
	if (*((*word)->str) == '<' || *((*word)->str) == '>')
	{
		if (sh_ps_parser_get_redirs(command, head_word, word) < 0)
			return (printf("ERROR REDIRECTION!\n"));
	}
	else if (command->cmd_name == NULL && (*word)->term_type == TT_JUST_WORD)
	{
		if (sh_ps_parser_get_cmd_name(command, head_word, word) < 0)
			return (printf("ERROR CMD NAME!\n"));
	}
	else if (command->cmd_name != NULL && (*word)->term_type == TT_JUST_WORD)
	{
		if (sh_ps_parser_get_cmd_args(command, head_word, word) < 0)
			return (printf("ERROR CMD ARGS!\n"));
	}
	else
		sh_ps_lexer_word_del_word(head_word, *word, FREE_ALL);
	*word = *head_word;
	return (0);
}

static t_commands	*get_next_command(t_words **head_word)
{
	t_commands	*command;
	t_words		*word;

	if (head_word == NULL || *head_word == NULL)
		return (NULL);
	command = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (command == NULL)
		return (NULL);
	word = *head_word;
	while (word != NULL && word->term_type != TT_PIPE)
	{
		if (run_cmds_getter(command, head_word, &word) != 0)
		{
			sh_ps_lexer_word_free_list(*head_word);
			sh_ps_parser_commands_free(command, FREE_ALL);
			return (NULL);
		}
		word = *head_word;
	}
	if (word != NULL && word->term_type == TT_PIPE \
	&& word->prev == NULL)
	{
		printf("ERROR PIPE!\n");
	}
	sh_ps_lexer_word_print_list(*head_word);
	sh_ps_lexer_word_del_word(head_word, word, FREE_ALL);
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

/*
** check where the executable file is in the bin path
** and return it if found 
char *sh_ex_bindir(t_shell_s *shell, char *cmd)
{
    int i;
    char *realpath;

    i = 0;
    while (shell->path[i])
    {
        realpath = malloc(sizeof(char) * (ft_strlen(shell->path[i] + ft_strlen(cmd) + 1)));
        if (!realpath)
            return (NULL);
        realpath = ft_strjoin(shell->path[i], cmd);
        // check if the file is found in the directory if found 
        // return it
        if (access(realpath, F_OK) == 0)
            return (realpath);
        i++;
    }
    free(realpath);
    return (NULL);
}
*/
