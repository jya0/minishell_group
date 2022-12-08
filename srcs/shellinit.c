#include "../includes/sh_executor.h"

// make the subshell a forground process if it is not
// and make it a process group to have the job control of the terminal
// and make it to ignore all signal that will stop it and send it to
// background process.

// once it have the control of the terminal it can launch commands typed 
// by the user


// setsid() creates a new function and the calling process becomes the session
// leader and it puts in the new process group whose process group ID is the same
// as the process ID of that process.
    pid_t shell_pgid;
    struct termios shell_tmodes;
    int shell_terminal;
    int shell_is_interactive;

void init_shell()
{
    shell_terminal = STDIN_FILENO;
    // isatty test whethet a file descriptro refers to a terminal
    // return 1 if it fd is open;
    shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive)
    {
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill(- shell_pgid, SIGTTIN);

            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            signal(SIGTSTP, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            signal(SIGCHLD, SIG_IGN);

            shell_pgid = getpid();
        // setpgid() puts the process pid into the proces group pgid    
            if (setpgid(shell_pgid, shell_pgid) < 0)
            {
                perror("Couldn't put the shell in it's own process group.");
                exit (1);
            }
            tcsetpgrp(shell_terminal, shell_pgid);
            tcgetattr(shell_terminal, &shell_tmodes);
    }
}