#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>

#include <string.h>

/* String com max de 63 caracteres para descricao de um produto */
#define DESMAX 64

/* Tamanho max do vetor que contem o id dos produtos */
#define PMAX 10000

/* Tamanho max do vetor que contem o id das encomendas */
#define EMAX 500

/* Peso max de uma encomenda */
#define PESOMAX 200


struct __produto__ {
    char DES[DESMAX];    /* Descricao do produto */
    int PR;              /* Preco do produto */
    int PESO;            /* Peso do produto */
    int STCK;            /* Quantidade em stock */
    int VALIDO;          /* Indica se o produto ja foi utilizado numa ordenacao */
};

struct __encomenda__ {
    int QTD[PMAX];       /* Vetor com as quantidades de cada produto na encomenda */
    int PESO;            /* Peso da encomenda <= 200 unidades */
};

struct __produto__ P[PMAX];

struct __encomenda__ E[EMAX];

/* Identificador de produtos, que aumenta cada vez que um novo eh introduzido */
int P_ID = 0;

/* Identificador de encomendas, que aumenta cada vez que uma nova eh introduzida */
int E_ID = 0;

/* Leitor de caracteres que identificam comandos */
char C;

/* Variaveis utilizadas para os comandos */
int IDE, IDP, QTD, PR, ID;

/* Variaveis de contagem */
int A, B, i, N, M;

/* Custo de uma encomenda */
int TOTAL;

/* Numero maximo de ocorrencias de um produto nas encomendas */
int OCORR_MAX, OCORR_MAXN;

void ordena(int OR[PMAX], int l, int r);

int menor_descricao(int CH, int l, int r, struct __produto__ PR[PMAX]);

int main()
{
    /* Vetores de ordenacao */
    int O[PMAX];

    while ((C = getchar()) != EOF) {
        switch(C) {

            /* Adiciona um novo produto ao sistema e devolve o seu numero de identificacao */
            case 'a':
                if (P_ID < PMAX) {
                    scanf(" %[^:]:%d:%d:%d", P[P_ID].DES, &P[P_ID].PR, &P[P_ID].PESO, &P[P_ID].STCK);
                    P[P_ID].VALIDO = 0;
                    printf("Novo produto %d.\n", P_ID++);
                }
                continue;

            /* Adiciona stock a um produto existente no sistema */
            case 'q':
                scanf("%d:%d", &IDP, &QTD);
                if (0 <= IDP && IDP < P_ID) {
                    P[IDP].STCK += QTD;
                }
                else {
                    printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", IDP);
                }
                continue;
            
            /* Cria uma nova encomenda */
            case 'N':
                if (E_ID < EMAX) {
                    printf("Nova encomenda %d.\n", E_ID);
                    ++E_ID;
                    /* Coloca a zero os valores do vetor da encomenda */
                    for (N = 0; N < PMAX; ++N){
                        E[E_ID].QTD[N] = 0;
                    }
                    E[E_ID].PESO = 0;
                }
                continue;

            /* Adiciona um produto a uma encomenda */
            case 'A':
                scanf(" %d:%d:%d", &IDE, &IDP, &QTD);
                if (0 <= IDE && IDE < E_ID) {
                    if (0 <= IDP && IDP < P_ID) {
                        if (P[IDP].STCK - QTD >= 0) {
                            if (E[IDE].PESO + (P[IDP].PESO * QTD) <= PESOMAX) {
                                E[IDE].QTD[IDP] += QTD;
                                E[IDE].PESO += P[IDP].PESO * QTD;
                                P[IDP].STCK = P[IDP].STCK - QTD;
                            }
                            else {
                                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", IDP, IDE);
                            }
                        }
                        else {
                            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", IDP, IDE);
                        }

                    }
                    else {
                        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", IDP, IDE);
                    }

                }
                else {
                    printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", IDP, IDE);
                }
                continue;
            
            /* Remove stock de um produto existente */
            case 'r':
                scanf("%d:%d", &IDP, &QTD);
                if (0 <= IDP && IDP < P_ID) {
                    if (P[IDP].STCK - QTD >= 0) {
                        P[IDP].STCK = P[IDP].STCK - QTD;
                    }
                    else {
                        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", QTD, IDP);
                    }
                }
                else {
                    printf("Impossivel remover stock do produto %d. Produto inexistente.\n", IDP);
                }
                continue;
            
            /* Remove um produto de uma encomenda */
            case 'R':
                scanf("%d:%d", &IDE, &IDP);
                if (0 <= IDE && IDE < E_ID) {
                    if (0 <= IDP && IDP < P_ID) {
                        /* Ajuste do peso da encomenda */
                        E[IDE].PESO = E[IDE].PESO - (P[IDP].PESO * E[IDE].QTD[IDP]);
                        /* Ajuste do stock do produto */
                        P[IDP].STCK += E[IDE].QTD[IDP];
                        E[IDE].QTD[IDP] = 0;
                    }
                    else {
                        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", IDP, IDE);
                    }
                }
                else {
                    printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", IDP, IDE);
                }
                continue;

            /* Calcula o custo de uma encomenda */
            case 'C':
                TOTAL = 0;
                scanf("%d", &IDE);
                if (0 <= IDE && IDE < E_ID) {
                    /* Apenas procura os precos de produtos existentes na encomenda */
                    for (N = 0; N < P_ID; ++N) {
                        TOTAL += E[IDE].QTD[N] * P[N].PR;
                    }
                    printf("Custo da encomenda %d %d.\n", IDE, TOTAL);
                }
                else {
                    printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", IDE);
                }
                continue;
            
            /* Altera o preco de um produto existente no sistema */
            case 'p':
                scanf("%d:%d", &IDP, &PR);
                if (0 <= IDP && IDP < P_ID) {
                    P[IDP].PR = PR;
                }
                else {
                    printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", IDP);
                }
                continue;
            
            /* Lista a descricao e a quantidade de um produto numa encomenda */
            case 'E':
                scanf("%d:%d", &IDE, &IDP);
                if (0 <= IDE && IDE < E_ID) {
                    if (0 <= IDP && IDP < P_ID) {
                        printf("%s %d.\n", P[IDP].DES, E[IDE].QTD[IDP]);
                    }
                    else {
                        printf("Impossivel listar produto %d. Produto inexistente.\n", IDP);
                    }
                }
                else {
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IDE);
                }
                continue;

            /* Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
            case 'm':
                OCORR_MAX = -1;
                OCORR_MAXN = 0;
                scanf("%d", &IDP);
                if (0 <= IDP && IDP < P_ID) {
                    for (N = 0; N <= E_ID; ++N) {
                        if (E[N].QTD[IDP] > OCORR_MAX) {
                            OCORR_MAX = E[N].QTD[IDP];
                            OCORR_MAXN = N;
                        }
                    }
                    if ((E_ID != 0) && (OCORR_MAX > 0)) {
                        printf("Maximo produto %d %d %d.\n", IDP, OCORR_MAXN, OCORR_MAX);
                    }
                }
                else {
                    printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", IDP);
                }
                continue;
            
            /* Lista todos os produtos no sistema por ordem crescente de preco */
            case 'l':
                /* Vetor para ordenar os precos */
                for (N = 0; N < P_ID; ++N) {
                    O[N] = P[N].PR;
                }
                printf("Produtos\n");
                ordena(O, 0, N - 1);
                for (N = 0; N < P_ID; ++N) {
                    for (M = 0; M < P_ID; ++M) {
                        /* Se o produto ja foi listado, nao podera ser listado novamente (VALIDO) */
                        if ((O[N] == P[M].PR) && (P[M].VALIDO == 0)) {
                            printf("* %s %d %d\n", P[M].DES, P[M].PR, P[M].STCK);
                            P[M].VALIDO = 1;
                        }
                    }
                }
                /* Coloca a validade novamente a 0 */
                for (N = 0; N < P_ID; ++N) {
                    P[N].VALIDO = 0;
                }
                continue;
            
            /* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
            case 'L':
                A = 0;
                B = 0;
                scanf("%d", &IDE);
                if (0 <= IDE && IDE < E_ID){
                    for (N = 0; N < P_ID; ++N) {
                        if (E[IDE].QTD[N] > 0) {
                            O[A++] = P[N].DES[0];
                        }
                    }
                    printf("Encomenda %d\n", IDE);
                    ordena(O, 0, A - 1);
                    for (N = 0; N < A; ++N) {
                        for (M = 0; M < A; ++M) {
                            if ((O[N] == P[M].DES[0]) && (P[M].VALIDO == 0)) {
                                /* Se houver produtos com a mesma letra inicial */
                                if ((O[N] == O[N+1] && N < A - 1) || (O[N] == O[N-1] && N > 1)) {
                                    ID = menor_descricao(O[N], B, A, P);
                                    /* A funcao menor_descricao devolve o ID do produto com menor descricao */
                                    printf("* %s %d %d\n", P[ID].DES, P[ID].PR, E[IDE].QTD[ID]);
                                    /* Verifica que este elemento nao sera lido novamente */
                                    P[ID].VALIDO = 1;
                                    /* Na proxima leitura, a funcao menor_descricao devolve o elemento seguinte */
                                    ++B;
                                }
                                else {
                                    printf("* %s %d %d\n", P[M].DES, P[M].PR, E[IDE].QTD[M]);
                                    P[M].VALIDO = 1;
                                    B = 0;
                                }
                            }
                        }
                    }
                    /* Coloca a validade novamente a 0 */
                    for (N = 0; N < P_ID; ++N) {
                        P[N].VALIDO = 0;
                    }
                }
                else {
                    printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", IDE);
                }
                continue;
            
            /* Termina o programa */
            case 'x':
                break;
        }
    }
    return 0;
}


/* Funcao que ordena um vetor de modo crescente */
void ordena(int OR[PMAX], int l, int r)
{
    /* Insertion Sort */
    int i, j;
    for (i = l+1; i <= r; ++i) {
        int v = OR[i];
        j = i-1;
        while ((j >= l) && (OR[j] > v)) {
            OR[j+1] = OR[j];
            j--;
        }
        OR[j+1] = v;
    }
}


/* Funcao que devolve o ID do l esimo produto, cuja descricao inicia com o caracter CH */
int menor_descricao(int CH, int l, int r, struct __produto__ PR[PMAX])
{
    /* Matriz que contem a ordem por ID dos produtos iniciados com o caracter CH */
    char V[PMAX][DESMAX];
    /* Vetor que contem os indices dos produtos associados a V */
    int Vi[PMAX];
    /* Vetor auxiliar */
    char A[DESMAX];
    /* Variaveis */
    int a = 0, b = 0, i = 0, j = 0, k = 0;
    int nenhuma_troca = 1;
    for (i = 0; i < r; ++i) {
        /* Produtos iniciados com o caracter CH */
        if (PR[i].DES[0] == CH) {
            strcpy(V[b], PR[i].DES);
            Vi[b++] = i;
        }
    }
    /* Ordenacao das descricoes */
    nenhuma_troca = 0;
    for (i = 0; i < b-1; ++i) {
        /* k = menor dos tamanhos da string */
        k = 1;
        if (strlen(V[i]) < strlen(V[i+1]) && i < DESMAX-1) {
            k = (int) strlen(V[i]);
        }
        else {
            k = (int) strlen(V[i+1]);
        }
        /* Leitura da string e comparacao com a string seguinte */
        for (j = 1; j < k; ++j) {
            /* Se o elemento seguinte for menor, troca as posicoes */
            if (V[i][j] > V[i+1][j]) {
                strcpy(A, V[i]);
                strcpy(V[i], V[i+1]);
                strcpy(V[i+1], A);
                a = Vi[i];
                Vi[i] = Vi[i+1];
                Vi[i+1] = a;
                nenhuma_troca = 1;
            }
        }
        /* No caso de uma string terminar sem haver trocas */
        if (nenhuma_troca == 0) {
            /* Verifica qual terminou, e troca se for a seguinte */
            if ((int) strlen(V[i+1]) == k && (int) strlen(V[i]) != k) {
                strcpy(A, V[i]);
                strcpy(V[i], V[i+1]);
                strcpy(V[i+1], A);
                a = Vi[i];
                Vi[i] = Vi[i+1];
                Vi[i+1] = a;
            }
        }
    }
    return Vi[l];
}