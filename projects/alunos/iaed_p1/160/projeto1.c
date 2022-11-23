#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define desc 63
#define id_max 10000
#define encomenda_max 500
#define peso_maximo 200
int id_num = 0; /*guardar o id do produto onde estamos onde estamos*/
int id_encomenda = 0; /*guarda o id da encomenda onde estamos */

typedef struct produto{ /* estrutura dos produtos com id,desc,preco,peso,stock*/
    int id;
    char descricao[desc]; 
    int preco;
    int peso;
    int stock;
}produto;

typedef struct encomenda{ /* estrutura das encomendas,com um conjunto de estruturas de produtos,id da encomenda,se existe,peso total*/
    int id;
    struct produto fila[id_max];
    int peso_total;
    int existe;
}encomenda;

/*criacao dos arrays com as estruturas*/
struct encomenda encomendas[encomenda_max]; 

struct produto produtos[id_max];

/*Formato de entrada: `a descricao:preco:peso:qtd`
 Formato de sa?da: `Novo produto <idp>.` onde `<idp>` ? o identificador do produto criado.
*/
void executa_a(){
    if (id_num < id_max)
    {
    produtos[id_num].id = id_num; 
    /*guarda os dados lidos dentro do array com o que caracteriza o produto*/
    scanf(" %[^:]:%d:%d:%d",produtos[id_num].descricao,&produtos[id_num].preco,&produtos[id_num].peso,&produtos[id_num].stock);
    printf("Novo produto %d.\n",produtos[id_num].id);
    id_num = id_num + 1;
    }
}

/*adiciona stock a um produto existente no sistema
  * Formato de entrada: `q idp:qtd`
  * Formato de sa?da: NADA (excepto erro)*/
void executa_q(){
    int id_local,qtd;
    scanf(" %d:%d",&id_local,&qtd);
    if (produtos[id_local].preco == 0){ /*ver se existe o produto*/
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id_local); 
    }
    else{
        produtos[id_local].stock = produtos[id_local].stock + qtd; /*aumentar o stock do produto dentro dos arrays*/
    } 
}
/*cria uma nova encomenda
  * Formato de entrada: `N`
  * Formato de sa?da: `Nova encomenda <ide>.` onde `<ide>` ? o identificador da encomenda criada.*/
void executa_N(){
    if (id_encomenda < encomenda_max)
    {
    encomendas[id_encomenda].peso_total = 0; 
    encomendas[id_encomenda].id = id_encomenda; 
    encomendas[id_encomenda].existe = 1; /*cria uma encomenda mudando este numero para 1*/
    printf("Nova encomenda %d.\n",id_encomenda);
    id_encomenda = id_encomenda + 1; /*prepara o id para a proxima encomenda*/
    }
    
   
}

/*adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente
  * Formato de entrada: `A ide:idp:qtd`
  * Formato de sa?da: NADA (excepto erro)*/
void executa_A(){
    int ide,idp,qtd;
    scanf(" %d:%d:%d",&ide,&idp,&qtd); 
    if (encomendas[ide].existe != 1){ /* ver se existe encomenda*/
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    else if (produtos[idp].preco == 0){ /*ve se existe produto*/
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }
    else if (produtos[idp].stock < qtd){ /*ver  se a quantidade e suficiente*/
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
    }
    else if (produtos[idp].peso*qtd + encomendas[ide].peso_total > peso_maximo){ /*ver se o peso ultrapassa 200*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n",idp,ide,peso_maximo);
    }
    else
    {
        /* ver se o produto ja existe na encomenda*/
        if (encomendas[ide].fila[idp].peso != 0)
        {
            encomendas[ide].fila[idp].stock = encomendas[ide].fila[idp].stock + qtd;
        }
        else
        {
            encomendas[ide].fila[idp] = produtos[idp]; /*se nao existir meter na encomenda, adicionar*/
            encomendas[ide].fila[idp].stock = qtd; /*mudar o stock para a quantidade que metemos na encomenda*/
        }
        produtos[idp].stock = produtos[idp].stock - qtd; /*tirar a quantidade do produto que metemos na encomenda*/
        encomendas[ide].peso_total= encomendas[ide].peso_total + produtos[idp].peso*qtd; /*adicionar ao peso da encomenda*/
    }
    
}

/*lista a descri??o e a quantidade de um produto numa encomenda
  * Formato de entrada: `E ide:idp`
  * Formato de sa?da: `<desc> <qtd>.` onde `<desc>` ? a descri??o do produto `<idp>` e `<qtd>` ? a quantidade desse produto na encomenda `<ide>`*/

void executa_E(){
    int ide,idp;
    scanf(" %d:%d",&ide,&idp);
    if (encomendas[ide].existe != 1){ /*ver se existe encomenda*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }
    else if (produtos[idp].preco == 0){ /*ver se o produto esta na encomenda*/
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
    }
    else{
        printf("%s %d.\n",produtos[idp].descricao,encomendas[ide].fila[idp].stock);/*por a descricao e por o stock na encomenda*/
    }
}

void quicksort_l(int ordenado[id_max],int first,int last){
    int i, j, pivot, temp;
    if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){ /*comparar o preco do ordenado com o do pivot*/
         while(produtos[ordenado[i]].preco <= produtos[ordenado[pivot]].preco &&i<last){
            if (produtos[ordenado[i]].preco == produtos[ordenado[pivot]].preco){ /*se forem iguais comparar os ids*/ 
               if (produtos[ordenado[i]].id > produtos[ordenado[pivot]].id){
                    break;
                }
            }
            i++; }
         while(produtos[ordenado[j]].preco >= produtos[ordenado[pivot]].preco &&j>first){ /*comparar o preco do ordenado com o pivot*/
            if (produtos[ordenado[j]].preco == produtos[ordenado[pivot]].preco){ /*se forem iguais comparar os ids*/
                if (produtos[ordenado[j]].id < produtos[ordenado[pivot]].id){
                    break;
                }
            }
            j--;
        }
         if(i<j){ /*se o i<j, trocar o dentro do array o item de ordem j e i*/
            temp=ordenado[i];
            ordenado[i] = ordenado[j];
            ordenado[j] = temp;
         }
      }
      /*trocar dentro do array a ordem do item do pivot e do j*/
      temp=ordenado[pivot];
      ordenado[pivot] = ordenado[j];
      ordenado[j] = temp;
      /*fazer o quicksort a direita do pivot e a esquerda*/
      quicksort_l(ordenado,first,j-1);
      quicksort_l(ordenado,j+1,last);

   }
}


/*lista todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo pre?o, dever? imprimir esses por ordem crescente de `id` de produto
  * Formato de entrada: `l`
  * Formato de sa?da: Um bloco, e em que os produtos s?o listados por ordem crescente de pre?o*/

void executa_l(){
    int maior, i;
    int ordenado[id_max];
    maior = id_num; 
    for (i=0; i < maior;i++){
        ordenado[i] = i; /*Ids dentro do ordenado igual ao produtos*/
    }
    quicksort_l(ordenado,0,maior-1);
    printf("Produtos\n");
    for (i=0;i < maior;i++){ /*print aos produtos na ordem do ordenado*/
        printf("* %s %d %d\n",produtos[ordenado[i]].descricao,produtos[ordenado[i]].preco,produtos[ordenado[i]].stock);
    }
}

/*remove stock a um produto existente
  * Formato de entrada: `r idp:qtd`
  * Formato de sa?da: NADA (excepto erro)*/
void executa_r(){
    int idp,qtd;
    scanf(" %d:%d",&idp,&qtd);
    if (produtos[idp].preco == 0){/*ver se existe produto*/
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        }
    else if (produtos[idp].stock - qtd < 0){/*ver se o stock e suficiente*/
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
    }
    else
    {
        produtos[idp].stock = produtos[idp].stock - qtd; /*subtrair a quantidade ao produto*/
    }
}

/*remove um produto de uma encomenda
  * Formato de entrada: `R ide:idp`
  * Formato de sa?da: NADA (excepto erro)*/
void executa_R(){
    int ide,idp;
    scanf(" %d:%d",&ide,&idp);
    if (encomendas[ide].existe != 1){ /*ver se encomenda existe*/
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
    }
    else if (produtos[idp].preco == 0){/*ver se produto existe*/
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
    }
    else
    {
        if (encomendas[ide].fila[idp].peso != 0) /*se o produto existe*/
        {
            produtos[idp].stock = encomendas[ide].fila[idp].stock + produtos[idp].stock; /*por o stock nos produtos*/
            encomendas[ide].peso_total = encomendas[ide].peso_total - encomendas[ide].fila[idp].stock*produtos[idp].peso;/*tiar ao peso total*/
            encomendas[ide].fila[idp].stock = 0; /*por stock a zero*/
        }
        
    }
    
}
void quicksort_L(int ordenado[encomenda_max],int first,int last, int ide){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(strcmp(encomendas[ide].fila[ordenado[i]].descricao,encomendas[ide].fila[ordenado[pivot]].descricao) <= 0 && i<last){/*comparar as descricoes dos ids dentro do ordenado*/
            i++;}
         while(strcmp(encomendas[ide].fila[ordenado[j]].descricao,encomendas[ide].fila[ordenado[pivot]].descricao) > 0){/*comparar as descricoes dos ids dentro do ordenado as descricoes*/
            j--;}
         if(i<j){/*trocar dentro do ordenado o item de ordem i e j*/
            temp=ordenado[i];
            ordenado[i]=ordenado[j];
            ordenado[j]=temp;
         }
      }/*trocar o item com ordem pivot e j*/
      temp=ordenado[pivot];
      ordenado[pivot]=ordenado[j];
      ordenado[j]=temp;
      /*quick sort a esquerda do pivot e a direita*/
      quicksort_L(ordenado,first,j-1,ide);
      quicksort_L(ordenado,j+1,last,ide);

   }
}


 /*lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o
  * Formato de entrada: `L <ide>`
 * Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem alfab?tica de descri??o*/
void executa_L(){
    int maior, i,ide;
    int ordenado[id_max];
    maior = 0;
    scanf("%d",&ide);
    if (encomendas[ide].existe != 1){ /* ver se existe encomenda*/
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
    }
    else
    {
        for (i=0;i != id_num; i++){
            if (encomendas[ide].fila[i].peso != 0)
            {
                ordenado[maior] = encomendas[ide].fila[i].id; /*guardar os ids dos produtos que ha na encomenda*/
                maior = maior +1; /*guardar o numero de produtos que ha*/
            }
        }
        quicksort_L(ordenado,0,maior-1,ide);
        printf("Encomenda %d\n",ide);
        for (i=0; i < maior; i++){
            if (encomendas[ide].fila[ordenado[i]].stock > 0) /* print so se o stock for maior que zero*/
            {
                printf("* %s %d %d\n",encomendas[ide].fila[ordenado[i]].descricao,produtos[ordenado[i]].preco,encomendas[ide].fila[ordenado[i]].stock);
            }
        }
    }

}
/*calcula o custo de uma encomenda
  * Formato de entrada: `C ide`
  * Formato de sa?da: `Custo da encomenda <ide> <total>.` onde `<total>` ? o valor total da encomenda `<ide>`*/

void executa_C(){
    int ide,total,i;
    total =0;
    scanf("%d",&ide);
    if (encomendas[ide].existe != 1){/*ver se existe encomenda*/
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
    }
    else
    {
        for (i=0; i< id_num; i++){
            if (encomendas[ide].fila[i].stock != 0) /*se o stock for maior que zero*/
            {
                total = encomendas[ide].fila[i].stock*encomendas[ide].fila[i].preco + total;/*somar ao preco total os precos vezes encomendas*/
            }
        }
        printf("Custo da encomenda %d %d.\n",ide,total);
    } 
    
}

/*altera o pre?o de um produto existente no sistema
  * Formato de entrada: `p idp:preco`
  * Formato de sa?da: NADA (excepto erro)*/

void executa_p(){
    int idp,price,i;
    scanf("%d:%d",&idp,&price);
    if (produtos[idp].preco == 0){ /*ver se o produto existe*/
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
    }
    else
    {
        produtos[idp].preco = price; /*mudar o preco do produto*/
        for (i = 0; encomendas[i].existe == 1; i++){ /*mudar o preco de todas as encomendas que existem*/
            if (encomendas[i].fila[idp].preco !=0){
                encomendas[i].fila[idp].preco = price;
            }
           }
    }
    
}


/*lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor `id`.
  * Formato de entrada: `m idp`
  * Formato de sa?da:
    * `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` ? o n?mero da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`
    * N?o dever? listar nada caso o produto `<idp>` n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas*/
void executa_m(){
    int idp,i,id_do_maximo,numero_maximo;
    scanf("%d",&idp);
    if (produtos[idp].peso != 0){ /*ver se o produto existe*/
        numero_maximo = 0;
        id_do_maximo = 0;
        for (i=0; encomendas[i].existe == 1;i++){ 
            if (encomendas[i].fila[idp].stock > numero_maximo){/*se o stock for maior que o stock maximo ate agora*/
                numero_maximo = encomendas[i].fila[idp].stock; /*trocar os dados para esta encomenda*/
                id_do_maximo = i;
            }
        }
        if (numero_maximo > 0) /*se o produto estiver em pelo menos uma encomenda, print*/
        {
            printf("Maximo produto %d %d %d.\n",idp,id_do_maximo,numero_maximo);
        }   
    }
    else
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
    }
    
}

int main(){
    char command;
    while (1) {
        command = getchar(); /*primeira letra e lida e comparada com as letras do comandos existentes*/
        switch (command){
            case 'a':
                executa_a();
                break;
            case 'q':
                executa_q();
                break;
            case 'N':
                executa_N();
                break;
            case 'A':
                executa_A();
                break;
            case 'E':
                executa_E();
                break;
            case 'l':
                executa_l();
                break;
            case 'r':
                executa_r();
                break;
            case 'R':
                executa_R();
                break;
            case 'L':
                executa_L();
                break;
            case 'C':
                executa_C();
                break;
            case 'p':
                executa_p();
                break;
            case 'm':
                executa_m();
                break;
            case 'x':
                return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}


