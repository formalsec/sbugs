#include "jogos.h"
#include "equipas.h"
#include "common.h"

#define CORRER 1
#define PARAR 0

/* Adiciona um novo jogo */
void adiciona_jogo(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas) {
    Jogo *jogo = criar_jogo();
    Equipa *e1, *e2;

    /* Verifica que se o jogo ja existe */
    if (procura_jogo(tabJogos, jogo->nome) != NULL) {
        printf("%d Jogo existente.\n", nl);
        free_jogo(jogo);
        return;
    }
    
    /* Verifica que se as equipas existem */
    e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
    e2 = procura_equipa(tabEquipas, jogo->equipas[1]);

    if (e1 == NULL || e2 == NULL) {
        printf("%d Equipa inexistente.\n", nl);
        free_jogo(jogo);
        return;
    }

    /* Atualiza o numero de jogos ganhos pelas equipas */
    if (jogo->scores[0] > jogo->scores[1]) {
        e1->score++;
    } else if (jogo->scores[0] < jogo->scores[1]) {
        e2->score++;
    }

    /* Insere o jogo na tabela */
    inserir_jogo(tabJogos, jogo);
}

/* Adiciona uma nova equipa */
void adiciona_equipa(int nl, TabelaEquipas *tabEquipas) {
    Equipa *equipa;
    char input[STR_MAX];
    scanf(" %[^:\n]", input);

    /* Verifica se a equipa ja existe */
    if (procura_equipa(tabEquipas, input) != NULL) {
        printf("%d Equipa existente.\n", nl);
        return;
    }
    
    /* Aloca e insere a equipa */
    equipa = malloc(sizeof(Equipa));
    equipa->nome = copiar_texto(input);
    equipa->score = 0;
    inserir_equipa(tabEquipas, equipa);
}

/* Lista todos os jogos pela ordem em que foram introduzidos */
void lista_jogos(int nl, TabelaJogos *tabJogos) {
    struct node *no = tabJogos->first;
    
    while (no != NULL) {
        if (no->v != NULL) {
            printf("%d %s %s %s %d %d\n", 
                nl, no->v->nome, no->v->equipas[0], no->v->equipas[1], 
                no->v->scores[0], no->v->scores[1]);
        }
        no = no->next;
    }
}

/* Procura um jogo */
void procurar_jogo(int nl, TabelaJogos *tabJogos) {
    char nome[STR_MAX];
    Jogo *jogo;

    scanf(" %[^:\n]", nome);

    jogo = procura_jogo(tabJogos, nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", nl);
        return;
    }
    printf("%d %s %s %s %d %d\n", 
        nl, jogo->nome, jogo->equipas[0], jogo->equipas[1], 
        jogo->scores[0], jogo->scores[1]);
}

/* Procura uma equipa */
void procurar_equipa(int nl, TabelaEquipas *tabEquipas) {
    char nome[STR_MAX];
    Equipa *equipa;

    scanf(" %[^:\n]", nome);
    equipa = procura_equipa(tabEquipas, nome);

    if (equipa == NULL) {
        printf("%d Equipa inexistente.\n", nl);
        return;
    }

    printf("%d %s %d\n", nl, equipa->nome, equipa->score);
}

/* Apaga um jogo */
void apaga_jogo(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas) {
    char nome[STR_MAX];
    Jogo *jogo;
    Equipa *e1, *e2;
    
    scanf(" %[^:\n]", nome);
    jogo = procura_jogo(tabJogos, nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", nl);
        return;
    }

    /* Atualiza o numero de vitorias das equipas */
    e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
    e2 = procura_equipa(tabEquipas, jogo->equipas[1]);
    if (jogo->scores[0] > jogo->scores[1]) {
        e1->score--;
    } else if (jogo->scores[0] < jogo->scores[1]) {
        e2->score--;
    }

    apagar_jogo(tabJogos, nome);
}

/* Altera a pontuacao de um jogo */
void altera_score(int nl, TabelaJogos *tabJogos, TabelaEquipas *tabEquipas) {
    char nome[STR_MAX];
    Jogo *jogo;
    Equipa *e1, *e2;
    int novosScores[2];

    scanf(" %[^:\n]:%d:%d", nome, &novosScores[0], &novosScores[1]);
    jogo = procura_jogo(tabJogos, nome);
    if (jogo == NULL) {
        printf("%d Jogo inexistente.\n", nl);
        return;
    }

    /* Atualiza o numero de vitorias das equipas */
    e1 = procura_equipa(tabEquipas, jogo->equipas[0]);
    e2 = procura_equipa(tabEquipas, jogo->equipas[1]);
    if (jogo->scores[0] > jogo->scores[1]) {
        e1->score--;
    } else if (jogo->scores[0] < jogo->scores[1]) {
        e2->score--;
    }

    jogo->scores[0] = novosScores[0];
    jogo->scores[1] = novosScores[1];

    if (jogo->scores[0] > jogo->scores[1]) {
        e1->score++;
    } else if (jogo->scores[0] < jogo->scores[1]) {
        e2->score++;
    }
}

/* Encontra as equipas que venceram mais jogos */
void melhores_equipas(int nl, TabelaEquipas *tabEquipas) {
    int i, j;
    int numEquipas = 0;
    int jogosGanhos = 0;
    char **equipas = NULL;

    if (tabEquipas->tamanho == 0) 
        return;

    /* Obtem o maior numero de jogos ganhos e o numero de equipas com esse valor */
    for (i = 0; i < tabEquipas->capacidade; i++) {
        if (tabEquipas->equipas[i] != NULL) {
            if (tabEquipas->equipas[i]->score > jogosGanhos) {
                jogosGanhos = tabEquipas->equipas[i]->score;
                numEquipas = 1;
            } else if (tabEquipas->equipas[i]->score == jogosGanhos) {
                numEquipas++;
            }
        }
    }

    /* Aloca o vetor para os nomes das equipas com maior numero de vitorias */
    equipas = malloc(sizeof(char*) * numEquipas);
    j = 0;
    for (i = 0; i < tabEquipas->capacidade; i++) {
        if (tabEquipas->equipas[i] != NULL 
            && tabEquipas->equipas[i]->score == jogosGanhos) {
            equipas[j] = tabEquipas->equipas[i]->nome;
            j++;
        }
    }

    /* Ordena alfabeticamente e mostra cada equipa */
    ordena_equipas(equipas, 0, numEquipas - 1);
    printf("%d Melhores %d\n", nl, jogosGanhos);
    for (i = 0; i < numEquipas; i++) {
        printf("%d * %s\n", nl, equipas[i]);
    }

    free(equipas);
}

int main() {
    int estado = CORRER;
    int nl = 1;
    TabelaJogos *tabJogos = inicia_tabela_jogos(13);
    TabelaEquipas *tabEquipas = inicia_tabela_equipas(13);

    while (estado == CORRER) {
        char comando = getchar();

        switch (comando) {
        case 'a':
            adiciona_jogo(nl, tabJogos, tabEquipas);
            nl++;
            break;
        case 'A':
            adiciona_equipa(nl, tabEquipas);
            nl++;
            break;
        case 'l':
            lista_jogos(nl, tabJogos);
            nl++;
            break;
        case 'p':
            procurar_jogo(nl, tabJogos);
            nl++;
            break;
        case 'P':
            procurar_equipa(nl, tabEquipas);
            nl++;
            break;
        case 'r':
            apaga_jogo(nl, tabJogos, tabEquipas);
            nl++;
            break;
        case 's':
            altera_score(nl, tabJogos, tabEquipas);
            nl++;
            break;
        case 'g':
            melhores_equipas(nl, tabEquipas);
            nl++;
            break;
        case 'x':
            estado = PARAR;
            break;
        }
    }

    free_tabela_jogos(tabJogos);
    free_tabela_equipas(tabEquipas);

    return 0;
}
