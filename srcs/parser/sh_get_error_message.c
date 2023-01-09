/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ps_get_error_message.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:10:41 by jyao              #+#    #+#             */
/*   Updated: 2023/01/09 13:33:31 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*sh_get_error_msg(enum e_exit_codes exit_code)
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
	else if (exit_code == EXT_NO_CD_ERR)
		return ("NO SUCH DIRECTORY ERROR!\n");
	else if (exit_code == EXT_NOT_VALID_KEY_ERR)
		return ("NOT VALID KEY ERROR!\n");
	else if (exit_code == EXT_IN_FILE_ERR)
		return ("IN FILE ERROR!\n");
	else if (exit_code == EXT_OUT_FILE_ERR)
		return ("OUT FILE ERROR!\n");
	return (NULL);
}
