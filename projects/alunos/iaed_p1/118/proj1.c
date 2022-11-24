#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*palavra de controlo*/
#define SISTEMA 1

/*palavra de controlo*/
#define ENCOMENDAS 4

/*palavra de controlo para ordenacao*/
#define ALFABETICO 2

/*palavra de controlo para ordenacao*/
#define PRECOS 3

/*palavra de controlo para igualdade de strings*/
#define IGUAIS 0

/*palavra de controlo*/
#define PRESENTE 1

/*palavra de controlo para produtos em sistemas*/
#define NAO -1

/*palavra de controlo da existencia de strings*/
#define EXISTE "existe"

/* numero maximo de carateres da descricao do produto*/
#define DESCRICAO 64

/* numero maximo de encomendas*/
#define MAX_ENCOMENDAS 500

/*numero maximo de produtos em sistema*/
#define MAX_PRODUTOS 10000

/*numero maximo de produtos numa encomenda*/
#define MAX_PRODUTO_ENCOMENDA 200


/*-------------------------------------definicao de estruturas---------------------------------------------------------------*/

/*definicao da estrutura produto, constituida pela 
sua descricao, pelo identificador,peso e quantidade em stock*/
typedef struct produto{
     char descricao[DESCRICAO];
     int  preco,peso,stock,id;
} produto;

/*------------------------prototipos----------------------------------------------*/
int existe_produto_sistema(int identificador);
int verfica_stock_produto(int identificador,int quantidade);
void ordena(produto a[], int left, int right,int chave);
void copia_sistema(produto destino[]);

/*--------------------------------------variaveis globais--------------------------------------------------------------------*/

/*auxiliar no merge sort*/
produto aux[MAX_PRODUTOS];

/*variavel global que guarda os produtos em sistem*/
produto sistema[MAX_PRODUTOS];

/*variavel global que guarda o tamanho do sistema*/
int tamanho_sistema = 0;

/*variavel que guarda o tamanho de cada encomenda*/
int tamanho_encomenda[MAX_ENCOMENDAS];

/*variavel global que controla as encomendas*/
produto encomendas[MAX_ENCOMENDAS][MAX_PRODUTO_ENCOMENDA];
/*--------------------------------Manipulacao de encomendas--------------------------------------------------------------------*/
                            /*--------------Auxiliares-------------------*/


/*Verifica o peso da encomenda com o novo produto. Caso esta exceda o limite
e retornado nao. Caso contrario retorna o tamanho da encomenda*/
int verifica_peso_encomenda(int identificador, 
        int id_produto,int quantidade){
    int i,peso_total = 0;
    for (i = 0;i<tamanho_encomenda[identificador];i++){
        peso_total += encomendas[identificador][i].peso * encomendas[identificador][i].stock;
    }
    if (peso_total + sistema[id_produto].peso * quantidade > MAX_PRODUTO_ENCOMENDA) 
        return NAO;
    return PRESENTE;
}

/*verfica se a encomenda existe.Caso exista retorna Presente caso contrario
retorna nao*/
int existe_encomenda(int identificador){
        if (strcmp(encomendas[identificador][0].descricao,"\0") != IGUAIS)
            return PRESENTE;
        else
        {
            return NAO;
        }
        
}

/*verifica se um produto se encotra na encomenda. Retorna
a posicao onde este se encontra ou nao caso este nao exista*/
int procura_produto_encomenda(int id_produto,int id_encomenda){
    int i;
    for (i = 0;i<tamanho_encomenda[id_encomenda];i++){
        if (encomendas[id_encomenda][i].id == id_produto)
            return i;
    }
    return NAO;
}

/* cria uma nova encomenda, alterando a  string vazia da descricao do primeiro produto
(por convencao, encomenda existe <=> descricao == existe)*/
void cria_encomenda(){
    static int i = 0; /*identificador de encomendas*/
    strcpy(encomendas[i][0].descricao,EXISTE);
    printf("Nova encomenda %d.\n",i);
    i++;
}

/*lista a descricao e quantidade de um produto numa 
encomenda*/
void lista_produto_encomenda(int id_encomenda,int id_produto){
    int local;
    /*a encomenda existe?*/
    if (existe_encomenda(id_encomenda) == NAO){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_encomenda);
        return;
    }
    /*o produto existe em sistema?*/
    if (existe_produto_sistema(id_produto) == NAO){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_produto);
        return;
    }
    local = procura_produto_encomenda(id_produto,id_encomenda);
    if (local != NAO)
        printf("%s %d.\n",encomendas[id_encomenda][local].descricao,encomendas[id_encomenda][local].stock);
    else
    {
        printf("%s %d.\n",sistema[id_produto].descricao,0);
    }
}

/*lista todos os produtos de uma encomenda por ordem alfabetica*/
void lista_encomenda(int id){
    int i;
    /*existe a encomenda?*/
    if (existe_encomenda(id) == NAO){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id);
        return;
    }  
    ordena(encomendas[id],0,tamanho_encomenda[id]-1,ALFABETICO);
    /*listagem dos produtos*/
    printf("Encomenda %d\n",id);
    for (i=0;i<tamanho_encomenda[id];i++){
        if (encomendas[id][i].stock != 0){
            printf("* %s %d %d\n",encomendas[id][i].descricao,
            encomendas[id][i].preco,encomendas[id][i].stock);
        }
    }

}

                        /*--------------Adiciona/remove-----------------------*/

/*Adiciona um produto a uma encomenda, verificando se este existe em sistema
com stock suficiente e se a encomenda existe tambem*/
void adicionar_produto_encomenda(int identificador_produto, int identificador_encomenda,int stock){
        int local;
        /*verificacao da existencia da encomenda*/
        if (existe_encomenda(identificador_encomenda) == NAO){
            printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",
            identificador_produto,identificador_encomenda);
            return;
        }
        /*verificacao da existencia da produto*/
        if (existe_produto_sistema(identificador_produto) == NAO){
            printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",
            identificador_produto,identificador_encomenda);
            return;
        }
        /* verificacao do stock do produto*/
        if (verfica_stock_produto(identificador_produto,stock) == NAO){
            printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
            identificador_produto,identificador_encomenda);
            return;
        }
        /*controlo do peso da encomenda*/
        if (verifica_peso_encomenda(identificador_encomenda,
            identificador_produto,stock) == NAO){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
            identificador_produto,identificador_encomenda);
            return;
        }
        local = procura_produto_encomenda(identificador_produto,identificador_encomenda);
        /*se nao, coloca o produto na encomenda*/
        if (local == NAO){
           encomendas[identificador_encomenda][tamanho_encomenda[identificador_encomenda]] = sistema[identificador_produto];
           encomendas[identificador_encomenda][tamanho_encomenda[identificador_encomenda]].stock = stock;
           tamanho_encomenda[identificador_encomenda]++;
        }
        /*se sim, aumenta a quantidade de produto na encomenda*/
        else
        {
             encomendas[identificador_encomenda][local].stock += stock;
        }
        sistema[identificador_produto].stock -= stock;
                
}

/*elimina um produto de uma encomenda*/
void remove_produto_encomenda(int id_encomenda,int id_produto){
    int local;
    /*a encomenda existe?*/
    if (existe_encomenda(id_encomenda) == NAO){
            printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",
            id_produto,id_encomenda);
            return;
    }
    /*o produto existe?*/
    if (existe_produto_sistema(id_produto) == NAO){
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",
            id_produto,id_encomenda);
            return;
    }
    /*procura o produto*/
    local = procura_produto_encomenda(id_produto,id_encomenda);
    if (local != NAO){
        /*remocao do produto da encomenda e recolocacao em stock*/
        sistema[id_produto].stock += encomendas[id_encomenda][local].stock;
        encomendas[id_encomenda][local].stock = 0;
    }

    
}


/*-------------------------------------------Manipulacao de sistema--------------------------------------------------------*/
                            /*-----------------------Auxiliares------------------------------------------*/


/*cria um novo produto*/
produto cria_produto(char descricao[],int preco,int peso, int stock,int id){
     produto novo;
     strcpy(novo.descricao,descricao);
     novo.peso = peso;
     novo.stock = stock;
     novo.preco = preco;
     novo.id = id;
     return novo;

}

/*verfica se um produto existe no sistema. Retorna presente caso
exista e nao caso contrario*/
int existe_produto_sistema(int identificador){
    if (sistema[identificador].peso != 0)
        return PRESENTE;
    else
    {
        return NAO;
    }
    
}

/*verifica se existe quantidade suficiente para a encomenda. Retorna presente
caso exista, retorna nao caso contrario*/
int verfica_stock_produto(int identificador,int quantidade){
    if (sistema[identificador].stock >=quantidade)
        return PRESENTE;
    else
    {
        return NAO;
    }  
}

/*lista os produtos por ordem crescente de preco*/
void lista_produtos_sistema(){
    int i;
    produto copia[MAX_PRODUTOS];
    /*copia o sistema para preservacao dos identificadores de produto*/
    copia_sistema(copia);
    ordena(copia,0,tamanho_sistema-1,PRECOS);
    printf("Produtos\n");
    for (i=0;i<tamanho_sistema;i++)
        printf("* %s %d %d\n",copia[i].descricao,copia[i].preco,copia[i].stock);
    
}
                /*---------------------------adicao/remocao------------------------------------------------*/
/*adiciona ao sistema um novo produto*/
void adiciona_sistema(char descricao[],int preco,int peso, int stock){
     produto novo_produto;
     novo_produto = cria_produto(descricao,preco,peso,stock,tamanho_sistema);
     sistema[tamanho_sistema] = novo_produto;
     printf("Novo produto %d.\n",tamanho_sistema);
     tamanho_sistema++;
}

/*Adiciona a quantidade inserida no produto. Caso o produto
nao exista retorna um erro*/
void adiciona_quantidade(int quantidade,int identificador){
    /*verifica a existencia do produto*/
    if (existe_produto_sistema(identificador) == PRESENTE)
        sistema[identificador].stock += quantidade;
    else /*nao existe, retorna erro*/
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",identificador);
    }  
}

/*reduz o stock de um produto em sistema*/
void remove_stock_sistema(int id_produto,int stock){
    /*o produto exite?*/
    if (existe_produto_sistema(id_produto) == NAO){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id_produto);
        return;
    }
    /*a quantidade e suficiete para tudo?*/
    if (sistema[id_produto].stock-stock < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",stock,id_produto);
        return;
    } 
    /*nao havendo problemas, remove a quantidade*/
    sistema[id_produto].stock -= stock;
}
 

/*------------------------------------------Outras funcoes----------------------------------------------*/


/*calcula o custo de uma encomenda*/
void calcula_custo(int id_encomenda){
    int i,custo_total = 0;
    /*a encomenda existe?*/
    if (existe_encomenda(id_encomenda) == NAO){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id_encomenda);
        return;
    }
    for (i=0;i<tamanho_encomenda[id_encomenda];i++)
        custo_total += encomendas[id_encomenda][i].preco * encomendas[id_encomenda][i].stock;
    printf("Custo da encomenda %d %d.\n",id_encomenda,custo_total);
}

/*altera o preco de um produto em sistema e nas encomendas em
que se encontra*/
void altera_preco(int id,int preco){
    int i,local;
    /*o produto existe em sistema?*/
    if (existe_produto_sistema(id) == NAO){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
        return;
    }
    sistema[id].preco = preco;
    /*alteracao do preco nas encomendas*/
    for (i=0;i<MAX_ENCOMENDAS && existe_encomenda(i) != NAO;i++){
        local = procura_produto_encomenda(id,i);
        if (local != NAO)
            encomendas[i][local].preco = preco;
    }
}

/*copia o sistema */
void copia_sistema(produto destino[]){
    int i;
    for (i=0; i< MAX_PRODUTOS &&i<tamanho_sistema;i++){
        destino[i] = sistema[i];
    }
}

/*procura a encomenda em que o produto ocorre mais vezes.
Imprime o id da encoemnda encontrada*/
void maior_quantidade_encomenda(int id_produto){
    int i,maior = NAO,quantidade = 0,local = NAO;
    /*o produto existe?*/
    if (existe_produto_sistema(id_produto) == NAO){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_produto);
        return;
    }
    /*procura a encomenda com a maior quantidade desse produto*/
    for (i=0;i<MAX_ENCOMENDAS && existe_encomenda(i) != NAO;i++){
        local = procura_produto_encomenda(id_produto,i);
        /*o produto existe na encomenda?*/
        if (local != NAO){
            /*a quantidade e superior as anteriores?*/
            if (encomendas[i][local].stock > quantidade){
                quantidade = encomendas[i][local].stock;
                maior = i;
            }
        }
    }
    if (maior != NAO)
        printf("Maximo produto %d %d %d.\n",id_produto,maior,quantidade);  
}

/*funcao auxiliar que junta os vetores de forma ordenada*/
void merge(produto a[], int left, int m, int right,int chave){
    int i, j, k;
    /*divisao do vetor*/
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    /*juncao de forma ordenada*/
    for (k = left; k <= right; k++)
        /*comparacao dos produtos*/
        if ((chave == PRECOS && aux[j].preco < aux[i].preco )|| 
            (chave ==  ALFABETICO && strcmp(aux[j].descricao,aux[i].descricao)<0) || i>m){
            a[k] = aux[j];
            j--;
        }
        else{
            a[k] = aux[i];
            i++;
        }
}

/*ordena o vetor dado de acordo com a chave fornecida,
ordem dos precos ou alfabetica. Utiliza o algoritmo merge sort*/
void ordena(produto a[], int left, int right,int chave){
    /*definicao do meio*/
    int m = (right+left)/2;
    if (right <= left) 
        return;
    ordena(a, left, m, chave);
    ordena(a, m+1, right, chave);
    merge(a, left, m, right,chave);
}


/*-----------------------------------main----------------------------------------------------------------*/
int main(){
     char c,descricao[DESCRICAO];

     int peso,preco,stock,identificador_produto,identificador_encomenda;

     while ((c = getchar()) != 'x'){

         switch (c){

             /*caso em que c == a, ie adicionar produto ao sistema*/
             case 'a':{
                 scanf(" %[^:]:%d:%d:%d",descricao,&preco,&peso,&stock);
                 adiciona_sistema(descricao,preco,peso,stock);
                 break;

             }/* caso em que c == q,ie adicionar quantidade a um produto*/
             case 'q':{
                 scanf("%d:%d",&identificador_produto,&stock);
                 adiciona_quantidade(stock,identificador_produto);
                 break;

             }
             /* caso em que c == N,ie cria uma nova encomenda*/
             case 'N':{
                 cria_encomenda();
                 break;

             }

             /*caso em que c == A,ie adiciona um produto a uma encomenda*/
             case 'A':{
                 scanf("%d:%d:%d",&identificador_encomenda,&identificador_produto,&stock);
                 adicionar_produto_encomenda(identificador_produto, identificador_encomenda,stock);
                 break;
             }

             /*caso em que c== r,ie reducao do stock de um produto em sistema*/
             case 'r':{
                 scanf("%d:%d",&identificador_produto,&stock);
                 remove_stock_sistema(identificador_produto,stock);
                 break;
             }

             /*caso  em que c == R,ie remocao de um produto numa encomenda*/
             case 'R':{
                scanf("%d:%d",&identificador_encomenda,&identificador_produto);
                remove_produto_encomenda(identificador_encomenda,identificador_produto);
                break;
             }

             /*caso em que c == C, ie calculo do custo de uma encomenda*/
             case 'C':{
                 scanf("%d",&identificador_encomenda);
                 calcula_custo(identificador_encomenda);
                 break;
             }

             /*caso em que c ==p,ie alteracao do preco de um produto*/
             case 'p':{
                 scanf("%d:%d",&identificador_produto,&preco);
                 altera_preco(identificador_produto,preco);
                 break;
             }

             /*caso em que c == E,listagem de um produto de uma encomenda*/
             case 'E':{
                 scanf("%d:%d",&identificador_encomenda,&identificador_produto);
                 lista_produto_encomenda(identificador_encomenda,identificador_produto);
                 break;
             }

             /*caso em que c == m, ie listagem da encomenda que tem mais produto*/
             case 'm':{
                 scanf("%d",&identificador_produto);
                 maior_quantidade_encomenda(identificador_produto);
                 break;
             }
             /*caso em que c == l,ie lista os produtos me sistema*/
            case 'l':{
                lista_produtos_sistema();
                break;
            }
            /*caso em que c == L, ie lista os produtos de uma encomenda*/
            case 'L':{
                scanf("%d",&identificador_encomenda);
                lista_encomenda(identificador_encomenda);
                break;
            }
        }
    }
    return 0;
    
}




