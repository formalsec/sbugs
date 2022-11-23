#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "interface.h"

int main()
{
    team_node tree_ptr;
    game_item * hash_ptr;

    /*Initialize AVL tree and hash table*/
    init_tree(&tree_ptr);
    init_games(&hash_ptr);

    execute_command(&tree_ptr, hash_ptr);

    return 0;
}

