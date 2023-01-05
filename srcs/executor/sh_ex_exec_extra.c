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
        // perror("error oh oh!\n");
        // errno = 127;
        // free(file_name);
        // perror("fake enoent error!\n");
        return (127);
    }
    free(file_name);
    return (0);
}

int sh_ex_exec_cmd(t_shell_s *shell, t_commands *command)
{
    char *file_name;

    file_name = sh_ex_bindir(shell, command->cmd_argv[0]);
    if (file_name == NULL)
    {
        printf("commnad not found: %s\n", command->cmd_argv[0]);
        free(file_name);
        return (127);
    }
    else
    {
        if (execve(file_name, command->cmd_argv, (char **)shell->envp.envp_chain) == -1)
        {
            sh_ex_exitstatus = 127;
            free(file_name);
            exit(EXIT_FAILURE);
        }
    }

    free(file_name);
    return (0);
}

int sh_ex_simplecmd(t_shell_s *shell, t_commands *command)
{
    int fid;

    if (command->redirs != NULL)
    {
        if (sh_ex_check_redirect(shell, command->redirs))
            return (1);
    }  
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
    if (sh_ex_isbuiltin(command))
    {
        // printf("I AM BUILTIN\n");
        sh_ex_exitstatus = sh_ex_builtin(shell, command);
        sh_ex_exit(shell, command, 0);
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
    shell->num_commands = sh_ex_listlen(command);

    // duplicate stdin and stdout using dup
    sh_ex_stdstatus(1);
    if (command == NULL && command->redirs == NULL)
        return (1);
    if (shell->num_commands > 1)
        sh_ex_exitstatus = sh_ex_init_fork(shell, command);
    else
        sh_ex_simplecmd(shell, command);
    sh_ex_stdstatus(0);
    return (sh_ex_exitstatus);
}
