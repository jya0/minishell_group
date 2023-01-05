/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:54:47 by marvin            #+#    #+#             */
/*   Updated: 2023/01/01 14:54:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int redir_stdout(t_redirections *redir, int *fd)
{
    if (redir->redir_term_type == TT_REDIR_OUT)
        *fd = open(redir->redir_file, \
        O_WRONLY | O_CREAT | O_TRUNC, 0777);
    else if (redir->redir_term_type == TT_APPND_OUT)
        *fd = open(redir->redir_file, \
        O_WRONLY | O_CREAT | O_APPEND, 0777);
    // printf("pass 1\n");
    if ((*fd) == -1)
        return (1);
    // printf("pass 2\n");
    dup2((*fd), STDOUT_FILENO);
    // ft_putstr_fd("pass 3\n", 1);
    close((*fd));
    // printf("pass 4\n");
    return (0);
}

static int redir_stdin(t_redirections *redir, int *fd)
{
    if (redir->redir_term_type == TT_REDIR_IN)
        *fd = open(redir->redir_file, O_RDONLY);
    else if (redir->redir_term_type == TT_APPND_IN)
        *fd = open(HEREDOC_FILE, O_RDONLY);
    if ((*fd) == -1)
        return (1);
    dup2((*fd), STDIN_FILENO);
    close((*fd));
    return (0);
}

int sh_ex_check_redirect(t_shell_s *shell, t_redirections *redir)
{

    while (redir != NULL)
    {
        if (redir->redir_term_type == TT_REDIR_OUT \
        || redir->redir_term_type == TT_APPND_OUT)
        {
            if (redir_stdout(redir, &shell->red_fd[1]))
                return (1);
        }
        else if (redir->redir_term_type == TT_REDIR_IN \
        || redir->redir_term_type == TT_APPND_IN)
        {
            if (redir_stdin(redir, &shell->red_fd[0]))
                return (1);
        }
        redir = redir->next;
        // printf("hello\n");
    }
    return (0);
}
