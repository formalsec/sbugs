#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Constante que indica o numero maximo de caracteres da descricao de um produto */
#define MAX_CHAR 64
/* Constante que indica o numero maximo de produtos no sistema */
#define MAX_PROD 10000
/* Constante que indica o numero maximo de encomendas no sistema */
#define MAX_ENC 500
/* Constante que indica o numero maximo de produtos numa encomenda */
#define MAX_ENC_PROD 200
/* Constante que indica o peso maximo de uma encomenda */
#define MAX_PESO_ENC 200

/* Definicao da estrutura produto */
typedef struct produto
{
    int idp;
    char descricao[MAX_CHAR];
    int preco;
    int peso;
    int qtd;
}produto;

/* Definicao da estrutura encomenda */
typedef struct encomenda
{
    int ide;
    int conta_prod_enc;
    produto prod[MAX_ENC_PROD];
} encomenda;

/* Prototipos de funcoes */
void init_inventario_prod();
void init_inventario_enc();
encomenda init_enc();
void adiciona_stock(int idp, int qtd);
void adiciona_prod_enc(int ide, int idp, int qtd);
int peso_enc(encomenda enc);
void remove_stock_prod(int idp, int qtd);
void remove_prod_enc(int ide, int idp);
void custo_enc(int ide);
void altera_preco(int idp, int preco);
void lista_descricao_qtd(int ide, int idp);
void maior_quantidade(int idp);
void ordena_prods();
void ordena_prods_enc(int ide);
void mergeSort(produto arr[], int l, int r, int valor);
void merge(produto arr[], int l, int m, int r, int valor);

/* Vetor de produtos que representa o inventario de produtos */
produto inventario_prod[MAX_PROD], inventario_prod_ord[MAX_PROD];
/* Vetor de encomendas que representa o inventario de encomendas */
encomenda inventario_enc[MAX_ENC];
/* Variaveis que guardam o numero de produtos e de encomendas existentes no sistema, respetivamente */
int conta_prod=0, conta_enc=0;

int main()
{
    /* Variavel que guardar o comando inserido pelo utilizador */
    int comando;
    /* Variaveis que guardam o valor do idp, da qtd, do ide e do preco inseridos pelo utilizador */
    int idp, qtd, ide, preco;
    /* Variavel produto generica */
    produto prod;
    /* Variavel encomenda generica */
    encomenda enc;

    /* Inicializacao do inventario dos produtos */
    init_inventario_prod();
    /* Inicializacao do inventario das encomendas */
    init_inventario_enc();


    while((comando=getchar())!=EOF)
    {
        /* Seleciona a operacao correta para cada comando inserido */
        switch(comando)
        {
            case 'a':
                prod.idp=conta_prod;
                conta_prod++;

                scanf(" %[^:]:%d:%d:%d", prod.descricao, &prod.preco, &prod.peso, &prod.qtd);
                inventario_prod[prod.idp]=prod;

                printf("Novo produto %d.\n", prod.idp);
                break;

            case 'q':
                scanf(" %d:%d", &idp, &qtd);
                adiciona_stock(idp, qtd);
                break;

            case 'N':
                enc = init_enc();

                inventario_enc[enc.ide]=enc;

                conta_enc++;
                printf("Nova encomenda %d.\n", enc.ide);
                break;

            case 'A':
                scanf(" %d:%d:%d", &ide, &idp, &qtd);
                adiciona_prod_enc(ide, idp, qtd);
                break;

            case 'r':
                scanf(" %d:%d", &idp, &qtd);
                remove_stock_prod(idp, qtd);
                break;

            case 'R':
                scanf(" %d:%d", &ide, &idp);
                remove_prod_enc(ide, idp);
                break;

            case 'C':
                scanf(" %d", &ide);
                custo_enc(ide);
                break;

            case 'p':
                scanf(" %d:%d", &idp, &preco);
                altera_preco(idp, preco);
                break;

            case 'E':
                scanf(" %d:%d", &ide, &idp);
                lista_descricao_qtd(ide, idp);
                break;

            case 'm':
                scanf(" %d", &idp);
                maior_quantidade(idp);
                break;

            case 'l':
                ordena_prods();
                break;

            case 'L':
                scanf(" %d", &ide);
                ordena_prods_enc(ide);
                break;

            case 'x':
                return EXIT_SUCCESS;
        
            default:
                fprintf(stderr, "Invalid input!\n");
                return EXIT_FAILURE;
        }
        getchar();
    }
    return 0;
}

/* Funcao que inicializa o idp dos produtos do inventario a -1 */
void init_inventario_prod()
{
    int i;
    for(i=0; i<MAX_PROD; i++)
    {
        inventario_prod[i].idp=-1;
    }
}

/* Funcao que inicializa o ide das encomendas do inventario a -1 */
void init_inventario_enc()
{
    int i;
    for(i=0; i<MAX_ENC; i++)
    {
        inventario_enc[i].ide=-1;
    }
}

/* Funcao que inicializa o idp de todos os produtos de uma encomenda a -1
e a contagem dos seus produtos a 0 */
encomenda init_enc()
{
    /* Variavel encomenda generica */
    encomenda enc;
    int i;

    enc.ide=conta_enc;
    enc.conta_prod_enc = 0;

    for(i=0; i<MAX_ENC_PROD; i++)
    {
        enc.prod[i].idp=-1;
    }
    return enc;
}

/* Funcao que adiciona stock a um produt */
void adiciona_stock(int idp, int qtd)
{
    if(inventario_prod[idp].idp==idp)
    {
        inventario_prod[idp].qtd+=qtd;
    }
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

/* Funcao que adiciona um produto a uma encomenda */
void adiciona_prod_enc(int ide, int idp, int qtd)
{
    if(inventario_enc[ide].ide==-1)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if(inventario_prod[idp].qtd<qtd)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if(peso_enc(inventario_enc[ide])+inventario_prod[idp].peso*qtd>MAX_PESO_ENC)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else
    {
        /* A vari?vel index_enc_prod representa o indice no vetor dos produtos de uma encomenda
        onde se encontra um determinado produto */
        int i, index_enc_prod;
        for(i=0; i < inventario_enc[ide].conta_prod_enc; i++)
        {
            if(inventario_enc[ide].prod[i].idp==idp)
            {
                inventario_enc[ide].prod[i].qtd+=qtd;
                inventario_prod[idp].qtd-=qtd;
                return;
            }
        }
    
        index_enc_prod = inventario_enc[ide].conta_prod_enc;

        inventario_enc[ide].prod[index_enc_prod] =inventario_prod[idp];
        inventario_enc[ide].conta_prod_enc++;

        inventario_prod[idp].qtd -= qtd;
        inventario_enc[ide].prod[index_enc_prod].qtd = qtd;
        return;
    }   
}

/* Funcao que calcula o peso de uma encomenda */
int peso_enc(encomenda enc)
{
    /* A variavel peso_t guarda o valor do peso total de uma encomenda */
    int i=0, peso_t=0;
    for(i=0; i < enc.conta_prod_enc; i++)
    {
        peso_t+=inventario_enc[enc.ide].prod[i].peso*inventario_enc[enc.ide].prod[i].qtd;
    }
    return peso_t;
}

/* Funcao que remove o stock de um produto do sistema */
void remove_stock_prod(int idp, int qtd)
{
    if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if(inventario_prod[idp].qtd<qtd)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
        inventario_prod[idp].qtd-=qtd;
    }
}

/* Funcao que remove um produto de uma encomenda */
void remove_prod_enc(int ide, int idp)
{
    if(inventario_enc[ide].ide==-1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
    {
        int i, j;
        for(i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
        {
            if(inventario_enc[ide].prod[i].idp==idp)
            {
                inventario_prod[idp].qtd += inventario_enc[ide].prod[i].qtd;

                for(j = i; j < inventario_enc[ide].conta_prod_enc; j++)
                {
                    inventario_enc[ide].prod[j] = inventario_enc[ide].prod[j+1];
                }

                inventario_enc[ide].conta_prod_enc--;
                return;
            }
        }                
    }
}

/* Funcao que calcula o custo de uma encomenda */
void custo_enc(int ide)
{
    if(inventario_enc[ide].ide==-1)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        /* A variavel custo guarda o valor do custo total de uma encomenda */
        int i, custo=0;
        
        for(i=0; i < inventario_enc[ide].conta_prod_enc; i++)
        {
            custo+=inventario_enc[ide].prod[i].preco*inventario_enc[ide].prod[i].qtd;
        }

        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

/* Funcao que altera o pre?o de um produto existente no sistema */
void altera_preco(int idp, int preco)
{
    if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        int i,j;
        inventario_prod[idp].preco=preco;

        for(i = 0; i < conta_enc; i++)
        {
            for(j = 0; j < inventario_enc[i].conta_prod_enc; j++)
            {
                if(inventario_enc[i].prod[j].idp==idp)
                {
                    inventario_enc[i].prod[j].preco=preco;
                    break;
                }
            }
        }
    }
}

/* Funcao que retorna a descri??o e a quantidade de um produto numa dada encomenda */
void lista_descricao_qtd(int ide, int idp)
{
    if(inventario_enc[ide].ide==-1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        int i;
        for(i=0; i < inventario_enc[ide].conta_prod_enc; i++)
        {
            if(inventario_enc[ide].prod[i].idp==idp)
            {
                printf("%s %d.\n", inventario_enc[ide].prod[i].descricao, inventario_enc[ide].prod[i].qtd);
                return;
            }
        }
        printf("%s 0.\n", inventario_prod[idp].descricao);
    }
}

/* Funcao que retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void maior_quantidade(int idp)
{
    /* A variavel maior guarda a maior quantidade de um produto no sistema de encomendas 
    e a variavel ide guarda o identificador da encomenda onde essa quantidade esta */
    int maior = 0, ide;
    /* A vari?vel afirmativo indica se a encomenda com ide predefinido tem o produto */
    int i, j, afirmativo=0;

    if(inventario_prod[idp].idp==-1)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        for(i=0; i < conta_enc; i++)
        {
            for(j=0; j < inventario_enc[i].conta_prod_enc; j++)
            {
                if (inventario_enc[i].prod[j].idp==idp && inventario_enc[i].prod[j].qtd>maior)
                {
                    maior=inventario_enc[i].prod[j].qtd;
                    ide=i;
                    afirmativo=1;
                }
                if (inventario_enc[i].prod[j].idp==idp && inventario_enc[i].prod[j].qtd==maior && i<=ide)
                {
                    ide=i;
                    afirmativo=1;
                }
            }
        }
        if(afirmativo==1)
        {
            printf("Maximo produto %d %d %d.\n", idp, ide, maior);
        }
    }
}

/* Funcao que lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void ordena_prods()
{
    /* Vetor onde vai ser colocada uma copia do inventario para ser ordenado */
    produto produtos[MAX_PROD];
    /* Variavel produto generica */
    produto prod;
    int i;

    for(i=0; i<conta_prod; i++)
    {
        produtos[i]=inventario_prod[i];
    }

    mergeSort(produtos, 0, conta_prod-1, 0);


    printf("Produtos\n");
    for (i = 0; i < conta_prod; i++)
    {
        prod=produtos[i];
        printf("* %s %d %d\n", prod.descricao, prod.preco, prod.qtd);
    }
}

/* Funcao que lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void ordena_prods_enc(int ide)
{
    if(inventario_enc[ide].ide==-1)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        /* Vetor onde vai ser colocada uma copia dos produtos de uma encomenda para serem ordenados */
        produto prods_enc[MAX_ENC_PROD];
        /* Variavel produto generica */
        produto prod;
        int i, j=0;
        
        for(j=0; j<inventario_enc[ide].conta_prod_enc; j++)
        {
            prods_enc[j]=inventario_enc[ide].prod[j];
        }
            
        mergeSort(prods_enc, 0, inventario_enc[ide].conta_prod_enc-1, 1);
        
        printf("Encomenda %d\n", ide);
        for (i = 0; i < inventario_enc[ide].conta_prod_enc; i++)
        {
            prod=prods_enc[i];
            printf("* %s %d %d\n", prod.descricao, prod.preco, prod.qtd);
        }
    }

}

/* Funcao que ordena produtos por ordem crescente de pre?o ou
por ordem alfab?tica da descri??o dependendo do valor */
void mergeSort(produto arr[], int l, int r, int valor) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2;
        
        mergeSort(arr, l, m, valor); 
        mergeSort(arr, m+1, r, valor); 
  
        merge(arr, l, m, r, valor); 
        
    } 
} 

/* Funcao que ordena produtos por ordem crescente de pre?o ou
por ordem alfab?tica da descri??o dependendo do valor */
void merge(produto arr[], int l, int m, int r, int valor) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* Vetores para guardar uma copia do array que a funcao recebe */
    produto L[MAX_PROD], R[MAX_PROD]; 
    
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1+ j]; 
    }
  
    i = 0; 
    j = 0;  
    k = l;
    
    while (i < n1 && j < n2) 
    { 
        if (L[i].preco <= R[j].preco && valor==0) 
        { 
            arr[k] = L[i]; 
            i++; 
        }
        else if (strcmp(L[i].descricao, R[j].descricao)<=0 && valor==1) 
        { 
            arr[k] = L[i]; 
            i++; 
        }
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
