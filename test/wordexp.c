#include "shell.h"

t_word_s *make_word(char *str)
{
    t_word_s *word = malloc(sizeof(t_word_s));
    if (!word)
        return NULL;
    size_t len = strlen(str);
    char *data = malloc(len + 1);

    if (!data)
    {
        free(word);
        return (NULL);
    }

    strcpy(data, str);
    word->data = data;
    word->len = len;
    word->next = NULL;
    
    return word;
}

void free_all_words(t_word_s *first)
{
    while (first)
    {
        t_word_s *cur;
        cur = first->next;
        if (first->data)
        {
            free(first->data);
            free(first);
        }
        first = cur;
    }
}

char *wordlist_to_str(t_word_s *word)
{
    if (!word)
        return NULL;

    t_word_s *w = word;
    char *str;
    int len = 0;

    while (w)
    {
        len += w->len + 1;
        w = w->next;
    }

    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    w = word;
    char *str2 = str;
    while (w)
    {
        sprintf(str2 , "%s ", w->data);
        str2 += w->len + 1;
        word = word->next;
    }
    str2[-1] = '\0';
    return (str);
}

void delete_char_at(char *str, size_t index)
{
    if (!str)
        return ;
    size_t len = strlen(str);
    size_t i, j;
    i = 0;
    j = 0;

    char *str2 = malloc(len);

    while (str[i])
    {
        if (i == index)
        {
            i++;
            continue;
        }
        str2[j++] = str[i++];
    }
    str2[j] = '\0';
    memset(str, 0, strlen(str2));
    strcpy(str, str2);
    free(str2);
}

int is_name(char *str)
{
    if (!str)
        return (0);
    while (*str)
    {
        if (!isalnum(*str) || *str != '_')
            return (0);
        *str++;
    }
    return (1);
}

size_t find_closing_quote(char *data)
{
    if (!data)
        return (0);
    size_t i = 0;
    char quote = data[i];
    if (quote != 34 && quote != 39 && quote != 96)
        return (0);
    i++;
    while (data[i])
    {
        if (data[i] == quote)
        {
            if (data[i - 1] == 92)
                if (quote != 39)
                    continue;
            return (i);
        }
        i++;
    }
    return (0);
}

char *substitute_str(char *s1, char *s2, size_t start, size_t end)
{
    if (!s1 || !s2)
        return NULL;
    size_t i = 0;
    size_t j = 0;
    char *exp_str = NULL;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    size_t len = (len1 - (end - start)) + len2; 

    exp_str = malloc(sizeof(char) * (len + 1));
    if (!exp_str)
        return (NULL);
    while (i < start)
    {
        exp_str[i] = s1[i];
        i++;
    }   
    while (j < strlen(s2))
        exp_str[i++] = s2[j++];
    while (end < strlen(s1))
        exp_str[i++] = s1[end++];

    return (exp_str);
}

char *tilde_expand(char *s)
{
    if (!s)
        return NULL;
    char *home = getenv("HOME");
    char *sub = NULL;

    if ((s[0] == '~') && (s[1] == '/'))
        sub = ft_substr(s, 2, strlen(s));
    else if (s[0] == '~')   
        sub = ft_substr(s, 1, strlen(s));
    
    if (sub)
    {
        char *str = malloc(sizeof(char) * (strlen(home) + strlen(sub) + 2));
        if (!str)
            return NULL;
        strcpy(str, home);
        strcat(str, "/");
        strcat(str, sub);
        return (str);
    }
    return (NULL);
}

char *var_expand(char *orig_var_name)
{
    if (!orig_var_name)
        return (NULL);
    char *word = NULL;
    int start = 0;
    int i = 0;
    while (orig_var_name[i])
    {
        if (orig_var_name[i] == '$')
        {
            start = i + 1;
            i++;
        }
        if (!isalnum(orig_var_name[i]))
            word = ft_substr(orig_var_name, start, i);
        i++;
    }
    
    char *new_str = substitute_str(orig_var_name, )
}
