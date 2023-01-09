/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_get_error_message.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:10:41 by jyao              #+#    #+#             */
/*   Updated: 2023/01/09 18:46:00 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_get_error_msg(enum e_exit_codes exit_code)
{
	if (exit_code == EXT_MALLOC_FAILURE)
		return ("MALLOC CAN'T MALLOC ERROR!\n");
	else if (exit_code == EXT_HEREDOC_ERR)
		return ("CAN'T CREATE " HEREDOC_FILE " FILE FOR HEREDOC ERROR!\n");
	else if (exit_code == EXT_QUOTES_ERR)
		return ("UNCLOSED QUOTES SYNTAX ERROR!\n");
	else if (exit_code == EXT_REDIR_ERR)
		return ("REDIRECTION SYNTAX ERROR!\n");
	else if (exit_code == EXT_PIPE_ERR)
		return ("PIPE SYNTAX ERROR!\n");
	else if (exit_code == EXT_SYNTAX_ERR)
		return ("SYNTAX ERROR!\n");
	else if (exit_code == EXT_CMD_NOT_FOUND_ERR)
		return ("COMMAND NOT FOUND ERROR!\n");
	else if (exit_code == EXT_CANT_FORK_ERR)
		return ("CAN'T FORK ERROR!\n");
	else if (exit_code == EXT_CD_ERR)
		return ("CD ERROR!\n");
	else if (exit_code == EXT_NOT_VALID_KEY_ERR)
		return ("NOT VALID KEY ERROR!\n");
	else if (exit_code == EXT_IN_FILE_ERR)
		return ("IN FILE ERROR!\n");
	else if (exit_code == EXT_OUT_FILE_ERR)
		return ("OUT FILE ERROR!\n");
	return (NULL);
}
