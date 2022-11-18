#include "sh_executor.h"

void    sh_ex_wcmessage()
{
    printf("%s\n","----------------------------------------");
    printf("%s\n","||                                    ||");
    printf("%s\n","||                                    ||");
    printf("%s\n","||      Wel come to Minishell         ||");
    printf("%s\n","||                                    ||");
    printf("%s\n","||                                    ||");
    printf("%s\n","----------------------------------------");
}

int main(int argc, char **argv, char **envp)
{
    t_shell_s shell;

    sh_ex_wcmessage();
    return (0);
}