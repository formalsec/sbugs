#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcoes.h"

/* --------CONSTANTES------------*/

/* Tamanho maximo de uma string */
#define STR_MAX 1023

/* Tamanho da hash table */
#define TAM_HASH 1091

/* Constantes para descrever o resultado de um jogo */
#define EMPATE 0
#define VITORIA_E1 1
#define VITORIA_E2 2


/*---------- FUNCOES AUXILIARES -------------*/
int funcao_comparacao( const void *equipa1, const void *equipa2);
int obtem_resultado(int score1, int score2);
void free_hashequipas(linkeq* hash_equipas);
void free_listajogos(lista l);
void free_hash_jogos(item_hash_jg* hash_jogos);


/*--------- FUNCOES PRINCIPAIS ------------*/
void adiciona_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista_jogos, int linha);
void lista_todos_jogos(lista lista_jogos, int linha);
void procura_jogo(item_hash_jg* hash_jogos, int linha);
void apaga_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista, int linha);
void altera_score(item_hash_jg* hash_jogos, linkeq* hash_equipas, int linha);
void adiciona_equipa(linkeq* hash_equipas, int linha);
void procura_equipa(linkeq* hash_equipas, int linha);
void lista_melhores_equipas(linkeq* hash_equipas, int linha);


/* ------------------------------------------------------------------ */


/* Funcao que adiciona um jogo ao sistema. 
                -INPUT-                              -OUTPUT-
    a nome:equipa1:equipa2:score1:score2              ------.
*/
void adiciona_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista_jogos, int linha){
    char nome[STR_MAX], equipa1[STR_MAX], equipa2[STR_MAX];
    int score1, score2;
    jogo *novo_jogo;
    linkjg new;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa1, equipa2,&score1,&score2);

    /* Se ja existir um jogo com esse nome no sistema */
    if (encontra_jogo(hash_jogos, nome) != NULL){
        printf("%d Jogo existente.\n", linha);
        return;
    }

    /* Verifica se ambas as equipas existem no sistema */
    if (encontra_equipa(hash_equipas, equipa1) == NULL || encontra_equipa(hash_equipas, equipa2) == NULL){
        printf("%d Equipa inexistente.\n", linha);
        return;
    }

    /* Criacao de um novo jogo e de um ponteiro para o mesmo */
    novo_jogo = (jogo*) malloc(sizeof(jogo));

    novo_jogo->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(novo_jogo->nome,nome);

    novo_jogo->equipa1 = (char*) malloc(sizeof(char)*(strlen(equipa1)+1));
    strcpy(novo_jogo->equipa1, equipa1);

    novo_jogo->equipa2 = (char*) malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(novo_jogo->equipa2, equipa2);

    novo_jogo->score1 = score1;
    novo_jogo->score2 = score2;

    /* Acrescentar uma vitoria a equipa vencedora (se nao for empate) */
    if (score1 > score2)
        encontra_equipa(hash_equipas, equipa1)->pequipa->vitorias++;
    
    else if (score2 > score1)
        encontra_equipa(hash_equipas, equipa2)->pequipa->vitorias++;

    /* Insercao do ponteiro para o jogo na lista de jogos */
    new = add_lista(lista_jogos, novo_jogo);

    /* Insercao de um novo item na hash dos jogos com o ponteiro para o jogo */
    HashJogos_insere(hash_jogos, new);

}


/* Funcao que lista todos os jogos. Os jogos sao listados pela ordem em
que foram introduzidos no sistema. 
            -INPUT-                         -OUTPUT-
                l       * NL nome-jogo1 nome-equipa1 nome-equipa2 score1 score2
                        * ...
*/
void lista_todos_jogos(lista lista_jogos, int linha){
    linkjg aux = lista_jogos->head;

    while (aux != NULL){
        printf("%d %s %s %s %d %d\n", linha, aux->jogo->nome,
                                            aux->jogo->equipa1,
                                            aux->jogo->equipa2,
                                            aux->jogo->score1,
                                            aux->jogo->score2);
        aux = aux->next;
    }
}


/* Funcao que procura um jogo com o nome dado no sistema.
           -INPUT-                      -OUTPUT-
           p nome        NL nome-jogo nome-equipa1 nome-equipa2 score1 score2
*/
void procura_jogo(item_hash_jg* hash_jogos, int linha){
    char nome[STR_MAX];
    item_hash_jg aux;
    jogo *jogo_procurado;

    scanf(" %[^:\n]", nome);

    /* aux sera o item da hash com o ponteiro para jogo pretendido */
    aux = encontra_jogo(hash_jogos, nome);

    /* Caso o jogo exista no sitema */
    if (aux != NULL){
        jogo_procurado = aux->pno->jogo;
    
        printf("%d %s %s %s %d %d\n", linha, jogo_procurado->nome,
                                            jogo_procurado->equipa1,
                                            jogo_procurado->equipa2,
                                            jogo_procurado->score1,
                                            jogo_procurado->score2);
    
    }

    /* Se o jogo nao existir */
    else
        printf("%d Jogo inexistente.\n", linha);
    
}


/* Funcao que apaga um jogo do sistema dado o nome.
           -INPUT-                -OUTPUT-
           r nome                 --------
*/
void apaga_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista, int linha){

    char nome[STR_MAX];
    item_hash_jg aux;
    int key, resultado_jogo;

    scanf(" %[^:\n]", nome);

    /* aux sera o item da hash com o ponteiro para jogo pretendido */
    aux = encontra_jogo(hash_jogos, nome);
    key = hashfunc(nome);

    /* Caso o jogo nao exista no sistema */
    if (aux == NULL){
        printf("%d Jogo inexistente.\n", linha);
        return;
    }

    /* Obter resultado do jogo */
    resultado_jogo = obtem_resultado(aux->pno->jogo->score1, aux->pno->jogo->score2);

    /* Retirar uma vitoria a equipa vencedora (se houver) */
    if (resultado_jogo == VITORIA_E1)
        encontra_equipa(hash_equipas, aux->pno->jogo->equipa1)->pequipa->vitorias--;
        
    else if (resultado_jogo == VITORIA_E2)
        encontra_equipa(hash_equipas, aux->pno->jogo->equipa2)->pequipa->vitorias--;

    /* Apagar o jogo do sistema */
    /* Caso seja o primeiro elemento da hash_jogos[key] */
    if (aux->prev == NULL){
        remove_lista(aux->pno, lista);

        /* Se for o unico elemento da hash_jogos[key] */
        if (aux->next != NULL)
            hash_jogos[key]->next->prev = NULL;

        hash_jogos[key] = hash_jogos[key]->next;
    }

    /* Caso seja o ultimo elemento da hash_jogos[key] */
    else if (aux->next == NULL){
        remove_lista(aux->pno, lista);
        aux->prev->next = NULL;
    }

    /* Caso nao seja nenhuma das extremidades */
    else {
        remove_lista(aux->pno, lista);
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }

    free(aux);

}


/* Funcao que altera o score de um jogo com um dado nome.
                -INPUT-                -OUTPUT-
         s nome:score1:score2          --------
*/
void altera_score(item_hash_jg* hash_jogos, linkeq* hash_equipas, int linha){
    char nome_jogo[STR_MAX], equipa1[STR_MAX], equipa2[STR_MAX];
    int score1, score2;
    int resultado_antigo, resultado_novo;
    item_hash_jg aux;

    scanf(" %[^:\n]:%d:%d", nome_jogo, &score1, &score2);

    /* aux sera o item da hash com o ponteiro para jogo pretendido */
    aux = encontra_jogo(hash_jogos, nome_jogo);

    /* Caso nao exista um jogo no sistema com esse nome */
    if (aux == NULL){
        printf("%d Jogo inexistente.\n", linha);
        return;
    }
    
    /* Obter os nomes das equipas envolvidas no jogo */
    strcpy(equipa1, aux->pno->jogo->equipa1);
    strcpy(equipa2, aux->pno->jogo->equipa2);

    /* Determinar o resultado do jogo antes de ser mudado */
    resultado_antigo = obtem_resultado(aux->pno->jogo->score1, aux->pno->jogo->score2);    

    /* Atualizar os scores das equipas no jogo */
    aux->pno->jogo->score1 = score1;
    aux->pno->jogo->score2 = score2;


    /* Determinar o vencedor segundo o novo resultado */
    resultado_novo = obtem_resultado(score1, score2);

    /* Alteracao do numero de vitoria de ambas as equipas em funcao
    do antigo e do novo resultado */
    if (resultado_antigo == EMPATE){

        /* Incrementa as vitorias do novo vencedor (caso exista) */

        if (resultado_novo == VITORIA_E1)
            encontra_equipa(hash_equipas, equipa1)->pequipa->vitorias++;
    
        else if (resultado_novo == VITORIA_E2)
            encontra_equipa(hash_equipas, equipa2)->pequipa->vitorias++;
    }

    else if (resultado_antigo == VITORIA_E1){

        if (resultado_novo == VITORIA_E2){
            encontra_equipa(hash_equipas, equipa2)->pequipa->vitorias++;
            encontra_equipa(hash_equipas, equipa1)->pequipa->vitorias--;
        }

        if (resultado_novo == EMPATE)
            encontra_equipa(hash_equipas, equipa1)->pequipa->vitorias--;

        /* Se o novo resultado tambem for vitoria da equipa1, nao ha alteracoes */
    }

    else { /* resultado_antigo == VITORIA_E2 */

        if (resultado_novo == VITORIA_E1){
            encontra_equipa(hash_equipas, equipa1)->pequipa->vitorias++;
            encontra_equipa(hash_equipas, equipa2)->pequipa->vitorias--;
        }

        if (resultado_novo == EMPATE)
            encontra_equipa(hash_equipas, equipa2)->pequipa->vitorias--;

        /* Se o novo resultado tambem for vitoria da equipa2, nao ha alteracoes */
    }
}


/* Funcao que adiciona uma nova equipa ao sistema.
           -INPUT-                -OUTPUT-
           A nome                 --------
*/
void adiciona_equipa(linkeq* hash_equipas, int linha){
    char nome[STR_MAX];
    int key;
    equipa *pequipa;

    scanf(" %[^:\n]", nome);
    key = hashfunc(nome);

    /* Verificar se ja existe uma equipa com esse nome no sistema. */
    if (encontra_equipa(hash_equipas, nome) != NULL){
        printf("%d Equipa existente.\n", linha);
        return;
    }

    /* Criacao de uma nova equipa e de um ponteiro para a mesma */
    pequipa = malloc(sizeof(equipa));
    pequipa->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(pequipa->nome,nome);
    pequipa->vitorias = 0;

    /* Insercao do ponteiro para a equipa na hash das equipas */
    HashEquipas_insere(hash_equipas, pequipa, key);

}


/* Funcao que uma equipa no sistema dado um nome.           
            -INPUT-                      -OUTPUT-
            P nome             NL nome numero-de-jogos-ganhos
*/
void procura_equipa(linkeq* hash_equipas, int linha){
    char nome[STR_MAX];
    linkeq aux;

    scanf(" %[^:\n]", nome);

    /* aux contem o ponteiro que aponta para a equipa pretendida */
    aux = encontra_equipa(hash_equipas, nome);

    if (aux != NULL){
        printf("%d %s %d\n", linha, nome, aux->pequipa->vitorias);
        return;
    }

    else
        printf("%d Equipa inexistente.\n", linha);

}


/* Funcao que encontra as equipas que ganharam mais jogos e as lista por
ordem lexicografica.
            -INPUT-                      -OUTPUT-
                                NL Melhores numero-de-jogos-ganhos
               g                NL * nome-equipa1
                                NL * nome-equipa2
                                ... 
*/
void lista_melhores_equipas(linkeq* hash_equipas, int linha){

    int i, max_vitorias = 0, tamanho_lista = 0;
    linkeq aux;
    equipa **l = malloc(sizeof(equipa*));
    l[0] = NULL;

    /* Cria lista com ponteiros para as equipas com mais vitorias */
    for (i = 0; i < TAM_HASH; i++){
        aux = hash_equipas[i];
        while (aux != NULL){

            /* Quando houver uma equipa com mais vitorias, atualiza o numero
            maximo de vitorias e realoca memoria para uma lista unitaria so 
            com o ponteiro para essa equipa na primeira posicao */
            if (aux->pequipa->vitorias > max_vitorias){
                max_vitorias = aux->pequipa->vitorias;
                tamanho_lista = 1;
                l = realloc(l, sizeof(equipa*));
                l[0] = aux->pequipa;
            }

            /* Quando existe uma equipa com vitorias iguais ao maximo, incrementa
            o tamanho da lista e realoca memoria para o novo tamanho da mesma
            (tamanho anterior + 1), adicionando o ponteiro para a nova equipa na
            ultima posicao da lista */
            else if (aux->pequipa->vitorias == max_vitorias){
                tamanho_lista++;
                l = realloc(l, (tamanho_lista)*sizeof(equipa*));
                l[tamanho_lista-1] = aux->pequipa;
            }

            aux = aux->next;
            
        }
        
    }

    /* Se nao houver equipas (lista so tera ponteiro para NULL) */
    if (l[0] == NULL){
        free(l);
        return;
    }

    /* Ordena os elementos da lista */
    qsort(l, tamanho_lista, sizeof(equipa*), funcao_comparacao);

    printf("%d Melhores %d\n", linha, max_vitorias);
    for (i = 0; i < tamanho_lista; i++){
        printf("%d * %s\n", linha, l[i]->nome);
    }

    /* Limpa a lista de ponteiros */
    free(l);

}



/* Funcao usada no qsort para ordenar os nomes por ordem lexicografica. */
int funcao_comparacao( const void *equipa1, const void *equipa2){
    const char *nome1 = (*(equipa**)equipa1)->nome;
    const char *nome2 = (*(equipa**)equipa2)->nome;

    return strcmp(nome1, nome2);

}

/* Funcao que obtem o resultado de um jogo dados dois scores. */
int obtem_resultado(int score1, int score2){
    int resultado;

    if (score1 > score2)
        resultado = VITORIA_E1;
    else if (score2 > score1)
        resultado = VITORIA_E2;
    else
        resultado = EMPATE;

    return resultado;

}

/* Funcao que limpa toda a memoria alocada para a hash das equipas. */
void free_hashequipas(linkeq* hash_equipas){
    int i;
    linkeq next;

    for ( i = 0; i < TAM_HASH; i++){
        while (hash_equipas[i] != NULL){
            next = hash_equipas[i]->next;
            free(hash_equipas[i]->pequipa->nome);
            free(hash_equipas[i]->pequipa);
            free(hash_equipas[i]);
            hash_equipas[i] = next;
        }
    }
    free(hash_equipas);
}

/* Funcao que limpa toda a memoria alocada para a lista dos jogos. */
void free_listajogos(lista l){
    linkjg next;
    
    while (l->head != NULL){
        next = l->head->next;
        free(l->head->jogo->nome);
        free(l->head->jogo->equipa1);
        free(l->head->jogo->equipa2);
        free(l->head->jogo);
        free(l->head);
        l->head = next;
    }
    free(l);

}

/* Funcao que limpa toda a memoria alocada para a hash dos jogos */
void free_hash_jogos(item_hash_jg* hash_jogos){
    int i;
    item_hash_jg next;

    for ( i = 0; i < TAM_HASH; i++){
        while (hash_jogos[i] != NULL){
            next = hash_jogos[i]->next;
            free(hash_jogos[i]);
            hash_jogos[i] = next;
        }
    }
    free(hash_jogos);

}


