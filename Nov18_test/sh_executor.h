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

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// struct for the environment variables

typedef struct t_env_s
{
    int env_index;
    int env_size;
    char **envp;
    char **key;
    char **value;
}   t_env_s;

// struct for the command variables

typedef struct t_shell_s
{
    int infile;  //file descriptor stdin 
    int outfile;  // file descriptor for stdout
    char *cmd_line; // read the command line
    char **commands; // simple commands
    char *home;  //  a path for a home directory
    char **path;    // a path for the list of path direcotories separeted by ':'
    struct t_env_s envp;
}   t_shell_s;

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
char   *sh_ex_createprompt(void);
void sh_ex_freeallvar(t_shell_s *shell);

int	count_words(const char *str, char c);
char	*word_dup(const char *str, int start, int finish);

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, unsigned int n);
int	ft_strlen(const char *str);

#endif