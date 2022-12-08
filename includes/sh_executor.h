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
#define EOF -1


#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/types.h>

// struct for the environment variables

//struct termios new_term, old_term;
int sh_ex_exitstatus;
struct termios old_term, new_term;

typedef struct t_env_s
{
    int env_index; // current index of enviroment variable
    int env_size; // total number of enviroment variables
    char **envp;   // environment variable 
    char **key; // keys of environment variables
    char **value;   // values of environment variables
}   t_env_s;

// struct for the command variables

typedef struct t_shell_s
{
    char line;  // check command in the execution
    char error_file; // 
    char **tokens;
    char *file_name; // executable file

    int flag;    // to represent the delimeter 
    int char_count;  // number of characters 
    char *outdir_filename; // file name for out redirect
    char *outapp_filename;  // file used for truncate for >>
    char *indir_filename; // file name for in redirect
    char *herdoc; // for <<
    int cmdindex; // index of the commands
    int num_commands; // number of all commands
    int num_pipes;  // number of all pipes
    int infile;  //file descriptor for redirect in file 
    int outfile;  // file descriptor for redirect out file
    int dbl_infile;  // to check if there is << 
    int dbl_outfile; // to chec if there is >>
    char *cmd_line; // read the command line
    char **commands; // simple commands
    char *cwd;    // displays the current working directory
    char *home;  //  a path for a home directory
    char **path;    // a path for the list of path direcotories separeted by ':'
    struct t_env_s envp;
}   t_shell_s;


void sh_ex_display(t_shell_s *shell);
void    sh_ex_wcmessage();
int sh_ex_doublelen(char **str);
void    sh_ex_envlen(t_shell_s *shell);
void sh_ex_freeallin(char **str);
void sh_ex_freeall(char **str);
void sh_ex_memkeyval(t_shell_s *shell);
void    sh_ex_createenvp(t_shell_s *shell, char **envp);
void sh_ex_viewenvp(t_shell_s *shell);
char *sh_ex_searchenvvar(t_shell_s *shell, char *key);
void sh_ex_initshell(t_shell_s *shell, char **envp);
void    sh_ex_readline(t_shell_s *shell);
char *sh_ex_cwd(void);
//char   *sh_ex_createprompt(void);
char   *sh_ex_createprompt(t_shell_s *shell);

void sh_ex_freeallvar(t_shell_s *shell);
int	count_words(const char *str, char c);
void sh_ex_countcommand(t_shell_s *shell);
void sh_ex_splitcommands(t_shell_s *shell);
int sh_ex_delimeterfound(char c);
char	*word_dup(char *str, int start, int finish);
int sh_ex_outdirfound(char c);
int sh_ex_indirfound(char c);
int sh_ex_pipefound(char c);
void sh_ex_execcmd(t_shell_s *shell);
int sh_ex_isbuiltin(t_shell_s *shell);


int sh_ex_exit(void);
void sh_ex_echo(t_shell_s *shell);
void    sh_ex_builtin(t_shell_s *shell);
//void sh_ex_showpwd(void);
void sh_ex_showpwd(t_shell_s *shell);


char *sh_ex_bindir(t_shell_s *shell, char *cmd);
char *sh_ex_finddollar(char *str);
char *sh_ex_changekey(t_shell_s *shell);
void sh_ex_export(t_shell_s *shell);
void    sh_ex_addenv(t_shell_s *shell, char *str);
void sh_ex_addvalue(t_shell_s *shell, char *tmp_value);
void sh_ex_addkey(t_shell_s *shell, char *tmp_key);
void sh_ex_cd(t_shell_s *shell);
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
void    sh_ex_removeenv(t_shell_s *shell, char *key);
void sh_ex_unset(t_shell_s *shell);
void sh_ps_echoall(t_shell_s *shell, char *arg);
int sh_ps_isvalidname(char c);


// functions for signal handling
//void sighandle(int sig);
void	sh_ex_sighandle(int sig);
void sh_ex_exitshell(int sig);

void	sh_ex_backslash(int sig);
void	sh_ex_cntrlc(int sig);
void	sh_ex_newprompt(int sig);
//char	**ft_splitset(char *s, int num);
void save_mode(void);
void set_mode(void);
void reset_mode(void);


void sh_ex_redirectfile(t_shell_s *shell);

void init_shell();
#endif