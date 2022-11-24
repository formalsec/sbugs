#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* maximo de capacidade para as descricoes */
#define DIMDES 63
/* maximo numero de produtos possiveis */
#define DIMPRO 10000
/* maximo numero de encomendas */
#define DIMEM 500
/* maximo numero de produtos por encomenda */
#define DIMEMPRO 200
/* definicao da funcao less*/
#define less(a,b) (a<b)





/*++++++++++++++++++++++++++++++*/
/*     estruturas a utilizar    */
/*++++++++++++++++++++++++++++++*/





/* 
    * descricao: criacao de uma esturuta auxiliar para os produtos e encomendas,
    servira par identificar os produtos que estao nas encomendas
    (caso das encomendas), servira para identificar as encomendas 
    onde esta o produto (caso dos produtos)
    * nome: relevo

*/
typedef struct relevo
{
    int indice;/* idp/ide */
    int identificador;/* 1 se estiver ativo, !=1 nao esta ativo */
    int quantidade;/* corresponde a quantidade do produto na encomenda, apenas e utilizada para encomendas */
} relevo;


/*
    *descricao: criacao de uma estrutura especifica para as encomendas, 
    *nome: encomenda
*/
typedef struct encomendas
{
    int identificador;/* 1 se estiver ativa, != 1 esta inativa*/
    int peso;/* peso da encomenda */
    int preco;/* preco da encomenda */
    int n_produtos_encomendas;/* numero de produtos na encomenda */
    relevo products[DIMEMPRO];/* criacao de 200 estruturas para os 200 possiveis produtos para cada encomenda */    
} encomendas;


/*  
    *descricao: criacao de uma estrutura especifica para os produtos
    *nome: produto
*/
typedef struct produtos
{
    int identificador;/* 1 se estiver ativo, !=1 se estiver inativo */
    int preco;/* preco da encomenda */
    int peso;/* peso da encomenda */
    int n_encomendas_produtos;/* numero de encomendas onde o produto esta */
    char descricao[DIMDES];/* descricao do produto */
    int stock;/* stock existente do produto */
    relevo orders[DIMEM];/* criacao de 500 estruturas para as possiveis 500 encomendas onde o produto podera estar */
} produtos;






/*+++++++++++++++++++++++++++++++++++*/
/*inicializacao das variaveis globais*/
/*+++++++++++++++++++++++++++++++++++*/





/* corresponde ao numero de produtos existentes */
int n_produtos=0;
/* corresponde ao numero de encomendas eistentes */
int n_encomendas=0;
/* criacao do vetor auxiliar para o merge sort */
int aux[DIMPRO]={0};
/* criacao das estruturas para os produtos com todos os valores iguais a zero */
produtos produto[DIMPRO]={0};
/* criacao das estruturas para as encomendas com todos os valores iguais a zero */
encomendas encomenda[DIMEM]={0};






/*++++++++++++++++++++++++++++++++++++*/
/*          funcoes auxiliares        */
/*++++++++++++++++++++++++++++++++++++*/





/* a descricao das funcoes em si esta presente no main */


/*                  a                   */

void adicionar_produto()
{
    /*leitura dos dados */
    scanf(" %[^:]:%d:%d:%d", produto[n_produtos].descricao, &produto[n_produtos].preco, &produto[n_produtos].peso, &produto[n_produtos].stock);
    /* ativar o produto */
    produto[n_produtos].identificador=1;
    printf("Novo produto %d.\n", n_produtos);
    n_produtos++;
}




/*                  q                   */

void adicionar_stock_produto()
{
    int procura, quantidade;
    /* leitura dos dados */
    scanf("%d:%d", &procura, &quantidade);
            
    /*
    verificar se o produto existe
    */
            
    /*se existir*/
    if( produto[procura].identificador == 1)
    {
        produto[procura].stock+=quantidade;
    }
            
    /*se nao existir*/
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", procura);
    }
    
}




/*                  N                   */

void adicionar_encomenda()
{
    /*inicializar a encomenda*/
    encomenda[n_encomendas].identificador=1;
    encomenda[n_encomendas].peso=0;
    encomenda[n_encomendas].preco=0;
    printf("Nova encomenda %d.\n", n_encomendas);
    n_encomendas++;
            
}





/*                  A                   */

void adicionar_produto_a_encomenda(int search, int procura, int quantidade)
{
    int aux=0, indicador;
    
    /*
    erros
    */

    /* se a encomenda nao existir*/        
    if( encomenda[search].identificador !=1 )
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", procura, search);
    }

    /* se o produto nao existir */       
    else if( produto[procura].identificador !=1 )
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", procura, search);
    }
    
    /* se a quantidade for acima do valor possivel */       
    else if( quantidade > produto[procura].stock)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", procura, search);
    }
    
    /* se o peso for acima do possivel */        
    else if( encomenda[search].peso + quantidade*produto[procura].peso > 200)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", procura, search);
    }
    

    /*
    caso passe os testes todos
    */

    else
    {
        /*se estiver na encomenda*/
        if(produto[procura].orders[search].identificador==1)
        {
            for(indicador=0; indicador<encomenda[search].n_produtos_encomendas; indicador++)
            {
                if(encomenda[search].products[indicador].indice==procura)
                {
                    aux=indicador;
                    break;
                }
            }
            /*alteracoes na encomenda*/
            encomenda[search].products[aux].quantidade += quantidade;

            /*alteracoes nos produtos*/
            produto[procura].orders[search].quantidade += quantidade;
        }
        else
        {
            /*
            adicionar o produto
            */

            aux=encomenda[search].n_produtos_encomendas;
            
            /*alteracoes nas encomendas*/
            encomenda[search].products[aux].indice = procura;
            encomenda[search].products[aux].quantidade += quantidade;
            encomenda[search].products[aux].identificador = 1;
            encomenda[search].n_produtos_encomendas++;
            
            /*alteracoes nos produtos*/
            produto[procura].n_encomendas_produtos++;
            produto[procura].orders[search].identificador = 1;
            produto[procura].orders[search].indice = search;
            produto[procura].orders[search].quantidade = quantidade;
        } 
        /* alteracoes comuns aos dois casos */ 
        encomenda[search].peso += quantidade*produto[procura].peso;
        encomenda[search].preco += quantidade*produto[procura].preco;
        produto[procura].stock -= quantidade; 
    }
}
   




/*                  r                   */


void remove_stock_a_produto()
{
    int procura, quantidade;
    /* leitura dos dados */
    scanf("%d:%d", &procura, &quantidade);

    /*
    erros
    */
            
    /*no caso do produto nao existir*/
    if( produto[procura].identificador !=1 )
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", procura);
    }
            
    /*no caso da quantidade ser superior ao stock*/
    else if( quantidade > produto[procura].stock )
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, procura);
    }

    /*
    caso passe nos testes todos
    */

    else
    {
        /*remover a quantidade dada do stock*/
        produto[procura].stock -= quantidade;
    }
}





/*                  R                   */


void remover_produto_da_encomenda(int search ,int procura)
{
    int quantidade, indicador=0, aux=0;

    /*se a encomenda nao existir*/
    if( encomenda[search].identificador != 1 )
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", procura, search);
    } 


    /*se nao existir o produto*/
    else if( produto[procura].identificador !=1 )
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", procura, search);
    }

    /*se nao estiver na encomenda*/
    else if(produto[procura].orders[search].identificador==0)
    {
        ;
    }

    /*
    caso passe os testes
    */

    else
    {
        /*aux fica com a 'casa' correspondente ao produto na encomenda*/
        for(indicador=0; indicador<encomenda[search].n_produtos_encomendas; indicador++)
        {
            if( encomenda[search].products[indicador].indice == procura)
            {
                aux=indicador;
                break;
            }
        }
              
        
        /*saber a quantidade que la estava*/
        quantidade=encomenda[search].products[aux].quantidade;
        
        

        /*puxa os produtos na encomenda uma casa para tras*/
        for(; aux<encomenda[search].n_produtos_encomendas; aux++)
        {
            encomenda[search].products[aux].indice=encomenda[search].products[aux+1].indice;
            encomenda[search].products[aux].quantidade=encomenda[search].products[aux+1].quantidade;
        }
        /*alteracoes nas encomendas*/
        encomenda[search].n_produtos_encomendas--;
        encomenda[search].preco -= quantidade * produto[procura].preco;
        encomenda[search].peso -= quantidade * produto[procura].peso;

        /*alteracoes nos produtos*/
        produto[procura].orders[search].identificador = 0;
        produto[procura].orders[search].quantidade = 0;
        produto[procura].n_encomendas_produtos--;
        produto[procura].stock += quantidade;
    }
}





/*                  C                   */

void custo_encomenda()
{
    int search;
    /* leitura dos dados */
    scanf("%d", &search);
     
    /* no caso da encomenda nao existir */
    if ( encomenda[search].identificador != 1 )
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", search);
    }

    /*
    passar nos testes
    */

    else
    {
        printf("Custo da encomenda %d %d.\n", search, encomenda[search].preco);
    }
}





/*                  p                   */

void alterar_preco_produto()
{
    int procura, preco, indicador, indicador2;
    /* leitura dos dados */
    scanf("%d:%d", &procura, &preco);
            
    /*no caso do produto nao existir*/
    if ( produto[procura].identificador != 1 )
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", procura);
    }

    /*
    passar nos testes
    */

    else
    {   
        /*a todas as encomendas ativas, indicador toma o valor dos <ide> onde o produto estiver*/
        for(indicador=0; indicador < n_encomendas; indicador++)
        {
            for(indicador2=0; indicador2 < encomenda[indicador].n_produtos_encomendas; indicador2++)
            {
                if(encomenda[indicador].products[indicador2].indice==procura)
                {
                    encomenda[indicador].preco+=(preco-produto[procura].preco)*encomenda[indicador].products[indicador2].quantidade;
                }
            }
        }
        produto[procura].preco=preco;
    }
}






/*                  E                   */

void listar_descricao_e_quantidade()
{
    int procura, search;
    /*leitura dos dados do input*/
    scanf("%d:%d", &search, &procura);

    /*no caso do produto nao existir*/
    if ( produto[procura].identificador != 1 )
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", procura);
    }

    /*no caso de nao existir essa encomenda*/
    else if ( encomenda[search].identificador != 1 )
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", search);
    }

    /*
    passar nos testes
    */

    else
    {
        printf("%s %d.\n", produto[procura].descricao, produto[procura].orders[search].quantidade);
    }
    
}






/*                  m                   */

void listar_maior_quantidade_produto()
{
    /*
       maior_encomenda = encomenda com maior quantidade do produto ate ao momento
       maior_quantidade = maior quantidade numa encomenda ate ao momento 
    */
    int procura, maior_encomenda=0, maior_quantidade=0, indicador=0;
    
    /* leitura dos dados */
    scanf("%d", &procura);

    /*caso o produto nao exista*/
    if ( produto[procura].identificador != 1 )
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", procura);
    }

    /*
    caso passe nos testes
    */
    else
    {
        /*para todas as encomendas*/
        for(; indicador<n_encomendas; indicador++)
        {
            /* caso o produto esteja na encomenda e a quantidade for maior a maior quantidade ate ao momento*/
            if(produto[procura].orders[indicador].identificador == 1 && produto[procura].orders[indicador].quantidade > maior_quantidade)
            {
                maior_encomenda=indicador;
                maior_quantidade=produto[procura].orders[indicador].quantidade;
            }
        }
        /* para o caso de estar, de facto, numa encomenda */
        if(maior_quantidade>0)
        {
            printf("Maximo produto %d %d %d.\n", procura, maior_encomenda, maior_quantidade);
        }       
    }
}





/*                  merge 'l'                   */


void merge_l(int a[], int left,int m, int right)
{
    int i, j, k;
    for(i=m+1; i>left; i--)
    {
        aux[i-1]=a[i-1];
    }
    for(j=m; j<right; j++)
    {
        aux[right+m-j]=a[j+1];
    }
    for( k=left; k<=right; k++)
    {
        if(produto[aux[j]].preco < produto[aux[i]].preco || ( produto[aux[j]].preco == produto[aux[i]].preco && aux[j]<aux[i]))
        {
            a[k]=aux[j--];
        }
        else
        {
            a[k]=aux[i++];
        }   
    }
}


/*                      funcao para ordenar o vetor usando o merge 'l'                 */


void mergesort_l(int a[], int left, int right)
{
    int m=(right+left)/2;

    if(right<=left)
    {
        return;
    }

    mergesort_l(a, left, m);
    mergesort_l(a, m+1, right);
    merge_l(a, left, m, right);
}






/*                  merge 'L'                   */

void merge_L(int a[], int left,int m, int right)
{
    int i, j, k;
    for(i=m+1; i>left; i--)
    {
        aux[i-1]=a[i-1];
    }
    for(j=m; j<right; j++)
    {
        aux[right+m-j]=a[j+1];
    }
    for( k=left; k<=right; k++)
    {
        if(strcmp(produto[aux[j]].descricao, produto[aux[i]].descricao)<0)
        {
            a[k]=aux[j--];
        }
        else
        {
            a[k]=aux[i++];
        }   
    }
}


/*                  funcao para ordenar o vetor usando o merge 'L'                 */


void mergesort_L(int a[], int left, int right)
{
    int m=(right+left)/2;

    if(right<=left)
    {
        return;
    }

    mergesort_L(a, left, m);
    mergesort_L(a, m+1, right);
    merge_L(a, left, m, right);
}






/*                  l                   */

void lista_por_preco()
{
    /* vetor com os 'idp' ativos */
    int vetor[DIMPRO]={0}, i, j=0, max;
    
    printf("Produtos\n");
    for(i=0; i<n_produtos; i++, j++)
    {
        vetor[j]=i;
    }
    
    max=j-1;
    
    /*ordenar o vetor*/
    mergesort_l(vetor, 0, max);
    
    /*para cada preco*/
    for(i=0; i<max+1; i++)
    {
        printf("* %s %d %d\n", produto[vetor[i]].descricao, produto[vetor[i]].preco, produto[vetor[i]].stock);
    }
}






/*                  L                   */

void listar_ordem_alfabetica()
{
    /* criacao de um vetor para os 'idp' dos produtos dentro da encomenda */
    int search, max, i, j=0, vetor[DIMEMPRO];
    scanf("%d", &search);
    
    /* se a encomenda nao existir */
    if(encomenda[search].identificador==0)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", search);
    }

    /*
    passar os testes
    */

    else
    {
        printf("Encomenda %d\n", search);
        
        /*tabela dos produtos*/
        for(i=0; i<encomenda[search].n_produtos_encomendas; i++)
        {
            vetor[j]=encomenda[search].products[i].indice;
            j++;
        } 
        max=j-1;
        
        /*ordenar a tabela*/
        mergesort_L(vetor, 0, max);

        /*para cada idp ordenado*/
        for( i=0 ; i<max+1 ; i++)
        {
            printf("* %s %d %d\n", produto[vetor[i]].descricao, produto[vetor[i]].preco, produto[vetor[i]].orders[search].quantidade);
        }
    }
}






/*++++++++++++++++++++++++++++++++++++*/
/*            main                    */
/*++++++++++++++++++++++++++++++++++++*/





int main()
{
    char caracter;/*o caracter serve para ler a acao que vamos fazer*/
    int ide, idp, quantity;
    
    
    /* ate o caracter lido ser 'x'*/
    do
    {
    switch(caracter=getchar())
    {
        /*adiciona um novo produto ao sistema*/
        case'a':
            adicionar_produto();
            break;
                
        /*adiciona stock a um produto existente no sistema*/
        case 'q':
            adicionar_stock_produto();
            break;
        
        /*cria uma nova encomenda*/
        case 'N':
            adicionar_encomenda();
            break;
        
        /*adiciona um produto a uma encomenda*/
        case 'A':
            /*leitura dos dados*/
            scanf("%d:%d:%d", &ide, &idp, &quantity);
            adicionar_produto_a_encomenda(ide, idp, quantity);
            break;
        
        /*remove stock a um produto existente*/
        case 'r':
            remove_stock_a_produto();
            break;

        /*remove o produto de uma encomenda*/
        case 'R':
            /*leitura dos dados*/
            scanf("%d:%d", &ide, &idp);
            remover_produto_da_encomenda(ide, idp);
            break;
        
        /*calcular o custo de uma encomenda*/
        case 'C':
            custo_encomenda();
            break;

        /*alterar o preco de um produto*/
        case 'p':
            alterar_preco_produto();
            break;

        /*lista a descricao e a quantidade de um produto numa encomenda*/
        case 'E':
            listar_descricao_e_quantidade();
            break;

        /*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
        case 'm':
            listar_maior_quantidade_produto();
            break;
            
        /*lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
        case 'l':
            lista_por_preco();
            break;
        
        /*listar todos os produtos de uma encomenda por ordem alfabetica*/
        case 'L':
            listar_ordem_alfabetica();
            break;

        /*para o caso de se enganar e digitar uma tecla sem acao*/
        default:
            break;     
    }
    } while (caracter!='x');
    return 0;   
}







