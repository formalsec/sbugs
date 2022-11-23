#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_IDP 10000
#define MAX_IDE 500
#define key(A) (A) 
#define less(A, B) (key(A) < key(B))


int aux_produtos[MAX_IDP]; /* lista auxiliar a ser usada na funcao junta_produtos() */
int aux_encomenda[MAX_IDP]; /* lista auxiliar a ser usada na funcao junta_encomenda() */

/* Criar a estrutura Produto */

typedef struct produto {
    char descricao[63]; /*descricao do produto*/
    int preco; /*preco do produto*/
    int peso; /*peso do produto*/
    int qtd; /*quantidade do produto*/
} Produto;

/* Criar a estrutura Encomenda */

typedef struct encomenda {
    int qtd; /*quantidade de um produto na encomenda */
    int preco; /* preco total de um produto na encomenda */
} Encomenda;

static Encomenda encomenda[MAX_IDE][MAX_IDP]; /* encomenda x com o produto y que da a qtd e o preco de y */
static Produto produto[MAX_IDP]; /* produto x que da a descricao,o preco,o peso e a qtd de x */


/* Funcoes auxiliares - comandos */

void cria_produto(int lista_idp[MAX_IDP], int idp);
void adiciona_stock(int lista_idp[MAX_IDP]);
void cria_encomenda(int lista_ide[MAX_IDE], int ide);
void adiciona_encomenda(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE],int peso_total[MAX_IDE]);
void remove_stock(int lista_idp[MAX_IDP]);
void altera_preco(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE]);
void custo_encomenda(int lista_ide[MAX_IDE],int lista_idp[MAX_IDP]);
void remove_produto(int lista_ide[MAX_IDE],int lista_idp[MAX_IDP],int peso_total[MAX_IDE]);
void desc_produto_enc(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE]);
void maior_quantidade(int lista_ide[MAX_IDE],int lista_idp[MAX_IDP]);
void lista_produtos(int lista_idp[MAX_IDP]);
void lista_produtos_encomenda(int lista_ide[MAX_IDE],int lista_idp[MAX_IDP]);

/*Funcoes de preenchimento */

void preenche_estrutura();
void preenche_peso(int peso_total[MAX_IDE]);

/* Funcoes de ordenacao */

void junta_encomenda(int a[MAX_IDP],int esq,int m,int dir);
void ordena(int a[MAX_IDP],int esq,int dir,char key);
void junta_produtos(int a[MAX_IDP],int esq,int m,int dir);

/* Funcao Principal */

int main() {
    char comando; 
    int lista_idp[MAX_IDP],lista_ide[MAX_IDE];  /* lista com os ids dos produto e encomendas */
    int idp = 0; /*id do produto*/
    int ide = 0; /*id da encomenda*/
    int peso_total[MAX_IDE]; /* indica o peso total da encomenda x */

    preenche_estrutura(encomenda); /* preencher a qtd e o preco dos produtos a 0 */
    preenche_peso(peso_total);  /* preencher o peso total das encomendas a 0 */
    

    scanf("%c",&comando); 

    while (comando != 'x') {
        switch (comando) { /* indica o comando a ser executado */
        
            case 'a': /* adiciona um novo produto ao sistema */
              cria_produto(lista_idp,idp);
              idp = idp + 1;
              break;

            case 'q': /* adiciona stock a um produto existente no sistema */
              adiciona_stock(lista_idp);
              break;

            case 'N': /* cria uma nova encomenda */
              cria_encomenda(lista_ide,ide); 
              ide = ide + 1;
              break;

            case 'A': /* adiciona um produto existente no sistema a uma encomenda */
              adiciona_encomenda(lista_idp,lista_ide,peso_total);
              break;

            case 'r': /* remove stock a um produto existente no sistema */
              remove_stock(lista_idp);
              break;

            case 'R': /* remove um produto a uma encomenda */
              remove_produto(lista_ide,lista_idp,peso_total);
              break;
            
            case 'C': /* calculo o custo total de uma encomenda */
              custo_encomenda(lista_ide,lista_idp);
              break;
             
            case 'p': /* altera o preco de uma funcao existente no sistema */
              altera_preco(lista_idp,lista_ide);
              break;

            case 'E': /* retorna a descricao e a quantidade de um produto existente no sistema */
              desc_produto_enc(lista_idp,lista_ide);
              break;

            case 'm': /* retorna a encomenda em que o dado produto ocorre mais vezes */
              maior_quantidade(lista_ide,lista_idp);
              break;

            case 'l': /* lista todos os produtos existentes no sistema por ordem crescente de peso */
              lista_produtos(lista_idp);
              break;

            case 'L': /* lista todos os produtos de uma dada encomenda por ordem alfabetica */
              lista_produtos_encomenda(lista_ide,lista_idp);
              break;
            
        }

        scanf("%c",&comando); /* executa o proximo comando */

    }
    return 0;
}

/* funcao que recbe o sistema (lista_idp) e o id do produto adicona um novo produto (idp) ao sistema */

void cria_produto(int lista_idp[MAX_IDP], int idp) {
    scanf(" %[^:]:%d:%d:%d", produto[idp].descricao, &produto[idp].preco, &produto[idp].peso, &produto[idp].qtd); /* le as caracteristicas do produto */

    printf("Novo produto %d.\n", idp); /* imprime o id do produto */

    lista_idp[idp] = 'P'; /* indica a existencia de um novo produto */

}

/* funcao que adiciona a um produto do sistema (lista_idp) stock */

void adiciona_stock(int lista_idp[MAX_IDP]) {
    int idp_aux,qtd_aux;

    scanf("%d:%d", &idp_aux,&qtd_aux);

    if (lista_idp[idp_aux] != 'P') { /*caso o produto nao exista, o output e erro */

        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp_aux);
    }

    else produto[idp_aux].qtd = produto[idp_aux].qtd + qtd_aux; /* adiciona o stock dado ao produto */

}

/* funcao que recebe uma lista com todas as encomendas e o id da encomenda e adiciona essa encomenda(ide) a lista (lista_ide) */

void cria_encomenda(int lista_ide[MAX_IDE], int ide) {
    lista_ide[ide] = 'E'; /* indica a existencia de uma nova encomenda */
    printf("Nova encomenda %d.\n", ide); /* imprime o id da encomenda */
}

/* funcao que adiciona a encomenda um produto e uma dada quantidade desse produto, alterando o preco e o peso da encomenda */

void adiciona_encomenda(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE], int peso_total[MAX_IDE]) {
    int ide_aux,idp_aux,qtd_aux;

    scanf("%d:%d:%d", &ide_aux, &idp_aux, &qtd_aux);

    if (lista_idp[idp_aux] != 'P') { /* caso o produto a ser adicionado nao exista, o output e erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp_aux,ide_aux);
    }

    else if (lista_ide[ide_aux] != 'E') { /*caso a encomenda nao exista, o output e erro */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp_aux,ide_aux);
    }

    else if (produto[idp_aux].qtd < qtd_aux) { /*caso a quantidade do prduto seja menor que a quantidade desejada */
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp_aux,ide_aux);
    }

    else if (peso_total[ide_aux] + (qtd_aux * produto[idp_aux].peso) > 200) { /*caso o peso seja superior a 200*/
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp_aux,ide_aux);
    }
    
    else { /* adiciona a quatidade desejada a encomenda e retira essa quantidade do stock do produto */

        encomenda[ide_aux][idp_aux].qtd = encomenda[ide_aux][idp_aux].qtd + qtd_aux; /* adiciona stock do produto a encomenda */
        encomenda[ide_aux][idp_aux].preco = encomenda[ide_aux][idp_aux].preco + (qtd_aux * produto[idp_aux].preco); /*contabiliza o preco */
        peso_total[ide_aux] = peso_total[ide_aux] + (qtd_aux * produto[idp_aux].peso); /*contabiliza o peso*/
        produto[idp_aux].qtd = produto[idp_aux].qtd - qtd_aux; /* remove o stock do produto */
    }
}

/* funcao que remove uma certa quantidade de um determinado produto */

void remove_stock(int lista_idp[MAX_IDP]) {
    int idp_aux,qtd_aux;

    scanf("%d:%d", &idp_aux,&qtd_aux);

    if (lista_idp[idp_aux] != 'P') {

        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp_aux);
    }

    else if (produto[idp_aux].qtd - qtd_aux < 0 ) { /* caso a quantidade a tirar seja superior ao stock do produto */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd_aux,idp_aux);
    }

    else {
        produto[idp_aux].qtd = produto[idp_aux].qtd - qtd_aux; /* retira a quantidade desejada do stock do produto */
    }


}

/* funcao que altera o preco de um determinado produto, afetando tambem o preco da encomenda */

void altera_preco(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE]) {
    int idp_aux;
    int preco_aux;
    int i = 0;

    scanf("%d:%d", &idp_aux,&preco_aux);

    if (lista_idp[idp_aux] != 'P') {

        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp_aux);
    }
    
    else { /*altera o preco do produto */
        produto[idp_aux].preco = preco_aux;

        while(lista_ide[i] == 'E') {

            if (encomenda[i][idp_aux].qtd != 0) { /*altera o preco de todas as encomendas com esse produto */
                encomenda[i][idp_aux].preco = encomenda[i][idp_aux].qtd * preco_aux;
            }

            ++i;
        }
    }

}

/* funcao que calcula o custo total da encomenda */

void custo_encomenda(int lista_ide[MAX_IDE], int lista_idp[MAX_IDP]){
    int ide_aux;
    int i = 0;
    int total = 0; /* custo total da encomenda */
    scanf("%d", &ide_aux);
    if (lista_ide[ide_aux] != 'E') {
      printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide_aux);
    }
    else {
         
        while(lista_idp[i] == 'P') { /*enquanto existir produtos*/

            if (encomenda[ide_aux][i].qtd != 0) { /*ver se o produto existe nesta encomenda */

                total = total + encomenda[ide_aux][i].preco; /*calcular o custo da encomenda */
            }

            ++i;
        }

     printf("Custo da encomenda %d %d.\n", ide_aux,total);

    }

}

/* funcao que remove um produto de uma dada encomenda */

void remove_produto(int lista_ide[MAX_IDE],int lista_idp[MAX_IDP],int peso_total[MAX_IDE]) {
    int ide_aux,idp_aux;

    scanf("%d:%d", &ide_aux, &idp_aux);
    if (lista_ide[ide_aux] != 'E') {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp_aux,ide_aux);
    }

    else if (lista_idp[idp_aux] != 'P') {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp_aux,ide_aux);
    }

    else {

        peso_total[ide_aux] = peso_total[ide_aux] - (encomenda[ide_aux][idp_aux].qtd * produto[idp_aux].peso); /*o peso total do produto na encomenda e removido*/
        produto[idp_aux].qtd = produto[idp_aux].qtd + encomenda[ide_aux][idp_aux].qtd; /* retoma o stock do produto */
        encomenda[ide_aux][idp_aux].qtd = 0; /*quantidade a 0 indica a nao existencia do produto */
        encomenda[ide_aux][idp_aux].preco = 0; /* o preco e tambem anulado */
        

        
    }
}

/* funcao que retorna a descricao de um dado produto numa dada encomenda */

void desc_produto_enc(int lista_idp[MAX_IDP], int lista_ide[MAX_IDE]) {
    int ide_aux,idp_aux;

    scanf("%d:%d", &ide_aux, &idp_aux);
    if (lista_ide[ide_aux] != 'E') {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_aux);
    }

    else if (lista_idp[idp_aux] != 'P') {
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp_aux);
    }
    else {

        printf("%s %d.\n",produto[idp_aux].descricao,encomenda[ide_aux][idp_aux].qtd); /* imprime a descricao do produto e a quantidade do mesmo na encomenda */

    }

}

/* funcao que retorna o produto que se repete mais vezes numa dada encomenda */

void maior_quantidade(int lista_ide[MAX_IDE], int lista_idp[MAX_IDP]) {
    int idp_aux,ide_aux;
    int i=0;
    int maior; /*variavel que depende da quantidade do produto na encomenda*/

    scanf("%d",&idp_aux);

    if (lista_idp[idp_aux] != 'P') {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp_aux);
    }
    
    else {

        maior = encomenda[0][idp_aux].qtd; 
        ide_aux = 0;

        while(lista_ide[i] == 'E') {
            if (lista_ide[i+1] == 'E' && encomenda[i+1][idp_aux].qtd > maior) { 
                maior = encomenda[i+1][idp_aux].qtd; /* verifica em qual encomenda o produto se repete mais vezes */
                ide_aux = i + 1;

            }
            
            /* caso as quantidades sejam iguais o de maior quantidade sera o de menor id */

            else if(lista_ide[i+1] == 'E' && encomenda[i+1][idp_aux].qtd == maior) {
                maior = encomenda[i+1][idp_aux].qtd; 
            }

            ++i;
        }

        if (maior != 0) { /* caso exista o produto em qualquer encomenda */
            printf("Maximo produto %d %d %d.\n",idp_aux,ide_aux,maior);
        }

    }

}

/* funcao que lista todos os produtos existentes no sistemas por ordem crescente de precos */

void lista_produtos(int lista_idp[MAX_IDP]) {
    int j,i = 0;
    int dir,esq;  /* dir -> 1 membro do vetor; esq -> ultimo membro do vetor */
    int vetor_aux[MAX_IDP];  /* vetor auxiliar com os idps */

    printf("Produtos\n");

    while(lista_idp[i] == 'P') {
        vetor_aux[i] = i; /*criar o vetor com todos os idps para saber a que idp corresponde o preco */
        ++ i;
    }

    dir = i-1;
    esq = 0;

    ordena(vetor_aux,esq,dir,'P'); /*funcao que ordena o vetor dos idps por ordem crescente do preco de cada idp */
    
    for(j = 0; j <= dir; ++j) {

        printf("* %s %d %d\n",produto[vetor_aux[j]].descricao,produto[vetor_aux[j]].preco,produto[vetor_aux[j]].qtd); /*imprimo todos os elementos do vetor*/
    }
}

/* funcao que lista todos os produtos de uma dada encomenda */

void lista_produtos_encomenda(int lista_ide[MAX_IDE], int lista_idp[MAX_IDP]) {

    int ide_aux;
    int cont = 0;
    int i,k = 0;
    int dir; /*ultimo membro da lista */
    int lista_idps[200];

    scanf("%d", &ide_aux); /* le a encomenda em que vao ser listados os produtos */

    if (lista_ide[ide_aux] != 'E') {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide_aux);
    }

    else {

        printf("Encomenda %d\n", ide_aux);

        while(lista_idp[k] == 'P') {

            if (encomenda[ide_aux][k].qtd != 0) {
                lista_idps[cont] = k; /* crio um vetor com todos os idps dos produtos da encomenda */
                ++cont;
            }

            ++k;
        }

        dir = cont - 1; /* indico a posicao do ultimo elemento do vetor */

        ordena(lista_idps,0,dir,'E'); /* ordeno o vetor de acordo com a descricao dos idps */

        for(i = 0; i <= cont-1; i++) {

            printf("* %s %d %d\n",produto[lista_idps[i]].descricao,produto[lista_idps[i]].preco,encomenda[ide_aux][lista_idps[i]].qtd); /* imprimo o vetor */

        }
    
    }

}   

/* funcao que poe todos os valores a 0 indicando que ainda nao existe nenhum produto na encomenda */

void preenche_estrutura() {
    int k,l;

    for (k = 0; k < MAX_IDE; ++k) {
        for (l = 0; l < MAX_IDP; ++ l) {
            encomenda[k][l].preco = 0; /* coloco a quantidade de todos os produtos a 0 */
            encomenda[k][l].qtd = 0;  /*coloco o preco dos produtos a 0 */
        }   
    }

}

/* funcao que poe o vetor peso_total a 0 */

void preenche_peso(int peso_total[MAX_IDE]) {
    int i;
    for(i = 0; i < MAX_IDE; ++i) {
        peso_total[i] = 0; /* inicio a lista a 0s */
    }
}

/* funcao que ordena um determinado vetor */

void ordena(int a[MAX_IDP],int esq,int dir,char key) {
    int m = (esq+dir)/2; /*indico o meio da lista */
    if (dir <= esq) return; 
    /*separar a lista em duas (esquerda-meio, meio+1-direira) */
    ordena(a,esq,m,key); /*faco o mesmo para a nova lista */
    ordena(a,m+1,dir,key);  /* o mesmo para a outra */
    if (key == 'P') {
        junta_produtos(a,esq,m,dir); /* junto todas as listas obtendo uma lista ordenada */
    }

    else if (key == 'E') {
        junta_encomenda(a,esq,m,dir);
    }
}

/* funcao que junta varios vetores ordenados num so vetor */

void junta_encomenda(int a[MAX_IDP],int esq,int m,int dir) {
    int i,j,k;
    int idp1,idp2;

    /*cria o vetor auxiliar */

    for(i = m+1; i > esq; i--) {
        aux_encomenda[i-1] = a[i-1];
    }
    for(j=m;j < dir;j++) {
        aux_encomenda[dir+m-j] = a[j+1];
    }
    for(k= esq; k <= dir; k++) {
        idp1 = aux_encomenda[j];
        idp2 = aux_encomenda[i];

        /* vejo qual das descricoes vem primeiro alfabeticamente */

        if (strcmp(produto[idp1].descricao,produto[idp2].descricao) < 0) { /*escolho os elementos das pontas de forma a ordenar o vetor a[] */
            a[k] = aux_encomenda[j--];  
        }

        else {
            a[k] = aux_encomenda[i++];
        }
    }
}

/* funcao que junta varios vetores ordenados num so vetor */

void junta_produtos(int a[MAX_IDP],int esq,int m,int dir) {
    int i,j,k;
    int idp1,idp2;

    /*cria o vetor auxiliar */

    for(i = m+1; i > esq; i--) {
        aux_produtos[i-1] = a[i-1];
    }
    for(j=m;j < dir;j++) {
        aux_produtos[dir+m-j] = a[j+1];
    }
    for(k= esq; k <= dir; k++) {
        idp1 = aux_produtos[j];
        idp2 = aux_produtos[i];

        if (less(produto[idp1].preco,produto[idp2].preco)) { /*escolho os elementos das pontas de forma a ordenar o vetor a[] */
            a[k] = aux_produtos[j--];  
        }

        else if(produto[idp1].preco == produto[idp2].preco) { /*caso os precos sejam iguais, ordenar pelo idp*/
            if (less(idp1,idp2)) {
                a[k] = aux_produtos[j--];
            }

            else {
                a[k] = aux_produtos[i++];
            }
        }

        else {
            a[k] = aux_produtos[i++];
        }
    }
}




