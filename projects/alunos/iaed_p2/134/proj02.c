#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10000
#define TRUE 1
#define FALSE 0


typedef struct entry_e {
    char *nome;
    int vitorias;
    struct entry_e *next;
} entry_e;


typedef struct entry_j {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
    unsigned long jogo_id;
    struct entry_j *next;
} entry_j;


typedef struct {
    entry_e **entries;
} ht_e;

typedef struct {
    entry_j **entries;
} ht_j;

/*--------------------------Prototypes--------------------*/

unsigned int hash(const char *key);/* Hashtable fuction*/
static int myCompare(const void* a, const void* b);/* Defining comparator function as per the requirement */
void sort( char* arr[], int n);/* Function to sort the array */
entry_j *ht_pair_j(const char *nome, const char *equipa1, const char *equipa2, const int score1, const int score2, unsigned long jogo_id);/*Used to search for the entry required corresponding to the game*/
entry_e *ht_pair_e(const char *equipa, const int vitorias);/*Used to search for the entry required corresponding to the team*/
ht_j *ht_create_j(void);/*Used in order to create a game*/
ht_e *ht_create_e(void);/*Used in order to create a team*/
void ht_set_j(ht_j *hashtable, const char *nome, const char *equipa1, const char *equipa2, const int score1, const int score2, unsigned long jogo_id, int rnl );/*Used in order to "pair" entries to their correspondent places in the game hashtable*/
void ht_set_e(ht_e *hashtable, const char *nome, const int vitorias, int rnl );/*Used in order to "pair" entries to their correspondent places in the team hashtable*/
entry_j *ht_get_j(ht_j *hashtable, const char *nome);/*Used in order to find the entry that "contains" the input for the games name*/
entry_e *ht_get_e(ht_e *hashtable, const char *nome);/*Used in order to find the entry that "contains" the input for the teams name*/
/*Functions in order to remove, dump and\or free a game or team*/
void ht_del_j(ht_j *hashtable, const char *nome);
void ht_del_e(ht_e *hashtable, const char *nome);
void ht_dump_j(ht_j *hashtable, int rnl);  
void delete_all_j(ht_j *hashtable);
void delete_all_e(ht_e *hashtable);


/*-----------------Auxiliary Fuctions--------------------------*/

unsigned int hash(const char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    /* do several rounds of multiplication*/
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    /* make sure value is 0 <= value < TABLE_SIZE*/
    value = value % TABLE_SIZE;

    return value;
}


/* Defining comparator function as per the requirement */
static int myCompare(const void* a, const void* b) 
{ 
  
    /* setting up rules for comparison */
    return strcmp(*(const char**)a, *(const char**)b); 
} 
  
/* Function to sort the array */
void sort( char* arr[], int n) 
{ 
    /* calling qsort function to sort the array*/ 
    /* with the help of Comparator */
    qsort(arr, n, sizeof(const char*), myCompare); 
} 


entry_j *ht_pair_j(const char *nome, const char *equipa1, const char *equipa2, const int score1, const int score2, unsigned long jogo_id) {
    /* allocate the entry*/
    entry_j *entry = can_fail_malloc(sizeof(entry_j) * 1);
    entry->nome = can_fail_malloc(strlen(nome) + 1);
    entry->equipa1 = can_fail_malloc(strlen(equipa1) + 1);
    entry->equipa2 = can_fail_malloc(strlen(equipa2) + 1);
    entry->jogo_id = jogo_id;    

    /* copy the key and value in place*/
    strcpy(entry->nome, nome);
    strcpy(entry->equipa1, equipa1);
    strcpy(entry->equipa2, equipa2);
    entry->score1 = score1;
    entry->score2 = score2;

    /* next starts out null but may be set later on*/
    entry->next = NULL;

    return entry;
}


entry_e *ht_pair_e(const char *equipa, const int vitorias) {
    /* allocate the entry*/
    entry_e *entry = can_fail_malloc(sizeof(entry_e) * 1);
    entry->nome = can_fail_malloc(strlen(equipa) + 1);
    entry->vitorias = vitorias;

    /* copy the key and value in place*/
    strcpy(entry->nome, equipa);

    /* next starts out null but may be set later on*/
    entry->next = NULL;

    return entry;
}

ht_j *ht_create_j(void) {
    int i = 0;
    /* allocate table*/
    ht_j *hashtable = can_fail_malloc(sizeof(ht_j) * 1);

    /* allocate table entries*/
    hashtable->entries = can_fail_malloc(sizeof(entry_j*) * TABLE_SIZE);

    /* set each to null (needed for proper operation)*/
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}



ht_e *ht_create_e(void) {
    int i = 0;
    /* allocate table*/
    ht_e *hashtable = can_fail_malloc(sizeof(ht_e) * 1);

    /* allocate table entries*/
    hashtable->entries = can_fail_malloc(sizeof(entry_e*) * TABLE_SIZE);

    /* set each to null (needed for proper operation)*/
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set_j(ht_j *hashtable, const char *nome, const char *equipa1, const char *equipa2, const int score1, const int score2, unsigned long jogo_id, int rnl ) {
    unsigned int slot = hash(nome);

    /* try to look up an entry set*/
    entry_j *entry = hashtable->entries[slot];
    entry_j *prev;
    /* no entry means slot empty, insert immediately*/
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair_j(nome, equipa1, equipa2, score1, score2, jogo_id);
        return;
    }
    
    /* walk through each entry until either the end is*/
    /* reached or a matching key is found*/
    while (entry != NULL) {
        /* check key*/
        if (strcmp(entry->nome, nome) == 0) {
            /* match found, print error*/
            printf("%d Jogo existente.\n", rnl);
            return;
        }

        /* walk to next*/
        prev = entry;
        entry = prev->next;
    }

    /* end of chain reached without a match, add new*/
    prev->next = ht_pair_j(nome, equipa1, equipa2, score1, score2, jogo_id);
}



void ht_set_e(ht_e *hashtable, const char *nome, const int vitorias, int rnl ) {
    unsigned int slot = hash(nome);

    /* try to look up an entry set*/
    entry_e *entry = hashtable->entries[slot];
    entry_e *prev;
    /* no entry means slot empty, insert immediately*/
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair_e(nome, vitorias);
        return;
    }
     
    /* walk through each entry until either the end is*/
    /* reached or a matching key is found*/
    while (entry != NULL) {
        /* check key*/
        if (strcmp(entry->nome, nome) == 0) {
            /* match found, print error*/
            printf("%d Equipa existente.\n", rnl);
            return;
        }

        /* walk to next*/
        prev = entry;
        entry = prev->next;
    }

    /* end of chain reached without a match, add new*/
    prev->next = ht_pair_e(nome, vitorias);
}


entry_j *ht_get_j(ht_j *hashtable, const char *nome) {
    unsigned int slot = hash(nome);

    /* try to find a valid slot*/
    entry_j *entry = hashtable->entries[slot];

    /* no slot means no entry*/
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the slot, which could just be a single thing*/
    while (entry != NULL) {
        /* return value if found*/
        if (strcmp(entry->nome, nome) == 0) {
            return entry;
        }

        /* proceed to next key if available*/
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match*/
    return NULL;
}



entry_e *ht_get_e(ht_e *hashtable, const char *nome) {
    unsigned int slot = hash(nome);

    /* try to find a valid slot*/
    entry_e *entry = hashtable->entries[slot];

    /* no slot means no entry*/
    if (entry == NULL) {
        return NULL;
    }

    /* walk through each entry in the slot, which could just be a single thing*/
    while (entry != NULL) {
        /* return value if found*/
        if (strcmp(entry->nome, nome) == 0) {
            return entry;
        }

        /* proceed to next key if available*/
        entry = entry->next;
    }

    /* reaching here means there were >= 1 entries but no key match*/
    return NULL;
}

void ht_del_j(ht_j *hashtable, const char *nome) {
    unsigned int bucket = hash(nome);

    /* try to find a valid bucket*/
    entry_j *entry = hashtable->entries[bucket];
    entry_j *prev;
    int idx = 0;
    /* no bucket means no entry*/
    if (entry == NULL) {
        return;
    }

    

    /* walk through each entry until either the end is reached or a matching key is found*/
    while (entry != NULL) {
        /* check key*/
        if (strcmp(entry->nome, nome) == 0) {
            /* first item and no next entry*/
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            /* first item with a next entry*/
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            /* last item*/
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            /* middle item*/
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            /* free the deleted entry*/
            free(entry->nome);
            free(entry->equipa1);
            free(entry->equipa2);
            free(entry);

            return;
        }

        /* walk to next*/
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}



void ht_del_e(ht_e *hashtable, const char *nome) {
    unsigned int bucket = hash(nome);

    /* try to find a valid bucket*/
    entry_e *entry = hashtable->entries[bucket];
    entry_e *prev;
    int idx = 0;
    /* no bucket means no entry*/
    if (entry == NULL) {
        return;
    }

    

    /* walk through each entry until either the end is reached or a matching key is found*/
    while (entry != NULL) {
        /* check key*/
        if (strcmp(entry->nome, nome) == 0) {
            /* first item and no next entry*/
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            /* first item with a next entry*/
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            /* last item*/
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            /* middle item*/
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            /* free the deleted entry*/
            free(entry->nome);
            free(entry);

            return;
        }

        /* walk to next*/
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}




void ht_dump_j(ht_j *hashtable, int rnl) {
    int i,d;
    struct entry_j **lista_jogos;
    struct entry_j *swap;
    struct entry_j *entry; 
    int total_jogos = 0;
    int index = 0;
    for ( i = 0; i < TABLE_SIZE; ++i) {
        entry = hashtable->entries[i];
        

        if (entry == NULL) {
            continue;
        }
        for(;;) {
            total_jogos++;
            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }
    }
    lista_jogos = can_fail_malloc((total_jogos+1) * sizeof(struct entry_j*));
    for ( i = 0; i < TABLE_SIZE; ++i) {
        entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }
        for(;;) {
            lista_jogos[index] = (entry_j*)can_fail_malloc(sizeof(entry_j)); /*reallocating memory for the string (+1 is for '\0');*/
            lista_jogos[index]->equipa1 = (char*)can_fail_malloc((strlen(entry->equipa1)+1) * sizeof(char)); /*reallocating memory for the string (+1 is for '\0');*/
            lista_jogos[index]->equipa2 = (char*)can_fail_malloc((strlen(entry->equipa2)+1) * sizeof(char)); /*reallocating memory for the string (+1 is for '\0');*/
            lista_jogos[index]->nome = (char*)can_fail_malloc((strlen(entry->nome)+1) * sizeof(char)); /*reallocating memory for the string (+1 is for '\0');*/
            strcpy((char*)lista_jogos[index]->nome,entry->nome); /*storing the string*/
            strcpy((char*)lista_jogos[index]->equipa1,entry->equipa1); /*storing the string*/
            strcpy((char*)lista_jogos[index]->equipa2,entry->equipa2); /*storing the string*/
            lista_jogos[index]->score1 = entry->score1;
            lista_jogos[index]->score2 = entry->score2;
            lista_jogos[index]->jogo_id = entry->jogo_id;
            index++;
            
            if (entry->next == NULL) {
                break;
            }
            entry = entry->next;
        }
    }
    for (i = 0 ; i < total_jogos - 1; i++)
    {
        for (d = 0 ; d < total_jogos - i - 1; d++)
        {
            if (lista_jogos[d]->jogo_id > lista_jogos[d+1]->jogo_id) /* For decreasing order use < */
                {
                swap     = lista_jogos[d];
                lista_jogos[d]   = lista_jogos[d+1];
                lista_jogos[d+1] = swap;
                }
            }
        }

        for( i = 0; i < total_jogos; i++ ){
            printf("%d %s %s %s %d %d\n", rnl, lista_jogos[i]->nome, lista_jogos[i]->equipa1, lista_jogos[i]->equipa2, lista_jogos[i]->score1, lista_jogos[i]->score2);
            free( lista_jogos[i]->equipa1 );
            free( lista_jogos[i]->equipa2 );
            free( lista_jogos[i]->nome );
            free( lista_jogos[i] );
                        }
            free( lista_jogos );
            return;
}





void delete_all_j(ht_j *hashtable) {
    int i;
    entry_j *current;
    for ( i = 0; i < TABLE_SIZE; ++i) {
        entry_j *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        for(;;) {
            current = entry;
            entry = entry->next;
            free(current->nome);
            free(current->equipa1);
            free(current->equipa2);
            free(current);
            if (entry == NULL) {
                break;
            }
        }
    }
}


void delete_all_e(ht_e *hashtable) {
    int i;
    entry_e *current;
    for ( i = 0; i < TABLE_SIZE; ++i) {
        entry_e *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        for(;;) {
            current = entry;
            entry = entry->next;
            free(current->nome);
            free(current);
            if (entry == NULL) {
                break;
            }
        }
    }
}


/*--------------------------------------------Main--------------------------------------------------------------------*/
/*  
    Command list for user help:
    __a__ - Adiciona um novo jogo.
    __l__ - Lista todos os jogos introduzidos.
    __p__ - Procura um jogo com o nome dado.
    __r__ - Apaga um jogo dado um nome.
    __s__ - Altera o score de um jogo dado o nome.
    __A__ - Adiciona uma nova equipa.
    __P__ - Procura uma equipa dado um nome.
    __g__ - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa).
*/

int main() {
    /*Necessary constants tools for main*/
    ht_j *htj = ht_create_j();
    ht_e *hte = ht_create_e();
    int trabalha = TRUE;
    int rnl = 0;
    int c;
    int i;
    int index;
    int n_equipas;
    char **strings = NULL;
    char b[1024], h[1024], j[1024];
    int score1 = 0;
    int score2 = 0;
    unsigned long jogo_id = 0;
    entry_e *current_e;
    entry_e *entry_equipa; 
    entry_j *current_j;
    while (trabalha) {
    switch (c = getchar()) {
        case 'a':
                rnl++;
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", b, h, j, &score1, &score2);
                if ( ht_get_j(htj, b) == NULL){ 
                    if ( ht_get_e(hte, h)!= NULL && ht_get_e(hte, j)!= NULL) { 
                        ht_set_j(htj, b, h, j, score1, score2, jogo_id, rnl);
                        jogo_id++;
                        if ( score1 > score2) {
                            current_e = ht_get_e(hte,h);
                            current_e->vitorias++;
                        }
                        if ( score1 < score2) {
                            current_e = ht_get_e(hte,j);
                            current_e->vitorias++;
                        }
                        break;
                    }
                      else{
                            printf("%d Equipa inexistente.\n", rnl);
                        }
                }
               else {
                    printf("%d Jogo existente.\n",rnl);
                }
                break;

            case 'A':
                rnl++;
                scanf(" %[^:\n]", b);
                if(  ht_get_e(hte, b) == NULL){ 
                    ht_set_e(hte, b,0, rnl);
                    break;
                }
                else{
                    printf("%d Equipa existente.\n", rnl);
                }
                break;

            case 'l':
                rnl++;
                ht_dump_j(htj,rnl);
                break;

            case 'p':
                rnl++;
                scanf(" %[^:\n]", b);
                current_j = ht_get_j(htj, b);
                if ( current_j != NULL) {
                    printf( "%d %s %s %s %d %d\n", rnl, current_j->nome, current_j->equipa1,current_j->equipa2,current_j->score1,current_j->score2);
                }
                else {
                    printf("%d Jogo inexistente.\n", rnl);
                }
                break;
            
            case 'r':
                rnl++;
                scanf(" %[^:\n]", b);
                current_j = ht_get_j(htj, b);
                if ( current_j != NULL) {
                    if ( current_j->score1 > current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa1);
                        current_e->vitorias--;
                    }
                    if ( current_j->score1 < current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa2);
                        current_e->vitorias--;
                    }
                    ht_del_j( htj, b);
                    break;
                }
                else {
                    printf("%d Jogo inexistente.\n", rnl);
                }
            break;

            case 's':
                rnl++;
                scanf(" %[^:\n]:%d:%d", b, &score1, &score2);
                current_j = ht_get_j(htj, b);
                if ( current_j != NULL) {
                    if ( current_j->score1 > current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa1);
                        current_e->vitorias--;
                    }
                    if ( current_j->score1 < current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa2);
                        current_e->vitorias--;
                    }
                    current_j->score1 = score1;
                    current_j->score2 = score2;
                    if ( current_j->score1 > current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa1);
                        current_e->vitorias++;
                    }
                    if ( current_j->score1 < current_j->score2) {
                        current_e = ht_get_e(hte,current_j->equipa2);
                        current_e->vitorias++;
                    }
                    break;
                }
                else {
                    printf("%d Jogo inexistente.\n", rnl);
                }
            break;


            case 'P':
                rnl++;
                scanf(" %[^:\n]", b);
                current_e = ht_get_e(hte, b);
                if ( current_e != NULL) {
                    printf( "%d %s %d\n", rnl, current_e->nome,current_e->vitorias);
                }
                else {
                    printf("%d Equipa inexistente.\n", rnl);
                }
                break;

            case 'g':
                rnl++;
                c = 0;
                index = 0;
                n_equipas = 0;
                for ( i = 0; i < TABLE_SIZE; ++i) {
                    entry_equipa = hte->entries[i];
                    if (entry_equipa == NULL) {
                        continue;
                    }

                    for(;;) {
                        if (entry_equipa->vitorias > c)
                        {
                            c = entry_equipa->vitorias;
                            n_equipas = 1;
                        }
                        else if (entry_equipa->vitorias == c){
                            n_equipas ++;
                        }
                        if (entry_equipa->next == NULL) {
                            break;
                        }
                        entry_equipa = entry_equipa->next;
                    }
                }
                if ( n_equipas ==0){
                    break;
                }
                printf("%d Melhores %d\n", rnl, c);
                strings = can_fail_malloc((n_equipas+1) * sizeof(char*));
                

                for ( i = 0; i < TABLE_SIZE; ++i) {
                    entry_equipa = hte->entries[i];
                    if (entry_equipa == NULL) {
                        continue;
                    }
                    
                    for(;;) {
                        if (entry_equipa->vitorias == c)
                        {
                            strings[index] = (char*)can_fail_malloc((strlen(entry_equipa->nome)+1) * sizeof(char)); /*reallocating memory for the string (+1 is for '\0');*/
                            strcpy((char*)strings[index],entry_equipa->nome); /*storing the string*/
                            index++; /*updating the number of strings*/
                        }
                        if (entry_equipa->next == NULL) {
                            break; 
                        }
                        entry_equipa = entry_equipa->next;
                    }
                }
                sort(strings, n_equipas); 
                for( i = 0; i < index; i++ ){
                            printf("%d * %s \n", rnl, strings[i]);
                            free( strings[i] );
                            }
                        free( strings );
                break;

            case 'x':
                trabalha = FALSE;
                break;

            default:
                break;
        }
    }
    
    delete_all_e(hte);
    delete_all_j(htj);


    free(hte->entries);
    free(htj->entries);
    free(htj);
    free(hte);
    return 0;
}
