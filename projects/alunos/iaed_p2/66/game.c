#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "game.h"

/*Creates a game with the given elements and returns a pointer to that game*/
Game_ptr NewGame(char *name, Team_ptr team1, Team_ptr team2, int score1, int score2)
{
    Game_ptr new_game = (Game_ptr)can_fail_malloc(sizeof(struct Game));

    name(new_game) = StringDup(name);
    new_game->team1 = team1;
    new_game->team2 = team2;
    score1(new_game) = score1;
    score2(new_game) = score2;

    return new_game;
}

/*Prints the elements of a game*/
void PrintGame(Game_ptr game)
{
    int score1, score2;

    score1 = score1(game);
    score2 = score2(game);
    printf("%s %s %s %d %d\n", name(game), team1(game), team2(game), score1, score2);
}

Team_ptr game_winner(Game_ptr game)
{
    if (score1(game) > score2(game))
        return game->team1;

    if (score2(game) > score1(game))
        return game->team2;

    return NULL;
}

/*Frees the game name and the game pointer*/
void FreeGame(Game_ptr game)
{
    free(name(game));
    free(game);
}

/*Creates a game link and returns it.*/
Game_link NewGameLink(Game_ptr game_ptr)
{
    Game_link new_link = (Game_link)can_fail_malloc(sizeof(struct GameNode));

    new_link->game = game_ptr;
    new_link->prev = NULL;
    new_link->next = NULL;

    return new_link;
}

/*Inserts a game in the beggining of a list*/
Game_link InsertGameBeginList(Game_link head, Game_ptr game_ptr)
{
    Game_link new_link = NewGameLink(game_ptr), last;

    /*If the list is empty*/
    if (head == NULL)
    {
        new_link->next = new_link->prev = new_link;
        return new_link;
    }

    last = head->prev; /*Saves pointer to the last node*/

    new_link->next = head;
    new_link->prev = last;

    last->next = head->prev = new_link;

    return new_link;
}

/*Removes a game from the game list*/
Game_link RemoveGameList(Game_link head, char *name)
{
    Game_link link_to_remove = head, prev = NULL;

    /*Finds the link we want to remove*/
    while (strcmp(name(link_to_remove->game), name) != 0)
    {
        prev = link_to_remove;
        link_to_remove = link_to_remove->next;
    }

    /*If it is the only link in the list*/
    if (link_to_remove->next == head && prev == NULL)
    {
        FreeGameNode(link_to_remove);
        return NULL;
    }

    /*If it is the first link*/
    if (link_to_remove == head)
    {
        prev = head->prev;

        head = head->next;

        prev->next = head;
        head->prev = prev;
        FreeGameNode(link_to_remove);
    }

    /*If it is the last link*/
    else if (link_to_remove->next == head)
    {
        prev->next = head;
        head->prev = prev;
        FreeGameNode(link_to_remove);
    }

    /*If it is somewhere in the middle of the list*/
    else
    {
        Game_link aux = link_to_remove->next;

        prev->next = aux;
        aux->prev = prev;
        FreeGameNode(link_to_remove);
    }

    return head;
}

/*Frees a game node and the game associated with it*/
void FreeGameNode(Game_link game_link)
{
    FreeGame(game_link->game);
    free(game_link);
}

/*Creates a struct GameHash with a hash_table of size max and returns a pointer to it*/
GameHash_ptr GameHashInit(int max)
{
    int i;
    GameHash_ptr game_hash = (GameHash_ptr)can_fail_malloc(sizeof(struct GameHash));

    item_count(game_hash) = INITIAL_ITEM_COUNT;
    hash_size(game_hash) = max;
    game_hash->hash_table = (Game_ptr *)can_fail_malloc(hash_size(game_hash) * sizeof(Game_ptr));

    /*Initialize every pointer with NULL*/
    for (i = 0; i < hash_size(game_hash); i++)
        game_hash->hash_table[i] = NULL;

    return game_hash;
}

/*Inserts a game in the game_hash*/
GameHash_ptr GameHashInsert(GameHash_ptr game_hash, Game_ptr game)
{
    int i = HashU(name(game), hash_size(game_hash));

    /*Search for the first available space*/
    while (game_hash->hash_table[i] != NULL)
        i = (i + 1) % hash_size(game_hash);

    game_hash->hash_table[i] = game; /*Insert the pointer in the available space*/
    item_count(game_hash)++;         /*Increment the item_count of the GameHash*/

    /*If the occupancy is equal or over than 50%, expand the hash*/
    if (item_count(game_hash) >= hash_size(game_hash) / 2)
    {
        GameHash_ptr new_hash = GameHashExpand(game_hash);
        return new_hash;
    }
    return game_hash;
}

/*Creates a new struct GameHash with double the size of the previous hash and with every game from the previous hash.
Returns a pointer to the new struct GameHash*/
GameHash_ptr GameHashExpand(GameHash_ptr game_hash)
{
    int i;
    Game_ptr *aux = game_hash->hash_table;
    GameHash_ptr new_hash = GameHashInit(hash_size(game_hash) * 2);

    /*Inserts every game of the previous hash in the new hash*/
    for (i = 0; i < hash_size(game_hash); i++)
        if (game_hash->hash_table[i] != NULL)
            GameHashInsert(new_hash, game_hash->hash_table[i]);

    free(aux);
    free(game_hash);
    return new_hash;
}

/*Returns a pointer to the game with the name equal to the one given*/
Game_ptr GameHashSearch(GameHash_ptr game_hash, char *name)
{
    int i = HashU(name, hash_size(game_hash));

    /*Iterates through the hashtable until it finds NULL or the wanted game*/
    while (game_hash->hash_table[i] != NULL)

        if (strcmp(name, name(game_hash->hash_table[i])) == 0)
            return game_hash->hash_table[i];

        else
            i = (i + 1) % hash_size(game_hash);
    return NULL;
}

/*Removes a game from the GameHash*/
void GameHashRemove(GameHash_ptr game_hash, char *name)
{
    int j, i = HashU(name, hash_size(game_hash));
    Game_ptr aux;

    /*Finds the game we wish to remove*/
    while (game_hash->hash_table[i] != NULL)
        if (strcmp(name, name(game_hash->hash_table[i])) == 0)
            break;
        else
            i = (i + 1) % hash_size(game_hash);

    game_hash->hash_table[i] = NULL; /*Puts NULL in the position removed*/
    item_count(game_hash)--;         /*Decrements the item_count in the GameHash*/

    /*Reinserts every game until a NULL is found*/
    for (j = (i + 1) % hash_size(game_hash); game_hash->hash_table[j] != NULL; j = (j + 1) % hash_size(game_hash), item_count(game_hash)--)
    {
        aux = game_hash->hash_table[j];
        game_hash->hash_table[j] = NULL;
        GameHashInsert(game_hash, aux);
    }
}

/*Frees the game_hash*/
void DeleteGameHash(GameHash_ptr game_hash)
{
    int i;

    for (i = 0; i < hash_size(game_hash); i++)
        if (game_hash->hash_table[i] != NULL)
            FreeGame(game_hash->hash_table[i]);

    free(game_hash->hash_table);
    free(game_hash);
}

/*Frees the game_list*/
void DeleteGameList(Game_link head)
{
    Game_link current = head;
    Game_link next;

    if (head != NULL)
    {
        do
        {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }
}
