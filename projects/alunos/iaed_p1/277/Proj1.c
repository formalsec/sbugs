#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 64                      /* O numero maximo de caracteres da descricao. */
#define MAX_PRODUTOS 10000          /* O numero maximo de produtos do sistema. */
#define MAX_ENCOMENDAS 500          /* O numero maximo de encomendas. */
#define MAX_PESO 200                /* O valor maximo do peso de uma encomenda. */
#define STRING 80                   /* O numero maximo de caracteres do input apos o comando. */ 
#define VETOR_AUX 8                 /* O numero maximo de informacoes recebidas no input apos o comando. */


/* Estrutura produto. */
typedef struct produto {
    char descricao[MAX];
    int preco;
    int peso;
    int qtd;
    int identificador;
} Produto;


/* Estrutura encomenda. */
typedef struct encomenda {
    Produto p[MAX_PESO];
    int peso; 
    int preco;
    int variedade;
} Encomenda;

Produto nprodutos[MAX_PRODUTOS];            /* Lista de produtos. */
Encomenda n_encomendas[MAX_ENCOMENDAS];     /* Lista de encomendas. */
Produto copia_p[MAX_PRODUTOS];              /* Lista de produtos no sistema a ordenar. */
Encomenda copia_e[MAX_ENCOMENDAS];          /* Lista de produtos numa encomenda a ordenar. */


/* Funcao auxiliar que separa o input recebido apos um comando. */
char* separador(char s[STRING], char v[VETOR_AUX][MAX]) {
    int i;
    char* str;
    i = 0;
    str = strtok(s, ":");
    while (str != 0) {
        strcpy(v[i], str);
        str = strtok(0, ":");
        i++;
    }
    return (char*)v;
}


/* Adiciona um novo produto ao sistema.
    a descricao:preco:peso:qtd   -->   Novo produto <idp>. */
int a(Produto nprodutos[MAX_PRODUTOS], char s[STRING], int idp) {
    char v[VETOR_AUX][MAX];
    separador(s, v);
    strcpy(nprodutos[idp].descricao, v[0]);
    nprodutos[idp].preco = atoi(v[1]);
    nprodutos[idp].peso = atoi(v[2]);
    nprodutos[idp].qtd = atoi(v[3]);
    nprodutos[idp].identificador = idp;

    printf("Novo produto %d.\n", idp);
    return ++idp;
}


/* Adiciona stock a um produto existente no sistema.
    q idp:qtd   -->   NADA (excepto erro) */
void q(Produto nprodutos[MAX_PRODUTOS], char s[STRING], int idp) {
    char v[VETOR_AUX][MAX];
    int idp_aux, adiciona_quantidade;
    separador(s, v);
    idp_aux = atoi(v[0]);
    adiciona_quantidade = atoi(v[1]);

    if (idp_aux >= idp) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
    }
    else {
        nprodutos[idp_aux].qtd += adiciona_quantidade;
    }
}


/* Remove stock a um produto existente.
    r idp:qtd   -->   NADA (excepto erro) */
void r(Produto nprodutos[MAX_PRODUTOS] , char s[STRING], int idp) {
    char v[VETOR_AUX][MAX];
    int idp_aux, retira_quantidade;
    separador(s, v);
    idp_aux = atoi(v[0]);
    retira_quantidade = atoi(v[1]);

    if(idp_aux >= idp) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
    }
    else if (retira_quantidade > nprodutos[idp_aux].qtd) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", retira_quantidade, idp_aux); 
    }
    else {
        nprodutos[idp_aux].qtd -= retira_quantidade;
    }    
}


/* Altera o preco de um produto existente no sistema.
    p idp:preco   -->   NADA (excepto erro) */
void p(Produto nprodutos[MAX_PRODUTOS] , char s[STRING], int idp, int ide, Encomenda n_encomendas[MAX_ENCOMENDAS]) {
    char v[VETOR_AUX][MAX];
    int idp_aux, preco_novo, i;
    separador(s, v);
    idp_aux = atoi(v[0]);
    preco_novo = atoi(v[1]);

    if (idp_aux >= idp) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
    }
    else {
        nprodutos[idp_aux].preco = preco_novo;
        for(i = 0; i < ide; i++) {
            n_encomendas[i].p[idp_aux].preco = preco_novo;
        }
    }
}


/* Funcao auxiliar que calcula o peso de uma encomenda. */
int peso_encomenda(Encomenda n_encomendas[MAX_ENCOMENDAS], int ide_aux, int idp) {
    int i;
    n_encomendas[ide_aux].peso = 0;
    for(i = 0; n_encomendas[ide_aux].p[i].descricao < n_encomendas[ide_aux].p[idp].descricao; i++) {
        n_encomendas[ide_aux].peso += n_encomendas[ide_aux].p[i].qtd * n_encomendas[ide_aux].p[i].peso;
    }
    return n_encomendas[ide_aux].peso;
}


/* Adiciona um produto a uma encomenda. Se o produto ja existir na encomenda, adiciona nova quantidade
    a quantidade existente.
    A ide:idp:qtd   --->   NADA (excepto erro) */
void A(Encomenda n_encomendas[MAX_ENCOMENDAS], Produto nprodutos[MAX_PRODUTOS], char s[STRING], int ide, int idp) {
    char v[VETOR_AUX][MAX];
    int ide_aux, idp_aux, adiciona_quantidade;
    int soma = 0;
    separador(s, v);
    ide_aux = atoi(v[0]);
    idp_aux = atoi(v[1]);
    adiciona_quantidade = atoi(v[2]);

    if (ide_aux >= ide) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    }
    else if (idp_aux >= idp) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    }
    else if (adiciona_quantidade > nprodutos[idp_aux].qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp_aux, ide_aux);
    }
    else {
        soma += adiciona_quantidade * nprodutos[idp_aux].peso;
        soma += peso_encomenda(n_encomendas, ide_aux, idp);
        if (soma <= MAX_PESO) {
            if (n_encomendas[ide_aux].p[idp_aux].qtd == 0) {                                /* O produto nao existe na encomenda. */
                nprodutos[idp_aux].qtd -= adiciona_quantidade;
                n_encomendas[ide_aux].p[idp_aux].qtd = adiciona_quantidade;
                n_encomendas[ide_aux].p[idp_aux].preco = nprodutos[idp_aux].preco;
                n_encomendas[ide_aux].p[idp_aux].peso = nprodutos[idp_aux].peso;
                strcpy(n_encomendas[ide_aux].p[idp_aux].descricao, nprodutos[idp_aux].descricao);
                n_encomendas[ide_aux].p[idp_aux].identificador = nprodutos[idp_aux].identificador;
                n_encomendas[ide_aux].variedade += 1;
            }
            else {                                                                          /* O produto existe na encomenda. */
                n_encomendas[ide_aux].p[idp_aux].qtd += adiciona_quantidade;
                nprodutos[idp_aux].qtd -= adiciona_quantidade;
            }
        }
        else {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp_aux, ide_aux);
        }
    }  
}


/* Remove um produto de uma encomenda. 
    R ide:idp   -->   NADA (excepto erro) */
void R(Encomenda n_encomendas[MAX_ENCOMENDAS], Produto nprodutos[MAX_PRODUTOS], char s[STRING], int ide, int idp) {
    char v[VETOR_AUX][MAX];
    int ide_aux, idp_aux;
    separador(s, v);
    ide_aux = atoi(v[0]);
    idp_aux = atoi(v[1]);

    if (ide_aux >= ide) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp_aux, ide_aux);
    }
    else if (idp_aux >= idp) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp_aux, ide_aux);
    }
    else {
        nprodutos[idp_aux].qtd += n_encomendas[ide_aux].p[idp_aux].qtd;
        n_encomendas[ide_aux].p[idp_aux].qtd = 0;
        
        n_encomendas[ide_aux].p[idp_aux].preco = nprodutos[idp_aux].preco;
        n_encomendas[ide_aux].p[idp_aux].peso = nprodutos[idp_aux].peso;
        strcpy(n_encomendas[ide_aux].p[idp_aux].descricao, nprodutos[idp_aux].descricao);
        n_encomendas[ide_aux].p[idp_aux].identificador = nprodutos[idp_aux].identificador;
    }  
}


/* Calcula o custo de uma encomenda.
    C ide   -->   Custo da encomenda <ide> <total>. */
void C(Encomenda n_encomendas[MAX_ENCOMENDAS], int ide, int idp) {
    int ide_aux, i, total = 0;
    scanf("%d", &ide_aux);

    if (ide_aux >= ide) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
    else {
        for(i = 0; n_encomendas[ide_aux].p[i].descricao < n_encomendas[ide_aux].p[idp].descricao; i++) {
        total += n_encomendas[ide_aux].p[i].qtd * n_encomendas[ide_aux].p[i].preco;
        }
        printf("Custo da encomenda %d %d.\n", ide_aux, total);
    }
}


/* Lista a descricao e a quantidade de um produto numa encomenda.
    E ide:idp   -->   <desc> <qtd>. */
int E(Encomenda n_encomendas[MAX_ENCOMENDAS], char s[STRING], int ide, int idp, Produto nprodutos[MAX_PRODUTOS]) {
    char v[VETOR_AUX][MAX];
    int ide_aux, idp_aux;
    separador(s, v);
    ide_aux = atoi(v[0]);
    idp_aux = atoi(v[1]);

    if (ide_aux >= ide) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
    else if (idp_aux >= idp) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp_aux);
    }
    else {
        printf("%s %d.\n", nprodutos[idp_aux].descricao, n_encomendas[ide_aux].p[idp_aux].qtd);
    }
    return 0;
}


/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes. Em caso de igualdade,
    imprime a encomenda de menor id.
    m idp   -->   Maximo produto <idp> <ide> <qtd>. */
void m(Encomenda n_encomendas[MAX_ENCOMENDAS], int ide, int idp) {
    int idp_aux, maior, i, ide_aux;
    scanf("%d", &idp_aux);

    if (idp_aux >= idp) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp_aux);
    }
    else {
        maior = 0;
        ide_aux = 0;
        if (ide >= ide_aux) {
            for(i = 0; n_encomendas[i].p[idp_aux].descricao <= n_encomendas[ide].p[idp_aux].descricao; i++) {
                if (n_encomendas[i].p[idp_aux].qtd != 0 && n_encomendas[i].p[idp_aux].qtd > maior) {
                    maior = n_encomendas[i].p[idp_aux].qtd;
                    ide_aux = i;
                }
            }
            if (maior > 0) {
                printf("Maximo produto %d %d %d.\n", idp_aux, ide_aux, maior);
            }
        }
    }
}


/* Funcao auxiliar que copia os produtos existentes no sistema. */
void copia(Produto nprodutos[MAX_PRODUTOS], Produto copia_p[MAX_PRODUTOS], int idp) {
    int i;
    for (i = 0; i < idp; i++) {
        strcpy(copia_p[i].descricao, nprodutos[i].descricao);
        copia_p[i].preco = nprodutos[i].preco;
        copia_p[i].peso = nprodutos[i].peso;
        copia_p[i].qtd = nprodutos[i].qtd;
        copia_p[i].identificador = nprodutos[i].identificador;
    }
}


/* Funcao auxiliar que faz a troca dos produtos no sistema. */
void exch_p(Produto copia_p[], int i, int j) {
    Produto a = copia_p[i];
    copia_p[i] = copia_p[j];
    copia_p[j] = a;
}


/* Funcao auxiliar que realiza a particao dos produtos do sistema. */
int particao_preco(Produto copia_p[], int l, int r) {
    int i, j;
    Produto v = copia_p[r];
    i = l-1;

    for (j = l; j <= r-1; j++) {
        if (copia_p[j].preco < v.preco) {
            i++;
            exch_p(copia_p, i, j);
        }
        else if (copia_p[j].preco == v.preco) {
            if ( v.identificador > copia_p[j].identificador) {
                i++;
                exch_p(copia_p, i, j);
            }
        }
    }
    exch_p(copia_p, i+1, r);
    return (i+1);
}


/* Funcao auxiliar que ordena os produtos do sistema. */
void ordena_preco(Produto copia_p[], int l, int r) {
    int i;
    if (l < r) {
        i = particao_preco(copia_p, l, r);
        ordena_preco(copia_p, l, i-1);
        ordena_preco(copia_p, i+1, r);
    }
}


/* Lista todos os produtos existentes no sistema por ordem crescente de preco. Em caso de igualdade,
    imprime esses por ordem crescente de id.
    l   --> Produtos
            * <desc1> <preco1> <qtd1>
            * ...                      */
void l (Produto nprodutos[MAX_PRODUTOS], Produto copia_p[MAX_PRODUTOS], int idp) {
    int i;
    copia(nprodutos, copia_p, idp);
    printf("Produtos\n");
    ordena_preco(copia_p, 0, idp-1);
    for(i = 0; i < idp; i++) {
        printf("* %s %d %d\n", copia_p[i].descricao, copia_p[i].preco, copia_p[i].qtd);
    }
}


/* Funcao auxiliar que copia os produtos numa encomenda. */
void copia_encomenda(Encomenda n_encomendas[MAX_ENCOMENDAS], Encomenda copia_e[MAX_ENCOMENDAS], int ide_aux) {
    int i;
    for (i = 0; i < n_encomendas[ide_aux].variedade; i++) {
        strcpy(copia_e[ide_aux].p[i].descricao, n_encomendas[ide_aux].p[i].descricao);
        copia_e[ide_aux].p[i].preco = n_encomendas[ide_aux].p[i].preco;
        copia_e[ide_aux].p[i].peso = n_encomendas[ide_aux].p[i].peso;
        copia_e[ide_aux].p[i].qtd = n_encomendas[ide_aux].p[i].qtd;
        copia_e[ide_aux].p[i].identificador = n_encomendas[ide_aux].p[i].identificador;
        copia_e[ide_aux].peso = n_encomendas[ide_aux].peso;
        copia_e[ide_aux].preco = n_encomendas[ide_aux].preco;
        copia_e[ide_aux].variedade = n_encomendas[ide_aux].variedade;
    }
}


/* Funcao auxiliar que realiza a troca dos produtos na encomenda. */
void exch_e(Encomenda copia_e[], int i, int j, int ide_aux) {
    Encomenda a[MAX_ENCOMENDAS];
    a[ide_aux].p[0] = copia_e[ide_aux].p[i];
    copia_e[ide_aux].p[i] = copia_e[ide_aux].p[j];
    copia_e[ide_aux].p[j] = a[ide_aux].p[0];
}


/* Funcao auxiliar que realiza a particao dos produtos na encomenda. */
int particao(Encomenda copia_e[], int l, int r, int ide_aux) {
    int i = l-1;
    int j = r;
    Encomenda v = copia_e[r];
    while (i < j) {
        while (strcmp(copia_e[ide_aux].p[++i].descricao, v.p[r].descricao) < 0);
        while (strcmp(v.p[r].descricao, copia_e[ide_aux].p[--j].descricao) < 0)
            if (j == l)
                break;
        if (i < j)
            exch_e(copia_e, i, j, ide_aux);
    }
    exch_e(copia_e, i, r, ide_aux);
    return i;
}


/* Funcao auxiliar que ordena os produtos na encomenda. */
void ordena_descricao(Encomenda copia_e[], int l, int r, int ide_aux) {
    int i;
    if (r <= l)
        return;

    i = particao(copia_e, l, r, ide_aux);
    ordena_descricao(copia_e, l, i-1, ide_aux);
    ordena_descricao(copia_e, i+1, r, ide_aux);
}


/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao.
    L <ide>   --> Encomenda <ide>
                  * <desc1> <preco1> <qtd1>
                  * ...                     */
void L (Encomenda n_encomendas[MAX_ENCOMENDAS], Encomenda copia_e[MAX_ENCOMENDAS], int ide) {
    int ide_aux, i, len;
    scanf("%d", &ide_aux);

    if (ide_aux >= ide) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide_aux);
    }
    else { 
        copia_encomenda(n_encomendas, copia_e, ide_aux);
        len = n_encomendas[ide_aux].variedade;
        printf("Encomenda %d\n", ide_aux);
        ordena_descricao(copia_e, 0, len-1, ide_aux);
        for(i = 0; i < len; i++) {
            if (copia_e[ide_aux].p[i].qtd != 0) {
                printf("* %s %d %d\n", copia_e[ide_aux].p[i].descricao, copia_e[ide_aux].p[i].preco, copia_e[ide_aux].p[i].qtd);
            }
        }   
    } 
}


/* Le n comandos do stdin e realiza as operacoes associadas a cada comando. */
int main() {
    char n, s[STRING];
    int idp = 0;
    int ide = 0;

    while(1) {
        scanf("%c", &n);
        switch(n) {
            case 'a':/* adiciona um novo produto ao sistema. */
                scanf("%s", s);
                idp = a(nprodutos, s, idp);
                break; 

            case 'q': /* adiciona stock a um produto existente no sistema. */
                scanf("%s", s);
                q(nprodutos, s, idp);
                break;
        
            case 'N': /* cria uma nova encomenda. */
                printf("Nova encomenda %d.\n", ide++);
                break;
        
            case 'A': /* adiciona um produto a uma encomenda. */
                scanf("%s", s);
                A(n_encomendas, nprodutos, s, ide, idp);
                break; 
        
            case 'r': /* remove stock a um produto existente. */
                scanf("%s", s);
                r(nprodutos, s , idp);
                break;
        
            case 'R': /* remove um produto de uma encomenda. */
                scanf("%s", s);
                R(n_encomendas, nprodutos, s, ide, idp); 
                break;
        
            case 'C': /* calcula o custo de uma encomenda. */
                C(n_encomendas, ide, idp);
                break;
        
            case 'p': /* altera o preco de um produto existente no sistema. */
                scanf("%s", s);
                p(nprodutos, s, idp, ide, n_encomendas);
                break;
        
            case 'E': /* retorna a descricao e a quantidade de um produto numa encomenda. */
                scanf("%s", s);
                E(n_encomendas, s, ide, idp, nprodutos);
                break;
        
            case 'm': /* retorna o identificador da encomenda em que um dado produto ocorre mais vezes. */
                m(n_encomendas, ide, idp);
                break;
        
            case 'l': /* lista todos os produtos existentes no sistema por ordem crescente de preco. */
                l(nprodutos, copia_p, idp);
                break;
        
            case 'L': /* lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */ 
                L(n_encomendas, copia_e, ide); 
                break;
        
            case 'x': /* termina o programa. */
                return 0;
                break;
            }
    }
} 
