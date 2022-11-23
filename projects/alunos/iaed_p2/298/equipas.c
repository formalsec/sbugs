#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash_defines.h"
#include "equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Funcao que inicializa a hashtable_equipas retornando-a.*/
EQUIPA ** init_hash_table()
{
    int i;

/*aloca memoria do tipo EQUIPA necessaria para guardar TAM_HASH listas ligadas de equipas*/
    EQUIPA ** hashtable_equipas = can_fail_malloc(sizeof(EQUIPA)*TAM_HASH);

    for(i = 0; i < TAM_HASH; i++) hashtable_equipas[i] = NULL;

    return hashtable_equipas;
}

/*Funcao que adiciona uma nova_equipa a hashtable_equipas.*/
void add_equipa(EQUIPA ** hashtable_equipas, EQUIPA * nova_equipa)
{
    if (nova_equipa == NULL) return;
    else 
    {
        unsigned long indice = hash(nova_equipa -> nome);

/*adiciona nova_equipa no inicio da lista ligada respetiva a chave (indice) da hashtable*/
        nova_equipa -> next = hashtable_equipas[indice];
        hashtable_equipas[indice] = nova_equipa;
    }
}

/*Funcao que procura em hashtable_equipas uma equipa pelo seu nome.
    Retorna a equipa procurada caso encontrada e caso contrario nao retorna nada.*/
EQUIPA * procura_equipa(EQUIPA ** hashtable_equipas, char * nome)
{
    unsigned long indice = hash(nome);

/*tmp representa a head da lista ligada correspondente a chave (indice) da hashtable*/
    EQUIPA * tmp = hashtable_equipas[indice];

    if (tmp == NULL) return NULL;
    else
    {
        while(tmp != NULL)
        {
            if (strcmp(tmp -> nome , nome) == 0) return tmp;
            tmp = tmp -> next;
        }
        return NULL;
    }
}

/*Funcao que adiciona uma vitoria (score) a uma equipa dado o seu nome.*/
void add_score(EQUIPA ** hashtable_equipas, char * nome)
{   
    EQUIPA * equipa = procura_equipa(hashtable_equipas, nome);

    equipa -> score += 1;
}

/*Funcao que remove uma vitoria (score) a uma equipa dado o seu nome.*/
void remove_score(EQUIPA ** hashtable_equipas, char *nome)
{    
    EQUIPA * equipa = procura_equipa(hashtable_equipas, nome);

/*nao existe score negativo*/
    if (equipa -> score >= 1) equipa -> score -= 1;
    else
    {
        equipa -> score = 0;
    }
}

/*Funcao que retorna um inteiro que representa o maior_score que pelo
    menos uma equipa existente na hashtable_equipas tem.*/
int maior_score_equipa(EQUIPA ** hashtable_equipas)
{
    int i, maior_score = 0;
    EQUIPA * tmp = NULL;

    for(i = 0; i < TAM_HASH; i++)
    {
/*tmp representa a head da lista ligada correspondente a chave (indice) da hashtable*/
        tmp = hashtable_equipas[i];
        while(tmp != NULL)
        {
            if (maior_score < tmp -> score) maior_score = tmp -> score;
            tmp = tmp -> next;
        }
    }
    return maior_score;
}

/*Funcao que dado um score retorna um interiro que representa o numero de equipas 
    (num_equipas) existentes na hashtable_equipas que contem esse mesmo score dado.*/
int num_equipas(EQUIPA ** hashtable_equipas, int score)
{
    int i, num_equipas = 0;
    EQUIPA * tmp = NULL;

    for(i = 0; i < TAM_HASH; i++)
    {
/*tmp representa a head da lista ligada correspondente a chave (indice) da hashtable*/
        tmp = hashtable_equipas[i];

        while(tmp != NULL)
        {
            if (tmp -> score == score) num_equipas++;

            tmp = tmp -> next;
        }
    }
    return num_equipas;
}

/*Funcao que dado um nome cria uma nova_equipa com esse mesmo nome 
    e retorna a equipa criada.*/
EQUIPA * cria_equipa(char * nome)
{
/*aloca memoria do tipo EQUIPA para a equipa a criar*/
    EQUIPA * nova_equipa = can_fail_malloc(sizeof(EQUIPA));
    int len = strlen(nome);

/*aloca memoria do tipo char necessaria para guardar a string referente ao seu nome*/
    nova_equipa -> nome = can_fail_malloc(sizeof(char)*(len + 1));
    strcpy(nova_equipa -> nome, nome);

    nova_equipa -> score = 0;

    nova_equipa -> next = NULL;

    return nova_equipa;
}
/*Funcao que liberta a memoria alocada pela hashtable_equipas e seus elementos.*/
void destroy_hash_equipa(EQUIPA ** hashtable_equipas)
{
/*tmp representa a head da lista ligada correspondente a chave (indice) da hashtable*/
    EQUIPA * tmp = NULL;
    int i;

    for(i = 0; i < TAM_HASH; i++)
    {
        while((tmp = hashtable_equipas[i]) != NULL)
        {
            hashtable_equipas[i] = hashtable_equipas[i] -> next;
            free(tmp -> nome);
            free(tmp);
        }
    }
    free(hashtable_equipas);
}
