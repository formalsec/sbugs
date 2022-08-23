#include "trees.h"

/* Creates a new tree node and returns a pointer to it                        */
t_node *new_node(void *value){
    t_node *new;

    new = (t_node*) malloc(sizeof(t_node));
    new->value = value;
    new->left = new->right = NULL;
    new->height = 1;

    return new;
}

/* Returns height of a tree node                                              */
short height(t_node *target){
    if (target == NULL){
        return 0;
    }
    return target->height;
}

/* Rotates tree around given node                                             */
t_node *right_rotate(t_node *y){
    t_node *x = y->left;

    y->left = x->right;
    x->right = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

/* Rotates tree around given node                                             */
t_node *left_rotate(t_node *y){
    t_node *x = y->right;

    y->right = x->left;
    x->left = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

/* Rotates tree around the child of the given node and then the node itself   */
t_node *l_r_rotate(t_node *root){
    if (root == NULL){
        return root;
    }
    root->left = left_rotate(root->left);
    return right_rotate(root);
}

/* Rotates tree around the child of the given node and then the node itself   */
t_node *r_l_rotate(t_node *root){
    if (root == NULL){
        return root;
    }
    root->right = right_rotate(root->right);
    return left_rotate(root);
}

/* Calculates balance factor of a given node                                  */
short get_balance(t_node *node){
    if(node == NULL){
        return 0;
    }
    return height(node->left) - height(node->right);
}

/* Goes through BST and, using a given compare function, returns query result */
void *tree_lookup(t_node *root, int (*cmp)(void *val, void *nd), void *value){
    t_node *cursor = root;
    short dif;

    while (cursor != NULL && (dif = cmp(value, cursor->value)) != 0){
        if (dif < 0)
            cursor = cursor->left;
        else
            cursor = cursor->right;
    }
    return cursor ? cursor->value : NULL;
}

/* Returns the furthest left node of a given BST                              */
t_node *min_node(t_node* root){ 
    t_node* current = root;

    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

/* Returns the furthest right node of a given BST                             */
t_node *max_node(t_node* root){ 
    t_node* current = root;

    while (current->right != NULL){
        current = current->right;
    }
    return current;
}

/* Goes through BST and, using a given compare function, inserts given value  */
t_node *tree_insert(t_node *root, int (*cmp)(void *val, void *nod), void *value){
    if (root == NULL){
        return new_node(value);
    }

    if(cmp(value, root->value) < 0)
        root->left = tree_insert(root->left, cmp, value);
    else
        root->right = tree_insert(root->right, cmp, value);

    root = fix_balance(root);
    return root;
}

/* Goes through BST and, using a given compare function, removes given value  */
t_node *tree_remove(t_node *root, int (*cmp)(void *val, void *nd), void *value){
    t_node *temp, *aux;

    if(root == NULL)
        return root;

    if(cmp(value, root->value) < 0)
        root->left = tree_remove(root->left, cmp, value);
    else if(cmp(value, root->value) > 0)
        root->right = tree_remove(root->right, cmp, value);
    else {
        /* less than two children */
        if (root->left == NULL || root->right == NULL){
           temp = root;
           root = root->left ? root->left : root->right;
           free(temp);
        }
        else {
            /* has two children */  
            temp = min_node(root->right);
            aux = root->value;
            root->value = temp->value;
            temp->value = aux;
            root->right = tree_remove(root->right, cmp, temp->value);
        }
    }
    if (root == NULL)
        return root;

    root = fix_balance(root);
    return root;
}

/* Rebalances tree                                                            */
t_node *fix_balance(t_node *root){
    short bal;

    if (root == NULL){
        return root;
    }
    bal = get_balance(root);

    if (bal > 1){
        if (get_balance(root->left) >= 0)
            root = right_rotate(root);
        else
            root = l_r_rotate(root);
    }
    else if (bal < -1){
        if (get_balance(root->right) <= 0)
            root = left_rotate(root);
        else
            root = r_l_rotate(root);
    }
    else {
        root->height = max(height(root->left), height(root->right)) + 1;
    }
    return root;
}

/* Destroys tree using given function to destroy the value of each node       */
void destroy_tree(t_node *root, void (*del)(void *nd)){
    if(root == NULL){
        return;
    }
    destroy_tree(root->left, del);
    destroy_tree(root->right, del);
    del(root->value);
    free(root);
    return;
}

/* Frees each node of the tree, without doing anything to what they point to  */
void free_tree(t_node *root){
    if(root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
    return;
}