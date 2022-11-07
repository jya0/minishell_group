#include "shell.h"

void ft_ungetchar(t_src *tsrc)
{
    if (tsrc->curpos < 0)
        return;
    tsrc->curpos--;
}

char ft_nextchar(t_src *tsrc)
{
    if (!tsrc || !tsrc->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }

    char c1 = 0;
    if (tsrc->curpos == INIT_SRC_POS)
    {
        tsrc->curpos = -1;
    }
    else
    {
        c1 = tsrc->buffer[tsrc->curpos];
    }

    if (++tsrc->curpos >= tsrc->bufsize)
    {
        tsrc->curpos = tsrc->bufsize;
        return EOF;
    }
    return (tsrc->buffer[tsrc->curpos]);
}

char ft_peekchar(t_src *tsrc)
{
    if (!tsrc || !tsrc->buffer)
    {

        errno = ENODATA;
        return ERRCHAR;
    }

    long pos = tsrc->curpos;
    if (pos == INIT_SRC_POS)
    {
        pos++;
    }
    pos++;

    if (pos >= tsrc->bufsize)
    {
        return EOF;
    }
    return (tsrc->buffer[pos]);
}

void ft_skipwhihtcspace(t_src *tsrc)
{
    char c;

    if (!tsrc || !tsrc->buffer)
        return;
    
    while ((c = ft_peekchar(tsrc) != EOF)
             && (c == ' ' || c == '\t'))
    {
        ft_nextchar(tsrc);
    }
}
