#include <stdio.h>
#include <string.h>

/* Numero maximo de produtos no sistema. */
#define MAXPRODUTOS 10000
/* Tamanho maximo de uma descricao de um produto. */
#define MAXDESC 63
/* Numero maximo de encomendas no sistema. */
#define MAXENCOMENDAS 500
/* Peso maximo de uma encomenda. */
#define MAXPESO 200
/* Funcao auxiliar que troca o conteudo de dois produtos. */
#define exch(A, B) { Produto t = A; A = B; B = t; }

typedef struct produto {
    char desc[MAXDESC];
    int idp, preco, peso, qtd;
}Produto;

typedef struct encomenda {
    /* Variavel distintos mantem o controle dos tipos diferentes de produtos na encomenda. */
    int distintos;
    Produto produtos[MAXPESO];
}Encomenda;

/* Variaveis que sinaliza a posicao de um produto e uma encomenda respectivamente no sistema. */
int idpGlobal = 0, ideGlobal = 0;

/* Criacao dos vetores onde todos os produtos e encomendas serao guardados. */
Produto sistema[MAXPRODUTOS], ordenados[MAXPRODUTOS];
Encomenda encomendas[MAXENCOMENDAS];

/* Funcao que verifica se um produto com id "idp" existe na lista dada. */
int existeProduto(Produto lista[], int idp, int limite){
    int i;
    for (i = 0; i < limite; i++){
        /* Se o "idp" de um produto da lista coincide com o idp dado, retorna 1 (verdadeiro).*/
        if (lista[i].idp == idp) return 1;
    }
    /* Se o idp nao eh achado na lista, retorna 0 (falso). */
    return 0;
}

/* Funcao que verifica se o ide dado eh menor que o ideGlobal, e se sim, entao retorna 1 (true) pois ja foi criado. Se nao, retorna 0 (falso). */
int existeEncomenda(int ide){ return ideGlobal > ide;}

/* Calcula o peso de uma encomenda dada pelo ide. */
int peso(int ide){
    int i, peso = 0;
    /* Itera sobre todos os diferentes produtos e adiciona o peso de cada unidade (peso vezes quantidade de cada produto na encomenda) na variavel "peso". */
    for (i = 0; i < encomendas[ide].distintos; i++){
        peso += encomendas[ide].produtos[i].peso * encomendas[ide].produtos[i].qtd;
    }
    return peso;
}

/* Funcao que encontra a posicao de um produto no vetor de produtos de uma encomenda. */
int posicao(int ide, int idp){
    int i;
    /* Itera sobre todos os diferentes produtos e procura por um produto qual idp eh compativel com o idp dado. */
    for (i = 0; i < encomendas[ide].distintos; i++){
        /* Se o idp do produto eh compativel com o idp dado, a funcao retorna i, que eh a posicao no vetor em que o produto esta. */
        if (encomendas[ide].produtos[i].idp == idp) return i;
    }
    /* Se o produto nao for encontrado, retorna -1. */
    return -1;
}

/* Funcao que recebe compara dois produtos relativo ao tipo da funcao (preco para o caso l ou descricao para o caso L) */
int less(Produto a, Produto b, int tipo){
    /* Tipo 1 representa o caso l. */
    if (tipo == 1){
        /* Compara por idp se o preco eh igual. Retorna a comparacao de se o preco/idp de 'a' eh menor do que de 'b'. */
        if (a.preco == b. preco) return a.idp < b.idp;
        return a.preco < b.preco;
    }
    /* O unico outro tipo (tipo 2) representa o caso L. Compara a descricao de a e b e retorna se a descricao de 'a' comeca com uma letra antes da descricao do produto 'b' */
    else return strcmp(a.desc, b.desc) < 0;
}


/* Algaritmo de ordenacao quick sort. */
void quickSort(Produto lista[], int l, int r, int tipo){
    int i = l - 1, j = r;
    /* Criacao do produto pivot v. */
    Produto v = lista[r];
    /* Para o algoritmo se ja tiver percorrido a lista. */
    if (r <= l) return;
    /* Percorre a lista enquanto o iterador da esquerda 'i' for menor que o iterador da direita 'j'. */
    while (i < j){
        /* Enquanto (a[i] < v) avanca com o i para a direita. */
        while (less(lista[++i], v, tipo));
        /* Enquanto (v < a[j]) avanca com o j para a esquerda. O 'if' protege do caso que o elemento onde se faz a particao esta na primeira posicao da lista. */
        while (less(v, lista[--j], tipo)) if (j == l) break;
        /* Faz a troca se estiver fora de ordem. */
        if (i < j) exch(lista[i], lista[j]);
    }
    /* Coloca o pivot na posicao i. */
    exch(lista[i], lista[r]);
    /* Separa a lista em duas partes em volta do pivot e faz quick sort nas duas metades recursivamente. */
    quickSort(lista, l, i - 1, tipo);
    quickSort(lista, i + 1, r, tipo);
}

/* Funcao que cria e adiciona um produto ao sistema. */
void casoa(Produto p){
    p.idp = idpGlobal;
    /* incrementa o idpGlobal de acordo com a adicao de um produto. */
    sistema[idpGlobal++] = p;
    printf("Novo produto %d.\n", p.idp);
}

/* Funcao que adiciona stock a um produto existente. */
void casoq(int idp, int qtd){
    if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else sistema[idp].qtd += qtd;
}

/* Funcao que cria e adiciona uma encomenda ao sistema. */
void casoN(){
    Encomenda e;
    /* Distintos eh inicializado como zero, ja que nao ha produtos na encomenda. */
    e.distintos = 0;
    encomendas[ideGlobal] = e;
    /* O ide da encomenda nova eh printado e incrementado logo apos. */
    printf("Nova encomenda %d.\n", ideGlobal++);
}

/* Funcao que adiciona um produto a uma encomenda. */
void casoA(int ide, int idp, int qtd){
    if (!existeEncomenda(ide)) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (sistema[idp].qtd < qtd) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (peso(ide) + (sistema[idp].peso * qtd) > MAXPESO) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else {
        /* Remove a quantidade do produto do sistema. */
        sistema[idp].qtd -= qtd;
        /* So adiciona a quantidade se o produto ja existir na encomenda. */
        if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos)) encomendas[ide].produtos[posicao(ide, idp)].qtd += qtd;
        /* Se a encomenda nao tiver o produto, cria um novo produto na encomenda e aumenta o numero de produtos distintos na encomenda. */
        else {
            encomendas[ide].produtos[encomendas[ide].distintos] = sistema[idp];
            encomendas[ide].produtos[encomendas[ide].distintos++].qtd = qtd;
        }
    }
}

/* Funcao que remove stock de um produto do sistema. */
void casor(int idp, int qtd){
    if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (sistema[idp].qtd < qtd) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else sistema[idp].qtd -= qtd;
}

/* Funcao que remove um produto de uma encomenda. */
void casoR(int ide, int idp){
    if (!existeEncomenda(ide)) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos)){
            /* Devolve a quantidade da encomenda ao sistema e remove o produto por fazer sua quantidade ser 0. */
            sistema[idp].qtd += encomendas[ide].produtos[posicao(ide, idp)].qtd;
            encomendas[ide].produtos[posicao(ide, idp)].qtd = 0;
    }
}

/* Funcao que calcula o custo total de uma encomenda. */
void casoC(int ide){
    if (!existeEncomenda(ide)) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else {
        int preco = 0, i;
        for (i = 0; i < encomendas[ide].distintos; i++){
            /* Multiplica o preco pela quantidade de cada produto e soma a variavel preco que sera retornada. */
            preco += encomendas[ide].produtos[i].qtd * encomendas[ide].produtos[i].preco;
        }
        printf("Custo da encomenda %d %d.\n", ide, preco);
    }
}
         
/* Funcao que altera o preco de um produto. */
void casop(int idp, int preco){
    if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else {
        int i;
        /* Altera o preco do produto no sistema e en=m todas as encomendas que esta presente. */
        sistema[idp].preco = preco;
        for (i = 0; i < ideGlobal; i++) encomendas[i].produtos[posicao(i, idp)].preco = preco;
    }
}

/* Funcao que lista os produtos de uma encomenda, com descricao e quantidade. */
void casoE(int ide, int idp){
    if (!existeEncomenda(ide)) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else{
        if (existeProduto(encomendas[ide].produtos, idp, encomendas[ide].distintos)) printf("%s %d.\n", sistema[idp].desc, encomendas[ide].produtos[posicao(ide, idp)].qtd);
        else printf("%s %d.\n", sistema[idp].desc, 0);
    }
}

/* Funcao que lista a encomenda em que o produto identificado por 'idp' ocorre mais vezes. */
void casom(int idp){
    if (!existeProduto(sistema, idp, idpGlobal)) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else {
        int i, maxID, numero = 0;
        for (i = 0; i < ideGlobal; i++){
            if (existeEncomenda(i)){
                if (existeProduto(encomendas[i].produtos, idp, encomendas[i].distintos)){
                    if (encomendas[i].produtos[posicao(i, idp)].qtd > numero) numero = encomendas[i].produtos[posicao(i, idp)].qtd, maxID = i;
                }
            }
        }
        if (numero > 0) printf("Maximo produto %d %d %d.\n", idp, maxID, numero);
    }
}

/* Funcao que lista todos os produtos do sistema por ordem crescente de preco (usando o algoritmo de quick sort), e se forem iguais, imprime por ordem crescente de idp. */
void casol(){
    int i;
    for (i = 0; i < idpGlobal; i++) ordenados[i] = sistema[i];
    quickSort(ordenados, 0, idpGlobal - 1, 1);
    printf("Produtos\n");
    for (i = 0; i < idpGlobal; i++) printf("* %s %d %d\n", ordenados[i].desc, ordenados[i].preco, ordenados[i].qtd);
}

/* Funcao que lista todos os produtos de uma encomenda por ordem alfabetica de descricao. (usando o algoritmo de quick sort). */
void casoL(int ide){
    if (!existeEncomenda(ide)) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else{
        int i;
        quickSort(encomendas[ide].produtos, 0, encomendas[ide].distintos - 1, 2);
        printf("Encomenda %d\n", ide);
        for (i = 0; i < encomendas[ide].distintos; i++) if (encomendas[ide].produtos[i].qtd > 0) printf("* %s %d %d\n", encomendas[ide].produtos[i].desc, encomendas[ide].produtos[i].preco, encomendas[ide].produtos[i].qtd);
    }
}

/* Le cada caso e determina qual funcao usar com o uso de um switch. */
int main(){
    char caso;
    int ide;
    Produto p1;
    scanf("%c ", &caso);
    while (caso != 'x'){
        switch(caso){
            case 'a':
                scanf("%[^:]:%d:%d:%d", p1.desc, &p1.preco, &p1.peso, &p1.qtd);
                casoa(p1);
                break;
                
            case 'q':
                scanf("%d:%d", &p1.idp, &p1.qtd);
                casoq(p1.idp, p1.qtd);
                break;
                
            case 'N':
                casoN();
                break;
 
            case 'A':
                scanf("%d:%d:%d", &ide, &p1.idp, &p1.qtd);
                casoA(ide, p1.idp, p1.qtd);
                break;
            
            case 'r':
                scanf("%d:%d", &p1.idp, &p1.qtd);
                casor(p1.idp, p1.qtd);
                break;
            
            case 'R':
                scanf("%d:%d", &ide, &p1.idp);
                casoR(ide, p1.idp);
                break;
            
            case 'C':
                scanf("%d", &ide);
                casoC(ide);
                break;
            
            case 'p':
                scanf("%d:%d", &p1.idp, &p1.preco);
                casop(p1.idp, p1.preco);
                break;
            
            case 'E':
                scanf("%d:%d", &ide, &p1.idp);
                casoE(ide, p1.idp);
                break;
            
            case 'm':
                scanf("%d", &p1.idp);
                casom(p1.idp);
                break;
            
            case 'l':
                casol();
                break;
            
            case 'L':
                scanf("%d", &ide);
                casoL(ide);
                break;
        }
        scanf("\n%c ", &caso);
    }
    return 0;
}
