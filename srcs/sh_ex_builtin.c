#include "../includes/sh_executor.h"

int sh_ex_isbuiltin(char *str)
{
    if (ft_strcmp(str, "echo") == 0)
        return 1;
    if (ft_strcmp(str, "cd") == 0)
        return 1;
    if (ft_strcmp(str, "pwd") == 0)
        return 1;
    if (ft_strcmp(str, "export") == 0)
        return 1;
    if (ft_strcmp(str, "unset") == 0)
        return 1;
    if (ft_strcmp(str, "env") == 0)
        return 1;
    if (ft_strcmp(str, "exit") == 0)
        return 1;
    if (ft_strcmp(str, "$?") == 0)
        return 1;    
    return (0);
}

int sh_ex_isbuiltin(t_shell_s *shell)
{
    if (ft_strcmp(shell->cmd_line, "echo") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "cd") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "pwd") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "export") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "unset") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "env") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "exit") == 0)
        return 1;
    if (ft_strcmp(shell->cmd_line, "$?") == 0)
        return 1;    
    return (0);
}

void    sh_ex_builtin(t_shell_s *shell)
{
    if (ft_strncmp(shell->cmd_line, "echo", 4) == 0)
        sh_ex_echo(shell);
    if (ft_strncmp(shell->cmd_line, "cd", 2) == 0)
         sh_ex_cd(shell);
    if (ft_strncmp(shell->cmd_line, "pwd", 3) == 0)
        sh_ex_showpwd(shell);
    if (ft_strncmp(shell->cmd_line, "export", 6) == 0)
        sh_ex_export(shell);
    if (ft_strncmp(shell->cmd_line, "unset", 5) == 0)
         sh_ex_unset(shell);
    if (ft_strncmp(shell->cmd_line, "env", 3) == 0)
         sh_ex_viewenvp(shell);
    if (ft_strncmp(shell->cmd_line, "exit", 4) == 0)
        sh_ex_exit();
    if (ft_strncmp(shell->cmd_line, "$?", 4) == 0)
        sh_ex_exitcode();        
}

int sh_ex_exit(void)
{
    write(1, "exit\n", 5);
    exit (0);
}

// search for the key in the environment variables if found replace it 
// with the value

char *sh_ex_changekey(t_shell_s *shell)
{
    char *keys;
    char **values;
    char *msg;
    int i;
    int count;

    i = 0;
    count = 0;
    msg = NULL;
    keys = sh_ex_finddollar(shell->cmd_line);
    values = ft_split(keys, '$');

    // count the length of values 
    while (values[i])
    {
        if (sh_ex_searchenvvar(shell, values[i]))
            count += ft_strlen(sh_ex_searchenvvar(shell, values[i]));
        i++;
    }

    msg = malloc(sizeof(char) * (count + 1));
    if (!msg)
        return (NULL);
    i = 0;
    while (values[i])
    {
        if (sh_ex_searchenvvar(shell, values[i]))
            msg = ft_strjoin(msg, sh_ex_searchenvvar(shell, values[i]));
        i++;
    }
    return (msg);
}

char *sh_ex_finddollar(char *str)
{
    int i;
    char *key;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (&str[i + 1]);
        i++;
    }
    return (NULL);

}

// builin function for echo
void sh_ex_echo(t_shell_s *shell)
{
    char **str;
    char flag[2] = "-n";
    int len;

    str = ft_split(shell->cmd_line, ' ');

    if (str[1] == NULL)
        printf("%s\n", ft_strdup(""));
    else
    {
        if (ft_strncmp(str[1], flag, 2) == 0)
        {
            if (str[2] != NULL)
                printf("%s", str[2]);
            else
                printf("%s\n", ft_strdup(""));
        }
        else
        {
            sh_ps_echoall(shell, str[1]);
        //    printf("%s\n",str[1]);
        }
            
    }
    sh_ex_freeall(str);
}

// builtin function for pwd
void sh_ex_showpwd(t_shell_s *shell)
{
    char *dir = sh_ex_cwd();
    dir = ft_strjoin(WHITE, dir);
    printf("%s\n", dir);
    free(dir);
}

 void    sh_ex_addenv(t_shell_s *shell, char *str)
{
    int i;

    char **envp;
    envp = malloc(sizeof(char*) * (shell->envp.env_size + 2));
    if (!envp)
        exit(EXIT_FAILURE);  
    i = 0;  
    while (shell->envp.envp[i])
    {
        envp[i] = shell->envp.envp[i];
        i++;
    }
    if (str)
    {
        envp[i++] = ft_strdup(str);
        envp[i] = NULL;
    }
    else
        envp[i] = NULL;
    shell->envp.envp = NULL;
    shell->envp.envp = envp;
}

/* 
void sh_ex_addkey(t_shell_s *shell, char *tmp_key)
{
    int i;
    char **key;

    key = malloc(sizeof(char*) * (shell->envp.env_size + 1));
    if (!key)
        exit(EXIT_FAILURE);

    i = 0;
    while (shell->envp.key[i])
    {
        // check for double memery allocation
        key[i] = ft_strdup(shell->envp.key[i]);
        i++;
    }
    key[i++] = tmp_key;
    key[i] = NULL;

    sh_ex_freeall(shell->envp.key);
//    shell->envp.key = NULL;
    shell->envp.key = key;
}

void sh_ex_addvalue(t_shell_s *shell, char *tmp_value)
{
    int i;
    char **value;

    value = malloc(sizeof(char*) * (shell->envp.env_size + 1));
    if (!value)
        exit(EXIT_FAILURE);  

    i = 0;
    while (shell->envp.value[i])
    {
        // check for double memory allocation

        value[i] =ft_strdup(shell->envp.value[i]); 
        i++;
    }
    if (tmp_value)
        value[i++] = tmp_value;
    else
        value[i++] = ft_strdup("");
    value[i] = NULL;    
    
    sh_ex_freeall(shell->envp.value);
//    shell->envp.value = NULL;
    shell->envp.value = value; 
} 
 */

void sh_ex_export(t_shell_s *shell)
{
    char *str;
    char **tmp_str;
    char **tmp_env;

    str = NULL;
    tmp_str = ft_split(shell->cmd_line, ' ');
    if (tmp_str[1] == NULL)
    {
         sh_ex_viewenvp(shell);
         return;
    }
    else
    {
        str = sh_ps_removequote(tmp_str[1]);
        tmp_env = ft_split(str, '=');
        if (sh_ex_searchenvvar(shell, tmp_env[0]) == NULL)
        {
            shell->envp.env_size++;
            sh_ex_addenv(shell, str);
            sh_ex_createenvp(shell, shell->envp.envp);
            // sh_ex_addkey(shell, tmp_env[0]);
            // sh_ex_addvalue(shell, tmp_env[1]);       
        }
    }
    free(str);
//    sh_ex_freeall(tmp_str);
}

void    sh_ex_removeenv(t_shell_s *shell, char *key)
{
    int i;
    int j;
    char **envp;
    int size;
    char *str;

    if (sh_ex_searchenvvar(shell, key) != NULL)
    {
        shell->envp.env_size--;
        envp = malloc(sizeof(char *) * (shell->envp.env_size + 1));
        if (!envp)
            return ;
        i = 0;
        j = 0;
        while (shell->envp.envp[i])
        {
            if (ft_strncmp(key, shell->envp.envp[i], ft_strlen(key)) == 0)
            {
                i++;
                continue;
            }
            else
                envp[j++] = shell->envp.envp[i++]; 
        }
        envp[j] = NULL;
        shell->envp.envp = NULL;
    //    sh_ex_freeall(shell->envp.envp);
        shell->envp.envp = envp;
    }
}

void sh_ex_unset(t_shell_s *shell)
{
    char **tmp_str;
    char *tmp;
    char *str;

    tmp_str = ft_split(shell->cmd_line, ' ');
    if (tmp_str[1] != NULL)
    {
        str = sh_ps_removequote(tmp_str[1]);
        sh_ex_removeenv(shell,str);
        sh_ex_createenvp(shell,shell->envp.envp);
    }
}

void sh_ps_echoall(t_shell_s *shell, char *arg)
{
    int i;
    int j;
    char *key = NULL;
    char *key1 = NULL;
    char *str;
    i = 0;
    j = 0;
    
    if (sh_ps_issinglequotedarg(arg))
        printf("%s", sh_ps_removequote(arg));
    else
    {
        str = sh_ps_removequote(arg);
        while (i < ft_strlen(str))
        {
            if (str[i] == '$')
            {
                j = i + 1;;
                while (sh_ps_isvalidname(str[j]) && j < ft_strlen(str))
                    j++;
                key = ft_substr(str, i + 1 , (j - i - 1));
                key1 = sh_ex_searchenvvar(shell, key);
                if (key1)
                {
                    printf("%s", key1);
                //    key = NULL;
                //    key1 = NULL;
                }
                else
                    write(1, "", 0);
                    // printf("");
                i = j - 1;
            }
            else
                printf("%c", str[i]);
            i++;
        }
    }
    printf("\n");
}

void sh_ex_cd(t_shell_s *shell)
{
    char *dir;
    char **tmp_str;

    tmp_str = ft_split(shell->cmd_line, ' ');
    if (chdir(tmp_str[1]) == 0)
    {
        dir = ft_strjoin(WHITE, shell->cwd);
        shell->cwd = ft_strjoin(dir, "/");
        free(dir);
        dir = ft_strjoin(shell->cwd, tmp_str[1]);
    }
    else
        chdir(shell->home);
}

void sh_ex_exitcode(void)
{
    printf("%d\n", sh_ex_exitstatus);
}
