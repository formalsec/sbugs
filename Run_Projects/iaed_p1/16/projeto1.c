#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Maximo de caracteres na descricao de produto*/
#define MAX_s 63

/*Maximo de produtos possiveis no sistema*/
#define MAX_produtos 10000

/*Maximo de encomendas possiveis no sistema*/
#define MAX_encomendas 500

/*Maximo de peso (e tambem max de produtos) numa encomenda */
#define MAX_peso 200

/*Estrutura de um produto*/
typedef struct {
    int idp;
    char descricao[MAX_s];
    int preco;
    int peso;
    int quantidade;

} produto;

/*Estrutura de uma encomenda */
typedef struct {
    int ide;
    int lista[MAX_peso][2]; /*id do produto e quantidade requerida*/
    int peso_total;
    int custo_total;
    int total_produtos;
} encomenda;


/* Prototipo das funcoes */

void cria_produto();
void adiciona_s();
void cria_encomenda();
void adiciona_e();
void remove_s();
void remove_e();
void custo_e();
void altera_preco();
void lista_e();
void lista_ide();
void lista_produtos();
void lista_encomenda();
void mergesort_f(int a[][2], int l, int r);
void merge_f(int a[][2], int l, int m, int r);
void StringSort(char a[][MAX_s], int b[][2],int l,int r);

/*Numero de produtos ja criados*/
static int idp_atual = 0; 

/*Numero de encomendas ja criadas*/
static int ide_atual = 0; 


/*Lista de todos os produtos do sistema*/
produto Produtos[MAX_produtos];

/*Lista de todas as encomendas do sistema*/
encomenda Encomendas[MAX_encomendas];

/*Variavel auxiliar para a funcao mergesort_f*/
int aux[MAX_produtos][2];

/* Programa principal */

int main(){

    char comando;

    while ((comando = getchar()) != 'x'){

        switch (comando){
            case 'a':
                cria_produto();
                break;
            
            case 'q':
                adiciona_s(); /*adiciona stock a um produto*/
                break;
            
            case 'N':
                cria_encomenda(); /*cria uma nova encomenda*/
                break;

            case 'A':
                adiciona_e(); /*adiciona produto a uma encomenda*/
                break;

            case 'r':
                remove_s(); /*remove stock de um produto*/
                break;
            
            case 'R':
                remove_e(); /*remove produto de uma encomenda */
                break;

            case 'C':
                custo_e(); /* mostra custo total de uma encomenda*/
                break;

            case 'p':
                altera_preco(); /*altera preco de um produto*/
                break;
            
            case 'E':
                lista_e(); /*mostra a descricao e quantidade de um produto numa encomenda*/
                break;

            case 'm':
                lista_ide(); /*mostra a encomenda onde o produto aparece mais vezes*/
                break;

            case 'l':
                lista_produtos(); /*mostra os produtos do sistema por ordem crescente de preco*/
                break;
            
            case 'L':
                lista_encomenda(); /*lista produtos de uma encomenda por ordem alfabetica*/
                break;

            default:
                break;
             
        }
    }
    return 0;
}

/*Implementacao das funcoes*/


/*Adiciona um produto ao sistema logistico */
void cria_produto(){

    int qtd, preco, peso;

    char descricao[65];

    produto p;

    getchar();
    scanf("%[^:]:%d:%d:%d", descricao, &preco, &peso, &qtd);
           

    strcpy(p.descricao, descricao);

    p.idp = idp_atual;
    p.peso = peso;
    p.preco = preco;
    p.quantidade = qtd;

    /* Adicionar produto a lista de produtos */
    Produtos[idp_atual] = p;
    
    printf("Novo produto %d.\n", idp_atual);
    idp_atual++;
    
}

/*Adiciona unidades ao stock de um produto*/
void adiciona_s(){

    int idp, qtd;

    getchar();
    scanf("%d:%d", &idp, &qtd);

    if (idp_atual <= idp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else
    {
        Produtos[idp].quantidade += qtd;  
    }   
}


/*Adiciona uma encomenda ao sistema logistico*/
void cria_encomenda(){

    Encomendas[ide_atual].ide = ide_atual;
    Encomendas[ide_atual].custo_total = 0;
    Encomendas[ide_atual].peso_total = 0;
    Encomendas[ide_atual].total_produtos = 0;
    printf("Nova encomenda %d.\n", ide_atual);
    ide_atual++;
}


/*Adiciona uma quantidade de um produto a uma encomenda*/
void adiciona_e(){

    int ide, idp, qtd;
    
    getchar();
    scanf("%d:%d:%d", &ide, &idp, &qtd);

    if (ide >= ide_atual)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    }
    else if (idp >= idp_atual)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    }
    else if (qtd > Produtos[idp].quantidade)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

    }
    else if (Produtos[idp].peso * qtd + Encomendas[ide].peso_total > 200)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    
    else {
        encomenda e = Encomendas[ide];

        int procura = 1;        /*indica que ainda nao encontramos o produto na encomenda*/
            
        int i = 0;
        while (i < e.total_produtos && procura){
                
            if(e.lista[i][0] == idp){

                procura = 0;    /*encontrou o produto na encomenda*/
                /*Atualizar dados da encomenda */
                Encomendas[ide].lista[i][1] += qtd;
                Encomendas[ide].peso_total += Produtos[idp].peso * qtd;
                Encomendas[ide].custo_total += Produtos[idp].preco * qtd;

                /*Atualizar stock do produto */
                Produtos[idp].quantidade -= qtd;
                }
            i++;       
        }
        /*novo produto na encomenda */
        if (procura == 1){
            /*Adicionar produto a encomenda*/
            Encomendas[ide].lista[e.total_produtos][0] = idp;
            Encomendas[ide].lista[e.total_produtos][1] = qtd;
            Encomendas[ide].total_produtos += 1;
            Encomendas[ide].peso_total += Produtos[idp].peso * qtd;
            Encomendas[ide].custo_total += Produtos[idp].preco * qtd;

            /*Atualizar stock do produto*/
            Produtos[idp].quantidade -= qtd;                           
        }   
    }
}


/*Remove unidades do stock de um produto*/
void remove_s(){

    int idp, qtd;

    getchar();
    scanf("%d:%d", &idp, &qtd);

    if (idp >= idp_atual){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }

    else if (Produtos[idp].quantidade - qtd < 0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }

    else
    {
        Produtos[idp].quantidade -= qtd;
    }
}

/*Remove um produto de uma encomenda*/
void remove_e(){
    int ide, idp;
    getchar();
    scanf("%d:%d", &ide, &idp);

    if (ide >= ide_atual){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    else if (idp >= idp_atual){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    else
    {
        int qtd, k;
        int i;
        encomenda e = Encomendas[ide];

        for (i = 0; i < e.total_produtos; i++){
            if (e.lista[i][0] == idp){      /*Verificar se o produto esta na encomenda*/
                qtd = e.lista[i][1];        
                for (k = i; k < e.total_produtos - 1; k++){     /*Apagar esse produto da lista da encomenda*/
                    Encomendas[ide].lista[k][0] = e.lista[k+1][0]; /*e passar todos os produtos a esquerda*/
                    Encomendas[ide].lista[k][1] = e.lista[k+1][1]; /*um indice para tras*/
                }      
                /*Atualizar dados da encomenda*/
                Encomendas[ide].total_produtos -= 1;
                Encomendas[ide].custo_total -= Produtos[idp].preco * qtd;
                Encomendas[ide].peso_total -= Produtos[idp].peso * qtd;
                Produtos[idp].quantidade += qtd;
            }
        }
    }
    
}

/*Mostra o custo total de uma encomenda*/
void custo_e(){
    int ide;

    getchar();
    scanf("%d", &ide);

    if (ide >= ide_atual){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        printf("Custo da encomenda %d %d.\n", ide, Encomendas[ide].custo_total);
    }
}


/*Altera o preco de um produto*/
void altera_preco(){
    int idp, preco;
    
    getchar();
    scanf("%d:%d",&idp, &preco);

    if (idp >= idp_atual){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        int i, j, diff;

        diff = preco - Produtos[idp].preco; /*diferenca do novo preco e do anterior*/
        Produtos[idp].preco = preco;        

        /*Percorrer cada encomenda ja criada*/

        for (i = 0; i < ide_atual; i++){
            encomenda e = Encomendas[i];

            /*Percorrer a lista dos produtos para ver se o produto la esta*/
            for (j = 0; j < e.total_produtos; j++){
                int p = e.lista[j][0];
                int q = e.lista[j][1];
                if (p == idp){          /*Se la estiver mudar o custo total da encomenda */ 
                    Encomendas[i].custo_total += (diff * q);
                }
            }
        }
    }
   
}

/*Mostra a descricao e a quantidade de um produto numa encomenda*/
void lista_e(){

    int ide, idp;
    getchar();
    scanf("%d:%d", &ide, &idp);

    if (ide >= ide_atual){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (idp >= idp_atual){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        /*Procurar produto na lista para saber quantidade */
        encomenda e = Encomendas[ide];
        int q, i; 
        q = 0;          /*Se o produto nao estiver na encomenda tem quantidade 0*/
        for (i = 0; i < e.total_produtos; i++){
            if (e.lista[i][0] == idp){
                q = e.lista[i][1];
            }
        }
        printf("%s %d.\n", Produtos[idp].descricao, q);
    }
}

/*Mostra a encomenda em que o produto dado ocorre mais vezes*/
void lista_ide(){
    int idp, max, ide, i, j;
    getchar();
    scanf("%d", &idp);
    max = -1;       /*Considera-se max inicial= -1 para indicar que ainda nao foi encontrado na encomenda*/


    if (idp >= idp_atual){
       printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        for (i = 0; i < ide_atual; i++){        /*Percorrer todas as encomendas*/
            encomenda e = Encomendas[i];
            for (j = 0; j < e.total_produtos; j++){ /* Procurar na encomenda se o produto esta na lista */
                if (e.lista[j][0] == idp && e.lista[j][1] > max){
                    /*se a quantidade do produto for maior que o max atual, altera se*/
                    max = e.lista[j][1];
                    ide = e.ide;
                }
            }        
        }

        if (max >= 0){         
            printf("Maximo produto %d %d %d.\n", idp, ide, max);
        }
    }
}

/*Apresenta os produtos criados no sistema por ordem de preco*/
void lista_produtos(){  
    int idp, i, id, preco;    
    int lista[MAX_produtos][2]; 

    /*Cria se um array auxxiliar de 2 colunas com o preco e o idp de cada produto do sistema*/
    for (idp = 0; idp < idp_atual; idp++){
        lista[idp][0] = Produtos[idp].preco;
        lista[idp][1] = Produtos[idp].idp;
    }

    /*Ordenar por preco*/
    mergesort_f(lista, 0, idp_atual-1);
       
    
    printf("Produtos\n");
    for (i = 0; i < idp_atual;i++){
        id = lista[i][1];
        preco = lista[i][0];
        printf("* %s %d %d\n", Produtos[id].descricao, preco, Produtos[id].quantidade);
    }
}

/*Apresenta os produtos de uma encomenda por ordem alfabetica*/
void lista_encomenda(){
    int ide, i, idp;
    encomenda e;
    char lista[MAX_peso][MAX_s];
    getchar();
    scanf("%d", &ide);
    e = Encomendas[ide];

    if (ide >= ide_atual){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        /*Cria-se um array auxiliar com a descricao de cada produto */
        for (i = 0; i < e.total_produtos; i++){
            idp = e.lista[i][0];
            strcpy(lista[i], Produtos[idp].descricao);
        }

        /*Ordenar a lista com as descricoes; o array com os ids do produto entra como parametro para 
        indicar a que produto corresponde cada descricao*/
        StringSort(lista, e.lista, 0, e.total_produtos - 1);

        printf("Encomenda %d\n", ide);

        for (i = 0; i < e.total_produtos; i++){
            idp = e.lista[i][0];
            printf("* %s %d %d\n", lista[i], Produtos[idp].preco, e.lista[i][1]);
        }      
    }
}

/*Algoritmo de ordenacao baseado no merge */
void merge_f(int a[][2], int l, int m, int r){

    int i, j, k;
    
    /*em paralelo, tambem sao copiados os ids respetivos do produto para acompanhar a ordenacao do preco*/
    for ( i = m + 1; i > l; i--){
        aux[i-1][0] = a[i-1][0];
        aux[i-1][1] = a[i-1][1];
    }
    for (j = m; j< r; j++){
        aux[r+m-j][0] = a[j+1][0];
        aux[r+m-j][1] = a[j+1][1];

    } 
    for (k = l; k <= r; k++){
        /*criterio de desempate e o id do produto*/
        if((aux[j][0] < aux[i][0]) ||(aux[j][0] == aux[i][0] && aux[j][1] < aux[i][1]) ){
            a[k][0] = aux[j][0];
            a[k][1] = aux[j][1];
            j--;
        }      
        else{
            a[k][0] = aux[i][0];
            a[k][1] = aux[i][1];
            i++;
        }
    }
}

/*Algoritmo de ordenacao baseado no mergesort*/
void mergesort_f(int a[][2], int l, int r){
    int m;
    if (r > l){

        m = (r+l) / 2;
        mergesort_f(a, l, m); 
        mergesort_f(a, m+1, r);
        merge_f(a, l, m , r);
    }
}


/*Algoritmo de ordenacao baseado no selectionsort*/
void StringSort(char a[][MAX_s],int b[][2],int l,int r){
    int i, j, min;
    for ( i = l; i < r; i++){
        char aux[MAX_s];
        int id_aux[2];
        min = i;    
        for (j = i + 1; j <=r; j++){
            if (strcmp(a[j], a[min]) <= 0){
                min = j;
            }
        }
        /*Em paralelo, tambem e copiado o id do produto para ficar em correspondencia com a respetiva descricao*/
        strcpy(aux, a[i]);
        id_aux[0] = b[i][0];
        id_aux[1] = b[i][1];

        strcpy(a[i], a[min]);
        b[i][0] = b[min][0];
        b[i][1] = b[min][1];

        strcpy(a[min], aux);
        b[min][0] = id_aux[0];
        b[min][1] = id_aux[1];
    }
}
