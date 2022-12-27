#ifndef SH_EXECUTOR_H
#define SH_EXECUTOR_H

#define GREY "\033[1;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
// #define EOF -1

#include "../libft/libft.h"
// #include "sh_parser.h"

//******* struct for terminal
typedef struct t_ter
{
	pid_t	shell_pgid;
	struct	termios shell_tmodes;
	int		shell_terminal;
	int		shell_is_interactive;
} t_ter;

typedef struct t_echo
{
    int i;
    int j;
    char *key;
    char *key1;
    char *str;
    char *str1;
}   t_echo;

void sh_ex_displayarray(char **commands);
//void sh_ex_displayecho(t_shell_s *shell);
char *sh_ps_convertvalue(t_shell_s *shell, char *arg);
void sh_ps_echoall(t_shell_s *shell, char *arg);
//void sh_ps_changearg(t_shell_s *shell, char *arg);

void sh_ex_hasflag(t_shell_s *shell);

//void sh_ex_displayecho(char *str);

char	*ft_charjoin(char const *s1, char c);

void sh_ex_display(t_shell_s *shell);
void sh_ex_wcmessage();
int sh_ex_doublelen(char **str);
//void sh_ex_envlen(t_shell_s *shell);
void sh_ex_freeallin(char **str);
void sh_ex_freeall(char **str);
//void sh_ex_memkeyval(t_shell_s *shell);
//void sh_ex_createenvp(t_shell_s *shell, char **envp);
//void sh_ex_viewenvp(t_shell_s *shell);
//char *sh_ex_searchenvvar(t_shell_s *shell, char *key);
void sh_ex_initshell(t_shell_s *shell, char **envp);
void sh_ex_readline(t_shell_s *shell);
char *sh_ex_cwd(void);
// char   *sh_ex_createprompt(void);
char *sh_ex_createprompt(t_shell_s *shell);

//void sh_ex_freeallvar(t_shell_s *shell);
int count_words(const char *str, char c);
void sh_ex_countcommand(t_shell_s *shell);
void sh_ex_splitcommands(t_shell_s *shell);
int sh_ex_delimeterfound(char c);
char *word_dup(char *str, int start, int finish);
int sh_ex_outdirfound(char c);
int sh_ex_indirfound(char c);
int sh_ex_pipefound(char c);
// void sh_ex_execcmd(t_shell_s *shell);
// int sh_ex_isbuiltin(t_shell_s *shell);
//int sh_ex_isbuiltin(char *cmd);
//int sh_ex_isbuiltin(t_shell_s *shell, char *cmd);

//int sh_ex_exit(void);
//void sh_ex_echo(t_shell_s *shell);
//void sh_ex_builtin(t_shell_s *shell);
// void sh_ex_showpwd(void);
//void sh_ex_showpwd(t_shell_s *shell);

//char *sh_ex_bindir(t_shell_s *shell, char *cmd);
char *sh_ex_finddollar(char *str);
char *sh_ex_changekey(t_shell_s *shell);//
//void sh_ex_export(t_shell_s *shell);
//void sh_ex_addenv(t_shell_s *shell, char *str);
void sh_ex_addvalue(t_shell_s *shell, char *tmp_value);
void sh_ex_addkey(t_shell_s *shell, char *tmp_key);
//void sh_ex_cd(t_shell_s *shell);
void sh_ex_exitcode(void);

int sh_ex_firstdelimeter(char *str);

void sh_ex_checkinredirect(t_shell_s *shell, char *cmd);
void sh_ex_checkoutredirect(t_shell_s *shell, char *cmd);

int sh_ps_issinglequote(char c);
int sh_ps_isdoublequote(char c);
int sh_ps_isescape(char c);
char *sh_ps_removequote(char *str);
char *sh_ps_trimspace(char *str);

int sh_ps_issinglequotedarg(char *str);
void sh_ex_removeenv(t_shell_s *shell, char *key);
void sh_ex_unset(t_shell_s *shell);
void sh_ps_echoall(t_shell_s *shell, char *arg);
int sh_ps_isvalidname(char c);


int ft_chrfound(char *str, char c);

// functions for signal handling
// void sighandle(int sig);
void sh_ex_sighandle(int sig);
void sh_ex_exitshell(int sig);

void sh_ex_backslash(int sig);
void sh_ex_cntrlc(int sig);
void sh_ex_newprompt(int sig);
// char	**ft_splitset(char *s, int num);
void save_mode(void);
void set_mode(void);
void reset_mode(void);

void sh_ex_redirectfile(t_shell_s *shell);

//void init_shell();


//********sh_ex_builtin.c *************
int sh_ex_isbuiltin(t_commands *command);
void sh_ex_builtin(t_shell_s *shell, t_commands *command);

//******* sh_ex_echo.c*****************
void sh_ex_displayecho(t_shell_s *shell, t_commands *command);
void  sh_ex_echoflag(t_shell_s *shell, t_commands *command);
void sh_ex_echo(t_shell_s *shell, t_commands *command);
void sh_ex_echoarray(t_shell_s *shell, t_commands *command);

//******* sh_ex_cd.c*******************
void sh_ex_cd(t_shell_s *shell, t_commands *command);
void    sh_ex_changepwd(t_shell_s *shell);

//******* sh_ex_pwd.c *****************
char *sh_ex_cwd(void);
void sh_ex_showpwd(t_shell_s *shell);

//******** sh_ex_export.c *************
void sh_ex_addenv(t_shell_s *shell, char *str);
void sh_ex_export(t_shell_s *shell);
int sh_ex_searchenvindex(t_shell_s *shell, char *key);
void    sh_ex_changeenv(t_shell_s *shell, char *key, char *value);

//******** sh_ex_env.c ****************
void sh_ex_viewenvp(t_shell_s *shell);

//******* sh_ex_unset.c ***************
void sh_ex_removeenv(t_shell_s *shell, char *key);
void sh_ex_unset(t_shell_s *shell);

//******** sh_ex_exit.c ***************
void sh_ex_exit(t_shell_s *shell);

//******* sh_ex_utils.c ***************
void sh_ex_freeallvar(t_shell_s *shell, t_commands *command, t_words *words);

//******* sh_ex_bindir.c **************
char *sh_ex_bindir(t_shell_s *shell, char *cmd);

//******** sh_ex_builtin.c ************
int sh_ex_isbuiltin(t_commands *command);
void sh_ex_builtin(t_shell_s *shell, t_commands *command);

//******** sh_ex_env_utils.c **********
void sh_ex_envlen(t_shell_s *shell);
char *sh_ex_searchenvvar(t_shell_s *shell, char *key);
void sh_ex_memkeyval(t_shell_s *shell);
void sh_ex_createenvp(t_shell_s *shell, char **envp);

//******** sh_ex_quote.c **************
int sh_ps_issinglequote(char c);
int sh_ps_isdoublequote(char c);
int sh_ps_isescape(char c);
int sh_ps_isquoted(char c);
char *sh_ps_removequote(char *str);

//********* sh_ex_quote_utils.c ********
int sh_ps_issinglequotedarg(char *str);
int sh_ps_isvalidname(char c);
char *sh_ps_trimspace(char *str);

//********* sh_ex_shellinit.c **********
void	init_shell(t_ter *ter);
void save_mode(void);
void set_mode(void);
void reset_mode(void);

//********* sh_ex_signal.c *************
void sh_ex_sighandle(int sig);
void sh_ex_newprompt(int sig);
void sh_ex_exitshell(int sig);

//********* sh_ex_utils.c **************
void sh_ex_wcmessage(void);
int sh_ex_doublelen(char **str);
void sh_ex_freeall(char **str);
void sh_ex_freeallin(char **str);
void sh_ex_freeallvar(t_shell_s *shell, t_commands *command, t_words *words);

//********* extra.c ******************
void sh_ps_changearg(t_shell_s *shell, t_echo *echo, char *arg);
void sh_ex_display(t_shell_s *shell);
void sh_ex_displayarray(char **commands);
char	*ft_charjoin(char const *s1, char c);
int ft_chrfound(char *str, char c);
int sh_ps_listlen(t_commands *command);

//**********sh_ex_executor.c ************
void sh_ex_execcmd(t_shell_s *shell, t_commands *command);


#endif