#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = ft_strlen(s);
	i = 0;
	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (dup == 0)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;
	unsigned int	j;

	j = 0;
	i = 0;
	sub = (char *) malloc(sizeof(char) * (len + 1));
	if (sub == 0)
		return (NULL);
	while (s[j])
	{
		if (j >= start && i < len)
		{
			sub[i] = s[j];
			i++;
		}
		j++;
	}
	sub[i] = '\0';
	return (sub);
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
	free(str);
	return (sub_str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	*temp_str;
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
			temp_str = word_dup(s, index, i);
			split[j++] = sh_ps_trimspace(temp_str);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

int sh_ex_indirfound(char c)
{
	if (c == '<')
		return (1);
	return (0);
}

int sh_ex_outdirfound(char c)
{
	if (c == '>')
		return (1);
	return (0);
}

int sh_ex_delimeterfound(char c)
{
	if ((c == '<') || (c == '>') || (c == '|'))
		return (1);
	return (0);
}
int sh_ex_firstdelimeter(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (sh_ex_delimeterfound(str[i]))
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	return (i);
}

void sh_ex_indirectfile(char *str)
{
    int i;
    char *tmpstr;
    int j;

    i = 0;
    char *indir_filename = NULL;
    while (str[i])
    {
        if (sh_ex_outdirfound(str[i]))
        {
            i++;
            break;
        }
        i++;
    }
	printf("i = %d\n", i);
    if (i < ft_strlen(str))
    {
		j = sh_ex_firstdelimeter(&str[i]);
		printf("j = %d\n", j);
     	tmpstr = word_dup(str, i , i + j);
        indir_filename = sh_ps_trimspace(tmpstr);
    }
	printf("%s\n", indir_filename);
}
 int main(int argc, char **argv)
{
	sh_ex_indirectfile(argv[1]);
	return (0);
} 