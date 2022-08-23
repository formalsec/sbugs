#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashTables.h"

typedef Team* Item;
#define exch(A,B) {Item t=A;A=B;B=t;};

/*------------------------------------------------------------------------------------*/
TeamsHash* expandT (TeamsHash *HashT) {
    
    TeamsHash *new_HashT;
    /* Tamanho da nova Hash e o dobro do tamanho da anterior */
    int new_size = (HashT->size)*2;
    
    new_HashT = initTeamsHash(new_size);

    copy_elementsT(new_HashT, HashT);

    /* Liberta a memoria alocada para a Hash antiga */
    free(HashT->headsT);
    free(HashT);

    return new_HashT;
}

GamesHash* expandG (GamesHash *HashG) {

    GamesHash *new_HashG;
    int new_size = (HashG->size)*2;
    
    new_HashG = initGamesHash(new_size);

    copy_elementsG(new_HashG, HashG);

    free(HashG->headsG);
    free(HashG);

    return new_HashG;
}

void copy_elementsT (TeamsHash *new_Hash, TeamsHash *old_Hash) {
    
    int i, new_i;
    teamNodeP x, prev;

    /* Para cada entrada da hash antiga */
    for (i=0; i < old_Hash->size ; i++) {
        
        /*Percorre a lista ate ao seu ultimo elemento */
        for (x = old_Hash->headsT[i]; x != NULL && x->next != NULL; x = x->next);
        
        if (x != NULL ) {
            for (prev = x->prev; prev != NULL; x = prev, prev = prev->prev) {

                /* Calcula o novo indice */
                new_i = hashU(x->team->name, new_Hash->size);

                prev->next = NULL;
                x->prev = NULL;

                /* Adiciona a equipa a nova hash no novo indice */
                new_Hash = addTeam(new_Hash, new_i, x);
            }

            /* Faz o mesmo para o primeiro elemento */
            new_i = hashU(x->team->name, new_Hash->size);
            new_Hash = addTeam(new_Hash, new_i, x);
        }
    }
        
}


void copy_elementsG (GamesHash *new_Hash, GamesHash *old_Hash) {
    int i, new_i;
    gameNodeP x, prev;

    /* Para cada entrada da hash antiga */
    for (i=0; i < old_Hash->size ; i++) {
        
        for (x = old_Hash->headsG[i]; x != NULL && x->nextH != NULL; x = x->nextH);

        if (x != NULL) {
            for (prev = x->prevH; prev != NULL; x = prev, prev = prev->prevH) {

                new_i = hashU(x->game->name, new_Hash->size);

                prev->nextH = NULL;
                x->prevH = NULL;

                new_Hash = addGameHash(new_Hash, new_i, x);
            }

            new_i = hashU(x->game->name, new_Hash->size);
            new_Hash = addGameHash(new_Hash, new_i, x);
        }
    }
}

/*------------------------------------------------------------------------------------*/
TeamsHash* initTeamsHash(int M) {
    int i;
    TeamsHash *Hash;
    teamNodeP *heads;

    Hash = (TeamsHash*) malloc (sizeof(TeamsHash));

    /* Inicializa um vetor de teamNodeP's -> ponteiros para nos de equipas */
    heads = (teamNodeP*)malloc(sizeof(teamNodeP)*M);

    for (i = 0; i < M; i++) {
        /*Inicializa as heads de cada entrada a NULL*/
        heads[i]= NULL;
    }

    Hash->headsT = heads;
    Hash->n_elements = 0;
    Hash->size = M;

    return Hash;
}

GamesHash* initGamesHash(int M) {
    int i;
    GamesHash *Hash;
    gameNodeP *heads;

    Hash = (GamesHash*) malloc (sizeof(GamesHash));

    /* Inicializa um vetor de gameNodeP's -> ponteiros para nos de jogos */
    heads = (gameNodeP*)malloc(sizeof(gameNodeP)*M);

    for (i = 0; i < M; i++) {
        /*Inicializa as heads de cada entrada a NULL*/
        heads[i]= NULL;
    }

    Hash->headsG = heads;
    Hash->n_elements = 0;
    Hash->size = M;

    return Hash;
}

/*-----------------------------------------------------------------------------------*/
int verifyExistentTeam(TeamsHash *HashT, char* name) {

    teamNodeP *headsT = HashT->headsT;
    int i = hashU(name, HashT->size); /* Vai buscar o indice com a HashFunction */
    
    /* Se a entrada nao for vazia -> Procura a equipa na lista */
    if (headsT[i] != NULL) {

        teamNodeP x;

        for(x=headsT[i]; x != NULL ; x= x->next) {
            if (strcmp(x->team->name, name) == 0) {
                return -1;
            }
        }
    }

    return i;  
}

int verifyExistentGame(GamesHash *HashG, char* name) {

    gameNodeP *headsG = HashG->headsG;
    int i = hashU(name, HashG->size); /* Vai buscar o indice com a HashFunction */

    /* Se a entrada nao for vazia -> Procura a equipa na lista */
    if (headsG[i] != NULL) {

        gameNodeP x;

        for(x=headsG[i]; x != NULL ; x= x->nextH) {
            if (strcmp(x->game->name, name) == 0) {
                return -1;
            }
        }
    }

    return i;
}

/*----------------------------------------------------------------------------------*/
TeamsHash* addTeam(TeamsHash *HashT, int i, TeamNode * eq) {

    int load_factor = (HashT->n_elements / HashT->size);

    if (load_factor >= 1) {
        HashT = expandT(HashT);
        i = hashU(eq->team->name, HashT->size);
    }
    /*Insere na entrada correta o no da equipa*/
    HashT->headsT[i] = insertBeginT(HashT->headsT[i], eq);
    (HashT->n_elements)++;

    return HashT;
}

teamNodeP insertBeginT(teamNodeP head, teamNodeP eq) {
    
    if (head != NULL) {
        head->prev = eq;
    }
    eq->next= head;

    return eq;
}

GamesHash* addGameHash (GamesHash *HashG, int i, gameNodeP game) {

    int load_factor = (HashG->n_elements / HashG->size);

    if (load_factor >= 1) {
        HashG = expandG(HashG);
        i = hashU(game->game->name, HashG->size);
    }

    /*Insere na entrada correta o no do jogo*/
    HashG->headsG[i] = insertBeginG (HashG->headsG[i], game);
    (HashG->n_elements)++;

    return HashG;
}

gameNodeP insertBeginG (gameNodeP head, gameNodeP game) {
    
    if (head != NULL) {
        head->prevH = game;
    }
    game->nextH = head;

    return game;
}

/*----------------------------------------------------------------------------------*/
Team* searchTeam (TeamsHash *HashT, char *name) {

    teamNodeP *headsT = HashT->headsT;

    /*Vai buscar o indice com a HashFunction*/
    int i = hashU(name, HashT->size);

    /*Procura o nome da equipa na lista e retorna o no dessa equipa*/
    return searchListT (headsT[i], name);
}

Team* searchListT (teamNodeP head, char* name) {

    /*Se houver alguma equipa na lista*/
    if (head != NULL) {
        
        teamNodeP x;
        
        for (x=head; x != NULL; x= x->next) {
            /* Percorre ate encontrar uma equipa com o mesmo nome */
            if (strcmp(x->team->name, name) == 0) {
                return (x->team);
            }
        }
    }

    /* Se nao encontrar devolve NULL */
    return NULL;
}

Game* searchGame (GamesHash *HashG, char* name) {

    gameNodeP *headsG = HashG->headsG;
    /*Vai buscar o indice com a HashFunction*/
    int i = hashU(name, HashG->size);

    /*Procura o nome do jogo na lista e retorna o no desse jogo*/
    return searchListG (headsG[i], name);
}

Game* searchListG (gameNodeP head, char* name) {

    /*Se houver algum jogo na lista*/
    if (head != NULL) {
        
        gameNodeP x;
        
        for (x=head; x != NULL; x= x->nextH) {
            /* Percorre ate encontrar um jogo com o mesmo nome */
            if (strcmp(x->game->name, name) == 0) {
                return (x->game);
            }
        }
    }

    /* Se nao encontrar, devolve NULL */
    return NULL;
}

/*----------------------------------------------------------------------------------*/
void deleteGame (gameListP gameList, GamesHash *HashG, char *name) {
    
    int i = hashU(name, HashG->size);

    gameNodeP x, prev, *headsG = HashG->headsG;

    /* Percorre a lista da entrada correta da Hash Table */
    for(x=headsG[i], prev = NULL; x != NULL; prev = x, x = x->nextH) {

        /* Quando encontra o jogo */
        if (strcmp (x->game->name, name) == 0) {

            /* Se o jogo for a head, passa a head para o seguinte */
            if (x == headsG[i]) {
                headsG[i] = x->nextH;
                if (headsG[i] != NULL) {
                    headsG[i]->prevH = NULL;
                }
            }
            /* Se nao, aponta o jogo anterior para o jogo seguinte e o seguinte para o anterior*/
            else {
                prev->nextH = x->nextH;
                if (prev->nextH != NULL) {
                    prev->nextH->prevH = prev;
                }
            }

            /* Retira o jogo da lista */
            deleteGameList(gameList, name);

            free(x->game->name);
            free(x->game);
            free(x);

        break;
        }
    }

    (HashG->n_elements)--;
}

void deleteGameList (gameListP gameList, char* name) {
    
    gameNodeP x, prev;

    /* Percorre a lista ate ao ultimo elemento */
    for(x = gameList->head, prev = NULL; x != NULL; prev = x, x = x->nextL) {

        if (strcmp (x->game->name, name) == 0) {
            
            /* Se for a cabeca, a cabeca passa a apontar para o seguinte */
            if (x == gameList->head) {
                gameList->head = x->nextL;

                /* Caso o seguinte nao seja NULL, ajusta o seu previous */
                if (gameList->head != NULL) {
                    gameList->head->previous = NULL;
                }
            }

            else {
                /* O anterior aponta para o seguinte */
                prev->nextL = x->nextL;
                
                /* Caso fosse o ultimo elemento da lista, atualiza-o para oa nterior */
                if (x == gameList->last) {
                    gameList->last = prev;
                }
                /* Caso contrario aponta o seguinte para o anterior */
                else {  
                    x->nextL->previous = prev;
                }
            }
            
            break;
        }
    }
}

/*----------------------------------------------------------------------------------*/
void changeScores(GamesHash *HashG, char* name, int s1, int s2) {
    int winner = 0;

    Game* x;

    /* Vai buscar o jogo */
    x = searchGame(HashG, name);

    /* Guarda qual era o vencedor antes da mudanca de score */
    if (x->score1 > x->score2) {
        winner = 1;
    }
    else if (x->score2 > x->score1) {
        winner = 2;
    }

    /* Muda o score */
    x->score1 = s1;
    x->score2 = s2;

    /* Ajusta as vitorias */
    if ((winner == 1) && (s1<=s2)) {
        (x->team1->wins)--;
        if( s1 < s2) {
           (x->team2->wins)++; 
        }
    }
    else if ((winner == 2) && (s2<=s1)) {
        (x->team2->wins)--;
        if( s2 < s1){
            (x->team1->wins)++;
        }
    }
    else if (winner == 0) {
        if (s1>s2) {
            (x->team1->wins)++;
        }
        else if (s2>s1){
            (x->team2->wins)++;
        }
    }
}

/*------------------------------------------------------------------------------------*/
Team** winners(TeamsHash *HashT, Team **winnersTable, int maxCapacity, int cont) {
    int i;
    int max = 0, len = 1;
    int topMax=0; /* Numero maximo de vitorias */
    teamNodeP *headsT = HashT->headsT;

    /* Para cada entrada da tabela procura as equipas com mais vitorias e adiciona a um vetor */
    for (i=0; i< HashT->size ; i++) {
        if (headsT[i] != NULL) {
            winnersTable = searchWinners(headsT, &max, i, &len , winnersTable, &maxCapacity);
        }
    }

    /* Percorre as equipas do vetor construido e determina o numero maximo de vitorias */
    for (i=0; i<(len-1); i++) {
        if (winnersTable[i]->wins >= max) {
            topMax = winnersTable[i]->wins;
        }
    }

    /* Ordena as equipas por ordem lexicografica */
    winnersTable = sortWinners(winnersTable, &len);

    /* Caso haja pelo menos uma equipa imprime*/
    if(len>1) {
        printf("%d Melhores %d\n", cont, topMax);
        for (i=0; i<(len-1); i++) {
            /* Se a equipa tiver um numero de vitorias igual ao maximo imprime */
            if (winnersTable[i]->wins == topMax) {
                printf("%d * %s\n", cont, winnersTable[i]->name);
            }
        }
    }

    return winnersTable;
}

Team** searchWinners(teamNodeP *headsT, int *maxP, int i, int *lenP, Team **winnersTable, int* maxC) {
    
    teamNodeP x;

    /* Percorre a lista da entrada da Hash Table */
    for (x = headsT[i]; x != NULL; x = x->next) {

        /* Caso tenha mais vitorias do que o numero maior de vitorias ate ao momento */
        if (x->team->wins >= (*maxP)) {

            /* Adiciona a equipa ao vetor */
            winnersTable = addWinnerTable(x->team, lenP , winnersTable, maxC);
            (*lenP) ++; /* Incrementa o contador do tamanho do vetor */
            (*maxP) = x->team->wins; /* Incrementa o numero maximo de vitorias */
        }
    }

    return winnersTable;
}

Team** addWinnerTable(Team* x, int* lenP, Team **winnersTable, int* maxC) {

    /* Caso seja o primeiro elemento, adiciona */
    if ((*lenP) == 1) {
        winnersTable[0] = x;
    
    }
    else {

        /* Confirma se a capacidade maxima do vetor nao foi excedida */
        if (*lenP == *maxC){

            /* Realoca memoria caso necessario */
            winnersTable = (Team**) realloc (winnersTable, sizeof(Team*)*(*maxC)*2);
            (*maxC) = (*maxC)*2;

            /* Adiciona a equipa ao vetor */
            winnersTable[(*lenP)-1] = x;
        }
        else {
            /* Adiciona a equipa ao vetor */
            winnersTable[(*lenP)-1] = x;
        }
    }

    return winnersTable;

}

/* Bubble sort */
Team** sortWinners(Team **winnersTable, int* lenP) {
    int l = 0, r = (*lenP)-2, j , i;

    for(i=l; i<r; i++){

        for(j=l; j< r+(l-i) ;j++){

            if((strcmp(winnersTable[j+1]->name, winnersTable[j]->name))<0){
                exch(winnersTable[j+1],winnersTable[j]);
            }
        }
    }

    return winnersTable;
}

/*-------------------------------------------------------------------------------*/
void destroyTeamsHash(TeamsHash *HashT) {

    int i=0;
    teamNodeP x, aux, *headsT = HashT->headsT;
    
    for(i=0; i < HashT->size ; i++) {

        /* Se a entrada estiver vazia avanca */
        if (headsT[i] == NULL) continue;

        x = headsT[i];
        aux = x->next;

        /* Percorre a fila ate ao ultimo e liberta memoria*/
        for (; x != NULL && aux != NULL ; aux = x->next) {
            free(x->team->name);
            free(x->team);
            free(x);
            x = aux;
        }
        /* Quando chega ao final elimina o ultimo */
        free(x->team->name);
        free(x->team);
        free(x);
    }

    /* Liberta a tabela */
    free(HashT->headsT);
}

void destroyGamesHash(GamesHash *HashG) {
    
    int i=0;
    gameNodeP x, aux, *headsG = HashG->headsG;

    for(i=0; i < HashG->size ; i++) {
        if (headsG[i] == NULL) continue;

        x = headsG[i];
        aux = x->nextH;

        for (; x != NULL && aux != NULL; aux = x->nextH) {
            free(x->game->name);
            free(x->game);
            free(x);
            x = aux;
        }
        free(x->game->name);
        free(x->game);
        free(x);
    }

    free (HashG->headsG);
}

