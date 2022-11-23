#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Definicao da quantidade maxima de produtos, encomendas, peso e caracteres em uma string. */
#define MAX_STRING          63
#define MAX_PRODUTOS        10000
#define MAX_ENCOMENDAS      500
#define MAX_PESO_ENCOMENDA  200
/* Variaveis de estado para definir metodo de ordenacao. */
#define CMP_PRECO           0
#define CMP_DESC            1
/* Funcao auxiliar que troca o conteudo de dois produtos. */
#define exch(A, B) {Produto t = A; A = B; B = t;}

/*
    --------------------- STRUCTS ---------------------
*/

/* Estrutura que simboliza um produto. */
typedef struct {
    int idp;
    char desc[MAX_STRING];
    int preco;
    int peso;
    int qtd;
} Produto;

/* Estrutura que contem a quantidade de produtos em uma encomenda e uma lista com diversos produtos. */
typedef struct {
    int qtd_prod;
    Produto produtos[MAX_PRODUTOS];
} Encomenda;

/*
    ----------------- VARIAVEIS GLOBAIS -----------------
*/

/* Listas que controlam os produtos existentes no sistema e no conjunto de encomendas. */
Produto sistema[MAX_PRODUTOS];
Encomenda encomendas[MAX_ENCOMENDAS];

/* Ambos o id_prod_atual quanto o id_encomendas controlam o ultimo index inserido nas respetivas listas sistema e encomendas. */
int idp_atual = 0, ide_atual = 0;
/* Variavel que guarda o metodo a ser usado na ordenacao das listas. */
int cmp = CMP_PRECO;

/*
    ---------------- FUNCOES AUXILIARES ----------------
*/

/* Verifica a existencia de uma encomenda. */
int existe_encomenda(int id) {
    return (id < ide_atual);
}

/* Verifica a existencia do produto em uma lista generica de produtos. */
int existe_produto_sistema(int id) {
    return (id < idp_atual);
}

/* Verifica a existencia do produto em uma lista na encomenda e devolve sua posicao. */
int existe_produto_encomenda(int ide, int id) {
    int i, j = encomendas[ide].qtd_prod;
    /* Verifica em toda a lista de produtos se existe algum com o mesmo idp. */
    for (i = 0; i < j; i++)
        if (encomendas[ide].produtos[i].idp == id)
            return i;
    /*Retorna -1 caso nenhum produto seja encontrado. */
    return -1;
}


/* Verifica se o peso da encomenda nao ultrapassa o maximo peso estipulado. */
int verifica_peso_encomenda(Encomenda encomenda, int peso, int qtd) {
    int i, res = 0, j = encomenda.qtd_prod;

    for (i = 0; i < j; i++)
        res += encomenda.produtos[i].peso * encomenda.produtos[i].qtd;

    return (res + (peso * qtd) <= MAX_PESO_ENCOMENDA);
}

/* Metodo auxiliar a ordenacao que define a chave de ordenacao (preco / desc) a partir de variaveis de estado. */
int cmp_produtos(Produto a, Produto b) {
    /* 
    Caso os precos sejam iguais, a ordenacao passa a ser feita pelo idp.
    Caso nao seja feita a ordenacao por preco, sera feita pela descricao. 
    A funcao strcmp compara duas sequencias de char e retorna um valor negativo 
    caso o primeiro parametro seja menor que o segundo. 
    */
    if (cmp == CMP_PRECO)
        return (a.preco == b.preco ? (a.idp < b.idp) : (a.preco < b.preco));
    return (strcmp(a.desc, b.desc) < 0); 
}

/* Metodo de ordenacao onde a chave eh alterada por variaveis de estado. */
void quicksort(Produto a[], int l, int r) {
    Produto v;
    int i, j;
    if (r <= l) return;

    i = l - 1;
    j = r;
    /* Pivot : ultimo elemento da lista, onde separa os menores a esquerda e os maiores a direita. */
    v = a[r]; 
    /* Rearranja os elementos do vetor de acordo com o criterio de ordenacao. */
    while (i < j) {
        while (cmp_produtos(a[++i], v));
        while (cmp_produtos(v, a[--j]))
            if (j == l)
                break;

        /* Faz a troca conforme os indices finais. */
        if (i < j)
            exch(a[i], a[j]);
    }
    /* Faz a troca deixando o pivot na sua posicao final. */
    exch(a[i], a[r]);

    /* Aplica??o recursiva do algoritmo aos dois subconjuntos de dados resultantes. */
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}

/*
    ------------------ FUNCOES SECUNDARIAS ------------------
*/

/* Adiciona um novo produto no sistema. */
void adiciona_produto(Produto prod) {
    prod.idp = idp_atual;
    sistema[idp_atual] = prod;
    printf("Novo produto %d.\n", idp_atual++);
}

/* Adiciona mais produtos aos ja existentes no sistema. */
void adiciona_stock(int idp, int qtd) {
    if (existe_produto_sistema(idp))
        sistema[idp].qtd += qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* Remove uma quantidade especifica de produtos em stock. */
void remove_stock(int idp, int qtd) {
    if (!existe_produto_sistema(idp))
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (sistema[idp].qtd < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        sistema[idp].qtd -= qtd;
}

/* Verifica a existencia de um produto no sistema e o adiciona na encomenda especificada. */
void adiciona_produto_encomenda(int ide, int idp, int qtd) {
    int id_atual, i;
    if (!existe_encomenda(ide))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (!existe_produto_sistema(idp))
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (sistema[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (!verifica_peso_encomenda(encomendas[ide], sistema[idp].peso, qtd)) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else {
        /* Verifica a existencia do produto na encomenda e devolve o seu indice. */
        id_atual = encomendas[ide].qtd_prod;
        i = existe_produto_encomenda(ide, idp);
        remove_stock(idp, qtd);
        /*
        Caso o produto nao exista na encomenda, adiciona o produto do sistema as encomendas 
        e aumenta a quantidade de produtos na encomenda.
        Caso ja exista, apenas adicionamos a quantidade exigida.
        */
        if (i == -1) {
            encomendas[ide].produtos[id_atual] = sistema[idp];
            encomendas[ide].produtos[id_atual].qtd = qtd;
            encomendas[ide].qtd_prod++;
        }
        else
            encomendas[ide].produtos[i].qtd += qtd;
    }
}

/* Remove um produto de uma encomenda. */
void remove_produto(int ide, int idp) {
    int i;
    if (!existe_encomenda(ide))
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (!existe_produto_sistema(idp))
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else {
        /* Apenas remove o produto caso ele exista na encomenda. */
        i = existe_produto_encomenda(ide, idp);
        if (i > -1) {
            /* Adiciona ao sistema a quantidade do produto existente na encomenda, antes de ser removido. */
            sistema[idp].qtd += encomendas[ide].produtos[i].qtd;
            encomendas[ide].produtos[i].qtd = 0;
        }
    }
}

/* Calcula o custo de uma encomenda. */
void custo_encomenda(int ide) {
    int i, res = 0;
    if (!existe_encomenda(ide))
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        /* Soma os precos calculados para cada produto dentro da encomenda. */
        for (i = 0; i < encomendas[ide].qtd_prod; i++)
            res += encomendas[ide].produtos[i].preco * encomendas[ide].produtos[i].qtd;
        printf("Custo da encomenda %d %d.\n", ide, res);
    }
}

/* Altera o preco de um produto existente no sistema. */
void altera_preco_produto(int idp, int preco) {
    int i, j;
    if (!existe_produto_sistema(idp))
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        /* Altera o preco do produto no sistema e em todas as encomendas onde o produto existe. */
        sistema[idp].preco = preco;
        for (i = 0; i < ide_atual; i++) {
            j = existe_produto_encomenda(i, idp);
            if (j > -1)
                encomendas[i].produtos[j].preco = preco;
        }
    }
}

/* Lista a descricao e a quantidade de um produto numa encomenda. */
void lista_produto_encomenda(int ide, int idp) {
    int qtd = 0, i;
    if (!existe_encomenda(ide))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (!existe_produto_sistema(idp))
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        /* Atualiza a variavel qtd com a quantidade do produto na encomenda caso o mesmo exista. */
        i = existe_produto_encomenda(ide, idp);
        if (i > -1)
            qtd = encomendas[ide].produtos[i].qtd;
        printf("%s %d.\n", sistema[idp].desc, qtd);
    }
}

/* Lista a encomenda em que determinado produto eh mais encomendado. */
void lista_maximo_produto(int idp) {
    Produto prod;
    int i, j, ide_menor, maior_quantidade = -1;
    if (!existe_produto_sistema(idp))
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else {
        for (i = 0; i < ide_atual; i++)
            if (existe_encomenda(i)) {                  /* Caso a encomenda exista, verifica a existencia do produto na encomenda. */
                j = existe_produto_encomenda(i, idp);
                if (j > -1) {                           /* Compara a maior quantidade ja registada com o produto verificado atualmente. */
                    prod = encomendas[i].produtos[j];
                    if (maior_quantidade < prod.qtd) {  /* Atualiza as variaveis. */
                        maior_quantidade = prod.qtd;
                        ide_menor = i;
                    }
                }
            }
        /* Apenas faz a listagem caso haja ao menos um produto dentro da encomenda. */
        if (maior_quantidade > 0)
            printf("Maximo produto %d %d %d.\n", idp, ide_menor, maior_quantidade);
    }
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco. */
void lista_produtos_sistema() {
    int i;
    Produto aux[MAX_PRODUTOS];

    /* Cria uma lista auxiliar de copia para nao alterar os indices do sistema de produtos. */
    for (i = 0; i < idp_atual; i++)
        aux[i] = sistema[i];

    /* Define qual eh o metodo de ordenacao que o quicksort (funcao de ordenacao) devera realizar. */
    cmp = CMP_PRECO;
    quicksort(aux, 0, idp_atual - 1);

    /* Percorre a lista auxiliar imprimindo seus dados. */
    printf("Produtos\n");
    for (i = 0; i < idp_atual; i++)
        printf("* %s %d %d\n", aux[i].desc, aux[i].preco, aux[i].qtd);
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica da descricao. */
void lista_encomenda(int ide) {
    int i, j;

    if (!existe_encomenda(ide))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        j = encomendas[ide].qtd_prod;
        /*
        Desnecessaria a criacao de uma lista auxiliar de copia para usar no quicksort (funcao de ordenacao)
        uma vez que o indice do vetor dos produtos da encomenda nao esta relacionado com os indices dos produtos da mesma.
        */

        /* Define metodo de ordenacao que o quicksort (funcao de ordenacao) devera realizar. */
        cmp = CMP_DESC;
        quicksort(encomendas[ide].produtos, 0, j - 1);

        /* Percorre a lista auxiliar imprimindo seus dados apenas caso a quantidade do produto seja maior que zero. */
        printf("Encomenda %d\n", ide);
        for (i = 0; i < j; i++)
            if (encomendas[ide].produtos[i].qtd > 0)
                printf("* %s %d %d\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].preco, encomendas[ide].produtos[i].qtd);
    }
}

/*
    ------------------ FUNCAO PRINCIPAL ------------------
*/

/* Le uma sequencia de dados introduzidos pelo usuario. */
int main() {
    /* Variaveis auxiliares na leitura. */
    Produto prod;
    int ide, idp, qtd, preco;
    char opcao;

    /* 
    Verifica se o input recebido pelo stdin nao eh
    fim de arquivo ou o termo de saida 'x' e realiza 
    uma funcao conforme os dados de entrada.
    */
    while ((scanf("%c", &opcao) != EOF) && (opcao != 'x')) {
        switch (opcao) {
        case 'a':
            scanf(" %[^:]:%d:%d:%d", prod.desc, &prod.preco, &prod.peso, &prod.qtd);
            adiciona_produto(prod);
            break;
        case 'q':
            scanf("%d:%d", &idp, &qtd);
            adiciona_stock(idp, qtd);
            break;
        case 'N':
            printf("Nova encomenda %d.\n", ide_atual++);
            break;
        case 'A':
            scanf("%d:%d:%d", &ide, &idp, &qtd);
            adiciona_produto_encomenda(ide, idp, qtd);
            break;
        case 'r':
            scanf("%d:%d", &idp, &qtd);
            remove_stock(idp, qtd);
            break;
        case 'R':
            scanf("%d:%d", &ide, &idp);
            remove_produto(ide, idp);
            break;
        case 'C':
            scanf("%d", &ide);
            custo_encomenda(ide);
            break;
        case 'p':
            scanf("%d:%d", &idp, &preco);
            altera_preco_produto(idp, preco);
            break;
        case 'E':
            scanf("%d:%d", &ide, &idp);
            lista_produto_encomenda(ide, idp);
            break;
        case 'm':
            scanf("%d", &idp);
            lista_maximo_produto(idp);
            break;
        case 'l':
            lista_produtos_sistema();
            break;
        case 'L':
            scanf("%d", &ide);
            lista_encomenda(ide);
            break;
        }

        scanf("%c", &opcao);
    }

    return 0;
}
