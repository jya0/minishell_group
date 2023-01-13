/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:31:30 by jyao              #+#    #+#             */
/*   Updated: 2023/01/13 18:00:56 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXECUTOR_H
# define SH_EXECUTOR_H

# define GREY "\033[1;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# include "../libft/libft.h"

typedef struct t_var_s		t_var_s;

//******** main.c *************

void			sh_ex_initshell(t_shell_s *shell, char **envp);

int				main(int argc, char **argv, char **envp);

//******* sh_ex_bindir.c **************

char			*sh_ex_bindir(t_shell_s *shell, char *cmd);

//******** sh_ex_builtin.c ************

int				sh_ex_isbuiltin(t_commands *command);

int				sh_ex_builtin(t_shell_s *shell, t_commands *command);

//******* sh_ex_cd.c*******************

int				sh_ex_cd(t_shell_s *shell, t_commands *command);

//******* sh_ex_echo.c*****************
int				sh_ex_echo(t_shell_s *shell, t_commands *command);

//******* sh_ex_env.c*****************

int				sh_ex_view_env(t_shell_s *shell);

int				sh_ex_listlen(t_commands *command);

//******** sh_ex_envp_init.c ****************

void			sh_ex_envp_init(t_shell_s *shell, char **envp);

char			**sh_ex_get_envp_chain(t_shell_s *shell);

//******** sh_ex_exec_cmd.c *************

int				sh_ex_get_exit_code(int status);

int				sh_ex_simplecmd(t_shell_s *shell, t_commands *command);

int				sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command);

int				sh_ex_exec(t_shell_s *shell);

//********** sh_ex_exec_extra.c ***********

void			sh_ex_stdstatus(int status);

int				sh_ex_valid_exec(t_shell_s *shell, t_commands *command);

int				sh_ex_exec_cmd(t_shell_s *shell, t_commands *command);

//***********sh_ex_exec_utils.c**********

int				sh_ex_init_pipe_fork(t_shell_s *shell);

int				sh_ex_init_fork(t_shell_s *shell);

int				sh_ex_dup_pipe(\
t_shell_s *shell, t_commands *command, int *index_fd);

int				sh_ex_close_fd(t_shell_s *shell);
void			free_fd_pid(t_shell_s **shell);

//******** sh_ex_exit.c ***************

int				sh_ex_exit_all(t_shell_s *shell, int flag);

int				sh_ex_exit(t_shell_s *shell, t_commands *command, int flag);

//******** sh_ex_export_add.c *************

int				sh_ex_export_add_vars(t_shell_s *shell, char **vars);

int				sh_ex_find_key_index(t_var_s *vars, char *key);

//******** sh_ex_export_var.c *************

t_var_s			*sh_ex_realloc_vars(t_var_s *old_vars, size_t new_vars_size);

t_var_s			*sh_ex_dup_vars(t_var_s *vars);

int				sh_ex_is_valid_key(char *key);

//******** sh_ex_export.c *************

char			*sh_ex_searchenvvar(t_shell_s *shell, char *key);

int				sh_ex_export(t_shell_s *shell, char **vars);

//******* sh_ex_pwd.c *****************

char			*sh_ex_cwd(void);

int				sh_ex_showpwd(void);

//******* sh_ex_redirect.c *****************

int				sh_ex_check_redirect(t_shell_s *shell, t_redirections *redir);

//********* sh_ex_signal.c *************

void			sh_ex_child_handler(int sig);

void			sh_ex_sighandle(int sig);

//********* sh_ex_unset.c *************

int				sh_ex_unset(t_shell_s *shell, char **var_names);

//********* sh_ex_utils.c **************

int				sh_ex_doublelen(char **str);

void			sh_ex_free_arr(char **str);

void			sh_ex_free_loop(t_shell_s *shell);

void			sh_ex_free_vars(t_var_s *vars);

void			sh_ex_free_all(t_shell_s *shell);

#endif