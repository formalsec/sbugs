#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/*==========================CONSTANTES==========================*/


#define FALSE 0
#define TRUE 1
#define MAXPRODUTOS 10000  /*Numero maximo de produtos no sistema*/
#define MAXDESCRICAO 64    /*Tamanho maximo da descricao de um produto(63 caracters + \0)*/
#define MAXENCOMENDAS 500  /*Numero maximo de encomendas*/
#define MAXPESO 200        /*Peso maximo de uma encomenda*/

/*Modos para ordenacao*/
#define PRECO 0
#define ALFABETO 1

/*Valor de comparacao*/
#define MENOR -1
#define IGUAL 0
#define MAIOR 1

/*Valor de procura*/
#define NAOEXISTE -1


/*==========================TIPO DE DADOS==========================*/


/*PRODUTO*/
typedef struct{

    /*Descricao do produto*/
    char descricao[MAXDESCRICAO];

    /*Preco do produto*/
    int preco;

    /*Peso do produto*/
    int peso;

    /*Quantidade de produto em stock*/
    int quantidade;

}tipo_produto;


/*ENCOMENDA*/
typedef struct{

    /*Cada encomenda so pode ter 200 produtos no maximo (quando e constituida
     por 200 produto diferentes de peso igual a 1, limitada pelo peso maximo)
     -lista_produtos[x][0] = id do produto
     -lista_produtos[x][1] = numero de unidades */
    int lista_produtos[MAXPESO][2];

    /*Numero de produtos diferentes na encomenda*/
    int n_produtos;

    /*Peso da encomenda*/
    int peso;

}tipo_encomenda;


/*==========================VARIAVEIS GLOBAIS==========================*/


/*Numero de produtos existentes sistema*/
int max_idp;
/*Array de produtos no sistema*/
tipo_produto produtos[MAXPRODUTOS];


/*Numero de encomendas existentes sistema*/
int max_ide;
/*Array de encomendas no sistema*/
tipo_encomenda encomendas[MAXENCOMENDAS];


/*===========================FUNCOES===========================*/

/*==========================Auxiliares===========================*/


/*Funcao que verifica se existe um produto numa encomenda, e se existir retorna
a posicao deste na lista de produtos da encomenda dada e se nao existir retorna
um numero negativo (-1).*/

int EncontraProduto_Encomenda(int ide, int idp){
    
    int i;
    int posicao = NAOEXISTE;
    int n_produtos;

    /*Numero de produtos diferentes na encomenda*/
    n_produtos = encomendas[ide].n_produtos;

    for(i = 0 ; i < n_produtos ; i++){

        /*Se for encontrado o produto*/
        if(encomendas[ide].lista_produtos[i][0] == idp){
            posicao = i;
            break;
        }
    }

    return posicao;
}



/*Funcao auxiliar que compara dois valores e devolve se
e maior, menor ou igual. A comparacao e feita dependendo
do modo introduzido*/

int Compara(int idp_a, int idp_b,int modo){

    int resultado = IGUAL;

    /*Compara o preco dos produtos*/
    if(modo == PRECO){
        if(produtos[idp_a].preco < produtos[idp_b].preco){
            resultado = MENOR;
        }
        
        else if (produtos[idp_a].preco > produtos[idp_b].preco){
            resultado = MAIOR;
        }
    }

    /*Compara a descricao dos produtos (tem descricao sempre diferente)*/
    else if(modo == ALFABETO){
        if(strcmp(produtos[idp_a].descricao, produtos[idp_b].descricao) < 0){
            resultado = MENOR;
        }

        else{
            resultado = MAIOR;
        }
    }

   return resultado;
}

/*Auxilir do algoritmo de ordenacao, usado para juntar arrays*/

void Merge(int vetor[MAXPRODUTOS], int esq, int meio, int dir,int modo){

    int i;
    int r;
    int k;
    int res;

    /*Cria um vetor auxiliar*/
    int vetor_aux[MAXPRODUTOS];

    /*Constroi o vetor auxiliar que contem os valores correspondentes
    vetor[esq...meio]*/
    for(i = meio + 1 ; i > esq ; i--){
        vetor_aux[i-1] = vetor[i-1];
    }

    /*Constroi o vetor auxiliar que contem os valores correspondentes
    vetor[meio + 1...dir]*/
    for(r = meio ; r < dir ; r++){
        vetor_aux[dir + meio - r] = vetor[r + 1];
    }


    for(k = esq; k <= dir; k++){

        /*Resultado da comparacao entre os respetivos valores, dependendo do
        modo introduzido*/
        res = Compara(vetor_aux[r], vetor_aux[i], modo);

        /*Se o valor a comparar do vetor_aux[r] for menor*/
        if(res == MENOR){
            vetor[k] = vetor_aux[r--];
        }

        /*Se o valor a comparar do vetor_aux[r] for maior*/
        else if(res == MAIOR){
            vetor[k] = vetor_aux[i++];
        }

        /*Se os valores a comparar forem iguais compara-se os id dos produto*/
        else{

            if(vetor_aux[r] < vetor_aux[i]){
                vetor[k] = vetor_aux[r--];
            }
            
            else{
                vetor[k] = vetor_aux[i++];
            }
        }
    }
}



/*Algoritmo de ordenacao usado no sistema que recebe um vetor com 
id dos produtos e ordena-o dependente do modo escolhido
modo = PRECO, ordena pelo preco
modo = ALFABETO, ordena pela descricao*/

void MergeSort(int vetor[MAXPRODUTOS], int esq, int dir,int modo){
    int meio = (esq + dir) / 2;
    
    if(dir <= esq){
        return;
    }
    MergeSort(vetor, esq, meio, modo);

    MergeSort(vetor, meio + 1, dir, modo);

    Merge(vetor, esq, meio, dir, modo);
}


/*==========================Controlo de produtos==========================*/


/*Funcao que le uma descricao, um preco, um peso e uma quantidade dada sobre
um produto e adiciona-o ao sistema*/

void NovoProduto(void){
    
    /*Le a descricao ,preco ,peso e quantidade de um produto*/
    scanf(" %[^:]:%d:%d:%d",produtos[max_idp].descricao,
                            &produtos[max_idp].preco,
                            &produtos[max_idp].peso,
                            &produtos[max_idp].quantidade);

    printf("Novo produto %d.\n", max_idp);
    
    /*Aumenta o numero de produtos*/
    max_idp++;
}



/*Funcao que recebe o id de um produto e uma quantidade, e adiciona a quantidade
dada ao total de unidades do produto no sistema*/

void AdicionaProduto(int idp, int qtd){

    /*Verificar se o produto existe*/
    if(idp >= max_idp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }

    else{
        produtos[idp].quantidade += qtd;
    }
}



/*Funcao que recebe o id de um produto e uma quantidade, e remove a quantidade
dada ao total de unidades do produto no sistema*/

void RemoveProduto(int idp, int qtd){

    /*Verificar se o produto existe*/
    if(idp >= max_idp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }

    /*Verificar se e possivel retirar a quantidade introduzida*/
    else if(qtd > produtos[idp].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }

    else{
        produtos[idp].quantidade -= qtd;
    }
}



/*Funcao que le o id de um produto e um preco, e altera o preco do produto
no sistema pelo novo dado*/

void AlteraPreco(void){

    int idp;
    int novo_preco;

    /*Le o id do produto e o novo preco*/
    scanf("%d:%d", &idp, &novo_preco);

    /*Verificar se o produto existe*/
    if(idp >= max_idp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp );
    }

    else{
        produtos[idp].preco = novo_preco;

    }
}


/*==========================Controlo de encomendas==========================*/


void CriaEncomenda(){
    
    /*Imprime o id da nova encomenda*/
    printf("Nova encomenda %d.\n", max_ide);

    /*Aumenta o numero de encomendas existentes*/
    max_ide++;
}



/*Funcao que le o id de uma encomenda, o id de um poduto e uma quantidade, e adiciona
o produto a encomenda com a quantidade dada ou se o produto ja existir adiciona a
quantidade dada a ja existente*/

void AdicionaProduto_Encomenda(){

    int ide;
    int idp;
    int qtd;
    int peso;

    /*Le o id da encomenda,o id do produto e a quantidade de produto a adicionar*/
    scanf("%d:%d:%d", &ide, &idp, &qtd);

    /*Peso final da encomenda apos se ter adicionado o produto*/
    peso = encomendas[ide].peso + (produtos[idp].peso * qtd);

    /*Verificar se a encomenda existe*/
    if(ide >= max_ide){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    /*Verificar se o produto existe*/
    else if(idp >= max_idp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    /*Verificar se existe quantidade de produto em stock suficiente para adicionar a encomenda */
    else if(qtd > produtos[idp].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }

    /*Verificar se o peso final excede o limite por encomenda*/
    else if(peso > MAXPESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }

    else{

        int posicao;
        int n_produtos;

        /*Numero de produtos diferentes na encomenda*/
        n_produtos = encomendas[ide].n_produtos;

        /*Verifica se ja existe o produto na encomenda*/
        if((posicao = EncontraProduto_Encomenda(ide, idp)) != NAOEXISTE){
            /*Se o produto ja existe adiciona a quantidade introduzida*/
            encomendas[ide].lista_produtos[posicao][1] += qtd;   
        }

        /*Adicionar o produto a encomenda se este nao existir e aumentar 
        o numero de produtos na encomenda*/
        else{
            encomendas[ide].lista_produtos[n_produtos][0] = idp;
            encomendas[ide].lista_produtos[n_produtos][1] = qtd;
            encomendas[ide].n_produtos++;
        }

        /*Retira ao stock do produto as unidades adicionadas a encomenda*/
        RemoveProduto(idp, qtd);

        /*Atualiza o peso de encomenda*/
        encomendas[ide].peso = peso;

    }
}



/*Funcao que le o id de uma encomenda e o id de um produto, e remove o produto dado
da encomenda*/

void RemoveProduto_Encomenda(){

    int ide;
    int idp;

    /*Le o id da encomenda e o id do produto*/
    scanf("%d:%d", &ide, &idp);

    /*Verificar se a encomenda existe*/
    if(ide >= max_ide){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    /*Verificar se o produto existe*/
    else if(idp >= max_idp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    else{
        int n_produtos;
        int posicao;
        int qtd;

        /*Posicao do produto na lista de produtos da encomenda.*/
        if((posicao = EncontraProduto_Encomenda(ide, idp)) != NAOEXISTE){
            /*Quantidade do produto na encomenda.*/
            qtd = encomendas[ide].lista_produtos[posicao][1];

            /*Atualizar o peso da encomenda.*/
            encomendas[ide].peso -= qtd * produtos[idp].peso;
            
            /*Atualiza o numero de produtos diferentes na encomenda.*/
            --encomendas[ide].n_produtos;
            n_produtos = encomendas[ide].n_produtos;

            /*Retira completamente o produto de encomenda.*/
            for( ; posicao < n_produtos ; posicao++){

                encomendas[ide].lista_produtos[posicao][0] = encomendas[ide].lista_produtos[posicao + 1][0];
                encomendas[ide].lista_produtos[posicao][1] = encomendas[ide].lista_produtos[posicao + 1][1];
            }

            /*Adiciona ao stock a quantidade de produto que pertencia a encomenda.*/
            AdicionaProduto(idp, qtd);
        }
    }
}


/*==========================Informacoes==========================*/


/*Funcao que le o id do produto e imprime a encomenda em que o produto
dado se encontra em maior quanridade*/

void EncomendaProduto_MaiorQuantidade(){

    int idp;
    int ide;
    int posicao;
    int qtd;
    int maior_ide = 0;
    int maior_qtd = 0;

    /*Le o id do produto*/
    scanf("%d", &idp);

    /*Verificar se o produto existe*/
    if(idp >= max_idp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }

    else{
        /*Procura por todas as encomendas pela que tiver maior quantidade
        do produto*/
        for(ide = 0 ; ide < max_ide ; ide++){

            /*Se encontrar uma encomenda em que o produto exista compara
            com a maior quantidade encontrada anteriormente, e se for maior
            muda as respetivas variaveis.*/
            if((posicao = EncontraProduto_Encomenda(ide, idp)) != NAOEXISTE){
                qtd = encomendas[ide].lista_produtos[posicao][1];

                /*Quantidade superior*/
                if(qtd > maior_qtd){
                    maior_qtd = qtd;
                    maior_ide = ide;
                }
            }
        }

        if(maior_qtd != 0){
            /*Imprime o resultado*/
            printf("Maximo produto %d %d %d.\n", idp, maior_ide, maior_qtd);
        }
    }
    
}



/*Funcao que le o id de uma encomenda e o id de um produto, e imprime
a descricao do produto e a quantidade desse produto na encomenda */

void ProdutoEmEncomenda(){

    int ide;
    int idp;

    /*Le o id de uma encomenda e o id de um produto*/
    scanf("%d:%d", &ide, &idp);

    /*Verificar se a encomenda existe*/
    if(ide >= max_ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    /*Verificar se o produto existe*/
    else if( idp >= max_idp ){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }

    else{
        int qtd = 0;
        int posicao;

        /*Procura pela posicao do produto na ista de produtos da encomenda*/
        if((posicao = EncontraProduto_Encomenda(ide, idp)) != NAOEXISTE){
            qtd = encomendas[ide].lista_produtos[posicao][1];
        }

        /*Imprime a descricao e a quantidade de produto na encomenda*/
        printf("%s %d.\n", produtos[idp].descricao, qtd);        
    }
}



/*Funcao que le o id de uma encomenda e imprime o preco total desta*/

void PrecoEncomenda(void){

    int i;
    int ide;
    int idp;
    int n_produtos;
    int qtd;
    int preco;
    int total = 0;

    /*Le o id da encomenda*/
    scanf("%d", &ide);

    /*Verificar se a encomenda existe*/
    if(ide >= max_ide){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }

    else{
        /*Numero de produtos diferentes na encomenda*/
        n_produtos = encomendas[ide].n_produtos;
        
        /*Percorre os produtos da encomenda e calcula o preco total da encomenda*/
        for(i = 0 ; i < n_produtos ; i++){

            idp = encomendas[ide].lista_produtos[i][0];
            qtd = encomendas[ide].lista_produtos[i][1];
            preco = produtos[idp].preco;
            total += qtd * preco;
        }

        /*Imprime o id da encomenda e o preco total desta*/
        printf("Custo da encomenda %d %d.\n" ,ide ,total );
    }
}



/*Funcao que ordena todos os produtos no sistema por ordem crescente
de preco(se este for igual ordena por ordem crescente de id)*/

void OrdenaProdutos(){

    int produtos_copia[MAXPRODUTOS];
    int idp;
    int i;

    /*Cria um vetor que contem o id de todos os produto*/
    for(i = 0 ; i < max_idp ; i++){
        produtos_copia[i] = i;
    }

    /*Utiliza o algoritmo MergeSort para ordenar o id dos produtos
    de forma crescente pelo preco, indicado pela ultima entrada da funcao*/
    MergeSort(produtos_copia, 0, max_idp - 1, PRECO);

    /*Imprime o resultado da ordenacao*/
    printf("Produtos\n");

    for(i = 0; i < max_idp  ; i++){
        idp = produtos_copia[i];

        /*Imprime o produto*/
        printf("* %s %d %d\n", produtos[idp].descricao, produtos[idp].preco, produtos[idp].quantidade);
    }

}



/*Funcao que le o id de uma encomenda e ordena os produtos contidos
nesta de forma alfabetica*/

void OrdenaProdutos_Encomenda(){

    int ide;
    int lista_produtos_copia[MAXPESO];
    int n_produtos;
    int idp;
    int qtd;
    int i;
    int r;

    /*Le o id da encomenda*/
    scanf("%d", &ide);

    /*Verifica se existe uma encomenda com este id*/
    if(ide >= max_ide){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    else{
        /*Numero de produtos diferentes na encomenda*/
        n_produtos = encomendas[ide].n_produtos;

        /*Cria um vetor com todos os ids dos produtos existentes na encomenda*/
        for(i = 0; i < n_produtos ; i++){
            lista_produtos_copia[i] = encomendas[ide].lista_produtos[i][0];
        }

        /*Utiliza o algoritmo MergeSort para ordenar o id dos produtos
        de forma alfabetica pelas suas respetivas descricoes, indicado 
        pela ultima entrada da funcao*/
        MergeSort(lista_produtos_copia, 0, n_produtos - 1, ALFABETO);

        /*Imprime o resultado da ordenacao*/
        printf("Encomenda %d\n", ide);

        for(i = 0 ; i < n_produtos ; i++){
            idp = lista_produtos_copia[i];

            /*Procura a quantidade de produto na encomenda*/
            for(r=0; r < n_produtos; r++){
                if (encomendas[ide].lista_produtos[r][0] == idp){
                    qtd = encomendas[ide].lista_produtos[r][1];
                }
            }

            /*Imprime o produto*/
            printf("* %s %d %d\n", produtos[idp].descricao, produtos[idp].preco , qtd);
        }
    }
}


/*==========================MAIN==========================*/

/*Funcao principal que le um letra correspondente a um comando,e
executa a funcao correspondente ao comando valido introduzido*/
int main(){

    int idp ;
    int qtd ;
    int fim = FALSE ;
    char comando ;

    while(fim == FALSE){
        switch (comando = getchar()){

        /*__________COMANDOS RELATIVOS A PRODUTOS__________*/
            case 'x':{
                fim = TRUE;
                break;
            }

            case 'a':{
                NovoProduto();
                break;
            }

            case 'q':{
                scanf("%d:%d",&idp ,&qtd );
                AdicionaProduto(idp, qtd);
                break;
            }

            case 'r':{
                scanf("%d:%d",&idp ,&qtd );
                RemoveProduto(idp,qtd);
                break;
            }

            case 'p':{
                AlteraPreco();
                break;
            }

        /*__________COMANDOS RELATIVOS A ENCOMENDAS__________*/
            case 'N':{
                CriaEncomenda();
                break;
            }

            case 'A':{
                AdicionaProduto_Encomenda();
                break;
            }

            case 'R':{
                RemoveProduto_Encomenda();
                break;
            }

        /*__________COMANDOS QUE DAO INFORMACOES__________*/
            case 'm':{
                EncomendaProduto_MaiorQuantidade();
                break;
            }

            case 'E':{
                ProdutoEmEncomenda();
                break;
            }
            
            case 'C':{
                PrecoEncomenda();
                break;
            }

            case 'l':{
                OrdenaProdutos();
                break;
            }

            case 'L':{
                OrdenaProdutos_Encomenda();
                break;
            }
        }
    }

    return 0;
}