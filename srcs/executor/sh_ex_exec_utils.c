/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:05:00 by marvin            #+#    #+#             */
/*   Updated: 2022/12/26 18:05:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int sh_ex_init_pipe_fork(t_shell_s *shell)
{

    int i = 0;
    shell->pid = malloc(sizeof(int) * (shell->num_commands + 1));
    shell->fd = malloc(sizeof(int) * (shell->num_commands * 2));
    if (shell->pid == NULL || shell->fd == NULL)
        return (free(shell->pid), free(shell->fd), 1);
    while (i < shell->num_commands)
    {
        if (pipe(shell->fd + i * 2) < 0)
            return (1);
        i++;
    }
    return (0);
}

// initialize the fork

int sh_ex_init_fork(t_shell_s *shell, t_commands *command)
{
    int i;
    int index_fd;
     t_commands *cmd;

      cmd = command;

    i = 0;
    index_fd = 0;
    shell->num_commands--;
    if (sh_ex_init_pipe_fork(shell))
        return (1);
    while (cmd)
    {
        shell->pid[i] = fork();
        if (shell->pid[i] == -1)
            return (1);
        else if (shell->pid[i] == 0)
            sh_ex_dup_pipe(shell, cmd, &index_fd);
        cmd = cmd->next;
        index_fd += 2;
        sh_ex_stdstatus(0);
        i++;
    }
    return (sh_ex_close_fd(shell));
}
// use dup to duplicate the read and write end of the pipe

int sh_ex_dup_pipe(t_shell_s *shell, t_commands *command, int *index_fd)
{
    int i = 0;

    if (command->next)
    {
        if (dup2(shell->fd[*index_fd + 1], STDOUT_FILENO) < 0)
            return (1);
    }
    if (*index_fd != 0)
    {
        if (dup2(shell->fd[*index_fd - 2], STDIN_FILENO) < 0)
            return (1);
    }
    if (command->redirs != NULL)
    {
        if (sh_ex_check_redirect(shell, command->redirs))
            return (1);
    }   
    while (i < (shell->num_commands * 2))
        close(shell->fd[i++]);
    // sh_ex_exitstatus = sh_ex_exec_cmd(shell, command);
    sh_ex_exitstatus = sh_ex_simplecmd_exec(shell, command);
    return (sh_ex_exitstatus);
}

int sh_ex_close_fd(t_shell_s *shell)
{
    int i = 0;

    while (i < (shell->num_commands * 2))
        close(shell->fd[i++]);
    i = 0;
    while (i < (shell->num_commands + 1))
    {
        waitpid(shell->pid[i], &sh_ex_exitstatus, 0);
        // if (WIFEXITED(sh_ex_exitstatus))
        sh_ex_exitstatus = WEXITSTATUS(sh_ex_exitstatus);
        i++;
    }
    free(shell->fd);
    free(shell->pid);
    return (sh_ex_exitstatus);
}
