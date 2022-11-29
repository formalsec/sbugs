#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DIM_DESC         64     /* Numero max caracteres de uma descricao.    */
#define DIM_BUFFER    10000     /* Numero max de caracteres lidos no buffer.  */
#define MAX_PROD      10000     /* Numero max produtos existentes.            */
#define MAX_ENC         500     /* Numero max encomendas existentes.          */
#define MAX_PROD_ENC    500     /* Numero max de produtos por encomendas.     */
#define MAX_PESO        200     /* Peso max de cada encomenda.                */

typedef struct produto
{
    char    descricao[DIM_DESC];
    int     idp, preco, peso, qtd;

} Produto;

typedef struct encomenda
{   
    Produto lista[MAX_PROD_ENC];
    int     ide, peso, counter;

} Encomenda;

Produto     armazem[MAX_PROD];
Encomenda   pedidos[MAX_ENC];

int lastP = -1;
int lastE = -1;

/*          Fun??es Gerais:                                                   */
void lerBuffer(char array[][DIM_DESC], int x);
/*          Fun??es do Comando 'a':                                           */
Produto criaProduto(char array[][DIM_DESC]);
void addProduto(Produto x);
/*          Fun??es do Comando 'q':                                           */
void addStock(char array[][DIM_DESC]);
/*          Fun??es do Comando 'N':                                           */
void criaEncomenda();
/*          Fun??es do Comando 'A':                                           */
void addProdutoEncomenda(char array[][DIM_DESC]);
int naoExisteEncomenda(int x);
int naoExisteProduto(int x);
int naoExisteStock(int x, int y);
int limitePeso(int x, int y, int z);
/*          Fun??es do Comando 'r':                                           */
void removeStock(char array[][DIM_DESC]);
/*          Fun??es do Comando 'R':                                           */
void removeProdutoEncomenda(char array[][DIM_DESC]);
/*          Fun??es do Comando 'C':                                           */                            
void calculaCustoEncomenda(char array[][DIM_DESC]);
/*          Fun??es do Comando 'p':                                           */
void alteraPreco(char array[][DIM_DESC]);
/*          Fun??es do Comando 'E':                                           */
void E_lista(char array[][DIM_DESC]);
                                                        

int main()
{
    int num_inputs, i;

    char        command;
    char        buffer[3][DIM_DESC];
    
    Produto novoProd;
 
    while (1)
    {
        command = getchar();
        
        switch (command)
        {

            case 'a':
                num_inputs = 4;

                lerBuffer(buffer, num_inputs);
                novoProd = criaProduto(buffer);
                addProduto(novoProd);                
                break;

            case 'q':
                num_inputs = 2;

                lerBuffer(buffer, num_inputs);
                addStock(buffer);
                break;
            
            case 'N':
                criaEncomenda();
                break;
            
            case 'A':
                num_inputs = 3;

                lerBuffer(buffer, num_inputs);
                addProdutoEncomenda(buffer);
                break;
            
            case 'r':
                num_inputs = 2;

                lerBuffer(buffer, num_inputs);
                removeStock(buffer);
                break;
                
            case 'R':
                num_inputs = 2;

                lerBuffer(buffer, num_inputs);
                removeProdutoEncomenda(buffer);
                break;
            
            case 'C':
                num_inputs = 1;

                lerBuffer(buffer, num_inputs);
                calculaCustoEncomenda(buffer);
                break;
            
            case 'p':
                num_inputs = 2;

                lerBuffer(buffer, num_inputs);
                alteraPreco(buffer);
                break;

            case 'E':
                num_inputs = 2;

                lerBuffer(buffer, num_inputs);
                E_lista(buffer);
                break;
            
            case 'm':
                printf("Entrou um m\n");
                break;
            
            case 'l':
                printf("Entrou um l\n");
                break;
            
            case 'L':
                printf("Entrou um L\n");
                break;
            
            case 'x':
                return EXIT_SUCCESS;
                break;
            case 'T':
                printf("Todos os produtos em armazem:\n\n");
                for (i = 0; i < lastP; i++)
                {
                    printf("pid: %d descricao: %s preco: %d"
                    " peso: %d quantidade: %d\n", armazem[i].idp, 
                    armazem[i].descricao, armazem[i].preco, armazem[i].peso,
                    armazem[i].qtd);
                }
                printf("\n----------------------------------\n");
                for (i = 0; i < lastE; i++)
                {
                    printf("Encomenda: %d\n", pedidos[i].ide);
                }

                
                break;
            default:
                break;
        }
    }
    
  return 0;  
}
void lerBuffer(char array[][DIM_DESC], int x)
{
    char * token;
    char   buffer[DIM_BUFFER];
    int    i;

    i = 0; 

    scanf("%s", buffer);

    token = strtok(buffer, ":");    

    while(token != NULL && i<x)
    {
        strcpy(array[i], token);
        token = strtok(NULL,":");
        i++;
    }
}
Produto criaProduto(char array[][DIM_DESC])
{
    Produto x;

    strcpy(x.descricao, array[0]);
    
    x.preco = atoi(array[1]);
    x.peso  = atoi(array[2]);
    x.qtd   = atoi(array[3]);
    

    return x;
}
void addProduto(Produto x)
{
    /* 
        array ? a lista que contem todo os produtos do sistema
        y ? o ultimo produto inserido
        z ? o novo produto a inserir
    */
    lastP ++;
    
    x.idp = lastP;   
    armazem[lastP].idp = x.idp;
    strcpy(armazem[lastP].descricao, x.descricao);
    armazem[lastP].preco = x.preco;
    armazem[lastP].peso  = x.peso;
    armazem[lastP].qtd   = x.qtd;

    printf("Novo produto %d.\n", armazem[lastP].idp);
}
void addStock(char array[][DIM_DESC])
{
    int idp;                
    int stock;              

    idp = atoi(array[0]);
    stock = atoi(array[1]); 
    
    if (idp > lastP)
    {
        printf("Impossivel adicionar produto %d ao stock. "
        "Produto inexistente.\n", idp);
    }
    else
    {   
        armazem[idp].qtd += stock;
    }
}
void criaEncomenda()
{
    lastE++;
    pedidos[lastE].ide = lastE;
    pedidos[lastE].counter = 0;

    printf("Nova encomenda %d.\n", pedidos[lastE].ide);    
}
void addProdutoEncomenda(char array[][DIM_DESC])
{
    int ide, idp, qtd;

    ide = atoi(array[0]);
    idp = atoi(array[1]);
    qtd = atoi(array[2]);

    if(naoExisteEncomenda(ide))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Encomenda inexistente.\n", idp, ide);
    }
    else if(naoExisteProduto(idp))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Produto inexistente.\n", idp, ide);
    }
    else if(naoExisteStock(idp, qtd))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if(limitePeso(ide, idp, qtd))
    {
        printf("Impossivel adicionar produto %d a encomenda %d. "
        "Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else
    { 
        pedidos[ide].counter++;

        /* 
        Vamos acerder a lista de produtos de uma encomenda e atraves do contador 
        de produtos, adicionar um produto existente em armazem */
        pedidos[ide].lista[pedidos[ide].counter] = armazem[idp];
        /* 
        A quantidade do produto anteriormente adicionado ? lida do buffer.
        */
        pedidos[ide].lista[pedidos[ide].counter].qtd = qtd;
        armazem[idp].qtd -= qtd; 
        pedidos[ide].peso += armazem[idp].peso*qtd;
        
   }
}
int naoExisteEncomenda(int x)
{
    /*
    x -> ide
    */
    return (x > lastE);
}
int naoExisteProduto(int x)
{
    /*
    x -> idp do produto que queremos adicionar                                
    */
    return (x > lastP);
}
int naoExisteStock(int x, int y)
{
    /* 
    x -> idp
    y -> qtd a adicionar
    */

    return (y > armazem[x].qtd);
}
int limitePeso(int x, int y, int z)
{
    /*
    x -> ide
    y -> idp 
    z -> qtd a adicionar                                                      
    */

   if ((armazem[y].peso*z)>200||
   ((armazem[y].peso*z) + pedidos[x].peso) > 200)
   {
       return 1;
   }

    return  0;
}
void removeStock(char array[][DIM_DESC])
{
    int idp, qtd;

    idp = atoi(array[0]);
    qtd = atoi(array[1]);

    if (naoExisteProduto(idp))
    {
        printf("Impossivel remover stock do produto %d. "
        "Produto inexistente.\n", idp);
    }
    else if (naoExisteStock(idp, qtd))
    {
        printf("Impossivel remover %d unidades do produto %d do stock. "
        "Quantidade insuficiente.\n", qtd, idp);
    }
    else
    {
        armazem[idp].qtd-=qtd;
    }
}
void removeProdutoEncomenda(char array[][DIM_DESC])
{
    int ide, idp, qtd, i;

    i   = 0;
    ide = atoi(array[0]);
    idp = atoi(array[1]);

    if (naoExisteEncomenda(ide))
    {
        printf("Impossivel remover produto %d a encomenda %d. "
        "Encomenda inexistente.\n", idp, ide);
    }
    else if (naoExisteProduto(idp))
    {
        printf("Impossivel remover produto %d a encomenda %d. "
        "Produto inexistente.\n", idp, ide);
    }
    else
    {
        for (i = 0; i <= pedidos[ide].counter; i++)
        {
            if (pedidos[ide].lista[i].idp == idp)
            {
                qtd = pedidos[ide].lista[i].qtd;
                pedidos[ide].lista[i].qtd = 0;
                armazem[idp].qtd += qtd;
                pedidos[ide].peso -= armazem[idp].peso*qtd;
            }
                
        }
    }
}
void calculaCustoEncomenda(char array[][DIM_DESC])
{
    int ide, precoE, i;

    ide = atoi(array[0]);
    precoE = 0;

    if (naoExisteEncomenda(ide))
    {
        printf("Impossivel calcular custo da encomenda %d. "
        "Encomenda inexistente.\n", ide);
    }

    else
    {
        for (i = 0; i <= pedidos[ide].counter; i++)
        {
            precoE += (pedidos[ide].lista[i].preco)*(pedidos[ide].lista[i].qtd);
        }

        printf("Custo da encomenda %d %d.\n", ide, precoE);
    }
}
void alteraPreco(char array[][DIM_DESC])
{
    int idp, preco, i, j;

    idp     = atoi(array[0]);
    preco   = atoi(array[1]);

    if (naoExisteProduto(idp))
    {
        printf("Impossivel alterar preco do produto %d. "
        "Produto inexistente.\n", idp);
    }
    else
    {
        armazem[idp].preco = preco;

        for (i = 0; i <= lastE; i++)
        {
            for (j = 0; j <= pedidos[i].counter; j++)
            {
                if (pedidos[i].lista[j].idp == idp)
                {
                    pedidos[i].lista[j].preco = preco;
                }    
            }
        }
    }
}
void E_lista(char array[][DIM_DESC])
{
    int ide, idp;

    ide = atoi(array[0]);
    idp = atoi(array[1]);

    if (naoExisteEncomenda(ide))
    {
        printf("Impossivel listar encomenda %d. "
        "Encomenda inexistente.\n", ide);
    }

    else if (naoExisteProduto(idp))
    {
        printf("Impossivel listar produto %d. "
        "Produto inexistente.\n", idp);
    }
    else
    {
        printf("%s %d.\n", 
        armazem[idp].descricao, pedidos[ide].lista[idp].qtd);
    }
}
