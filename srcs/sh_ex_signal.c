#include "../includes/sh_executor.h"


void	sh_ex_sighandle(int sig)
{
    set_mode();

    if (sig == 1)
    {
         signal(SIGINT, sh_ex_newprompt);
    //     signal(SIGQUIT, SIG_IGN);
    }
/*     if (sig == 2)
    {
         signal(SIGINT, sh_ex_cntrlc);
         signal(SIGQUIT, sh_ex_backslash);
    } */
    if (sig == 3)
    {    
        sh_ex_exitshell(3);
    }
}
void	sh_ex_newprompt(int sig)
{
    set_mode();
    sh_ex_exitstatus = 130; // commnad terminated by cntl + c
    write(1, "\n", 1);
//    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    (void)sig;
}

void sh_ex_exitshell(int sig)
{
    set_mode();
    printf("exit\n");
    exit(0);
}
/* void	sh_ex_cntrlc(int sig)
{    
    set_mode();
//    g_ret_number = 130;
    write(1, "\n", 1);
    (void)sig;
}
void	sh_ex_backslash(int sig)
{
    set_mode();

//    g_ret_number = 131;
    printf("Quit (core dumped)\n");
    (void)sig;
} */

void save_mode(void)
{
    tcgetattr(STDIN_FILENO, &old_term);
}

 void set_mode(void)
{

    tcgetattr(STDIN_FILENO, &old_term);
    atexit(reset_mode);
    int t_mode = isatty(STDIN_FILENO);
    {
        if (t_mode == 1)
        {
            tcgetattr(STDIN_FILENO, &new_term);
            new_term.c_lflag &= ~(ICANON | ECHOCTL);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_term );
        }
    } 
} 

void reset_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
} 