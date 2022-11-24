#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "hash_jogos.h"
#include "equipa.h"
#include "hash_equipas.h"
#include "jogo.h"
#include "lista_jogos.h"

/* Funcao que recebe um nome de um jogo e devolve
 * a respetiva hash key */
long hashU(char *v, int M)
{
    long h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1))
        h = (a * h + *v) % M;
    return h;
}

/* Funcao que recebe um inteiro e inicializa a hashtable
 * com o tamanho respetivo ao inteiro*/
link_jg *HT_jg_init(int M)
{
    link_jg *heads = can_fail_calloc(M, sizeof(link_jg));
    return heads;
}

/* Funcao que recebe as head da posicao respetiva na hashtable
 * e um ponteiro para a Lista jogos e insere na hashtable*/
link_jg insertJgBeginList(link_jg head, link_jogo ptr_link_jogo)
{
    if (head == NULL)
    {
        link_jg first_node = (link_jg)can_fail_malloc(sizeof(struct node_jg));
        first_node->ptr_link_jogo = ptr_link_jogo;
        first_node->next = NULL;
        return first_node;
    }
    else
    {
        link_jg new_node = (link_jg)can_fail_malloc(sizeof(struct node_jg));
        new_node->ptr_link_jogo = ptr_link_jogo;
        new_node->next = head;
        head = new_node;
        return new_node;
    }
}

/* Funcao que recebe um ponteiro para a Lista jogos, a Hash jogos e
 * o tamanho da ultima e chama a funcao insertJgBeginList com 
 * base na hash do nome do jogo */
void HT_jg_insert(link_jogo ptr_link_jogo, link_jg *heads_jg, int M)
{
    long i = hashU(key_jogo(ptr_link_jogo), M);
    heads_jg[i] = insertJgBeginList(heads_jg[i], ptr_link_jogo);
}

/* Funcao que recebe as head da posicao respetiva na hashtable
 * e um ponteiro para a Lista jogos e remove da hashtable*/
link_jg removeJgList(link_jg head, link_jogo ptr_link_jogo)
{
    link_jg t, prev;
    for (t = head, prev = NULL; t != NULL; prev = t, t = t->next)
    {
        if (strcmp(t->ptr_link_jogo->jogo->nome, ptr_link_jogo->jogo->nome) == 0)
        {
            if (t == head)
            {
                head = t->next;
            }
            else
            {
                prev->next = t->next;
            }
            free(t);
            break;
        }
    }
    return head;
}

/* Funcao que recebe um ponteiro para a Lista jogos, a Hash jogos e
 * o tamanho da ultima e chama a funcao removeJgList com 
 * base na hash do nome do jogo */
void HT_jg_delete(link_jogo ptr_link_jogo, link_jg *heads_jg, int M)
{
    long i = hashU(key_jogo(ptr_link_jogo), M);
    heads_jg[i] = removeJgList(heads_jg[i], ptr_link_jogo);
}

/* Funcao que recebe as head da posicao respetiva na hashtable
 * e um nome de um jogo e procura na Hash jogos*/
link_jogo searchJgList(link_jg head, Key_jogo c)
{
    link_jg t;
    for (t = head; t != NULL; t = t->next)
    {
        if (strcmp(t->ptr_link_jogo->jogo->nome, c) == 0)
            return t->ptr_link_jogo;
    }
    return NULL;
}

/* Funcao que recebe um nome de um jogo, a Hash jogos e
 * o tamanho da ultima e chama a funcao searchJgList com 
 * base na hash do nome do jogo */
link_jogo HT_jg_search(Key_jogo c, link_jg *heads_jg, int M)
{
    long i = hashU(c, M);
    return searchJgList(heads_jg[i], c);
}

/* Funcao que recebe a Hash jogos e o seu tamanho e
 * destroi a primeira libertando a memoria alocada */
void HT_jg_destroy(link_jg *heads_jg, int M)
{
    long i;
    link_jg temp = NULL;
    link_jg aux = NULL;
    for (i = 0; i < M; i++)
    {
        temp = heads_jg[i];
        while (temp != NULL)
        {
            aux = temp;
            temp = temp->next;
            free(aux);
        }
    }
    free(heads_jg);
}