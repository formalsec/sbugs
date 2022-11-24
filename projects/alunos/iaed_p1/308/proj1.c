#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* Ricardo Rodrigues n?96764 LETI */

/* Nas proximas linhas definimimos umas quantas variaveis de forma a facilitar o processo no futuro */

#define MAX_NAME 64
#define MAX_PROD 10000
#define MAX_ORDER 500
#define MAX_WEIGHT 200
#define MAX_ENCOMENDAS 500

/* Construcao de uma estrutura correspondente aos produtos */
struct Product {

    int id;                /* id do produto */
    char nome[MAX_NAME];   /*  descricao do produto, onde usamos o define acima para definir o numero maximo de caracteres */
    int price;             /* preco do produto */ 
    int weight;            /* peso do produto */
    int quantidade;        /* quantidade do produto em stock */
};

/* Construcao de uma estrutura correspondente as encomendas */
struct Encomenda {
    int idp[200];         /* id de cada produto dentro da encomenda */
    int qtds[200];        /* quantidade de produtos contidos em cada vetor de idp */
    int len;              /* len diz o numero de vetores contidos em idp*/  
    int peso;             /* peso total dos produtos */
};

/*  Definicao de umas variaveis de forma a facilitar o processo */
struct Product produtos[MAX_PROD];
int length_produtos = 0;  /* numero de produtos  */

/* Esta funcao tem como objetivo adicionar um produto ao sistema */
void adiciona() {
    /* Proximo segmento le os valores dados no input */
    struct Product produto;
    scanf(" %[^:]:%d:%d:%d\n", produto.nome, &produto.price, &produto.weight, &produto.quantidade);
    /* Definicao de que o produto comeca com o id 0 */
    produto.id = length_produtos;
    produtos[length_produtos] = produto;
    /* Incrementamos um ao valor de length_produtos de forma a atualizar o id dos produtos */
    length_produtos += 1;
    printf("Novo produto %d.\n", produto.id);
}


/* Esta funcao auxiliar tem como finalidade trasnformar o id de um produto em um indice */
int busca_idxp(int idp) {
    int n;
    for (n = 0; n < length_produtos; n++) {
        if (produtos[n].id == idp) {
            return n;
        }
    }
    return -1;
}


/* Esta funcao tem como objetivo adicionar stock a um produto ja existente no sistema */
void adiciona_stock() {
    
    /* Proximo segmento le os valores dados no input */
    int idp, quantidade, idxp;
    scanf(" %d:%d\n", &idp, &quantidade);
    
    /* Proximas linhas de codigo estao a verificar se o produto que pretendemos adicionar stock existe, caso nao pertencer, da erro */
    if (idp >= length_produtos) {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
        return;
    }

    /* Adicionamos o stock que pretendemos adicionar, caso o produto exista */
    idxp = busca_idxp(idp);
    produtos[idxp].quantidade += quantidade;
}

/* definicao de umas variaveis de forma a facilitar o processo na funcao a seguir */
struct Encomenda encomendas[MAX_ENCOMENDAS];
int len_encomendas = 0;

/*Esta funcao tem como fundamento criar uma nova encomenda */
void cria_encomenda() {
    /* Valores fornecidos no input */
    struct Encomenda encomenda;

    /* Comecamos os valores de len e peso a 0, pois trata-se de uma nova encomenda */
    encomenda.len = 0;
    encomenda.peso = 0;

    /* Formamos assim uma nova encomenda */
    encomendas[len_encomendas] = encomenda;
    printf("Nova encomenda %d.\n", len_encomendas);
    len_encomendas += 1;
}


/* Esta funcao tem como objetivo adicionar um produto a uma encomenda que ja existia */
void adiciona_prod() {
    /* Leitura dos valores dados no input */
    int ide, idp, qtd, n, idxp;
    scanf("%d:%d:%d\n", &ide, &idp, &qtd);

    /* Se o ide da encomenda nao existir, geramos um erro */
    if (ide >= len_encomendas) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    /* Se o id do produto nao estiver na encomenda, geramos erro */
    if (idp >= length_produtos) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    idxp = busca_idxp(idp);

    /* Se a quantidade em stock do produto nao for suficiente, relativa aquela que e pedida, geramos erro */
    if (produtos[idxp].quantidade < qtd) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    /* Se o peso total ultrapssar as 200 unidades de pesso, gera erro */
    if (encomendas[ide].peso + qtd * produtos[idxp].weight > 200) {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    /* No caso de ter ultrapassado as etapas anteriores, atualizamos os valores com o novo produto */
    for (n = 0; n < encomendas[ide].len; n++) {
        if (encomendas[ide].idp[n] == idp) {
            encomendas[ide].qtds[n] += qtd;                       /* Adicionamos a quantidade a encomenda */ 
            produtos[idxp].quantidade -= qtd;                     /* Retiramos a quantidade ao produto*/
            encomendas[ide].peso += qtd * produtos[idxp].weight;  /* Atualizamos o peso total da encomenda*/
            return;
        }
    }

    /* Atualizacao dos valores na encomenda */
    encomendas[ide].idp[encomendas[ide].len] = idp;
    encomendas[ide].qtds[encomendas[ide].len] = qtd;
    encomendas[ide].len += 1;
    produtos[idxp].quantidade -= qtd;
    encomendas[ide].peso += qtd * produtos[idxp].weight;
}


/* Esta funcao remove stock a um protudo ja existente */ 
void remove_stock() {
    
    /* Leitura dos valores fornecidos no input */
    int idp, qtd, idxp;
    scanf("%d:%d\n", &idp, &qtd);

    /* Se o id do produto nao existir, geramos erro */
    if (idp >= length_produtos) {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }

    idxp = busca_idxp(idp);

    /*No caso da quantidade que pretendemos remover for superior a quantidade do produto, geramos erro */
    if (produtos[idxp].quantidade < qtd) {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        return;
    }

    /* Caso tenha passado os testes anteriores, removemos essa quantidade ao produto */
    produtos[idxp].quantidade -= qtd;
}


/* Esta funcao tem como finalidade remover um produto de uma dada encomenda */
void remove_prod() {

    /* Leitura dos valores dados no input */
    int ide, idp, idxp, n, temp;
    scanf("%d:%d\n", &ide, &idp);

    /* No caso do id da encomenda nao existir, geramos erro */
    if (ide >= len_encomendas) {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    /* Caso o produto que pretendemos remover nao estiver incluido na encomenda, geramos erro */
    if (idp >= length_produtos) {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    }

    idxp = busca_idxp(idp);

    /*Fazemos um ciclo de forma a passar por todas as encomendas */
    for (n = 0; n < encomendas[ide].len; n++) {
        /* Se a encomenda existir e coincidir com o id do produto, atualizamos os dados da encomenda */
        if (encomendas[ide].idp[n] == idp) {

            produtos[idxp].quantidade += encomendas[ide].qtds[n];
            encomendas[ide].peso -= encomendas[ide].qtds[n] * produtos[idxp].weight;
            temp = encomendas[ide].idp[n];
            encomendas[ide].idp[n] = encomendas[ide].idp[encomendas[ide].len - 1];
            encomendas[ide].idp[encomendas[ide].len - 1] = temp;
            temp = encomendas[ide].qtds[n];
            encomendas[ide].qtds[n] = encomendas[ide].qtds[encomendas[ide].len - 1];
            encomendas[ide].qtds[encomendas[ide].len - 1] = temp;
            encomendas[ide].len -= 1;
            return;
        }
    }
}


/* Esta funcao calcula o custo de uma dada encomenda */
void calcula_custo() {

    /* Leitura dos valores dados como input */
    int ide, custo, idxp, n;
    scanf("%d\n", &ide);

    /* No caso do id dado nao coincidir com id de uma encomenda ja existente,  geramos erro */
    if (ide >= len_encomendas) {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /* Iniciamos o custo da encomenda a 0 */
    custo = 0;

    /* Passamos por todos os produtos na encomenda e calculamos o seu custo */
    for (n = 0; n < encomendas[ide].len; n++) {
        idxp = busca_idxp(encomendas[ide].idp[n]);
        custo += produtos[idxp].price * encomendas[ide].qtds[n];
    }

    /* Como output, sai o ide da encomenda e o seu respetivo custo */
    printf("Custo da encomenda %d %d.\n", ide, custo);
}


/* ESta funcao altera o preco de um produto existente no sistema */
void muda_preco() {

    /* Leitura dos valores dados como input */
    int idp, preco, idxp;
    scanf("%d:%d", &idp, &preco);

    /* No caso do id do produto nao existir, geramso erro */
    if (idp >= length_produtos) {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /* Alteracao do valor do preco do produto */ 
    idxp = busca_idxp(idp);
    produtos[idxp].price = preco;
}


/* Esta funcao lista a descricao e quantidade de um produto numa dada encomenda */
void lista_desc() {

    /* Leitura dos valores dados como input */
    int ide, idp, idxp, n;
    scanf(" %d:%d\n", &ide, &idp);

    /* No caso do id da encomenda nao existir, geramos erro */
    if (ide >= len_encomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }

    /* No caso do id do produto nao existir, geramos erro */
    if (idp >= length_produtos) {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        return;
    }

    /*  Passamos por todos os ids dos produtos de todas encomendas */
    idxp = busca_idxp(idp);
    for (n = 0; n < encomendas[ide].len; n++) {

        /* Ao encontrarmos o id do produto na encomenda, imrpimimos a sua descricao e a quantidade */
        if (encomendas[ide].idp[n] == idp) {
            printf("%s %d.\n", produtos[idxp].nome, encomendas[ide].qtds[n]);
            return;
        }
    }
    printf("%s 0.\n", produtos[idxp].nome);
}


/* Esta funcao lista o identificador em que o produto aparece mais vezes, imprimindo o id. 
No caso de haver 2 encomendas, imprime a que tem menor id  */
void lista_maior_encomenda() {
    /* Leitura dos valores dados como input */
    int idp, n, ide_max, ide_qtd_max, i;
    scanf("%d\n", &idp);

    /* No caso do id do produto nao existir, geramos erro */
    if (idp >= length_produtos) {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
        return;
    }

    /* Inicializamos duas variaveis onde depois vamos colocando o valor do id maximo e quantidade maxima */
    ide_max = -1;
    ide_qtd_max = -1;

    /* Fazemos um ciclo de forma a passar por todos ids das encomendas*/
    for (n = 0; n < len_encomendas; n++) {
        /* Mais um ciclo onde passamos por todos os produtos presentes na encomenda*/
        for (i = 0; i < encomendas[n].len; i++) {
            /* Atualizacao das variaveis mencionadas anteriormente de forma a listar o identificador que aparece mais vezes,
              bem como o id do produto menor, caso houvesse duas encomendas que tinham esse produto */
            if (encomendas[n].idp[i] == idp) {
                if (encomendas[n].qtds[i] > ide_qtd_max || (encomendas[n].qtds[i] == ide_qtd_max && n < ide_max)) {
                    ide_max = n;
                    ide_qtd_max = encomendas[n].qtds[i];
                }
            }
        }
    }
    if (ide_max != -1) {
        /* Print do identificador onde esse produto aparece mais vezes, bem como o id da encomenda */ 
        printf("Maximo produto %d %d %d.\n", idp, ide_max, ide_qtd_max);
    }
}


/* Esta funcao auxiliar serve para comparar dois produtos segundo o seu id e o preco  */
int lista_prod_less(int l, int r) {
    if (produtos[l].price < produtos[r].price) {
        return 1;
    }

    else if (produtos[l].price > produtos[r].price) {
        return 0;
    }

    else if (produtos[l].id < produtos[r].id) {
        return 1;
    }

    else {
        return 0;
    }
}

/* Esta funcao auxiliar tem como ordenar os valores por ordem crescente */
void lista_prod_sort() {
    struct Product temp;
    int i, j;
    for (i = 0; i < length_produtos - 1; i++) {
        int min = i;
        for (j = i + 1; j < length_produtos; j++) {
            if (lista_prod_less(j, min)) {
                min = j;
            }
        }
        temp = produtos[i];
        produtos[i] = produtos[min];
        produtos[min] = temp;
    }
}

/* Esta funcao usa as duas funcoes auxiliares anteriores e ordena os produtos por ordem crescente de preco */
void lista_prod() {
    int n;
    lista_prod_sort();
    printf("Produtos\n");
    for (n = 0; n < length_produtos; n++) {
        printf("* %s %d %d\n", produtos[n].nome, produtos[n].price, produtos[n].quantidade);
    }
}


/* Esta funcao compara 2 ids dos produtos de uma encomenda segundo o seu nome, usando a funcao auxiliar strcmp*/
int lista_encomenda_alfabetica_less(int ide, int j, int min) {
    int idxp_j, idxp_min;
    idxp_j = busca_idxp(encomendas[ide].idp[j]);
    idxp_min = busca_idxp(encomendas[ide].idp[min]);
    /* Compara as duas strings correspondentes ao nome do produto */
    return strcmp(produtos[idxp_j].nome, produtos[idxp_min].nome) <= 0;
}

/*  Esta funcao auxiliar serve para ordenar as encomendas por ordem alfabetica*/
void lista_encomenda_alfabetica_sort(int ide) {
    int i, j, temp;
    for (i = 0; i < encomendas[ide].len - 1; i++) {
        int min = i;
        for (j = i + 1; j < encomendas[ide].len; j++) {
            /* Utilizacao da funcao anterior para ordenar as encomendas por ordem alfabetica */
            if (lista_encomenda_alfabetica_less(ide, j, min)) {
                min = j;
            }
        }
        /* Atualizacao dos valores por ordem alfabetica*/
        temp = encomendas[ide].idp[i];
        encomendas[ide].idp[i] = encomendas[ide].idp[min];
        encomendas[ide].idp[min] = temp;
        temp = encomendas[ide].qtds[i];
        encomendas[ide].qtds[i] = encomendas[ide].qtds[min];
        encomendas[ide].qtds[min] = temp;
    }
}

/* Esta funcao usa as duas funcoes anteriores e ordena as encomendas por ordem alfabetica */
void lista_encomenda_alfabetica() {
    /*  Leitura dos valores dados como input */
    int ide, n, idxp;
    scanf("%d\n", &ide);

    /* No caso do id da encomenda nao existir, gera erro */ 
    if (ide >= len_encomendas) {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        return;
    }
    /* Ordenacao como e pedida usando a funcao a xuiliar enunciada previamente */ 
    lista_encomenda_alfabetica_sort(ide);

    /* Print da encomenda com o seu id */
    printf("Encomenda %d\n", ide);

    /* Usamos um ciclo for de forma a passar por todas os produtos da encomenda */
    for (n = 0; n < encomendas[ide].len; n++) {
        idxp = busca_idxp(encomendas[ide].idp[n]);
        /* Print da descricao total do produto ja ordenada como pretendido */
        printf("* %s %d %d\n", produtos[idxp].nome, produtos[idxp].price, encomendas[ide].qtds[n]);
    }
}

/* Funcao principal do sistema de encomendas, onde se colocou todas as funcoes montadas anteriormente para criar o sistema */
int main() {
    while (1) {

        /* Leitura do valor dado como input */
        int c = getchar();
        switch (c) {
        
        case 'a':
            adiciona();
            break;

        case 'q':
            adiciona_stock();
            break;

        case 'N':
            cria_encomenda();
            break;

         case 'A':
            adiciona_prod();
            break;    

        case 'r':
            remove_stock();
            break;

        case 'R':
            remove_prod();
            break;

        case 'C':
            calcula_custo();
            break;
            
        case 'p':
            muda_preco();
            break;

        case 'E':
            lista_desc();
            break;

        case 'm':
            lista_maior_encomenda();
            break;

        case 'l':
            lista_prod();
            break;

        case 'L':
            lista_encomenda_alfabetica();
            break;

        case 'x':
            return 0;
        }
    }
}