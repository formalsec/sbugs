#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 10000 /* Maximo de produtos existentes no sistema*/
#define MAX_ENCOMENDAS 500 /* Maximo de encomendas existentes no sistema*/
#define MAX_PRODUTOS_ENCOMENDAS 200 /* Maximo de produtos numa encomenda*/
#define MAX_STRING_CHAR 64  /* Tamanho maximo das descricoes dos produtos*/

int contador_idp_produto = 0; /* contador que nos indica o proximo idp de um novo produto */
int contador_ide_encomenda = 0; /* contador que nos indica o proximo idp de uma nova encomenda */


/* Estrutura que define produtos*/
typedef struct produto{
    int identificador, preco, peso, quantidade;
    char string[MAX_STRING_CHAR];
}Produto;

Produto total_produtos[MAX_PRODUTOS]; /*Vetor que contem todos os produtos do sistema*/

/* Estrutura que define encomendas*/
typedef struct encomenda{
    Produto n_produtos[MAX_PRODUTOS_ENCOMENDAS];
    int identificador_en, peso_total, numero_prd;
}Encomenda;

Encomenda total_encomendas[MAX_ENCOMENDAS]; /*Vetor que contem todas as encomendas do sistema*/

/* Comando: a
* Input: descricao:preco:peso:qtd
* Descricao: Adiciona um produto novo ao sistema
*/
void adiciona_prd(){
    Produto novo;

    scanf(" %[^:]:%d:%d:%d", novo.string, &novo.preco, &novo.peso, &novo.quantidade);

    novo.identificador = contador_idp_produto;

    total_produtos[contador_idp_produto] = novo; /* Adiciona o novo protudo ao sistema*/

    printf("Novo produto %d.\n",contador_idp_produto);

    contador_idp_produto++; /* Incrementa o valor do contador para o proximo produto ter identificador seguinte*/
}

/* Comando: q
* Input: q idp:qtd
* Descricao: Adiciona stock a um produto ja existente no sistema
*/ 
void adiciona_stck(){
    int idp, stock_novo;

    scanf("%d:%d", &idp, &stock_novo);

    /* Condicao que verifica se existe um produto no sistema com o idp dado*/
    if (idp> contador_idp_produto-1){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else{
        total_produtos[idp].quantidade += stock_novo; /* Adiciona ao stock original a quantidade recebida no input*/
    }   
}

/* Comando: N
* Input: Nenhum
* Descricao: Adiciona uma encomenda nova ao sistema
*/
void nova_encomeda(){
    Encomenda nova;

    nova.identificador_en = contador_ide_encomenda;
    nova.peso_total = 0;
    nova.numero_prd = 0;
    total_encomendas[contador_ide_encomenda] = nova;
    contador_ide_encomenda++; /* Incrementa o valor do contador para a proxima encomenda ter identificador seguinte*/
    

    printf("Nova encomenda %d.\n", nova.identificador_en);
}

/* Comando: A
* Input: ide:idp:qtd
* Descricao: Adiciona um produto a uma encomenda em quantidades expecificas
*/
void adiciona_prd_encomenda(){
    int idp, ide, quantidade, i, peso_produto, flag=0, numero_prd;

    scanf("%d:%d:%d", &ide, &idp, &quantidade);

    peso_produto = total_produtos[idp].peso*quantidade; /* Utilizo a variavel peso_produto para poupar tempo de processamento*/

    if (ide > contador_ide_encomenda-1) /* Se a encomenda nao existir*/
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp > contador_idp_produto-1) /* Se o produto nao existir*/
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (quantidade > total_produtos[idp].quantidade) /* Se nao existir quantidade do produto suficiente em stock*/
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (total_encomendas[ide].peso_total+peso_produto > 200) /*Se o peso ja existente na encomenda mais o peso do produto ultrapassar 200*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else{
        /* Utilizo a variavel numero_prd para poupar tempo de processamento*/
        numero_prd = total_encomendas[ide].numero_prd;
        for (i=0; i < numero_prd; i++){
            /*Se o produto existir na encomenda passa a condicao e altera a flag para 1*/
            if (idp == total_encomendas[ide].n_produtos[i].identificador){
                total_encomendas[ide].n_produtos[i].quantidade += quantidade;
                total_encomendas[ide].peso_total += peso_produto;
                total_produtos[idp].quantidade -= quantidade;
                flag = 1;
                break;
            }
        }
        /* So entra nesta condicao se o produto nao existir na encomenda e
        * assim nao atualizando a flag para 1
        */
        if (flag == 0){
            total_encomendas[ide].n_produtos[total_encomendas[ide].numero_prd] = total_produtos[idp];
            total_encomendas[ide].peso_total += peso_produto;
            total_produtos[idp].quantidade -= quantidade;
            total_encomendas[ide].n_produtos[total_encomendas[ide].numero_prd].quantidade = quantidade;
            total_encomendas[ide].numero_prd++;
        }
    }
}

/* Comando: r
* Input: idp:qtd
* Descricao: Remove uma dada quantidade ao stock de um produto
*/
void remove_stk(){
    int idp, quantidade;

    scanf("%d:%d", &idp, &quantidade);

    /*Se o produto nao existir no sistema*/
    if (idp > contador_idp_produto-1)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    /*Se o stcok do produto for menor que a quantidade a remover*/
    else if (total_produtos[idp].quantidade - quantidade < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    else
        total_produtos[idp].quantidade -= quantidade;
}

/* Comando: R
* Input: ide:idp
* Descricao: Remove um produto de uma encomenda
*/
void remove_prd_encomenda(){
    int ide, idp, i, j, numero_produtos_en;

    scanf("%d:%d", &ide, &idp);

    /* Utilizo a variavel numero_produtos_en para poupar tempo de processamento*/
    numero_produtos_en = total_encomendas[ide].numero_prd; 

    /* Se nao existir encomenda com o ide dado*/
    if (ide > contador_ide_encomenda-1)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    /* Se nao existir um produto no sistema com o idp dado*/
    else if (idp > contador_idp_produto-1)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else{
        for (i=0; i < numero_produtos_en; i++){
            /* So entra na condicao quando encontrar o produto com idp dado na encomenda*/
            if (total_encomendas[ide].n_produtos[i].identificador == idp){
                total_encomendas[ide].numero_prd--;
                total_encomendas[ide].peso_total -= total_encomendas[ide].n_produtos[i].peso * 
                total_encomendas[ide].n_produtos[i].quantidade;
                total_produtos[idp].quantidade += total_encomendas[ide].n_produtos[i].quantidade;
                /* Elimina o produdo pedido dando aos produtos
                * com indice seguinte o seu indice e assim sucessivamente
                */
                for (j=i; j < numero_produtos_en; j++)
                    total_encomendas[ide].n_produtos[j] = total_encomendas[ide].n_produtos[j+1];
                total_encomendas[ide].n_produtos[j].identificador = 0;
                break;
            }
        }
    }
}

/* Comando: C
* Input: ide
* Descricao: Tem como output o custo da encomenda
*/
void custo_encomenda(){
    int ide, total=0, numero_prd_encomenda, i;

    scanf("%d", &ide);

    /* Utilizo a variavel numero_prd_encomenda para poupar tempo de processamento*/
    numero_prd_encomenda = total_encomendas[ide].numero_prd; 

    /* Condicao que verifica se a encomenda existe no sistema*/
    if (ide > contador_ide_encomenda-1)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        for(i=0; i < numero_prd_encomenda; i++)
            /* Calcula se o total adicionando o preco de todos os produtos multiplicados pelas suas quantidades*/
            total += total_encomendas[ide].n_produtos[i].preco * total_encomendas[ide].n_produtos[i].quantidade;
        printf("Custo da encomenda %d %d.\n", ide, total);
    }   
}

/* Comando: p
* Input: idp:preco
* Descricao: Altera o preco de um produto
*/
void altera_preco(){
    int idp, preco_novo, i, j;

    scanf("%d:%d", &idp, &preco_novo);

    /* Condicao que verifica se o produto existe no sistema*/
    if (idp > contador_idp_produto-1)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else{
        total_produtos[idp].preco = preco_novo;
        /* Muda o preco do produto se este estiver numa qualquer encomenda*/
        for (i=0; i < contador_ide_encomenda; i++){
            for (j=0; j < total_encomendas[i].numero_prd; j++){
                if (total_encomendas[i].n_produtos[j].identificador == idp){
                    total_encomendas[i].n_produtos[j].preco = preco_novo;
                }
            }
        }
    }
}

/* Comando: E
* Input: ide:idp
* Descricao: Lista a decricao e quantidade de um produto numa encomenda
*/
void dercricao_prd_en(){
    int ide, idp, flag=-1, numero_prd, i;

    scanf("%d:%d", &ide, &idp);

    /* Condicao que verifica se o produto e a encomenda existem no sistema*/
    if (ide > contador_ide_encomenda-1)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp > contador_idp_produto-1)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else{
        numero_prd = total_encomendas[ide].numero_prd;
        /* Condicao que ve se o produto existe ou nao na encomenda dada*/
        for (i=0; i < numero_prd; i++){
            if (idp == total_encomendas[ide].n_produtos[i].identificador){
                flag = i;
                break;
            }
        }
        /* Se o produto existir mas nao estiver numa encomenda*/
        if (flag == -1)
            printf("%s 0.\n", total_produtos[idp].string);
        /* Se o produto existir numa encomenda*/
        else
            printf("%s %d.\n", total_produtos[idp].string, total_encomendas[ide].n_produtos[flag].quantidade);
    }
}

/* Comando: m
* Input: idp
* Descricao: Lista o identificador da encomenda onde o produto dado ocorre mais vezes
*/
void listar_prd(){
    int idp, quantidade=0, i, posicao, flag=0, j;

    scanf("%d", &idp);

    /* Condicao que verefica se o produto existe no sistema*/ 
    if (idp > contador_idp_produto-1)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        /* Precorre todos os produtos de todas as encomendas*/
        for (i=0; i < contador_ide_encomenda; i++){
            for (j=0 ; j < total_encomendas[i].numero_prd; j++){
                if (total_encomendas[i].n_produtos[j].identificador == idp){
                    /* So entra nesta condicao se for o produto com maior quantidade que o ultimo
                    *  O ultimo produto a entrar nesta condicao tem a maior quantidade
                    */
                    if (total_encomendas[i].n_produtos[j].quantidade > quantidade){
                        quantidade = total_encomendas[i].n_produtos[j].quantidade;
                        posicao = i; /* Variavel que guarda a posicao do produto com maior quatidade*/
                        flag = 1;
                    }
                }

            }
        }
    }
    /* Condicao que verifica se o produto dado esta em alguma das encomendas*/
    if (flag == 1){
        printf("Maximo produto %d %d %d.\n", idp, total_encomendas[posicao].identificador_en, quantidade);
    }
}

void ordena(Produto vetor[], int esquerda, int meio, int direita) { 
    int i, j, k, indice_esquerda, indice_direita;
    Produto Esquerda[MAX_PRODUTOS], Direita[MAX_PRODUTOS]; /*Cria vetores temporarios para oredenar*/

    indice_esquerda = meio - esquerda + 1;
    indice_direita =  direita - meio;

    /* Copia informacao para os vetros Esquerda e Direita */
    for (i = 0; i < indice_esquerda; i++) 
        Esquerda[i] = vetor[esquerda + i];
    for (j = 0; j < indice_direita; j++) 
        Direita[j] = vetor[meio + 1+ j];

    /* Volta a passar a informacao dos vetores temporarios para o vetor a ordenar*/
    i = 0;
    j = 0;
    k = esquerda;
    while (i < indice_esquerda && j < indice_direita){
        if (Esquerda[i].preco <= Direita[j].preco){
            vetor[k] = Esquerda[i];
            i++;
        }
        else{
            vetor[k] = Direita[j];
            j++;
        }
        k++;
    }

    /* Copia os restantes elementos do vetor Esquerda*/
    while (i < indice_esquerda){
        vetor[k] = Esquerda[i];
        i++;
        k++;
    }

    /* Copia os restantes elementos do vetor Direita*/
    while (j < indice_direita) {
        vetor[k] = Direita[j];
        j++;
        k++;
    }
}

void ordena_partes(Produto vetor[], int esquerda, int direita){
    if (esquerda < direita){
        int meio;

        /* Calculo da metade do vetor*/
        meio = esquerda + (direita-esquerda)/2;

        /* Ordena a primeira e segunda metade do vetor*/
        ordena_partes(vetor, esquerda, meio);
        ordena_partes(vetor, meio+1, direita);

        ordena(vetor, esquerda, meio, direita);
    }
}


void printa_vetor(Produto vetor_ord[]){
    int i;

    printf("Produtos\n");

    for(i=0; i < contador_idp_produto; i++)
        printf("* %s %d %d\n", vetor_ord[i].string, vetor_ord[i].preco, vetor_ord[i].quantidade);
}

/* Comando: l
* Input: Nenhum
* Descricao: Ordena todos os produtos do sistema por ordem crescente de precos
*/
void lista_produtos(){
    int i;
    Produto vetor_ord[MAX_PRODUTOS];

    /* Copia o vetor que contem os produtos para um vetor novo*/
    for(i=0; i<contador_idp_produto; i++)
        vetor_ord[i] = total_produtos[i];

    /* Funcao que ordena o vetor*/
    ordena_partes(vetor_ord, 0, contador_idp_produto-1);
    /* Funcao que faz o print do vetor*/
    printa_vetor(vetor_ord);
}

void ordena_encomenda(Produto vetor[], int esquerda, int meio, int direita){
    int i, j, k, res, indice_esquerda, indice_direita;
    /*Cria vetores temporarios para oredenar*/
    Produto Esquerda[MAX_PRODUTOS_ENCOMENDAS], Direita[MAX_PRODUTOS_ENCOMENDAS];

    indice_esquerda = meio - esquerda + 1;
    indice_direita =  direita - meio;

    /* Copia informacao para os vetros Esquerda e Direita */
    for (i = 0; i < indice_esquerda; i++)
        Esquerda[i] = vetor[esquerda + i];
    for (j = 0; j < indice_direita; j++)
        Direita[j] = vetor[meio + 1+ j];

    /* Volta a passar a informacao dos vetores temporarios para o vetor a ordenar*/
    i = 0;
    j = 0;
    k = esquerda;
    while (i < indice_esquerda && j < indice_direita){
        /* Compraramos as strings
        * se forem iguais res = 0
        * se a string do vetor da esquerda vier primeiro no alfabeto r = negativo
        * se a string do vetor da direita vier primeiro no alfabeto r = positivo
        */
        res = strcmp(Esquerda[i].string, Direita[j].string);
        if (res <= 0)
            vetor[k++] = Esquerda[i++];
        else
            vetor[k++] = Direita[j++];
    }

    /* Copia os restantes elementos do vetor Esquerda*/
    while (i < indice_esquerda){
        vetor[k] = Esquerda[i];
        i++;
        k++;
    }

    /* Copia os restantes elementos do vetor Direita*/
    while (j < indice_direita) {
        vetor[k] = Direita[j];
        j++;
        k++;
    }
}

void ordena_partes_encomenda(Produto vetor[], int esquerda, int direita){
    if (esquerda < direita){
        int meio;

        /* Calcula o meio do vetor*/
        meio = esquerda + (direita-esquerda)/2;

        /* Ordena a primeira e segunda metade do vetor*/
        ordena_partes_encomenda(vetor, esquerda, meio);
        ordena_partes_encomenda(vetor, meio+1, direita);

        ordena_encomenda(vetor, esquerda, meio, direita);
    }
}

void printa_vetor_en(Produto vetor_ord[], int ide){
    int i, numero_prd;

    printf("Encomenda %d\n", ide);

    numero_prd = total_encomendas[ide].numero_prd;

    for(i=0; i < numero_prd ; i++)
        printf("* %s %d %d\n", vetor_ord[i].string, vetor_ord[i].preco, vetor_ord[i].quantidade);
}

/* Comando: L
* Input: ide
* Descricao: Ordena todos os produtos de uma eoncomenda por ordem alfabetica da descricao
*/
void lista_produtos_encomedas(){
    int ide, i, n_prd;
    Produto vetor_ord[MAX_PRODUTOS_ENCOMENDAS];

    scanf("%d", &ide);

    /* Condicao que verefica se existem encomendas com o ide dado*/
    if (ide > contador_ide_encomenda-1){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        n_prd = total_encomendas[ide].numero_prd;
        /* Copia o vetor com os produtos da encomenda para um vetor temporario*/
        for (i=0; i < n_prd; i++){
            vetor_ord[i] = total_encomendas[ide].n_produtos[i];
        }
        /* Funcao que ordena o vetor*/
        ordena_partes_encomenda(vetor_ord, 0, total_encomendas[ide].numero_prd-1);
        /* Funcao que faz print ao vetor ordenado*/
        printa_vetor_en(vetor_ord, ide);
    }
}

/*Descricao: Recebe um comando e redireciona para a funcao que o realiza
* Para para o programa usa se o comando x
*/
int main(){
    char comando = '\0';

    while(comando != 'x'){
        scanf("%c", &comando);
        switch(comando){
            case 'a':
                adiciona_prd();
                break;
            case 'q':
                adiciona_stck();
                break;
            case 'N':
                nova_encomeda();
                break;
            case 'A':
                adiciona_prd_encomenda();
                break;
            case 'r':
                remove_stk();
                break;
            case 'R':
                remove_prd_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                dercricao_prd_en();
                break;
            case 'm':
                listar_prd();
                break;
            case 'l':
                lista_produtos();
                break;
            case 'L':
                lista_produtos_encomedas();
                break;
        }
    }
    return 0;
}