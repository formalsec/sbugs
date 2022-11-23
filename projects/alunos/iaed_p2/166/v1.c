#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "listadupJOGO.h"
#include "listadupEQUIPA.h"

/* Tamanho de cada uma das hashtables */
#define TAMANHO_HASH 10007

/* Inicializa a hashtable dos jogos */
void inic_ht_jogos(list_jogo * ht_jogos[TAMANHO_HASH]){
    int i = -1;
    while (++i < TAMANHO_HASH)
        ht_jogos[i] = mk_list_jogo();
}

/* Inicializa a hashtable das equipas */
void inic_ht_equipas(list_equipa * ht_equipas[TAMANHO_HASH]){
    int i = -1;
    while (++i < TAMANHO_HASH)
        ht_equipas[i] = mk_list_equipa();
}

/* Recebe uma string e devolve a sua posicao na hashtable (0 a TAMANHO_HASH-1),
dada pelo resto da divisao da soma dos seus caracteres por 10 */
int hash(char * str){
    int soma=0,valorletra;
    while (*str != '\0'){
        valorletra = *str;
        soma += valorletra;
        ++str;
    }
    return soma % TAMANHO_HASH;
}

Jogo * procura_jogo_aux(char * nome, node_jogo * l_head){
    node_jogo * copiaL;
    /* percorreu lista toda sem encontrar */
    if (l_head == NULL)
        return NULL;
    else{
        /* encontrou o nome */
        if (strcmp(l_head->jogo->nome, nome) == 0)
            return l_head->jogo;
        else{
            /* nao encontrou, ve proximo */
            copiaL = l_head->next;
            return procura_jogo_aux(nome, copiaL);
        }
    }
}

/* Retorna o endereco onde se encontra o jogo com o nome dado, ou NULL se
ele ainda nao existir */
Jogo * procura_jogo(char * nome, list_jogo * ht_jogos[TAMANHO_HASH]){
    int hashVal = hash(nome);
    return procura_jogo_aux(nome, ht_jogos[hashVal]->head);
}

/* Procura equipa numa lista ligada de equipas */
Equipa * procura_equipa_aux(char * nome, node_equipa * l_head){
    node_equipa * copiaL;
    /* percorreu lista toda sem encontrar */
    if (l_head == NULL)
        return NULL;
    else{
        /* encontrou o nome */
        if (strcmp(l_head->equipa->nome, nome) == 0)
            return l_head->equipa;
        else{
            /* nao encontrou, ve proximo */
            copiaL = l_head->next;
            return procura_equipa_aux(nome, copiaL);
        }
    }
}

/* Retorna endereco onde se encontra equipa com o nome dado
(ou NULL se nao existir) */
Equipa * procura_equipa(char * nome, list_equipa * ht_equipas[TAMANHO_HASH]){
    int hashVal = hash(nome);
    return procura_equipa_aux(nome, ht_equipas[hashVal]->head);
}

/* Procura um jogo no sistema */
void func_p(list_jogo * ht_jogos[TAMANHO_HASH], int nl){
    char nome[MAXNOME];
    Jogo * j;
    scanf(" %[^:\n]", nome);
    j = procura_jogo(nome, ht_jogos);
    if (j == NULL)
        printf("%d Jogo inexistente.\n", nl);
    else
        printf("%d %s %s %s %d %d\n", nl, j->nome,
               j->equipa1, j->equipa2, j->score[0], j->score[1]);
}

/* Adiciona um jogo ao sistema (caso nao exista) */
void func_a(list_jogo * ht_jogos[TAMANHO_HASH],
            list_equipa * ht_equipas[TAMANHO_HASH],
            list_jogo * ordem_jogos, int nl){
    /* Input do utilizador */
    char nome[MAXNOME], eq1[MAXEQUIPA], eq2[MAXEQUIPA];
    int score[2], hashVal;
    Jogo * novoJogo;
    Equipa * endEquipa1, * endEquipa2;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
          nome, eq1, eq2, &score[0], &score[1]);
    /* Ja existe jogo com o mesmo nome no sistema */
    if (procura_jogo(nome, ht_jogos) != NULL){
        printf("%d Jogo existente.\n", nl);
        return;
    }
    endEquipa1 = procura_equipa(eq1, ht_equipas);
    endEquipa2 = procura_equipa(eq2, ht_equipas);
    /* Uma das equipas nao existe no sistema */
    if ((endEquipa1 == NULL) || (endEquipa2 == NULL)){
        printf("%d Equipa inexistente.\n", nl);
        return;
    }
    /* Adicionar novo jogo ao sistema */
    novoJogo = mk_jogo(nome, eq1, eq2, score);
    hashVal = hash(nome);
    /* Equipa1 venceu */
    if (score[0] > score[1])
        endEquipa1->vitorias += 1;
    else
        /* Equipa2 venceu */
        if (score[1] > score[0])
            endEquipa2->vitorias += 1;
    add_last_jogo(ht_jogos[hashVal], novoJogo);
    add_last_jogo(ordem_jogos, novoJogo);
}

/* Adiciona uma equipa ao sistema (caso nao exista) */
void func_A(list_equipa * ht_equipas[TAMANHO_HASH], int nl){
    char nome[MAXEQUIPA];
    Equipa * e;
    int hashVal;
    scanf(" %[^:\n]", nome);
    e = procura_equipa(nome, ht_equipas);
    /* Equipa ja existe */
    if (e != NULL){
        printf("%d Equipa existente.\n", nl);
        return;
    }
    hashVal = hash(nome);
    e = mk_equipa(nome);
    add_last_equipa(ht_equipas[hashVal], e);
}

/* Procura uma equipa no sistema */
void func_P(list_equipa * ht_equipas[TAMANHO_HASH], int nl){
    char nome[MAXEQUIPA];
    Equipa * e;
    scanf(" %[^:\n]", nome);
    e = procura_equipa(nome, ht_equipas);
    /* Equipa nao existe */
    if (e == NULL){
        printf("%d Equipa inexistente.\n", nl);
        return;
    }
    /* Equipa existe */
    printf("%d %s %d\n", nl, e->nome, e->vitorias);
}

/* Lista todos os jogos presentes no sistema pela ordem de insercao */
void func_l(list_jogo * ordem_jogos, int nl){
    node_jogo * nodeAtual = ordem_jogos->head;
    /* Enquanto nao chegarmos ao fim da lista, escrever linha */
    while (nodeAtual != NULL){
        printf("%d %s %s %s %d %d\n", nl, nodeAtual->jogo->nome,
               nodeAtual->jogo->equipa1, nodeAtual->jogo->equipa2,
               nodeAtual->jogo->score[0], nodeAtual->jogo->score[1]);
        nodeAtual = nodeAtual->next; 
    }
}

/* Altera a pontuacao de um jogo no sistema */
void func_s(list_jogo * ht_jogos[TAMANHO_HASH],
            list_equipa * ht_equipas[TAMANHO_HASH], int nl){
    char nome[MAXNOME];
    int score0, score1;
    Jogo * jogo;
    Equipa * equipa1, * equipa2;
    scanf(" %[^:\n]:%d:%d", nome, &score0, &score1);
    jogo = procura_jogo(nome,ht_jogos);
    /* jogo nao existe */
    if (jogo == NULL){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }
    equipa1 = procura_equipa(jogo->equipa1, ht_equipas);
    equipa2 = procura_equipa(jogo->equipa2, ht_equipas);

    /* jogo existe, atualizar vitorias eq1 */
    if (jogo->score[0] > jogo->score[1]){
        /* eq1 ganhava, mas deixa de ser vitoriosa */
        if (score0 <= score1)
            equipa1->vitorias--;
    }
    else{
        /* eq1 perdia/empatava, mas passa a ser vitoriosa */
        if (score0 > score1)
            equipa1->vitorias++;
    }

    /* atualizar vitorias eq2 */
    if (jogo->score[1] > jogo->score[0]){
        /* eq2 ganhava, mas deixa de ser vitoriosa */
        if (score1 <= score0)
            equipa2->vitorias--;
    }
    else{
        /* eq1 perdia/empatava, mas passa a ser vitoriosa */
        if (score1 > score0)
            equipa2->vitorias++;
    }
    /* atualizar jogo */
    jogo->score[0] = score0;
    jogo->score[1] = score1;
}

/* Remove um jogo do sistema */
void func_r(list_jogo * ht_jogos[TAMANHO_HASH],
            list_equipa * ht_equipas[TAMANHO_HASH],
            list_jogo * ordem_jogos, int nl){
    char nome[MAXNOME];
    int hashVal;
    Jogo * j;
    Equipa * e;
    node_jogo * membro_ordem;
    scanf(" %[^:\n]", nome);
    j = procura_jogo(nome, ht_jogos);
    /* Jogo nao existe */
    if (j == NULL){
        printf("%d Jogo inexistente.\n", nl);
        return;
    }
    /* descontar vitoria da equipa vencedora */
    if (j->score[0] > j->score[1]){
        e = procura_equipa(j->equipa1, ht_equipas);
        e->vitorias--;
    }
    if (j->score[0] < j->score[1]){
        e = procura_equipa(j->equipa2, ht_equipas);
        e->vitorias--;
    }
    /* remover da hashtable dos jogos */
    hashVal = hash(nome);
    remove_jogo(ht_jogos[hashVal], j);

    /* remover de ordem_jogos */
    membro_ordem = ordem_jogos->head;
    /* percorre ate chegar ao jogo */
    while (membro_ordem->jogo != j)
        membro_ordem = membro_ordem->next;
    /* se ordem_jogos so tiver um jogo */
    if (ordem_jogos->head == ordem_jogos->last){
        ordem_jogos->head = NULL;
        ordem_jogos->last = NULL;
    }
    /* se membro_ordem for cabeca da lista */
    if (membro_ordem == ordem_jogos->head)
        ordem_jogos->head = membro_ordem->next;

    /* se membro_ordem nao for a cabeca da lista */
    if (membro_ordem->previous != NULL)
        membro_ordem->previous->next = membro_ordem->next;

    /* se membro_ordem for ultimo da lista */
    if (membro_ordem == ordem_jogos->last)
        ordem_jogos->last = membro_ordem->previous;

    /* se membro_ordem nao for o ultimo da lista */
    if (membro_ordem->next != NULL)
        membro_ordem->next->previous = membro_ordem->previous;
        
    /* libertar memoria que falta */
    free(membro_ordem);
}

/* Utilizada pelo qsort para ordenar vetor de equipas */
int compara(const void * a, const void * b){
    /* buscar valores aos seus enderecos */
    Equipa * e1 = *((Equipa**)a);
    Equipa * e2 = *((Equipa**)b);
    return strcmp(e1->nome, e2->nome);
}

/* Lista as equipas com mais vitorias */
void func_g(list_equipa * ht_equipas[TAMANHO_HASH], int nl){
    int max = 0, cont_max = 0, i=-1, poslivre=0;
    list_equipa * lista;
    node_equipa * membro_lista;
    Equipa ** v;

    /* percorrer hashtable das equipas */ 
    while (++i < TAMANHO_HASH){
        lista = ht_equipas[i];
        membro_lista = lista->head;
        /* percorrer toda a lista e procurar novos max */
        while (membro_lista != NULL){
            /* se a equipa igualar max de vitorias */
            if (membro_lista->equipa->vitorias == max){
               /*v = can_fail_malloc(sizeof(Equipa*));
                v[cont_max] = membro_lista->equipa;*/
                cont_max++;
            }
            /* equipa tem novo max de vitorias */
            if (membro_lista->equipa->vitorias > max){
                /*free(v);
                v = can_fail_malloc(sizeof(Equipa*));
                v[0] = membro_lista->equipa;*/
                max = membro_lista->equipa->vitorias;
                cont_max = 1;
            }
            membro_lista = membro_lista->next;
        }
    }
    if (cont_max == 0)
        return;
    /* alocar memoria necessaria */
    v = can_fail_malloc(cont_max * sizeof(Equipa*));
    /* percorrer novamente hashtable, agora para colocar no vetor */
    i = -1;
    while (++i < TAMANHO_HASH){
        lista = ht_equipas[i];
        membro_lista = lista->head;
        /* percorrer toda a lista e procurar max */
        while (membro_lista != NULL){
            /* se a equipa igualar max de vitorias */
            if (membro_lista->equipa->vitorias == max){
                v[poslivre] = membro_lista->equipa;
                ++poslivre;
            }
            membro_lista = membro_lista->next;
        }
    }
    /* ordenar o vetor final */
    qsort((void*)v, cont_max, sizeof(Equipa*), compara);
    i = -1;
    /* escrita do resultado */
    printf("%d Melhores %d\n", nl, max);
    while (++i < cont_max)
        printf("%d * %s\n", nl, v[i]->nome);
    free(v);

}

/* Programa principal */
int main(){
    /* Caracter para a leitura das funcoes */
    char c;
    /* Indicador de linha */
    int nl = 1, i = -1;
    /* Hashtable com todos os jogos do sistema. Os jogos sao inseridos com
    base no nome atribuido pelo utilizador (resto da divisao da soma dos
    valores ASCII do nome por TAMANHO_HASH) */
    list_jogo * ht_jogos[TAMANHO_HASH];
    /* Hashtable com todas as equipas e seu numero de vitorias. As equipas sao
    inseridas da mesma forma que os jogos mas usa-se o nome da equipa */
    list_equipa * ht_equipas[TAMANHO_HASH];
    /* Lista duplamente ligada de jogos que guarda a ordem de insercao
    dos jogos no sistema (utilizada na funcao l) */
    list_jogo * ordem_jogos = mk_list_jogo();
    node_jogo * ordem_jogos_last;

    inic_ht_equipas(ht_equipas);
    inic_ht_jogos(ht_jogos);

    /* analise do input inicial */
    while ((c=getchar()) != 'x'){
        switch(c){
            case 'a':
                func_a(ht_jogos, ht_equipas, ordem_jogos, nl);
                nl++;
                break;
            case 'l':
                func_l(ordem_jogos, nl);
                nl++;
                break;
            case 'p':
                func_p(ht_jogos, nl);
                nl++;
                break;
            case 'r':
                func_r(ht_jogos, ht_equipas, ordem_jogos, nl);
                nl++;
                break;
            case 's':
                func_s(ht_jogos, ht_equipas, nl);
                nl++;
                break;
            case 'A':
                func_A(ht_equipas, nl);
                nl++;
                break;
            case 'P':
                func_P(ht_equipas, nl);
                nl++;
                break;
            case 'g':
                func_g(ht_equipas, nl);
                nl++;
            default:
                break;
        }
    }
    /* libertar memoria das hashtables */
    while (++i<TAMANHO_HASH){
        if (ht_equipas[i] != NULL)
            free_list_equipa(ht_equipas[i]);
        if (ht_jogos[i] != NULL)
            free_list_jogo(ht_jogos[i]);
    }
    /* libertar memoria associada a lista ordem_jogos */
    ordem_jogos_last = ordem_jogos->last;
    /* liberta se lista nao for vazia */
    if (ordem_jogos_last != NULL){
        /* liberta todos menos cabeca */
        while (ordem_jogos_last != ordem_jogos->head){
            ordem_jogos_last = ordem_jogos_last->previous;
            free(ordem_jogos_last->next);
        }
        free(ordem_jogos_last);
    }
    free(ordem_jogos);
    return 0;
}