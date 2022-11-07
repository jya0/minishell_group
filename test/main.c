#include "shell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    char *cmd;
    initsh();

    do
    {
        print_prompt1();

        cmd = read_cmd();
        if (!cmd)
            exit(EXIT_SUCCESS);
        
        if (cmd[0] == '\0' || strcmp(cmd , "\n") == 0)
        {
            free(cmd);
            continue;
        }

        if (strcmp(cmd , "exit\n") == 0)
        {
            free(cmd);
            break;
        }

        t_src src;
        src.buffer = cmd;
        src.bufsize = strlen(cmd);
        src.curpos = INIT_SRC_POS;
        parse_and_execute(&src);

//        printf("%s\n", cmd);
        free(cmd);
    }while (1);
    exit(EXIT_SUCCESS);
}
