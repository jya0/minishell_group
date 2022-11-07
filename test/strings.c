#include "shell.h"

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
        if (val[j] == quote)
            quoted[i++] = 92;
        quoted[i] = val[j];
        i++;
        j++;
    }
    quoted[j] = quote;
    printf("%s\n",quoted);
    return  (quoted);
}
