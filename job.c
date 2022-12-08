#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

typedef struct process
{
    struct process *next;
    char **argv;
    pid_t pid;
    char completed;
    char stopped;
    int status;
} process;

typedef struct  job
{
    struct job *next;
    char *command;
    process *first_process;
    pid_t pgid;
    struct termios tmodes;
    int stdin, stdout, stderr;
} job;

pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;
job *first_job = NULL;

job *find_job(pid_t pgid)
{
    job *j;

    for (j = first_job; j; j = j->next)
    {
        if (j->pgid == pgid)
            return (j);
    }
    return (NULL);
}

int job_is_stopped(job *j)
{
    process *p;

    for (p = j->first_process; p; p = p->next)
    {
        if (!p->completed && !p->stopped)
            return (0);
    }
    return (1);
}

int job_is_completed(job *j)
{
    process *p;
    for (p = j->first_process; p; p = p->next)
    {
        if (!p->completed)
            return (0);
    }
    return (1);
}

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

void launch_process(process *p, pid_t pgid, int infile, int outfile, int errfile, int forground)
{
    pid_t pid;
    
    if (shell_is_interactive)
    {
        // put the process in group process it has be done 
        // both in the shell and child process
        pid = getpid();
        if (pgid == 0)
            pgid = pid;
        setpgid(pid, pgid);
        tcsetpgrp(shell_terminal, pgid);

        // set the signal handling to default.
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

// set the new standard input / output channel of the new process
        if (infile != STDIN_FILENO)
        {
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        if (outfile != STDOUT_FILENO)
        {
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        if (errfile != STDERR_FILENO)
        {
            dup2(errfile, STDERR_FILENO);
            close(errfile);
        }
    // execute the process and make sure to exit;
        execvp(p->argv[0], p->argv);
        perror("exevp");
        exit(1);
    }
}