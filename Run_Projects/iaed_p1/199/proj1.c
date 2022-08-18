#include <stdio.h>
#include <string.h>

/* Numero max de produtos. */
#define MAXPRODS 10000
/* Numero max de encomendas. */
#define MAXENCOMENDAS 500
/* Peso max de cada encomenda, e tambem, numero max de produtos numa encomenda. */
#define MAXPESO 200
/* Numero max de carateres na descricao de um produto, incluindo \0. */
#define MAXDESCRICAO 64
/* Condicoes que distinguem se esta a ser executado o comando l ou L, respetivamente. */
#define ordempreco 0
#define ordemalfabetica 1

/* Numero de produtos no sistema +1. */
int identificadorprods;
/* Numero de encomendas no sistema +1. */
int identificadorencomendas;

typedef struct produto {
    int idp;
    char descricao[MAXDESCRICAO];
    int preco;
    int peso;
    int qtd;
} produto;

typedef struct encomenda {
    /* Vetor com o id dos produtos na encomenda. */
    int ids_prods[MAXPESO];
    int peso;
    int ide;
    /* Numero de produtos na encomenda +1. */
    int idprodsnaencomenda;
    /* Vetor com a quantidade de cada produto na encomenda. */
    int quantidade_prods[MAXPRODS];
} encomenda;

/* Vetor de todos os produtos no sistema. */
produto produtos[MAXPRODS];
/* Vetor auxiliar para o mergesort. */
produto aux[MAXPRODS];
/* Vetor de todas as encomendas no sistema. */
encomenda encomendas[MAXENCOMENDAS];

/* Verifica se um produto existe no sistema. */
int existe_produto(int idproduto) {
    return idproduto<identificadorprods;
}

/* Verifica se uma encomenda existe no sistema. */
int existe_encomenda(int idencomenda) {
    return idencomenda<identificadorencomendas;
}

/* Adiciona um novo produto ao sistema(vetor produtos). */
void adiciona_produto() {
    produto p1;
    char c;
    int i = 0;
    getchar();
    while ((c=getchar())!=':') {
        p1.descricao[i] = c;
        i++;
    }
    p1.descricao[i]='\0';
    scanf("%d:%d:%d\n",&p1.preco,&p1.peso,&p1.qtd);
    p1.idp = identificadorprods;
    produtos[identificadorprods++] = p1;
    printf("Novo produto %d.\n",p1.idp);
}

/* Adiciona stock(qtd) a um produto existente. */
void adiciona_stock() {
    int idproduto,nova_qtd;
    scanf(" %d:%d\n",&idproduto,&nova_qtd);
    if (existe_produto(idproduto)) {
        produtos[idproduto].qtd += nova_qtd;
    }
    else {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idproduto);
    }
}

/* Cria uma nova encomenda(adiciona uma nova encomenda ao vetor encomendas). */
void cria_encomenda() {
    encomendas[identificadorencomendas].ide = identificadorencomendas;
    printf("Nova encomenda %d.\n",encomendas[identificadorencomendas++].ide);
}

/* Adiciona um produto a uma encomenda, aumentando a sua quantidade e adicionando-lhe o seu id. */
void adiciona_produto_a_encomenda() {
    int idencomenda,idproduto,quantidade;
    encomenda e1;
    produto p1;
    scanf(" %d:%d:%d\n",&idencomenda,&idproduto,&quantidade);
    if (existe_encomenda(idencomenda)) {
        e1 = encomendas[idencomenda];
        if (existe_produto(idproduto)) {
            p1 = produtos[idproduto];
            if (p1.qtd >= quantidade) {
                if ((e1.peso+(p1.peso*quantidade)) <= MAXPESO) {
                    e1.peso += (p1.peso*quantidade);
                    p1.qtd -= quantidade;
                    /* Se o produto ainda nao esta na encomenda adicionar o seu id. */
                    if (e1.quantidade_prods[idproduto]==0) {
                            e1.ids_prods[e1.idprodsnaencomenda++] = p1.idp;
                    }
                    e1.quantidade_prods[idproduto] += quantidade;
                    encomendas[idencomenda] = e1;
                    produtos[idproduto] = p1;
                }
                else {
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idproduto,idencomenda);
                }
            }
            else {
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idproduto,idencomenda);
            }
        }
        else {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idproduto,idencomenda);
        }
    }
    else {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idproduto,idencomenda);
    }
}

/* Remove stock(qtd) a um produto existente. */
void remove_stock() {
    int idproduto,quantidade;
    scanf(" %d:%d\n",&idproduto,&quantidade);
    if (existe_produto(idproduto)) {
        if(produtos[idproduto].qtd>=quantidade) {
            produtos[idproduto].qtd -= quantidade;
        }
        else {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quantidade,idproduto);
        }
        
    }
    else {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idproduto);
    }
}

/* Remove um produto de uma encomenda, colocando a sua qtd a 0, repondo o seu stock e apagando o seu id da encomenda. */
void remove_produto() {
    int idencomenda,idproduto,i,j=0;
    encomenda e1;
    scanf(" %d:%d\n",&idencomenda,&idproduto);
    if (existe_encomenda(idencomenda)) {
        e1 = encomendas[idencomenda];
        if (existe_produto(idproduto)) {
            /* Apenas executa se o produto estiver de facto na encomenda. */ 
            if (e1.quantidade_prods[idproduto] != 0) {
                /* Retira da encomenda o peso do produto retirado. */
                e1.peso -= (e1.quantidade_prods[idproduto]*produtos[idproduto].peso);
                /* Volta a adicionar a quantidade do produto na encomenda ao stock. */
                produtos[idproduto].qtd += e1.quantidade_prods[idproduto];
                e1.quantidade_prods[idproduto] = 0;
                /* Apagar o id do produto da encomenda. */
                for(i=0;i<e1.idprodsnaencomenda;i++) {
                    if (e1.ids_prods[i]!=idproduto) {
                        e1.ids_prods[j++] = e1.ids_prods[i];
                    }
                }
                /* Agora ha menos 1 produto na encomenda. */
                e1.idprodsnaencomenda--;
                encomendas[idencomenda] = e1;
            }
            
        }
        else {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idproduto,idencomenda);
        }
    }
    else {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idproduto,idencomenda);
    }
}

/* Calcula o custo de uma encomenda. */
void calcula_custo() {
    int idencomenda,idproduto,i,total=0;
    encomenda e1;
    scanf(" %d\n",&idencomenda);
    if (existe_encomenda(idencomenda)) {
        e1 = encomendas[idencomenda];
        /* O custo total e a soma de preco de cada produto multiplicado pela sua quantidade na encomenda. */
        for (i=0;i<e1.idprodsnaencomenda;i++) {
            idproduto = e1.ids_prods[i];
            total += (e1.quantidade_prods[idproduto]*produtos[idproduto].preco);
        }
        printf("Custo da encomenda %d %d.\n",idencomenda,total);
    }
    else {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",idencomenda);
    }
}

/* Altera o preco de um produto existente no sistema. */
void altera_preco() {
    int idproduto,novo_preco;
    scanf(" %d:%d\n",&idproduto,&novo_preco);
    if (existe_produto(idproduto)) {
        produtos[idproduto].preco = novo_preco;
    }
    else {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idproduto);
    }
}

/* Imprime a descricao e a quantidade de um produto numa dada encomenda. */
void lista_encomenda() {
    int idencomenda,idproduto;
    encomenda e1;
    produto p1;
    scanf(" %d:%d\n",&idencomenda,&idproduto);
    if (existe_encomenda(idencomenda)) {
        e1 = encomendas[idencomenda];
        if (existe_produto(idproduto)) {
            p1 = produtos[idproduto];
            printf("%s %d.\n",p1.descricao,e1.quantidade_prods[idproduto]);
        }
        else {
            printf("Impossivel listar produto %d. Produto inexistente.\n",idproduto);
        }
    }
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idencomenda);
    }
}

/* Imprime o id da encomenda em que um dado produto ocorre mais vezes. */
void lista_mais_ocurrencias() {
    int idproduto,i,maisocurrencias = 0;
    scanf(" %d\n",&idproduto);
    if (existe_produto(idproduto)) {
        /* Ve de todas as encomendas a que tem o produto em maior quantidade. */
        for (i=0;i<identificadorencomendas;i++) {
            if (encomendas[i].quantidade_prods[idproduto]>encomendas[maisocurrencias].quantidade_prods[idproduto]) {
                maisocurrencias = i;
            }
        }
        /* Se essa quantidade for superior a 0, ou seja, se o produto esta em pelo menos uma encomenda, imprime. */
        if (encomendas[maisocurrencias].quantidade_prods[idproduto]>0) {
            printf("Maximo produto %d %d %d.\n",idproduto,maisocurrencias,encomendas[maisocurrencias].quantidade_prods[idproduto]);
        }
    }
    else {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idproduto);
    }
}

/* Funcao merge do algoritmo do Merge Sort: ordena um vetor copia_produtos[e...d],
   dados dois vetores ordenados em copia_produtos[e...m] e copia_produtos[m+1...d]. */
void merge(int cond,produto copia_produtos [],int e,int m,int d) {
    int i,j,k;
    /* Constroi o vetor auxiliar. */
    for (i = m+1; i > e; i--) {
        aux[i-1] = copia_produtos[i-1];
    }
    for (j=m;j<d;j++) {
        aux[d+m-j] = copia_produtos[j+1];
    }
    /* Condicao que seleciona que tipo de ordenacao esta a ser feita. */
    if (cond==ordempreco) {
        /* Escolhe os elementos das pontas para ordenar o vetor por ordem crescente de precos. */
        for (k=e;k<=d;k++) {
            if (aux[j].preco<aux[i].preco || i>m) {
                copia_produtos[k] = aux[j--];
            }
            else {
                copia_produtos[k] = aux[i++];
            }
        }
    }
    else {
        /* Escolhe os elementos das pontas para ordenar o vetor por ordem alfabetica. */
        for (k=e;k<=d;k++) {
            if (strcmp(aux[j].descricao,aux[i].descricao)<0) {
                copia_produtos[k] = aux[j--];
            }
            else {
                copia_produtos[k] = aux[i++];
            }
        }
    }
}

/* Algoritmo Merge Sort. */
void merge_sort(int cond,produto copia_produtos [],int e,int d) {
    int m = (d+e)/2;
    if (d <= e) {
        return;
    }
    merge_sort(cond,copia_produtos,e,m);
    merge_sort(cond,copia_produtos,m+1,d);
    merge(cond,copia_produtos,e,m,d);
}

/* Lista todos os produtos existentes no sistema por ordem crescente de preco. */
void lista_produtos_preco(int cond) {
    int i,e = 0,d = (identificadorprods-1);
    produto copia_produtos[MAXPRODS];
    /* Cria uma copia dos produtos para ser ordenada. */
    memcpy(copia_produtos,produtos,sizeof(produtos));
    merge_sort(cond,copia_produtos,e,d);
    printf("Produtos\n");
    /* Imprime os produtos ja ordenados. */
    for (i=0;i<identificadorprods;i++) {
        printf("* %s %d %d\n",copia_produtos[i].descricao,copia_produtos[i].preco,copia_produtos[i].qtd);
    }
}

/* Lista todos os produtos de uma encomenda por ordem alfabetica. */
void lista_ordem_alfabetica(int cond) {
    int idencomenda,i,e = 0,d;
    encomenda e1;
    produto copia_produtos[MAXPESO];
    scanf(" %d\n",&idencomenda);
    if (existe_encomenda(idencomenda)) {
        e1 = encomendas[idencomenda];
        /* Copia para um vetor todos os produtos que estao na encomenda. */
        for (i=0;i<e1.idprodsnaencomenda;i++) {
            copia_produtos[i] = produtos[e1.ids_prods[i]];
        }
        d = (e1.idprodsnaencomenda-1);
        merge_sort(cond,copia_produtos,e,d);
        printf("Encomenda %d\n",idencomenda);
        /* Imprime os produtos da encomenda ja ordenados. */
        for (i=0;i<e1.idprodsnaencomenda;i++) {
            printf("* %s %d %d\n",copia_produtos[i].descricao,copia_produtos[i].preco,e1.quantidade_prods[copia_produtos[i].idp]);
        }
    }
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idencomenda);
    }
}

/* Interpreta e executa os comandos que recebe atraves do stdin. */
int main() {
    char c = 0;
    while (c != EOF) {
        switch (c = getchar()) {
            case 'a':
                adiciona_produto();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                cria_encomenda();
                break;
            case 'A':
                adiciona_produto_a_encomenda();
                break;
            case 'r':
                remove_stock();
                break;
            case 'R':
                remove_produto();
                break;
            case 'C':
                calcula_custo();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                lista_encomenda();
                break;
            case 'm':
                lista_mais_ocurrencias();
                break;
            case 'l':
                lista_produtos_preco(ordempreco);
                break;
            case 'L':
                lista_ordem_alfabetica(ordemalfabetica);
                break;
            case 'x':
                return 0;
        }
    }
    return 0;
}