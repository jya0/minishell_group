// create a struct for the enviroment variables

typedef struct t_env_s
{
    char **envp; // the whole environments
    int len;     // length of the enviroments
    char **key;
    char **value;
    int index;
} t_env_s;

// start with the main function that accepts argv and environment

typedef struct t_mini_s
{
    char *home;
    char **path;
    // declare all the variables here
    struct t_env_s envp;

} t_mini_s;

int main(int argc, char **argv, char **envp)
{
    // declare and initialize the main struct (that contain all the variables)
    t_mini_s mini;

    // print wel com screen

    screen_init();

    // call the function that will initialize the values
    // currenly there are no value to be initialized

    mini_initialize(mini, envp);
    // initialize the prompt with wel come message

    //------------------------

    // create while (1)
    {
        mini_out = STDOUt_fileno
            mini_in = stdin_filino;
        // create infile and outfile variables in main struct
        // and assign it to STDOUT and STDIN
        readline(cmd_line);

        // read the command using readline
        if (read_line(mini))
        {
            /*
                Check if (mini->read_line != 0)
                {
                1 -    split the read_line with the delimeters
                2 -    if the num_command is > 0 and cmd[0][0] != '|' executet the command
                3 =    if command[0] && cmd[0][0] == '|' print error
                    exitstatus 2 syntax error near unexpecte token
                4 -    free command memory
                }
                */
        }
        free(read_line);
        else run singnal(3); // if the read line is empty ie it is null
                             // or pressed cntrl + d it will exit
    }
    void screen_init()
    {
        printf("%s\n", "welcome");
    }

    void mini_initialize(t_mini_s * mini, char **envp)
    {
        // create the enviroment variables key and value;
        create_envp(mini, envp);

        // search for "HOME" in the struct key and assign it
        // to mini->home;
        mini->home; // mini->home = strdup(find_env(mini->env.key, "HOME"))

        // search for the PATH in the environment key and take
        // the value and split it at ":" and assign it to the mini->path

        initialize_path(mini);
    }

    void create_envp(t_env_s * mini, char **envp)
    {
        // count the number of env
        envp_len(envp);

        // assign mini->envp to envp
        //------------------------

        // use void and if null exit_FAILURE
        //------------------------
        // first mallack mini->env.key and mini->envp.value

        // create a temp double char array to hold the env after
        // spliting at "=" for the key and value
        // index[0] will be key but check if index [1]
        // is not null if it is assign it with ""
        // using strdup;
        // free the temp char array
        //------------------
        // temp_env = NULL after freeing since we don't
        // use NULL in the function

        // use ft_strdup for all key and content
        //------------------------
        //  mini->env.key and mini->envp.value last value will be NULL at i;
    }

    int envp_len(envp)
    {
        // counts the number of enviromnets
        //------------------------
        // for len instead of return int
        // assign it to env-len_size
    }
    //------------------------
    char *search_env(t_env_s * mini, char *key)
    {
        // compare every mini->env.key with the key
        // if found retern the content with the same index
        // else return NULL;
    }

    //------------------------
    void free(**array)
    {
        // while (array[i] )
        // free the elements free(array[i])
        // and assign it to NULL array[i] = NULL
        // and free the main array free(array)
    }

    void free2(**array)
    {
        //     // free the elements free(array[i])
        // assing it to NULL
    }

    void readline(shell)
    {
        // create a variable in mini readline
        // create prompt char *prompt
        create_prompt() return the current direcotory
        // run signal function to accept signals
        // read the line
        // assign read line to mini->readline
        // if not null add it to history
        // free the prompt
    }

    char *create_prompt(){
        char * prompt
        // char *buf[] use geekstip to
        //  use getcwd funcition
        //  return current direictory
        //  and sign $ or >> at the end using ft_strjoin
        //  get buf
        //  dup color
        //  join color and buf
        //  free buf
        // joint with sign
        return prompt}

        make -
        L - lft - lreadline
 void	run_commands(t_struct *mini)
{
    int		j;
    int		fd[2];

    j = 0;
    mini->c = 0;
    mini->last_redir = 0;
    while (j < mini->split.qtt_pipe)
    {
        if (pipe(fd) < 0)
        {
            printf("Pipe error\n");
            g_ret_number = 127;
        }
        mini->out_fd = fd[1];
        run_commands_aux(mini);
        close(mini->out_fd);
        if (mini->in_fd != 0)
            close(mini->in_fd);
        mini->in_fd = fd[0];
        j++;
    }
    run_commands_aux(mini);
}

void	run_commands_aux(t_struct *mini)
{
    action(mini);
    if (mini->commands[0][0] != '>')
    {
        tokenizer(mini);
        if (mini->tokens[0])
            is_builtin(mini->tokens[0], mini);
        if (mini->in_fd != -1)
            exec_process(mini, mini->in_fd, mini->out_fd);
        free_char_array(mini->tokens);
        free(mini->token.to_print);
        free(mini->token.to_exec);
    }
    if (mini->name_file)
        unlink(mini->name_file);
}

void	action(t_struct *mini)
{
    mini->line = ft_strdup(mini->commands[mini->c]);
    if (mini->split.n_comand > 1 )
        mini->c++;
    mini->error_name_file = NULL;
    while (mini->commands[mini->c] && mini->commands[mini->c][0] != '|')
    {
        redirect_out(mini, mini->c);
        redirect_in(mini, mini->c, NULL);
        mini->c++;
    }
    if (mini->error_name_file != NULL)
    {
        g_ret_number = 1;
        printf("minishell: %s: %s", mini->error_name_file, ERROR_DIR);
        free(mini->error_name_file);
    }
}

void	exec_process(t_struct *mini, int in, int out)
{
    pid_t	pid;

    if (mini->is_builtin && mini->tokens[0])
        run_builtin(mini);
    else
    {
        pid = fork();
        run_signals(2);
        if (pid < 0)
        {
            printf("Fork error\n");
            g_ret_number = 127;
        }
        else if (pid == 0)
        {
            file_descriptor_handler(in, out);
            g_ret_number = 127;
            ft_execve_pipe(mini, 0, "");
            exit(g_ret_number);
        }
        else
            waitpid(pid, &g_ret_number, WUNTRACED);
        if (WIFEXITED(g_ret_number))
            g_ret_number = WEXITSTATUS(g_ret_number);
    }
}

void	ft_execve_pipe(t_struct *mini, int i, char *command)
{
    if (mini->tokens[0])
    {
        g_ret_number = execve(mini->tokens[0], &mini->tokens[0],
                mini->env.env);
        while (mini->path && mini->path[i] != NULL)
        {
            command = ft_strdup(mini->path[i]);
            if (mini->tokens[0][0] == '|' && mini->tokens[1])
            {
                if (!mini->tokens[0][1])
                    spaces_in_pipe(mini, 2, command);
                else
                {
                    mini->tokens[0] = &mini->tokens[0][1];
                    spaces_in_pipe(mini, 1, command);
                }
            }
            else
                spaces_in_pipe(mini, 1, command);
            i++;
        }
        execve_error(mini);
    }
}
*/

// first try to execute the commnad with out error check
// use pipe and redirect in and out

/* void	run_signals(int sig)
{
    if (sig == 1)
    {
        signal(SIGINT, restore_prompt);
        signal(SIGQUIT, SIG_IGN);
    }
    if (sig == 2)
    {
        signal(SIGINT, ctrl_c);
        signal(SIGQUIT, back_slash);
    }
    if (sig == 3)
    {
        printf("exit\n");
        exit(0);
    }
}

void	restore_prompt(int sig)
{
    g_ret_number = 130;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    (void)sig;
}

void	ctrl_c(int sig)
{
    g_ret_number = 130;
    write(1, "\n", 1);
    (void)sig;
}

void	back_slash(int sig)
{
    g_ret_number = 131;
    printf("Quit (core dumped)\n");
    (void)sig;
} */

// Exit code 127 means job's command can not be found or executed
/*
1: general errors

2: misuse of shell builtins (pretty rare)

126: cannot invoke requested command

127: command not found error

128: invalid argument to “exit”

128+n: fatal error signal “n” (for example, kill -9 = 137).

130: script terminated by Ctrl-C */

                      https : // www.thegeekstuff.com/2010/10/linux-error-codes/
/*
                              void
run_command(mini)
    {
        int j;
        int fd[2];

        i = 0;
        // create a function that count the number of pipes
        // and return the value

        while (i < num_of_pipes)
        {
            // pipe
            if (pipe(fd) == -1)
            { //
                printf(pipe errro\n);
                exitstatus = 127; // what is 127
            }

            mini_out = fd[1] // read end of pipe
                             // read from the standard out put and execute it
                             // create a function that will execute the commands
                execute_process(mini);
            close(min_out);
            if (mini - in != 0) // if it is not standard in put
                close(mini - in);
            mini->in = fd[0]; // assign it to read end;
            i++;
        }
        execute_process(mini);
    }

    void execute_process(mini)
    {
        some_action(mini); // to be determined later
        // check if commnad [0][0] is not '>' execute only pipe
        if (mini_ > cmd[0][0] != '>')
        {
            // tokenize the command to tokens split it again
            tokenize_function(mini);
            if (mini->token[0])
                // check if it is builtin function
                // if true execute it
                is_builtin(mini_token[0])
                    // check if the standard input is not error
                    if (mini_ > in != -1)
                        execut_commnad(mini);

            free(varialbels);
        }
    }

    void execute_command(mini)
    {
        pid_t pid;

        // create a fork

        pid = fork();
        run_signal(2);

        if (pid == -1)
        {
            printf("fork error");
            exitstatus = 127;
        }
        if (pid == 0)
        {
            file_descriptor_handler(in, out);
            exitstatus = 127;
            ft_execute_pipe(mini); // execute the command
            exit(exitstatus);
        }
        else
        {
            waitpid(pid, &exitstatus, WUNTRACED);
            if (wifexitd(exit))
                exitstatus = wexitstatus(exitstatus);
        }
    }

    void ft_execute_pipe(mini)
    {
        if (mini->token[0]) // if the first commnad is true
        {
            exitstatus = execve(mini->token[0], &mini - token[0], mine->env)
            // some action to be decided later
        }
    }

    int file_descriptor_handler(int in, int out)
    {
        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if (out != 1)
        {
            dup2(out, 1);
            close(out);
        }
        return (0);
    }

    /*     void	redirect_in(t_struct *mini, int j, char *aux)
    {
        char	**file;

        if (mini->commands[j][0] == '<')
        {
            file = NULL;
            if (mini->commands[j][1] == '<')
                file = double_redir(mini, file, j);
            else
            {
                file = ft_split(&mini->commands[j][1], ' ');
                mini->in_fd = open(file[0], O_RDONLY, 0777);
                if (mini->in_fd == -1 && mini->error_name_file == NULL)
                    mini->error_name_file = ft_strdup(file[0]);
            }
            aux = ft_strtrim(mini->line, " ");
            if (mini->split.n_comand == 1 || (aux[0] == '|'
                    && ft_strlen(aux) == 1))
            {
                free(mini->line);
                mini->line = new_comman(1, file);
            }
            free(aux);
            mini->last_redir = 0;
            free_char_array(file);
        }
    }

    char	**double_redir(t_struct *mini, char **file, int j)
    {
        file = ft_split(&mini->commands[j][2], ' ');
        read_until (file[0]);
        mini->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
        mini->name_file = ft_strdup(file[0]);
        mini->is_append++;
        return (file);
    }

    void	read_until(char *end)
    {
        char	*line;
        int		flags;
        int		fd;

        flags = O_WRONLY | O_CREAT | O_TRUNC;
        line = ft_strdup("");
        fd = open(end, flags, 0777);
        while (ft_strncmp(line, end, ft_strlen(end))
            || ft_strlen(line) != ft_strlen(end))
        {
            free(line);
            line = readline("> ");
            if (ft_strlen(line) != ft_strlen(end))
                ft_putendl_fd(line, fd);
        }
        close(fd);
        free(line);
    }

    char	*new_comman(int i, char **str)
    {
        char	*aux;

        aux = ft_strdup("");
        while (str[i] != NULL)
        {
            if (ft_strlen(aux) > 0)
                aux = ft_strjoin(aux, " ");
            aux = ft_strjoin(aux, str[i]);
            i++;
        }
        return (aux);
    }


    void	redirect_out(t_struct *mini, int j)
    {
        int		flags;
        char	*file;

        flags = O_WRONLY | O_CREAT;
        j = mini->c;
        if (mini->commands[j] && mini->commands[j][0] == '>')
        {
            if (mini->commands[j] && mini->commands[j][1] == '>')
            {
                file = ft_strtrim(&mini->commands[j][2], " ");
                mini->out_fd = open(file, flags | O_APPEND, 0777);
                free (file);
            }
            else
                simple_redir_out(mini, j, flags);
            mini->last_redir = 1;
            if (mini->split.n_comand == 1)
                free(mini->line);
        }
    }

    void	simple_redir_out(t_struct *mini, int j, int flags)
    {
        char	*aux;
        char	*file;

        aux = ft_strtrim(&mini->commands[j][1], " ");
        file = ft_substr(aux, 0, find_char(aux, ' '));
        mini->out_fd = open(file, flags | O_TRUNC, 0777);
        free (aux);
        free (file);
    }

    int	find_char(char *string, char needle)
    {
        int	i;

        i = 0;
        while (string[i])
        {
            if (string[i] == needle)
                return (i);
            i++;
        }
        return (i);
    } */
