#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "games.h"

/* Frees game and string associated                                           */
void del_game(void *g){
    free(((game*) g)->name);
    free(g);
    return;
}

/* Compares a string with a pointer to list node containing a pointer to game */
int cmp_game_str(void *str, void *g){
    g = ((lst_node*) g)->value;
    return strcmp((char*) str, ((game*) g)->name);
}

/* Compares two list nodes containing pointers to games, alphabetically       */
int cmp_game_nds(void *a_nd, void *b_nd){
    game *a = ((lst_node*)a_nd)->value, *b = ((lst_node*)b_nd)->value;
    return strcmp(a->name, b->name);
}

/*Prints given name with input input line                                     */
void print_game(game *g, int i_l){
    printf("%d %s %s %s %d %d\n", i_l, g->name, g->team1->name, g->team2->name,
        g->score1, g->score2);
    return;
}

/* Goes through team tree printing games with given score(max), alphabetically*/
void print_targets(t_node *root, short max, int in_line){
    team *t;

    if (root == NULL)
        return;
    t = root->value;
    
    if (t->victs == max){
        print_targets(root->left, max, in_line);
        printf("%d * %s\n", in_line, t->name);
    }
    print_targets(root->right, max, in_line);
    return;
}