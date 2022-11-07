#include "shell.h"

char *tok_buf = NULL;
int tok_bufsize = 0;
int tok_bufindex = -1;

t_token eof_token = 
{
    .text_len = 0,
};

void add_to_buf(char c)
{
    tok_buf[tok_bufindex++] = c;

    if (tok_bufindex >= tok_bufsize)
    {
        char *temp = realloc(tok_buf, tok_bufsize * 2);

        if (!temp)
        {
            errno = ENOMEM;
            return;
        }
        tok_buf = temp;
        tok_bufsize *= 2;
    }
}

t_token *create_token(char *str)
{
    t_token *tok = malloc(sizeof(t_token));

    if (!tok)
        return NULL;
    memset(tok, 0, sizeof(t_token));

    tok->text_len = strlen(str);

    char *nstr = malloc(sizeof(char) * (tok->text_len + 1));

    if (!nstr)
    {
        free(nstr);
        return NULL;
    }

    strcpy(nstr, str);
    tok->text = nstr;

    return (tok);
}

void free_token(t_token *tok)
{
    if (tok->text)
        free(tok->text);
    free(tok);
}

t_token *tokenize(t_src *src)
{
    int endloop = 0;

    if (!src || !src->buffer || !src->bufsize)
    {
        errno = ENODATA;
        return &eof_token;
    }

    if (!tok_buf)
    {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if (!tok_buf)
        {
            errno = ENOMEM;
            return &eof_token;
        }
    }

    tok_bufindex = 0;
    tok_buf[0] = '\0';

    char nc = ft_nextchar(src);
    if (nc == ERRCHAR || nc == EOF)
        return &eof_token;
    
    do
    {
        switch(nc)
        {
            case ' ':
            case '\t':
                if (tok_bufindex > 0)
                    endloop = 1;
                break;
            case '\n':
                if (tok_bufindex > 0)
                    ft_ungetchar(src);
                else
                    add_to_buf(nc);
                endloop = 1;
                break;
            default :
                add_to_buf(nc);
                break;
        }
        if (endloop)
            break;
    }while((nc = ft_nextchar(src)) != EOF);

    if (tok_bufindex == 0)
        return  &eof_token;
    
    if (tok_bufindex >= tok_bufsize)
        tok_bufindex--;
    
    tok_buf[tok_bufindex] = '\0';

    t_token *tok = create_token(tok_buf);

    if(!tok)
    {
        printf("Error allocating memory\n");
        return &eof_token;
    }
    
    tok->src = src;
    return tok;
} 

