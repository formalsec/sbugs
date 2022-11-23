#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash_defines.h"
#include "jogos_hash.h"
#include "jogos_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao que inicializa a hashtable_jogos retornando-a.*/
JOGO_HASH ** init_hash_jogos()
{
    int i;
/*aloca memoria do tipo JOGO necessaria para guardar TAM_HASH lista_de_jogos*/
    JOGO_HASH ** hashtable_jogos = can_fail_malloc(sizeof(JOGO_HASH)*TAM_HASH);

    for(i = 0; i < TAM_HASH; i++) hashtable_jogos[i] = NULL;

    return hashtable_jogos;
}

/*Funcao que adiciona um jogo a hashtable_jogos.*/
void add_jogo_hash(JOGO_HASH ** hashtable_jogos, JOGO * jogo)
{
    JOGO_HASH * tmp = NULL;
    unsigned long indice;

    indice = hash(jogo -> nome);

    if (hashtable_jogos[indice] == NULL) 
    {
/*aloca e inicializa memoria do tipo JOGO_HASH necessaria para guardar o respetivo jogo*/
        hashtable_jogos[indice] = can_fail_calloc(1, sizeof(JOGO_HASH));
        hashtable_jogos[indice] -> jogo_ptr = jogo; 
    } 
    else
    {
/*aloca e inicializa memoria do tipo JOGO_HASH necessaria para guardar o respetivo jogo*/
        tmp = can_fail_calloc(1, sizeof(JOGO_HASH));

/*adiciona jogo no inicio da lista ligada referente a chave (indice) obtida*/
        tmp -> next = hashtable_jogos[indice];
        tmp -> jogo_ptr = jogo;
        hashtable_jogos[indice] = tmp;
    }
}

/*Funcao que procura em hashtable_jogos um jogo pelo seu nome.
    Retorna o jogo procurado caso encontrado e caso contrario nao retorna nada.*/
JOGO * procura_jogo(JOGO_HASH ** hashtable_jogos, char * nome)
{
    unsigned long indice;

    JOGO_HASH * tmp = NULL;
    
    indice = hash(nome);

/*tmp representa a head da lista ligada correspondente a chave (indice) da hashtable*/
    tmp = hashtable_jogos[indice];

    while((tmp != NULL))
    {
        if (strcmp(tmp -> jogo_ptr -> nome, nome) == 0) return tmp -> jogo_ptr;
        else tmp = tmp -> next;
    }
    return NULL;
}

/*Funcao que remove um jogo de hashtable_jogos dado o seu nome.*/
void remove_jogo_hash(JOGO_HASH ** hashtable_jogos, char * nome)
{
    unsigned long indice;

    JOGO_HASH * tmp = NULL;
    JOGO_HASH * prev_tmp = NULL;

    indice = hash(nome);

/*tmp representa a head da atual lista ligada referente a chave (indice) da hashtable*/
    tmp = hashtable_jogos[indice];

    while(tmp != NULL)
    {
        if (strcmp(tmp -> jogo_ptr -> nome, nome) == 0) break;

/*prev_tmp representa a head da lista ligada anterior (no anterior a tmp)*/
        prev_tmp = tmp; 
        tmp = tmp -> next;
    }

    if (tmp == NULL) return;

/*caso a lista ligada referente a chave contenha apenas um no*/
    if ((prev_tmp == NULL) && (tmp -> next == NULL)) hashtable_jogos[indice] = NULL;

/*caso a jogo procurado seja a head da lista ligada referente a chave (indice)*/
    else if (prev_tmp == NULL) hashtable_jogos[indice] = tmp -> next;

    else prev_tmp -> next = tmp -> next;

    free(tmp);
}

/*Funcao que altera o score de um jogo existente na hashtable_jogos dado o seu nome.*/
void altera_score(JOGO_HASH ** hashtable_jogos, char * nome, int score1, int score2)
{
    JOGO * jogo_alterar = procura_jogo(hashtable_jogos, nome);

    jogo_alterar -> score1 = score1;
    jogo_alterar -> score2 = score2;
}

/*Funcao que dado um nome de um jogo retorna o nome da equipa pertencente 
    a esse jogo que venceu.*/
char * maior_score_jogo(JOGO_HASH ** hashtable_jogos, char * nome)
{
    JOGO * jogo = procura_jogo(hashtable_jogos, nome);

    if (jogo -> score1 > jogo -> score2) return jogo -> equipa1;
    if (jogo -> score1 < jogo -> score2) return jogo -> equipa2;
    else return NULL;
}

/*Funcao que liberta a memoria alocada pela hashtable_jogos e seus elementos.*/
void destroy_jogos_hash(JOGO_HASH ** hashtable_jogos)
{
    
    JOGO_HASH * tmp = NULL;
    int i;

    for(i = 0; i < TAM_HASH; i++)
    {
/*tmp representa a head da lista ligada atual correspondente a chave (indice) da hashtable*/
        while((tmp = hashtable_jogos[i]) != NULL)
        {
            hashtable_jogos[i] = hashtable_jogos[i] -> next;
            free(tmp);
        }
    }
    free(hashtable_jogos);
}
