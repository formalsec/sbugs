#include <stdio.h>
#include <string.h>
#define MAX_ID 10000
#define MAX_DESC 63
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200

/*
Estrutura "Produto"
A variavel "quantidade_especial" ira servir para guardar a quantidade deste produto numa encomenda especifica
*/
typedef struct produto{
    char descricao[MAX_DESC];
    int preco, peso,quantidade;
    int quantidade_especial;
}Produto;

/*
Estrutura encomenda
A variavel peso ira conter o peso total da encomenda
A variavel "produtos" ira conter uma lista de vetores de duas entradas.
Estas duas entradas (0 e 1) serao, respetivamente, o id de um produto e a sua quantidade na encomenda
A variavel ponteiro ira ser equivalente ao numero de produtos na encomenda e ia "apontar" para o proximo espa?o,
na lista de produtos da encomenda, a ser preenchido.
*/
typedef struct encomenda{
    int peso,produtos[MAX_PESO][2],ponteiro;
}Encomenda;



/*
Inicializacao de variaveis globais...
*/
Produto lista_produtos[MAX_ID];                /*Lista de produtos do sistema*/ 
Encomenda lista_encomendas[MAX_ENCOMENDAS];    /*Lista de encomendas do sistema*/
int i_produtos,i_encomendas;

/*
ad_produto()
Adiciona um produto ao sistema
in  -> a <descricao>:<preco>:<peso>:<quantidade>
out -> Novo produto <id>.
*/
void ad_produto(){
    Produto prod;

    scanf(" %[^:]:%d:%d:%d",prod.descricao,&prod.preco,&prod.peso,&prod.quantidade);
    lista_produtos[i_produtos] = prod;
    printf("Novo produto %d.\n",i_produtos);
    i_produtos++;
}


/*
ad_stock()
Adiciona quantidade a um produto
in  -> q <id>:<quantidade>
*/
void ad_stock(){
    int id, qtd;

    scanf(" %d:%d",&id,&qtd);
    if (id >= i_produtos){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
    }else{
        lista_produtos[id].quantidade += qtd;
    }
}


/*
cria_encomenda()
Adiciona uma encomenda ao sistema
in  -> N
out -> Nova encomenda <id>.
*/
void cria_encomenda(){
    Encomenda encomenda;

    encomenda.peso = 0;
    encomenda.ponteiro = 0;
    lista_encomendas[i_encomendas] = encomenda;
    printf("Nova encomenda %d.\n",i_encomendas);
    i_encomendas += 1;
}


/*
*FUNCAO AUXILIAR*
prod_na_encomenda(idp, encomenda);
Procura por um produto numa determinada encomenda.
Se encontrar o produto, devolve a sua posicao,
Se nao, devolve -1
*/
int prod_na_encomenda(int prod, Encomenda encomenda){
    int ponteiro = encomenda.ponteiro,i;

    for (i = 0;i< ponteiro;i++){
        if (encomenda.produtos[i][0] == prod){
            return i;
        }
    }
    return -1;
}


/*
ad_prod_a_encomenda()
Adiciona uma quantidade de um produto a uma encomenda. Se este nao existir, adiciona o produto a encomenda, com a quantidade inserida.
in  -> A <ide>:<idp>:<quantidade>
*/
void ad_prod_a_encomenda(){
    int id_prod,id_enc, qtd, i;
    
    scanf(" %d:%d:%d",&id_enc,&id_prod,&qtd);

    if (id_enc >= i_encomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }
    if (id_prod >= i_produtos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }
    if (qtd > lista_produtos[id_prod].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",id_prod,id_enc);
        return;
    } 
    if (lista_encomendas[id_enc].peso + lista_produtos[id_prod].peso*qtd > MAX_PESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",id_prod,id_enc);
        return;
    }

    /*
    Procurar pelo produto na encomenda
    */
    i = prod_na_encomenda(id_prod,lista_encomendas[id_enc]);

    /*
    lista_encomendas[id_enc] -> encomenda alvo
    */
    if (i != -1){
        /*
        Se existir, adiciona quantidade...
        */
        lista_encomendas[id_enc].produtos[i][1] += qtd;
    }else{
        /*
        Se nao existir, insere o id do produto e a sua quantidade no espaco indicado pelo ponteiro e incrementa o mesmo
        */
        lista_encomendas[id_enc].produtos[lista_encomendas[id_enc].ponteiro][0] = id_prod;
        lista_encomendas[id_enc].produtos[lista_encomendas[id_enc].ponteiro][1] = qtd;
        lista_encomendas[id_enc].ponteiro += 1;
    } 
    lista_encomendas[id_enc].peso += lista_produtos[id_prod].peso*qtd;
    lista_produtos[id_prod].quantidade -= qtd;
}


/*
rm_stock()
Remove uma certa quantidade ao stock de um produto no sistema
in  -> r <id>:<quantidade>
*/
void rm_stock(){
    int id,qtd;

    scanf(" %d:%d",&id,&qtd);
    if (id >= i_produtos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",id);
        return;
    }
    if (qtd > lista_produtos[id].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,id);
        return;
    }
    lista_produtos[id].quantidade -= qtd;
}


/*
rm_prod()
Remove um produto de uma encomenda
in  -> R <ide>:<idp>
*/
void rm_prod(){
    int id_prod,id_enc,i;

    scanf(" %d:%d",&id_enc,&id_prod);
    if (id_enc >= i_encomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",id_prod,id_enc);
        return;
    }
    if (id_prod >= i_produtos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",id_prod,id_enc);
        return;
    }
    
    /*
    Procurar pelo produto na encomenda...
    */
    i= prod_na_encomenda(id_prod,lista_encomendas[id_enc]);
    
    /*
    Se ele existir na encomenda...
    */
    if (i!=-1){
        lista_produtos[id_prod].quantidade += lista_encomendas[id_enc].produtos[i][1]; /* Devolver a quantidade ao stock do produto */
        lista_encomendas[id_enc].peso -= lista_produtos[id_prod].peso*lista_encomendas[id_enc].produtos[i][1]; /* Acertar o novo peso da encomenda */
        for(;i<lista_encomendas[id_enc].ponteiro-1 ;i++){
            /*
            Todos os produtos em posi?oes acima do produto removido passam para o espa?o abaixo, na lista de produtos da encomenda.
            */
            lista_encomendas[id_enc].produtos[i][0] = lista_encomendas[id_enc].produtos[i+1][0];
            lista_encomendas[id_enc].produtos[i][1] = lista_encomendas[id_enc].produtos[i+1][1];
        }
        lista_encomendas[id_enc].ponteiro = lista_encomendas[id_enc].ponteiro -1; /* Decrementar o ponteiro (numero de produtos na encomenda) */
    }
}


/*
calc_custo()
Calcula o custo de uma encomenda
in  -> C <id>
out -> Custo da encomenda <id> <custo>.
*/
void calc_custo(){
    int id,custo = 0,i;

    scanf(" %d",&id);
    if (id >= i_encomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id);
        return;
    }

    /*
    Percorre os produtos da encomenda e adiciona o preco*quantidade de cada um ao custo total da encomenda
    */
    for (i=0;i<lista_encomendas[id].ponteiro;i++){
        custo += lista_produtos[lista_encomendas[id].produtos[i][0]].preco * lista_encomendas[id].produtos[i][1];
    }

    printf("Custo da encomenda %d %d.\n",id,custo);
}


/*
alt_produto()
Altera o preco de um produto no sistema para o preco inserido
in  -> p <id>:<preco>
*/
void alt_produto(){
    int id,preco;

    scanf(" %d:%d",&id,&preco);
    if (id >= i_produtos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",id);
        return;
    }
    lista_produtos[id].preco = preco;
}


/*
ret_desc_quant()
Devolve a descricao e a quantidade de um produto existente numa encomenda
in  -> E <ide>:<idp>
out -> <descricao> <quantidade>.
*/
void ret_desc_quant(){
    int id_prod,id_enc,i,qtd;

    scanf(" %d:%d",&id_enc,&id_prod);

    if (id_enc >= i_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id_enc);
        return;
    }
    if (id_prod >= i_produtos){
        printf("Impossivel listar produto %d. Produto inexistente.\n",id_prod);
        return;
    }

    /*
    Procura pelo produto na encomenda...
    */
    i = prod_na_encomenda(id_prod,lista_encomendas[id_enc]);
    /*
    Se este nao existir na encomenda, a quantidade a devolver sera 0
    */
    if (i==-1){
        qtd = 0;
    }else{
        qtd = lista_encomendas[id_enc].produtos[i][1];
    }
    printf("%s %d.\n",lista_produtos[id_prod].descricao,qtd);
}  


/*
maior_encomenda()
Devolve o identificador da encomenda em que um dado produto ocorre mais vezes
in  -> m <idp>
out -> Maximo produto <idp> <ide> <maior quantidade>.
*/
void maior_encomenda(){
    int maior_quantidade = -1 , id_maior_encomenda,i,j,id_prod;

    scanf(" %d",&id_prod);
    
    if (id_prod >= i_produtos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",id_prod);
    }

    if (i_encomendas == 0){
        return;
    }

    /*
    Compara todas as quantidades de todos os produtos em todas as encomendas com a maior quantidade ate agora, guardada na variavel "maior_quantidade"
    Caso a quantidade seja maior, guarda o id da encomenda em caso em "id_maior_encomenda" e atualiza a maior quantidade
    */
    for (i=0;i<i_encomendas;i++){
        j = prod_na_encomenda(id_prod,lista_encomendas[i]);
        if (j != -1){
            if (lista_encomendas[i].produtos[j][1] > maior_quantidade){
                maior_quantidade = lista_encomendas[i].produtos[j][1];
                id_maior_encomenda = i;
            }
        }
    }
    if (maior_quantidade == -1){
        return;
    }
    printf("Maximo produto %d %d %d.\n",id_prod,id_maior_encomenda,maior_quantidade);
}


/*
MERGE SORT
mergesort(lista,0,n_elementos,flag)
*/

/*
menor(prod1,prod2)
Funcao que ira comparar os elementos da lista
A variavel flag serve para indicar o que vai ser comparado
Se flag for 1, compara alfabeticamente a descricao do produto, se for 0 compara o preco do produto 
*/
int menor(int prod1,int prod2,int flag){
    
    if (flag == 1){
        if (strcmp(lista_produtos[prod1].descricao,lista_produtos[prod2].descricao) < 0){
            return 1;
        }
    }else{
        if (lista_produtos[prod1].preco <= lista_produtos[prod2].preco){
            return 1;
        }
    }
    return 0;
}


void merge(int arr[], int l, int m, int r,int flag)
{
    /*
    Listas temporarias Left e Right
    */
    int Left[MAX_ID], Right[MAX_ID];
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;


    /*
    Copiar as entradas da lista recebida para as listas temporarias
    */
    for (i = 0; i < n1; i++)
        Left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        Right[j] = arr[m + 1+ j];

    /*
    Realizar o "merge" entre os dois vetores ordenados
    */
     i = 0; 
     j = 0; 
     k = l; 

     while (i < n1 && j < n2)
     {
         if (menor(Left[i],Right[j],flag))
         {
             arr[k] = Left[i];
             i++;
         }
         else
         {
             arr[k] = Right[j];
             j++;
         }
         k++;
     }

    /*
    Se sobrarem elemntos em qualquer uma das listas temporarias, copia-los
    */
     while (i < n1)
     {
         arr[k] = Left[i];
         i++;
         k++;
     }

     while (j < n2)
     {
         arr[k] = Right[j];
         j++;
         k++;
     }
 }

void mergesort(int arr[], int l, int r,int flag)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        /*
        Ordenar ambas as metades da lista
        */
        mergesort(arr, l, m,flag);
        mergesort(arr, m+1, r,flag);
        merge(arr, l, m, r, flag);
     }
 }
/*FIM DO MERGESORT*/


/*
ordenar_p_preco()
Lista todos os produtos existentes no sistema por ordem crescente de pre?o
in  -> l
out -> Produtos
       * <descricao> <preco> <quantidade>
*/
void ordenar_p_preco(){
    int lista_copia[MAX_ID];
    int i;

    /*
    Criar uma lista com todos os id's dos produtos
    */
    for (i=0;i<i_produtos;i++){
        lista_copia[i] = i;
    }

    /*
    Ordenar a lista copiada por preco (flag = 0)
    */
    mergesort(lista_copia, 0, i_produtos-1, 0);

    printf("Produtos\n");
    /*
    Percorrer a lista ordenada e retornar as informacoes necessarias de cada produto, a partir do seu id
    */
    for (i=0;i<i_produtos;i++){;
        printf("* %s %d %d\n",lista_produtos[lista_copia[i]].descricao,lista_produtos[lista_copia[i]].preco,lista_produtos[lista_copia[i]].quantidade);
    }
}


/*
ordenar_p_descricao()
Lista todos os produtos de uma encomenda por ordem alfabetica da descri??o
in  -> L <id>
out -> Encomenda <id>
       * <descricao> <preco> <quantidade na encomenda>
*/
void ordenar_p_descricao(){
    int lista_copia[MAX_ID];
    int i,id;

    scanf(" %d",&id);
    if (id >= i_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id);
        return;
    }
    printf("Encomenda %d\n",id);
    /*
    Guarda a quantidade na encomenda dos produtos na variavel "quantidade_especial"
    Criar uma lista com os id's dos produtos existentes na encomenda
    */
    for (i=0;i<lista_encomendas[id].ponteiro;i++){
        lista_produtos[lista_encomendas[id].produtos[i][0]].quantidade_especial = lista_encomendas[id].produtos[i][1];
        lista_copia[i] = lista_encomendas[id].produtos[i][0];
    }
    /*
    Ordenar alfabeticamente (flag = 1) a nova lista
    */
    mergesort(lista_copia,0,lista_encomendas[id].ponteiro-1,1);
    /*
    Percorrer a lista ordenada e retornar as informacoes necessarias de cada produto, a partir do seu id
    */
    for (i=0;i<lista_encomendas[id].ponteiro;i++){
        printf("* %s %d %d\n",lista_produtos[lista_copia[i]].descricao,lista_produtos[lista_copia[i]].preco,lista_produtos[lista_copia[i]].quantidade_especial);
    }

 }



/*
FUNCAO MAIN
*/
int main(){
    char cmd;
    i_produtos = 0;
    i_encomendas = 0;

    /*
    Loop infinito
    */
    while(1){
        /*
        Cada comando chama a sua funcao correspondente
        */
        scanf("%c",&cmd);
        switch (cmd){
            case 'a':
                ad_produto();
            break;
            case 'q':
                ad_stock();
            break;
            case 'N':
                cria_encomenda();
            break;
            case 'A':
                ad_prod_a_encomenda();
            break;
            case 'r':
                rm_stock();
            break;
            case 'R':
                rm_prod();
            break;
            case 'C':
                calc_custo();
            break;
            case 'p':
                alt_produto();
            break;
            case 'E':
                ret_desc_quant();
            break;
            case 'm':
                maior_encomenda();
            break;
            case 'l':
                ordenar_p_preco();
            break;
            case 'L':
                ordenar_p_descricao();
            break;
            case 'x':
            return 0;
            break;
        }

    }
    return 0;
}
