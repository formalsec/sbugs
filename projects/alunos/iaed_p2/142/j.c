#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq.h"
#include "j.h"

/* Cria a lista duplamente ligada */
list2 *list2_create()
{
    list2 *l = can_fail_malloc(sizeof(list2));
    l->head = l->last = NULL;
    return l;
}

/* Da free a um determinado jogo */
void free_node(List *n)
{
    free(n->eq2);
    free(n->eq1);
    free(n->key);
    free(n);
}

/* Da free a lista duplamente ligada */
void free_list2(list2 *l)
{
    while(l->head)
    {
        List *tmp = l->head->next;
        free_node(l->head);
        l->head = tmp;
    }
    free(l);
}

/* Adiciona um jogo ao final da lista duplamente ligada */
void add_list2(list2 *l, List *n)
{
    List *tmp = can_fail_malloc(sizeof(List));
    tmp->previous = l->last;
    tmp->next = NULL;
    tmp->key = can_fail_malloc(sizeof(char)*(strlen(n->key)+1));
    strcpy(tmp->key, n->key);
    tmp->eq1 = can_fail_malloc(sizeof(char)*(strlen(n->eq1)+1));
    strcpy(tmp->eq1, n->eq1);
    tmp->eq2 = can_fail_malloc(sizeof(char)*(strlen(n->eq2)+1));
    strcpy(tmp->eq2, n->eq2);
    tmp->score1 = n->score1;
    tmp->score2 = n->score2;
    if(l->last)
        l->last->next = tmp;
    else
        l->head = tmp;
    l->last = tmp;
}

/* Atualiza as pontuacoes de um determinado jogo na lista duplamente ligada */
void list2_handler(list2 *ls, char *nome, int score1, int score2)
{
    List *n;
    for(n=ls->head; n; n=n->next)
    {
        if(strcmp(n->key, nome)==0)
            break;
    }
    n->score1 = score1;
    n->score2 = score2;
}

/* Cria a hashtable dos jogos */
HashTable *ht_create()
{
    HashTable *ht = can_fail_malloc(sizeof(HashTable));
    ht->size = SIZE;
    ht->array = can_fail_calloc(ht->size, sizeof(List*));
    return ht;
}

/* Verifica se um determinado jogo existe na hashtable */
int ht_get(HashTable *hashtable, const char *key)
{
        unsigned int i;
        List *tmp;

        if (hashtable == NULL)
                return 1;

        i = hash(key, hashtable->size);
        tmp = hashtable->array[i];

        while (tmp != NULL) 
        {
                if (strcmp(tmp->key, key) == 0) 
                        return 0;
                tmp = tmp->next;
        }

        return 1;
}

/* Insere um determinado jogo a hashtable */
void ht_insert(HashTable *hashtable, List *jogo) 
{
    unsigned int i;
    i = hash(jogo->key, hashtable->size);
    if(hashtable->array[i]!=NULL)
        hashtable->array[i]->previous = jogo;
    jogo->next = hashtable->array[i];
    hashtable->array[i] = jogo;
}

/* Procura um jogo com o nome dado e devolve o */
List *ht_lookup(HashTable *hashtable, const char *key)
{
    unsigned int i = hash(key, hashtable->size);
    List *tmp = hashtable->array[i];
    while (tmp!= NULL && strcmp(tmp->key, key)!=0){
        tmp = tmp->next;
    }
    return tmp;
}

/* Atualiza as pontuacoes de um determinado jogo na hashtable */
int score_handler(HashTable *hashtable, char *nome, int s1, int s2)
{
    unsigned int i = hash(nome, hashtable->size);
    List *tmp = hashtable->array[i];

    while (tmp != NULL) 
    {
        if (strcmp(tmp->key, nome) == 0)
            break;
        tmp = tmp->next;
    }
    tmp->score1 = s1;
    tmp->score2 = s2;
        
    return 0;
}

/* Da free a hashtable dos jogos */
void free_hash_table_j(HashTable *ht)
{
    free(ht->array);
    free(ht);
}

/* Adiciona um novo jogo a hashtable. */
void a(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls)
{
    char key[MAXIJOGO], eq1[MAXIJOGO], eq2[MAXIJOGO];
    int score1, score2;
    List *name = can_fail_malloc(sizeof(List));

    getchar();
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", key, eq1, eq2, &score1, &score2);

    name->key = can_fail_malloc(sizeof(char)*(strlen(key)+1));
    strcpy(name->key, key);
    name->eq1 = can_fail_malloc(sizeof(char)*(strlen(eq1)+1));
    strcpy(name->eq1, eq1);
    name->eq2 = can_fail_malloc(sizeof(char)*(strlen(eq2)+1));
    strcpy(name->eq2, eq2);
    name->score1 = score1;
    name->score2 = score2;
    
    if(ht_get(hashtable, key) != 1)
    {
        printf("%d Jogo existente.\n", NL);
    }
    else if(check_eq(hash_eq, eq1)==1 || check_eq(hash_eq, eq2)==1)
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
        if(score1 > score2)
        {
            vit_handler(hash_eq, eq1);
        }
        else if (score1 < score2)
        {
            vit_handler(hash_eq, eq2);
        }

        ht_insert(hashtable, name);
        add_list2(ls, name);
    }
}

/* Lista todos os jogos introduzidos. */
void l(int NL, list2 *ls)
{
    List *n;
    if(ls->head != NULL)
    {
        for(n = ls->head; n; n=n->next)
            printf("%d %s %s %s %d %d\n", NL, n->key, n->eq1, n->eq2, n->score1, n->score2);
    }

}

/* Procura um jogo com o nome dado. */
void p(int NL, HashTable *hashtable)
{
    char nome[MAXIJOGO];
    List *jogo;
    int i;
    getchar();
    scanf("%[^:\n]", nome);
    i = hash(nome, hashtable->size);

    if(ht_get(hashtable, nome) == 1)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        for(jogo = hashtable->array[i]; jogo!=NULL; jogo=jogo->next)
            if(strcmp(jogo->key, nome)==0)
                break;
        printf("%d %s %s %s %d %d\n", NL,jogo->key, jogo->eq1, jogo->eq2, jogo->score1, jogo->score2);
    }
}

/*  Apaga um jogo dado um nome. */
void r(int NL, HashTable *hashtable, list2 *ls, HashTable2 *ht_eq)
{
    char nome[MAXIJOGO];
    int i;
    List *tmp, *a;
    getchar();
    scanf("%[^:\n]", nome);
    i = hash(nome, hashtable->size);
    if(ht_get(hashtable, nome) == 1)
        printf("%d Jogo inexistente.\n", NL);
    else
    {
        for(tmp = ls->head; tmp!=NULL; tmp=tmp->next)
            if(strcmp(tmp->key, nome)==0)
                break;
        /* Remove jogo da lista de jogos */
        if(tmp->previous == NULL)
            ls->head = tmp->next;
        else
            tmp->previous->next = tmp->next;
        if(tmp->next == NULL)
            ls->last = tmp->previous;
        else
            tmp->next->previous = tmp->previous;
        free_node(tmp);

        for(a = hashtable->array[i]; a!=NULL; a=a->next)
            if(strcmp(a->key, nome)==0)
                break;

        if(a->score1 > a->score2)
            vit_handler_aux(ht_eq, a->eq1);

        if(a->score1 < a->score2)
            vit_handler_aux(ht_eq, a->eq2);
        /* Remove jogo da hashtable */
        if(a == hashtable->array[i])
            hashtable->array[i] = a->next;
        else 
            a->previous->next = a->next;
        free_node(a);

    }
}

/* Altera o score de um jogo dado o nome. */
void s(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls)
{
    char nome[MAXIJOGO];
    int score1, score2;
    List *tmp;
    getchar();
    scanf("%[^:\n]:%d:%d", nome, &score1, &score2);
    if(ht_get(hashtable, nome) == 1)
    {
        printf("%d Jogo inexistente.\n", NL);
    }
    else
    {
        tmp = ht_lookup(hashtable, nome);
        if((tmp->score1)==(tmp->score2))
        {
            if(score1 > score2)
                vit_handler(hash_eq, tmp->eq1);
            else if(score1 < score2)
                vit_handler(hash_eq, tmp->eq2);
        }
        else if((tmp->score1) > (tmp->score2))
        {
            if(score1 < score2)
            {
                vit_handler(hash_eq, tmp->eq2);
                vit_handler_aux(hash_eq, tmp->eq1);
            }
            else if(score1==score2)
                vit_handler_aux(hash_eq, tmp->eq1);
        }
        else if ((tmp->score1) < (tmp->score2))
        {
            if(score1 > score2)
            {
                vit_handler(hash_eq, tmp->eq1);
                vit_handler_aux(hash_eq, tmp->eq2);
            }
            else if(score1==score2)
                vit_handler_aux(hash_eq, tmp->eq2);
        }
        score_handler(hashtable, nome, score1, score2);
        list2_handler(ls, nome, score1, score2);
    }
}
