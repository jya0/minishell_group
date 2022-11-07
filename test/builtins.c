#include "shell.h"

t_builtins_s builtins[] = 
{
    {"dump" , dump},
};

int builtins_count = sizeof(builtins)/sizeof(t_builtins_s);

int dump(int argc, char **argv)
{
    dump_local_symtab();
    return (0);
}