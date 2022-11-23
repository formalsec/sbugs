#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define DIM 10000 /*Numero maximo de produtos.*/
#define ENCO 500 /*Numero maximo de encomendas.*/
#define PRODS 200 /*Numero maximo de produtos numa encomenda.*/

/*Define a estrutura produto, onde esta contida a informacao sobre um determinado produto.*/
typedef struct{
    int qtd; /*Representa a quantidade do produto no sistema.*/
    int preco; /*Representa o preco do produto.*/
    int peso; /*Representa o peso do produto.*/
    int id; /*Representa o indice do produto.*/
    char descricao[62]; /*Representa a descricao do produto.*/
}produto;

/*Define a estrutura encomenda, onde esta contida a informacao sobre uma determinada encomenda.*/
typedef struct{
    int id; /*Representa onde se encontra o ultimo produto adicionado a encomenda.*/
    int produtos[PRODS][2]; /*No primeiro indice encontra-se o indice do produto e no segundo indice enconta-se a quantidade do produto na encomenda.*/
    int peso; /*Representa o peso da encomenda.*/
}encomenda;

produto lista_prods[DIM]; /*Array onde se guarda todos os produtos.*/
encomenda lista_enc[ENCO]; /*Array onde se guarda todas as encomendas.*/

/*Sempre que aparece ide neste programa corresponde ao indice da encomenda que o utilizador pretende.
Sempre que aparece idp e o indice do produto que o utilizador pretende.
Sempre que aparece qtd e a quantidade que o utilizador pretende.*/

/*Esta funcao serve para adicionar um produto ao sistema.*/
int adiciona_prod(int id_prods){
    id_prods++;
    scanf(" %[^:]:%d:%d:%d", lista_prods[id_prods].descricao, &lista_prods[id_prods].preco, &lista_prods[id_prods].peso , &lista_prods[id_prods].qtd);
    lista_prods[id_prods].id = id_prods;
    printf("Novo produto %d.\n", id_prods);
    return id_prods;
}

/*Esta funcao serve para adicionar stock a um produto existente no sistema.*/
void adiciona_stock(int id_prod){
    int id_stock, qtd;
    scanf("%d:%d", &id_stock, &qtd);
    if (id_stock > id_prod){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_stock);
    }
    else{
        lista_prods[id_stock].qtd += qtd; 
    }
}

/*Esta funcao serve para adicionar um produto a uma encomenda.*/
void ad_prod_enc(int id_prod, int id_enc){
    int i, ide, idp, qtd;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if (ide > id_enc){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp > id_prod){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if (qtd > lista_prods[idp].qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if (lista_prods[idp].peso*qtd + lista_enc[ide].peso > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else{    
        
        for (i = 0; i <= lista_enc[ide].id; i++){
            /*Este if verifica se o produto ja existe na encomenda*/
            if (lista_enc[ide].produtos[i][0] == idp){
                lista_enc[ide].produtos[i][1] += qtd;
                lista_enc[ide].peso += lista_prods[idp].peso*qtd;
                lista_prods[idp].qtd -= qtd;
                return;
            }
        }
        lista_enc[ide].id += 1; /*Aqui incrementa-se esta variavel para passar para o proximo sitio onde podemos guardar um produto novo na encomenda.*/
        lista_enc[ide].produtos[lista_enc[ide].id][0] = idp;
        lista_enc[ide].produtos[lista_enc[ide].id][1] = qtd;
        lista_enc[ide].peso += lista_prods[idp].peso*qtd;
        lista_prods[idp].qtd -= qtd;
    }

}

/*Esta funcao serve para retirar stock a um produto existente no sistema.*/
void remove_stock(int id_prod){
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    if(idp > id_prod){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if (qtd > lista_prods[idp].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else {
        lista_prods[idp].qtd -= qtd;
    }
}

/*Esta funcao remove um produto de uma encomenda.*/
void remove_prod_enc(int id_enc, int id_prod){
    int i, e, ide, idp;
    scanf("%d:%d", &ide, &idp);
    if (ide > id_enc){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp > id_prod){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        for (i = 0; i <= lista_enc[ide].id; i++){
            if (idp == lista_enc[ide].produtos[i][0]){
                lista_prods[idp].qtd += lista_enc[ide].produtos[i][1];
                lista_enc[ide].peso -= lista_prods[idp].peso * lista_enc[ide].produtos[i][1];
                /*Este ciclo 'for' serve para por os produtos, que se encontravam a frente do produto que foi retirado, uma posicao para tras
                ficando assim os produtos na encomenda todos seguidos.*/
                for (e = i; e < lista_enc[ide].id; e++){ 
                    lista_enc[ide].produtos[e][0] = lista_enc[ide].produtos[e + 1][0];
                    lista_enc[ide].produtos[e][1] = lista_enc[ide].produtos[e + 1][1];
                }
                lista_enc[ide].id--;
            }
        }
}
}

/*Esta funcao serve para calcular o preco de uma encomenda.*/
void cal_preco_enc(int id_enc){
    int i, idp, ide, soma = 0; /*A variavel soma e onde se vai acumulando o custo de cada produto da encomenda.*/
    scanf("%d", &ide);
    if (ide > id_enc){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for (i = 0; i <= lista_enc[ide].id; i++){
            idp = lista_enc[ide].produtos[i][0];
            soma += lista_prods[idp].preco * lista_enc[ide].produtos[i][1];
        }
        printf("Custo da encomenda %d %d.\n", ide, soma);
    }
}

/*Esta funcao serve para alterar o preco de um produto existente no sistema.*/
void altera_preco(int id_prod){
    int idp, preco;
    scanf("%d:%d", &idp, &preco);
    if (idp > id_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        lista_prods[idp].preco = preco;
    }
}

/*Esta funcao serve para devolver a descricao e quantidade de um produto numa encomenda.*/
void des_qtd_prod_enc(int id_enc, int id_prod){
    int i, ide, idp;
    scanf("%d:%d", &ide, &idp);
    if (ide > id_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (idp > id_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        for (i = 0; i <= lista_enc[ide].id; i++){
            /*Este 'if' serve para ver se o produto ja existe na encomenda.*/
            if (lista_enc[ide].produtos[i][0] == idp){ 
                printf("%s %d.\n", lista_prods[idp].descricao, lista_enc[ide].produtos[i][1]);
                return;
            }
        }
        printf("%s %d.\n", lista_prods[idp].descricao, 0);
    }
}

/*Esta funcao serve para devolver o identificador da encomenda onde um dado produto existe em maior quantidade.*/
void max_prod_enc(int id_prod, int id_enc){
    int e, i, idp, id_prod_max = -1, qtd_max = 0; /*A variavel id_prod_max e qtd_max correspondem ao indice da encomenda onde o produto existe 
    em maior quantidade e a quantidade do produto, respetivamente.*/
    scanf("%d", &idp);
    if (idp > id_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        for (i = 0; i <= id_enc; i++){
            for (e = 0; e <= lista_enc[i].id; e++){
                /*Esta 'if' serve para ver se o produto existe na encomenda e se a sua quantidade e superior a das encomendas anteriores.*/
                if ((lista_enc[i].produtos[e][0] == idp) && (lista_enc[i].produtos[e][1] > qtd_max)){
                    qtd_max = lista_enc[i].produtos[e][1];
                    id_prod_max = i;
                }
            }
        }
        if (id_prod_max != -1){
            printf("Maximo produto %d %d %d.\n", idp, id_prod_max, qtd_max);
        }
    }
}

produto aux[DIM]; /*Array auxiliar a funcao merge.*/
produto lista_ord[DIM]; /*Array que retorna ordenado da funcao mergesort.*/

/*Devolve um vetor ordenado, em lista[left..right], dados dois vetores ordenados em lista[left..m] e lista[m+1..right]*/
void merge(produto lista[], int left, int m, int right, char ctrl){
    int i, j, k;
    /*Os dois ciclos 'for' seguintes servem para contruir o vetor auxiliar.*/
    for (i = m+1; i > left; i--){
        aux[i-1] = lista[i-1];
    }
    for (j = m; j < right; j++){
        aux[right+m-j] = lista[j+1];
    }
    /*Este ciclo 'for' vai escolhendo os elementos das pontas de forma a ordenar o vetor lista[].*/
    for (k = left; k <= right; k++){
        /*Este 'if' serve para verificar se e para organizar por preco ou por descricao.*/
        if (ctrl == 'l'){
            if (lista_prods[aux[j].id].preco < lista_prods[aux[i].id].preco){
                lista[k].id = aux[j--].id;
            }
            else if (lista_prods[aux[j].id].preco == lista_prods[aux[i].id].preco){
                if (aux[j].id < aux[i].id){
                    lista[k].id = aux[j--].id;
                }
                else{
                    lista[k].id = aux[i++].id;
                }
            }
            else{
                lista[k].id = aux[i++].id;
            }
        }
        else{
            if (strcmp(lista_prods[aux[j].id].descricao,lista_prods[aux[i].id].descricao) < 0){
                lista[k] = aux[j--];
            }
            else{
                lista[k] = aux[i++];
            }
        }
    }
}

/*Esta funcao serve para dividir o array ao meio sucessivamente ate so ter array de 1 elemento, e posteriormente manda para a funcao merge para os juntar de forma ordenada.*/
void mergesort(produto lista[], int left, int right, char ctrl){
    int m = (right + left) / 2;
    if (right <= left){ 
        return;
    }
    mergesort(lista, left, m, ctrl);
    mergesort(lista, m+1, right, ctrl);
    merge(lista, left, m, right, ctrl);

}

/*Esta funcao serve para preparar o array que vai servir de input para a funcao mergesort e posteriormente mostrar a descricao, preco e quantidade, 
respetivamente, dos produtos no sistema de forma ordenada por preco.*/
void prod_por_preco(int id_prod){
    int i;
    for (i = 0; i <= id_prod; i++){
        lista_ord[i].id = lista_prods[i].id;
    }

    mergesort(lista_ord, 0, id_prod, 'l');
    
    printf("Produtos\n");
    for (i = 0; i <= id_prod; i++){
        printf("* %s %d %d\n",lista_prods[lista_ord[i].id].descricao, lista_prods[lista_ord[i].id].preco, lista_prods[lista_ord[i].id].qtd);
    }
}

/*Esta funcao serve para preparar o array que vai servir de input para a funcao mergesort e posteriormente mostrar a descricao, preco e quantidade, 
respetivamente, dos produtos numa encomenda de forma ordenada por descricao.*/
void prod_enc_nome(int id_enc){
    int i, ide;
    scanf("%d", &ide);
    if (ide > id_enc){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        for(i = 0; i <= lista_enc[ide].id; i++){
            lista_ord[i].id = lista_enc[ide].produtos[i][0];
            lista_ord[i].qtd = lista_enc[ide].produtos[i][1];
        }

        mergesort(lista_ord, 0, lista_enc[ide].id, 'L');

        printf("Encomenda %d\n", ide);
        for (i = 0; i <= lista_enc[ide].id; i++){
            printf("* %s %d %d\n", lista_prods[lista_ord[i].id].descricao, lista_prods[lista_ord[i].id].preco, lista_ord[i].qtd); 
        }
    }

}

/*Esta funcao serve para verificar qual e a operacao que o utilizador pretende realizar e, seguidamente, chama a funcao 
que realiza a operacao pretendida, em excecao do caso de o utilizador querer uma encomenda nova.*/
int main(){

    char caracter;/*Esta variavel e a que recebe, do utilizador, que acao deve acontecer.*/
    int i, id_prod = -1, id_enc = -1; /*A variavel id_prod representa o indice do ultimo produto adicionado ao sistema
    a variavel id_enc representa o id da ultima encomenda adicionada ao sistema.*/

    /*Este ciclo serve para por os indices da encomenda a -1, fazendo assim com que no inicio nao exista nenhuma encomenda ativa.*/
    for (i = 0; i < ENCO; i++){
        lista_enc[i].id = -1;
    }

    caracter = getchar();

    while (caracter != 'x'){
        switch(caracter){

            case 'a':
                id_prod = adiciona_prod(id_prod);
                break;

            case 'q':
                adiciona_stock(id_prod);
                break;
            
            case 'N':
                id_enc++; /*Incrementa-se a encomenda para saber que foi criada uma nova.*/
                printf("Nova encomenda %d.\n", id_enc);
                break;

            case 'A':
                ad_prod_enc(id_prod, id_enc);
                break;

            case 'r':
                remove_stock(id_prod);
                break;

            case 'R':
                remove_prod_enc(id_enc, id_prod);
                break;

            case 'C':
                cal_preco_enc(id_enc);
                break;

            case 'p':
                altera_preco(id_prod);
                break;

            case 'E':
                des_qtd_prod_enc(id_enc, id_prod);
                break;

            case 'm':
                max_prod_enc(id_prod, id_enc);
                break;

            case 'l':
                prod_por_preco(id_prod);
                break;

            case 'L':
                prod_enc_nome(id_enc);
                break;
            
        }
        
        caracter = getchar();
    }
    return 0;
}