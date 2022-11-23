#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************************************************/
/*defini as constantes que serao necessarias.                                 */
/******************************************************************************/
#define MAXCHAR 1023
#define HASHTABLE_TAM 167


/******************************************************************************/
/* Criar as estruturas necessarias no programa.                               */
/******************************************************************************/
typedef struct {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
} jogo;

typedef struct nodeJ {
    int NL;
    jogo j;
    struct nodeJ *next;
} nodeJ;

typedef struct {
    char *nome;
    int jogosGanhos;
} equipa;

typedef struct nodeE {
    equipa e;
    struct nodeE *next;
} nodeE;


/******************************************************************************/
/* Criar a hashtable com as equipas no sistema, que ficarao em cada balde,    */
/*dependendo do valor total das letras de cada nome do jogo.                  */
/******************************************************************************/
int hashString(char *s) {
    int i, total = 0, len = strlen(s);
    for (i = 0; i < len; i++) {
        total += (int) s[i];
    }
    return total % HASHTABLE_TAM;
}

/******************************************************************************/
/* Ira verificar a existencia de um certo jogo, dado o nome do mesmo.         */
/******************************************************************************/
nodeJ *JogoExiste(char *nome, nodeJ *headJ) {
    nodeJ *n;
    if (!headJ)
        return 0;
    if (!strcmp(headJ->j.nome, nome))
        return headJ;
    n = headJ;
    while (n->next) {
        n = n->next;
        if (!strcmp(n->j.nome, nome))
            return n;
    }
    return NULL;
}

/******************************************************************************/
/* Ira verificar a existencia de uma certa equipa, dado o nome da equipa.     */
/******************************************************************************/
nodeE *EquipaExiste(char *equipa, nodeE *headE) {
    nodeE *n;
    if (!headE)
        return 0;
    if (!strcmp(headE->e.nome, equipa))
        return headE;
    n = headE;
    while (n->next) {
        n = n->next;
        if (!strcmp(n->e.nome, equipa))
            return n;
    }
    return NULL;
}

/******************************************************************************/
/* Aumenta uma unidade aos jogos ganhos de uma certa equipa.                  */
/******************************************************************************/
void IncrementaJogosGanhos(char *nome, nodeE **h) {
    nodeE *n;
    n = *h;
    while (n) {
        if (!strcmp(n->e.nome, nome)) {
            n->e.jogosGanhos++;
            break;
        }
        n = n->next;
    }
}

/******************************************************************************/
/* Diminui uma unidade aos jogos ganhos de uma certa equipa.                  */
/******************************************************************************/
void DecrementaJogosGanhos(char *nome, nodeE **h) {
    nodeE *n;
    n = *h;
    while (n) {
        if (!strcmp(n->e.nome, nome)) {
            n->e.jogosGanhos--;
            break;
        }
        n = n->next;
    }
}

/******************************************************************************/
/* Adiciona um novo jogo ao sistema.                                          */
/******************************************************************************/
void AdicionaNovoJogo(int NL, nodeJ **htJ, nodeE **htE) {
    int a, b, ind, indE1, indE2;
    nodeJ *n, *headJ;
    char buffer1[MAXCHAR];
    char buffer2[MAXCHAR];
    char buffer3[MAXCHAR];
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", buffer1, buffer2, buffer3, &a, &b);

    ind = hashString(buffer1);
    headJ = htJ[ind];

    if (JogoExiste(buffer1, headJ)) {
        printf("%d Jogo existente.\n", NL);
        return;
    }
    indE1 = hashString(buffer2);
    indE2 = hashString(buffer3);
    if (!EquipaExiste(buffer2, htE[indE1]) || !EquipaExiste(buffer3, htE[indE2])) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    /* Alocar memoria, inicializando tudo a 0.                                */
    if (!headJ) {
        htJ[ind] = can_fail_calloc(1, sizeof(nodeJ));
        n = htJ[ind];
    } else {
        n = headJ;
        while (n->next)
            n = n->next;
        n->next = can_fail_calloc(1, sizeof(nodeJ));
        n = n->next;
    }

    n->j.nome = can_fail_malloc(strlen(buffer1) + 1);
    n->j.equipa1 = can_fail_malloc(strlen(buffer2) + 1);
    n->j.equipa2 = can_fail_malloc(strlen(buffer3) + 1);

    strcpy(n->j.nome, buffer1);
    strcpy(n->j.equipa1, buffer2);
    strcpy(n->j.equipa2, buffer3);
    n->j.score1 = a;
    n->j.score2 = b;
    n->NL = NL;

    if (a > b)
        IncrementaJogosGanhos(buffer2, &htE[indE1]);
    else if (b > a)
        IncrementaJogosGanhos(buffer3, &htE[indE2]);
}

/******************************************************************************/
/* Lista todos os jogos pela ordem em que foram introduzidos.                 */
/******************************************************************************/
void ListaJogos(int NL, nodeJ **htJ) {
    int j, ind, val;

    nodeJ **n = can_fail_calloc(HASHTABLE_TAM, sizeof(nodeJ *));

    for (j = 0; j < HASHTABLE_TAM; j++) {
        n[j] = htJ[j];
    }

    while (1) {
        ind = -1;
        val = -1;
        for (j = 0; j < HASHTABLE_TAM; ++j) {
            if (n[j])
                if (n[j]->NL < val || val == -1) {
                    ind = j;
                    val = n[j]->NL;
                }
        }
        if (ind == -1) {
            /* Libertar memoria.                                              */
            free(n);
            return;
        } else {
            printf("%d %s %s %s %d %d\n", NL, n[ind]->j.nome, n[ind]->j.equipa1,
             n[ind]->j.equipa2, n[ind]->j.score1, n[ind]->j.score2);
            n[ind] = n[ind]->next;
        }
    }
}

/******************************************************************************/
/* Procura um certo jogo no sistema, dando erro caso o jogo seja inexistente. */
/******************************************************************************/
void ProcuraJogo(int NL, nodeJ **htJ) {
    nodeJ *n;
    int ind;
    char buffer1[MAXCHAR];
    scanf(" %[^:\n]", buffer1);

    ind = hashString(buffer1);

    n = JogoExiste(buffer1, htJ[ind]);

    if (!n) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    } else {
        printf("%d %s %s %s %d %d\n", NL, n->j.nome, n->j.equipa1, n->j.equipa2, n->j.score1, n->j.score2);
        return;
    }
}

/******************************************************************************/
/* Apaga um jogo dado um nome.*/
/******************************************************************************/
void ApagaJogo(int NL, nodeJ **htJ, nodeE **htE) {
    nodeJ *n, *tmp = NULL, *headJ;
    int ind, indE1, indE2, flag = 0;
    char buffer1[MAXCHAR];
    scanf(" %[^:\n]", buffer1);

    ind = hashString(buffer1);
    headJ = htJ[ind];

    if (headJ) {
        /* Verifica se o jogo no indice corresponde ao buffer1. Se corresponde*/
        /*, entao a flag sera 1, e o programa passa para a proxima condicao,  */
        /* se nao for, entao verificara se o jogo no proximo indice sera, e   */
        /* assim em diante.                                                   */
        if (!strcmp(headJ->j.nome, buffer1)) {
            tmp = headJ;
            htJ[ind] = headJ->next;
            flag = 1;
        } else {
            n = headJ;
            while (n->next) {
                if (!strcmp(n->next->j.nome, buffer1)) {
                    tmp = n->next;
                    n->next = n->next->next;
                    flag = 1;
                    break;
                }
                n = n->next;
            }
        }
    }
    if (!flag) {
        printf("%d Jogo inexistente.\n", NL);
    } else {
        indE1 = hashString(tmp->j.equipa1);
        indE2 = hashString(tmp->j.equipa2);

        if (tmp->j.score1 > tmp->j.score2) {
            DecrementaJogosGanhos(tmp->j.equipa1, &htE[indE1]);
        } else if (tmp->j.score1 < tmp->j.score2) {
            DecrementaJogosGanhos(tmp->j.equipa2, &htE[indE2]);
        }

        free(tmp->j.equipa1);
        free(tmp->j.equipa2);
        free(tmp->j.nome);
        free(tmp);
    }

}

/******************************************************************************/
/* Altera o reultado de um jogo.                                              */
/******************************************************************************/
void AlteraScore(int NL, nodeJ **htJ, nodeE **htE) {
    int a, b, c, d, ind, indE1, indE2;
    nodeJ *n, *headJ;
    char buffer1[MAXCHAR];
    scanf(" %[^:]:%d:%d", buffer1, &a, &b);

    ind = hashString(buffer1);
    headJ = htJ[ind];

    n = JogoExiste(buffer1, headJ);

    if (!n) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    c = n->j.score1;
    d = n->j.score2;
    n->j.score1 = a;
    n->j.score2 = b;

    indE1 = hashString(n->j.equipa1);
    indE2 = hashString(n->j.equipa2);

    /* Consoante o resultado antigo e o resultado apos o novo score, os jogos */
    /*ganhos e perdidos sao incrementados ou decrementados ou mantidos iguais.*/
    if (a > b && c <= d)
        IncrementaJogosGanhos(n->j.equipa1, &htE[indE1]);
    else if (a <= b && c > d)
        DecrementaJogosGanhos(n->j.equipa1, &htE[indE1]);
    if (a < b && c >= d)
        IncrementaJogosGanhos(n->j.equipa2, &htE[indE2]);
    else if (a >= b && c < d)
        DecrementaJogosGanhos(n->j.equipa2, &htE[indE2]);

}

/******************************************************************************/
/* Adiciona nova equipa ao sistema.                                           */
/******************************************************************************/
void AdicionaNovaEquipa(int NL, nodeE **htE, int *numE) {
    nodeE *n, *headE;
    int ind;
    char buffer1[MAXCHAR];
    scanf(" %[^:\n]", buffer1);

    ind = hashString(buffer1);
    headE = htE[ind];

    if (EquipaExiste(buffer1, headE)) {
        printf("%d Equipa existente.\n", NL);
        return;
    }

    if (!headE) {
        htE[ind] = can_fail_calloc(1, sizeof(nodeE));
        n = htE[ind];
    } else {
        n = headE;
        while (n->next)
            n = n->next;
        n->next = can_fail_calloc(1, sizeof(nodeE));
        n = n->next;
    }

    n->e.nome = can_fail_malloc(strlen(buffer1) + 1);

    strcpy(n->e.nome, buffer1);
    n->e.jogosGanhos = 0;
    *numE = *numE + 1;

}

/******************************************************************************/
/* Procura uma equipa dado um nome.                                           */
/******************************************************************************/
void ProcuraEquipa(int NL, nodeE **htE) {
    nodeE *n;
    int ind;
    char buffer1[MAXCHAR];
    scanf(" %[^:\n]", buffer1);

    ind = hashString(buffer1);

    n = EquipaExiste(buffer1, htE[ind]);

    if (!n) {
        printf("%d Equipa inexistente.\n", NL);
        return;
    }

    printf("%d %s %d\n", NL, n->e.nome, n->e.jogosGanhos);
}

/******************************************************************************/
/* Compara dois elementos.                                                    */
/******************************************************************************/
int comparador(const void *a, const void *b) {
    return strcmp((*(nodeE **) a)->e.nome, (*(nodeE **) b)->e.nome);
}

/******************************************************************************/
/* Verifica quais as equipas com mais jogos ganhos e caso haja equipas com o  */
/*mesmo numero de jogos ganhos, eh listado segundo o conforme o nome da equipa*/
/******************************************************************************/
void EquipasGanhadoras(int NL, nodeE **htE) {
    nodeE **n, **array;
    int i = 0, j, jogosGanhos = 0, numE = 0;

    n = can_fail_calloc(HASHTABLE_TAM, sizeof(nodeJ *));

    for (j = 0; j < HASHTABLE_TAM; j++) {
        n[j] = htE[j];
    }

    for (j = 0; j < HASHTABLE_TAM; j++) {
        while (n[j]) {
            /* Verifica se alguma equipa tem mais jogos ganhos que a equipa   */
            /*com mais jogos ganhos ate ao momento.                           */
            if (n[j]->e.jogosGanhos > jogosGanhos) {
                jogosGanhos = n[j]->e.jogosGanhos;
                numE = 1;
            } else if (n[j]->e.jogosGanhos == jogosGanhos) {
                /* Numero de equipas que tem tantos jogos ganhos quanto a     */
                /*equipa com mais.                                            */
                numE++;
            }
            n[j] = n[j]->next;
        }
    }

    if (!numE){
        free(n);
        return;
    }

    array = (nodeE **) can_fail_calloc(numE, sizeof(nodeE *));

    for (j = 0; j < HASHTABLE_TAM; j++) {
        n[j] = htE[j];
    }

    for (j = 0; j < HASHTABLE_TAM; j++) {
        while (n[j]) {
            if (n[j]->e.jogosGanhos == jogosGanhos) {
                array[i] = n[j];
                i++;
            }
            n[j] = n[j]->next;
        }
    }

    /* Dentro de as equipas que terao o maximo de jogos ganhos, estas serao   */
    /*ordenadas por ordem alfabetica, utilizando o comparador, sendo o array a*/
    /*lista ordenada.                                                         */
    qsort(array, numE, sizeof(nodeE *), comparador);

    printf("%d Melhores %d\n", NL, jogosGanhos);
    for (i = 0; i < numE; i++)
            printf("%d * %s\n", NL, array[i]->e.nome);

    free(array);
    free(n);
}

/******************************************************************************/
/* Termina o programa.                                                        */
/* Liberta a memoria que esta a ser ocupada.                                  */
/******************************************************************************/
void Terminar(nodeJ **htJ, nodeE **htE) {
    nodeE *nE, *tmpE, *headE;
    nodeJ *nJ, *tmpJ, *headJ;
    int i;

    for (i = 0; i < HASHTABLE_TAM; ++i) {
        headJ = htJ[i];
        if (headJ) {
            nJ = headJ;
            while (nJ->next) {
                tmpJ = nJ->next;
                nJ->next = nJ->next->next;
                free(tmpJ->j.equipa1);
                free(tmpJ->j.equipa2);
                free(tmpJ->j.nome);
                free(tmpJ);
            }
            free(nJ->j.equipa1);
            free(nJ->j.equipa2);
            free(nJ->j.nome);
            free(nJ);
        }
    }

    for (i = 0; i < HASHTABLE_TAM; ++i) {
        headE = htE[i];
        if (headE) {
            nE = headE;
            while (nE->next) {
                tmpE = nE->next;
                nE->next = nE->next->next;
                free(tmpE->e.nome);
                free(tmpE);
            }
            free(nE->e.nome);
            free(nE);
        }
    }
    free(htJ);
    free(htE);
}

int main() {
    nodeJ **hashtableJ = can_fail_calloc(HASHTABLE_TAM, sizeof(nodeJ *));
    nodeE **hashtableE = can_fail_calloc(HASHTABLE_TAM, sizeof(nodeE *));

    int car, NL = 0, numE = 0;

    /*ve qual sera o primeiro caracter*/
    while ((car = getchar())) {
        NL++;
        switch (car) {
            case 'a':
                AdicionaNovoJogo(NL, hashtableJ, hashtableE);
                break;
            case 'l' :
                ListaJogos(NL, hashtableJ);
                break;
            case 'p' :
                ProcuraJogo(NL, hashtableJ);
                break;
            case 'r' :
                ApagaJogo(NL, hashtableJ, hashtableE);
                break;
            case 's' :
                AlteraScore(NL, hashtableJ, hashtableE);
                break;
            case 'A' :
                AdicionaNovaEquipa(NL, hashtableE, &numE);
                break;
            case 'P' :
                ProcuraEquipa(NL, hashtableE);
                break;
            case 'g' :
                EquipasGanhadoras(NL, hashtableE);
                break;
            case 'x':
                Terminar(hashtableJ, hashtableE);
                return 0;

        }
        getchar();
    }
    return 0;
}
