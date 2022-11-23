#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX 10000
#define MAX_CHAR 63
#define MAX_PROD_ENC 200
#define MAX_ENC 500


typedef struct{
    int identificador;
    char descricao[MAX_CHAR];
    int preco;
    int peso;
    int qtd;
    int insideEncomenda;
}Produto;

typedef struct {
    Produto ENC[MAX];
    int IDE;
    int Weight;
    int Price;
}Encomenda;




void a(int i, Produto Stock[MAX]);
void q(Produto Stock[MAX], int SIZEofSTOCK);
void N(int NrEncomendas, Encomenda ListEnc[MAX_ENC]);
void A(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofE, int SIZEofSTOCK);
void r(Produto Stock[MAX], int SIZEofV);
void R(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofSTOCK, int SIZEofE);
void C(Encomenda ListENC[MAX_ENC], Produto Stock[MAX], int SIZEofE);
void p(Encomenda ListENC[MAX_ENC], Produto Stock[MAX], int SIZEofE, int SIZEofSTOCK);
void E(Encomenda ListENC[MAX_ENC], Produto Stock[MAX], int SIZEofSTOCK);
void mm(Encomenda ListaENC[MAX_ENC], Produto Stock[MAX], int SIZEofE);
void l(Produto Stock[MAX], int SIZEofV);
void L(Encomenda ListENC[MAX_ENC], int SIZEofE); 
/*void L(Encomenda ListENC[MAX_ENC], int left, int SIZEofE);
void merge(Produto ARR[MAX], int left, int m, int right); */



/* Esta variavel serve para guardar os produtos do stock */
/* E uma estrutura definida com preco, peso e quantidade */
Produto Stock[MAX] = {0};
/* A encomenda e uma estrtura definida com identificacao, um vetor que contem os produtos dessa encomenda, peso e preco */ 
Encomenda ListaE[MAX_ENC] = {0};
/* Variavel que conta o tamanho do stock */
int i = 0; /* SIZEofSTOCK */
/* Variavel que guarda o numero de encomendas que existem */
int m = 0; /* SIZEofE */


int main()
{
    char c;
    while ((c = getchar()) != 'x' && c != EOF)
    {
        switch(c)
        {
            case 'a':
                a(i, Stock);
                i += 1;
                break;
            case 'q':
                q(Stock, i);  
                break;
            case 'N':
                N(m, ListaE);
                m += 1;  
                break;
            case 'A':
                A(ListaE, Stock, m, i);   
                break;
            case 'r':
                r(Stock, i); 
                break;
            case 'R':
                R(ListaE, Stock, i, m); 
                break;
            case 'C':
                C(ListaE, Stock, m); 
                break;
            case 'p':
                p(ListaE, Stock, m, i); 
                break;
            case 'E':
                E(ListaE, Stock,i);  
                break;
            case 'm':
                mm(ListaE, Stock, m); 
                break;
            case 'l':
                l(Stock, i);  
                break;
            case 'L':
              /*  L(ListaE, 0, m); */ 
                L(ListaE, m); 
                break;
            default:
                break;
        }
    }
    return 0;
}

void a(int i, Produto Stock[MAX])

/* Guarda e coloca produtos dentro do vetor stock */

{
    Produto produto;
    scanf(" %[^:]:%d:%d:%d", produto.descricao, &produto.preco, &produto.peso, &produto.qtd);
    printf("Novo produto %d.\n", i);
    Stock[i].identificador = i;
    Stock[i].preco = produto.preco;
    Stock[i].peso = produto.peso;
    Stock[i].qtd = produto.qtd;
    strcpy(Stock[i].descricao,produto.descricao);
}

void q(Produto Stock[MAX], int SIZEofSTOCK)

/* Adiciona quantidades a um determinado produto */


{
    int idp, qtd, G = 1;
    scanf("%d:%d", &idp, &qtd);
        if (idp == Stock[idp].identificador && SIZEofSTOCK != 0)
        {
            Stock[idp].qtd += qtd;
            G = 0;
        } 
    if (G != 0)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
}

void N(int NrEncomendas, Encomenda ListEnc[MAX_ENC])

/* Imprime quando recebe uma nova encomenda*/
/*Guarda essa encomenda*/

{
    printf("Nova encomenda %d.\n", NrEncomendas);
    ListEnc[NrEncomendas].IDE = NrEncomendas;
}

void A(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofE, int SIZEofSTOCK) /*Se houver problemas e nesta merda*/

/* adiciona um produto a uma encomenda */

{
  int ide, idp, qtd;
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    if ( ide == 0 && SIZEofE == 0)    
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }    
    else if (ListEnc[ide].IDE != ide) /* Se esta encomenda existir */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp == 0 && SIZEofSTOCK == 0)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }      
    else if (Stock[idp].identificador != idp) /* Se este produto existe em stock */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);      
    }
    else  if (Stock[idp].qtd < qtd) /* Se a quantidade em stock e maior que a pedida */
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else
    {
        if (ListEnc[ide].Weight + (Stock[idp].peso * qtd) <= MAX_PROD_ENC) 
        {
            if (ListEnc[ide].ENC[idp].identificador == idp)
            {
                ListEnc[ide].Weight += Stock[idp].peso * qtd;
                ListEnc[ide].ENC[idp].qtd += qtd;
                Stock[idp].qtd -= qtd;
            }
            
            else
            {
                ListEnc[ide].ENC[idp] = Stock[idp];
                ListEnc[ide].ENC[idp].qtd = qtd;
                ListEnc[ide].Weight += Stock[idp].peso * qtd;
                Stock[idp].qtd -= qtd;
            }
        }
        else
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);    
        }
    }
}

void r(Produto Stock[MAX], int SIZEofV)

/* remove stock a um produto existente */

{
    int idp, quantidade;
    scanf("%d:%d", &idp, &quantidade);
    if (Stock[idp].identificador == idp && SIZEofV != 0)
    {        
        if (quantidade > Stock[idp].qtd)
        {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
        }
        else
        {
            Stock[idp].qtd = Stock[idp].qtd - quantidade;
        }
    } 
    else
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
}

void R(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofSTOCK, int SIZEofE) 

/* remove um produto de uma encomenda */

{
    int ide, idp;
    scanf("%d:%d", &ide, &idp);
    if (ListEnc[ide].IDE == ide && SIZEofE != 0)
    {
        if (Stock[idp].identificador == idp && SIZEofSTOCK != 0)
        {
            Stock[idp].qtd += ListEnc[ide].ENC[idp].qtd;
            ListEnc[ide].Weight -= ListEnc[ide].ENC[idp].qtd * Stock[idp].peso;
            ListEnc[ide].Price -= ListEnc[ide].ENC[idp].qtd * Stock[idp].preco;
            ListEnc[ide].ENC[idp].qtd = 0;
        }
        else
        {
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
    }
    else
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
}

void C(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofE)

/* calcula o custo de uma encomenda */

{
    int ide, i, STOTAL = 0, j = 0;
    scanf("%d", &ide);
    if (ListEnc[ide].IDE == ide && SIZEofE != 0)
    {
        for (i = 0; i < MAX; i++)
        {
            j = ListEnc[ide].ENC[i].identificador;
            STOTAL += Stock[j].preco * ListEnc[ide].ENC[i].qtd;
        }
        ListEnc[ide].Price = STOTAL;
    printf("Custo da encomenda %d %d.\n", ide, STOTAL);
    }
    else
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    
}



void p(Encomenda ListaENC[MAX_ENC] ,Produto Stock[MAX], int SIZEofE, int SIZEofSTOCK)

/* altera o pre?o de um produto existente no sistema */

{
    int idp, preco, i, j;
    scanf("%d:%d", &idp, &preco);
    if (Stock[idp].identificador == idp)
    {
        Stock[idp].preco = preco;
        for (j = 0; j < SIZEofE; j++)
        {
            for ( i = 0; i < SIZEofSTOCK; i++)
            {
                if (ListaENC[j].ENC[i].identificador == idp)
                {
                    ListaENC[j].ENC[i].preco = preco;
                }
            }
        }
    }
    else
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
}

void E(Encomenda ListENC[MAX_ENC], Produto Stock[MAX], int SIZEofSTOCK)

/*retorna a descri??o e a quantidade de um produto numa dada encomenda */

{
    int ide, idp;
    scanf("%d:%d", &ide, &idp);
    if (ListENC[ide].IDE == ide)
    {
        if (Stock[idp].identificador == idp && SIZEofSTOCK != 0)
        {
            printf("%s %d.\n", Stock[idp].descricao, ListENC[ide].ENC[idp].qtd);
        }
        else
        {
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
    }
    else
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    
}

void mm(Encomenda ListEnc[MAX_ENC], Produto Stock[MAX], int SIZEofE)

/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes */

{
    int idp, k = 0, maximo = 0, soma = 0, G = 0, ide = 0;
    scanf("%d", &idp);
    if (Stock[idp].identificador == idp)
    {    
        for (k = 0; k < SIZEofE;  k++)
        {
            if (ListEnc[k].ENC[idp].identificador == idp)
            {
                soma = ListEnc[k].ENC[idp].qtd;
                G = k;        
            }
            if (soma > maximo)
            {
                maximo = soma;
                ide = G;
            }
        }
        if (ListEnc[ide].ENC[idp].qtd > 0)
        {   
            printf("Maximo produto %d %d %d.\n", idp, ide, maximo);
        }
    }
    else
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
}

void l(Produto Stock[MAX], int SIZEofSTOCK)

/* lista todos os produtos existentes no sistema por ordem crescente de pre?o */

{     
    int i, j, k;
    Produto ARR[MAX], last;
    printf("Produtos\n");
    for (k = 0; k < SIZEofSTOCK; k++)
    {
        ARR[k] = Stock[k];
    }
    for (i = 1; i < SIZEofSTOCK; i++)
    {
        last = ARR[i];
        j = i -1;
        while (j >= 0 && last.preco < ARR[j].preco)
        {
            ARR[j + 1] = ARR[j];
            j--;
        }
        ARR[j + 1] = last;
    }
    for (i = 0; i < SIZEofSTOCK; i++)
        printf("* %s %d %d\n", ARR[i].descricao, ARR[i].preco, ARR[i].qtd);
}

void L(Encomenda ListENC[MAX_ENC], int SIZEofE)

/* lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */   

{
    int i, j, k, ide;
    Produto ARR[MAX], last;
    scanf("%d", &ide);
    
    if (ListENC[ide].IDE == ide && SIZEofE > 0)
    {
        printf("Encomenda %d\n", ide);
        for (k = 0; k < MAX; k++)
        {
            ARR[k] = ListENC[ide].ENC[k];
            strcpy(ARR[k].descricao, ListENC[ide].ENC[k].descricao);
        }
        for (i = 1; i < MAX; i++)
        {
            strcpy(last.descricao, ARR[i].descricao);
            j = i - 1;
            {
                while (j >= 0 && last.descricao[0] < ARR[j].descricao[0])
                {
                    ARR[j + 1] = ARR[j];
                    j--; 
                }
                ARR[j + 1] = last;
            }
        }
        for (i = 0; i < MAX; i++)
        {
            if (ARR[i].identificador >= 0 && ARR[i].qtd > 0)
                printf("* %s %d %d\n", ARR[i].descricao, ARR[i].preco, ARR[i].qtd);
        }
    }
    else
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
}


