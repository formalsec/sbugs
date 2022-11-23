#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "comandos.h"

/******************************************************************************
 * Funcoes:
******************************************************************************/

/* processa_equipas: Funcao que, a seguir a adicionar/remover/alterar a 
pontuacao de um jogo, processa as equipas intervenientes (na arvore binaria).
(i.e. altera as pontuacoes de cada equipa individualmente, e remove-as e 
readiciona-as 'a arvore caso seja necessario).
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 equipa1: parametro que representa o nome da primeira equipa.
 equipa2: parametro que representa o nome da segunda equipa.
 score1: parametro que representa a pontuacao da primeira equipa.
 score2: parametro que representa a pontuacao da segunda equipa.
 operacao: parametro que representa o ponteiro para uma funcao que executa a 
operacao de processamento.  */
void processa_equipas(Bt **bt, Lp **lp, char *equipa1, char *equipa2, int score1,
 int score2, void operacao(Team *)) {
    Team *vencedora;

    if (score1 != score2) {
        if (score1 > score2) {
            vencedora = (Team *) search_item_lp(*lp, equipa1, key_team_lp,
             hash);
        }
        else {
            vencedora = (Team *) search_item_lp(*lp, equipa2, key_team_lp,
             hash);
        }
        root_bt(*bt) = remove_item_bt(vencedora, root_bt(*bt), key_team_bt,
         free_team);
        operacao(vencedora);
        root_bt(*bt) = add_item_bt(vencedora, root_bt(*bt), key_team_bt);
    }
}

/* adiciona_jogo: Funcao que executa o comando "a". 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void adiciona_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha) {
    char buffer1[MAX_NOME], buffer2[MAX_NOME], buffer3[MAX_NOME];
    int arg1, arg2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer1, buffer2, buffer3, &arg1,
     &arg2);
    if (search_item_lp(*lp1, buffer1, key_game, hash) != NULL) {
        printf("%d Jogo existente.\n", linha);
    }
    else if (search_item_lp(*lp2, buffer2, key_team_lp, hash) == NULL ||
     search_item_lp(*lp2, buffer3, key_team_lp, hash) == NULL) {
        printf("%d Equipa inexistente.\n", linha);
    }
    else {
        Game *jogo;
        Node_list *no;
        
        jogo = new_game(buffer1, buffer2, buffer3, arg1, arg2);
        no = add_node_list(*lista, jogo);
        *lp1 = add_item_lp(*lp1, no, key_game, hash);
        processa_equipas(bt, lp2, buffer2, buffer3, arg1, arg2, add_win);
    }
}

/* adiciona_equipa: Funcao que executa o comando "A". 
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void adiciona_equipa(Bt **bt, Lp **lp, int linha) {
    char buffer[MAX_NOME];

    scanf(" %[^:\n]", buffer);
    if (search_item_lp(*lp, buffer, key_team_lp, hash) != NULL) {
        printf("%d Equipa existente.\n", linha);
    }
    else {
        Team *equipa;

        equipa = new_team(buffer);
        root_bt(*bt) = add_item_bt(equipa, root_bt(*bt), key_team_bt);
        *lp = add_item_lp(*lp, equipa, key_team_lp, hash);
    }
}

/* lista_jogos: Funcao que executa o comando "l". 
 lista: parametro que representa o ponteiro do o ponteiro para lista (duplamente 
ligada) dos jogos.
 linha: parametro que representa a linha de input que esta a ser lida. */
void lista_jogos(List **lista, int linha) {
    print_list(*lista, linha, print_game_list);
}

/* procura_jogo: Funcao que executa o comando "p".
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 linha: parametro que representa a linha de input que esta a ser lida. */
void procura_jogo(Lp **lp , int linha) {
    char buffer[MAX_NOME];

    scanf(" %[^:\n]", buffer);
    if (search_item_lp(*lp, buffer, key_game, hash) == NULL) {
        printf("%d Jogo inexistente.\n", linha);
    }
    else {
        Game *jogo;
        Node_list *no;

        no = (Node_list *) search_item_lp(*lp, buffer, key_game, hash);
        jogo = item_list(no);
        printf("%d ", linha);
        print_game(jogo);
    }
}

/* procura_equipa: Funcao que executa o comando "P".
 lp: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void procura_equipa(Lp **lp, int linha) {
    char buffer[MAX_NOME];

    scanf(" %[^:\n]", buffer);
    if (search_item_lp(*lp, buffer, key_team_lp, hash) == NULL) {
        printf("%d Equipa inexistente.\n", linha);
    }
    else {
        void *equipa;

        equipa = search_item_lp(*lp, buffer, key_team_lp, hash);
        printf("%d ", linha);
        print_team_lp(equipa);
    }
}

/* apaga_jogo: Funcao que executa o comando "r". 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void apaga_jogo(List **lista, Lp **lp1, Bt **bt, Lp **lp2, int linha) {
    char buffer[MAX_NOME];

    scanf(" %[^:\n]", buffer);
    if (search_item_lp(*lp1, buffer, key_game, hash) == NULL) {
        printf("%d Jogo inexistente.\n", linha);
    }
    else {
        Node_list *no;
        Game *jogo;

        no = (Node_list *) search_item_lp(*lp1, buffer, key_game, hash);
        jogo = item_list(no);
        processa_equipas(bt, lp2, team1(jogo), team2(jogo), score_team1(jogo),
         score_team2(jogo), remove_win);
        no = delete_item_lp(*lp1, name(jogo), key_game, hash);
        *lista = remove_node_list(*lista, no, free_game);
    }
}

/* altera_score: Funcao que executa o comando "s".
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void altera_score(Lp **lp1, Bt **bt, Lp **lp2, int linha) {
    char buffer[MAX_NOME];
    int arg1, arg2;

    scanf(" %[^:\n]:%d:%d", buffer, &arg1, &arg2);
    if (search_item_lp(*lp1, buffer, key_game, hash) == NULL) {
        printf("%d Jogo inexistente.\n", linha);
    }
    else {
        Node_list *no;
        Game *jogo;

        no = (Node_list *) search_item_lp(*lp1, buffer, key_game, hash);
        jogo = item_list(no);
        processa_equipas(bt, lp2, team1(jogo), team2(jogo), score_team1(jogo),
         score_team2(jogo), remove_win);
        change_score(jogo, arg1, arg2);
        processa_equipas(bt, lp2, team1(jogo), team2(jogo), arg1, arg2, add_win);
    }
}

/* my_strcmp: Funcao de comparacao usada no qsort.
 a: parametro que representa o primeiro elemento a comparar.
 b: parametro que representa o segundo elemento a comparar. */
int my_strcmp(const void *a, const void *b) {
    Team **el1, **el2;
    char *v1, *v2;
    
    el1 = (Team **) a;
    el2 = (Team **) b;
    v1 = name(*el1);
    v2 = name(*el2);

    return strcmp(v1, v2);
}

/* encontra_equipas: Funcao que executa o comando "g".
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 linha: parametro que representa a linha de input que esta a ser lida. */
void encontra_equipas(Bt **bt, int linha) {
    int contador, n_equipas, vitorias;
    Team **equipas;

    if (!empty_bt(root_bt(*bt))) {
        n_equipas = count_bt(max_bt(root_bt(*bt)));
        equipas = (Team **) items_bt(max_bt(root_bt(*bt)));
        qsort(equipas, n_equipas, sizeof(char *), my_strcmp);
        vitorias = wins(equipas[0]);
        printf("%d Melhores %d\n", linha, vitorias);
        for (contador = 0; contador < n_equipas; contador++) {
            printf("%d ", linha);
            print_team_bt(equipas[contador]);
        }
    }
}

/* adiciona_jogo: Funcao que liberta todo o espaco associado 'as estruturas. 
 lista: parametro que representa o ponteiro do o ponteiro para lista 
(duplamente ligada) dos jogos.
 lp1: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) dos nos da lista dos jogos.
 bt: parametro que representa o ponteiro do ponteiro para a arvore binaria das 
equipas.
 lp2: parametro que representa o ponteiro do ponteiro para a tabela de dispersao 
(por procura linear) das equipas. */
void liberta_estruturas(List *lista, Lp *lp1, Bt *bt, Lp *lp2) {
    free_lp(lp1);
    free_lp(lp2);
    free_list(lista, free_game);
    free_bt(bt, free_team);
}
