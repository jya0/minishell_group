#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pwd.h>

typedef struct t_word_s
{
    int len;
    char *name;
    struct t_word_s *next;
}   t_word_s;


typedef struct t_envval_s
{
    char *key;
    char *value;
    struct t_envval_s *next;
}   t_envval_s;

int errro_msg(char *str, int i)
{
    printf("%s\n", str);
    return (i);
}

void display_node(t_word_s *word)
{
    int i = 0;
    while(word)
    {
        printf("[%04d] %s [%d]\n", i++, word->name, word->len);
        word = word->next;
    }
}

void display_env_node(t_envval_s *envt)
{
    int i = 0;
    while(envt)
    {
        printf("[%04d] %s %s\n", i++, envt->key, envt->value);
        envt = envt->next;
    }
}


int size_of_node(t_word_s *word)
{
    int i;

    i = 0;
    while (word)
    {
        word = word->next;
        i++;
    }
    return (i);
}

void    free_node(t_word_s **word)
{
    t_word_s *head;
    head = *word;

    if (!head || !word)
        return ;

    while (head)
    {
        if (head->name)
            free(head->name);
        t_word_s *cur = head->next;
        free(head);
        head = cur;
    }
}

t_word_s *new_word(char *str)
{
    t_word_s *head = malloc(sizeof(t_word_s));
    if (!head)
        errro_msg("Error allocating new node memory", 1);

    
    if (!str)
    {
        free(head);
        return (NULL);
    }

    int len = strlen(str);
    char *name = malloc(sizeof(char) * (len + 1));

    if (!name)
    {
    //    free(head);
        errro_msg("Error allocating data memory", 2);
    }

    strcpy(name, str);
    head->name = name;
    head->len = len;
    head->next = NULL;

    return head;
}


void add_node(t_word_s **word, char *str)
{
    t_word_s *head, *tail;
    head = *word;

    tail = new_word(str);
    if (word && head)
    {
        if (!head)
            *word = tail;
        else
        {
            while (head->next != NULL)
                head = head->next;
            head->next = tail;
        }
    }
}

int search_node(t_word_s *word, char *str)
{
    if (!str || !word)
        return 0;
    while (word)
    {
        if (strcmp(word->name, str) == 0)
            return (1);
        word = word->next;
    }
    return (0);
}


char *wordlist_to_str(t_word_s *word)
{
    if (!word)
        return NULL;
    t_word_s *w;
    char *str;
    int len = 0;

    w = word;
    while (w)
    {
        len += w->len + 1;
        w = w->next;
    }

    printf("%d\n", len);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    char *str2 = str;

    w = word;
    while (w)
    {
        sprintf(str2, "%s ", w->name);
        str2 += w->len + 1;
    //    strcat(str2, w->name);
    //    strcat(str2, " ");
        w = w->next;
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
    int i = 0;
    while (str[i])
    {
        if (!isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
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

size_t find_closing_brace(char *data)
{
    if (!data)
        return (0);
    size_t i = 0;
    char brace = data[0];

    if (brace != 40 && brace != 91 && brace != 123)
        return 0;
    size_t len = strlen(data);
    while (++i < len)
    {
        if (brace == 40)
        {
            if (data[i] == 41)
            {
                if (data[i - 1] == 92)
                    continue;
                return (i);
            }
        }
        else if (brace == 91)
        {
            if (data[i] == 93)
            {
                if (data[i - 1] == 92)
                    continue;
                return (i);
            }
        }
        else if (brace == 123)
        {
            if (data[i] == 125)
            {
                if (data[i - 1] == 92)
                    continue;
                return (i);
            }
        }
    }
    return (0);
}
/* size_t find_closing_quote(char *data)
{
    size_t i = 0;
    int q1 = 0;
    int q2 = 0;
    int q3 = 0;


    if (!data)
        return (0);
    while (data[i])
    {
        if (data[i] == 34)
            q1++;
        else if (data[i] == 39)
            q2++;
        else if (data[i] == 96)
            q3++;
        i++;
    }
    if ((q1 % 2 == 0) && (q2 % 2 == 0) && (q3 % 2 == 0))
        return (1);
    return (0);
} */

/* char *substitute_str(char *s1, char *s2, size_t start, size_t end)
{
    size_t i = 0;
    size_t j = 0;
    char *exp_str;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = end - start;

    size_t len = (len1 - len3) + len2;

    exp_str = malloc(sizeof(char) * (len + 1));
    if (!exp_str)
        return (NULL);
    while (i < start)
    {
        exp_str[i] = s1[i];
        i++;
    }
    while (j < len2)
    {
        exp_str[i] = s2[j];
        i++;
        j++;
    }
    while (end < len1)
    {
        exp_str[i] = s1[end];
        i++;
        end++;
    }

    printf("%s\n", exp_str);
    return (exp_str);
}
 */
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

char *strchr_any(char *string, char *chars)
{
    int i = 0;
    int j;

    if (!string)
        return (NULL);
    while (string[i])
    {
        j = 0;
        while (chars[j])
        {
            if (string[i] == chars[j])
                return (&string[i]);
            j++;
        }
        i++;
    }
    return (NULL);
}
char *quote_val(char *val, int add_quotes)
{
    if (!val)
        return NULL;
    
    int i = 0;
    int j = 0;
    char *quoted = malloc(sizeof(char) * (strlen(val) + 3));
    if (!quoted)
        return NULL;
    char quote = (char)add_quotes;
    quoted[i++] = quote;

    while (val[j])
    {
        if ((val[j] == 34) || (val[j] == 39) || (val[j] == 96))
            quoted[i++] = 92;
        quoted[i++] = val[j++];
    //    i++;
    //    j++;
    }
    quoted[i++] = quote;
    quoted[i] = '\0';

    printf("%s\n",quoted);
    return  (quoted);
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

char *get_key(char *str)
{
    if (!str)
        return NULL;
    char *key = NULL;

    int i = 0;
    while (str[i] != '=')
        i++;
    key = malloc(sizeof(char) * (i + 1));
    if (!key)
        return NULL;
    i = 0;
    while (str[i] != '=')
    {
        key[i] = str[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

char *get_value(char *str)
{
    if (!str)
        return NULL;
    
    int i = 0;
    int j = 0;
    while (str[i] != '=')
        i++;
    
    i++;
    char *value = NULL;
    int len = strlen(str);
    value = malloc(sizeof(char) * (len - i + 1));
    if (!value)
        return NULL;
    while (i < len)
        value[j++] = str[i++];
    value[j] = '\0';
    return (value);
}

//t_envval_s *ft_environ(t_envval_s **envt, char **env)
/* 
t_envval_s *new_tenv(char *str)
{
    t_envval_s *tenvt;
    tenvt = malloc(sizeof(t_envval_s));

    if (!tenvt)
        return (NULL);
    tenvt->key = get_key(str);
    tenvt->value = get_value(str);
    tenvt->next = NULL;
    return (tenvt);
}

void add_envt_var(t_envval_s **tenvt, char *str)
{
    t_envval_s *head, *tail;
    head = *tenvt;
    
    tail = new_tenv(str);
    if (!tail)
        return ;
    if (tenvt && head)
    {
        if (!head)
            head = tail;
        else
        {
            while (head->next)
                head = head->next;
            head->next = tail;
        }
    }
}

 */

t_envval_s *create_env_node(char **env)
{
    int j = 0;

    t_envval_s *p, *head;

    while (env[j])
    {
        if (j == 0)
        {
            head = malloc(sizeof(t_envval_s));
            p = head;
        }
        else
        {
            p->next = malloc(sizeof(t_envval_s));
            p = p->next;
        }
        p->key = get_key(env[j]);
        p->value = get_value(env[j]);
        j++;
    }
    p->next = NULL;
    return  (head);
}

int main(int argc, char **argv, char **env)
{
   /* 
    t_word_s *word;
    char name[] = "yonas";
    char name1[] = "tolosa";
    word = new_word(name);
    add_node(&word, "yohannes");
    add_node(&word, "gebremichal");
    add_node(&word, "medihin");
    add_node(&word, "samson"); 
//    display_node(word);
//    printf("Size of the node is %d\n", size_of_node(word));

    if (search_node(word, name1))
        printf("Found %s\n", name1);
    else
        printf("Couldn't find %s\n", name1); 
//    free_node(&word);

//    char *name2;
//    char name3[] = "abcde_fghi jkl";
//    name2 = wordlist_to_str(word);
//    printf("%s\n", name3);

//    delete_char_at(name3, 0);
//    printf("%s\n", name3);

//    char name[] = "adbw"hatiis"fads";
    
    
    size_t j;
    if ((j = find_closing_quote(argv[1])) != 0)
        printf("yes %zu", j);
    else
        printf("no"); 
    
    if ((j = find_closing_brace(argv[1])) != 0)
        printf("yes %zu\n", j);
    else
        printf("no\n");



    char a[] = "${PATH}\\ls";
    char b[] = "\\bin\\lib\\dir";

    char *p = NULL;
    p = substitute_str(a, b, 0, 7);
    free(p); 

   char a[] = "hello?how are you";
   char b[] = {' ', '$', '|', '?'};
   printf("%s\n", strchr_any(a, b));
   
    char a[] = "abcd 'efgh fadi";
    char *b = quote_val(argv[1], 34);

    printf("%s\n", b);
    */
//   printf("%s\n", tilde_expand(argv[1]));
/*   char a[] = "~/test";
  char b[] = "home/yonas";
  char *c = substitute_str(a, b, 0 , 1);
  printf("%s\n", c); */

    t_envval_s *tenvt;
    tenvt = create_env_node(env);
    display_env_node(tenvt);
    return (0);
}