#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAXDESC 63 /*Tamanho maximo de uma descricao*/
#define MAXIPD 10000 /*Numero maximo de produtos*/
#define MAXIDE 500 /*Numero maximo de encomendas*/
#define MAXENC 200 /*Numero maximo de produtos numa encomenda*/

/*Definicao das estruturas produto e encomenda**/
typedef struct{
    char desc[MAXDESC];
    int idp, preco, peso, qtd;
} produto;

typedef struct{
    int ide, peso, n_produtos_encomenda;
    produto produto[MAXENC]; /*Vetor com todos os produtos de uma certa encomenda*/
} encomenda;

/*Inicializacao das variaveis globais*/
produto armazem[MAXIPD]; /*Vetor com todos os produtos existentes*/
encomenda encomendas[MAXIDE]; /*Vetor com todas as encomendas existentes*/
int n_produtos_armazem=0; /*Numero de produtos existentes no armazem*/
int n_encomendas=0; /*Numero de encomendas existentes*/
int idp, ide, qtd, i, preco, max, j, k; /*Variaveis utilizadas por quase todas as funcoes*/
produto aux[MAXIPD]; /*Vetor auxiliar utilizado no merge sort*/
produto teste[MAXIPD]; /*Vetor utilizado para copiar outros vetores*/

/*Definicoes das funcoes utilizadas*/
/*Comando a - adiciona um novo produto ao sistema*/
void novo_produto(){
    produto novo;
    int i=0;
    char c;
    
    /*Dois getchar para ignorar o espaco em branco antes do input*/
    c=getchar();
    c=getchar();

    while(c!=':'){
        novo.desc[i]=c;
        c=getchar();
        i++;
    }
    novo.desc[i]='\0';
   
    scanf("%d:%d:%d", &novo.preco, &novo.peso, &novo.qtd);

    /*Visto que os id dos produtos sao ordenados, estes correspondem ao indice do vetor que contem todos os produtos*/
    novo.idp=n_produtos_armazem;
    armazem[n_produtos_armazem]=novo;
    n_produtos_armazem++;

    printf("Novo produto %d.\n", novo.idp);
}

/*Comando q - adiciona stock a um produto existente no sistema*/
void adiciona_stock(){
    scanf("%d:%d", &idp, &qtd);
    if(idp>=n_produtos_armazem){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else{
        armazem[idp].qtd+=qtd;
    }
}

/*Comando N - cria uma nova encomenda*/
void nova_encomenda(){
    encomenda nova;
    nova.n_produtos_encomenda=0;
    nova.peso=0;
    /*Visto que os id das encomendas sao ordenados, estes correspondem ao indice do vetor que contem todas as encomendas*/
    nova.ide=n_encomendas;
    encomendas[n_encomendas]=nova; 
    printf("Nova encomenda %d.\n", nova.ide);
    n_encomendas++;
}

/*Comando A - adiciona um produto a uma encomenda*/
void troca_armazem_encomenda(int ide, int i, int qtd, int idp){
    /*Atualiza as quantidades no armazem e na encomenda, assim como o peso da mesma*/
    encomendas[ide].produto[i].qtd+=qtd;
    armazem[idp].qtd-=qtd;
    encomendas[ide].peso+=armazem[idp].peso*qtd;
}

void adiciona_prod_encomenda(){
    scanf("%d:%d:%d", &ide, &idp, &qtd);
    /*Verificacoes*/
    if (ide>=n_encomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp>=n_produtos_armazem){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if (armazem[idp].qtd-qtd<0){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if (encomendas[ide].peso+armazem[idp].peso*qtd>200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    else{
        for (i=0; i<encomendas[ide].n_produtos_encomenda; i++){
            /*Caso o id procurado ja exista na encomenda*/
            if (encomendas[ide].produto[i].idp==idp){
                troca_armazem_encomenda(ide, i, qtd, idp);
                return;
            }
        }
        /*Caso o id nao exista na encomanda*/
        encomendas[ide].produto[encomendas[ide].n_produtos_encomenda].idp=idp;
        troca_armazem_encomenda(ide, encomendas[ide].n_produtos_encomenda, qtd, idp);
        encomendas[ide].n_produtos_encomenda++;
    }
}

/*Comando r - remove stock a um produto existente*/
void remove_stock(){
    scanf("%d:%d", &idp, &qtd);
    /*Verificacoes*/
    if (idp>=n_produtos_armazem){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if(armazem[idp].qtd-qtd<0){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    }
    else{
        /*Atualiza a quantidade em armazem*/
        armazem[idp].qtd-=qtd;
    }
}

/*Comando R - remove um produto de uma encomenda*/
void remover(){
    scanf("%d:%d", &ide, &idp);
    /*Verificacoes*/
    if (ide>=n_encomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if (idp>=n_produtos_armazem){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else{
        for (i=0; i<encomendas[ide].n_produtos_encomenda; i++){
            /*Caso o produto exista na encomenda, eh removido, repondo a sua quantidade no armazem*/
            if (encomendas[ide].produto[i].idp==idp){
                armazem[idp].qtd+=encomendas[ide].produto[i].qtd;
                encomendas[ide].peso-=armazem[idp].peso*encomendas[ide].produto[i].qtd;
                /*Recua um indice a todos os produtos existentes ah frente do indice do produto removido*/
                for(j=i; j<encomendas[ide].n_produtos_encomenda; j++){
                    encomendas[ide].produto[j]=encomendas[ide].produto[j+1];
                }
                encomendas[ide].n_produtos_encomenda--;
                return;
            }
        }
    }
}

/*Comando C - calcula o custo de uma encomenda*/
void calcula_custo(){
    scanf("%d", &ide);
    /*Verificacoes*/
    if (ide>=n_encomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        preco=0;
        /*Soma o preco de todos os produtos*/
        for(i=0; i<encomendas[ide].n_produtos_encomenda; i++){
            idp=encomendas[ide].produto[i].idp;
            preco+=encomendas[ide].produto[i].qtd*armazem[idp].preco;
        }
        printf("Custo da encomenda %d %d.\n", ide, preco);
    }
}

/*Comando p - altera o preco de um produto existente no sistema*/
void altera_preco(){
    scanf("%d:%d", &idp, &preco);
    /*Verificacoes*/
    if (idp>=n_produtos_armazem){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        /*Atualiza o preco*/
        armazem[idp].preco=preco;
    }
}

/*Comando E - lista a descri??o e a quantidade de um produto numa encomenda*/
void lista_desc_qtd(){
    scanf("%d:%d", &ide, &idp);
    /*Verificacoes*/
    if (ide>=n_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if (idp>=n_produtos_armazem){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else{
        for(i=0; i<encomendas[ide].n_produtos_encomenda; i++){
            /*Caso o produto exista na encomenda, lista a sua descricao e a sua quantidade, nessa mesma encomenda*/
            if (encomendas[ide].produto[i].idp==idp){
                printf("%s %d.\n", armazem[idp].desc, encomendas[ide].produto[i].qtd);
                return;
            }
        }
        /*Caso na exista, a quantidade eh 0*/
        printf("%s 0.\n", armazem[idp].desc);
    }
}

/*Comando m - lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void lista_ide_max(){
    scanf("%d", &idp);
    /*Verificacoes*/
    if (idp>=n_produtos_armazem){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else{
        max=0; /*Variavel que guarda o valor maximo do prododuto nas encomendas*/
        /*Dois ciclos for, um que percorre encomendas e outro que percorre os produtos dentro dessas encomendas*/
        for(i=0; i<n_encomendas;i++){
            for(j=0; j<=encomendas[i].n_produtos_encomenda; j++){
                /*Caso o id seja o pretendido e a quantidade maior que o maximo ate ai registado, atualiza o maximo*/
                if (encomendas[i].produto[j].idp==idp && encomendas[i].produto[j].qtd>max){
                    max=encomendas[i].produto[j].qtd;
                    ide=encomendas[i].ide;
                }
            }
        }
        if (max!=0){
            printf("Maximo produto %d %d %d.\n", idp, ide, max);
        }
    }
}

/*Comando l - lista todos os produtos existentes no sistema por ordem crescente de preco*/
/*Merge sort utilizado para ordenar os produtos, sendo o criterio os precos dos mesmos*/
void merge_preco(produto a[], int left, int m, int right) {
    /*Junta as listas auxiliares ja ordenadas*/
    for (i = m+1; i > left; i--){
        aux[i-1] = a[i-1];
    }
    for (j = m; j < right; j++){
        aux[right+m-j] = a[j+1];
    }
    /*Gera o vetor ordenado, atraves dos dois vetores auxiliares ja organizados*/
    for (k = left; k <= right; k++){
        if (aux[j].preco==aux[i].preco){
            if (aux[j].idp< aux[i].idp){
                a[k] = aux[j--];
            }
            else{
                a[k] = aux[i++];
            }
        }
        else if (aux[j].preco< aux[i].preco){
            a[k] = aux[j--];
        }
        else{
            a[k] = aux[i++];    
        }
    }
}

void mergesort_preco(produto a[], int left, int right){
    int m = (right+left)/2; /*Indice da posicao media*/

    if (right <= left){
        return;
    } 
    /*Parte recurssiva da funcao, que divide a lista inicial em duas, ate que estas sejam de apenas de um elemento*/
    mergesort_preco(a, left, m);
    mergesort_preco(a, m+1, right);
    merge_preco(a, left, m, right); 
}

void cria_copia(produto copia[], produto copiado[], int n){
    int i;
    /*Copia o conteudo de um vetor ate ao indice desejado*/
    for (i=0; i<n; i++){
        copia[i]=copiado[i];
    }
}

void lista_ordem_preco(){
    /*Cria uma copia do armazem e organiza essa copia atraves do merge sort, sendo o criterio o preco*/
    cria_copia(teste, armazem, n_produtos_armazem);
    mergesort_preco(teste,0,n_produtos_armazem-1);
    printf("Produtos\n");
    /*Imprime os produtos ordenados por ordem crescente do preco*/
    for(i=0;i<n_produtos_armazem;i++){
        printf("* %s %d %d\n", armazem[teste[i].idp].desc, teste[i].preco, teste[i].qtd);
    }
}

/*Comando L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
/*Merge sort utilizado para ordenar os produtos, ordenando-os alfabeticamente*/
void merge_alfa(produto a[], int left, int m, int right) {
    /*Junta as listas auxiliares ja ordenadas*/
    for (i = m+1; i > left; i--){
        aux[i-1] = a[i-1];
    }
    for (j = m; j < right; j++){
        aux[right+m-j] = a[j+1];
    }
    /*Gera o vetor ordenado, atraves dos dois vetores auxiliares ja organizados*/
    for (k = left; k <= right; k++){
        if (strcmp(armazem[aux[j].idp].desc,armazem[aux[i].idp].desc)<0){
            a[k] = aux[j--];
        }
        else{
            a[k] = aux[i++];    
        }
    }
}

void mergesort_alfa(produto a[], int left, int right){
    int m = (right+left)/2; /*Indice da posicao media*/

    if (right <= left){
        return;
    } 
    /*Parte recurssiva da funcao, que divide a lista inicial em duas, ate que estas sejam de apenas de um elemento*/
    mergesort_alfa(a, left, m);
    mergesort_alfa(a, m+1, right);
    merge_alfa(a, left, m, right);
}

void lista_ordem_alfa(){
    scanf("%d", &ide);
    /*Verificacoes*/
    if (ide>=n_encomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        /*Cria uma copia do armazem e organiza essa copia atraves do merge sort, sendo o criterio a ordem alfabetica*/
        cria_copia(teste, encomendas[ide].produto, encomendas[ide].n_produtos_encomenda);
        mergesort_alfa(teste,0,encomendas[ide].n_produtos_encomenda-1);
        printf("Encomenda %d\n", ide);
        /*Imprime os produtos ordenados alfabeticamente*/
        for(i=0;i<encomendas[ide].n_produtos_encomenda;i++){
            printf("* %s %d %d\n", armazem[teste[i].idp].desc, armazem[teste[i].idp].preco, teste[i].qtd);
        }
    }
}

/*Funcao main, que le o input e atraves de um switch determina que conjunto de funcoes eh chamado*/
int main(){
    char c;
    
    while((c=getchar())!=EOF){
        switch(c){
            case 'a':
                novo_produto();
                break;
            case 'q':
                adiciona_stock();
                break;
            case 'N':
                nova_encomenda();
                break;
            case 'A':
                adiciona_prod_encomenda();
                break;
            case 'r':
                remove_stock();
                break;
            case 'R':
                remover();
                break;
            case 'C':
                calcula_custo();
                break;
            case 'p':
                altera_preco();
                break;
            case 'E':
                lista_desc_qtd();
                break;
            case 'm':
                lista_ide_max();
                break;
            case 'l':
                lista_ordem_preco();
                break;
            case 'L':
                lista_ordem_alfa();
                break;
            case 'x':
                return 0;
        }
    }
    return 0;
}
