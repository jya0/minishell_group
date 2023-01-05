/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:33:05 by jyao              #+#    #+#             */
/*   Updated: 2023/01/05 22:51:24 by jyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

// struct for the environment variables

// struct termios new_term, old_term;
int				sh_ex_exitstatus;
struct termios old_term, new_term;

typedef struct	t_var_s {
	char	*key;
	char	*val;
}	t_var_s;

typedef struct	t_env_s	{
	char		**envp_chain;
	size_t		env_size;
	// char		**key_chain;
	// char		**val_chain;
	t_var_s		*vars;
}	t_env_s;

typedef struct t_cmd
{
    int *fd;
    int *pid;
} t_cmd;

// struct for the command variables

typedef struct t_shell_s
{
    char *echo_print; //
    int *fd;
    int *pid;
    int red_fd[2];
    int i;

    char *echovar; // echo argument conveted
    int echoflag;
    char line;       // check command in the execution
    char error_file; //
    char **tokens;
    char *file_name; // executable file

    int flag;              // to represent the delimeter
    int char_count;        // number of characters
    char *outdir_filename; // file name for out redirect
    char *outapp_filename; // file used for truncate for >>
    char *indir_filename;  // file name for in redirect
    char *herdoc;          // for <<
    int cmdindex;          // index of the commands
    int num_commands;      // number of all commands
    int num_pipes;         // number of all pipes
    int fdin;              // file descriptor for redirect in file
    int fdout;             // file descriptor for redirect out file
    int dbl_infile;        // to check if there is <<
    int dbl_outfile;       // to chec if there is >>
    char *cmd_line;        // read the command line
    char **commands;       // simple commands
    char *cwd;             // displays the current working directory
    char *home;            //  a path for a home directory
    char **path;           // a path for the list of path direcotories separeted by ':'
    struct t_env_s envp;
} t_shell_s;

typedef struct t_context
{
    int fd[2];
    int fd_close;
} t_context;
# include "../libft/libft.h"
# include "./sh_parser.h"
# include "./sh_executor.h"

#endif
