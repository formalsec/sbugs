#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"

/*
 * Functions
*/

Jogo * cria_jogo(char *nome, char *equipa1, char *equipa2, int pontuacao1, 
int pontuacao2){
    Jogo *jogo = (Jogo *) can_fail_malloc(sizeof(Jogo));
    jogo->pontuacao_1 = pontuacao1;
    jogo->pontuacao_2 = pontuacao2;
    jogo->nome = (char *) can_fail_malloc((1 + strlen(nome)) * sizeof(char));
    strcpy(jogo->nome, nome);
    jogo->equipa_1 = (char *) can_fail_malloc((1 + strlen(equipa1)) * sizeof(char));
    strcpy(jogo->equipa_1, equipa1);
    jogo->equipa_2 = (char *) can_fail_malloc((1 + strlen(equipa2)) * sizeof(char));
    strcpy(jogo->equipa_2, equipa2);
    return jogo;
}

void altera_pontucao_jogo(Jogo *jogo, int pontuacao1, int pontuacao2){
    jogo->pontuacao_1 = pontuacao1;
    jogo->pontuacao_2 = pontuacao2;
}

void liberta_jogo(Jogo *jogo){
    free(jogo->nome);
    free(jogo->equipa_1);
    free(jogo->equipa_2);
    free(jogo);
}

Lista_jogo * cria_lista_jogo(void){
    Lista_jogo *lista = (Lista_jogo *) can_fail_malloc(sizeof(Lista_jogo));
    lista->head = NULL;
    lista->tail = NULL;
    return lista;
}

void adiciona_lista_jogo(Lista_jogo *lista, Jogo *jogo){
    Node_jogo *node = (Node_jogo *) can_fail_malloc(sizeof(Node_jogo));
    node->jogo = jogo;

    if (lista->head == NULL && lista->tail == NULL){  /* caso de a lista nao ter elementos */
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

Node_jogo * procura_lista_jogo(Lista_jogo *lista, char *jogo){
    Node_jogo *node_inicio = lista->head;
    Node_jogo *node_fim = lista->tail;

    while (node_inicio != node_fim && node_fim->next != node_inicio){ /* ciclo que percorre a lista de "fora para dentro" ate chegar-mos ao mesmo local */
        if (strcmp(node_inicio->jogo->nome, jogo) == 0){
            return node_inicio;
        }
        else if (strcmp(node_fim->jogo->nome, jogo) == 0){
            return node_fim;
        }
        node_inicio = node_inicio->next;
        node_fim = node_fim->previous;
    }

    if (node_inicio == node_fim && node_inicio != NULL){ /* caso de haver um unico jogo na lista */
        if (strcmp(node_inicio->jogo->nome, jogo) == 0){
            return node_inicio;
        }
    }

    return NULL;
}

void remove_lista_jogo(Lista_jogo *lista, Jogo *jogo){
    Node_jogo *node;
    node = procura_lista_jogo(lista, jogo->nome);

    if (node != NULL){
        if (node == lista->head && node == lista->tail){  /* se node == lista->head && node == lista->tail a lista so tem um elemento, logo vamos remove-lo */
            lista->head = NULL;
            lista->tail = NULL;
        }
        else{
            if (node == lista->head){
                node->next->previous = NULL;
                lista->head = node->next;
            }
            else if (node == lista->tail){
                node->previous->next = NULL;
                lista->tail = node->previous;
            }
            else{
                node->previous->next = node->next;  
                node->next->previous = node->previous;
            }
        }
        free(node);
    }
}

void imprime_lista_jogo(Lista_jogo *lista, int linha_input){
    Node_jogo *node = lista->head;

    while (node != NULL){
        printf("%d %s %s %s %d %d\n", linha_input, node->jogo->nome,
         node->jogo->equipa_1, node->jogo->equipa_2, node->jogo->pontuacao_1,
         node->jogo->pontuacao_2);
         node = node->next;
    }
}

void liberta_lista_jogo(Lista_jogo *lista){
    Node_jogo *node = lista->head;
    Node_jogo *aux;

    while (node != NULL){
        aux = node->next;
        liberta_jogo(node->jogo);
        free(node);
        node = aux;
    }
    free(lista);
}

Hashtable_jogo * cria_hashtable_jogo(int tamanho){
    int i = 0;
    Hashtable_jogo *hashtable = (Hashtable_jogo *)
     can_fail_malloc(sizeof(Hashtable_jogo));
    hashtable->tamanho = tamanho;
    hashtable->tabela = (Lista_jogo **) can_fail_malloc(sizeof(Lista_jogo *) * tamanho);

    for (; i < tamanho; i++){ /* ciclo que coloca todos os elementos da hashtable a NULL */
        *(hashtable->tabela + i) = NULL;
    }
    return hashtable;
}

void adiciona_hashtable_jogo(Hashtable_jogo *hashtable, Jogo *jogo){
    int i = hash_jogo(jogo->nome, hashtable->tamanho);

    if (*(hashtable->tabela + i) == NULL){
        *(hashtable->tabela + i) = cria_lista_jogo();
    }
    adiciona_lista_jogo(*(hashtable->tabela + i), jogo);
}

Jogo * procura_hashtable_jogo(Hashtable_jogo *hashtable, char *chave){
    int i = hash_jogo(chave, hashtable->tamanho);

    if (*(hashtable->tabela + i) != NULL){
        Node_jogo *node = procura_lista_jogo(*(hashtable->tabela + i), chave);

        if (node != NULL){
            return node->jogo;
        }
    }
    return NULL;
}

Jogo * remove_hashtable_jogo(Hashtable_jogo *hashtable, char *chave){
    int i = hash_jogo(chave, hashtable->tamanho);
    Jogo *jogo = (procura_lista_jogo(*(hashtable->tabela + i), chave))->jogo;

    if (jogo != NULL){
        remove_lista_jogo(*(hashtable->tabela + i), jogo);
    }

    if ((*(hashtable->tabela + i))->head == NULL){
        free(*(hashtable->tabela + i));
        *(hashtable->tabela + i) = NULL;
    }

    return jogo;
}

void liberta_hashtable_jogo(Hashtable_jogo *hashtable){
    int i = 0;

    for (; i < hashtable->tamanho; i++){ 
        if (*(hashtable->tabela + i) != NULL){ 
            Node_jogo *node = (*(hashtable->tabela + i))->head;
            Node_jogo *aux;
            while (node != NULL){
                aux = node->next;
                free(node);
                node = aux;
            }
            free(*(hashtable->tabela + i));
        }
    }
    free(hashtable->tabela);
    free(hashtable);
}

int hash_jogo(char *chave, int tamanho){
    int i = 0;
    int x = 31415;
    int y = 27183;

    for (; *chave != '\0'; chave++, x = x * y % (tamanho - 1)) {
        i = (x * i + *chave) % tamanho;
    }

    return i;
}
