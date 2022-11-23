#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_IDP 10000           /*numero maximo de produtos*/
#define MAX_DESCRICAO 64        /*numero maximo de caracteres mais o \0*/
#define MAX_IDE 500             /*numero maximo de encomendas*/
#define MAX_PESO 200            /*numero maximo de unidades de peso numa encomenda*/

typedef struct {                /*estrutura do produto*/
    int identificador;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int stock;
    int vetor[MAX_IDE];
}produto;

typedef struct {                /*estrutura do produto sem o preco nem o peso dentro da encomenda*/
    int identificador;
    int quantidade;
}qtd_prod;

typedef struct {                /*estrutura da encomenda*/
    int identificador;
    int peso_total;
    qtd_prod prod_encom[MAX_PESO];
    int contador;               /*contador que serve para colocar os produtos ddentro das encomendas*/
}encomenda;

produto produtos[MAX_IDP];      /*sistema*/
encomenda encomendas[MAX_IDE];  /*encomendas*/

int conta_prod = 0;             /*identificador dos produtos*/
int conta_encom = 0;            /* identificador das encomendas*/

void comando_a();               /*declaracao das funcoes*/
void comando_q();
void comando_N();
void comando_A();
void comando_r();
void comando_R();
void comando_C();
void comando_p();
void comando_E();
void comando_m();
int comando_l();
void comando_L();
void mergesort_l(produto a[], int left, int right);
void merge_l(produto a[], int left, int m, int right);
void mergesort_L(produto a[], int left, int right);
void merge_L(produto a[], int left, int m, int right);

int main()
{   
    char c=getchar();
    encomendas[0].identificador=-1;
    produtos[0].identificador=-1;
    while(c!='x')
    {
        switch(c)
        {
            case 'a':
                comando_a();
                break;          
            case 'q':
                comando_q();
                break;    
            case 'N':
                comando_N();
                break;           
            case 'A':
                comando_A();
                break;
            case 'r':
                comando_r();
                break;              
            case 'R':
                comando_R();
                break;            
            case 'C':
                comando_C();
                break;           
            case 'p':
                comando_p();
                break;           
            case 'E':
                comando_E();
                break;           
            case 'm':
                comando_m();
                break;           
            case 'l':
                comando_l();
                break;           
            case 'L':
                comando_L();
                break;            
        }
        c=getchar();
    }
    return 0;
}

/* adiciona um novo produto ao sistema */
void comando_a()
{
    scanf(" %[^:]:%d:%d:%d", produtos[conta_prod].descricao, &produtos[conta_prod].preco, &produtos[conta_prod].peso, &produtos[conta_prod].stock);
    produtos[conta_prod].identificador=conta_prod;
    printf("Novo produto %d.\n", produtos[conta_prod].identificador);
    conta_prod++;
}

/* adiciona stock a um produto existente */
void comando_q()
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if  (produtos[idp].identificador==idp)      /*verificar se existe o produto*/
        produtos[idp].stock+=qtd;
    else
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
}

/* cria uma nova encomenda */
void comando_N()
{
    encomendas[conta_encom].identificador=conta_encom;
    printf("Nova encomenda %d.\n", encomendas[conta_encom].identificador);
    conta_encom++;
}

/* adiciona um produto a uma encomenda */
void comando_A()
{
    int ide, idp, qtd, i, conta, e;
    scanf(" %d:%d:%d", &ide, &idp, &qtd);
    if (encomendas[ide].identificador==ide)     /*verifica se existe encomenda*/
    {
        if (produtos[idp].identificador==idp)       /*verifica se existe produto*/
        {
            if (produtos[idp].stock - qtd >= 0)     /*verifica se existe quantidade suficiente de produto*/
            {
                if (produtos[idp].peso * qtd + encomendas[ide].peso_total<=200)     /*verifica se o peso total da encomenda nao excede 200 unidades*/
                {
                    for(i=0;i<MAX_PESO;i++)
                    {
                        if (encomendas[ide].prod_encom[i].identificador==idp)       /*verifica se ja existia o produto na encomenda, aumentando lhe assim a quantidade na encomenda*/
                        {
                            encomendas[ide].prod_encom[i].quantidade+=qtd;
                            produtos[idp].vetor[ide]+=qtd;
                        }
                        else    
                            {
                               for(e=0;e<MAX_PESO;e++)
                               {
                                    if (encomendas[ide].prod_encom[e].quantidade==0)        /*verifica se existe algum produto na encomenda com 0 de quantidade para ser substituido*/
                                    {
                                        encomendas[ide].prod_encom[e].identificador=idp;
                                        encomendas[ide].prod_encom[e].quantidade=qtd;
                                    }
                                    else
                                    {
                                        conta=encomendas[ide].contador;
                                        encomendas[ide].prod_encom[conta].identificador=idp;
                                        encomendas[ide].prod_encom[conta].quantidade=qtd;
                                        encomendas[ide].contador++;
                                    }
                               }
                               produtos[idp].vetor[ide]=qtd;
                            }
                    }
                    produtos[idp].stock-= qtd;
                    produtos[idp].peso = produtos[idp].peso * qtd + encomendas[ide].peso_total;
                } 
                else
                    printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        }
        else
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/* remove stock a um produto existente */
void comando_r()
{
    int idp, qtd;
    scanf(" %d:%d", &idp, &qtd);
    if (produtos[idp].identificador==idp)       /*verifica se existe produto*/
    {
        if (produtos[idp].stock - qtd >= 0)     /*verifica se tem quantidade de produto suficiente*/
        {
            produtos[idp].stock-=qtd;
        }
        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else   
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
} 

/* remove um produto de uma encomenda */
void comando_R()
{
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);
    if (encomendas[ide].identificador==ide)     
    {
        if (produtos[idp].identificador==idp)       
        {
            for(i=0;i<MAX_PESO;i++)
            {
                if (encomendas[ide].prod_encom[i].identificador==idp)
                {
                    encomendas[ide].prod_encom[i].quantidade=0;
                    produtos[idp].vetor[ide]=0;
                }
            }
        }
        else
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
} 

/* calcula o custo de uma encomenda */
void comando_C()
{
    int ide, idp, qtd, preco, total, i;
    scanf(" %d", &ide);
    if (encomendas[ide].identificador==ide)    
    {
        total=0;
        for(i=0;i<MAX_PESO;i++)
        {
            idp=encomendas[ide].prod_encom[i].identificador;
            qtd=encomendas[ide].prod_encom[i].quantidade;
            preco=produtos[idp].preco;
            total+=preco*qtd;
        }
        printf("Custo da encomenda %d %d.\n", ide, total);
    }
    else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
}

/* altera o preco de um produto existente no sistema */
void comando_p()
{
    int idp, preco;
    scanf(" %d:%d", &idp, &preco);
    if (produtos[idp].identificador==idp)     
        produtos[idp].preco=preco;
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

/* retorna a descricao e a quantidade de uma produto numa dada encomenda */
void comando_E()
{
    int ide, idp, i;
    scanf(" %d:%d", &ide, &idp);
    if (encomendas[ide].identificador==ide)
    {
        if (produtos[idp].identificador==idp)
        {
            for (i=0;i<MAX_PESO;i++)
            {
                if (encomendas[ide].prod_encom[i].identificador==idp)       /*verifica se existe produto na encomenda*/
                    printf("%s %d.\n", produtos[idp].descricao, encomendas[ide].prod_encom[i].quantidade);
                else
                    printf("%s 0.\n", produtos[idp].descricao);
            }
        }
        else
            printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else    
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
}

/* retorna o identificador da encomenda em que um dado produto ocorre mais vezes */
void comando_m()
{
    int idp, i, e, qtd, ide;
    qtd=0;
    scanf(" %d", &idp);
    if (produtos[idp].identificador==idp)
    {
        for(i=0;i<MAX_IDE;i++)
        {
            for (e=0;e<MAX_PESO;e++)
            {
                if (encomendas[i].prod_encom[e].identificador==idp)
                {
                    if (encomendas[i].prod_encom[e].quantidade>qtd)     /*verifica qual o produto da encomenda tem mais quantidade e guarda esse valor*/
                    {
                        qtd=encomendas[i].prod_encom[e].quantidade;
                        ide=i;
                    }
                }
            }
        }
    }
    else    
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    
    if (qtd!=0)
        printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
}

/* lista todos os produtos existentes no sistema por ordem crescente de preco */
int comando_l()
{
    int i;
    int left=0;
    int right=MAX_IDP;
    produto a[MAX_IDP];
  
    for(i=0; i<MAX_IDP; i++)
    {
        a[i]=produtos[i];
    }
  
    mergesort_l(a, left, right-1);

    printf("Produtos\n");
    for (i=left; i<right; i++)
    {
        printf("* %s %d %d\n", a[i].descricao, a[i].preco, a[i].stock);
    }
    return 0;
}

/*ordenar os produtos por ordem crescente de preco*/
void mergesort_l(produto a[], int left, int right)
{
    int m = (right+left)/2;
    if(right<=left)
        return;
    mergesort_l(a, left, m);
    mergesort_l(a, m+1, right);
    merge_l(a, left, m, right);
}
void merge_l(produto a[], int left, int m, int right)
{
    int i, j, k;
    produto aux[MAX_IDP];

    for(i=m+1; i>left; i--)
        aux[i-1]= a[i-1];
    for(j=m; j<right; j++)
        aux[right+m-j] = a[j+1];

    for(k=left; k<=right; k++)
    {
        if (aux[j].preco<aux[i].preco) 
            a[k] = aux[j--];
        else if(aux[j].preco==aux[i].preco)
        {
            if (aux[j].identificador<aux[i].identificador)
                a[k]=aux[j++];
            else
                a[k]=aux[i++];
        }
        else    
            a[k]=aux[i++];
    }
}

/* lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void comando_L()
{
    int ide, i, e;
    int left=0;
    int right=MAX_PESO;
    produto a[MAX_PESO];
    
    scanf(" %d", &ide);

    if (encomendas[ide].identificador==ide)
    {
        for (i=0;i<MAX_PESO;i++)
        {
            e=encomendas[ide].prod_encom[i].identificador;  
            a[i]=produtos[e];
        }
        mergesort_L(a, left, right-1);
        printf("Encomenda %d\n", ide);

        for (i=0; i<MAX_PESO; i++)
        {   
            printf("* %s %d %d\n", a[i].descricao, a[i].preco, a[i].vetor[ide]);
        }
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.", ide);
}



/*ordenar os produtos de uma encomenda por ordem alfabetica*/
void mergesort_L(produto a[], int left, int right)
{
    int m = (right+left)/2;
    if(right<=left)
        return;
    mergesort_L(a, left, m);
    mergesort_L(a, m+1, right);
    merge_L(a, left, m, right);
}
void merge_L(produto a[], int left, int m, int right)
{
    int i, j, k;
    produto aux[MAX_IDP];

    for(i=m+1; i>left; i--)
        aux[i-1]= a[i-1];
    for(j=m; j<right; j++)
        aux[right+m-j] = a[j+1];

    for(k=left; k<=right; k++)
    {
        if(strcmp(aux[j].descricao, aux[i].descricao)<0)
            a[k] = aux[j--];
        else
            a[k]=aux[i++];
    }
}