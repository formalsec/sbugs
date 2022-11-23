#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "team_struct.h"

/*CORE FUNCTIONS*/
/*Initializes the AVL tree.*/
void init_tree(team_node * node)
{
    *node = NULL;
}

/*Frees the AVL tree responsible for storing teams.*/
void free_teams(team_node node)
{
    if(node != NULL)
    {
        free_teams(node->left);
        free_teams(node->right);
        free_team(node->team);
        free(node);
    }
}

/*Returns the height of a given AVL tree node.*/
int height(team_node node)
{
    if(node == NULL)
    {
        return 0;
    }
    return node->height;
}

/*Returns the largest of two given integers.*/
int max(int a, int b)
{
    return (a>b) ? a:b;
}

/*Creates a an AVL tree node and returns its pointer.*/
team_node node_create(team team)
{
    team_node node = (team_node) can_fail_malloc(sizeof(struct t_node));
     node->team = team;
     node->left = NULL;
     node->right = NULL;
     node->height = 1;
     return node;
}

/*Performs a rotate right operation on a given AVL tree node.*/
team_node rotate_right(team_node node)
{
    team_node auxiliar_node = node->left;
    team_node temporary = auxiliar_node->right;

    auxiliar_node->right = node;
    node->left = temporary;
    
    node->height = max(height(node->left), height(node->right))+1;
    auxiliar_node->height = max(height(auxiliar_node->left), height(auxiliar_node->right))+1;

    return auxiliar_node;
}

/*Performs a rotate left operation on a given AVL tree node.*/
team_node rotate_left(team_node node)
{
    team_node auxiliar_node = node->right;
    team_node temporary = auxiliar_node->left;

    auxiliar_node->left = node;
    node->right = temporary;
    
    node->height = max(height(node->left), height(node->right))+1;
    auxiliar_node->height = max(height(auxiliar_node->left), height(auxiliar_node->right))+1;

    return auxiliar_node;
}

/*Gets the balance factor of a given AVL tree.*/
int getBalanceFactor(team_node node)
{
    if(node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

/*Inserts a team into the AVL tree applying all required functions to ensure the tree is balanced.*/
team_node team_insert(team_node node, team team)
{
    int balance;

/*Insertion*/
    if (node == NULL) 
        return(node_create(team));
    if(strcmp(team->name, node->team->name) < 0)
        node->left = team_insert(node->left, team);
    else if(strcmp(team->name, node->team->name) > 0)
        node->right = team_insert(node->right, team);
    else
        return node;

/*Update height*/
    node->height = 1 + max(height(node->left), height(node->right));

/*Get AVL tree balance factor.*/
    balance = getBalanceFactor(node);

/*Balancing*/
    if ((balance > 1) && (strcmp(team->name, node->left->team->name) < 0))
        return rotate_right(node);
    if((balance < -1) && (strcmp(team->name, node->right->team->name) > 0))
        return rotate_left(node);
    if ((balance > 1) && (strcmp(team->name, node->left->team->name) > 0))
    {
        node->left =  rotate_left(node->left);
        return rotate_right(node); 
    }
    if ((balance < -1) && (strcmp(team->name, node->right->team->name) < 0))
    {
        node->right =  rotate_right(node->right);
        return rotate_left(node); 
    }

    return node;
}

void insert_team(team_node * node, team team)
{
    *node = team_insert(*node, team);
}

/*Prints all teams with most victories by lexicographic order.*/
void print_inorder(team_node node, int m, int NL) 
{ 
    if(node != NULL)
    {
        print_inorder(node->left, m, NL);
        if(node->team->score == m)
            print_team(node->team, NL); 
        print_inorder(node->right, m, NL); 
    }
} 

void in_order(team_node * node, int m, int NL)
{
    print_inorder(*node, m, NL);
}


/*ADITIONAL FUNCTIONS*/
/*Searches AVL tree for a specific node by name.*/
team_node search(team_node node, char * name)
{
    if(node == NULL)
        return NULL;

    if(strcmp(name, node->team->name) == 0)
        return node;
    if(strcmp(name, node->team->name) < 0)
        return search(node->left, name);
    else
        return search(node->right, name);
}

team_node search_team(team_node * node, char * name)
{
    return search(*node, name);
}

/*Returns the largest amount of victories obtain by a single or multiple teams.*/
int victories(team_node node)
{
    int r, r_left, r_right;
    
    if(node == NULL)
        return -1;

    r = node->team->score;
    r_left = victories(node->left);
    r_right = victories(node->right);

    if(r_left > r)
        r = r_left;
    if(r_right > r)
        r = r_right;
    return r;
}