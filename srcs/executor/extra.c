/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyohann <yoyohann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 03:27:22 by yoyohann          #+#    #+#             */
/*   Updated: 2023/01/03 19:27:37 by yoyohann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sh_ps_changearg(t_shell_s *shell, t_echo *echo, char *arg)
{
    if (sh_ps_issinglequotedarg(arg))
    {
        shell->echovar = sh_ps_removequote(arg);
        return;
    }
    else if (ft_strcmp(arg, "$?") == 0)
    {
        shell->echovar = "$?";
        return;
    }
    else
    {
        echo->str = sh_ps_removequote(arg);
        while (echo->i < ft_strlen(echo->str))
        {
            if (echo->str[echo->i] == '$')
            {
                echo->j = echo->i + 1;
                while (sh_ps_isvalidname(echo->str[echo->j]) && echo->j < ft_strlen(echo->str))
                    echo->j++;
                echo->key = ft_substr(echo->str, echo->i + 1, (echo->j - echo->i - 1));
                echo->key1 = sh_ex_searchenvvar(shell, echo->key);
                if (echo->key1 != NULL)
                    echo->str1 = ft_strjoin(echo->str1, echo->key1);
                echo->i = echo->j - 1;
            }
            else
                echo->str1 = ft_charjoin(echo->str1, echo->str[echo->i]);
            echo->i++;
        }
    }
    shell->echovar = echo->str1;
}

void sh_ex_display(t_shell_s *shell)
{
    int i = 0;
    while (i < shell->num_commands)
    {
        printf("%s\n", shell->commands[i]);
        i++;
    }
}

void sh_ex_displayarray(char **commands)
{
    int i = 0;
    while (commands[i])
    {
        printf("%s\n", commands[i]);
        i++;
    }
}

char *ft_charjoin(char const *s1, char c)
{
    int i;
    int l_s1;

    char *join;

    if (s1 == NULL)
    {
        i = 0;
        join = (char *)malloc(sizeof(char) * (1 + 1));
        join[i++] = c;
        join[i] = '\0';
        return (join);
    }
    else
    {
        l_s1 = ft_strlen(s1);
        join = (char *)malloc(sizeof(char) * (l_s1 + 1 + 1));
        if (join == 0)
            return (NULL);
        i = 0;
        while (s1[i])
        {
            join[i] = s1[i];
            i++;
        }
        join[i++] = c;
        join[i] = '\0';
        return (join);
    }
}

int ft_chrfound(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int sh_ex_listlen(t_commands *command)
{
    int i;

    i = 0;
    while (command)
    {
        command = command->next;
        i++;
    }
    return (i);
}

void sh_display(t_commands *command)
{
    while (command)
    {
        printf("commands %s \n", command->cmd_name);
        command = command->next;
    }
}

void sh_dispred(t_redirections *redirs)
{
    while (redirs)
    {
        printf("redir %s\n", redirs->redir_file);
            redirs = redirs->next;
    }
}
int sh_ex_pipecount(t_commands *command)
{
    int i;
    i = 0;
    while (command->next)
    {
        if (command->redirs == NULL && command->redirs == NULL)
            i++;
        command = command->next;
    }
    return (i);
}

int sh_count(t_words *word)
{
    int i = 0;
    while (word)
    {
        if (word->term_type == TT_PIPE)
            i++;
        word = word->next;
    }
    return (i);
}

char *sh_ex_fileout(t_commands *command)
{
    t_redirections *redir;
    redir = command->redirs;

    while (redir->next)
        redir = redir->next;
    return (redir->redir_file);
}

char *sh_ex_filein(t_commands *command)
{
    t_redirections *redir;
    redir = command->redirs;

    while (redir->next)
        redir = redir->next;
    return (redir->redir_file);
}