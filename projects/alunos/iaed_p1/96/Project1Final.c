#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/*Constantes utilizadadas*/
#define MAX_PRODUCTS 10000  
#define STR_LEN 63
#define MAX_WEIGHT 200
#define MAX_ORDER 500
#define MAX_ORDER_PROD 200
#define TRUE 1
#define FALSE 0

/*Criacao de uma estrutura que representa o produto("Product")*/
typedef struct{
    int id;
    char descrip[STR_LEN];
    int price;
    int weight;
    int stock;
}Product;

/*Criacao de uma estrutura que representa a encomenda("Order)*/
typedef struct{
    int nrProd;
    /*Coluna 0 -> ID do produto, Coluna 1 -> Qtd do produto*/
    int products[MAX_ORDER_PROD][2];   
}Order;

/*Incicializacao da funcao que ira receber o comando do utilizador e executar conforme o comando pedido*/
int scanCommand();
/*Inicializacao das funcoes dos comandos*/
void command_a();
void command_q();
void command_N();
void command_A();
void command_r();
void command_R();
void command_C();
void command_p();
void command_E();
void command_m();
void command_l();
void command_L();
void command_k();
void command_K();

/*Funcoes auxiliares*/
int orderWeight(int idO);
int orderCost(int idO);

/*Fun??es de ordena??o*/
void mergeSort(int ids[], int left, int right, int type);
void merge(int ids[], int left, int m, int right, int type);

/*Variaveis Globais*/
/*Numero de Ids de Produtos, ou seja, numero de produtos*/
int nrIds; 
/*Numero de Ids de Encomendas, ou seja, numero de encomendas*/                             
int nrOIds;  
/*Array com todos os produtos criados*/                           
Product warehouse[MAX_PRODUCTS];    
/*Array com todas as encomendas criadas*/
Order orders[MAX_ORDER];        

/*Entra num ciclo que chama a funcao scanCommand, quando a funcao retornar 0 o programa*/
int main()
{   
    int running = TRUE;                 
    while(running){                     
        running = scanCommand();
    }
    return 0;
}


/* Le o primeiro caracter do comando de modo a saber qual o comando a ser executado. 
Apos o saber chama a funcao auxiliar correspondente*/
int scanCommand(){
    char c;
    c = getchar();
    switch (c)
    {
    case 'a':
        command_a();
        break;
    case 'q':
        command_q();
        break;
    case 'N':
        command_N();
        break;
    case 'A':
        command_A();
        break;
    case 'r':
        command_r();
        break;
    case 'R':
        command_R();
        break;
    case 'C':
        command_C();
        break;
    case 'p':
        command_p();
        break;
    case 'E':
        command_E();
        break;
    case 'm':
        command_m();
        break;
    case 'l':
        command_l();
        break;
    case 'L':
        command_L();
        break;
    case 'x':
        return FALSE;
        break;
    default:
        break;
    }
    return TRUE;
}


/*Funcoes dos comandos*/
/*Nota: Em todas as fun??es que se seguem as seguintes variaveis correspondem a:
idP -> identificador do produto
idO -> identificador da encomenda
qtd -> quantidade do produto
*/
/*Comando 'a' - adiciona um novo produto ao sistema.*/
void command_a(){
    /*Cria um novo produto com os valores dados pelo utilizador*/
    Product newP;
    newP.id = nrIds;
    scanf(" %[^:]:%d:%d:%d", newP.descrip, &newP.price, &newP.weight, &newP.stock);
    /*Adiciona o novo produto ao armazem e incrementa o nr de Ids*/
    warehouse[nrIds] = newP;
    printf("Novo produto %d.\n", nrIds);
    nrIds++;
}

/*Comando 'q' - adiciona stock a um produto existente no sitema*/
void command_q(){
    /*Obtem os valores do itilizador*/
    int id, qtd;
    scanf(" %d:%d", &id, &qtd);
    /*Caso o produto exista adiciona ao seu stock (variavel dentro da estrutura)*/
    if(nrIds>id){
        warehouse[id].stock += qtd;
    }else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id);
    }

}

/*Comando 'N' - Cria uma nova encomenda*/
void command_N(){
    /*Cria a encomenda*/
    Order newOrder;
    newOrder.nrProd = 0;
    /*Adiciona a encomenda ao vetor das mesmas e incrementa o nr de Ids de encomenda*/
    orders[nrOIds] = newOrder;
    printf("Nova encomenda %d.\n", nrOIds);
    nrOIds += 1;
}

/*Comando 'A' - Adiciona um produto a uma enomenda, caso j? exista, adiciona a quantidade ao produto. */
void command_A(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idO, idP, qtd, i, nrProd;
    scanf(" %d:%d:%d", &idO, &idP, &qtd);
    if(idO >= nrOIds){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idP, idO);
    }else if(idP >= nrIds){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n" , idP, idO);
    }else if(qtd > warehouse[idP].stock){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idP, idO);
    }else if(orderWeight(idO) + qtd * (warehouse[idP].weight) > MAX_WEIGHT){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idP, idO);
    }else{
        /*Ciclo que percorre os ids de produtos dentro de uma encomenda e adiciona a quantidade caso ache algum id igual ao introduzido*/
        for (i = 0; i < orders[idO].nrProd; i++)
        {
            if(orders[idO].products[i][0] == idP){
                
                orders[idO].products[i][1] += qtd;
                warehouse[idP].stock -= qtd;
                return;
            }
        }
        /*Caso n?o tenha encontrado o produto pedido, adiciona-o*/
        nrProd = orders[idO].nrProd;
        orders[idO].products[nrProd][0] = idP;
        orders[idO].products[nrProd][1] = qtd;
        warehouse[idP].stock -= qtd;
        orders[idO].nrProd++;
    }
    
}

/*Command 'r' - remove stock de um produto existente*/
void command_r(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idP, qtd;
    scanf(" %d:%d", &idP, &qtd);
    if(idP >= nrIds){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idP);
    }else if(warehouse[idP].stock<qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idP);
    }else{
        /*Remove a quantidade pedida do produto indicado*/
        warehouse[idP].stock -= qtd;
    }
}

/*Command 'R' - Remove um produto de uma encomenda*/
void command_R(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idP, idO, i, troca = FALSE;
    scanf(" %d:%d", &idO, &idP);
    if (idO >= nrOIds){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idP, idO);
    }else if(idP >= nrIds){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idP, idO);
    }else{
        /*Ciclo que procura o produto com o id pedido pelo utilizador e ap?s o encontrar, elimina-o
        , e a partir desse ponto d? um shift para a esquerda no array de ids de produtos dentro da encomenda*/
        for (i = 0; i < orders[idO].nrProd; i++)
        {
            /*Shift do array para a esquerda*/
            if(troca){
                orders[idO].products[i-1][0] = orders[idO].products[i][0];
                orders[idO].products[i-1][1] = orders[idO].products[i][1];
            }
            if(idP == orders[idO].products[i][0] && !troca){
                warehouse[idP].stock += orders[idO].products[i][1];
                troca = TRUE;
                
            }
        }
        /*Caso tenha havido troca, decrementa o nr de produtos da encomenda*/
        if(troca){
            orders[idO].nrProd -= 1;
        }
        
    }
}

/*Command 'C' - Calcula o custo da encomenda*/
void command_C(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idO;
    scanf(" %d", &idO);
    if (idO >= nrOIds){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idO);
    }else{
        /*Calcula o custo da encomenda usando a funcao orderCost e imprime o valor */
        printf("Custo da encomenda %d %d.\n", idO, orderCost(idO));
    }
}

/*Command 'p' - altera o preco de um produto existente no sitema*/
void command_p(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idP, newPrice;
    scanf(" %d:%d", &idP, &newPrice);
    if (idP >= nrIds){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idP);
    }else{
        /*Altera o preco do produto no sistema*/
        warehouse[idP].price = newPrice;
    }
}

/*Command 'E' - lista a descricao e a quantidade de um produto numa encomenda*/
void command_E(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idP, idO, i;
    scanf(" %d:%d", &idO, &idP);
    if(idO >= nrOIds){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idO);
    }else if(idP >= nrIds){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idP);
    }else{
        /*Ciclo que percorre todos os produtos at? encontrar o com o id pedido pelo utlizador
        quando o encontrar, imprime os valores pedidos*/
        for (i = 0; i < orders[idO].nrProd; i++)
        {
            if(idP == orders[idO].products[i][0]){
                printf("%s %d.\n", warehouse[idP].descrip, orders[idO].products[i][1]);
                return;
            }
        }
        printf("%s %d.\n", warehouse[idP].descrip, 0);
        
    }
}

/*Command 'm' - lista o identificador da encomenda em que o produto ocorre mais vezes.*/
void command_m(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int idP, qtd = 0, idO, i, j;
    scanf(" %d", &idP);
    if(idP >= nrIds){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idP);
    }else{
        /*Ciclo que percorre todas as encomendas*/
        for (i = 0; i < nrOIds; i++)
        {
            /*Ciclo que percorre todos os produtos de uma encomenda ate achar o id pedido,
            apos isso guarda a quantidade desse produto e o ida da encomenda onde esta*/
            for (j = 0; j < orders[i].nrProd; j++)
            {
                if(idP == orders[i].products[j][0]){
                    /*Verifica se a quantidade do produto ? maior que a maior quantidade ate ao momento*/
                    if(qtd < orders[i].products[j][1]){
                        qtd = orders[i].products[j][1];
                        idO = i;
                        break;
                    }
                }
            }
        }
        if(qtd != 0){
            printf("Maximo produto %d %d %d.\n",  idP, idO, qtd);
        }
    }
}

/*Command 'l' - lista todos os produtos existentes no sistema por ordem crecente de preco*/
void command_l(){
    int i, ids[MAX_PRODUCTS];
    /*Ciclo cujo objetivo e criar um vetor comt todos os ids dos produtos*/
    for (i = 0; i < nrIds; i++)
    {
        ids[i] = i;
    }
    /*Ordena os ids por ordem crescente de preco*/
    mergeSort(ids, 0, nrIds -1, 1);
    /*Imprime os resultados*/
    printf("Produtos\n");
    for (i = 0; i < nrIds; i++)
    {
        printf("* %s %d %d\n", warehouse[ids[i]].descrip, warehouse[ids[i]].price, warehouse[ids[i]].stock);
    }
}

/*Command 'L' - Lista todos os produtos por ordem alfabetica da descricao*/
void command_L(){
    /*Obtem os valores do utilizador e verifica se tem erros*/
    int i, idO, ids[MAX_ORDER_PROD], qtds[MAX_PRODUCTS];
    scanf(" %d", &idO);
    if(idO >= nrOIds){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idO);
        return;
    }
    /*Ciclo cujo objetivo ecriar dois novos vetores, um com os ids dos produtos existentes na encomenda
    e outro com a quantidade presente na encomenda dos mesmos produtos*/
    for (i = 0; i < orders[idO].nrProd; i++)
    {
        ids[i] = orders[idO].products[i][0];
        qtds[ids[i]] = orders[idO].products[i][1];
    }
    /*Ordena os ids por ordem alfabetica*/
    mergeSort(ids, 0, orders[idO].nrProd - 1, 0);
    /*Imprime os resultados*/
    printf("Encomenda %d\n", idO);
    for (i = 0; i < orders[idO].nrProd; i++)
    {
        printf("* %s %d %d\n", warehouse[ids[i]].descrip, warehouse[ids[i]].price, qtds[ids[i]]);
    }
}

/*Funcoes auxiliares*/
/*orderWeght - Calcula o peso de uma encomenda*/
int orderWeight(int idO){
    int i, wt = 0;
    /*Ciclo que percorre todos os produtos de uma encomenda e vai adicionando o seu (peso*quantidade) a variavel wt*/
    for (i = 0; i < orders[idO].nrProd; i++)
    {
        wt += orders[idO].products[i][1]*(warehouse[orders[idO].products[i][0]].weight);
    }
    return wt;
}

/*orderCost - Calcula o custo da encomenda*/
int orderCost(int idO){
    int i, cost = 0;
    /*Ciclo que percorre todos os produtos de uma encomenda e vai adicionando o seu (preco*quantidade) a variavel cost*/
    for (i = 0; i < orders[idO].nrProd; i++)
    {
        cost += orders[idO].products[i][1]*(warehouse[orders[idO].products[i][0]].price);
    }
    return cost;
}

/*Funcoes de ordenacao*/
/*mergeSort - funcao principal do algoritmo de ordenacao Merge, o parametro type e usado para sabermos se queremos
ordenar pelo o preco(type = 1) do produto ou aflfabeticamente(type = 0)*/
void mergeSort(int ids[], int left, int right, int type){
    int m = (right + left) / 2;
    if (right <= left){
        return;
    }
    mergeSort(ids, left, m, type);
    mergeSort(ids, m+1, right, type);
    merge(ids, left, m , right, type);
}

/*merge - devolve um vetor ordernado em ids[left, right], quando dois vetores ordenados em ids[left, m]
e ids[m+1, right] s?o dados*/
int aux[MAX_PRODUCTS];
void merge(int ids[], int left, int m, int right, int type){
    int i, j, k;
    /*Construcao do vetor aux*/
    for (i = m+1; i > left; i--)
    {
        aux[i-1] = ids[i-1];
    }
    for (j = m; j < right; j++)
    {
        aux[right+m-j] = ids[j+1];
    }
    /*Escolhe os vetores das pontas e ordena-os*/
    for (k = left; k <= right; k++)
    {
        if(type){
            /*Caso seja ordenado pelo preco*/
            if (warehouse[aux[j]].price < warehouse[aux[i]].price)
            {
                ids[k] = aux[j--];
            }else if(warehouse[aux[j]].price > warehouse[aux[i]].price){
                ids[k] = aux[i++];
            }else{
                /*Caso os precos sejam iguais e comparado pelo id, sendo o merge um algoritmo estavel
                nao era suposto necessitar, porem o quando chegava ao preco maior deixava de ser estavel
                esta foi a unica solucao que encontrei*/
                if (aux[j]>aux[i]){
                    ids[k] = aux[i++];
                }else{
                    ids[k] = aux[j--];
                }
            }
        }else{
            /*Caso seja ordenado por ordem alfabetica*/
            if (strcmp(warehouse[aux[i]].descrip, warehouse[aux[j]].descrip) > 0){
                ids[k] = aux[j--];
            }else{
                ids[k] = aux[i++];
            }
        }
    }
}
