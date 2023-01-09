/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:31:30 by jyao              #+#    #+#             */
/*   Updated: 2023/01/10 00:20:19 by jyao             ###   ########.fr       */
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

typedef struct s_terminal	t_terminal;

void			sh_ex_displayarray(char **commands);
char			*sh_ps_convertvalue(t_shell_s *shell, char *arg);
void			sh_ps_echoall(t_shell_s *shell, char *arg);
void			sh_ex_hasflag(t_shell_s *shell);
char			*ft_charjoin(char const *s1, char c);
void			sh_ex_display(t_shell_s *shell);
void			sh_ex_wcmessage(void);
int				sh_ex_doublelen(char **str);
void			sh_ex_freeallin(char **str);
void			sh_ex_free_arr(char **str);
void			sh_ex_initshell(t_shell_s *shell, char **envp);
void			sh_ex_readline(t_shell_s *shell);
char			*sh_ex_cwd(void);
char			*sh_ex_createprompt(t_shell_s *shell);
int				count_words(const char *str, char c);
void			sh_ex_countcommand(t_shell_s *shell);
void			sh_ex_splitcommands(t_shell_s *shell);
int				sh_ex_delimeterfound(char c);
char			*word_dup(char *str, int start, int finish);
int				sh_ex_outdirfound(char c);
int				sh_ex_indirfound(char c);
int				sh_ex_pipefound(char c);
char			*sh_ex_finddollar(char *str);
char			*sh_ex_changekey(t_shell_s *shell);
void			sh_ex_addvalue(t_shell_s *shell, char *tmp_value);
void			sh_ex_addkey(t_shell_s *shell, char *tmp_key);
void			sh_ex_exitcode(void);
int				sh_ex_firstdelimeter(char *str);
void			sh_ex_checkinredirect(t_shell_s *shell, char *cmd);
void			sh_ex_checkoutredirect(t_shell_s *shell, char *cmd);
char			*sh_ps_removequote(char *str);
char			*sh_ps_trimspace(char *str);
void			sh_ex_execcmdall(t_shell_s *shell, t_commands *command);
int				is_str_quoted(char *str);
int				sh_ps_issinglequotedarg(char *str);
void			sh_ps_echoall(t_shell_s *shell, char *arg);
int				sh_ps_isvalidname(char c);
int				ft_chrfound(char *str, char c);
void			sh_ex_sighandle(int sig);
void			sh_ex_backslash(int sig);
void			sh_ex_cntrlc(int sig);
void			sh_ex_newprompt(int sig);
void			save_mode(void);
void			set_mode(void);
void			reset_mode(void);
void			sh_ex_redirectfile(t_shell_s *shell);
//******* sh_ex_echo.c*****************
void			sh_ex_displayecho(t_shell_s *shell, t_commands *command);
void			sh_ex_echoflag(t_shell_s *shell, t_commands *command);
int				sh_ex_echo(t_shell_s *shell, t_commands *command);
void			sh_ex_echoarray(t_commands *command);

//******* sh_ex_cd.c*******************

int				sh_ex_cd(t_shell_s *shell, t_commands *command);
void			sh_ex_changepwd(t_shell_s *shell);

//******* sh_ex_pwd.c *****************
char			*sh_ex_cwd(void);
int				sh_ex_showpwd(void);

//******** sh_ex_export.c *************
int				sh_ex_export(t_shell_s *shell, char **vars);

char			*sh_ex_searchenvvar(t_shell_s *shell, char *key);

//******** sh_ex_export_add.c *************
char			**sh_ex_realloc_str_arr(char **old_arr, size_t new_arr_size);
int				sh_ex_export_add_vars(t_shell_s *shell, char **vars);
int				sh_ex_find_key_index(t_var_s *vars, char *key);

//******** sh_ex_export_var.c *************
t_var_s			*sh_ex_dup_vars(t_var_s *vars);
t_var_s			*sh_ex_realloc_vars(t_var_s *old_vars, size_t new_vars_size);
int				sh_ex_is_valid_key(char *key);

//******** sh_ex_env.c ****************
int				sh_ex_view_env(t_shell_s *shell);

//******** sh_ex_envp_init.c ****************
void			sh_ex_envp_init(t_shell_s *shell, char **envp);
char			**sh_ex_get_envp_chain(t_shell_s *shell);

//******* sh_ex_unset.c ***************
int				sh_ex_unset(t_shell_s *shell, char **var_names);

//******** sh_ex_exit.c ***************
int				sh_ex_exit(t_shell_s *shell, t_commands *command, int flag);
int				sh_ex_exit_all(t_shell_s *shell, int flag);

//******* sh_ex_utils.c ***************
void			sh_ex_free_loop(t_shell_s *shell);

//******* sh_ex_bindir.c **************
char			*sh_ex_bindir(t_shell_s *shell, char *cmd);

//******** sh_ex_builtin.c ************
int				sh_ex_isbuiltin(t_commands *command);
int				sh_ex_builtin(t_shell_s *shell, t_commands *command);

//******** sh_ex_env_utils.c **********
void			sh_ex_envlen(t_shell_s *shell);
char			*sh_ex_searchenvvar(t_shell_s *shell, char *key);
void			sh_ex_memkeyval(t_shell_s *shell);
void			sh_ex_createenvp(t_shell_s *shell, char **envp);

//******** sh_ex_quote.c **************
int				sh_ps_issinglequote(char c);
int				sh_ps_isdoublequote(char c);
int				sh_ps_isescape(char c);
int				sh_ps_isquoted(char c);
char			*sh_ps_removequote(char *str);

//********* sh_ex_quote_utils.c ********
int				sh_ps_issinglequotedarg(char *str);
int				sh_ps_isvalidname(char c);
char			*sh_ps_trimspace(char *str);

//********* sh_ex_shellinit.c **********
void			init_shell(t_terminal *term);
void			save_mode(void);
void			set_mode(void);
void			reset_mode(void);

//********* sh_ex_signal.c *************
void			sh_ex_sighandle(int sig);

void			sh_ex_nl_sigint_handler(int sig);

void			sh_ex_killchild_handler(int sig);

//********* sh_ex_utils.c **************
void			sh_ex_wcmessage(void);

int				sh_ex_doublelen(char **str);

void			sh_ex_free_arr(char **str);

void			sh_ex_freeallin(char **str);

// void sh_ex_freeallvar(t_shell_s *shell, t_commands *command, t_words *words);

//********* extra.c ******************

void			sh_ex_display(t_shell_s *shell);

void			sh_ex_displayarray(char **commands);

char			*ft_charjoin(char const *s1, char c);

int				ft_chrfound(char *str, char c);

int				sh_ex_listlen(t_commands *command);

int				sh_ex_pipecount(t_commands *command);

int				sh_count(t_words *word);

char			*sh_ex_fileout(t_commands *command);

char			*sh_ex_filein(t_commands *command);

//**********sh_ex_executor.c ************
void			sh_ex_execcmd(t_shell_s *shell, t_commands *command);

//***********sh_ex_exec_utils.c**********
int				sh_ex_init_pipe_fork(t_shell_s *shell);

int				sh_ex_init_fork(t_shell_s *shell);

int				sh_ex_dup_pipe(\
t_shell_s *shell, t_commands *command, int *index_fd);

int				sh_ex_close_fd(t_shell_s *shell);

//********** sh_ex_exec_extra.c ***********
void			sh_ex_stdstatus(int status);
int				sh_ex_check_redirect(t_shell_s *shell, t_redirections *redir);
int				sh_ex_exec_cmd(t_shell_s *shell, t_commands *command);
int				sh_ex_exec(t_shell_s *shell);
void			sh_ex_testfork(t_shell_s *shell, t_commands *command);

//*********extra**************
void			sh_display(t_commands *command);
void			sh_dispred(t_redirections *redirs);
int				sh_ex_simplecmd(t_shell_s *shell, t_commands *command);
int				sh_ex_simplecmd_exec(t_shell_s *shell, t_commands *command);
int				sh_ex_valid_exec(t_shell_s *shell, t_commands *command);
void			sh_ex_free_all(t_shell_s *shell);

#endif