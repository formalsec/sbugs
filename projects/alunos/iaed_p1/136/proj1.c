#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>


#define encomendas_max 500
#define quantidade_produtos 10000
#define peso_max 200
#define tamanho_encomenda 200
#define tamanho_descricao 63

/* criacao da estrutura produto que possui um id, uma descricao, um preco, um peso e uma quantidade*/
typedef struct Produto{
    int id;
    char descricao[tamanho_descricao];
    int preco;
    int peso;
    int quantidade;
}produto;

/*criacao da estrutura encomenda que possui um id, um peso e um vetor que contem varios produtos*/
typedef struct Encomenda{
    int id;
    int peso;
    produto produtos[quantidade_produtos]; 
}encomenda;

int indice_produto=0;   /*indice global que e incrementado cada vez que um novo produto e criado*/              
int indice_encomenda=0;   /*indice global que e incrementado cada vez que uma nova encomenda e criada*/
int key;   /*variavel global que e usada para diferenciar os comandos l e L nas funcoes merge e mergesort*/
produto vetor_produtos[quantidade_produtos] = {0};   /*vetor constituido por produtos que representa todos os produtos no sistema*/
encomenda vetor_encomendas[encomendas_max] = {0};    /*vetor constituido por encomendas que representa todas as encomendas no sitema*/

/* chamada das funcoes*/
void cria_produto();
void adicionar_stock();
void cria_encomenda();
void adiciona_produto();
void remove_stock();
void remove_produto();
void calcula_custo();
void altera_preco();
void informacao_produto_encomenda();
void ocorrencia_produto();
void merge(produto vetor_produtos[],int left,int m,int right, int key);
void mergesort(produto vetor_produtos[], int left, int right, int key);
void ordena_preco();
void ordena_alfa();


/*funcao main com um switch que executa as funcoes dependendo do caracter introduzido*/
int main(){
    char c;
    do{
        c = getchar();
        switch(c){
        case 'a':
            cria_produto();
            break;
        case 'q':
            adicionar_stock();
            break;
        case 'N':
            cria_encomenda();
            break;
        case 'A':
            adiciona_produto();
            break;
        case 'r':
            remove_stock();
            break;
        case 'R':
            remove_produto();
            break;
        case 'C':
            calcula_custo();
            break;
        case 'p':
            altera_preco();
            break;
        case 'E':
            informacao_produto_encomenda();
            break;
        case 'm':
            ocorrencia_produto(); 
            break;
        case 'l':
            ordena_preco();
            break;
        case 'L':
            ordena_alfa();
            break;
        } 
    }while(c != 'x');
    return 0;
}


/* comando a*/
void cria_produto(){ 

/*funcao que faz scanf a uma string e 3 inteiros, atribuindo ao vetor sistema um produto na posicao indice_produto, consituido por um id, uma descricao, um peso, uma quantidade, e um preco */
    
    produto prod;
    prod.id=indice_produto;
    scanf(" %[^:]:%d:%d:%d", prod.descricao, &prod.preco, &prod.peso, &prod.quantidade);
    vetor_produtos[prod.id] = prod;
    indice_produto++;
    printf("Novo produto %d.\n", prod.id);
}


/* comando q*/
void adicionar_stock(){

/*funcao que faz scanf a um id de produto e a uma quantidade, se o produto correspondente a esse id existir, ser-lhe-a adicionada essa quantidade ao stock*/
    
    produto prod;
    scanf("%d:%d", &prod.id, &prod.quantidade);
    if(prod.id >= indice_produto){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",prod.id);
    }
    else{
        vetor_produtos[prod.id].quantidade+=prod.quantidade;
    }
}


/* comando N*/
void cria_encomenda(){

/*funcao que atribui uma nova encomenda ao vetor encomendas na posicao indice_encomenda, a essa encomenda e atribuido um id correspondente ao indice_encomenda */
    
    encomenda ord;
    ord.id = indice_encomenda;
    ord.peso=0;
    vetor_encomendas[ord.id]= ord;
    indice_encomenda++; 
    printf("Nova encomenda %d.\n", ord.id);
}


/* comando A*/
void adiciona_produto(){

/*funcao que adiciona um produto a uma encomenda*/

    encomenda ord;
    produto prod;
    scanf("%d:%d:%d",&ord.id,&prod.id,&prod.quantidade);

/*verificacao da existencia do produto, da encomenda, da disponibilidade do produto em stock e se a quantidade respeita os limites de peso*/
    if(ord.id >= indice_encomenda){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", prod.id, ord.id);
    }
    else if(prod.id >= indice_produto){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", prod.id, ord.id);
    }
    else if(prod.quantidade > vetor_produtos[prod.id].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", prod.id, ord.id);
    }
    else if((vetor_produtos[prod.id].peso*prod.quantidade) + vetor_encomendas[ord.id].peso > peso_max){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", prod.id, ord.id);
    }

/*se o produto ja estiver nessa encomenda apenas e modificada a sua quantidade*/
    else if(vetor_encomendas[ord.id].produtos[prod.id].quantidade != 0){
        vetor_encomendas[ord.id].peso += (vetor_produtos[prod.id].peso * prod.quantidade);
        vetor_encomendas[ord.id].produtos[prod.id].quantidade += prod.quantidade;
        vetor_produtos[prod.id].quantidade -= prod.quantidade;
    }

/*caso contrario e adiconado o novo produto ao vetor produtos que a encomenda possui na posicao correspondente ao seu id*/
    else{
        prod.preco = vetor_produtos[prod.id].preco;
        prod.peso = vetor_produtos[prod.id].peso;
        strcpy(prod.descricao, vetor_produtos[prod.id].descricao);
        vetor_encomendas[ord.id].produtos[prod.id] = prod;
        vetor_encomendas[ord.id].peso += (vetor_produtos[prod.id].peso * prod.quantidade);
        vetor_produtos[prod.id].quantidade -= prod.quantidade;
    }
}


/* comando r*/
void remove_stock(){

/*funcao que remove stock a um produto no vetor sistema verificando se esse produto existe e se o stock final nao sera negativo*/

    produto prod;
    scanf("%d:%d", &prod.id, &prod.quantidade);
        if(prod.id >= indice_produto){
            printf("Impossivel remover stock do produto %d. Produto inexistente.\n", prod.id);
        }
        else if(vetor_produtos[prod.id].quantidade - prod.quantidade < 0){
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", prod.quantidade, prod.id);
        }
        else{
            vetor_produtos[prod.id].quantidade = vetor_produtos[prod.id].quantidade - prod.quantidade;
        }
}


/* comando R*/
void remove_produto(){
    
/*funcao que remove um produto de uma encomenda, para isto as variaveis peso, quantidade e preco ficam a 0; e tambem verificado se o produto e encomenda introduzidos existem*/    
    
    encomenda ord;
    produto prod;
    scanf("%d:%d", &ord.id, &prod.id);
        if(ord.id >= indice_encomenda){
            printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", prod.id, ord.id);
        }
        else if(prod.id >= indice_produto){
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", prod.id, ord.id);
        }
        else{
            vetor_produtos[prod.id].quantidade += vetor_encomendas[ord.id].produtos[prod.id].quantidade;
            vetor_encomendas[ord.id].peso -= vetor_produtos[prod.id].peso * vetor_encomendas[ord.id].produtos[prod.id].quantidade;
            vetor_encomendas[ord.id].produtos[prod.id].quantidade=0;
            vetor_encomendas[ord.id].produtos[prod.id].peso=0;
            vetor_encomendas[ord.id].produtos[prod.id].preco=0;
        }
}


/* comando C*/
void calcula_custo(){

/*funcao que calcula o custo da encomenda cujo id foi introduzido, e verificada a existencia da encomenda*/

    encomenda ord;
    int total=0;
    int i;
    scanf("%d", &ord.id);
    if(ord.id >= indice_encomenda){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ord.id);
    }
    else{  
        for (i = 0; i < indice_produto; i++){
            total+= (vetor_encomendas[ord.id].produtos[i].preco * vetor_encomendas[ord.id].produtos[i].quantidade);
        }
        printf("Custo da encomenda %d %d.\n",ord.id, total);
    }
}


/* comando p*/

/*funcao que altera o preco de um produto no vetor sistema, como consequencia se esse produto estiver numa encomenda o seu preco ira ser alterado no vetor produtos dessa encomenda*/

void altera_preco(){
    produto prod;
    int i;
    scanf("%d:%d",&prod.id, &prod.preco);
    if(prod.id > indice_produto){
        printf("Impossivel alterar o preco do produto %d. Produto inexistente.\n", prod.id);
    }
    else{
        vetor_produtos[prod.id].preco = prod.preco;
        for ( i = 0; i < indice_encomenda; i++){
            if(vetor_encomendas[i].produtos[prod.id].quantidade!=0){
                vetor_encomendas[i].produtos[prod.id].preco=prod.preco;
            }
        }   
    }
}


/* comando E*/

/*funcao que apresenta a quantidade de um certo produto numa encomenda, verificando se o produto e a encomenda existem e se a quantidade nao e o.*/

void informacao_produto_encomenda(){
    produto prod;
    encomenda ord;
    scanf("%d:%d", &ord.id, &prod.id);
    if(ord.id >= indice_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ord.id);
    }    
    else if(prod.id >= indice_produto){
        printf("Impossivel listar produto %d. Produto inexistente.\n", prod.id);
    }
    else{
        printf("%s %d.\n", vetor_produtos[prod.id].descricao, vetor_encomendas[ord.id].produtos[prod.id].quantidade);  
    }
}


/* comando m*/
void ocorrencia_produto(){

/*funcao que recebe input de um id de produto e apresenta a encomenda que tem a maior quantidade desse produto, verificando se o produto existe e se esta em alguma encomenda*/

    produto prod;
    int maior_encomenda=0;
    int j;
    scanf("%d", &prod.id);
    if(prod.id >= indice_produto){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", prod.id);
    }
    else{
        for (j = 0; j < indice_encomenda; j++){
            if(vetor_encomendas[j].produtos[prod.id].quantidade > vetor_encomendas[maior_encomenda].produtos[prod.id].quantidade){
                maior_encomenda = vetor_encomendas[j].id;
            }
            /*no caso de duas encomendas possuirem a mesma quantidade do produto, a com id menor sera escolhida*/
            else if(vetor_encomendas[j].produtos[prod.id].quantidade == vetor_encomendas[maior_encomenda].produtos[prod.id].quantidade && vetor_encomendas[j].id < maior_encomenda){
                maior_encomenda = vetor_encomendas[j].id;
            }
        }
        if(maior_encomenda != 0){
            printf("Maximo produto %d %d %d\n", prod.id, maior_encomenda, vetor_encomendas[maior_encomenda].produtos[prod.id].quantidade);
        }
    }
}
   

/* comando l*/
void ordena_preco(){

/*funcao que ordena os produtos no vetor sistema por ordem crescente de precos, utilizando o algoritmo merge sort*/

    int i;
    mergesort(vetor_produtos,0,indice_produto-1, 0);
    printf("Produtos\n");
    for ( i = 0; i < indice_produto; i++){
        printf("* %s %d %d\n", vetor_produtos[i].descricao, vetor_produtos[i].preco, vetor_produtos[i].quantidade);
    }
}

void merge(produto vetor_produtos[],int left,int m,int right, int key){

/*a funcao merge junta dois subvetores do vetor principal introduzido*/
/*o primeiro vetor sera vetor_introduzido[left...m] e o segundo sera vetor_introduzido[m+1...right]*/
    int i,j,k;
    int n1 = m-left+1;
    int n2 = right-m;
    /*vetores auxiliares temporarios*/
    produto aux_left[quantidade_produtos];
    produto aux_right[quantidade_produtos];  

    /*a informacao do vetor principal e copiada para os vetores auxiliares*/
    for(i=0; i<n1; i++){
        aux_left[i]=vetor_produtos[left+i];
    }
    for(j=0; j<n2; j++){
        aux_right[j] = vetor_produtos[m+1+j];
    }

    i=0; /*indice inicial de aux_left*/
    j=0; /*indice inicial de aux_right*/
    k=left; /*indice inicial da juncao de ambos*/

    /*no caso de a key ser 0, os produtos no vetor serao comparados pelo seu preco*/
    if(key==0){
        while(i<n1 && j<n2){
            if(aux_left[i].preco <= aux_right[j].preco){
                vetor_produtos[k] = aux_left[i];
                i++;
            }
            else{
                vetor_produtos[k] = aux_right[j];
                j++;
            }
            k++;
        }
    }

    /*caso a key seja diferente de 0, os produtos serao comparados pela sua descricao*/
    else{
        while(i<n1 && j<n2){
            if(strcmp(aux_left[i].descricao, aux_right[j].descricao)<0){
                vetor_produtos[k] = aux_left[i];
                i++;
            }
            else{
                vetor_produtos[k] = aux_right[j];
                j++;
            }
            k++;
        }
    }

    /*se existirem, os restantes elementos de aux_left sao copiados*/
    while(i < n1){
        vetor_produtos[k] = aux_left[i];
        i++;
        k++;
    }
    /*se existirem, os restantes elemnetos de aux_right sao copiados*/
    while(j<n2){
        vetor_produtos[k] = aux_right[j];
        j++;
        k++;
    }
}


void mergesort(produto vetor_produtos[], int left, int right, int key){

/*a funcao mergesort */

    if(left < right){
        int m = left + (right - 1)/2;

        mergesort(vetor_produtos,left,m, key);
        mergesort(vetor_produtos,m+1,right, key);
        merge(vetor_produtos,left,m,right, key);
    }
}

/* comando L*/
void ordena_alfa(){

/*funcao que ordena os produtos numa encomenda por ordem alfabetica, utilizando o algoritmo merge sort*/

    encomenda ord;
    int i,j,k=0;
    produto vetor_aux[tamanho_encomenda]; /*vetor auxiliar que sera ordenado e imprimido*/
    scanf("%d", &ord.id);
    if(ord.id >= indice_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ord.id);
    }
    else{
        /*o vetor auxiliar vai ser constituido apenas pelos produtos que existem na encomenda*/
        for (j=0; j < tamanho_encomenda; j++){
            if(vetor_encomendas[ord.id].produtos[j].quantidade!=0){
                vetor_aux[k] = vetor_encomendas[ord.id].produtos[j];
                k++;
            }
        }
        mergesort(vetor_aux,0,k-1, 1);
        printf("Encomenda %d\n", ord.id);
        for ( i = 0; i < k; i++){
            printf("* %s %d %d\n", vetor_aux[i].descricao, vetor_aux[i].preco, vetor_aux[i].quantidade);
        }
    }
}
