/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:14:02 by jyao              #+#    #+#             */
/*   Updated: 2022/12/28 13:32:29 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* right after lexer word chain call this
** function to mark variables to justword
*/
int	sh_ps_lexer_heredoc_mark_variable(t_words *head_word)
{
	t_words	*word;
	int		marker;

	if (head_word == NULL)
		return (0);
	marker = 0;
	word = head_word;
	while (word != NULL)
	{
		if (word->term_type == TT_APPND_IN)
			marker = 1;
		else if (marker == 1 \
		&& (word->term_type == TT_JUST_WORD || word->term_type == TT_VAR))
		{
			marker = 0;
			if (word->term_type == TT_VAR)
				word->term_type = TT_JUST_WORD;
		}
		word = word->next;
	}
	return (0);
}

/*when it's to add redirections, call this function for heredoc*/
/* when it's time to free the resources 
** remember to tell the execution to first open 
** (because there might have never been heredoc called)
** then unlink the file at the end!
*/
int	sh_ps_parser_heredoc(t_redirections *redirection)
{
	char		*str_stdin;
	const char	*delim;
	int			fd;

	if (redirection == NULL || redirection->redir_term_type != TT_APPND_IN)
		return (-1);
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < -1)
		return (\
		perror("CAN'T CREATE FILE: " HEREDOC_FILE " FOR HEREDOC!\n"), -1);
	delim = redirection->redir_file;
	while (1)
	{
		str_stdin = readline("> ");
		if (ft_strcmp(str_stdin, delim) == 0)
		{
			free(str_stdin);
			break ;
		}
		write(fd, str_stdin, ft_strlen(str_stdin));
		write(fd, "\n", 1);
		free(str_stdin);
	}
	close(fd);
	return (0);
}
