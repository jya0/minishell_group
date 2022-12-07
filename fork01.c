#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static int	count_words(const char *str, char c)
{
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char *sh_ps_trimspace(char *str)
{
	int i;
	int j;
	char *sub_str;

	j = ft_strlen(str);

	i = 0; 
	while (str[i] && str[i] == ' ')
		i++;
	while (j >= 0 && str[j] == ' ')
		j--;
	sub_str = word_dup(str, i, j);
	return (sub_str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	*tmpstr;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			tmpstr = word_dup(s, index, i);
			split[j++] = sh_ps_trimspace(tmpstr);
			index = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

int arrlen(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

/* 
int main()
{
    pid_t pid;
    int fd[2];
    int pipeid;

    pipeid = pipe(fd);
    if (pipeid == -1)
        exit(EXIT_FAILURE);

    pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0)
    {
        close(fd[0]);
        int n;
        printf("Enter a number: ");
        scanf("%d",&n);
        if (write(fd[1], &n, sizeof(int)) == -1)
            exit(EXIT_FAILURE);
        close(fd[1]);
      
    }
    else
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
            exit(EXIT_FAILURE);
        close(fd[0]);
        printf("The number is %d\n", y);
        waitpid(pid, NULL, 0);
    }
    return (0);
} */

/*  int main()
{
    pid_t pid;
    int exe;
    char *cmd[] = {"ping", "-c", "1","www.google.com", NULL};

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        int file = open("out.txt", O_WRONLY | O_CREAT , 0777);
        dup2(file, STDOUT_FILENO);
        close(file);
        exe = execvp(cmd[0], cmd);
        if (exe == -1)
        {
            printf("Error executing\n");
            return (exe);
        }
    }
     else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
        printf("Exit code %d\n", status);
    }
    return (0);
}  */
/* 
  int main()
{
    char *cmd[] = {"ping -c 3 google.com", "grep packets", NULL};
    pid_t pid1, pid2;
    int fd[2];
    int pipeid;
    char **path;

    pipeid = pipe(fd);
    if (pipeid == -1)
        return (1);
    // fd[1] = STDOUT_FILENO;
    // fd[0] = STDIN_FILENO;

    pid1 = fork();
    if (pid1 == -1)
        return (3);
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        path = ft_split(cmd[0], ' ');
        execvp(path[0], path);
    }

    pid2 = fork();
    if (pid2 == -1)
        return (5);
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        path = ft_split(cmd[1], ' ');
        execvp(path[0], path);
    }

    close(fd[1]);
    close(fd[0]);
    waitpid(pid1, NULL, 0); 
    return (0);


}   */


/* int main()
{
    int len;
    char *cmd[] = {"ping -c 3 google.com", "grep packets","wc -l", NULL};
    char **path;
    len = arrlen(cmd);
    int tmpin = dup(0);
    int tmpout = dup(1);
    char *infile, *outfile;

    infile = NULL;
    outfile = NULL;

    int fdin;

    if (infile)
        fdin = open(infile, O_RDONLY);
    else
        fdin = dup(tmpin);

     int ret;
     int fdout;

     for (int i = 0; i < len; i++)
     {
         dup2(fdin, 0);
         close(fdin);

         if (i == len - 1)
         {
            if (outfile)
                fdout = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
            else
                fdout = dup(tmpout);
         }
         else
         {
            int fd[2];
            pipe(fd);
            fdout = fd[1];
            fdin = fd[0];
         }
         dup2(fdout, 1);
         close(fdout);

         ret = fork();
         if (ret == 0)
         {
            path = ft_split(cmd[i], ' ');
            execvp(path[0], path);
         }
     }
     dup2(tmpin, 0);
     dup2(tmpout, 1);
     close(tmpin);
     close(tmpout);

     waitpid(ret, NULL, 0);
    return (0);
} */


int main()
{
    char *cmd[] = {"ping -c 3 google.com", "grep packets", NULL};
    int len = arrlen(cmd);
    pid_t pid;
    int fd[2];
    int pipeid;
    char **path;

    int tmpin = dup(STDIN_FILENO);
    int tmpout = dup(STDOUT_FILENO);

    int fdin;
    int fdout;

    fdin = dup(tmpin);
    fdout = dup(tmpout);
    for (int i = 0; i < len; i++)
    {
        dup2(fdin, STDIN_FILENO);
        close(fdin);

        pipe(fd);
        fdout = fd[1];
        fdin = fd[0];

        dup2(fdout, STDOUT_FILENO);
        close(fdout);

        pid = fork();
        if (pid == 0)
        {
            path = ft_split(cmd[i], ' ');
            execvp(path[0], path);
        }
    }
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    waitpid(pid, NULL, 0);
    return (0);
}  