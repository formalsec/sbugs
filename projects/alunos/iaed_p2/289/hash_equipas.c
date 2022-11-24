#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash_equipas.h"

/* Funcao que recebe um nome de uma equipa e devolve
 * a respetiva hash key */
long hashUeq(char *v, int m)
{
    long h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (m - 1))
        h = (a * h + *v) % m;
    return h;
}

/* Funcao que recebe um inteiro e inicializa a hashtable
 * com o tamanho respetivo ao inteiro*/
link_eq *HT_eq_init(int m)
{
    link_eq *heads = can_fail_calloc(m, sizeof(link_eq));
    return heads;
}

/* Funcao que recebe as head da posicao respetiva na hashtable
 * e uma equipa e insere na hashtable*/
link_eq insertEqBeginList(link_eq head, ptr_equipa link_team)
{
    if (head == NULL)
    {
        link_eq first_node = can_fail_malloc(sizeof(struct node_eq));
        first_node->link_team = link_team;
        first_node->next = NULL;
        return first_node;
    }
    else
    {
        link_eq new_node = can_fail_malloc(sizeof(struct node_eq));
        new_node->link_team = link_team;
        new_node->next = head;
        return new_node;
    }
}
/* Funcao que recebe uma equipa, a Hash equipas e
 * o tamanho da ultima e chama a funcao insertEqBeginList com 
 * base na hash do nome da equipa */
void HT_eq_insert(ptr_equipa link_team, link_eq *heads_eq, int m)
{
    long i = hashUeq(key_equipa(link_team), m);
    heads_eq[i] = insertEqBeginList(heads_eq[i], link_team);
}

/* Funcao que recebe as head da posicao respetiva na hashtable
 * e um nome de uma equipa e procura na Hash equipas */
ptr_equipa searchEqList(link_eq head, Key_equipa c)
{
    link_eq t;
    for (t = head; t != NULL; t = t->next)
    {
        if (strcmp(t->link_team->nome, c) == 0)
            return t->link_team;
    }
    return NULL;
}

/* Funcao que recebe um nome de uma equipa, a Hash equipas e
 * o tamanho da ultima e chama a funcao searchEqList com 
 * base na hash do nome da equipa */
ptr_equipa HT_eq_search(Key_equipa c, link_eq *heads_eq, int m)
{
    long i = hashUeq(c, m);
    return searchEqList(heads_eq[i], c);
}

/* Funcao que recebe a Hash equipas e o seu tamanho e
 * destroi a primeira libertando a memoria alocada */
void HT_eq_destroy(link_eq *heads_eq, int m)
{
    long i;
    link_eq temp = NULL;
    link_eq aux = NULL;
    for (i = 0; i < m; i++)
    {
        temp = heads_eq[i];
        while (temp != NULL)
        {
            aux = temp;
            temp = temp->next;
            freeEquipa(aux->link_team);
            free(aux);
        }
    }
    free(heads_eq);
}