#ifndef SH_EXECUTOR_H
#define SH_EXECUTOR_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    char *command;
    char *home;
    char **path;
    struct t_env_s envp;
}   t_shell_s;

void    sh_ex_wcmessage();


#endif