#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

//#define EOF -1
#define ERRCHAR 0
#define INIT_SRC_POS -2
#define MAX_SYMTAB 256
#define FALG_EXPORT (1 << 0)

typedef struct t_src
{
    char *buffer;
    long bufsize;
    long curpos;
}   t_src;

typedef struct t_token
{
    struct t_src *src;
    int text_len;
    char *text;
}   t_token;

enum node_type_e
{
    NODE_COMMAND,
    NODE_VAR,
};

enum val_type_e
{
    VAL_SINT = 1,
    VAL_UITN,
    VAL_SLLONG,
    VAL_ULLONG,
    VAL_FLOAT,
    VAL_LDOUBLE,
    VAL_CHR,
    VAL_STR,
};

union symval_u
{
    long    sint;
    unsigned long   uuint;
    long long   sllong;
    unsigned long long ullong;
    double  sfloat;
    long double ldouble;
    char chr;
    char *str; 
};

typedef struct t_node
{
    enum node_type_e type;
    enum val_type_e val_type;
    union symval_u val;
    int children;
    struct t_node *first_child;
    struct t_node *next_sibling, *prev_sibling;
} t_node;

enum symbol_type_e
{
    SYM_STR,
    SYM_FUNC,
};

typedef struct symtab_entry_s
{
    char *name;
    enum symbol_type_e val_type;
    char *val;
    unsigned int flags;
    struct symtab_entry_s *next;
    struct t_node *func_body;
}   symtab_entry_s;

typedef struct symtab_s
{
    int level;
    struct symtab_entry_s *first, *last;
} symtab_s;

typedef struct symtab_stack_s
{
    int symtab_count;
    struct symtab_s *symtab_list[MAX_SYMTAB];
    struct symtab_s *global_symtab, *local_symtab;
}   symtab_stack_s;

typedef struct t_builtins_s
{
    char *name;
    int (*func)(int argc, char **argv);
} t_builtins_s;

typedef struct t_word_s
{
    char *data;
    int len;
    struct t_word_s *next;
}   t_word_s;


extern t_builtins_s builtins[];
extern int builtins_count;

extern struct t_token eof_token;
void ft_skipwhihtcspace(t_src *tsrc);
char ft_peekchar(t_src *tsrc);
char ft_nextchar(t_src *tsrc);
void ft_ungetchar(t_src *tsrc);
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
void add_to_buf(char c);
t_token *create_token(char *str);
t_token *tokenize(t_src *src);
void free_token(t_token *tok);
t_node *parse_simple_command(t_token *tok);
t_node *new_node(enum node_type_e type);
void add_child_node(t_node *parent, t_node *child);
void    set_node_val_str(t_node *node, char *val);
void free_node_tree(t_node *node);
char *search_path(char *file);
int do_exec_cmd(int argc, char **argv);
static inline void free_argv(int argc, char **argv);
int do_simple_command(t_node *node);
int parse_and_execute(t_src *src);


void init_symtab(void);
symtab_s *new_symtab(int level);
void free_symtab(symtab_s *symtab);
void dump_local_symtab(void);
symtab_entry_s *add_to_symtab(char *symbol);
int rem_from_symtab(symtab_entry_s *entry, symtab_s *symtab);
symtab_entry_s *do_lookup(char *str, symtab_s *symtable);
symtab_entry_s *get_symtab_entry(char *str);
void    symtab_entry_setval(symtab_entry_s *entry, char *val);
void symtab_stack_add(symtab_s *symtab);
symtab_s *symtab_stack_push(void);
symtab_s *symtab_stack_pop(void);
symtab_s *get_local_symtab(void);
symtab_s *get_global_symtab(void);
symtab_stack_s *get_symtab_stack(void);

void initsh(void);

int dump(int argc, char **argv);


#endif