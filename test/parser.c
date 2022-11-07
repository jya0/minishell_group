#include "shell.h"

t_node *new_node(enum node_type_e type)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;
    
    memset(node, 0, sizeof(t_node));
    node->type = type;

    return node;
}

void add_child_node(t_node *parent, t_node *child)
{
    if (!parent || !child)
        return ;
    
    if (!parent->first_child)
        parent->first_child = child;
    else
    {
        t_node *sibling = parent->first_child;
        while (sibling->next_sibling)
            sibling = sibling->next_sibling;
        
        sibling->next_sibling = child;
        child->prev_sibling = sibling;
    }
    parent->children++;
}

void    set_node_val_str(t_node *node, char *val)
{
    node->val_type = VAL_STR;

    if (!val)
        node->val.str = NULL;
    else
    {
        char *val2 = malloc(strlen(val) + 1);

        if (!val)
            node->val.str = NULL;
        else
        {
            strcpy(val2, val);
            node->val.str = val2;
        }
    }
}

void free_node_tree(t_node *node)
{
    if (!node)
        return ;
    
    t_node *child = node->first_child;

    while (child)
    {
        t_node *next = child->next_sibling;
        free_node_tree(child);
        child = next;
    }

    if (node->val_type == VAL_STR)
    {
        if (node->val.str)
            free(node->val.str);
    }
    free(node);
}

t_node *parse_simple_command(t_token *tok)
{
    if (!tok)
        return NULL;

    t_node *cmd = new_node(NODE_COMMAND);

    if (!cmd)
    {
        free_token(tok);
        return NULL;
    }

    t_src *src = tok->src;

    do
    {
        if (tok->text[0] == '\n')
        {
            free_token(tok);
            break;
        }

        t_node *word = new_node(NODE_VAR);
        if (!word)
        {
            free_node_tree(cmd);
            free_token(tok);
            return (NULL);
        }

        set_node_val_str(word, tok->text);
        add_child_node(cmd, word);

        free_token(tok);
    } while ((tok = tokenize(src)) != &eof_token);

    return cmd;
}