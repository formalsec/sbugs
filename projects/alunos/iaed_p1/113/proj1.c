#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_DESC 63
#define MAX_PROD 10000
#define MAX_ENC  500
#define MAX_PESO 200
#define DIM3     2
#define VAZIO    -1

typedef struct produto{
    char desc[MAX_DESC];
    int preco;
    int peso;
    int stock;
} produto;

/*contador de produtos, vai sendo incrementado a medida que novos produtos vao sendo adicionados*/
int conta_p = VAZIO;

/*contador de encomendas, vai sendo incrementado a medida que novas encomendas vao sendo adicionadas*/
int conta_e = VAZIO;

/*vetor dos produtos no sistema*/
produto produtos[MAX_PROD];

/*array 3-dimensional das encomendas
[[[idp, qtd], [idp, qtd]...], [[idp, qtd]...]...]*/
int encomendas[MAX_ENC][MAX_PESO][DIM3];

/*inicializa o array das encomendas*/
void inicializaEncomendas (){
    int i, j;
    for (i = 0; i < MAX_ENC; i++)
        for (j = 0; j < MAX_PESO; j++)
            encomendas[i][j][0] = VAZIO;
}

/*vetor auxiliar para o mergeSort*/
produto aux[MAX_PROD];

void mergeDescricao (produto vetor[], int left, int m, int right){
    int i, j, k;
    for (i = m + 1; i > left; i--)
        aux[i - 1] = vetor[i - 1];
    for (j = m; j < right; j++)
        aux[right + m - j] = vetor[j + 1];
    for (k = left; k <= right; k++)
        if (strcmp(aux[j].desc, aux[i].desc) < 0 || i > m)
            vetor[k] = aux[j--];
        else
            vetor[k] = aux[i++];
}

/*mergeSort que ordena produtos por ordem alfabetica da descricao*/
void mergeSortDescricao (produto vetor[], int left, int right){
    int m = (left + right) / 2;
    if (right <= left)
        return;
    mergeSortDescricao(vetor, left, m);
    mergeSortDescricao(vetor, m + 1, right);
    mergeDescricao(vetor, left, m, right);
}

void mergePreco (produto vetor[], int left, int m, int right){
    int i, j, k;
    for (i = m + 1; i > left; i--)
        aux[i - 1] = vetor[i - 1];
    for (j = m; j < right; j++)
        aux[right + m - j] = vetor[j + 1];
    for (k = left; k <= right; k++)
        if (aux[j].preco < aux[i].preco || i > m)
            vetor[k] = aux[j--];
        else
            vetor[k] = aux[i++];
}

/*mergeSort que ordena produtos com base no seu preco*/
void mergeSortPreco (produto vetor[], int left, int right){
    int m = (left + right) / 2;
    if (right <= left)
        return;
    mergeSortPreco(vetor, left, m);
    mergeSortPreco(vetor, m + 1, right);
    mergePreco(vetor, left, m, right);
}

/*adiciona um novo produto ao sistema*/
void adicionaProdutoSistema (){
    char desc[MAX_DESC];
    int preco, peso, qtd;
    scanf(" %[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
    conta_p++;
    strcpy(produtos[conta_p].desc, desc);
    produtos[conta_p].preco = preco;
    produtos[conta_p].peso = peso;
    produtos[conta_p].stock = qtd;
    printf("Novo produto %d.\n", conta_p);
}

/*adiciona stock a um produto existente no sistema*/
void adicionaStock (){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if ((idp > conta_p) || idp < 0){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }
    produtos[idp].stock += qtd;
}

/*cria uma nova encomenda*/
void criaEncomenda (){
    conta_e++;
    printf("Nova encomenda %d.\n", conta_e);
}

/*remove stock a um produto existente*/
void removeStock (){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if (idp > conta_p || idp < 0){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }
    else if (produtos[idp].stock < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }
    produtos[idp].stock -= qtd;
}

/*funcao auxiliar para calcular o peso de uma encomenda*/
int calculaPeso (int ide){
    int i, peso = 0;
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] != VAZIO)
            peso += produtos[encomendas[ide][i][0]].peso * encomendas[ide][i][1];
    return peso;
}

/*adiciona um produto a uma encomenda*/
void adicionaProdutoEncomenda (){
    int ide, idp, qtd, i;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (idp > conta_p || idp < 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    else if (ide > conta_e || ide < 0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (produtos[idp].stock < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    else if (calculaPeso(ide) + produtos[idp].peso * qtd > MAX_PESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }
    /*caso o produto estiver na encomenda*/
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] == idp){
            encomendas[ide][i][1] += qtd;
            produtos[idp].stock -= qtd;
            return; 
        }
    /*caso o produto nao estiver na encomenda*/
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] == VAZIO){
            encomendas[ide][i][0] = idp;
            encomendas[ide][i][1] = qtd;
            produtos[idp].stock -= qtd;
            return;
        }
}

/*remove um produto de uma encomenda*/
void removeProdutoEncomenda (){
    int ide, idp, i;
    scanf("%d:%d", &ide, &idp);
    if (ide > conta_e || ide < 0){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }
    else if (idp > conta_p || idp < 0){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] == idp){
            encomendas[ide][i][0] = VAZIO;
            produtos[idp].stock += encomendas[ide][i][1];
            return; 
        }
}

/*calcula o custo de uma encomenda*/
void calculaCusto (){
    int ide, i; 
    long int custo = 0;
    scanf("%d", &ide);
    if (ide > conta_e || ide < 0){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] != VAZIO)
            custo += produtos[encomendas[ide][i][0]].preco * encomendas[ide][i][1];
    printf("Custo da encomenda %d %ld.\n", ide, custo);
}

/*altera o preco de um produto existentes no sistema*/
void alteraPreco (){
    int idp, novo_preco;
    scanf("%d:%d", &idp, &novo_preco);
    if (idp > conta_p || idp < 0){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }
    produtos[idp].preco = novo_preco;
}

/*lista a descricao e a quantidade de um produto numa encomenda*/
void listaProdutoNaEncomenda (){
    int ide, idp, i;
    scanf("%d:%d", &ide, &idp);
    if (ide > conta_e || ide < 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    else if (idp > conta_p || idp < 0){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }
    /*caso o produto estiver na encomenda*/
    for (i = 0; i < MAX_PESO; i++)
        if (encomendas[ide][i][0] == idp){
            printf("%s %d.\n", produtos[idp].desc, encomendas[ide][i][1]);
            return;
        }
    /*caso o produto nao estiver na encomenda*/
    printf("%s %d.\n", produtos[idp].desc, 0);
}

/*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void listaEncomendaComMaiorFrequencia (){
    int idp, i, j, maior_qtd = -1, enc_a_listar, encontrou_produto = 0;
    if (conta_e < 0)
        return;
    scanf("%d", &idp);
    if (idp > conta_p || idp < 0){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }
    for (i = 0; i < MAX_ENC; i++)
        for (j = 0; j < MAX_PESO; j++)
            if (encomendas[i][j][0] == idp && encomendas[i][j][1] > maior_qtd){
                maior_qtd = encomendas[i][j][1];
                enc_a_listar = i;
                encontrou_produto = 1;
            }
    /*nao faz nada se o produto nao estiver na encomenda*/
    if (encontrou_produto == 1)
        printf("Maximo produto %d %d %d.\n", idp, enc_a_listar, maior_qtd);
}

/*lista todos os produtos existentes no sistema por ordem crescente de preco*/
void listaProdutos (){
    produto produtos_a_ordenar[MAX_PROD];
    int i;
    printf("Produtos\n");
    for (i = 0; i <= conta_p; i++)
        produtos_a_ordenar[i] = produtos[i];
    mergeSortPreco(produtos_a_ordenar, 0, conta_p);
    for (i = 0; i <= conta_p; i++)
        printf("* %s %d %d\n", produtos_a_ordenar[i].desc, produtos_a_ordenar[i].preco, produtos_a_ordenar[i].stock);
}

/*lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
void listaEncomenda (){
    int ide, i = 0, j = 0;
    produto produtos_a_ordenar[MAX_PESO];
    scanf("%d", &ide);
    if (ide > conta_e || ide < 0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    printf("Encomenda %d\n", ide);
    while (i < MAX_PESO){
        if (encomendas[ide][i][0] != VAZIO){
            produtos_a_ordenar[j] = produtos[encomendas[ide][i][0]];
            produtos_a_ordenar[j].stock = encomendas[ide][i][1];
            j++;
        }
        i++;
    }
    mergeSortDescricao(produtos_a_ordenar, 0, j - 1);
    for (i = 0; i < j; i++)
        printf("* %s %d %d\n", produtos_a_ordenar[i].desc, produtos_a_ordenar[i].preco, produtos_a_ordenar[i].stock);
} 

int main (){
    char command;
    inicializaEncomendas();
    while ((command = getchar()) != 'x'){
        switch (command){
        case 'a':
            adicionaProdutoSistema();
            break;
        case 'q':
            adicionaStock();
            break;
        case 'N':
            criaEncomenda();
            break;
        case 'A':
            adicionaProdutoEncomenda();
            break;
        case 'r':
            removeStock();
            break;
        case 'R':
            removeProdutoEncomenda();
            break;
        case 'C':
            calculaCusto();
            break;
        case 'p':
            alteraPreco();
            break;
        case 'E':
            listaProdutoNaEncomenda();
            break;
        case 'm':
            listaEncomendaComMaiorFrequencia();
            break;
        case 'l':
            listaProdutos();
            break;
        case 'L':
            listaEncomenda();
            break;
        }
    }
    return 0;
}