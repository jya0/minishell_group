/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ex_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 08:05:25 by yoyohann          #+#    #+#             */
/*   Updated: 2022/12/26 11:04:16 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    sh_ex_execcmd(t_shell_s *shell, t_commands *command)
{
    // sh_ex_countcommand(shell);
    // sh_ex_redirectfile(shell);


    char *file;
    char **path;
    file = NULL;
    int tmpin = dup(0);
    int tmpout = dup(1);


    int fdin;

    if (shell->indir_filename)
        fdin = open(shell->indir_filename, O_RDONLY);
    else
        fdin = dup(tmpin);

    int ret;
    int fdout;

    int len = sh_ps_listlen(command);
     int i = 0;
    while (command)
//    for (int i = 0; i < len; i++)
    {
        dup2(fdin, 0);
        close(fdin);

/*         if (i == len - 1)
        {
            if (shell->outdir_filename || shell->outapp_filename)
            {
                if (shell->outdir_filename)
                    fdout = open(shell->outdir_filename, O_WRONLY | O_TRUNC, 0777);
                else
                    fdout = open(shell->outapp_filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
            }
            else
                fdout = dup(tmpout);
        }
        else */
        {
        int fd[2];
        pipe(fd);
        fdout = fd[1];
        fdin = fd[0];
        }
        dup2(fdout, 1);
        close(fdout);

        ret = fork();
        if (ret == 0)
        {
            file = sh_ex_bindir(shell, command->cmd_argv[0]);
            if (file == NULL)
                printf("commnad not found: %s\n", command->cmd_argv[0]);
            else
            {
                if (execve(file, command->cmd_argv, shell->envp.envp) == -1)
                {
                    // update exit_status
                    exit(EXIT_FAILURE);
                }
            }
            return;

        }
        command = command->next;
    }
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    waitpid(ret, &sh_ex_exitstatus, 0);
    if (WIFEXITED(sh_ex_exitstatus))
        sh_ex_exitstatus = WEXITSTATUS(sh_ex_exitstatus);
    return;
}
