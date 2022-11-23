#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Jogos.h"
#include "Equipas.h"
#include "Misc.h"

/* Inicializa um novo jogo com os argumentos fornecidos na funcao adiciona_jogo. */
jogo* cria_jogo(char* nome, equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    jogo* novo_jogo = (jogo*) can_fail_malloc(sizeof(jogo));
    novo_jogo -> nome = (char*) can_fail_malloc (strlen(nome)+1);
    strcpy(novo_jogo -> nome, nome);
    novo_jogo -> eq_casa = eq_casa;
    novo_jogo -> eq_fora = eq_fora;
    novo_jogo -> golos_casa = golos_casa;
    novo_jogo -> golos_fora = golos_fora;
    atribui_vitoria(eq_casa, eq_fora, golos_casa, golos_fora);
    return novo_jogo;
}


/* FUNCOES SOBRE LISTAS DUPLAMENTE LIGADAS DE JOGOS */

/* Inicializa uma lista duplamente ligada de jogos. */
lista_jogos* cria_lst_jogos()
{
    lista_jogos* novo = can_fail_malloc(sizeof(lista_jogos));
    novo -> inicio = novo -> fim = NULL;
    return novo;
}

/* Insere um jogo como ultimo elemento (tail) da lista. */
void insere_fim_jogo(lista_jogos* l, jogo* novo_jogo)
{
    node_jogo* n = (node_jogo*) can_fail_malloc(sizeof(node_jogo));
    n -> prox = NULL;
    n -> ant = l -> fim;
    n -> jogo = novo_jogo;
    if (l -> fim)
        l -> fim -> prox = n;
    l -> fim = n;
    if (!l -> inicio)
        l -> inicio = n;
}

/* Remove um jogo da lista, caso o seu nome coincida com o fornecido. */
void remove_jogo_lst(lista_jogos* l, char* nome)
{
    node_jogo* aux1 = l -> inicio;
    while (aux1)
    {
        if (!strcmp(aux1 -> jogo -> nome, nome))
        {
            node_jogo* aux2 = aux1;
            if (l -> inicio == l -> fim)
                l -> inicio = l -> fim = NULL; 
            else if (aux1 == l -> inicio)
            {
                l -> inicio = l -> inicio -> prox;
                aux1 -> prox -> ant = NULL;
            }
            else if (aux1 == l -> fim)
            {
                l -> fim = l -> fim -> ant;
                aux1 -> ant -> prox = NULL;
            }
            else
            {
                aux1 -> ant -> prox = aux1 -> prox;
                aux1 -> prox -> ant = aux1 -> ant;
            }
            free(aux2);
            break;
        }
        aux1 = aux1 -> prox;
    }
}

/* Remove todos os jogos da lista, a qual e destruida no final. */
void destroi_lst_jogos(lista_jogos* l)
{
    while (l -> fim)
    {
        node_jogo* aux = l -> fim -> ant;
        free(l -> fim);
        l -> fim = aux;
    }
    free(l);
}


/* FUNCOES SOBRE HASH TABLES DE JOGOS: Esta hash table recorre a resolucao
 * linear de conflitos entre keys com o mesmo valor (linear probing). */

/* Insere um jogo na hash table. Se o numero de jogos ultrapassar metade da hash
 * table, ela e realocada para uma nova tabela com o dobro da dimensao inicial. */
jogo** insere_jogo_h(jogo** h_jogos, jogo* novo_jogo, int* cont_jogos, int* tam_h_jogos)
{
    int i = hash(novo_jogo -> nome, *tam_h_jogos);
    while (h_jogos[i])
        i = (i+1) % (*tam_h_jogos);
    h_jogos[i] = novo_jogo;
    if (*cont_jogos > *tam_h_jogos/2) /* Verifica se e necessaria realocacao. */
        h_jogos = expande_h_jogos(h_jogos, cont_jogos, tam_h_jogos);
    return h_jogos;
}

/* Duplica uma hash table de jogos e efetua o respetivo rehashing dos seus elementos. */
jogo** expande_h_jogos(jogo** h_jogos, int* cont_jogos, int* tam_h_jogos)
{
    int j, novo_tam_h_jogos = 2*(*tam_h_jogos);
    jogo** aux = (jogo**) can_fail_calloc (novo_tam_h_jogos, sizeof(jogo*));
    for (j = 0; j < *tam_h_jogos; j++)
        if (h_jogos[j])
            insere_jogo_h(aux, h_jogos[j], cont_jogos, &novo_tam_h_jogos);
    free(h_jogos);
    *tam_h_jogos = novo_tam_h_jogos;
    return aux;
}


/* Procura um jogo na hash table, dado um nome.
 * Se ele existir, um ponteiro para esse jogo e devolvido pela funcao. */
jogo* procura_jogo_h(char* nome, jogo** h_jogos, int tam_h_jogos)
{
    int i = hash(nome, tam_h_jogos);
    for (; h_jogos[i]; i = (i+1) % tam_h_jogos)
        if (!strcmp(h_jogos[i] -> nome, nome))
            return h_jogos[i];
    return NULL;
}

/* Remove todos os jogos da hash table (incluindo os seus
 * nomes) previamente alocados, e destroi a propria tabela. */
void destroi_h_jogos(jogo** h_jogos, int tam_h_jogos)
{
    int i;
    for (i = 0; i < tam_h_jogos; i++)
        if (h_jogos[i])
        {
            free(h_jogos[i] -> nome);
            free(h_jogos[i]);
        }
    free(h_jogos);
}
