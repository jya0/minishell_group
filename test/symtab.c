#include "shell.h"

symtab_stack_s symtab_stack;
int symtab_level;

void init_symtab(void)
{
    symtab_stack.symtab_count = 1;
    symtab_level = 0;

    symtab_s *global_symtab = malloc(sizeof(symtab_s));
    if (!global_symtab)
    {
        printf("1 - Errro allocating global symbol table\n");
        exit (EXIT_FAILURE);
    }

    memset(global_symtab, 0 , sizeof(symtab_s));
    symtab_stack.global_symtab = global_symtab;
    symtab_stack.local_symtab = global_symtab;
    symtab_stack.symtab_list[0] = global_symtab;
    global_symtab->level = 0;
}

symtab_s *new_symtab(int level)
{
    symtab_s *symtab = malloc(sizeof(symtab_s));

    if (!symtab)
    {
        printf("2 - Error creating symbol table\n");
        exit (EXIT_FAILURE);
    }

    memset(symtab, 0, sizeof(symtab_s));
    symtab->level = level;
    return symtab;
}

void free_symtab(symtab_s *symtab)
{
    if (symtab == NULL)
        return ;
    
    struct symtab_entry_s *entry = symtab->first;
    while (entry)
    {
        if (entry->name)
            free(entry->name);
        if (entry->val)
            free(entry->val);
        if (entry->func_body)
            free_node_tree(entry->func_body);
        
        symtab_entry_s *next = entry->next;
        free(entry);
        entry = next;
    }

    free(symtab);
}

void dump_local_symtab(void)
{
    symtab_s *symtab = symtab_stack.local_symtab;
    int i = 0;
    int indent = symtab->level * 4;

    printf("3 - Symbol table\n");

    symtab_entry_s *entry = symtab->first;

    while (entry)
    {
        printf("%*s[%04d] %-32s '%s' \r\n", indent, " ", i++, entry->name, entry->val);
        entry = entry->next;
    }
}

symtab_entry_s *add_to_symtab(char *symbol)
{
    if (!symbol || symbol[0] == '\0')
        return NULL;
    
    symtab_s *st = symtab_stack.local_symtab;
    symtab_entry_s *entry = NULL;

    if ((entry = do_lookup(symbol, st)))
        return (entry);

    entry = malloc(sizeof(symtab_entry_s));
    if (!entry)
    {
        printf("4 - Error allocating symbol table memory\n");
        exit (EXIT_FAILURE);
    }

    memset(entry, 0 , sizeof(symtab_entry_s));
    entry->name = malloc(sizeof(strlen(symbol) + 1));

    if (!entry->name)
    {
        printf("5 - Error allocating symbol table name memory\n");
        exit (EXIT_FAILURE);
    }

    strcpy(entry->name, symbol);
    if (!st->first)
    {
        st->first = entry;
        st->last = entry;
    }
    else
    {
        st->last->next = entry;
        st->last = entry;
    }
    return entry;
}

int rem_from_symtab(symtab_entry_s *entry, symtab_s *symtab)
{
    int res = 0;
    if (entry->val)
        free(entry->val);
    if (entry->func_body)
        free_node_tree(entry->func_body);
    free(entry->name);

    if (symtab->first == entry)
    {
        symtab->first = symtab->first->next;

        if (symtab->last == entry)
            symtab->last = NULL;
        res = 1;
    }
    else
    {
        symtab_entry_s *e = symtab->first;
        symtab_entry_s *p = NULL;

        while (e && e != entry)
        {
            p = e;
            e = e->next;
        }

        if (e == entry)
        {
            p->next = entry->next;
            res = 1;
        }
    }
    free(entry);
    return (res);
}

symtab_entry_s *do_lookup(char *str, symtab_s *symtable)
{
    if (!str || !symtable)
        return NULL;
    
    symtab_entry_s *entry = symtable->first;

    while (entry)
    {
        if (strcmp(entry->name, str) == 0)
            return  entry;
        entry = entry->next;
    }
    return NULL;
}

symtab_entry_s *get_symtab_entry(char *str)
{
    int i = symtab_stack.symtab_count - 1;

    do
    {
        symtab_s *symtab = symtab_stack.symtab_list[i];
        symtab_entry_s *entry = do_lookup(str, symtab);

        if (entry)
            return (entry);
    } while (--i >= 0);
    return NULL;
}

void    symtab_entry_setval(symtab_entry_s *entry, char *val)
{
    if (entry->val)
        free(entry->val);
    
    if (!val)
        entry->val = NULL;
    else
    {
        char *val2 = malloc(strlen(val) + 1);

        if (val2)
            strcpy(val2, val);
        else
            printf("6 - Error allocating memory\n");
        
        entry->val = val2;
    }   
}

void symtab_stack_add(symtab_s *symtab)
{
    symtab_stack.symtab_list[symtab_stack.symtab_count++] = symtab;
    symtab_stack.local_symtab = symtab;
}

symtab_s *symtab_stack_push(void)
{
    symtab_s *st = new_symtab(++symtab_level);
    symtab_stack_add(st);
    return (st);
}

symtab_s *symtab_stack_pop(void)
{
    if (symtab_stack.symtab_count == 0)
        return NULL;
    
    symtab_s *st = symtab_stack.symtab_list[symtab_stack.symtab_count - 1];
    symtab_stack.symtab_list[--symtab_stack.symtab_count] = NULL;
    symtab_level--;

    if (symtab_stack.symtab_count == 0)
    {
        symtab_stack.global_symtab = NULL;
        symtab_stack.local_symtab = NULL;
    }
    else
        symtab_stack.local_symtab = symtab_stack.symtab_list[symtab_stack.symtab_count - 1];

    return (st);
}

symtab_s *get_local_symtab(void)
{
    return symtab_stack.local_symtab;
}

symtab_s *get_global_symtab(void)
{
    return symtab_stack.global_symtab;
}

symtab_stack_s *get_symtab_stack(void)
{
    return &symtab_stack;
}