#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "tab_equipas.h"

#define SEMEQUIPAS -1
#define TAM_INIT 100    /* tamanho maximo inicial do vetor de equipas */

/* bases arbitrarias primas entre si */
#define BASE1 31415
#define BASE2 27183

/* funcoes nao exportadas */
int ordem_alfa (const void * equipa_a, const void * equipa_b);
int disp_equipas(void *nome, int tamanho);

/* funcao de dispersao para tabelas de equipas */
int disp_equipas(void *nome, int tamanho) {

    char *ptr_aux = (char *) nome;
    int res = 0;
    int base1 = BASE1;
    int base2 = BASE2;

    for (; *ptr_aux != '\0'; ptr_aux++, base1 = (base1 * base2) % tamanho) {
        res = (res + base1 * (*ptr_aux)) % tamanho;
    }

    return res;

}

/* chave de dispersao para equipas */
void* chave_equipas(void *e) {
    return (void *)(((equipa)(e))->nome);
}

/* insere uma equipa na tabela */
void insere_tab_equipa(tab_disp tab_equipas, equipa e) {
    insere_tab(tab_equipas, (void *)e, &chave_equipas, &disp_equipas);
}

/* apaga uma equipa na tabela */
void retira_tab_equipa(tab_disp tab_equipas, char *nome) {
    retira_tab(tab_equipas, (void *)nome, &disp_equipas, &equipa_nome_igual, &liberta_equipa);
}

/* liberta a memoria associada a uma tabela de equipas */
void liberta_tab_equipas(tab_disp tab_equipas) {
    liberta_tab(tab_equipas, &liberta_equipa);
}

/* procura uma equipa pelo nome na tabela e retorna NULL caso nao exista */
equipa procura_tab_equipa(tab_disp tab_equipas, char *nome) {
    return (equipa) procura_tab(tab_equipas, (void *)nome, &disp_equipas, &equipa_nome_igual);
}

/* retorna o numero maximo de vitorias registado numa tabela de equipas */
int max_vitorias_tab(tab_disp tab_equipas) {

    int max = 0;  
    int max_aux; 
    int i;
    int num_equipas = 0; /* contador das equipas analisadas */
    no *no_aux;

    for (i=0; i<tab_equipas->tamanho; i++) {

        if (tab_equipas->tab[i] != NULL) {

            /* percorrer cada lista ligada da tabela */
            no_aux = tab_equipas->tab[i];

            while(no_aux != NULL) {

                num_equipas++;

                if ((max_aux = ((equipa)(no_aux->item))->vitorias) > max) {
                    max = max_aux;
                }

                no_aux = no_aux->prox;
            }
        }
    }

    /* caso especial em que a hashtable esta vazia */
    if (num_equipas == 0) {
        return -1;
    }

    else {
        return max;
    }

}

/* funcao de comparacao alfabetica de duas equipas */
int ordem_alfa (const void * equipa_a, const void * equipa_b) {
    return (strcmp((*((equipa *)(equipa_a)))->nome, (*((equipa *)(equipa_b)))->nome));
}

/* lista as equipas mais vitoriosas da tabela de dispersao, uma por linha */
void mostra_equipas_max(tab_disp tab_equipas, int num_linha) {

    int i, max_vitorias;
    int tamanho_max = TAM_INIT;
    int tamanho_vetor = 0;
    no *no_aux;

    max_vitorias = max_vitorias_tab(tab_equipas);

    /* se a tabela nao esta vazia */
    if (max_vitorias != SEMEQUIPAS) {

        equipa *vetor_equipas = (equipa *) can_fail_malloc(tamanho_max * sizeof(equipa));

        for (i = 0; i < tab_equipas->tamanho; i++) {

            /* procurar equipas com o numero maximo de vitorias e inseri-las no vetor */
            if (tab_equipas->tab[i] != NULL) {

                no_aux = tab_equipas->tab[i];

                while (no_aux != NULLequipa) {

                    if ( (((equipa)((no_aux)->item))->vitorias) == max_vitorias) {
                        vetor_equipas[tamanho_vetor ++] = (equipa)(no_aux->item);
                    }

                    no_aux = no_aux->prox;

                    /* duplicar a capacidade do vetor se necessario */
                    if (tamanho_vetor > (tamanho_max / 2)) {
                        tamanho_max *= 2;
                        vetor_equipas = (equipa *) can_fail_realloc(vetor_equipas, tamanho_max);
                    }

                }

            }
        }

        /* ordenar vetor alfabeticamente */
        qsort(vetor_equipas, tamanho_vetor, sizeof(equipa), &ordem_alfa);

        printf("%d Melhores %d\n", num_linha, max_vitorias);

        for (i = 0; i < tamanho_vetor; i++) {
            printf("%d * %s\n", num_linha, vetor_equipas[i]->nome);
        }

        free(vetor_equipas);
    }

}







