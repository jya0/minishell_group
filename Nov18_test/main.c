#include "sh_executor.h"

// displays a welcome message 

void    sh_ex_wcmessage()
{
    printf("%s%s\n",CYAN,"----------------------------------------");
    printf("%s\n","||                                    ||");
    printf("%s\n","||                                    ||");
    printf("%s\n","||      Welcome to Minishell          ||");
    printf("%s\n","||                                    ||");
    printf("%s\n","||                                    ||");
    printf("%s%s\n\n","----------------------------------------", WHITE);
}

// count the number of string in the double arrray return the length

int sh_ex_doublelen(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    sh_ex_envlen(t_shell_s *shell)
{
    int i;

    i = 0;
    while (shell->envp.envp[i])
        i++;
    shell->envp.env_size = i;
}

// frees all the memory of a double array

void sh_ex_freeall(char **str)
{
    int i;

    if (!str && !(*str))
        return ;
    i = 0;
    while (str[i])
    {
        free(str[i]);
        str[i] = NULL;
        i++;
    }
    free(str);
    str = NULL;
}

void sh_ex_freeallin(char **str)
{
    int i;

    if (!str && !(*str))
        return ;
    i = 0;
    while (str[i])
    {
        free(str[i]);
        str[i] = NULL;
        i++;
    }
}

// view the all the environment variables

void sh_ex_viewenvp(t_shell_s *shell)
{
    int i;

    i = 0;
    while (shell->envp.envp[i])
    {
        printf("%s", shell->envp.key[i]);
        printf("%c",'=');
        printf("%s\n",shell->envp.value[i]);
        i++;
    }
}

// search for the key in the environment if found returns the value else return NULL

char *sh_ex_searchenvvar(t_shell_s *shell, char *key)
{
    int i;
    int len;
    
    len = ft_strlen(key);
    i = 0;
    while (shell->envp.key[i])
    {
        if (ft_strncmp(shell->envp.key[i], key, len) == 0)
            return (shell->envp.value[i]);
        i++;
    }
    return (NULL);
}

// allocates a memory for the key and value of environment variables 
// cutted out of sh_ex_creteenv() beacause it is long

void sh_ex_memkeyval(t_shell_s *shell)
{
    shell->envp.key = malloc(sizeof(char*) * (shell->envp.env_size + 1));
    if (!shell->envp.key)
        exit (EXIT_FAILURE);  
    shell->envp.value = malloc(sizeof(char*) * (shell->envp.env_size + 1));
    if (!shell->envp.value)
        exit (EXIT_FAILURE);
} 

// creates the environment variables form the env argument

void    sh_ex_createenvp(t_shell_s *shell, char **envp)
{
    int i;
    char **temp_env;

    shell->envp.envp = envp;
    sh_ex_envlen(shell);
    sh_ex_memkeyval(shell);
    
    i = 0;
    while (i < shell->envp.env_size)
    {
        temp_env = ft_split(shell->envp.envp[i], '=');
        shell->envp.key[i] = ft_strdup(temp_env[0]);
        if (temp_env[1])
            shell->envp.value[i] = ft_strdup(temp_env[1]);
        else 
            shell->envp.value[i] = ft_strdup("");
// free the memory allocated by ft_split() nad ft_strdup()
        sh_ex_freeall(temp_env);
        i++;
    }

    shell->envp.key[i] = NULL;
    shell->envp.value[i] = NULL;

}

// initialize the shell values home and path variables
// and free home becuase it use ft_strdup to allocate memory
// and free path it uses allocate memory

void sh_ex_initshell(t_shell_s *shell, char **envp)
{
    int i;
    char *all_path;
    char **path;
    char *home;

    sh_ex_createenvp(shell, envp);
    home = sh_ex_searchenvvar(shell, "HOME");
    shell->home = ft_strdup(home);
    all_path = sh_ex_searchenvvar(shell, "PATH");
    path = ft_split(all_path, ':');
    shell->path = malloc(sizeof(char *) * (shell->envp.env_size + 1));
    if (!shell->path)
        return ; 
    i = 0;
    while (path[i])
    {
        shell->path[i] = ft_strjoin(path[i], "/");
        i++;
    }
    sh_ex_freeall(path);
    shell->path[i] = NULL;  
}

// create a function that read a command line using builtin
// funciton readline first create a prompt line
// accept the string from the command line and assign it 
// to the commnad in the shell struct variable

void    sh_ex_readline(t_shell_s *shell)
{
    char *prompt_line;

    prompt_line = sh_ex_createprompt();
    
    // create a function for handling a signal
//    sh_ex_sighandle(1);
    shell->cmd_line = NULL;
    if (shell->cmd_line)
    {
        free(shell->cmd_line);
        shell->cmd_line = (char *)NULL;
    }
    shell->cmd_line = readline(prompt_line);
    free(prompt_line);
    if (shell->cmd_line && (*shell->cmd_line))
        add_history(shell->cmd_line);
}

// get the current working directory and return it

char *sh_ex_cwd(void)
{
    char cwd_str[1024];

    getcwd(cwd_str, sizeof(cwd_str));
    char *cwd = ft_strdup(cwd_str);
    return (cwd);
}

// create the commnad line prompt

 char   *sh_ex_createprompt(void)
{
    char *prompt;
    char *buf;
    char *color;

    buf = sh_ex_cwd();
    color = ft_strdup(GREEN);
    prompt = ft_strjoin(color, buf);
    free(buf);
    free(color);
    color = ft_strdup(WHITE);
    buf = ft_strjoin(prompt, color);
    free(color);
    free(prompt);
    prompt = ft_strjoin(buf, " 🤡 >> ");
    free(buf);
    return (prompt);
} 

// free all the variable that are allocated dynamically

void sh_ex_freeallvar(t_shell_s *shell)
{
    sh_ex_freeall(shell->envp.key);
    sh_ex_freeall(shell->envp.value);
    sh_ex_freeall(shell->path);
    free(shell->home);
    free(shell->cmd_line);
}


// for now let split the command line only with space
// and when you insert the command use the special charcters (< > >> |)
// together with the command
void sh_ex_split(t_shell_s *shell)
{
    int len;

    len = count_words(shell->cmd_line, ' ');
    shell->commands = malloc(sizeof(char*) * (len + 1));
    if (!shell->commands)
        exit(EXIT_FAILURE);

    shell->commands = ft_split(shell->cmd_line , ' ');
}
int main(int argc, char **argv, char **envp)
{
    t_shell_s shell;

    sh_ex_wcmessage();
    sh_ex_initshell(&shell, envp);
    
    while (1)
    {
        shell.infile = STDIN_FILENO;
        shell.outfile = STDOUT_FILENO;
        sh_ex_readline(&shell);

        // check if cmd_line is null
        if (shell.cmd_line && ft_strlen(shell.cmd_line) != 0)
        {
            if (ft_strncmp(shell.cmd_line,"exit", 4) == 0)
                exit(0);
        // check if the cmd_is not error
        // if there is no error split using the delimiters and assign it the members of
        // commands as a double array 
    
        // use to exit from the loop for now until using signal

            sh_ex_split(&shell);

        }
    }
    sh_ex_freeallvar(&shell);
    return (0);
} 