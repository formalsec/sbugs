#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EQUIPAS 10000  /* maximo de equipas no sistema */
#define fHash 1     /* flag que indica que estamos a trabalhar com a hashtable */
#define fLst_Ord 0  /* flag que indica que estamos a trabalhar com a estrutura de equipas e jogos ordenados */


/* associa um numero a uma string para ser o indice da hashtable */
int hashU(char *v, int m){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (m-1))
        h = (a*h + *v) % m;
    return h;
}


/* aloca memoria dinamica para uma string */
char* str_dup(char* buffer){
    char* str;
    str = (char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(str,buffer);
    return str;
} 


/* inicializa a hashtable */
pListas* inicializa_listas(pListas* listas, int m){
    int i;
    listas = (pListas*) can_fail_malloc(m * sizeof(pListas));
    for (i = 0; i < m; i++){
        listas[i] = (pListas) can_fail_malloc(sizeof(struct Listas));
        listas[i]->head_equipas = NULL;
        listas[i]->head_jogos = NULL;
        listas[i]->tail_equipas = NULL;
        listas[i]->tail_jogos = NULL;
    }
    return listas;
}


/* inicializa a estrutura com os jogos e equipas ordenados por insercao */
pLst_Ord inicializa_lista_ordenada(pLst_Ord lista_ordenada){
    lista_ordenada = (pLst_Ord) can_fail_malloc(sizeof(struct Lst_Ord));
    lista_ordenada->head_jogos = NULL;
    lista_ordenada->tail_jogos = NULL;
    lista_ordenada->lista_equipas = (pEquipa*) can_fail_calloc(MAX_EQUIPAS, sizeof(pEquipa));
    lista_ordenada->cont_equipas = 0;
    return lista_ordenada;
}


/* insere uma equipa na hashtable */
void insere_equipa(pListas lista_equipas, link_equipa nova_equipa){
    if (lista_equipas->head_equipas == NULL){
        lista_equipas->head_equipas = nova_equipa;
        lista_equipas->tail_equipas = nova_equipa;
        return;
    }
    /* insercao da nova equipa a seguir a tail, e atualizacao da mesma */
    lista_equipas->tail_equipas->next = nova_equipa;
    lista_equipas->tail_equipas = nova_equipa;
    return;
}


/* insere um jogo na hashtable */
void insere_jogo_hash(pListas lista_jogos, link_jogo novo_jogo){
    if (lista_jogos->head_jogos == NULL){
        lista_jogos->head_jogos = novo_jogo;
        lista_jogos->tail_jogos = novo_jogo;
        return;
    }
    lista_jogos->tail_jogos->next = novo_jogo;
    lista_jogos->tail_jogos = novo_jogo;
    return;
}


/* insere um jogo na estrutura com listas e jogos ordenados */
void insere_jogo_lista_ordenada(pLst_Ord lista_jogos, link_jogo novo_jogo){
    if (lista_jogos->head_jogos == NULL){
        lista_jogos->head_jogos = novo_jogo;
        lista_jogos->tail_jogos = novo_jogo;
        return;
    }
    lista_jogos->tail_jogos->next = novo_jogo;
    lista_jogos->tail_jogos = novo_jogo;
    return;
}


/* procura por uma equipa na hashtable */
link_equipa procura_equipa(pListas* listas, char* nome, int m){
    int index = hashU(nome, m);
    link_equipa link;
    if (listas[index]->head_equipas == NULL){
        return NULL;
    }
    for (link = listas[index]->head_equipas; link != NULL; link = link->next){
        if (!strcmp(nome, link->equipa->nome))
            return link;
    }
    return NULL;
}


/* procura por um jogo na hashtable */
link_jogo procura_jogo(pListas* listas, char* nome, int m){
    int index = hashU(nome, m);
    link_jogo link;
    if (listas[index]->head_jogos == NULL){
        return NULL;
    }
    for (link = listas[index]->head_jogos; link != NULL; link = link->next){
        if (!strcmp(nome, link->jogo->nome))
            return link;
    }
    return NULL;
}


/* elimina um jogo da hashtable */
void elimina_hash(pListas lista_jogos, char* nome){
    link_jogo link, prev;
    for (link = lista_jogos->head_jogos, prev = NULL; link != NULL; prev = link, link = link->next){
        if (!strcmp(link->jogo->nome, nome)){
            /* caso especial se o jogo for o primeiro da lista */
            if (link == lista_jogos->head_jogos)
                lista_jogos->head_jogos = link->next;
            else
                prev->next = link->next;
            /* se o jogo for o ultimo da lista, atualizar a tail */
            if (link == lista_jogos->tail_jogos)
                lista_jogos->tail_jogos = prev;
            /* dar free so do no, e nao dos seus elementos, pois a funcao 
            de eliminacao do jogo da lista ordenada vai usa-los ainda */
            free(link);
            break;
        }
    }
    return;
}


/* elimina um jogo da lista com os jogos ordenados por insercao */
void elimina_lista_ordenada(pLst_Ord lista_jogos, char* nome){
    link_jogo link, prev;
    for (link = lista_jogos->head_jogos, prev = NULL; link != NULL; prev = link, link = link->next){
        if (!strcmp(link->jogo->nome, nome)){
            if (link == lista_jogos->head_jogos)
                lista_jogos->head_jogos = link->next;
            else
                prev->next = link->next;
            if (link == lista_jogos->tail_jogos)
                lista_jogos->tail_jogos = prev;
            free(link->jogo->equipa_1);
            free(link->jogo->equipa_2);
            free(link->jogo->nome);
            free(link->jogo);
            free(link);
            break;
        }
    }
    return;
}


/* adiciona uma equipa ao sistema */
void adiciona_equipa(int NL, pListas* listas, pLst_Ord lista_ordenada, int m){
    int index;
    char nome[1023];
    link_equipa nova_equipa = (link_equipa) can_fail_malloc(sizeof(struct node_equipa));
    scanf(" %[^:\n]", nome);
    index = hashU(nome, m);
    /* verifica se ja nao existe uma equipa com esse nome */ 
    if (procura_equipa(listas, nome, m) != NULL){
        printf("%d Equipa existente.\n", NL);
        free(nova_equipa);
        return;
    }
    nova_equipa->equipa = (pEquipa) can_fail_malloc(sizeof(struct Equipa));
    nova_equipa->next = NULL;
    nova_equipa->equipa->nome = str_dup(nome);
    nova_equipa->equipa->vitorias = 0;
    /* adicionar a equipa a hashtable */
    insere_equipa(listas[index], nova_equipa);
    /* adicionar a equipa ao vetor de equipas e aumentar o contador do numero de equipas */
    lista_ordenada->lista_equipas[lista_ordenada->cont_equipas] = nova_equipa->equipa;
    lista_ordenada->cont_equipas++;
}


/* adiciona um jogo ao sistema */
void adiciona_jogo(int NL, pListas* listas, pLst_Ord lista_ordenada, int m){
    int index;
    char nome[1023];
    char equipa_1[1023];
    char equipa_2[1023];
    int pontuacao_1;
    int pontuacao_2;
    link_equipa equipa_vencedora;
    link_jogo novo_jogo_hash = (link_jogo) can_fail_malloc(sizeof(struct node_jogo));
    link_jogo novo_jogo_lista_ordenada = (link_jogo) can_fail_malloc(sizeof(struct node_jogo));
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome, equipa_1, equipa_2, &pontuacao_1, &pontuacao_2);
    index = hashU(nome, m);
    /* verifica se ja existe um jogo com esse nome */
    if (procura_jogo(listas, nome, m) != NULL){
        printf("%d Jogo existente.\n", NL);
        free(novo_jogo_hash);
        free(novo_jogo_lista_ordenada);
        return;
    }
    /* verifica se as equipas realmente existem */
    if (procura_equipa(listas, equipa_1, m) == NULL || procura_equipa(listas, equipa_2, m) == NULL){
        printf("%d Equipa inexistente.\n", NL);
        free(novo_jogo_hash);
        free(novo_jogo_lista_ordenada);
        return;
    }
    /* acrescenta uma vitoria a equipa com pontuacao maior */
    if (pontuacao_1 > pontuacao_2){
        equipa_vencedora = procura_equipa(listas, equipa_1, m);
        equipa_vencedora->equipa->vitorias++;
    }
    else if (pontuacao_2 > pontuacao_1){
        equipa_vencedora = procura_equipa(listas, equipa_2, m);
        equipa_vencedora->equipa->vitorias++;
    }
    novo_jogo_hash->jogo = (pJogo) can_fail_malloc(sizeof(struct Jogo));
    novo_jogo_hash->next = NULL;
    novo_jogo_hash->jogo->equipa_1 = str_dup(equipa_1);
    novo_jogo_hash->jogo->equipa_2 = str_dup(equipa_2);
    novo_jogo_hash->jogo->nome = str_dup(nome);
    novo_jogo_hash->jogo->pontuacao[0] = pontuacao_1;
    novo_jogo_hash->jogo->pontuacao[1] = pontuacao_2;
    novo_jogo_lista_ordenada->jogo = novo_jogo_hash->jogo;
    novo_jogo_lista_ordenada->next = NULL;
    /* adiciona o novo jogo a hashtable e a lista com os jogos ordenados */
    insere_jogo_hash(listas[index], novo_jogo_hash);
    insere_jogo_lista_ordenada(lista_ordenada, novo_jogo_lista_ordenada);
}


/* procura uma equipa no sistema e indica quantos jogos ganhou */
void consulta_equipa(int NL, pListas* listas, int m){
    char nome[1023];
    int vitorias;
    link_equipa link;
    scanf(" %[^\n]", nome);
    link = procura_equipa(listas, nome, m);
    if (link == NULL){
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    vitorias = link->equipa->vitorias;
    printf("%d %s %d\n", NL, nome, vitorias);
}


/* procura um jogo no sistema e indica as suas informacoes:
nome do jogo, equipas que jogaram, e pontuacao */
void consulta_jogo(int NL, pListas* listas, int m){
    char nome[1023];
    int pontuacao_1;
    int pontuacao_2;
    link_jogo link;
    scanf(" %[^\n]", nome);
    link = procura_jogo(listas, nome, m);
    if (link == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    pontuacao_1 = link->jogo->pontuacao[0];
    pontuacao_2 = link->jogo->pontuacao[1];
    printf("%d %s %s %s %d %d\n", NL, nome, link->jogo->equipa_1, link->jogo->equipa_2, pontuacao_1, pontuacao_2);

}


/* lista todos os jogos pela ordem de insercao 
no sistema, indicando as informacoes de cada um */
void jogos_ordenados(int NL, pLst_Ord lista_ordenada){
    link_jogo link;
    if (lista_ordenada->head_jogos == NULL){
        return;
    }
    for (link = lista_ordenada->head_jogos; link != NULL; link = link->next){
        printf("%d %s %s %s %d %d\n", NL, link->jogo->nome, link->jogo->equipa_1, link->jogo->equipa_2, link->jogo->pontuacao[0], link->jogo->pontuacao[1]);
    }
    return;
}


/* remove um jogo do sistema */
void remove_jogo (int NL, pListas* listas, pLst_Ord lista_ordenada, int m){
    char nome[1023];
    int index, pontuacao_1, pontuacao_2;
    link_jogo link;
    link_equipa equipa_vencedora;
    scanf(" %[^\n]", nome);
    link = procura_jogo(listas, nome, m);
    if (link == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    /* retira uma vitoria a equipa que tinha ganho 
    o jogo, visto que o jogo vai ser eliminado */
    pontuacao_1 = link->jogo->pontuacao[0];
    pontuacao_2 = link->jogo->pontuacao[1];
    if (pontuacao_1 > pontuacao_2){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_1, m);
        equipa_vencedora->equipa->vitorias--;
    }
    else if (pontuacao_2 > pontuacao_1){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_2, m);
        equipa_vencedora->equipa->vitorias--;
    }
    index = hashU(nome, m);
    /* elimina o jogo da hashtable e da lista com os jogos ordenados */
    elimina_hash(listas[index], nome);
    elimina_lista_ordenada(lista_ordenada, nome);
    return;
}


/* altera a pontuacao de um jogo, modificando o numero 
de vitorias das equipas envolvidas caso necessario */
void altera_pontuacao(int NL, pListas* listas, int m){
    char nome[1023];
    int pontuacao_1_nova, pontuacao_2_nova, pontuacao_1_antiga, pontuacao_2_antiga;
    link_jogo link;
    link_equipa equipa_vencedora, equipa_derrotada;
    scanf(" %[^:]:%d:%d", nome, &pontuacao_1_nova, &pontuacao_2_nova);
    link = procura_jogo(listas, nome, m);
    if (link == NULL){
        printf("%d Jogo inexistente.\n", NL);
        return;
    }
    pontuacao_1_antiga = link->jogo->pontuacao[0];
    pontuacao_2_antiga = link->jogo->pontuacao[1];
    link->jogo->pontuacao[0] = pontuacao_1_nova;
    link->jogo->pontuacao[1] = pontuacao_2_nova;
    /* verifica se as pontuacoes novas alteram qual das equipas ganhou, 
    alterando o numero de vitorias de cada uma conformemente */
    if (pontuacao_1_antiga < pontuacao_2_antiga && pontuacao_1_nova == pontuacao_2_nova){
        equipa_derrotada = procura_equipa(listas, link->jogo->equipa_2, m);
        equipa_derrotada->equipa->vitorias--;
    }
    else if (pontuacao_1_antiga < pontuacao_2_antiga && pontuacao_1_nova > pontuacao_2_nova){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_1, m);
        equipa_derrotada = procura_equipa(listas, link->jogo->equipa_2, m);
        equipa_vencedora->equipa->vitorias++;
        equipa_derrotada->equipa->vitorias--;
    }
    else if (pontuacao_1_antiga > pontuacao_2_antiga && pontuacao_1_nova == pontuacao_2_nova){
        equipa_derrotada = procura_equipa(listas, link->jogo->equipa_1, m);
        equipa_derrotada->equipa->vitorias--;
    }
    else if (pontuacao_1_antiga > pontuacao_2_antiga && pontuacao_1_nova < pontuacao_2_nova){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_2, m);
        equipa_derrotada = procura_equipa(listas, link->jogo->equipa_1, m);
        equipa_vencedora->equipa->vitorias++;
        equipa_derrotada->equipa->vitorias--;
    }
    else if (pontuacao_1_antiga == pontuacao_2_antiga && pontuacao_1_nova < pontuacao_2_nova){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_2, m);
        equipa_vencedora->equipa->vitorias++;
    }
    else if (pontuacao_1_antiga == pontuacao_2_antiga && pontuacao_1_nova > pontuacao_2_nova){
        equipa_vencedora = procura_equipa(listas, link->jogo->equipa_1, m);
        equipa_vencedora->equipa->vitorias++;
    }
    return;
}


/* funcao de comparacao do qsort para ordenar as equipas
segundo o seu numero de vitorias, por ordem decrescente */
int compara_vitorias(const void* a, const void* b){
    pEquipa* l = (pEquipa*) a;
    pEquipa* r = (pEquipa*) b;
    return((*r)->vitorias - (*l)->vitorias);
}


/* funcao de comparacao do qsort para ordenar as 
equipas segundo o seu nome, por ordem crescente */
int compara_nomes(const void* a, const void* b){
    pEquipa* l = (pEquipa*) a;
    pEquipa* r = (pEquipa*) b;
    return(strcmp((*l)->nome, (*r)->nome));
}


/* lista todas as equipas que estao empatadas em primeiro lugar
em termos de vitorias, listando-as por ordem lexicografica */
void ordena_equipas_vitorias(int NL, pLst_Ord lista_ordenada){
    int i, max_vitorias, max_equipas_vencedoras = 0;
    pEquipa* equipas_vencedoras = (pEquipa*) can_fail_malloc(sizeof(pEquipa) * lista_ordenada->cont_equipas); 
    /* nao faz nada se nao houver equipas no sistema */
    if (!lista_ordenada->cont_equipas){
        free(equipas_vencedoras);
        return;
    }
    /* ordena todas as equipas por ordem decrescente do numero de vitorias, de modo 
    a que os primeiros indices sejam os das equipas que estao em primeiro lugar */
    qsort(lista_ordenada->lista_equipas, lista_ordenada->cont_equipas, sizeof(pEquipa), compara_vitorias);
    max_vitorias = lista_ordenada->lista_equipas[0]->vitorias;
    /* percorrer as equipas para ver quantas e quais delas estao 
    empatadas em primeiro lugar, e adiciona-las a um novo vetor */ 
    for (i = 0; i < lista_ordenada->cont_equipas && lista_ordenada->lista_equipas[i]->vitorias == max_vitorias; i++){
        equipas_vencedoras[i] = lista_ordenada->lista_equipas[i];
        max_equipas_vencedoras++;
    }
    /* reajustar o tamanho do vetor de equipas que estao
    em primeiro lugar para ser a quantidade exata dessas 
    equipas e, de seguida, ordena-las pelo nome */
    equipas_vencedoras = (pEquipa*) can_fail_realloc(equipas_vencedoras, sizeof(pEquipa) * max_equipas_vencedoras);
    qsort(equipas_vencedoras, max_equipas_vencedoras, sizeof(pEquipa), compara_nomes);
    printf("%d Melhores %d\n", NL, max_vitorias);
    for (i = 0; i < max_equipas_vencedoras; i++){
        printf("%d * %s\n", NL, equipas_vencedoras[i]->nome);
    }
    free(equipas_vencedoras);
    return;
}


/* faz free de uma lista de equipas */
void free_equipas(link_equipa head_equipas){
    link_equipa link;
    link_equipa aux;
    link = head_equipas;
    while (link != NULL){
        free(link->equipa->nome);
        free(link->equipa);
        /* ponteiro de no auxiliar que vai apontar para
        o mesmo no do ponteiro atual, de modo a poder fazer
        free do atual sem perder o que se lhe segue (o next) */
        aux = link;
        link = link->next;
        free(aux);
    }
    return;
}
            

/* faz free de uma lista de jogos */
void free_jogos(link_jogo head_jogos, int flag_struct){
    link_jogo link;
    link_jogo aux;
    link = head_jogos; 
    while (link != NULL){
        /* verificacao da flag de estrutura 
        de dados, de modo a fazer free dos 
        componentes dos nos apenas uma vez */
        if (flag_struct == fLst_Ord){
            free(link->jogo->nome);
            free(link->jogo->equipa_1);
            free(link->jogo->equipa_2);
            free(link->jogo);
        }
        aux = link;
        link = link->next;
        free(aux);
    }
    return;
}


/* faz free da hashtable */
void free_listas(pListas* listas, int m){
    int i;
    for (i = 0; i < m; i++){
        free_equipas(listas[i]->head_equipas);
        free_jogos(listas[i]->head_jogos, fHash);
        free(listas[i]);
    }
    free(listas);
    return;
}


/* faz free da lista com os jogos e equipas ordenados */
void free_lista_ordenada(pLst_Ord lista_ordenada){
    free(lista_ordenada->lista_equipas);
    free_jogos(lista_ordenada->head_jogos, fLst_Ord);
    free(lista_ordenada);
    return;
}