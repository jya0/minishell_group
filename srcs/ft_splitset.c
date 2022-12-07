#include "../includes/sh_executor.h"

static int	sh_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int sh_ex_delimeterfound(char c)
{
	if ((c == '<') || (c == '>') || (c == '|'))
		return (1);
	return (0);
}

int sh_ex_pipefound(char c)
{
	if (c == '|')
		return (1);
	return (0);
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

void sh_ex_countcommand(t_shell_s *shell)
{
	int i;
	int index;
	
	i = 0;
	index = 1;
    shell->num_commands = 0;
    shell->num_pipes = 0;
	while (shell->cmd_line[i])
	{
		if (!sh_ex_delimeterfound(shell->cmd_line[i]) && index == 1)
        {
			shell->num_commands++;
			index = 0;
        }
		else if (sh_ex_delimeterfound(shell->cmd_line[i]))
		{
		    if (sh_ex_pipefound(shell->cmd_line[i]))
                shell->num_pipes++;
			index = 1;
		}
		i++;
	}
	shell->char_count = i;
}

char	*word_dup(char *str, int start, int finish)
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

void sh_ex_splitcommands(t_shell_s *shell)
{
	int		i;
	int		j;
	int		index;
	char	*tmp_str;
	char	*tmp_str1;

	tmp_str1 = NULL;
	tmp_str = NULL;
    sh_ex_countcommand(shell);
 	shell->commands = malloc((shell->num_commands + 1) * sizeof(char *));
	if (!shell->cmd_line || !shell->commands)
		return ;; 
	i = 0;
	j = 0;
	index = -1;
	while (i <= shell->char_count)
	{
		if (!sh_ex_delimeterfound(shell->cmd_line[i]) && index < 0)
			index = i;
		else if ((sh_ex_delimeterfound(shell->cmd_line[i]) || i == shell->char_count) && index >= 0)
		{
			tmp_str = word_dup(shell->cmd_line, index, i);
			// tmp_str1 = sh_ps_trimspace(tmp_str);
			shell->commands[j++] = sh_ps_trimspace(tmp_str);

			// shell->commands[j++] = sh_ps_removequote(tmp_str);
			index = -1;
		}
		i++;
	}
	shell->commands[j] = NULL;
//	free(tmp_str1);
	free(shell->cmd_line);
}


