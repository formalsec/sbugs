#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrapper_futebol.h"

/* declaracao de funcao auxiliar */
int vencedor(int score1, int score2);

/* ========================= CRIACAO  ============================= */

equipa cria_equipa(char *nome, int jogos_ganhos) {
    equipa nova_equipa;
    nova_equipa.nome = nome;
    nova_equipa.jogos_ganhos = jogos_ganhos;
    return nova_equipa;
}

jogo cria_jogo(char *nome, char *nome_equipa1, char *nome_equipa2, int score_eq1, int score_eq2) {
    jogo novo_jogo;
    novo_jogo.nome = nome;
    novo_jogo.nome_equipa1 = nome_equipa1;
    novo_jogo.nome_equipa2 = nome_equipa2;
    novo_jogo.score_eq1 = score_eq1;
    novo_jogo.score_eq2 = score_eq2;
    return novo_jogo;
}

lista_equipas cria_lista() {
    lista_equipas l;
    l.head = NULL;
    return l;
}


/* ========================= COPIA ============================= */

void *copiar_equipa(void *equipa_original) {
    equipa *temp = (equipa *) equipa_original;

    equipa *copia = (equipa *) can_fail_malloc(sizeof(struct equipa));
    if (copia != NULL) {
        copia->nome = dupstring(temp->nome);
        copia->jogos_ganhos = temp->jogos_ganhos;

        if (copia->nome != NULL) 
            return (void *)copia; 
    }
    return NULL;
}

void *copiar_jogo(void *jogo_original) {
    jogo *temp = (jogo *) jogo_original;

    jogo *copia = (jogo *) can_fail_malloc(sizeof(struct jogo));
    if (copia != NULL) {
        copia->nome = dupstring(temp->nome);
        copia->nome_equipa1 = dupstring(temp->nome_equipa1);
        copia->nome_equipa2 = dupstring(temp->nome_equipa2);
        copia->score_eq1 = temp->score_eq1;
        copia->score_eq2 = temp->score_eq2;
        if (copia->nome != NULL && copia->nome_equipa1 != NULL && copia->nome_equipa2 != NULL) 
            return (void *)copia; 
    }
    return NULL;
}


/* ========================= DESTRUICAO ============================= */

void destroi_jogo(void *jogo_original) {
    jogo *temp = (jogo *) jogo_original;
    free(temp->nome);
    free(temp->nome_equipa1);
    free(temp->nome_equipa2);
    free(temp);
}

void destroi_equipa(void *equipa_original) {
    equipa *temp = (equipa *) equipa_original;
    free(temp->nome);
    free(temp);
}

void destroi_lista(lista_equipas *l) {
    node_equipa *temp = l->head;
    node_equipa *next;
    
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

    l->head = NULL;
}


/* ========================= INSERCAO ============================= */

bool insere_equipa(tabela *t, char *chave, equipa *equipa) { 
    return insere_tabela(t, chave, (void *)equipa, copiar_equipa);
}

bool insere_jogo(tabela *t_jogos, tabela *t_equipas, char *chave, jogo *jogo) { 

    equipa *equipa1, *equipa2;
    bool status = insere_tabela(t_jogos, chave, (void *)jogo, copiar_jogo);
    
    /* atualiza numero de jogos ganhos das equipas */
    equipa1 = procura_equipa(t_equipas, jogo->nome_equipa1);
    equipa2 = procura_equipa(t_equipas, jogo->nome_equipa2); 
    
    if ((equipa1 != NULL) && (equipa2 != NULL)) {
        /* calcula quem ganhou*/
        if (jogo->score_eq1 > jogo->score_eq2) {   
            equipa1->jogos_ganhos++;
        } else if (jogo->score_eq2 > jogo->score_eq1) {
            equipa2->jogos_ganhos++;
        }
    }
    return status;
}

/* cria (se for null) e insere equipa na lista de equipas */
bool insere_lista(lista_equipas *l, equipa *equipa) {

    node_equipa *novo_elemento, *temp;

    /* insere no inicio */
    novo_elemento = (node_equipa *) can_fail_malloc(sizeof(struct node_equipa));
    if (novo_elemento != NULL) {
        temp = l->head;
        novo_elemento->equipa = equipa;
        novo_elemento->next = temp;
        l->head = novo_elemento;
        return true;
    }
    return false;
}


/* ========================= REMOCAO ============================= */

bool remove_equipa(tabela *t, char *chave) { 
    return remove_tabela(t, chave, destroi_equipa);
}

bool remove_jogo(tabela *t_jogos, tabela *t_equipas, char *chave) { 

    equipa *equipa1, *equipa2;
    jogo *jogo;
    int vencedor_jogo;

    jogo = procura_jogo(t_jogos, chave);
    equipa1 = procura_equipa(t_equipas, jogo->nome_equipa1);
    equipa2 = procura_equipa(t_equipas, jogo->nome_equipa2);

    /* determinar o vencedor do jogo a ser removido*/
    vencedor_jogo = vencedor(jogo->score_eq1, jogo->score_eq2);
    
    /* decrementar jogos ganhos ao vencedor do jogo a ser removido*/
    if (vencedor_jogo == 1) {
        equipa1->jogos_ganhos--;
    } else if (vencedor_jogo == 2) {
        equipa2->jogos_ganhos--;
    }
    return remove_tabela(t_jogos, chave, destroi_jogo);
}


/* ========================= PROCURA ============================= */

equipa *procura_equipa(tabela *t, char *chave) {
    return (equipa *) procura_tabela(t, chave);
}

jogo *procura_jogo(tabela *t, char *chave) {
    return (jogo *) procura_tabela(t, chave);
}

node_equipa *obtem_inicio_lista(lista_equipas *l) {
    return l->head;
}


/* ========================= AUXILIARES ============================= */

/* funcao auxiliar que determina o vencedor (ou empate) dadas duas scores */
int vencedor(int score1, int score2) {
    if (score1 > score2) {
        return 1;
    } else if (score2 > score1) {
        return 2;
    } else {
        return 0;
    }
}

/* modifica o numero de jogos ganhos de 2 equipas dado um jogo e as suas novas scores */
bool muda_pontuacao(tabela *t_equipas, jogo *jogo, int novo_score1, int novo_score2) {

    equipa *equipa1, *equipa2;

    /* determinar os vencedores */
    int anterior_vencedor = vencedor(jogo->score_eq1, jogo->score_eq2);
    int novo_vencedor = vencedor(novo_score1, novo_score2);

    /* alterar o jogo com novos scores */
    jogo->score_eq1 = novo_score1;
    jogo->score_eq2 = novo_score2;
    
    /* atualiza numero de jogos ganhos das equipas */
    equipa1 = procura_equipa(t_equipas, jogo->nome_equipa1);
    equipa2 = procura_equipa(t_equipas, jogo->nome_equipa2); 
    
    if ((equipa1 != NULL) && (equipa2 != NULL)) {
        /* se o vencedor mudou, alterar os jogos ganhos das equipas correspondentes */
        switch (anterior_vencedor) {
            case 0:
                switch (novo_vencedor) {
                    case 0:
                        return true;
                    case 1:
                        equipa1->jogos_ganhos++;
                        return true;
                    case 2:
                        equipa2->jogos_ganhos++;
                        return true;
                }
                break;

            case 1:
                switch (novo_vencedor) {
                    case 0:
                        equipa1->jogos_ganhos--;
                        return true;
                    case 1:
                        return true;
                    case 2:
                        equipa1->jogos_ganhos--;
                        equipa2->jogos_ganhos++;
                        return true;
                }
                break;

            case 2:
                switch (novo_vencedor) {
                    case 0:
                        equipa2->jogos_ganhos--;
                        return true;
                    case 1:
                        equipa2->jogos_ganhos--;
                        equipa1->jogos_ganhos++;
                        return true;
                    case 2:
                        return true;
                }

        }
    }

    return false;
}

/* compara lexicograficamente duas equipas, passadas como void pointers*/
int compara_equipas(const void *e1_void, const void *e2_void) {
    equipa *e1 = *(equipa **)e1_void;
    equipa *e2 = *(equipa **)e2_void;

    if (e1 != NULL && e2 != NULL && e1->nome != NULL && e2->nome != NULL) {
        return -strcmp(e1->nome, e2->nome); /* */
    }

    return 0;
}

/* funcao que ordena uma lisita de equipas. modifica o parametro "resultados"*/
void ordenar_lista_equipas(lista_equipas *l, lista_equipas *resultados) {

    int i, num_equipas = 0;
    node_equipa *temp;
    equipa **equipas_ordenadas;

    /* obtem tamanho da lista */
    for (temp = obtem_inicio_lista(l); temp != NULL; temp = temp->next) {
        num_equipas++;
    }

    /* nota: ineficiente fazer 3 transformacoes mas melhora a legibilidade do codigo a meu ver*/

    /* transformar lista num array */
    equipas_ordenadas = (equipa **) can_fail_malloc(num_equipas * sizeof(struct equipa *));
    for (temp = obtem_inicio_lista(l), i = 0; temp != NULL && i < num_equipas; temp = temp->next, i++) {
        equipas_ordenadas[i] = temp->equipa;
    }

    /* ordena lexicograficamente com a funcao compara_equipas */
    if (equipas_ordenadas != NULL) {
       qsort(equipas_ordenadas, num_equipas, sizeof(struct equipa *), compara_equipas); 
    }

    /* transformar de volta para lista ligada */
    for (i = 0; i < num_equipas; i++) {
        insere_lista(resultados, equipas_ordenadas[i]);
    }

    free(equipas_ordenadas);
}