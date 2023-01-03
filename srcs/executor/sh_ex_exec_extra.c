/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_exec_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:02:20 by marvin            #+#    #+#             */
/*   Updated: 2022/12/27 09:02:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// duplicate stdin and stdout so to restore them after using

void sh_ex_stdstatus(int status)
{
    static int fdin;
    static int fdout;

    if (status)
    {

        fdin = dup(STDIN_FILENO);
        fdout = dup(STDOUT_FILENO);
    }
    else if (!status)
    {
        dup2(fdin, STDIN_FILENO);
        dup2(fdout, STDOUT_FILENO);
    }
}
int sh_ex_valid_exec(t_shell_s *shell, t_commands *command)
{
    char *file_name;

    file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
    if (file_name == NULL)
    {
        printf("commnad not found: %s\n", command->cmd_argv[0]);
        return (127);
    }
    return (0);
}

int sh_ex_exec_cmd(t_shell_s *shell, t_commands *command)
{
    char *file_name;

    file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
    if (file_name == NULL)
    {
        printf("commnad not found: %s\n", command->cmd_argv[0]);
        return (127);
    }
    else
    {
        if (execve(file_name, command->cmd_argv, shell->envp.envp) == -1)
        {
            sh_ex_exitstatus = 127;
            exit(EXIT_FAILURE);
        }
    }
    return (0);
}

int sh_ex_simplecmd(t_shell_s *shell, t_commands *command)
{
    int fid;

    if (command->cmd_argv == NULL)
        return (0);
    if (sh_ex_isbuiltin(command))
        sh_ex_exitstatus = sh_ex_builtin(shell, command);
    else if (!sh_ex_valid_exec(shell, command))
    {
        fid = fork();
        if (fid == -1)
            return (1);
        if (fid == 0)
            sh_ex_exec_cmd(shell, command);
        else
        {
            waitpid(fid, &sh_ex_exitstatus, 0);
            if (WIFEXITED(sh_ex_exitstatus))
                sh_ex_exitstatus = WEXITSTATUS(sh_ex_exitstatus);
        }
        return (0);
    }
     else
        sh_ex_exitstatus = 1;
    return (sh_ex_exitstatus);
}

int sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command)
{
    // printf("isbuiltin val = %d\n", sh_ex_isbuiltin(command));
    // printf("shell num cmd val = %d\n", shell->num_commands);
    if (sh_ex_isbuiltin(command) && shell->num_commands >= 1)
    {
        // printf("I AM BUILTIN\n");
        sh_ex_exitstatus = sh_ex_builtin(shell, command);
        exit(sh_ex_exitstatus);
    }
    else
    {
        // printf("I AM EXTERNAL\n");
        sh_ex_exitstatus =  sh_ex_exec_cmd(shell, command);
    }
    return (sh_ex_exitstatus);
}

int sh_ex_exec(t_shell_s *shell, t_commands *command)
{
    // shell->red_fd[0] = 0;
    // shell->red_fd[1] = 0;
    shell->num_commands = sh_ex_listlen(command);

    // duplicate stdin and stdout using dup
    sh_ex_stdstatus(1);
    // check if there is a redirection
/*     if (redir != NULL)
    {
        if (sh_ex_check_redirect(shell, redir))
        {
            // if there is no redirection fd will be default std in and out
            // duplicat it so it will not affect the main shell
            // printf("hey 1\n");
            sh_ex_stdstatus(0);
            return (1);
        }
    } */
    // printf("hey 2\n");
    if (command == NULL && command->redirs == NULL)
        return (1);
    // printf("hey 3\n");
    // printf("num commands = %d\n", shell->num_commands);
    if (shell->num_commands > 1)
        sh_ex_exitstatus = sh_ex_init_fork(shell, command);
    else if (command->next == NULL)
        sh_ex_simplecmd(shell, command); 
    sh_ex_stdstatus(0);
    return (sh_ex_exitstatus);
}
