#ifndef linked_list_h_330
#define linked_list_h_330


/* First is only valid for the last value - If the first value of the 
list is deleted, all other first are not valid */
typedef struct node{
    char *value;
    struct node *next, *prev, *first; 
    int size;
} *Node_ptr;


/* Initialize the list */
Node_ptr init();

/* Push a value to the top of the list */
Node_ptr push(char *value, Node_ptr top);

/*  Check if the list is empty */
int is_empty(Node_ptr top);

/* Delete the value at a certain index */
Node_ptr delete_index(int index, Node_ptr top);

/* Delete all of the values in the list */
void clear_all(Node_ptr top);

/* Print all of the values (if flag set to 1 the direction will be right to left) */
void print_all(int side_flag, Node_ptr top);

/* Return the pointer to the node corresponding to the given index */
Node_ptr get_index(int index, Node_ptr top);







#endif
