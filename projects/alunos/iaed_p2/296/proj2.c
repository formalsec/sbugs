#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Inclusao das estruturas utilizadas no armazenamento de equipas e jogos. */
#include "HashtableJogo.h"
#include "HashtableEquipa.h"

/* Funcao auxiliar que troca o conteudo de dois ponteiros de char. */
#define exch(A, B) {char* t = A; A = B; B = t;}
/* Definicao do tamanho das estruturas que guardam equipas e jogos, bem como a 
   definicao do maximo de caracteres em uma string. Definicao tambem do valor auxiliar
   a funcao cmd_g*/
#define MAX_JOGOS 1997
#define MAX_EQUIPAS 1997
#define MAX_CHAR 1024
#define VALOR_AUX_CMD_G 100



/*
    ---------------- FUNCOES AUXILIARES ----------------
*/

/* Dado um jogo, printa todas as suas informacoes. */
void print_jogo(int nl, char* key, Jogo* jogo) {
    printf("%d %s %s %s %d %d\n", nl, key, 
        jogo->equipa_1->nome_equipa, 
        jogo->equipa_2->nome_equipa, 
        jogo->score_equipa_1, 
        jogo->score_equipa_2);
}

/* Metodo de ordenacao. */
void quicksort(char ** a, int l, int r) {
    char* v;
    int i, j;
    if (r <= l) return;

    i = l - 1;
    j = r;
    /* Pivot : ultimo elemento da lista, onde separa os menores a esquerda e os maiores a direita. */
    v = a[r];
    /* Rearranja os elementos do vetor de acordo com o criterio de ordenacao(ordem alfabetica). */
    while (i < j) {
        while (strcmp(a[++i], v) < 0);
        while (strcmp(v, a[--j]) < 0)
            if (j == l)
                break;

        /* Faz a troca conforme os indices finais. */
        if (i < j)
            exch(a[i], a[j]);
    }
    /* Faz a troca deixando o pivot na sua posicao final. */
    exch(a[i], a[r]);

    /* Aplicacao recursiva do algoritmo aos dois subconjuntos de dados resultantes. */
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

/* Libertacao da memoria alocada pelas estruturas base da funcao principal. */
void free_estruturas(Hashtable_Jogo* htj, Hashtable_Equipa* hte, Lista_Ligada_Jogo* jogos, Lista_Ligada_Equipa* equipas) {
    free_lista_ligada_jogo(jogos);
    free_lista_ligada_equipa(equipas);
    free_hash_jogo(htj);
    free_hash_equipa(hte);
}

/*
    ------------------ FUNCOES SECUNDARIAS ------------------
*/

/* Adiciona um novo jogo ao sistema. */
void cmd_a(Hashtable_Jogo* htj, Hashtable_Equipa* hte, Lista_Ligada_Jogo* jogos, int nl, char* chave, char* ne1, char* ne2, int se1, int se2) {
    Jogo* jogo;
    Equipa* e1, * e2;
    if (ht_pesquisar_jogo(htj, chave))
        printf("%d Jogo existente.\n", nl);
    else {
        /* Verifica a existencia das equipas vinculadas ao jogo. */
        e1 = ht_pesquisar_equipa(hte, ne1);
        e2 = ht_pesquisar_equipa(hte, ne2);
        if (e1 && e2) {
            jogo = j_criar(e1, e2, se1, se2);
            ll_inserir_jogo(jogos, jogo, chave);
            ht_inserir_jogo(htj, jogo, chave);

            /* Caso haja uma equipa vencedora, seu numero de vitorias eh alterado. */
            if (vencedor(jogo))
                vencedor(jogo)->vitorias++;
        }
        else
            printf("%d Equipa inexistente.\n", nl);
    }
}

/* Adiciona uma nova equipa ao sistema. */
void cmd_A(Hashtable_Equipa* hte, Lista_Ligada_Equipa* equipas, int nl, char* chave) {
    Equipa* equipa;
    if (ht_pesquisar_equipa(hte, chave))
        printf("%d Equipa existente.\n", nl);
    else {
        equipa = e_criar(chave);
        ll_inserir_equipa(equipas, equipa, chave);
        ht_inserir_equipa(hte, equipa, chave);
    }
}

/* Lista todos os jogos presentes no sistema por ordem de insercao. */
void cmd_l(Lista_Ligada_Jogo* jogos, int nl) {
    No_Jogo* n;
    for (n = jogos->inicio; n; n = n->prox)
        print_jogo(nl, n->chave, n->jogo);
}

/* Procura um jogo no sistema. */
void cmd_p(Hashtable_Jogo* htj, int nl, char* chave) {
    Jogo* jogo = ht_pesquisar_jogo(htj, chave);
    if (jogo)
        print_jogo(nl, chave, jogo);
    else
        printf("%d Jogo inexistente.\n", nl);
}

/* Procura uma equipa no sistema. */
void cmd_P(Hashtable_Equipa* hte, int nl, char* chave) {
    Equipa* equipa = ht_pesquisar_equipa(hte, chave);
    if (equipa)
        printf("%d %s %d\n", nl, equipa->nome_equipa, equipa->vitorias);
    else
        printf("%d Equipa inexistente.\n", nl);
}

/* Remove um jogo do sistema. */
void cmd_r(Hashtable_Jogo* htj, Lista_Ligada_Jogo* jogos, int nl, char* chave) {
    Jogo* jogo = ht_pesquisar_jogo(htj, chave);
    if (jogo) {
        /* Caso houvesse uma equipa vencedora, seu numero de vitorias eh alterado. */
        if (vencedor(jogo))
            vencedor(jogo)->vitorias--;
        ht_deletar_jogo(htj, chave);
        ll_deletar_jogo(jogos, chave);
    }
    else
        printf("%d Jogo inexistente.\n", nl);
}

/* Altera os resultados de um jogo. */
void cmd_s(Hashtable_Jogo* htj, int nl, char* chave, int se1_novo, int se2_novo) {
    Jogo* antigo = ht_pesquisar_jogo(htj, chave);
    Jogo* novo;
    Equipa* e_antiga, * e_nova;

    if (antigo) {
        novo = j_criar(antigo->equipa_1, antigo->equipa_2, se1_novo, se2_novo);
        /* Verifica e retorna o vencedor em cada partida(antiga e nova). */
        e_antiga = vencedor(antigo);
        e_nova = vencedor(novo);

        /* Apenas faz modificacoes no numero de vitorias caso a 
           equipa que venceu anteriormente seja diferente da nova. */
        if (e_antiga != e_nova) {
            /* Caso exista um novo vencedor. */
            if (e_nova) {
                /* Caso exista um antigo vencedor. */
                if (e_antiga)
                    e_antiga->vitorias--;
                e_nova->vitorias++;
            } /* Caso existisse um antigo vencedor. */
            else if (e_antiga)
                e_antiga->vitorias--;
        }

        /* Faz a alteracao dos resultados. */
        antigo->score_equipa_1 = novo->score_equipa_1;
        antigo->score_equipa_2 = novo->score_equipa_2;
        free(novo);
    }
    else
        printf("%d Jogo inexistente.\n", nl);
}

/* Lista todas as equipas que tiveram o maior numero de vitorias, por ordem alfabetica. */
void cmd_g(Lista_Ligada_Equipa* equipas, int nl) {
    int i, valor_aux = 100, valor_adiciona_aux = 100;
    /* Variavel auxiliar de contagem e controle do maior */
    int index_aux = 0, maior = 0;
    char** equipas_filt;
    No_Equipa* n = equipas->inicio;
    
    if (equipas->inicio) {
        /* Cria uma lista auxiliar, alocando memoria com um valor provisorio de elementos. */
        equipas_filt = can_fail_malloc(sizeof(char*)* valor_aux);
        /* Percorre a lista ligada de jogos para montar uma lista auxiliar apenas com as equipas 
           que possuam o maior numero de vitorias, sobreescrevendo esta lista auxiliar e reiniciando a variavel de contagem 
           caso seja encontrada uma equipa com um maior numero de vitorias. */
        while (n) {
            if (n->equipa->vitorias > maior) {
                maior = n->equipa->vitorias;
                index_aux = 0;
                equipas_filt[index_aux++] = n->chave;
            }
            else if (n->equipa->vitorias == maior) {
                /* Caso o numero de equipas ultrapasse o valor provisorio, este eh atualizado, alocando mais memoria. */
                if (index_aux >= valor_aux) {
                    valor_aux += valor_adiciona_aux;
                    equipas_filt = can_fail_realloc(equipas_filt, sizeof(char*) * valor_aux);
                }
                equipas_filt[index_aux++] = n->chave;
            }
            n = n->prox;
        }

        /* Apos filtrar apenas as equipas com o maior numero de vitorias, ordena a mesma alfabeticamente. */
        quicksort(equipas_filt, 0, index_aux - 1);
        printf("%d Melhores %d\n", nl, maior);
        /* Lista as equipas ja filtradas e ordenadas. */
        for (i = 0; i < index_aux; i++)
                printf("%d * %s\n", nl, equipas_filt[i]);

        free(equipas_filt);
    }
}

/*
    ------------------ FUNCAO PRINCIPAL ------------------
*/

/* Le uma sequencia de dados introduzidos pelo usuario. */
int main() {

    /* Variaveis auxiliares na leitura. */
    int nl = 0, score_equipa_1, score_equipa_2;
    char opcao, nome_jogo[MAX_CHAR], nome_equipa_1[MAX_CHAR], nome_equipa_2[MAX_CHAR];

    /* Cria e inicializa as estruturas necessarias para a manutencao do sistema. */
    Hashtable_Jogo* htj          = ht_criar_jogo(MAX_JOGOS);
    Hashtable_Equipa* hte        = ht_criar_equipa(MAX_EQUIPAS);
    Lista_Ligada_Jogo* jogos     = ll_criar_jogo();
    Lista_Ligada_Equipa* equipas = ll_criar_equipa();

    /*
    Verifica se o input recebido pelo stdin nao eh
    fim de arquivo ou o termo de saida 'x' e realiza
    uma funcao conforme os dados de entrada.
    */
    while ((scanf("%c", &opcao) != EOF) && (opcao != 'x')) {
        nl++;
        switch (opcao) {
        case 'a':
            scanf(" %[^:]:%[^:]:%[^:]:%d:%d", nome_jogo, nome_equipa_1, nome_equipa_2, &score_equipa_1, &score_equipa_2);
            cmd_a(htj, hte, jogos, nl, nome_jogo, nome_equipa_1, nome_equipa_2, score_equipa_1, score_equipa_2);
            break;
        case 'A':
            scanf(" %[^\n]", nome_equipa_1);
            cmd_A(hte, equipas, nl, nome_equipa_1);
            break;
        case 'l':
            cmd_l(jogos, nl);
            break;
        case 'p':
            scanf(" %[^\n]", nome_jogo);
            cmd_p(htj, nl, nome_jogo);
            break;
        case 'P':
            scanf(" %[^\n]", nome_equipa_1);
            cmd_P(hte, nl, nome_equipa_1);
            break;
        case 'r':
            scanf(" %[^\n]", nome_jogo);
            cmd_r(htj, jogos, nl, nome_jogo);
            break;
        case 's':
            scanf(" %[^:]:%d:%d", nome_jogo, &score_equipa_1, &score_equipa_2);
            cmd_s(htj, nl, nome_jogo, score_equipa_1, score_equipa_2);
            break;
        case 'g':
            cmd_g(equipas, nl);
            break;
        }

        getchar();
    }

    /* Liberta todas as estruturas utilizadas no programa. */
    free_estruturas(htj, hte, jogos, equipas);
    return 0;
}