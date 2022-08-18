#include <stdio.h>
#include <string.h>
#define MAXPROD 10000
#define MAXENCM 500
#define MAXPESOENCM 200
#define MAXCSTRING 63
#define MAXPRODENCM 200

/* definir o tipo produto */

typedef struct {
    int idp;
    char descricao[MAXCSTRING];
    int preco;
    int peso;
    int qtd;
    }Produto;

/* declarar todas as funcoes */

void novo_produto();
void adiciona_stock();
void remove_stock();
void altera_preco();
void cria_encomenda();
void adiciona_produto_encomenda();
void remove_produto_encomenda();
void custo_encomenda();
void lista_descricao_qtd();
void lista_ide();
void lista_sistema();
void quick_sort_sistema(Produto arr[], int low, int high);
int particao (Produto arr[], int low, int high);
void troca(Produto arr[], int a, int b);
int lim_sup(Produto arr[]);
void lista_encomenda();

/* declarar o sistema de produtos e o sistema de encomendas */

Produto encomendas[MAXENCM][MAXPRODENCM];
Produto sistema[MAXPROD];

Produto produto_vazio = {-1,"vazio",0,0,0};

/* switch para os diferentes comandos at? o comando ser == 'x', em que o programa termina */
int main(){

    char comando;
    int i, e;
    

    for (i=0; i<MAXPROD; i++){   /* inicializar o sistema com todas as slots como um produto vazio */ 
        sistema[i] = produto_vazio;
    }
    
    for (i=0; i<MAXENCM; i++){    /* inicializar o sistema de encomendas com todas as slots como um produto vazio */
        for (e=0; e<MAXPRODENCM; e++){
            encomendas[i][e] = produto_vazio;
        }
    }

    do{     
        switch (comando = getchar()){
        
            case 'a':
                novo_produto();
                break;
            case 'q':  
                adiciona_stock();
                break;
            case 'r':
                remove_stock();
                break;
            case 'p':
                altera_preco();
                break;
            case 'N':
                cria_encomenda();
                break;
            case 'A':
                adiciona_produto_encomenda();
                break;
            case 'R':
                remove_produto_encomenda();
                break;
            case 'C':
                custo_encomenda();
                break;
            case 'E':
                lista_descricao_qtd();
                break;
            case 'm':
                lista_ide();
                break;
            case 'l':
                lista_sistema();
                break;
            case 'L':
                lista_encomenda();
                break;
        }
    }while (comando != 'x');
    
    return 0;
}


/* cria um produto novo, atribui-lhe um id unico, e guarda-o no sistema de produtos */
void novo_produto(){

    Produto novo_produto;
    int i;

    scanf(" %[^:]:%d:%d:%d", novo_produto.descricao, &novo_produto.preco, &novo_produto.peso, &novo_produto.qtd);

    for (i=0; i<MAXPROD; i++){    /* encontra uma slot vazia para o novo produto */
        if (sistema[i].idp == produto_vazio.idp){
            novo_produto.idp = i;
            sistema[i] = novo_produto;
            break;
        }   
    }

    printf("Novo produto %d.\n",i);
}

/* adiciona stock a um produto existente no sistema */
void adiciona_stock(){

    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);

    else
        sistema[idp].qtd = (sistema[idp].qtd) + qtd;
    
}

/* remove stock a um produto existente no sistema */
void remove_stock(){

    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

    else if (sistema[idp].qtd < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);

    else
        sistema[idp].qtd -= qtd;
}

/* altera o preco de um produto existente no sistema */
void altera_preco(){

    int idp, preco, i, e;

    scanf("%d:%d", &idp, &preco);

    if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

    else{
        sistema[idp].preco = preco; /* altera preco no sistema */

        for (i=0; encomendas[i][0].idp >= 0; i++){  /* altera o preco do produto nas encomendas */
            for (e=0; encomendas[i][e].idp >= 0; e++){
                if (encomendas[i][e].idp == idp){
                    encomendas[i][e].preco = preco;
                }
            }
        }
    }
}

/* cria uma encomenda definindo o id do produto na primeira slot da encomenda como -2, estando assim a encomenda aberta */
void cria_encomenda(){

    int i;

    for (i=0; i<MAXENCM; i++){
        if (encomendas[i][0].idp == produto_vazio.idp){
            encomendas[i][0].idp = -2;
            break;
        }
    }

    printf("Nova encomenda %d.\n",i);
}

/* adiciona um produto a uma encomenda num certa quantidade */
void adiciona_produto_encomenda(){

    int ide, idp, qtd, peso_encomenda = 0, i;

    scanf("%d:%d:%d", &ide, &idp, &qtd);

    if (encomendas[ide][0].idp != produto_vazio.idp){    /* calcula o peso atual da encomenda */
        for (i=0; encomendas[ide][i].idp >= 0; i++){
            peso_encomenda += (encomendas[ide][i].peso * encomendas[ide][i].qtd);
        }
    }

    if (encomendas[ide][0].idp == produto_vazio.idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else if (sistema[idp].qtd < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

    else if ((peso_encomenda + (sistema[idp].peso * qtd)) > MAXPESOENCM)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

    else{
        for (i=0; i<MAXPRODENCM; i++){    
            if (encomendas[ide][i].idp == idp){   /* se o produto ja se encontrar na encomenda adiciona a quantidade ao produto */
                encomendas[ide][i].qtd += qtd;    /* na encomenda e retira a quantidade ao sistema de produtos */
                sistema[idp].qtd -= qtd;
                break;
            }
            if (encomendas[ide][i].idp < 0){         /* no caso de o produto ainda nao estar na encomenda vai adiciona-lo a */
                encomendas[ide][i] = sistema[idp];   /* encomenda na quantidade pedida e retirar essa quantidade ao sistema de produtos*/
                encomendas[ide][i].qtd = qtd;
                sistema[idp].qtd -= qtd;
                break;
            }
        }
    }
}

/* remove um produto de uma encomenda e devolve a quantidade de produto na encomenda ao sistema de produtos */
void remove_produto_encomenda(){

    int ide, idp, i, e;

    scanf("%d:%d", &ide, &idp);

    if (encomendas[ide][0].idp == produto_vazio.idp)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else{

        for (i=0; i<MAXPRODENCM; i++){               /* remove o produto da encomenda transformando todos os produtos no seu pr?ximo */
            if (encomendas[ide][i].idp == idp){     /* e devolve a quantidade de produto na encomenda ao sistema de produtos */
                sistema[idp].qtd += encomendas[ide][i].qtd;
                for(e=i; encomendas[ide][e].idp != produto_vazio.idp; e++){
                    encomendas[ide][e] = encomendas[ide][e+1];
                }
                break;
            }
        }

        if (encomendas[ide][0].idp == -1)   /* no caso de todos os produtos terem sido removidos da encomenda */
            encomendas[ide][0].idp = -2;     /* esta continua aberta sendo o id do primeiro produto -2 */
    }
}

/* calcula o preco total da encomenda */
void custo_encomenda(){

    int ide, i, total = 0;

    scanf("%d", &ide);

    if (encomendas[ide][0].idp == produto_vazio.idp)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else{
        for (i=0; encomendas[ide][i].idp >= 0; i++){
            total += (encomendas[ide][i].preco * encomendas[ide][i].qtd);
        }

        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}

/* lista a descricao e a quantidade do produto na encomenda pedida */
void lista_descricao_qtd(){

    int ide, idp, i;

    scanf("%d:%d", &ide, &idp);

    if (encomendas[ide][0].idp == produto_vazio.idp)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else{
        for (i=0; encomendas[ide][i].idp >= 0; i++){
            if (encomendas[ide][i].idp == idp){
                printf("%s %d.\n", encomendas[ide][i].descricao, encomendas[ide][i].qtd);
                break;
            }
        }
        if (encomendas[ide][i].idp != idp)    /* no caso de o produto nao estar na encomenda devolve a quantidade como sendo 0 */
            printf("%s %d.\n", sistema[idp].descricao, 0);
    }
}

/* lista o id da encomenda em que o produto pedido ocorre mais vezes, apenas se o produto estiver em alguma encomenda */
void lista_ide(){
    
    int idp, ide = -1, qtd = 0, i, e;    /* o id da encomenda e inicializado a -1 e a quantidade para quando encontrar o produto pedido*/
    scanf("%d", &idp);                  /* estes mudarem para o respetivo id da encomenda e quantidade de produto na encomenda*/

    if (sistema[idp].idp == produto_vazio.idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    
    else{
        for (i=0; encomendas[i][0].idp != -1; i++){
            for (e=0; encomendas[i][e].idp >= 0 || encomendas[i][e].idp == -2; e++){
                if (encomendas[i][e].idp == idp && encomendas[i][e].qtd > qtd){
                    qtd = encomendas[i][e].qtd;
                    ide = i;
                    break;
                }
            }
        }

        if (ide >= 0)   /* faz o print apensas se o produto pedido se encontrar numa encomenda */
            printf("Maximo produto %d %d %d.\n", idp, ide, qtd);
    }
}

/* encontra o indice superior para usar na funcao quick_sort_sistema */
int lim_sup(Produto arr[]){

    int i = 0;

    while (arr[i].idp != produto_vazio.idp)
        i++;

    return (i-1);
}

/* troca no vetor dado os produtos com indice a e b */
void troca(Produto arr[], int a, int b){

    Produto temp;

    temp = arr[a]; 
    arr[a] = arr[b]; 
    arr[b] = temp; 
}
  
/* cria a particao para ser usada na funcao quick_sort_sistema */
int particao (Produto arr[], int inf, int sup){

    Produto pivot = arr[sup];
    int i = inf - 1, j;
  
    for (j = inf; j <= sup-1; j++){
        if (arr[j].preco < pivot.preco){
            i++;
            troca(arr, i, j);
        } 
    }

    troca(arr, i + 1, sup);
    return i + 1; 
} 
  
/* ordena os produtos do vetor dado por ordem de preco */
void quick_sort_sistema(Produto arr[], int inf, int sup){

    int ip;

    if (inf < sup){

        ip = particao(arr, inf, sup); 
        quick_sort_sistema(arr, inf, ip - 1); 
        quick_sort_sistema(arr, ip + 1, sup); 
    }
}

void lista_sistema(){

    Produto lista[MAXPROD];
    int i;

    for (i=0; i<MAXPROD; i++)
        lista[i] = sistema[i];

    quick_sort_sistema(lista, 0, lim_sup(lista));

    for (i=0; i < lim_sup(lista); i++)
        if (lista[i].preco == lista[i+1].preco && lista[i].idp > lista[i+1].idp)  /* no caso de haver produtos com o mesmo preco*/
            troca(lista, i, i+1);                                                 /* ordena-os por ordem de id */


    printf("Produtos\n");

    for (i=0; lista[i].idp != produto_vazio.idp; i++)
        printf("* %s %d %d\n", lista[i].descricao, lista[i].preco, lista[i].qtd);
}


/* cria um vetor = encomenda e ordena-o por ordem alfabetica de descricao */
void lista_encomenda(){

    int ide, i, j;
    Produto listaencm[MAXPRODENCM];

    scanf("%d", &ide);

    if (encomendas[ide][0].idp == produto_vazio.idp)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else{

        for (i=0; i<MAXPRODENCM; i++)    /* listaencm = encomenda*/
            listaencm[i] = encomendas[ide][i];

        for (i=0; encomendas[ide][i].idp >= 0; i++){
            for (j=i+1; encomendas[ide][j].idp >= 0; j++){
                if (strcmp(listaencm[i].descricao,listaencm[j].descricao) > 0){
                    troca(listaencm, i, j);
                }
            }
        }
        printf("Encomenda %d\n", ide);

        for (i=0; listaencm[i].idp >= 0; i++)
            printf("* %s %d %d\n", listaencm[i].descricao, listaencm[i].preco, listaencm[i].qtd);        
    }
}