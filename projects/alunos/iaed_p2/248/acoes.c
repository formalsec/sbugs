#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "acoes.h"

/*
 * Functions
*/

void a(Lista_jogo *jogos, Hashtable_jogo *jogos_hashtable,
 Hashtable_equipa *equipas, int linha_input){
    char nome[LIM_INPUT], equipa_1[LIM_INPUT], equipa_2[LIM_INPUT];
    int pontuacao_1, pontuacao_2;
    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, equipa_1, equipa_2,
     &pontuacao_1, &pontuacao_2);

    if (procura_hashtable_jogo(jogos_hashtable, nome) != NULL){
        printf("%d Jogo existente.\n", linha_input);
    }
    else if (procura_hashtable_equipa(equipas, equipa_1) == NULL ||
     procura_hashtable_equipa(equipas, equipa_2) == NULL){
        printf("%d Equipa inexistente.\n", linha_input);
    }
    else{
        Equipa *equipa;
        Jogo *jogo = cria_jogo(nome, equipa_1, equipa_2, pontuacao_1, pontuacao_2);
        adiciona_lista_jogo(jogos, jogo);
        adiciona_hashtable_jogo(jogos_hashtable, jogo);
        
        if (pontuacao_1 > pontuacao_2){
            equipa = procura_hashtable_equipa(equipas, equipa_1);
            altera_vitorias_equipas(equipa, equipa->vitorias + 1);
        }
        else if (pontuacao_2 > pontuacao_1){
            equipa = procura_hashtable_equipa(equipas, equipa_2);
            altera_vitorias_equipas(equipa, equipa->vitorias + 1);
        }
    }
}

void l(Lista_jogo *jogos, int linha_input){
    imprime_lista_jogo(jogos, linha_input);
}

void p(Hashtable_jogo *jogos, int linha_input){
    Jogo *jogo;
    char nome[LIM_INPUT];
    scanf("%[^:\n]", nome);

    if ((jogo = procura_hashtable_jogo(jogos, nome)) == NULL){
        printf("%d Jogo inexistente.\n", linha_input);
    }
    else{
        printf("%d %s %s %s %d %d\n", linha_input, jogo->nome, jogo->equipa_1,
         jogo->equipa_2, jogo->pontuacao_1, jogo->pontuacao_2);
    }
}

void r(Lista_jogo *jogos, Hashtable_jogo *jogos_hashtable,
 Hashtable_equipa *equipas, int linha_input){
    Jogo *jogo;
    char nome[LIM_INPUT];
    scanf("%[^:\n]", nome);

    if ((jogo = procura_hashtable_jogo(jogos_hashtable, nome)) == NULL){
        printf("%d Jogo inexistente.\n", linha_input);
    }
    else{
        Equipa *equipa;
        jogo = remove_hashtable_jogo(jogos_hashtable, nome);
        remove_lista_jogo(jogos, jogo);

        if (jogo->pontuacao_1 > jogo->pontuacao_2){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_1);
            altera_vitorias_equipas(equipa, equipa->vitorias - 1);
        }
        else if (jogo->pontuacao_2 > jogo->pontuacao_1){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_2);
            altera_vitorias_equipas(equipa, equipa->vitorias - 1);
        }
        liberta_jogo(jogo);
    }
}

void s(Hashtable_jogo *jogos, Hashtable_equipa *equipas, int linha_input){
    Jogo *jogo;
    char nome[LIM_INPUT];
    int pontuacao_1, pontuacao_2;
    scanf("%[^:\n]:%d:%d", nome, &pontuacao_1, &pontuacao_2);

    if ((jogo = procura_hashtable_jogo(jogos, nome)) == NULL){
        printf("%d Jogo inexistente.\n", linha_input);
    }
    else{
        Equipa *equipa;

        if (jogo->pontuacao_1 > jogo->pontuacao_2){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_1);
            altera_vitorias_equipas(equipa, equipa->vitorias - 1);
        }
        else if (jogo->pontuacao_2 > jogo->pontuacao_1){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_2);
            altera_vitorias_equipas(equipa, equipa->vitorias - 1);
        }

        if (pontuacao_1 > pontuacao_2){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_1);
            altera_vitorias_equipas(equipa, equipa->vitorias + 1);
        }
        else if (pontuacao_2 > pontuacao_1){
            equipa = procura_hashtable_equipa(equipas, jogo->equipa_2);
            altera_vitorias_equipas(equipa, equipa->vitorias + 1);
        }
        altera_pontucao_jogo(jogo, pontuacao_1, pontuacao_2);
    }
}

void A(Hashtable_equipa *equipas, int linha_input){
    char nome[LIM_INPUT];
    scanf("%[^:\n]", nome);

    if (procura_hashtable_equipa(equipas, nome) != NULL){
        printf("%d Equipa existente.\n", linha_input);
    }
    else{
        Equipa *equipa = cria_equipa(nome);
        adiciona_hashtable_equipa(equipas, equipa);
    }
}

void P(Hashtable_equipa *equipas, int linha_input){
    Equipa *equipa;
    char nome[LIM_INPUT];
    scanf("%[^:\n]", nome);

    if ((equipa = procura_hashtable_equipa(equipas, nome)) == NULL){
        printf("%d Equipa inexistente.\n", linha_input);
    }
    else{
        printf("%d %s %d\n", linha_input, equipa->nome, equipa->vitorias);
    }
}

int compara(const void *x, const void *y) {
    Equipa **i = (Equipa **) x;
    Equipa **j = (Equipa **) y;
    char *equipa_1 = (*i)->nome;
    char *equipa_2 = (*j)->nome;
    return strcmp(equipa_1, equipa_2);
}

void g(Hashtable_equipa *equipas, int linha_input){
    Tabela_equipas *tabela;

    if ((tabela = maximas_vitorias_equipa(equipas))->equipas != NULL){
        int i = 0;
        qsort(tabela->equipas, tabela->n_equipas, sizeof(char *), compara); /* orderna as equipas por ordem lexicografica */
        printf("%d Melhores %d\n", linha_input, tabela->vitorias);
        for (; i < tabela->n_equipas; i++){
            printf("%d * %s\n", linha_input, (*(tabela->equipas + i))->nome);
        }
        free(tabela->equipas);
    }
    free(tabela);
}
