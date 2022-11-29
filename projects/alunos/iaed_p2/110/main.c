#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "gameslinked.h"
#include "hashteams.h"

gamelist addGame(int NL, gamelist *list, heads *hash);
/* Adds a game onto a linked list */
/*INPUT: a name:team1:team2:score1:score2 */
/*OUTPUT: N/A*/
/*ERROR CASES: - 'Jogo existente.' If theres an existing match with the same name in the system.*/
/*             - 'Equipa inexistente.' If there isn't a team with the given name in the system.*/

heads addTeam(int NL, heads *hash);
/* Adds a team onto a hash table */
/*INPUT: A name */
/*OUTPUT: N/A*/
/*ERROR CASES: - 'Equipa existente.' If theres an existing team with the same name in the system.*/

void lookupTeam(int NL, heads hash);
/*Searches for a team in a hash table */
/*INPUT: P name */
/*OUTPUT: NL name wins*/
/*ERROR CASES: - 'Equipa inexistente.' If theres isn't a team with the given name in the system.*/

void printGames(int NL, gamelist list);
/*Prints every game, by order of insertion */
/*INPUT: l */
/*OUTPUT: NL name team1 team2 score1 score2*/
/*ERROR CASES: - N/A*/

void lookupGame(int NL, gamelist list);
/* Searches for a match in a linked list */
/*INPUT: p name */
/*OUTPUT: NL name team1 team2 score1 score2*/
/*ERROR CASES: - 'Jogo inexistente.' If theres isn't a match with the given name in the system.*/

gamelist deleteGame(int NL, gamelist *list);
/* Deletes a game from a linked list */
/*INPUT: r name */
/*OUTPUT: N/A */
/*ERROR CASES: - 'Jogo inexistente.' If theres isn't a match with the given name in the system.*/

gamelist changeScore(int NL, gamelist *list);
/* Changes the score of a game */
/*INPUT: s name:score1:score2 */
/*OUTPUT: N/A */
/*ERROR CASES: - 'Jogo inexistente.' If theres isn't a match with the given name in the system.*/

int compare(const void *a, const void *b);
/* Auxiliary function used to sort the teams */

void topWinners(int NL, heads hash);
/* Shows the teams with the maximum number of wins */
/*INPUT: g */
/*OUTPUT:   NL Melhores maximum wins
            NL * name-equipa1
            NL * name-equipa2
            NL * name-equipa3
            ... */
/*ERROR CASES: - N/A*/

int main(){
    int NL = 1;
    char letra;
    gamelist head = game_listInit();
    heads hash = hashInit();

    while(letra != EOF){
        letra = getchar();
        switch(letra){
            case 'a':
                addGame(NL, &head, &hash);
                NL++;
                break;
            case 'A':
                addTeam(NL, &hash);
                NL++;
                break;
            case 'l':
                printGames(NL, head);
                NL++;
                break;
            case 'p':
                lookupGame(NL, head);
                NL++;
                break;
            case 'P':
                lookupTeam(NL, hash);
                NL++;
                break;
            case 'r':
                deleteGame(NL, &head);
                NL++;
                break;
            case 's':
                changeScore(NL, &head);
                NL++;
                break;
            case 'g':
                topWinners(NL, hash);
                NL++;
                break;
            case 'x':
                game_destroyList(head);
                hashDestroy(hash); 
                return 0;
            default:
                break;
        }     
    }
    return 0;
}

gamelist addGame(int NL, gamelist *list, heads *hash){
    char name[MAXNAME], t1[MAXNAME], t2[MAXNAME];
    int s1, s2;
    
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, t1, t2, &s1, &s2);
    
    if (game_searchList(*list, name) == NULL){
        link team1 = hashSearch(*hash, t1); 
        link team2 = hashSearch(*hash, t2);
     
        if (team1 == NULL || team2 == NULL){
            printf("%d Equipa inexistente.\n", NL);
        }
        else{
            Game game = gameInit(name, getItem(team1), getItem(team2), s1, s2);
            *list = game_insertListEnd(*list, game);
            team1->Team->wins = game->t1->wins;
            team2->Team->wins = game->t2->wins;      
        }
        return *list;
    }
    else{   
        printf("%d Jogo existente.\n", NL);
    }
    return *list;
}

heads addTeam(int NL, heads *hash){
    char name[MAXNAME];

    scanf(" %[^:\n]", name);
    hashInsert(NL, *hash, teamInit(name));
    return *hash;
}

void lookupTeam(int NL, heads hash){
    char name[MAXNAME];

    scanf(" %[^:\n]", name);
    teamPrint(NL, getItem(hashSearch(hash, name)));
}

void printGames(int NL, gamelist list){
    game_showList(NL, list);
}

void lookupGame(int NL, gamelist list){
    char name[MAXNAME];
    gamelink game2print;

    scanf(" %[^:\n]", name);
    
    game2print = game_searchList(list, name);
    if (!game2print){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    gamePrint(NL, game2print->game); 
}

gamelist deleteGame(int NL, gamelist *list){
    gamelink node;
    int score1, score2;
    char name[MAXNAME];

    scanf(" %[^:\n]", name);
    
    node = game_searchList(*list, name);
    if (node == NULL){
	    printf("%d Jogo inexistente.\n", NL);
        return *list;
    }
    
    score1 = gameScoreT1(node->game);
    score2 = gameScoreT2(node->game);

    if (score1 == score2)
        return game_removeList(*list, node);
    if (score1 > score2) 
        node->game->t1->wins--;	
    if (score1 < score2)
        node->game->t2->wins--;	

    return game_removeList(*list, node);
}

gamelist changeScore(int NL, gamelist *list){
    char name[MAXNAME];
    int s1, s2;
    
    scanf(" %[^:\n]:%d:%d", name, &s1, &s2);
   
    return game_changeScore(NL, *list, name, s1, s2);
}

int compare(const void *a, const void *b){ /* Compares every letter from the pointer of pointers in order to sort them alphabetically */
    char **v1, **v2;
    v1 = (char **) a;
    v2 = (char **) b;
    return strcmp(*v1, *v2);
}

void topWinners(int NL, heads hash){
   
    if (!hashEmpty(hash)){
        int  i = 0;
        maxes maxes = getHashMax(hash);
        char **strings = can_fail_malloc(sizeof(char**) * maxes.maxOcc);
        
        strings = getHashStrings(hash, maxes.max, strings);        
        qsort(strings, maxes.maxOcc, sizeof(char**), compare);
        printf("%d Melhores %d\n", NL, maxes.max);
        while (i < maxes.maxOcc){
            printf("%d * %s\n",NL, strings[i]);
            free(strings[i]);
            i++;
        }
        free(strings);
    }
}