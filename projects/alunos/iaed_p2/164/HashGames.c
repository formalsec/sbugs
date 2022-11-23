#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "HashGames.h"

/* Hash function used both in the hash table of Teams and the hash table of Nodes.*/
int hash(char * v, int * M){
    int h = 0, a = 127;
    for (; *v != '\0'; v++)
        h = (a*h + *v) % (*M);
    return h;
}

/* Receives a size and creates a new hash table of Nodes with the given size, with all the positions
initialized as NULL.*/
Node * HashGamesInit(int * m){
    int i;
    Node * hash_table;
    hash_table = (Node*) can_fail_malloc(sizeof(Node) * (*m));
    for (i = 0; i < *m; i++)
        hash_table[i] = NULL;   
    return hash_table;
}

/* Receives a hash table of Nodes, its size and a Node, inserting the Node in the hash table.*/
void HashGamesInsert(Node * hash_table,Node node, int * m){
    /* "i" is the index where the Node should be inserted.*/
    int i = hash(GameName(NodeGame(node)), m);
    /* If there is a collision, the Node is placed in the next free position.*/
    while (hash_table[i] != NULL)
        i = (i+1) % (*m);
    hash_table[i] = node;
}

/* Receives a hash table of Nodes, its size and a Game name. Returns an index "i" if the Game is found on the Node 
at the position "i". Returns DOES_NOT_EXIST (-1) if the Game is not found.*/
int GameSearch(char * name, int * m, Node * hash_table){
    /* "i" is the index where the pretended Node should be.*/
    int i = hash(name, m);
    /* If there is a collision, the search continues until a NULL value is found.*/
    while (hash_table[i] != NULL){
        /* If the Game is found, the index is returned.*/
        if (eq(GameName(NodeGame(hash_table[i])), name))
            return i;
        else 
            i = (i+1) % (*m);
    }
    return DOES_NOT_EXIST;
}

/* Receives a hash table of Nodes, its size and a Game name. If the Node containing that 
Game exists, the Node is removed from the hash table. The same Node is returned.*/
Node HashRemoveGame(char * name, int * m, Node * hash_table){
    int j, i = GameSearch(name, m, hash_table);
    Node aux, node;
    /* If the Game does not exist, returns the NULL value.*/
    if (i == DOES_NOT_EXIST)
        return NULL;
    /* "node" is the Node to be removed.*/
    node = hash_table[i];
    /* The position removed is set to NULL and the next non NULL positions are re-inserted.*/
    hash_table[i] = NULL;
    for ( j = (i+1) % *m; hash_table[j] != NULL; j = (j+1) % *m){
        aux = hash_table[j];
        hash_table[j] = NULL;
        HashGamesInsert(hash_table, aux, m);
    }
    return node;
}

/* Receives a hash table of Nodes and destroys it.*/
void DestroyHashGames(Node * hash_games){
    free(hash_games);
}

/* Receives a hash table of Nodes, its size and the number of Games. Expands the hash table 
to the double of its size and returns the new hash table with every element re-inserted.*/
Node * ExpandGames(Node * hash_game, int * n_games, int * m){
    int i = 0, count = 0;
    Node * new_hash_game;
    /* Sets the new hash table size to the double.*/
    (*m)*=2;
    /* The new hash table is created with the new size.*/
    new_hash_game = HashGamesInit(m);
    /* For every Node in the old hash table, it is inserted in the new hash table.*/
    for (; count < *n_games; i++)
        if (hash_game[i] != NULL){
            HashGamesInsert(new_hash_game, hash_game[i], m);
            count++;
        } 
    /* Destroys the old hash table.*/
    free(hash_game);
    return new_hash_game;
}