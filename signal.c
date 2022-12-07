#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
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

int main(int argc, char **argv)
{
    char **path;
    char **cmd;
	int len;
	cmd = ft_split(argv[1], '|');
    len = arrlen(cmd);

    int fid[len];
    int i;


    for (i = 0; i < len; i++)
	{
		fid[i] = fork();
		if (fid[i] == -1)
        	return (120);
		if (fid[i] == 0)
		{
			path = ft_split(cmd[i], ' ');
			if (execvp(path[0], path) == -1)
				return (4);
		//	return (0);
		}
	}
	wait(NULL);

/*  	for (i = 0; i < len; i++)
	{
	
 		int status;          
		waitpid(fid[i], &status, 0);

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
		} 
		
    }   */

    return (0);
}

