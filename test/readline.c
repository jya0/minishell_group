#include "shell.h"

void print_prompt1(void)
{
//    fprintf(stderr, "yonas @>> ");
    symtab_entry_s *entry = get_symtab_entry("PS1");
    if (entry && entry->val)
        fprintf(stderr, "%s", entry->val);
    else
        fprintf(stderr, "$ ");
}

void print_prompt2(void)
{
//    fprintf(stderr, "> ");
    symtab_entry_s *entry = get_symtab_entry("PS1");
    if (entry && entry->val)
        fprintf(stderr, "%s", entry->val);
    else
        fprintf(stderr, "> ");
}

char *read_cmd(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while (fgets(buf, 1024, stdin))
    {
        int buflen = strlen(buf);
         if (!ptr)
            ptr = malloc(buflen + 1); 
         else
        {
            char *ptr2 = realloc(ptr, ptrlen + buflen +  1);

            if (ptr2)
                ptr = ptr2;
            else
            {
                free(ptr);
                ptr = NULL;
            }
        } 

        if (!ptr)
        {
            printf("Error allocating memory\n");
            return (NULL);
        }
        strcpy (ptr + ptrlen , buf);

        if (buf[buflen - 1] == '\n')
        {
            if (buflen == 1 || buf[buflen - 2] != '\\')
                return (ptr);
        
        ptr[ptrlen + buflen - 2] = '\0';
        buflen  -= 2;
        print_prompt2();
        }

        ptrlen += buflen;
    }
    return  ptr;
}

int parse_and_execute(t_src *src)
{
    ft_skipwhihtcspace(src);

    t_token *tok = tokenize(src);
    if (tok == &eof_token)
        return 0;

    while (tok && tok != &eof_token)
    {
        t_node *cmd = parse_simple_command(tok);

        if (!cmd)
            break;
        
        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }
    return 1;
}
