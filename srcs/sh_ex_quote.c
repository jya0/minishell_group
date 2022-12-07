#include "../includes/sh_executor.h"

int sh_ps_issinglequote(char c)
{
    if (c == 39)
        return (1);
    return (0);
}

int sh_ps_isdoublequote(char c)
{
    if (c == 34)
        return (1);
    return (0);
}

int sh_ps_isescape(char c)
{
    if (c == 27)
        return (1);
    return (0);
}

int sh_ps_isquoted(char c)
{
    if (sh_ps_issinglequote(c) || sh_ps_isdoublequote(c))
        return (1);
    return (0);
}

char *sh_ps_removequote(char *str)
{
    int len;

    len = ft_strlen(str);
    if (str)
    {
        if ((sh_ps_issinglequote(str[0]) && sh_ps_issinglequote(str[len - 1]))
            || (sh_ps_isdoublequote(str[0]) && sh_ps_isdoublequote(str[len - 1])))
            return (ft_substr(str, 1, (len - 2)));
        else
            return (str);
    }
    return (str);
}

int sh_ps_issinglequotedarg(char *str)
{
    int len;

    len = ft_strlen(str);
    if (str)
    {
        if (sh_ps_issinglequote(str[0]) && sh_ps_issinglequote(str[len - 1]))
            return (1);
    }
    return (0);
}

int sh_ps_isvalidname(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9') || (c == '_'))
        return (1);
    return (0);
}

/* 
int main(int argc, char **argv)
{
    printf("%s\n", sh_ps_removequote(argv[1]));
    return (0);
} */