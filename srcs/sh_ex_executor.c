#include "../includes/sh_executor.h"


void sh_ex_checkinredirect(t_shell_s *shell, char *cmd)
{
    int i;
    
    shell->infile = STDIN_FILENO; 
    shell->dbl_infile = 0;
    shell->indir_filename = NULL;
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '<')
        {
            if (cmd[i + 1] == '<')
            {
                shell->dbl_infile = 1;
                shell->indir_filename = cmd;
                break;
            }
                shell->infile = 1;
                shell->indir_filename = cmd;

        }
        i++;
    } 
}

void sh_ex_checkoutredirect(t_shell_s *shell, char *cmd)
{
    int i;

    shell->outfile = STDOUT_FILENO;
    shell->dbl_outfile = 0;
    shell->outdir_filename = NULL;
    i = 0;
    while (shell->cmd_line[i])
    {
        if (shell->cmd_line[i] == '>')
        {
            if (shell->cmd_line[i + 1] == '>')
            {
                shell->dbl_outfile = 1;
                shell->outdir_filename = cmd; 
                break ;
            }
            shell->outfile = 1;
            shell->outdir_filename = cmd; 
        }
        i++;
    } 
}

void sh_ex_inredirect(t_shell_s *shell)
{
	int i;
	char **cmd;
	
	i = 0;
    cmd = ft_split(shell->cmd_line, ' ');
	while (cmd[i])
	{
		sh_ex_checkinredirect(shell, cmd[i]);
		sh_ex_checkoutredirect(shell, cmd[i]);
		i++;
	}
}

void sh_ex_execute_piped(t_shell_s *shell)
{
    int tmpin = dup(0);
    int tmpout = dup(1);
    char **file_path = NULL;

    int fdin;
    int i;
	int len;
	char *infile;
	char *outfile;

	// check if there is a file redirection and
	// assign the values
	sh_ex_countcommand(shell);
	sh_ex_inredirect(shell);

    infile = shell->indir_filename; 
    outfile = shell->outdir_filename;
	len = shell->num_commands;

    if (infile)
        fdin = open(infile, O_RDONLY);
    else
        fdin = dup(tmpin);
    
    int ret;
    int fdout;

    for (i = 0; i < len ; i++)
    {
        dup2(fdin, 0);
        close(fdin);
        if (i == len - 1)
        {
            if (outfile)
                fdout = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
            else
                fdout = dup(tmpout);
        }
        else
        {
            int fdpipe[2];
            pipe(fdpipe);
            fdout = fdpipe[1];
            fdin = fdpipe[0];
        }
        dup2(fdout, 1);
        close(fdout);

        ret = fork();
        if (ret == 0)
        {
            file_path = ft_split(shell->commands[i], ' ');
            execvp(file_path[0], file_path);
            exit(1);
        }
    }
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    waitpid(ret, NULL, 0);

} 

/* int main()
{
	t_shell_s shell;
    sh_ex_execute_piped(&shell);
    return (0);
} */

/* void sh_ex_execcmd(t_shell_s *shell)
{
    int fid;
    int i;
    char **run_cmd;
    char *file;

    fid = fork();
    if (fid == -1)
        // update exit_status 
        return ;
    if (fid == 0)
    {
        i = 0;
        while (i < shell->num_commands)
        {
            run_cmd = ft_split(shell->commands[i], ' ');
            if ((file = sh_ex_bindir(shell, run_cmd[0])) != NULL)
            {
                if (execve(file, run_cmd, shell->envp.envp) == -1)
                {
                    // update exit_status
                    exit(EXIT_FAILURE);
                }
            }
            i++;
        }
    }
    else
    {
        int status;
        
        waitpid(fid, &status, 0);
        if (WIFEXITED(status))
            sh_ex_exitstatus = WEXITSTATUS(status);
    }
}
 */

void sh_ex_redirectfile(t_shell_s *shell)
{
    int i;
    char *tmpstr;
    char *tmpstr1;
    int j;

    shell->outdir_filename = NULL;
    shell->outapp_filename = NULL;
    i = 0;
    while (shell->cmd_line[i])
    {
        if (sh_ex_outdirfound(shell->cmd_line[i]))
        {
            i++;
            if (sh_ex_outdirfound(shell->cmd_line[i]))
            {
                i++;
                j = sh_ex_firstdelimeter(&shell->cmd_line[i]);
                tmpstr = word_dup(shell->cmd_line, i, j + i);
                shell->outapp_filename = sh_ps_trimspace(tmpstr);
                return ;
            }
            j = sh_ex_firstdelimeter(&shell->cmd_line[i]);
            tmpstr = word_dup(shell->cmd_line, i, j + i);
            shell->outdir_filename = sh_ps_trimspace(tmpstr);
            return ;
        }
        i++;
    }
}

void sh_ex_indirectfile(t_shell_s *shell)
{
    int i;
    char *tmpstr;
    int j;

    i = 0;
    shell->indir_filename = NULL;
    while (shell->cmd_line[i])
    {
        if (sh_ex_indirfound(shell->cmd_line[i]))
        {
            i++;
            break;
        }
        i++;
    }
    if (i < shell->char_count && i != 0)
    {
        j = sh_ex_firstdelimeter(&shell->cmd_line[i]);
        tmpstr = word_dup(shell->cmd_line, i , j + i);
        shell->indir_filename = sh_ps_trimspace(tmpstr);
    }
} 

void sh_ex_execcmd(t_shell_s *shell)
{
    sh_ex_countcommand(shell);
    sh_ex_redirectfile(shell);
//    sh_ex_indirectfile(shell);
 
    char *file;
    char **path;
    int tmpin = dup(0);
    int tmpout = dup(1);

    int fdin;

    if (shell->indir_filename)
        fdin = open(shell->indir_filename, O_RDONLY);
    else
        fdin = dup(tmpin);

     int ret;
     int fdout;

    if (shell->outdir_filename || shell->outapp_filename)
          shell->num_commands--;
     for (int i = 0; i < shell->num_commands; i++)
     {
         dup2(fdin, 0);
         close(fdin);

        if (i == shell->num_commands - 1)
         {
            if (shell->outdir_filename || shell->outapp_filename)
            {
                if (shell->outdir_filename)
                    fdout = open(shell->outdir_filename, O_WRONLY | O_TRUNC, 0777);
                else
                    fdout = open(shell->outapp_filename,O_WRONLY | O_CREAT | O_APPEND , 0777);
            }    
            else
                fdout = dup(tmpout);
         }
         else
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

            path = ft_split(shell->commands[i], ' ');
            if ((file = sh_ex_bindir(shell, path[0])) != NULL)
            {
                if (execve(file, path, shell->envp.envp) == -1)
                {
                    // update exit_status
                    exit(EXIT_FAILURE);
                }
            }
            return ;
            // path = ft_split(shell->commands[i], ' ');
            // if (execvp(path[0], path) == -1)
            //     return ;
         }
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

 void sh_ex_executeall(t_shell_s *shell)
{
    int i;
    int fd[2];
    
    shell->cmdindex = 0;
// create pipe for piped commands
    while (i < shell->num_pipes)
    {
        if (pipe(fd) == -1)
        {
            sh_ex_exitstatus = 127;
            printf("pipe error\n");
        }
        shell->outfile = fd[1];
        sh_ex_executetoken(shell);
    // call execution function
        close(shell->outfile);
        if (shell->infile != 0)
            close(shell->infile);
        shell->infile =  fd[0];
 
        close(shell->infile);
        i++;
    }
    // call execution function
    sh_ex_executetoken(shell);

}

void sh_ex_executetoken(t_shell_s *shell)
{
    // check if there is redirection
    sh_ex_checkredirect(shell);
    if (shell->commands[0][0] != '>')
    {
        // check for the commands which are not redirect
        // split the command to tokens for execution
        // create tokens from the commnad
        if (shell->tokens[0])
        {
            // it the first token is true check if it is builtin
            sh_ex_isbuiltin(shell->tokens[0]);
        }
        // check if the infile is true
        if (shell->infile != -1)
            sh_ex_executeprocess(shell, shell->infile, shell->outfile);

        // free for tokens
    }
    if (shell->file_name)
        unlink(shell->file_name);
} 

void sh_ex_checkredirect(t_shell_s *shell)
{
    // check where is this is used not clear
     shell->line = ft_strdup(shell->commands[shell->cmdindex]);

    // increment cmdindex if the number of command is greater than 1
    if (shell->num_commands > 1)
        shell->cmdindex++;
    // for which file?    
    shell->error_file = NULL;
    while (shell->commands[shell->cmdindex] && shell->commands[shell->cmdindex][0] != '|')
    {
        // call the out redirect function with the index of the commnad
        sh_ex_outredirect(shell, shell->cmdindex);

        // call the in redirect function with the index of the command
        sh_ex_inredirect(shell, shell->cmdindex);
        shell->cmdindex++;
    }
    if (shell->error_file != NULL)
    {
        sh_ex_exitstatus = 1;
        printf("minishell: %s", shell->error_file);
    }
}