#ifndef TREES
#define TREES

#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

typedef struct t_node {
    void *value;
    struct t_node *left, *right;
    short height;
} t_node;

t_node *new_node(void *);
short height(t_node *);
t_node *right_rotate(t_node *);
t_node *left_rotate(t_node *);
t_node *l_r_rotate(t_node *);
t_node *r_l_rotate(t_node *);
short get_balance(t_node *);
void *tree_lookup(t_node *, int (*cmp)(void *, void *), void *);
t_node *tree_insert(t_node *, int (*cmp)(void *, void *), void *);
t_node *min_node(t_node *);
t_node *max_node(t_node *);
t_node *tree_remove(t_node *, int (*cmp)(void *, void *), void *);
t_node *fix_balance(t_node *);
void destroy_tree(t_node *, void (*del)(void *));
void free_tree(t_node *);

#endif