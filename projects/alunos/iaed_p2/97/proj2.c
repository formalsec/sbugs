#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj2.h"

void apaga_todos_dados(lista **j, lista **j_o, elem_eq **e) {
    apaga_tabela_jogos(j);
    liberta_lista_jogos(*j_o);
    apaga_tabela_equipas(e);
}

void novo_jogo(lista **j, lista **j_o, elem_eq **e, int NL,
               char *nome, char *eq1, char *eq2, int sc1, int sc2) {
    Item_j *novo;
    elem_eq *tmp1, *tmp2;
    Item_eq *aux1, *aux2;
    tmp1 = encontra_equipa_tabela(e, eq1);
    tmp2 = encontra_equipa_tabela(e, eq2);
    if (encontra_jogo_tabela(j, nome) != NULL) {
        /* Verifica se o jogo nao existe */
        printf("%d Jogo existente.\n", NL);
        return;
    } else if (tmp1 == NULL || tmp2 == NULL) {
        /* Verifica se ambas as equipas existem */
        printf("%d Equipa inexistente.\n", NL);
        return;
    }
    /* Inicializa o jogo com os nomes e pontuacoes */
    aux1 = acede_equipa(tmp1);
    aux2 = acede_equipa(tmp2);
    novo = inicializa_jogo(nome, nome_equipa(aux1), 
                                 nome_equipa(aux2), sc1, sc2);
    /* Adiciona o jogo na lista e na tabela */
    adiciona_jogo_lista(*j_o, novo);
    insere_jogo_tabela(j, novo);
    /* Adiciona um ponto a quem ganhar (se ganhar alguem) */
    if (sc1 > sc2) {
        aumenta_pontuacao(acede_equipa(tmp1));
    } else if (sc2 > sc1) {
        aumenta_pontuacao(acede_equipa(tmp2));
    }
}

void nova_equipa(elem_eq **e, int NL, char *nome) {
    Item_eq *novo;
    if (encontra_equipa_tabela(e, nome) == NULL) {
        /* Se a equipa nao existir, inicializa-la e adiciona-la */
        novo = inicializa_equipa(nome);
        insere_equipa_tabela(e, novo);
    } else {
        /* Caso contrario, dar erro */
        printf("%d Equipa existente.\n", NL);
    }
}

void LDL_jogos(lista **j_o, int NL) {
    int sc1, sc2;
    Item_j *tmp;
    elem_j *aux = acede_inicio_lista_jogos(*j_o);
    while (aux != NULL) {
        tmp = acede_jogo(aux);
        sc1 = pontuacao_eq1(tmp);
        sc2 = pontuacao_eq2(tmp);
        /* Escreve as propriedades do jogo */
        printf("%d %s %s %s %d %d\n", 
                NL, nome_jogo(tmp), nome_eq1(tmp), nome_eq2(tmp), sc1, sc2);                     
        aux = prox_elem(aux); /* Avanca para o proximo elemento */
    }
}

void procura_jogo(lista **j, int NL, char *nome) {
    int sc1, sc2;
    Item_j *tmp;
    elem_j *aux = encontra_jogo_tabela(j, nome);
    if (aux != NULL) {
        /* Caso o jogo exista, escreve as propriedades deste */
        tmp = acede_jogo(aux);
        sc1 = pontuacao_eq1(tmp);
        sc2 = pontuacao_eq2(tmp);
        printf("%d %s %s %s %d %d\n", 
                NL, nome_jogo(tmp), nome_eq1(tmp), nome_eq2(tmp), sc1, sc2);
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

void procura_equipa(elem_eq **e, int NL, char *nome) {
    elem_eq *aux = encontra_equipa_tabela(e, nome);
    Item_eq *tmp;
    if (aux != NULL) {
        /* Caso a equipa exista, escreve as propriedades desta */
        tmp = acede_equipa(aux);
        printf("%d %s %d\n", NL, nome_equipa(tmp), ganhos_equipa(tmp));
    } else {
        printf("%d Equipa inexistente.\n", NL);
    }
}

void apaga_jogo(lista **j, lista **j_o, elem_eq **e, int NL, char *nome) {
    int sc1, sc2;
    /* Tem que se retirar o jogo da lista e da tabela */
    elem_j *tmp1 = encontra_jogo_tabela(j, nome);
    elem_j *tmp2 = encontra_jogo_lista(*j_o, nome);
    elem_eq *aux;
    Item_j *jogo;
    if (tmp1 != NULL) { /* Caso o jogo exista */
        jogo = acede_jogo(tmp1); 
        sc1 = pontuacao_eq1(jogo);
        sc2 = pontuacao_eq2(jogo);
        /* Altera-se a pontuacao das equipas */
        if (sc1 > sc2) {
            aux = encontra_equipa_tabela(e, nome_eq1(jogo));
            diminui_pontuacao(acede_equipa(aux));
        } else if (sc1 < sc2) {
            aux = encontra_equipa_tabela(e, nome_eq2(jogo));
            diminui_pontuacao(acede_equipa(aux));
        }
        /* Remove-se o jogo da lista, da tabela e apaga-se a memoria deste */
        remove_jogo_lista(*j_o, tmp2);
        remove_jogo_tabela(j, tmp1);
        liberta_jogo(jogo);
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

void altera_ganhos_equipas(int sc1, int sc2, int ant1, int ant2,
                                    elem_eq *aux1, elem_eq *aux2) {
    if (sc1 == sc2) {
        if (ant1 > ant2) {
            diminui_pontuacao(acede_equipa(aux1));
        } else if (ant1 < ant2) {
            diminui_pontuacao(acede_equipa(aux2));
        }
    } else if (sc1 > sc2) {
        if (ant1 == ant2) {
            aumenta_pontuacao(acede_equipa(aux1));
        } else if (ant1 < ant2) {
            diminui_pontuacao(acede_equipa(aux2));
            aumenta_pontuacao(acede_equipa(aux1));
        }
    } else {
        if (ant1 == ant2) {
            aumenta_pontuacao(acede_equipa(aux2));
        } else if (ant1 > ant2) {
            diminui_pontuacao(acede_equipa(aux1));
            aumenta_pontuacao(acede_equipa(aux2));
        }
    }
}

void altera_sc_jogo(lista **j, elem_eq **e, int NL, char *nome,
                                                    int sc1, int sc2) {
    int sc_antigo1, sc_antigo2;
    elem_j *tmp = encontra_jogo_tabela(j, nome);
    elem_eq *aux1, *aux2;
    Item_j *jogo;
    if (tmp != NULL) {
        /* Caso o jogo exista */
        jogo = acede_jogo(tmp);
        sc_antigo1 = pontuacao_eq1(jogo);
        sc_antigo2 = pontuacao_eq2(jogo);
        aux1 = encontra_equipa_tabela(e, nome_eq1(jogo));
        aux2 = encontra_equipa_tabela(e, nome_eq2(jogo));
        /* Altera-se a pontuacao das equipas */
        altera_ganhos_equipas(sc1, sc2, sc_antigo1, sc_antigo2, aux1, aux2);
        /* Alteram-se os valores do jogo */
        altera_pontuacao(jogo, sc1, sc2);
    } else {
        printf("%d Jogo inexistente.\n", NL);
    }
}

int compara(const void *str1, const void *str2) {
    const char *s1 = *(const char**)str1;
    const char *s2 = *(const char**)str2;
    return strcmp(s1, s2);
}

void equipas_maior_pontuacao(elem_eq **e, int NL) {
    int maior = 0, len, i = 0;
    char **nomes;
    elem_eq *vencedores, *aux;
    /* Obter as equipas vencedoras */
    vencedores = equipas_vencedoras(e, &maior);
    len = tamanho(vencedores);
    /* Caso nao existam vencedores */
    if (!len) {
        return;
    }
    /* Alocacao e populacao dum vetor de strings */
    nomes = can_fail_malloc(len * sizeof(char*));
    aux = vencedores;
    while (i < len) {
        nomes[i] = can_fail_malloc(MAX_STR * sizeof(char));
        strcpy(nomes[i], nome_equipa(acede_equipa(aux)));
        i++;
        aux = prox_equipa(aux);
    }
    /* Limpeza da lista das equipas vencedoras */
    liberta_lista_equipas(vencedores);
    /* Sort dos nomes */
    qsort(nomes, len, sizeof(char*), compara);
    /* Print do resultado */
    printf("%d Melhores %d\n", NL, maior);
    for (i = 0; i < len; i++) {
        printf("%d * %s\n", NL, nomes[i]);
        free(nomes[i]); /* Vamos libertando a memoria alocada */
    }
    /* Libertacao do vetor de strings */
    free(nomes);
}