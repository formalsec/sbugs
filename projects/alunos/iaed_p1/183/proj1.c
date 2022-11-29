#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*N?mero m?ximo de carateres da string que descreve um produto.*/
#define MAXCHAR 63
#define MAXENCOMENDAS 500
#define MAXPRODENC 200
#define MAXPRODUTOS 10000

#define ENC_SEM_PRODUTO 250
#define ENC_NAO_INICIADA -1
#define PRODUTO_NAO_INICIADO -2

/*Definicao da estrutura do produto.*/
typedef struct produto {
    int iden;
    char desc[MAXCHAR];
    int preco;
    int peso;
    int quanti;
} produto;

/*Definicao da estrutura da encomenda.*/
 typedef struct encomenda {
    produto v_encomendas[MAXPRODENC];
    int ide;
    int peso_enc;
} encomenda;

/*Criei um array de produtos para os armazenar enquanto eles nao sao postos numa encomenda.*/
produto armazem[MAXPRODUTOS];

/*Criei a 'estrutura' das encomendas.*/
encomenda encomendas[MAXENCOMENDAS];


char vazia[MAXCHAR] = "\0"; /*Auxiliar para ser usado futuramente na funcao_R.*/


/*Esta funcao inicia todas as encomendas como vazias.
Ao iniciar as encomendas com o ide a -1 permite-me lidar com as encomendas de forma mais clara mais a frente.*/
void distingue_encomendas(encomenda encomendas[]){
    int i;
    for(i = 0; i < MAXENCOMENDAS; i++){
        encomendas[i].ide = ENC_NAO_INICIADA;
    }
}

/*Esta funcao inicia o armazem sem produtos.*/
void distingue_produtos_armazem(produto armazem[]){
    int i;
    for(i = 0; i < MAXPRODUTOS; i++){
        armazem[i].iden = PRODUTO_NAO_INICIADO;
    }
}

/*Todas as funcoes de copia de produtos sao auxiliares e vao ser usadas mais a frente.*/
void copia_produtos(produto destino[], produto fonte[]){
    int i;
    for(i = 0; i < MAXPRODENC; i++){
        destino[i].iden = fonte[i].iden;
        destino[i].peso = fonte[i].peso;
        destino[i].preco = fonte[i].preco;
        destino[i].quanti = fonte[i].quanti;
        strcpy(destino[i].desc, fonte[i].desc);
    }
}

void copia_produto_1(produto destino[], produto fonte[], int l){
    destino[l].iden = fonte[l].iden;
    destino[l].peso = fonte[l].peso;
    destino[l].preco = fonte[l].preco;
    destino[l].quanti = fonte[l].quanti;
    strcpy(destino[l].desc, fonte[l].desc);
}

void copia_produto_2(produto destino[], produto fonte[], int j){
    destino[0].iden = fonte[j].iden;
    destino[0].peso = fonte[j].peso;
    destino[0].preco = fonte[j].preco;
    destino[0].quanti = fonte[j].quanti;
    strcpy(destino[0].desc, fonte[j].desc);
}

void copia_produto_3(produto destino[], produto fonte[], int j){
    destino[j].iden = fonte[j+1].iden;
    destino[j].peso = fonte[j+1].peso;
    destino[j].preco = fonte[j+1].preco;
    destino[j].quanti = fonte[j+1].quanti;
    strcpy(destino[j].desc, fonte[j+1].desc);
}

void copia_produto_4(produto destino[], produto fonte[], int j){
    destino[j+1].iden = fonte[0].iden;
    destino[j+1].peso = fonte[0].peso;
    destino[j+1].preco = fonte[0].preco;
    destino[j+1].quanti = fonte[0].quanti;
    strcpy(destino[j+1].desc, fonte[0].desc);
}

void copia_produtos_5(produto destino[], produto fonte[], int i){
    destino[i-1].iden = fonte[i-1].iden;
    destino[i-1].peso = fonte[i-1].peso;
    destino[i-1].preco = fonte[i-1].preco;
    destino[i-1].quanti = fonte[i-1].quanti;
    strcpy(destino[i-1].desc, fonte[i-1].desc);
}

void copia_produtos_6(produto destino[], produto fonte[], int k, int j){
    destino[k].iden = fonte[j].iden;
    destino[k].peso = fonte[j].peso;
    destino[k].preco = fonte[j].preco;
    destino[k].quanti = fonte[j].quanti;
    strcpy(destino[k].desc, fonte[j].desc);
    j--;
}

void copia_produtos_7(produto destino[], produto fonte[], int k, int i){
    destino[k].iden = fonte[i].iden;
    destino[k].peso = fonte[i].peso;
    destino[k].preco = fonte[i].preco;
    destino[k].quanti = fonte[i].quanti;
    strcpy(destino[k].desc, fonte[i].desc);
    i++;
}

void copia_produtos_8(produto destino[], produto fonte[], int r, int m, int j){
    destino[r+m-j].iden = fonte[j+1].iden;
    destino[r+m-j].peso = fonte[j+1].peso;
    destino[r+m-j].preco = fonte[j+1].preco;
    destino[r+m-j].quanti = fonte[j+1].quanti;
    strcpy(destino[r+m-j].desc, fonte[j+1].desc);
}

/*Esta funcao permite descobrir quantos produtos o armazem contem.*/
int descobre_tamanho(produto armazem[]){
    int contador = 0;
    int i;
    for(i=0; i<MAXPRODUTOS; i++){
        if(armazem[i].iden != PRODUTO_NAO_INICIADO)
            contador++;
    }
    return contador; 
}

/*Esta funcao e necessaria para o algoritmo de ordenacao merge sort.*/
void merge(produto lista[], int l, int m, int r){
    int i, j, k; 
    produto lista_aux[MAXPRODENC];

    for (i = m+1; i > l; i--){
        copia_produtos_5(lista_aux, lista, i);
    }    
    for (j = m; j < r; j++){
        copia_produtos_8(lista_aux, lista, r, m, j);
    }    
    for (k = l; k <= r; k++){
        if (lista_aux[j].quanti > lista_aux[i].quanti || i > m)
            copia_produtos_6(lista, lista_aux, k, j);
        else
            copia_produtos_7(lista, lista_aux, k, i);
    }        
} 

/*Esta funcao vai ser chamada pela funcao_L, e o algoritmo de ordenacao dessa funcao.*/
void merge_sort(produto lista[], int l, int r){
    if (l < r){
        int meio = (int) (r+l)/2;

        merge_sort(lista, l, meio);
        merge_sort(lista, meio+1, r);

        merge(lista, l, meio, r);
    }
}


/*Definicao das funcoes especificas para cada caso.*/
/*Adiciona um produto ao armazem.*/
void funcao_a(produto armazem[], char descricao[], int preco, int peso, int quantidade){
    static int gere_produto;

    strcpy(armazem[gere_produto].desc, descricao);    
    armazem[gere_produto].preco = preco;
    armazem[gere_produto].peso = peso;
    armazem[gere_produto].quanti = quantidade;
    armazem[gere_produto].iden = gere_produto;
    
    printf("Novo produto %d.\n", gere_produto);
    
    gere_produto++;
}

/*Remove um produto do armazem.*/
produto funcao_q(produto armazem[], int idp, int quantidade){
    if (armazem[idp].iden == PRODUTO_NAO_INICIADO){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else{
        armazem[idp].quanti += quantidade;
    }   
    return armazem[idp];    
}

/*Inicia uma encomenda.*/
encomenda funcao_N(){
    /*A variavel em baixo e usada para a criacao da encomenda e incrementada no fim da funcao 
    para poder estar com o valor correta para ser usada na utilizacao seguinte desta funcao.*/
    static int gere_enc;  

    int l, aux;
    for(l = 0; l < MAXPRODENC; l++){ 
        encomendas[gere_enc].v_encomendas[l].iden = ENC_SEM_PRODUTO;
        strcpy(encomendas[gere_enc].v_encomendas[l].desc, vazia);
        encomendas[gere_enc].v_encomendas[l].preco = 0;
        encomendas[gere_enc].v_encomendas[l].peso = 0;
        encomendas[gere_enc].v_encomendas[l].quanti = 0;
    }
    encomendas[gere_enc].ide = gere_enc;
    encomendas[gere_enc].peso_enc = 0;
    printf("Nova encomenda %d.\n", gere_enc);
    aux = gere_enc;
    gere_enc++;
    return encomendas[aux];
}

/*Coloca um produto do armazem numa encomenda ja iniciada.*/
encomenda funcao_A(encomenda encomendas[], int ide, int idp, int quantidade){
    static int i; /*Variavel que vai ser usada para a colocacao do produto na encomenda*/
    if (encomendas[ide].ide == ENC_NAO_INICIADA)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    
    else if (armazem[idp].iden == PRODUTO_NAO_INICIADO)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    
    else if (quantidade > armazem[idp].quanti)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);

    else if (encomendas[ide].peso_enc + armazem[idp].peso > 200)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n" ,idp ,ide);

    else{
       encomendas[ide].v_encomendas[i].preco = armazem[idp].preco;
       encomendas[ide].v_encomendas[i].quanti = armazem[idp].quanti;
       encomendas[ide].v_encomendas[i].peso = armazem[idp].peso;
       encomendas[ide].v_encomendas[i].iden = armazem[idp].iden;
       strcpy(encomendas[ide].v_encomendas[i].desc, armazem[idp].desc);
       encomendas[ide].peso_enc += armazem[idp].peso;
       armazem[idp].quanti -= quantidade;
       i++; 
    }
    return encomendas[ide];
}

/*Remove uma quantidade a um produto do armazem.*/
produto funcao_r(produto armazem[], int idp, int quantidade){
    if (armazem[idp].iden == PRODUTO_NAO_INICIADO)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else if (armazem[idp].quanti - quantidade < 0)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidade, idp);
    
    else{
        armazem[idp].quanti -= quantidade;
    }
    return armazem[idp];    
}

/*Remove um produto de uma encomenda se o produto existir na encomenda.*/
encomenda funcao_R(encomenda encomendas[], int ide, int idp){
    int i;

    if (encomendas[ide].ide == ENC_NAO_INICIADA)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (encomendas[ide].v_encomendas[idp].iden == ENC_SEM_PRODUTO)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else {
        for(i=0; i < MAXPRODUTOS; i++){
            /*Procurei onde estava o produto dentro da encomenda.*/
            if(encomendas[ide].v_encomendas[i].iden == idp){
                armazem[idp].quanti += encomendas[ide].v_encomendas[i].quanti;

                encomendas[ide].v_encomendas[i].iden = ENC_SEM_PRODUTO;
                encomendas[ide].v_encomendas[i].preco = 0;
                encomendas[ide].v_encomendas[i].peso = 0;
                encomendas[ide].v_encomendas[i].quanti = 0;
                strcpy(encomendas[ide].v_encomendas[i].desc, vazia);
            } 
        }
    }
    return encomendas[ide]; 
}

/*Calcula o custa de uma encomenda se esta existir.*/
void funcao_C(encomenda encomendas[], int ide){
    int total = 0;
    int m;
    if (encomendas[ide].ide == ENC_NAO_INICIADA)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        for(m = 0; m < MAXENCOMENDAS; m++){
            total += encomendas[ide].v_encomendas[m].preco;
        }
    }    
    printf("Custo da encomenda %d %d.\n", ide, total);
}

/*Altera o preco de um produto que se encontra no sistema.*/
void funcao_p(produto armazem[], int idp, int valor_numerico){
    int i, j, k;
    if (armazem[idp].iden == PRODUTO_NAO_INICIADO){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        for(k=0; k<MAXPRODUTOS; k++){
            /*Procurar o produto no armazem.*/
            if (armazem[k].iden == idp)
                armazem[k].preco = valor_numerico;
        }        
        
        for(i=0; i<MAXENCOMENDAS; i++){
            for(j=0; j<MAXPRODENC; j++){
                /*Procurar o produto em todas as encomendas.*/
                if (encomendas[i].v_encomendas[j].iden == idp)
                    encomendas[i].v_encomendas[j].preco = valor_numerico;
            }
        }
    }
    
}

/*Lista a descricao e a quantidade de todos os produtos de uma encomenda.*/
void funcao_E(encomenda encomendas[], int ide, int idp){
    int i;
    if (encomendas[ide].ide == ENC_NAO_INICIADA)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (encomendas[ide].v_encomendas[idp].iden == ENC_SEM_PRODUTO)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else {
        for(i=0; i < MAXPRODENC; i++){
            if(encomendas[ide].v_encomendas[i].iden == idp)
                printf("%s %d\n", encomendas[ide].v_encomendas[i].desc, encomendas[ide].v_encomendas[i].quanti);
        }
    }    
}

/*Lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/
void funcao_m(encomenda encomendas[], produto armazem[], int idp){
    int i, j, m, k;
    int contador[MAXENCOMENDAS]; /*Criei um vetor de inteiros para guardar o valor do contador de cada encomenda.*/
    int maior = 0;
    int ide_pretendido;
    int quantidade_do_idp = 0;
    int encomendas_nao_iniciadas = 0;
    int contador_idp_inexistente = 0;
    int contador_aux = 0;

    /*Inicializa o contador de cada encomenda a 0.*/
    for(m = 0; m < MAXENCOMENDAS; m++){
        contador[m] = 0;
    }

    for(k=0; k<MAXPRODUTOS; k++){
        if (armazem[k].iden != idp)
            contador_aux++;
    }
    if (contador_aux == MAXPRODUTOS)        
        printf("Impossivel listar maximo do produto %d. Produto inexistente.", idp);
    
    for(i = 0; i < MAXENCOMENDAS; i++){
        if (encomendas[i].ide == ENC_NAO_INICIADA)
            encomendas_nao_iniciadas++;
            
                

        for(j = 0; j < MAXPRODENC; j++){
            if (encomendas[i].v_encomendas[j].iden == idp){
                contador[i]++;
                if (contador[i] > maior)
                    maior = contador[i];
            }
            else if (encomendas[i].v_encomendas[j].iden != idp){
                contador_idp_inexistente++;
                if (contador_idp_inexistente == MAXPRODUTOS)
                    break;
            }        
        }

        if (contador[i] == maior)
            ide_pretendido = i;
    }
    
    if (encomendas_nao_iniciadas == MAXPRODENC)
        return;

    for(i = 0; i < MAXPRODENC; i++){
        if (encomendas[ide_pretendido].v_encomendas[i].iden == idp)
            quantidade_do_idp += encomendas[ide_pretendido].v_encomendas[i].quanti;
    }

    printf("Maximo produto %d %d %d.\n", idp, ide_pretendido, quantidade_do_idp);
}

/*Lista todos os produtos existentes no sistema por ordem crescente de pre?o.*/
void funcao_l(produto armazem[]){
    int i, j, l,k;
    produto novo_armazem[MAXPRODUTOS];
    produto auxiliar[1]; /*Criei um vetor so com um produto, pois a funcao auxiliar recebe vetores como argumento.*/
    int barreira = descobre_tamanho(armazem);

    for(l=0; l<barreira; l++){
        copia_produto_1(novo_armazem, armazem, l); 
    }

    for(i = 0; i < barreira; i++){
        for(j=0; j < barreira-1; j++){
            if (novo_armazem[j].preco > novo_armazem[j+1].preco){
                copia_produto_2(auxiliar, novo_armazem, j);
                copia_produto_3(novo_armazem, novo_armazem, j);
                copia_produto_4(novo_armazem, auxiliar, j);
            }
        }
    }

    printf("Produtos\n");
    for(k=0; k<barreira; k++){
        printf("*%s %d %d\n", novo_armazem[k].desc, novo_armazem[k].preco, novo_armazem[k].quanti);
    }
}

/*Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void funcao_L(encomenda encomendas[], int ide){
    if (encomendas[ide].ide == ENC_NAO_INICIADA)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else{
        int i, r;
        produto lista_de_prod_da_enc[MAXPRODENC];
        copia_produtos(lista_de_prod_da_enc, encomendas[ide].v_encomendas);
        r = descobre_tamanho(lista_de_prod_da_enc);
        merge_sort(lista_de_prod_da_enc, 0, r);
        printf("Encomenda %d\n", ide);
        for(i = 0; i < r; i++){
            printf("%s %d %d\n", lista_de_prod_da_enc[i].desc, lista_de_prod_da_enc[i].preco, lista_de_prod_da_enc[i].quanti);
        }    
    }    
}

/* Codigo principal. */
int main(){

    /*Variaveis para ir buscar o input e passar os valores para as funcoes.*/
    int c;
    int ide;
    int idp; 
    int preco_aux;
    int peso_aux;
    int quanti_aux;
    char cadeia_auxiliar[MAXCHAR];

    distingue_produtos_armazem(armazem); /*Inicia o armazem sem produtos.*/
    distingue_encomendas(encomendas); /*Inicia as encomendas todas como vazias.*/

    while( (c = getchar()) != EOF ){
        switch(c) {
            case 'a':
                scanf("%[^:]:%d:%d:%d", cadeia_auxiliar, &preco_aux, &peso_aux, &quanti_aux);
                funcao_a(armazem, cadeia_auxiliar, preco_aux, peso_aux, quanti_aux);
                continue;
            
            case 'q':
                scanf("%d:%d", &idp, &quanti_aux);
                funcao_q(armazem, idp, quanti_aux);
                break;    
            
            case 'N':
                funcao_N();
                break;
            
            case 'A':
                scanf("%d:%d:%d", &ide, &idp ,&quanti_aux);
                funcao_A(encomendas, ide, idp, quanti_aux);
                break;
        
            case 'r':
                scanf("%d:%d", &idp, &quanti_aux);
                funcao_r(armazem, idp, quanti_aux);
                break;
            
            case 'R':
                scanf("%d:%d", &ide, &idp);
                funcao_R(encomendas, ide, idp);
                break;
            
            case 'C':
                scanf("%d", &ide);
                funcao_C(encomendas, ide);
                break;
            
            case 'p':
                scanf("%d:%d", &idp, &preco_aux);
                funcao_p(armazem, idp, preco_aux);
                break;

            case 'E':
                scanf("%d:%d", &ide, &idp);
                funcao_R(encomendas, ide, idp);
                break;    
            
            case 'm':
                scanf("%d", &idp);
                funcao_m(encomendas, armazem, idp);
                break;

            case 'l':
                funcao_l(armazem);
                continue;

            case 'L':
                scanf("%d", &ide);
                funcao_L(encomendas, ide);
                break;

            case 'x':
                return 0;
        }
    }
    return -1;
}