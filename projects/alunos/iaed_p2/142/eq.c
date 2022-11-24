#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq.h"
#include "j.h"

/* Descobre o indice na hashtable de um dado nome */
unsigned int hash(const char *key, unsigned int size)
{
        unsigned int hash;
        unsigned int i;

        hash = 0;
        i = 0;
        while (key && key[i]) {
                hash = (hash + key[i]) % size;
                ++i;
        }
        return (hash);
}

/* Cria a hashtable das equipas */
HashTable2 *ht_create_eq()
{
    HashTable2 *ht = can_fail_malloc(sizeof(HashTable2));
    ht->size = SIZE;
    ht->array = can_fail_calloc(ht->size, sizeof(equipa*));
    return ht;
}

/* Retira um ponto de uma equipa da hashtable */
int vit_handler_aux(HashTable2 *hashtable, char *nome)
{
    unsigned int i = hash(nome, hashtable->size);
    equipa *tmp = hashtable->array[i];

    while (tmp != NULL) 
    {
        if (strcmp(tmp->nome, nome) == 0)
            break;
        tmp = tmp->next;
    }
    tmp->vitoria = (tmp->vitoria)-1;
        
    return 0;
}

/* Adiciona um ponto de uma equipa da hashtable */
int vit_handler(HashTable2 *hashtable, char *nome)
{
    unsigned int i = hash(nome, hashtable->size);
    equipa *tmp = hashtable->array[i];

    while (tmp != NULL) 
    {
        if (strcmp(tmp->nome, nome) == 0)
            break;
        tmp = tmp->next;
    }
    tmp->vitoria = (tmp->vitoria)+1;
        
    return 0;
}

/* Procura uma equipa com o nome dado e devolve a */
equipa *ht_lookup_eq(HashTable2 *hashtable, const char *key)
{
    unsigned int i = hash(key, hashtable->size);
    equipa *tmp = hashtable->array[i];
    while (tmp!= NULL && strcmp(tmp->nome, key)!=0)
    {
        tmp = tmp->next;
    }
    return tmp;
}

/* Insere uma determinada equipa a hashtable */
int ht_insert_eq(HashTable2 *hashtable, equipa *eq)
{
    unsigned int i;
    i = hash(eq->nome, hashtable->size);
    if(eq == NULL)
        return 1;
    eq->next = hashtable->array[i];
    hashtable->array[i] = eq;
    return 0;
}

/* Verifica se uma determinada equipa existe na hashtable */
int check_eq(HashTable2 *hashtable, const char *nome)
{
    int i = hash(nome, hashtable->size);
    equipa *m;
    for(m = hashtable->array[i]; m != NULL; m=m->next)
    {
        if (strcmp(m->nome, nome)==0)
            return 0;
    }
    return 1;
}

/* Da free a uma equipa */
void free_eq(equipa *eq)
{
    free(eq->nome);
    free(eq);
}

/* Da free a hashtable das equipas */
void free_hash_table_e(HashTable2 *ht)
{
    equipa *a;
    size_t i;
    for (i=0; i< ht->size; i++)
    {
        while (ht->array[i])
        {
            a= ht->array[i]->next;
            free(ht->array[i]);
            ht->array[i]=a;
        }
    }
    free(ht->array);
    free(ht);
}

/* Adiciona uma nova equipa a hashtable. */
void A(int NL, HashTable2 *hashtable)
{
    char nome[MAXIJOGO];
    equipa *eq = can_fail_malloc(sizeof(equipa));
    getchar();
    scanf("%[^:\n]", nome);
    if(check_eq(hashtable, nome) == 0)
        printf("%d Equipa existente.\n", NL);
    else
    {
        eq->nome = can_fail_malloc(sizeof(char)*(strlen(nome)+1));
        strcpy(eq->nome, nome);
        eq->vitoria = 0;
        ht_insert_eq(hashtable, eq);
    }
}

/* Procura uma equipa dado um nome. */
void P(int NL, HashTable2 *hashtable)
{
    char nome[MAXIJOGO];
    equipa *eq;
    getchar();
    scanf("%[^:\n]", nome);
    if(check_eq(hashtable, nome) == 1)
        printf("%d Equipa inexistente.\n", NL);
    else
    {
        eq = ht_lookup_eq(hashtable, nome);
        printf("%d %s %d\n", NL, eq->nome, eq->vitoria);
    }
}

/* Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa). */
void g(int NL, HashTable2 *hashtable)
{
    equipa *m;
    size_t i;
    char **tab, *tmp;
    int x,y, cont;
    int j=-1, k=0;
    /* Procura a pontuacao mais alta */
    for (i=0; i< hashtable->size; i++)
    {
        for(m = hashtable->array[i]; m != NULL; m=m->next)
        {
            if ((m->vitoria)>j)
            {
                j = m->vitoria;
                cont=1;
            }
            else if ((m->vitoria)==j)
                cont++;

        }
    }

    /* Se nao houver nenhuma equipa entao nao retorna nada */
    if(j==-1)
        return;

    /* Copia para a tabela todas as equipas que tenham a pontuacao mais alta */
    tab = can_fail_malloc(sizeof(char*)*(cont+1));
    for (i=0; i< hashtable->size; i++)
    {
        for(m = hashtable->array[i]; m != NULL; m=m->next)
        {
            if ((m->vitoria)==j)
            {
                tab[k] = can_fail_malloc(sizeof(char)*(strlen(m->nome)+1));
                strcpy(tab[k],m->nome);
                k++;
            }
        }
    }
    
    /* Lista por ordem lexicografica */
    for(x=0; x<=(cont-1); x++)
    {
        for(y=x+1; y<=(cont-1); y++)
        {
            if(strcmp(tab[x],tab[y])>0)
            {
                tmp = can_fail_malloc(sizeof(char)*(strlen(tab[x])+1));
                strcpy(tmp,tab[x]);
                tab[x] = can_fail_realloc(tab[x], (strlen(tab[y])+1));
                strcpy(tab[x],tab[y]);
                tab[y] = can_fail_realloc(tab[y], (strlen(tmp)+1));
                strcpy(tab[y],tmp);
                free(tmp);
            }
        }
    }
    printf("%d Melhores %d\n", NL, j);
    for(x=0; x<cont; x++)
        printf("%d * %s\n", NL, tab[x]);
    for(x=0; x<cont; x++)
        free(tab[x]);
    free(tab);
}
