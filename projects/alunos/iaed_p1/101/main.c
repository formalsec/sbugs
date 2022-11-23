#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define key_from_idp(A) (stock[A].descricao)
#define key(A) (key_from_idp(A.idp))
#define more(A, B) (strcmp(A, B) > 0)
#define less(A, B) (strcmp(key(A), key(B)) < 0)

/* Numero maximo de produtos */
#define MAX_PRODUTOS 10000
/* Numero maximo de encomendas */
#define MAX_ENCOMENDAS 500
/* Numero maximo de caracteres na descricao */
#define MAX_DESCRICAO 63

/* Estados do programa */
#define CORRER 0
#define TERMINAR 1

/* Peso maximo de uma encomenda */
#define PESO_MAXIMO 200

/* Estrutura que representa um produto no stock */
typedef struct {
    int idp;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
} Produto;

/* Estrutura que representa um produto numa encomenda */
typedef struct {
    int idp;
    int quantidade;
} Item;

/* Estrutura que representa uma encomenda */
typedef struct {
    Item itens[MAX_PRODUTOS];
    int tamanho;
    int peso;
} Encomenda;

/* Funcoes auxiliares */
void inserir_produto(Item itens[MAX_PRODUTOS], int left, int right);
int encontrar_produto(Item itens[MAX_PRODUTOS], int left, int right, int idp);

void mergesort(int a[], int left, int right);
void merge(int a[], int left, int middle, int right);

/* Funcoes dos comandos */
void comando_a();
void comando_q();
void comando_N();
void comando_A();
void comando_r();
void comando_R();
void comando_C();
void comando_p();
void comando_E();
void comando_m();
void comando_L();
void comando_l();

/* Array de produtos (Stock) */
Produto stock[MAX_PRODUTOS];
/* Array de indices de produtos */
int por_preco[MAX_PRODUTOS];
/* Array auxiliar a execucao do algoritmo de ordenacao */
int aux[MAX_PRODUTOS];
int num_produtos = 0;

/* Array de encomendas */
Encomenda encomendas[MAX_ENCOMENDAS];
int num_encomendas = 0;

int main() {
    int estado = CORRER;
    char comando;

    while (estado != TERMINAR) {
        comando = getchar();

        switch (comando) {
        case 'a':
            comando_a();
            break;
        case 'q':
            comando_q();
            break;
        case 'N':
            comando_N();
            break;
        case 'A':
            comando_A();
            break;
        case 'r':
            comando_r();
            break;
        case 'R':
            comando_R();
            break;
        case 'C':
            comando_C();
            break;
        case 'p':
            comando_p();
            break;
        case 'E':
            comando_E();
            break;
        case 'm':
            comando_m();
            break;
        case 'l':
            comando_l();
            break;
        case 'L':
            comando_L();
            break;
        case 'x':
            estado = TERMINAR;
            break;
        }
    }

    return 0;
}

/* Funcao auxiliar para inserir um produto numa encomenda de modo a ficar ordenado */
void inserir_produto(Item itens[MAX_PRODUTOS], int left, int right) {
    Item v = itens[right];
    int i = right - 1;
    while (i >= left && less(v, itens[i])) {
        itens[i + 1] = itens[i];
        i--;
    }
    itens[i + 1] = v;
}

/* Funcao auxiliar para encontrar um produto numa encomenda */
int encontrar_produto(Item itens[MAX_PRODUTOS], int left, int right, int idp) {
    if (right >= left) {
        int middle = left + (right - left) / 2;

        if (itens[middle].idp == idp)
            return middle;
        
        if (more(key(itens[middle]), key_from_idp(idp)))
            return encontrar_produto(itens, left, middle - 1, idp);

        return encontrar_produto(itens, middle + 1, right, idp);
    }

    return -1;
}

/* Funcao auxiliar para ordenar uma array de indices por ordem crescente do preco */
void mergesort(int a[], int left, int right) {
    int middle = (right + left) / 2;
    if (right <= left) return;

    mergesort(a, left, middle);
    mergesort(a, middle + 1, right);
    merge(a, left, middle, right);
}

/* Funcao auxiliar para juntar duas arrays de indices por ordem crescente de preco */
void merge(int a[], int left, int middle, int right) {
    int i, j, k;
    for (i = middle + 1; i > left; i--) 
        aux[i - 1] = a[i - 1];
    for (j = middle; j < right; j++)
        aux[right + middle - j] = a[j + 1];
    for (k = left; k <= right; k++)
        if (stock[aux[j]].preco < stock[aux[i]].preco
            || (stock[aux[j]].preco == stock[aux[i]].preco && aux[j] < aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}

/* Adiciona um novo produto ao sistema */
void comando_a() {
    scanf(" %[^:]:%d:%d:%d", 
        stock[num_produtos].descricao, 
        &stock[num_produtos].preco,
        &stock[num_produtos].peso,
        &stock[num_produtos].quantidade
    );
    stock[num_produtos].idp = num_produtos;
    por_preco[num_produtos] = num_produtos;

    printf("Novo produto %d.\n", num_produtos);
    num_produtos++;
}

/* Adiciona stock a um produto existente no sistema */
void comando_q() {
    int idp, quantidade;
    scanf("%d:%d", &idp, &quantidade);

    if (idp >= num_produtos) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    } else {
        stock[idp].quantidade += quantidade;
    }
}

/* Cria uma nova encomenda */
void comando_N() {
    encomendas[num_encomendas].tamanho = 0;
    encomendas[num_encomendas].peso = 0;
    printf("Nova encomenda %d.\n", num_encomendas);
    num_encomendas++;
}

/* Adiciona um produto a uma encomenda */
void comando_A() {
    int ide, idp, quantidade;
    scanf("%d:%d:%d", &ide, &idp, &quantidade);

    if (ide >= num_encomendas) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    } else if (idp >= num_produtos) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else if (quantidade > stock[idp].quantidade) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    } else if (quantidade * stock[idp].peso + encomendas[ide].peso > PESO_MAXIMO) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    } else {
        /* Verificar se o produto se encontra na encomenda */
        int procurar = encontrar_produto(encomendas[ide].itens, 0, encomendas[ide].tamanho - 1, idp);
        stock[idp].quantidade -= quantidade;
        encomendas[ide].peso += quantidade * stock[idp].peso;
        
        if (procurar != -1) {
            /* Adiciona nova quantidade ao produto na encomenda */
            encomendas[ide].itens[procurar].quantidade += quantidade;
        } else {
            /* Adiciona um novo produto a encomenda */
            encomendas[ide].itens[encomendas[ide].tamanho].idp = idp;
            encomendas[ide].itens[encomendas[ide].tamanho].quantidade = quantidade;
            inserir_produto(encomendas[ide].itens, 0, encomendas[ide].tamanho);
            encomendas[ide].tamanho++;
        }
    }
}

/* Remove stock a um produto */
void comando_r() {
    int idp, quantidade;
    scanf("%d:%d", &idp, &quantidade);

    if (idp >= num_produtos) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    } else if (stock[idp].quantidade - quantidade < 0) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    } else {
        stock[idp].quantidade -= quantidade;
    }
}

/* Remove um produto de uma encomenda */
void comando_R() {
    int ide, idp;
    scanf("%d:%d", &ide, &idp);

    if (ide >= num_encomendas) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    } else if (idp >= num_produtos) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    } else {
        /* Verificar se o produto se encontra na encomenda */
        int pos = encontrar_produto(encomendas[ide].itens, 0, encomendas[ide].tamanho - 1, idp);
        if (pos != -1) {
            int i;
            encomendas[ide].peso -= encomendas[ide].itens[pos].quantidade * stock[idp].peso;
            stock[idp].quantidade += encomendas[ide].itens[pos].quantidade;
            encomendas[ide].itens[pos].quantidade = 0; 
            for (i = pos; i < encomendas[ide].tamanho - 1; i++) {
                encomendas[ide].itens[i] = encomendas[ide].itens[i + 1];
            }
            encomendas[ide].tamanho--;
        }
    }
}

/* Calcula o custo de uma encomenda */
void comando_C() {
    int ide;
    scanf("%d", &ide);

    if (ide >= num_encomendas) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    } else {
        int custo = 0;
        int i;
        int tamanho = encomendas[ide].tamanho;

        for (i = 0; i < tamanho; i++) {
            custo += stock[encomendas[ide].itens[i].idp].preco * encomendas[ide].itens[i].quantidade;
        }

        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

/* Altera o pre?o de um produto existente no sistema */
void comando_p() {
    int idp, preco;
    scanf("%d:%d", &idp, &preco);

    if (idp >= num_produtos) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    } else {
        stock[idp].preco = preco;
    }
}

/* 	Devolve a descricao e a quantidade de um produto numa dada encomenda */
void comando_E() {
    int ide, idp;
    scanf("%d:%d", &ide, &idp);

    if (ide >= num_encomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    } else if (idp >= num_produtos) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    } else {
        int quantidade = 0;
        int indice = encontrar_produto(encomendas[ide].itens, 0, encomendas[ide].tamanho, idp);
        if (indice != -1) {
            quantidade += encomendas[ide].itens[indice].quantidade;
        }
        printf("%s %d.\n", stock[idp].descricao, quantidade);
    }
}

/* Devolve o identificador da encomenda em que um dado produto ocorre mais vezes */
void comando_m() {
    int idp;
    scanf("%d", &idp);

    if (idp >= num_produtos) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    } else if (num_encomendas > 0) {
        int quantidade = 0;
        int ide = 0;
        int i;

        for (i = 0; i < num_encomendas; i++) {
            int item = encontrar_produto(encomendas[i].itens, 0, encomendas[i].tamanho - 1, idp);
            if (item != -1 && encomendas[i].itens[item].quantidade > quantidade) {
                quantidade = encomendas[i].itens[item].quantidade;
                ide = i;
            }
        }
        
        if (quantidade > 0)
            printf("Maximo produto %d %d %d.\n", idp, ide, quantidade);
    }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco */
void comando_l() {
    int i;

    mergesort(por_preco, 0, num_produtos - 1);
    printf("Produtos\n");

    for (i = 0; i < num_produtos; i++) {
        int idp = por_preco[i];
        printf("* %s %d %d\n", stock[idp].descricao, stock[idp].preco, stock[idp].quantidade);
    }
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void comando_L() {
    int ide;
    scanf("%d", &ide);

    if (ide >= num_encomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    } else {
        int i;
        printf("Encomenda %d\n", ide);

        for (i = 0; i < encomendas[ide].tamanho; i++) {
            int idp = encomendas[ide].itens[i].idp;
            int quantidade = encomendas[ide].itens[i].quantidade;
            printf("* %s %d %d\n", stock[idp].descricao, stock[idp].preco, quantidade);
        }
    }
}
