/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_error_message.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:10:41 by jyao              #+#    #+#             */
/*   Updated: 2023/01/20 08:05:34 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_error_parser(enum e_exit_codes exit_code)
{
	if (exit_code == EXT_QUOTES_ERR)
		return ("UNCLOSED QUOTES SYNTAX ERROR!\n");
	else if (exit_code == EXT_REDIR_ERR)
		return ("REDIRECTION SYNTAX ERROR!\n");
	else if (exit_code == EXT_PIPE_ERR)
		return ("PIPE SYNTAX ERROR!\n");
	else if (exit_code == EXT_SYNTAX_ERR)
		return ("SYNTAX ERROR!\n");
	return (NULL);
}

static char	*get_error_exec(enum e_exit_codes exit_code)
{
	if (exit_code == EXT_MALLOC_FAILURE)
		return ("MALLOC CAN'T MALLOC ERROR!\n");
	else if (exit_code == EXT_HEREDOC_ERR)
		return ("CAN'T CREATE " HEREDOC_FILE " FILE FOR HEREDOC ERROR!\n");
	else if (exit_code == EXT_CMD_NOT_FOUND_ERR)
		return (" command not found\n");
	else if (exit_code == EXT_CANT_FORK_ERR)
		return ("CAN'T FORK ERROR!\n");
	else if (exit_code == EXT_IN_FILE_ERR)
		return ("IN FILE ERROR!\n");
	else if (exit_code == EXT_OUT_FILE_ERR)
		return ("OUT FILE ERROR!\n");
	else if (exit_code == EXT_NOT_DIRECTORY)
		return ("NOT DIRECTORY ERROR!\n");
	else if (exit_code == EXT_EISDIR)
		return ("is DIRECTORY ERROR!\n");
	return (NULL);
}

char	*sh_get_error_msg(enum e_exit_codes exit_code)
{
	char	*error_msg;

	if (exit_code == 0)
		return ("");
	error_msg = get_error_parser(exit_code);
	if (error_msg != NULL)
		return (error_msg);
	error_msg = get_error_exec(exit_code);
	if (error_msg != NULL)
		return (error_msg);
	return ("");
}
