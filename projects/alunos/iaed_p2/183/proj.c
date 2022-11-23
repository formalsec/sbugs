#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "wrapper_futebol.h"

/* ========================= DIRETIVAS  ============================= */
#define MAX_STR 1024
#define M_EQUIPAS 1997
#define M_JOGOS 1997

#define SIZE "1024"

/* ========================= PROTOTIPOS  ============================= */
/* declaracao de funcoes: optei por manter os nomes das funcoes
   iguais aos comandos que as invocam por questoes de nao interferencia
   com as outras funcoes.  */

void a(tabela *jogos, tabela *equipas, int numero_linha);
void A(tabela *equipas, int numero_linha);
void l(tabela *jogos, int numero_linha);
void p(tabela *jogos, int numero_linha);
void P(tabela *equipas, int numero_linha);
void r(tabela *jogos, tabela *equipas, int numero_linha);
void s(tabela *jogos, tabela *equipas, int numero_linha);
void g();

/* ============================== MAIN ============================= */
int main() {

    /* criacao de hashtables para equipas e jogos */
    tabela *equipas = cria_tabela(M_EQUIPAS);
    tabela *jogos = cria_tabela(M_JOGOS);

    int ch, numero_linha = 0;

    while (1) {

        switch(ch = getchar()) {
            
            /* Adiciona jogo */
            case 'a': 
                a(jogos, equipas, ++numero_linha);
                break;
             
            /* Adiciona equipa */
            case 'A':
                A(equipas, ++numero_linha);
                break;
            
                
            /* Lista todos os jogos pela ordem de entrada */
            case 'l':  
                l(jogos, ++numero_linha);
                break;

            /* Procura um jogo */
            case 'p': 
                p(jogos, ++numero_linha);
                break;
            
            /* Procura uma equipa */
            case 'P': 
                P(equipas, ++numero_linha);
                break;
            
            /* Apaga um jogo */
            case 'r': 
                r(jogos, equipas, ++numero_linha);
                break;
            
                
            /* Altera a pontuacao de um jogo */
            case 's': 
                s(jogos, equipas, ++numero_linha);
                break;

            
            /* Encontra as equipas que venceram mais jogos */
            case 'g': {
                g(equipas, ++numero_linha);
                break;
            }

            /* Termina o programa */
            case 'x': 
                destroi_tabela(equipas, destroi_equipa);
                destroi_tabela(jogos, destroi_jogo);
                return 0;
            
        }
    }
}

void a(tabela *jogos, tabela *equipas, int numero_linha) {

    int score_eq1, score_eq2;

    /* strings na stack para ler input*/
    char nome[MAX_STR], nome_eq1[MAX_STR], nome_eq2[MAX_STR];
    jogo novo_jogo;

    /* le input */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, nome_eq1, nome_eq2, &score_eq1, &score_eq2);

    /* verifica se o jogo ja existe */
    if (procura_jogo(jogos, nome) != NULL) {
        printf("%d Jogo existente.\n", numero_linha);
    
    /* verifica se as equipas existem */
    } else if (procura_equipa(equipas, nome_eq1) == NULL || procura_equipa(equipas, nome_eq2) == NULL) {
        printf("%d Equipa inexistente.\n", numero_linha);

    } else {
        /* cria novo jogo e insere */
        novo_jogo = cria_jogo(nome, nome_eq1, nome_eq2, score_eq1, score_eq2);
        insere_jogo(jogos, equipas, novo_jogo.nome, &novo_jogo);
    }
}

void A(tabela *equipas, int numero_linha) {

    equipa nova_equipa;
    char nome[MAX_STR];

    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se a equipa ja existe */
    if (procura_equipa(equipas, nome) != NULL) {
        printf("%d Equipa existente.\n", numero_linha);

    } else {
        /* cria nova equipa e insere */
        nova_equipa = cria_equipa(nome, 0);
        insere_equipa(equipas, nova_equipa.nome, &nova_equipa);
    }
}

/* a assinatura da funcao deve cumprir os requisitos de iterar_ordenado */
bool imprime_jogo(char *nome, void *jogo_void, void *num_ptr) {

    jogo *j = (jogo *)jogo_void;
    int numero_linha = *(int *)num_ptr;

    if (j != NULL) {
        printf("%d %s %s %s %d %d\n", numero_linha, nome, j->nome_equipa1, j->nome_equipa2, j->score_eq1, j->score_eq2);
    }

    return true;
}

/* Lista todos os jogos pela ordem de entrada */
void l(tabela *jogos, int numero_linha) {

    void *num_ptr = (void *)&numero_linha;

    /* iterar pela forma de insercao por todos os jogos, imprimindo-os */
    iterar_ordenado(jogos, imprime_jogo, num_ptr);
}

/* Procura um jogo */
void p(tabela *jogos, int numero_linha) {

    jogo *jogo;

    char nome[MAX_STR];
    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se o jogo existe */
    if ((jogo = procura_jogo(jogos, nome)) == NULL) {
        printf("%d Jogo inexistente.\n", numero_linha);

    } else {
        printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
    }
}

/* Procura uma equipa */
void P(tabela *equipas, int numero_linha) {

    equipa *equipa;
    char nome[MAX_STR];

    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se a equipa existe */
    if ((equipa = procura_equipa(equipas, nome)) == NULL) {
        printf("%d Equipa inexistente.\n", numero_linha);

    } else {
        printf("%d %s %d\n", numero_linha, nome, equipa->jogos_ganhos);
    }
}

/* Apaga um jogo */
void r(tabela *jogos, tabela *equipas, int numero_linha) {

    char nome[MAX_STR];
    jogo *jogo;
    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se o jogo existe */
        /* verifica se o jogo existe */
    if ((jogo = procura_jogo(jogos, nome)) == NULL) {
        printf("%d Jogo inexistente.\n", numero_linha);
    } else {
        remove_jogo(jogos, equipas, nome);
    }
}

/* Altera a pontuacao de um jogo */
void s(tabela *jogos, tabela *equipas, int numero_linha) {

    int score1, score2;
    char nome[MAX_STR];
    jogo *jogo;
    
    /* le input */
    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    /* verifica se o jogo existe */
    if ((jogo = procura_jogo(jogos, nome)) == NULL) {
        printf("%d Jogo inexistente.\n", numero_linha);
    } else {
        muda_pontuacao( equipas, jogo, score1, score2);
    }
}

/* funcao auxiliar que seleciona as melhores equipas*/
bool melhores_equipas(char *chave, void *equipa_void, void *melhores_void) {

    int score_max;
    bool status;
    equipa *e = (equipa *)equipa_void;
    lista_equipas *melhores = (lista_equipas *)melhores_void;
    node_equipa *inicio = obtem_inicio_lista(melhores);

    (void)chave; /* nao precisamos da chave, suprimir warning */

    if (melhores != NULL && inicio != NULL) {
        if (e != NULL && inicio->equipa != NULL)  {
            /* basta escolher a escolher a score da primeira "melhor" equipa, 
            pois todas tem a mesma score (numero de jogos ganhos)*/
            score_max = inicio->equipa->jogos_ganhos;

            /* equipa e melhor */
            if (e->jogos_ganhos > score_max) {
                destroi_lista(melhores);
                status = insere_lista(melhores, e);

            /* mesma score */
            } else if (e->jogos_ganhos == score_max) {
                status = insere_lista(melhores, e);
            }
            /* equipa inferior, nada a fazer */
        }
    /* se nao houver nenhuma equipa nas melhores, inserir nova*/
    } else {
        status = insere_lista(melhores, e);
    }

    return status;
}

/* Encontra as equipas que venceram mais jogos */
void g(tabela *equipas, int numero_linha) {
    /* iterar por todas as equipas e encontrar as equipas com score maxima igual */
    /* dessas equipas, ordenar por ordem lexicografica (alfabetica) */

    node_equipa *temp;
    lista_equipas melhores = cria_lista();
    lista_equipas melhores_ordenadas = cria_lista();

    iterar_tabela(equipas, melhores_equipas, (void *)&melhores);
    
    ordenar_lista_equipas(&melhores, &melhores_ordenadas);
    temp = obtem_inicio_lista(&melhores_ordenadas);

    if (temp != NULL && temp->equipa != NULL) {
        printf("%d Melhores %d\n", numero_linha, temp->equipa->jogos_ganhos);

        for ( ; temp != NULL; temp = temp->next) {
            printf("%d * %s\n", numero_linha, temp->equipa->nome);
        }
    }

    destroi_lista(&melhores);
    destroi_lista(&melhores_ordenadas);
}