/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:33:05 by jyao              #+#    #+#             */
/*   Updated: 2023/01/18 22:47:55 by jyao             ###   ########.fr       */
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
# include <limits.h>
# include <sys/stat.h>

# include "../libft/libft.h"
# include "./sh_parser.h"
# include "./sh_executor.h"

// struct for the environment variables
typedef struct s_commands	t_commands;

// struct termios new_term, old_term;

typedef struct t_var_s {
	char	*key;
	char	*val;
}	t_var_s;

typedef struct t_env_s {
	char		**envp_chain;
	size_t		env_size;
	t_var_s		*vars;
}	t_env_s;

typedef struct t_cmd {
	int	*fd;
	int	*pid;
}	t_cmd;

// struct for the command variables

typedef struct s_exit_info {
	int				if_pid_fork;
	int				exit_code;
}	t_exit_info;

//******* struct for terminal
typedef struct s_terminal {
	pid_t				shell_pgid;
	struct termios		shell_tmodes;
	struct termios		old_term;
	struct termios		new_term;
	int					shell_terminal;
	int					shell_is_interactive;
}	t_terminal;

typedef struct t_shell_s
{
	int				*fd;
	int				*pid;
	int				red_fd[2];
	char			line;
	char			error_file;
	char			*file_name;
	int				echoflag;
	int				num_commands;
	int				num_pipes;
	int				fdin;
	int				fdout;
	char			*cmd_line;
	t_commands		*head_command;
	t_exit_info		exit_info;
	t_terminal		mini_terminal;
	struct t_env_s	envp;
}	t_shell_s;

t_shell_s					g_shell;

#endif
