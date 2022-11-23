#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Definicao das constantes atraves da diretiva de pre processamento*/
#define MAXDESCRICAO 64 /*uma string nao vazia com um maximo de 63 caracteres*/
#define MAXPRODUTO 10000 /*existiram no maximo de 10 000 produtos diferentes*/
#define MAXENCOMENDA 500 /*existiram no maximo 500 encomendas*/
#define MAXPESO 200 /*cada encomenda podera ter no maximo 200 unidades de peso*/

/* Estrutura do produto*/
typedef struct produto
{
    char descricao[MAXDESCRICAO];
    int preco;
    int peso;
    int stock;
    int identificador; /*identificador do produto criado*/
} produto;

/* Estrutura da encomenda*/
typedef struct encomenda
{
    int nr_produtos; /*vai servir para percorrer todas as encomendas*/
    int peso_acum;
    produto prod[MAXPESO];
}encomenda;

produto produtos[MAXPRODUTO];    
encomenda encomendas[MAXENCOMENDA];

/* A funcao 'a' adiciona um novo produto ao sistema */
int a(char descricao[MAXDESCRICAO], int preco, int peso, int qtd, int idp)
{
    produto prod;
    strcpy (prod.descricao, descricao);
    prod.preco = preco;
    prod.peso = peso;
    prod.stock=qtd;
    prod.identificador=idp;
    produtos[idp]=prod;
    printf("Novo produto %d.\n", idp);
    return ++idp;/*vai incrementando o idp, aumentando o idpmax*/
}

/* funcao auxiliar da funcao l */
void k(int idpmax)
{   
    int i;
    printf("Inventario atual:\n");
    for(i=0; i<idpmax; i++)
        printf("Descri?ao: %s  Preco:%d  Peso:%d  Qtd:%d\n", produtos[i].descricao, produtos[i].preco, produtos[i].peso, produtos[i].stock);
}

/* A funcao 'q' adiciona stock a um produto existente no sistema, ou seja se existir um produto criado
 com o identificador inserido, a funcao vai aumentar a qtd inserida no produto desejado. */
void q(int idpmax, int qtd, int idp)
{
    if (idp>=idpmax)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        produtos[idp].stock += qtd; /*adiciona a qtd desejada ao stock do produto*/
}   

/* Esta funcao inicializa as variaveis presentes nas structs */
void init_struct()
{
    int i;
    for(i=0; i<MAXENCOMENDA; i++)
    {
        encomendas[i].nr_produtos=0;
        encomendas[i].peso_acum=0; 
    }
}

/* A funcao 'A' adiciona um produto a uma encomenda, mas se esse produto ja existir na encomenda
adiciona a nova qtd a qtd existente. */
void A(int idpmax, int idp, int idemax, int ide, int qtd)
{
    int i;
    produto novo_produto;
    if (ide>=idemax)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp>=idpmax)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (qtd>produtos[idp].stock)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if ((encomendas[ide].peso_acum + (qtd * produtos[idp].peso))> MAXPESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else
    {
        encomendas[ide].peso_acum += qtd * produtos[idp].peso; /*adiciona o peso dos produtos<idp> ao peso acumulado na encomenda*/
        produtos[idp].stock -= qtd;  /*retira do stock a qtd pedida para colocar na encomenda */
        for(i=0; i<encomendas[ide].nr_produtos; i++)  /*vai percorrer os produtos dentro das encomendas*/
        {
            if (encomendas[ide].prod[i].identificador==produtos[idp].identificador) /*quando dentro da encomenda se encontra o produto com o idp que queremos adicionar salta fora 
            e vai para a condicao do else adicionar a qtd desejada ao produto j? existente na encomenda*/
                break;
        }
        if (i==encomendas[ide].nr_produtos) 
        {
            encomendas[ide].prod[i] = produtos[idp];                             /*criar uma encomenda com produtos l? dentro*/
            encomendas[ide].nr_produtos += 1;
            strcpy (novo_produto.descricao, produtos[idp].descricao);
            novo_produto.preco = produtos[idp].preco;
            novo_produto.peso = produtos[idp].peso;
            novo_produto.stock=qtd;
            novo_produto.identificador=produtos[idp].identificador;
            encomendas[ide].prod[i] = novo_produto;
        }
        else
            encomendas[ide].prod[i].stock += qtd;
    }
}

/* A funcao 'r' remove stock a um produto existente*/
void r(int idpmax, int qtd, int idp)
{
    if (idp>=idpmax)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (qtd>produtos[idp].stock) 
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        produtos[idp].stock -= qtd; /*retira a qtd desejada ao stock do produto*/
}

/* A funcao 'R' remove um produto de uma encomenda */
void R(int idpmax, int idp, int idemax, int ide)
{
    int i;
    if(ide>=idemax)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if(idp>=idpmax)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else
    {
        for(i=0; i<encomendas[ide].nr_produtos; i++) 
        {
            if(encomendas[ide].prod[i].identificador == produtos[idp].identificador) /*quando dentro da encomenda se encontra o produto com o idp que queremos retirar*/
            {
                produtos[idp].stock += encomendas[ide].prod[i].stock; /*retorna uma x qtd do produto que se tinha na encomenda de volta ao stock atual desse produto */
                encomendas[ide].peso_acum -= (encomendas[ide].prod[i].stock * encomendas[ide].prod[i].peso); /*adiciona a qtd desejada ao stock do produto*/
                encomendas[ide].nr_produtos-=1; /*decrementa o nr de produtos numa encomenda*/
                for (; i<encomendas[ide].nr_produtos; i++) /*vai continuar a percorrer os elementos da encomenda*/
                    encomendas[ide].prod[i] = encomendas[ide].prod[i+1];  /*uma vez que foi removido x produto da encomenda iria ficar um "espaco" vazio*/
            }   
        }
    }
}

/* A funcao 'C' calcula o custo de uma encomenda*/
void C(int idemax, int ide)
{
    int i, custototal=0;
    if (ide>=idemax)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);  
    else 
    {
        for (i=0; i<encomendas[ide].nr_produtos; i++)
            custototal += encomendas[ide].prod[i].stock * encomendas[ide].prod[i].preco; /*multiplica o preco de um produto numa encomenda pela sua qtd presente nessa mesma encomenda e vai guardando o valor*/
        printf("Custo da encomenda %d %d.\n", ide, custototal);
    }   
}

/* A funcao 'p' altera o preco de um produto existente no sistema*/
void p(int idp, int idpmax, int idemax, int preco)
{
    int corre_ide, corre_prod;
    if (idp>=idpmax)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp); 
    else
    {
        produtos[idp].preco=preco; /*altera logo diretamente o preco de um produto sem estar dentro de uma encomenda*/
        for(corre_ide=0; corre_ide<idemax; corre_ide++)
        {
            for(corre_prod=0; corre_prod<encomendas[corre_ide].nr_produtos; corre_prod++)
            {
                if (encomendas[corre_ide].prod[corre_prod].identificador == produtos[idp].identificador)/*quando dentro da encomenda se encontra o produto com o idp que queremos*/
                    encomendas[corre_ide].prod[corre_prod].preco=preco;/*altera  o preco de um produto que esta dentro de uma encomenda*/
            }
        }
    }
}

/* A funcao 'E' lista a descricao e a qtd de um produto numa encomenda*/
void E(int idpmax, int idemax, int ide, int idp)
{
    int i, order_stock=0;
    if (idp>=idpmax)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp); 
    else if (ide>=idemax)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide); 
    else
        /*printf("%s %d.\n", encomendas[0].prod[0].descricao, order_stock);*/
    {
        for (i=0; i<encomendas[ide].nr_produtos; i++)
        {
            if (encomendas[ide].prod[i].identificador==produtos[idp].identificador)/*quando dentro da encomenda se encontra o produto com o idp que queremos*/
            {
                order_stock = encomendas[ide].prod[i].stock; /*guarda o stock de x <idp> dentro de uma encomenda */
                break;
            }
        }
        printf("%s %d.\n", produtos[idp].descricao, order_stock);
    }
}

/*A funcao 'm' lista o identificador da encomenda em que o produto dado ocorre mais vezes. 
Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor identificador.*/
void m(int idp, int idpmax, int idemax)
{
    int corre_ide, corre_prod, ide=0, qtd_max=0;
    if(idp>=idpmax)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else
    {
        for(corre_ide=0; corre_ide<idemax; corre_ide++) 
        {
            for(corre_prod=0; corre_prod<encomendas[corre_ide].nr_produtos; corre_prod++) 
            {
                if(encomendas[corre_ide].prod[corre_prod].identificador==produtos[idp].identificador)/*quando dentro da encomenda se encontra o produto com o idp que queremos*/
                {
                    if(encomendas[corre_ide].prod[corre_prod].stock > qtd_max) {
                        qtd_max = encomendas[corre_ide].prod[corre_prod].stock; /*vai guardadndo a maior qtd de um <idp> dentro de uma encomenda */
                        ide = corre_ide;
                    }
                }
            }
        }
        if (qtd_max!=0) /*Nao lista nada caso o produto <idp> nao ocorra em nenhuma encomenda, ou caso nao haja encomendas*/
            printf("Maximo produto %d %d %d.\n", idp, ide, qtd_max);
    }
}

/*Algoritmo auxiliar da funcao l - merge, Gerar um vector ordenado a partir de dois vectores ordenados, usando um auxiliar*/
void merge(produto prod[], int left, int m, int right)
{ 
    int i, j, k;
    produto aux[MAXPRODUTO];
    for (i = m+1; i > left; i--)      /*Constroi o vetor auxiliar*/ 
        aux[i-1] = prod[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = prod[j+1];
    for (k = left; k <= right; k++)   /*Vai escolhendo os elementos das pontas de forma a ordenar o vetor prod[]*/
    {
        if ((aux[j].preco < aux[i].preco) || i > m)
            prod[k] = aux[j--];
        else
            prod[k] = aux[i++];
    }
}

void mergesort(produto prod[], int left, int right)
{
    int m;

    if(left<right) 
        m = ((left+right)/2); /*Find the middle point to divide the array into two halves*/
    else  
        return;   /*senao da  segmentation fault*/
    mergesort(prod, left, m);  /*Call mergeSort for first half*/    /*recursividade*/   
    mergesort(prod, m+1, right);  /*Call mergeSort for secomd half*/     
    merge(prod, left, m, right);   /*Merge the two halves sorted in step 2 and 3*/
}

/* A funcao 'l' lista todos os produtos existentes no sistema por ordem crescente de preco. Se houver 2 ou mais
produtos com o mesmo preco, devera imprimir esses por ordem crescente de id de produto */
void l(int left, int right){   
    int i;
    produto prod[MAXPRODUTO];
    for (i=left; i<=right; i++)
        prod[i] = produtos[i];

    mergesort(prod, left, right);

    printf("Produtos\n");
    for(i=left; i<=right; i++)
        printf("* %s %d %d\n", prod[i].descricao, prod[i].preco, prod[i].stock);
}

/* A funcao 'L' lista todos os produtos de uma encomendsa por ordem alfabetica da descricao.*/                   
void L(int idemax, int ide, int idpmax){   
    int i;
    if (ide>=idemax)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);    
    else
    {
        /*a completar*/

        printf("Encomenda %d\n", idemax);
        for(i = 0; i <= idpmax; i++)
            printf("* %s %d %d\n", encomendas[ide].prod[i].descricao, encomendas[ide].prod[i].preco, encomendas[ide].prod[i].stock);
    }
}

int main(){
    char action, descricao[MAXDESCRICAO];
    int preco=0, peso, qtd;
    int idpmax=0, idp, idemax=0, ide;
    init_struct();

    while (1)
    {
        scanf("%c", &action);
        switch(action)
        {
            case'a':
                scanf(" %[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
                idpmax = a(descricao, preco, peso, qtd, idpmax);
                break;
            case 'k':
                k(idpmax);
                break;
            case 'q':
                scanf(" %d:%d", &idp, &qtd);
                q(idpmax, qtd, idp);
                break;
            case 'N': /* A funcao 'N' adiciona uma nova encomenda ao sistema */
                printf("Nova encomenda %d.\n", idemax++); /*vai incrementando o ide, aumentando o idemax*/
                break;
            case 'A':
                scanf(" %d:%d:%d", &ide, &idp, &qtd);
                A(idpmax, idp, idemax, ide, qtd);
                break;
            case 'r':
                scanf(" %d:%d", &idp, &qtd);
                r(idpmax, qtd, idp);
                break;
            case 'R':
                scanf(" %d:%d", &ide, &idp);
                R(idpmax, idp, idemax, ide);
                break;
            case 'C':
                scanf(" %d", &ide);
                C(idemax, ide);
                break;
            case 'p':
                scanf(" %d:%d", &idp, &preco);
                p(idp, idpmax, idemax, preco);
                break;   
            case 'E':
                scanf(" %d:%d", &ide, &idp);
                E(idpmax, idemax, ide, idp);
                break;
            case 'm':
                scanf(" %d", &idp);
                m(idp, idpmax, idemax);
                break;
            case 'l':
            /*exemplo na main .....merge(arr, 0, arr_size - 1) <---- tirar dps*/
                l(0, idpmax-1);
                break;
            case 'L':
                L(idemax, ide, idpmax);
                break;
            case 'x':
                return 0;
        } 
    }
    return 0;
}

