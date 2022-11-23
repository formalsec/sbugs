#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/****************************************************
 * CONSTANTES
 * MAXSIZE : 63 caracteres mais o '\0'
 ****************************************************/
#define MAXSIZE 64 
#define MAXPRODUTO 10000
#define MAXENCONMENDAS 500
#define MAXPESO 200
#define NAO -1
#define SIM 1
#define FALSE -1

/*********************************************************
 * Estruturas para Produto e Encomenda.
 *********************************************************/
typedef struct Produtos
{
    int id;
    char descricao[MAXSIZE];
    int preco;
    int peso;
    int qtdPedidaNaEnc;
    int qtdEmStock;
    int exite;
    int numerodeVezesEnc;
    int idpNaEnc;
}Produto;


typedef struct Encomendas
{
    Produto encomendado[MAXPESO];
    int encPeso;
    int idEnc;
    int numeroDeProdutos;
    int existeEncomenda;
    int custo;
    int idsProdEnc[MAXPRODUTO];
}Encomenda;

/***********************************************
 * Declaracao de Variaveis
 * contador : para o numero de produtos
 * contadorEnc: para o numero de encomendas
 ***********************************************/

Produto ListaDeProdutos[MAXPRODUTO];
Produto ListaAuxProd[MAXPRODUTO];
Produto ListaOrdProd[MAXPRODUTO];
Encomenda ListaDeEncomendas[MAXENCONMENDAS];
int contador = 0;
int contadorEnc = 0;

/********************************************
 * Declaracao de Funcoes
 * *****************************************/

void adicionaProduto();
void adicionaStock();
void criaNovaEncomenda();
void adicionaProdEncomenda();
void removeProdStock();
void removeProdEncomenda();
void calculaCustoDeEncomenda();
void alteraPrecoDoProduto();
void listaProdDescQuant();
void listaIdEncMaxProd();
void listaProdPorOrdemDePreco();
void listaProdPorDescricao();
void ordenaPorNome(Produto encomendados[], int tam);
void ordenaPorPreco();
int  existeProd(int idProd);
int  existeEnc(int idEnc);
int  produtoExistenteNaEncomenda(int idp, int idenc);
int  idProdNaEnc(int ide, int idp);

/*******************************************
 * Funcao Principal 
 ******************************************/
int main()
{

    char comando;
    

    do
    {
        comando = getchar();
        switch(comando) /* Dado o comando, uma das funcoes e executada*/
        {
            case 'a':
                        adicionaProduto();
                        break;
            case 'q':
                        adicionaStock();
                        break;
            case 'N':
                        criaNovaEncomenda();
                        break;
            case 'A':
                        adicionaProdEncomenda();
                        break;
            case 'r':
                        removeProdStock();
                        break;
            case 'R':
                        removeProdEncomenda();
                        break;
            case 'C':
                        calculaCustoDeEncomenda();
                        break;
            case 'p':
                        alteraPrecoDoProduto();
                        break;
            case 'E':
                        listaProdDescQuant();
                        break;
            case 'm':
                        listaIdEncMaxProd();
                        break;
            case 'l':
                        listaProdPorOrdemDePreco();
                        break;
            case 'L':
                        listaProdPorDescricao();
                        break;
            default:
                        break;


        }

    }while(comando != 'x');

    return 0;

}

/*********************************************************
 * Adiciona um produto a lista de produtos
 * ****************************************************/
void adicionaProduto()
{
  
    char descricao[MAXSIZE];
    int preco, peso, qtd;
    Produto p;
    getchar();
    scanf("%[^:]:%d:%d:%d",descricao, &preco, &peso, &qtd);
   
    strcpy(p.descricao,descricao);
   
    p.preco = preco;
    p.peso = peso;
    p.qtdPedidaNaEnc = 0;
    p.qtdEmStock = qtd;
    p.id = contador;
    p.exite = SIM;
    p.numerodeVezesEnc = 0;
    p.idpNaEnc = -1;
    ListaDeProdutos[contador++] = p;

    printf("Novo produto %d.\n",p.id);

}
/**************************************************
 * Adiciona stock a um produto da lista de produtos
 * Entrada : id do produto e quantidade a adicionar
 * Erros: No caso do produto nao existir
 * Obs: Um produto existe se: id < contador de produtos
 * ************************************************.**/
void adicionaStock()
{
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);
    
    if(idp < contador)
    {
        ListaDeProdutos[idp].qtdEmStock += qtd;
    }
    else
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    
}
/******************************************
 * Cria uma nova encomenda
 * ****************************************/
void criaNovaEncomenda()
{
    Encomenda novaEncomenda;
    novaEncomenda.idEnc = contadorEnc;
    novaEncomenda.encPeso = 0;
    novaEncomenda.numeroDeProdutos = 0;
    novaEncomenda.existeEncomenda = SIM;
    novaEncomenda.custo = 0;

    ListaDeEncomendas[contadorEnc++] = novaEncomenda;

    printf("Nova encomenda %d.\n", novaEncomenda.idEnc);
}

/************************************************
 * Adiciona um produto a uma encomenda 
 ***********************************************/
void adicionaProdEncomenda()
{
    int idEnc, idp, qtdPedida, idpEnc;
    Encomenda e;
    Produto p;
    
    scanf("%d:%d:%d", &idEnc, &idp, &qtdPedida);


    if(idEnc < contadorEnc)
    {
        if(idp < contador)
        {
            p = ListaDeProdutos[idp];
            e = ListaDeEncomendas[idEnc];
            
            if(ListaDeProdutos[idp].qtdEmStock < qtdPedida )
            {
               
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, idEnc);
            }
            else
            {
               if((ListaDeEncomendas[idEnc].encPeso +(p.peso*qtdPedida )) > MAXPESO)
               {
                   printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, idEnc);
               }
               else
               {
                   idpEnc = produtoExistenteNaEncomenda(idp, idEnc); /* verifica se o produto existe na encomenda*/
                   if( idpEnc == NAO)
                   {
                        p.preco = ListaDeProdutos[idp].preco;
                        strcpy(p.descricao, ListaDeProdutos[idp].descricao);
                        p.id = ListaDeProdutos[idp].id;
                        p.qtdPedidaNaEnc += qtdPedida;
                        p.peso = ListaDeProdutos[idp].peso;
                        p.idpNaEnc = e.numeroDeProdutos;
                        ListaDeEncomendas[idEnc].encomendado[e.numeroDeProdutos] = p;
                        ListaDeEncomendas[idEnc].encPeso += (p.peso*qtdPedida);
                        ListaDeProdutos[idp].qtdEmStock -= qtdPedida;
                        ListaDeEncomendas[idEnc].numeroDeProdutos++;
                        ListaDeEncomendas[idEnc].encomendado[e.numeroDeProdutos].numerodeVezesEnc++;  
                        
                   }
                   else
                   {
                        ListaDeEncomendas[idEnc].encomendado[idpEnc].qtdPedidaNaEnc += qtdPedida;
                        ListaDeEncomendas[idEnc].encPeso += (qtdPedida* p.peso);
                        ListaDeProdutos[idp].qtdEmStock -= qtdPedida;
                        ListaDeEncomendas[idEnc].encomendado[idpEnc].numerodeVezesEnc++;  
                         
                   }
                   
               }
               
            }
        }
        else
        {
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, idEnc);
            
        }  

    }
    else
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp,idEnc);
    }

}

/**********************************************************
 * Remove unidades ao Stock de um produto
 *********************************************************/

void removeProdStock()
{
    int idp, qtd;
    scanf("%d:%d", &idp, &qtd);

    if(idp < contador)
    {       
        if(ListaDeProdutos[idp].qtdEmStock < qtd )
        {
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        else
        {
            ListaDeProdutos[idp].qtdEmStock -= qtd;
        }
        
    }
    else
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);      
    }
    
}

/************************************************
 * Remove um produto a uma encomenda 
 **********************************************/
void removeProdEncomenda()
{
    int ide, idp,peso, qtd, i, limite,  idpEnc;
   
    scanf("%d:%d", &ide, &idp);

    if(ide < contadorEnc)
    {
       
        if(idp < contador)
        {

            idpEnc = produtoExistenteNaEncomenda(idp, ide);
            if(idpEnc != NAO)
            {
            
            peso = ListaDeEncomendas[ide].encomendado[idpEnc].peso;
            qtd = ListaDeEncomendas[ide].encomendado[idpEnc].qtdPedidaNaEnc;
            
            ListaDeProdutos[idp].qtdEmStock += qtd;
            ListaDeEncomendas[ide].encPeso -= (qtd*peso);
            

            ListaDeEncomendas[ide].encomendado[idpEnc].qtdPedidaNaEnc = 0;
            ListaDeEncomendas[ide].encomendado[idpEnc].idpNaEnc = -1;

            limite = ListaDeEncomendas[ide].numeroDeProdutos-1;
            for( i=idpEnc; i< limite; i++)
            {
                ListaDeEncomendas[ide].encomendado[i] = ListaDeEncomendas[ide].encomendado[i+1];
            }
            ListaDeEncomendas[ide].numeroDeProdutos--;

            }
     
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
/********************************************
 * Calcula o custo da Encomenda
 * Entrada: ide- identificador da encomenda
 ******************************************/
void calculaCustoDeEncomenda() 
{
    int ide, i;
    scanf("%d", &ide);

    if(ide < contadorEnc)
    {
       
        for(i =0; i < ListaDeEncomendas[ide].numeroDeProdutos; i++)
        {
            ListaDeEncomendas[ide].custo += (ListaDeEncomendas[ide].encomendado[i].preco * ListaDeEncomendas[ide].encomendado[i].qtdPedidaNaEnc);

        }
        printf("Custo da encomenda %d %d.\n",ide, ListaDeEncomendas[ide].custo);
        ListaDeEncomendas[ide].custo = 0;
    }
    else
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    
}
/*************************************************
 * Altera o preco de um produto 
 * ***********************************************/
void alteraPrecoDoProduto()
{
    int idp, preco, i, idpEnc = FALSE;
   
    scanf("%d:%d", &idp, &preco);

    if(idp < contador)
    {
        ListaDeProdutos[idp].preco = preco;
        for(i = 0; i< contadorEnc; i++)
        {
           idpEnc = idProdNaEnc(i, idp); /*devolve a posicao do produto na respetica encomenda*/
           if(idpEnc != FALSE)
           {
               ListaDeEncomendas[i].encomendado[idpEnc].preco = preco;
           }
        }
    }
    else
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    
}
/*****************************************
 * Procura a posicao do produto dado pelo
 * identificador idp na encomenda ide
 * **************************************/
int idProdNaEnc(int ide, int idp)
{
    int i,  existe = FALSE;
    for( i = 0; i< ListaDeEncomendas[ide].numeroDeProdutos && existe == FALSE; i++)
    {
        if(idp == ListaDeEncomendas[ide].encomendado[i].id)
        {
            existe = i;
        }
    }
    return existe;
            
}

/*****************************************
 * Lista a descricao e quantidade do produto 
 * idp na encomenda ide
 *****************************************/ 
void listaProdDescQuant() 
{
    int ide, idp, qtd, existe = FALSE;
    
    scanf("%d:%d", &ide, &idp);

    if(ide < contadorEnc)
    {
        if(idp < contador)
        {
            existe = idProdNaEnc(ide, idp); 
            qtd = 0;
            if(existe != NAO)
            {
                printf("%s %d.\n",ListaDeEncomendas[ide].encomendado[existe].descricao,  ListaDeEncomendas[ide].encomendado[existe].qtdPedidaNaEnc);
            }
            else
            {
                printf("%s %d.\n",ListaDeProdutos[idp].descricao, qtd);
            } 
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
/*****************************************
 * Lista o identificador da encomenda em que
 * o produto idp aparece mais vezes
 ****************************************/
void listaIdEncMaxProd()
{
    int idp, i, maior, ide,  idpEnc = FALSE;
  
    scanf("%d", &idp);
    ide =  maior = i = 0;
   
    if (idp < contador)
    {
       for(; i< contadorEnc ; i++)
       {
           idpEnc = idProdNaEnc(i, idp);
           if(idpEnc != FALSE)
           {
               if(ListaDeEncomendas[i].encomendado[idpEnc].qtdPedidaNaEnc > maior)
               {
                   maior = ListaDeEncomendas[i].encomendado[idpEnc].qtdPedidaNaEnc;
                   ide = i; 
               }
           }  
       }

       if(ide < contadorEnc && maior != 0)
       {
           printf("Maximo produto %d %d %d.\n",idp, ide, maior);
       }
    }
    else
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
       
}

/**************************************
 * Lista todos os produtos por ordem 
 * crescente do peso
 *************************************/
void  listaProdPorOrdemDePreco()
{
    int i;
    Produto temp;
    for (i =0; i< contador; i++)
    {
        ListaOrdProd[i] = ListaDeProdutos[i]; /* copia os produtos para umvetor auxiliar de maneira a que a ordem deles nao seja alterada*/
    }

    ordenaPorPreco(); /*ordena por ordem crescente*/
    printf("Produtos\n");
    for(i =0; i< contador; i++)
    {
        temp = ListaOrdProd[i];
        printf("* %s %d %d\n", temp.descricao, temp.preco, temp.qtdEmStock);
    }
}

/******************************************************
 * Funcao que lista todosos produtos da encomenda 
 * por ordem alfabetica da descricao
 * ***************************************************/
void listaProdPorDescricao()
{
    int ide, numDeProdutos, i, preco;
    Produto aux;
    scanf("%d", &ide);

    if(ide < contadorEnc)
    {
        numDeProdutos = ListaDeEncomendas[ide].numeroDeProdutos;

        for (i = 0; i< numDeProdutos; i++)
        {
            ListaOrdProd[i] =ListaDeEncomendas[ide].encomendado[i];
        }

        ordenaPorNome(ListaOrdProd, numDeProdutos);
        
        printf("Encomenda %d\n", ide);
        for(i=0; i<numDeProdutos; i++)
        {
            aux = ListaOrdProd[i];
            preco = ListaDeProdutos[aux.id].preco;
            printf("* %s %d %d\n",aux.descricao,preco,aux.qtdPedidaNaEnc);
        }
    }
    else
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    
}

/*********************************************************
 * Funcao que dado o identificador da encomenda
 * e do produto determina a posicao do produto na encomenda
 **********************************************************/
int produtoExistenteNaEncomenda(int idp, int idenc)
{
    int i, existe = NAO;
    for(i =0; i< ListaDeEncomendas[idenc].numeroDeProdutos && existe == -1 ; i++)
    {
        if(ListaDeEncomendas[idenc].encomendado[i].id == idp)
        {
            if(ListaDeEncomendas[idenc].encomendado[i].idpNaEnc != -1)
            { 
                existe = i;
            }
        }
    }
    
    return existe;
}

/*****************************************************
 * Funcao que compara os produtos dependedo do codigo 
 * que recebe, se codigo for 1 entao compara os precos
 * senao compara as descricoes o que significa se faz 
 * uma ordenacao em funcao das descricoes
 ****************************************************/
int comparador(Produto p1, Produto p2, int codigo)
{
    int comp;
    if(codigo == 1)
    {
        return (p1.preco < p2.preco) || (((p1.preco == p2.preco) && (p1.id  < p2.id)));

    }
    else
    {
        comp = strcmp(p1.descricao, p2.descricao);
        return (comp < 0) || (((comp  == 0 ) && (p1.id  < p2.id)));
    }
    
}

void merge(Produto a[], int left, int m, int right, int codigo)
{ 
    int i, j, k;
    for (i = m+1; i > left; i--) 
    {
        ListaAuxProd[i-1] = a[i-1];
    }
    for (j = m; j < right; j++)
    {
        ListaAuxProd[right+m-j] = a[j+1];
    }
        
    for (k = left; k <= right; k++)
    {
        if (comparador(ListaAuxProd[j], ListaAuxProd[i], codigo) || i > m)
        {
            a[k] = ListaAuxProd[j--];
        }
           
        else
        {
            a[k] = ListaAuxProd[i++];
        }
          
    }
       
}

/***********************************
 * Funcao para ordencao 
 ************************************/
void mergesort(Produto a[], int l, int r, int codigo )
{
    int m;
    m= (l+r)/2;

    if(r<= l) return;

    mergesort(a, l, m,  codigo);
    mergesort(a, m+1, r, codigo);
    merge(a, l, m, r, codigo);

}

void ordenaPorPreco()
{
    mergesort(ListaOrdProd, 0, contador-1, 1);  
}

void ordenaPorNome(Produto encomendados[], int tam)
{
    mergesort(encomendados, 0, tam-1, 2);
}
