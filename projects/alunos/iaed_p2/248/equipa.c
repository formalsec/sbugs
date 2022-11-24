#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"

/*
 * Functions
*/

Equipa * cria_equipa(char *nome){
    Equipa *equipa = (Equipa *) can_fail_malloc(sizeof(Equipa));
    equipa->vitorias = 0;
    equipa->nome = (char *) can_fail_malloc((1 + strlen(nome)) * sizeof(char));
    strcpy(equipa->nome, nome);
    return equipa;
}

void altera_vitorias_equipas(Equipa *equipa, int vitorias){
    equipa->vitorias = vitorias;
}

void liberta_equipa(Equipa *equipa){
    free(equipa->nome);
    free(equipa);
}

Lista_equipa * cria_lista_equipa(void){
    Lista_equipa *lista = (Lista_equipa *) can_fail_malloc(sizeof(Lista_equipa));
    lista->head = NULL;
    lista->tail = NULL;
    return lista;
}

void adiciona_lista_equipa(Lista_equipa *lista, Equipa *equipa){
    Node_equipa *node = (Node_equipa *) can_fail_malloc(sizeof(Node_equipa));
    node->equipa = equipa;

    if (lista->head == NULL && lista->tail == NULL){ /* caso em que a lista nao tem elementos */
        node->previous = NULL;
        node->next = NULL;
        lista->head = node;
        lista->tail = node;
    }
    else{
        node->previous = lista->tail; 
        node->next = NULL;
        lista->tail->next = node;
        lista->tail = node;
    }
}

Equipa * procura_lista_equipa(Lista_equipa *lista, char *equipa){
    Node_equipa *node_inicio = lista->head;
    Node_equipa *node_fim = lista->tail;

    while (node_inicio != node_fim && node_fim->next != node_inicio){ /*ciclo que percorre a lista de "fora para dentro" ate chegar-mos ao mesmo local */
        if (strcmp(node_inicio->equipa->nome, equipa) == 0){
            return node_inicio->equipa;                               
        }
        else if (strcmp(node_fim->equipa->nome, equipa) == 0){
            return node_fim->equipa;
        }
        node_inicio = node_inicio->next;
        node_fim = node_fim->previous;
    }

    if (node_inicio == node_fim && node_inicio != NULL){   /* caso de haver uma unica equipa na lista */
        if (strcmp(node_inicio->equipa->nome, equipa) == 0){
            return node_inicio->equipa;
        }
    }

    return NULL;
}

void liberta_lista_equipa(Lista_equipa *lista){
    Node_equipa *node = lista->head;
    Node_equipa *aux;

    while (node != NULL){
        aux = node->next;
        liberta_equipa(node->equipa);
        free(node);
        node = aux;
    }
    free(lista);
}

Hashtable_equipa * cria_hashtable_equipa(int tamanho){
    int i = 0;
    Hashtable_equipa *hashtable = (Hashtable_equipa *)
     can_fail_malloc(sizeof(Hashtable_equipa));
    hashtable->tamanho = tamanho;
    hashtable->tabela = (Lista_equipa **) can_fail_malloc(sizeof(Lista_equipa *) * tamanho);

    for (; i < tamanho; i++){ /* coloca todos os elementos da hashtable a NULL */
        *(hashtable->tabela + i) = NULL;
    }
    return hashtable;
}

void adiciona_hashtable_equipa(Hashtable_equipa *hashtable, Equipa *equipa){
    int i = hash_equipa(equipa->nome, hashtable->tamanho);

    if (*(hashtable->tabela + i) == NULL){
        *(hashtable->tabela + i) = cria_lista_equipa();
    }
    adiciona_lista_equipa(*(hashtable->tabela + i), equipa);
}

Equipa * procura_hashtable_equipa(Hashtable_equipa *hashtable, char *chave){
    int i = hash_equipa(chave, hashtable->tamanho);

    if (*(hashtable->tabela + i) != NULL){
        Equipa *equipa = procura_lista_equipa(*(hashtable->tabela + i), chave);
        return equipa;
    }
    return NULL;
}

Tabela_equipas * maximas_vitorias_equipa(Hashtable_equipa *hashtable){
    int i;
    int n_equipas = 0;
    int max_vitorias = 0;
    Equipa **equipas = NULL;
    Tabela_equipas *tabela = (Tabela_equipas *) can_fail_malloc(sizeof(Tabela_equipas));

    for (i = 0; i < hashtable->tamanho; i++){
        if (*(hashtable->tabela + i) != NULL){
            Node_equipa *node_inicio = (*(hashtable->tabela + i))->head;
            Node_equipa *node_fim = (*(hashtable->tabela + i))->tail;

            while (node_inicio != node_fim && node_fim->next != node_inicio){  /* ciclo que percorre a lista de "fora para dentro" ate chegar-mos ao mesmo local */
                if (node_inicio->equipa->vitorias > node_fim->equipa->vitorias ||
                 node_inicio->equipa->vitorias < node_fim->equipa->vitorias){ /* se o numero de vitorias de uma equipa for maior que a outra vamos ver qual deles e maior e verificar se e maior que max_vitorias */
                    Node_equipa *node;

                    if (node_inicio->equipa->vitorias > node_fim->equipa->vitorias){
                        node = node_inicio; 
                    }
                    else{
                        node = node_fim;
                    }

                    if (node->equipa->vitorias > max_vitorias){ /* se for maior que max_vitorias vamos realocar a memoria de equipas, de modo a esta ser so ocupada pela equipa com max_vitorias */
                        n_equipas = 1;
                        max_vitorias = node->equipa->vitorias;
                        equipas = (Equipa **) can_fail_realloc(equipas, sizeof(Equipa *));
                        *equipas = node->equipa;
                    }
                    else if (node->equipa->vitorias == max_vitorias){ /* se for igual a max_vitorias vamos realocar a memoria de equipas, de modo adicionar a nova equipa */
                        n_equipas++;
                        equipas = (Equipa **) can_fail_realloc(equipas,
                        n_equipas * sizeof(Equipa *));
                        *(equipas + (n_equipas - 1)) = node->equipa;
                    }
                }
                else{ /* caso em que node_inicio e node_fim tem o mesmo numero de vitorias*/
                    if (node_inicio->equipa->vitorias > max_vitorias){ /* se for maior que max_vitorias vamos realocar a memoria de equipas, de modo a esta ser ser ocupada pelas equipas com max_vitorias */
                        n_equipas = 2;
                        max_vitorias = node_inicio->equipa->vitorias;
                        equipas = (Equipa **) can_fail_realloc(equipas, 2 * sizeof(Equipa *));
                        *equipas = node_inicio->equipa;
                        *(equipas + 1) = node_fim->equipa;
                    }
                    else if (node_inicio->equipa->vitorias == max_vitorias){ /* se for igual a max_vitorias vamos realocar a memoria de equipas, de modo adicionar as duas novas equipas */
                        n_equipas += 2;
                        equipas = (Equipa **) can_fail_realloc(equipas,
                         n_equipas * sizeof(Equipa *));
                        *(equipas + (n_equipas - 1 - 1)) = node_inicio->equipa;
                        *(equipas + (n_equipas - 1)) = node_fim->equipa;
                    }
                }
                node_inicio = node_inicio->next;
                node_fim = node_fim->previous;
            }

            if (node_inicio == node_fim && node_inicio != NULL){ /* caso em que existe apenas uma equipa */
                if (node_inicio->equipa->vitorias > max_vitorias){
                    n_equipas = 1;
                    max_vitorias = node_inicio->equipa->vitorias;
                    equipas = (Equipa **) can_fail_realloc(equipas, sizeof(Equipa *));
                    *equipas = node_inicio->equipa;
                }
                else if (node_inicio->equipa->vitorias == max_vitorias){
                    n_equipas++;
                    equipas = (Equipa **) can_fail_realloc(equipas,
                     n_equipas * sizeof(Equipa *));
                    *(equipas + (n_equipas - 1)) = node_inicio->equipa;
                }
            }
        }
    }
    tabela->equipas = equipas;
    tabela->n_equipas = n_equipas;
    tabela->vitorias = max_vitorias;
    return tabela;
}

void liberta_hashtable_equipa(Hashtable_equipa *hashtable){
    int i;

    for (i = 0; i < hashtable->tamanho; i++){
        if (*(hashtable->tabela + i) != NULL){
            liberta_lista_equipa(*(hashtable->tabela + i));
        }
    }
    free(hashtable->tabela);
    free(hashtable);
}

int hash_equipa(char *chave, int tamanho){
    int i = 0;
    int a = 31415;
    int b = 27183;

    for (; *chave != '\0'; chave++, a = a * b % (tamanho - 1)) {
        i = (a * i + *chave) % tamanho;
    }

    return i;
}
