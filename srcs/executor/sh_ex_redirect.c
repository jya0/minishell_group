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

int sh_ex_check_redirect(t_shell_s *shell, t_redirections *redir)
{

    while (redir != NULL)
    {
        if (redir->redir_term_type == TT_REDIR_OUT)
        {
            if (sh_ex_redir_out(redir, &shell->red_fd[1]))
                return (1);
        }
        else if (redir->redir_term_type == TT_APPND_OUT)
        {
            if (sh_ex_redir_out_app(redir, &shell->red_fd[1]))
                return (1);
        }
        else if (redir->redir_term_type == TT_REDIR_IN)
        {
            if (sh_ex_redir_in(redir, &shell->red_fd[0]))
                return (1);
        }
        redir = redir->next;
        // printf("hello\n");
    }
    return (0);
}

int sh_ex_redir_out(t_redirections *redir, int *fd)
{
    *fd = open(redir->redir_file, O_RDWR | O_CREAT | O_TRUNC, 0777);
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

int sh_ex_redir_out_app(t_redirections *redir, int *fd)
{
    *fd = open(redir->redir_file, O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0777);
    if ((*fd) == -1)
        return (1);
    dup2((*fd), STDOUT_FILENO);
    close((*fd));
    return (0);
}

int sh_ex_redir_in(t_redirections *redir, int *fd)
{
    *fd = open(redir->redir_file, O_RDONLY);
    if ((*fd) == -1)
        return (1);
    dup2((*fd), STDIN_FILENO);
    close((*fd));
    return (0);
}