#include <stdio.h>
#include <string.h>

/*--------------------DEFINICAO DE DIRETIVAS DE PRE-COMPILACAO--------------------*/

#define STRMAX 63
#define PRODMAX 10000
#define ENCMAX 500
#define PESOMAX 200
#define TRUE -8
#define FALSE -7 /* O true e false foram definidos com valores diferentes de 0 e 1 de forma a nao intervir no normal funcionamento do programa */
#define maxN 10000 /* Dimensao maxima do vetor de ordenacao */
#define existeSistema(idp) idp >= id_p /* Abstracoes uteis, indicam nos se um produto ja foi inserido no sistema */
#define existeEncomenda(ide) ide >= id_e /* Indicam, nos se uma encomenda ja foi inserida no sistema */

/*--------------------INICIALIZACAO DE ESTRUTURAS--------------------*/

typedef struct{

    int id; /*Contem um id unico, que lhe e atribuido ao ser adicionado*/
    char desc[STRMAX]; 
    int preco;
    int peso;
    int qtd; /* Stock do produto */

} Produto;

typedef struct{
    int n_produtos; /*Quantidade maxima de produtos numa encomenda*/
    int peso;
    Produto prods[PRODMAX];
} Encomenda;

/*--------------------INICIALIZACAO DOS VETORES UTILIZADOS PARA ARMAZENAR OS PRODUTOS--------------------*/

Produto lista_produtos[PRODMAX]; /* Vetor que armazena os produtos (e os seus atributos) existentes no sistema */
Encomenda encomenda[ENCMAX]; /* Vetor de encomendas, que contem produtos. */
Produto aux[maxN]; /* Vetor auxiliar para a ordenacao de produtos */

/*--------------------INICIALIZACAO DE VARIAVEIS GLOBAIS--------------------*/

int id_p = 0; /*Aponta para o numero maximo de produtos existentes no sistema*/
int id_e = 0; /*Aponta para o numero maximo de encomendas existentes no sistema*/

/*--------------------PROTOTIPOS - FUNCOES AUXILIARES--------------------*/

void printProduto(); /* INPUT: () / OUTPUT: Produtos existentes no sistema */
void printEncomenda(int ide); /* INPUT: id_encomenda (inteiro) / OUTPUT: Produtos existentes nessa encomenda */
int existeProduto(int idp); /* INPUT: id_produto / OUTPUT: Posicao do produto no sistema, caso exista, FALSE, caso nao */
int estaEncomenda(int idp, int ide); /* INPUT: id_produto, id_encomenda / OUTPUT: Posicao do produto numa encomenda, caso exista, FALSE, caso nao */

/*--------------------PROTOTIPOS - FUNCOES UTILIZADAS NO MAIN--------------------*/

void adicionaProduto();
void adicionaStock();
void criaEncomenda();
void adicionaProduto_E();
void removeProduto_E();
void removeStock();
void custoEncomenda();
void alteraPreco();
void listaDescQtd();
void ocorreMais_E();
void listaProdutos();
void listaProdutos_E();

int main(){
    char letra = '\0';
    
    while(letra != 'x'){
        letra = getchar();
        switch(letra){
            case 'a':
                adicionaProduto();
                break;
            case 'q':
                adicionaStock();
                break;
            case 'N':
                criaEncomenda();
                break;
            case 'A':
                adicionaProduto_E();
                break;
            case 'r':
                removeStock();
                break;
            case 'C':
                custoEncomenda();
                break;
            case 'R':
                removeProduto_E();
                break;
            case 'p':
                alteraPreco();
                break;
            case 'E':
                listaDescQtd();
                break;
            case 'm':
                ocorreMais_E();
                break;
            case 'l':
                listaProdutos();
                break;
            case 'L':
                listaProdutos_E();
                break;
            default:
                break;
        }
    }
    return 0;
}


void printProduto(){ /* 'k': Devolve os produtos existentes no sistema, quando chamada */
    int i;

    printf("Produtos\n");
    for(i = 0; i < id_p; i++){
        printf("* %s %d %d\n", lista_produtos[i].desc , lista_produtos[i].preco, lista_produtos[i].qtd);        
    }
}

void printEncomenda(int ide){ /* 'K': Devolve a encomenda correspondente ao ID dado existente no sistema, quando chamada */
    int i;

    printf("Encomenda %d\n", ide);
    for(i=0; i < encomenda[ide].n_produtos; i++){
        printf("* %s %d %d\n", encomenda[ide].prods[i].desc, encomenda[ide].prods[i].preco, encomenda[ide].prods[i].qtd);
    }
}

int existeProduto(int idp){ /* Verifica se existe o produto com o ID dado no sistema, e devolve a sua posicao */
    int i;
    int pos = FALSE; /* Comeca definido como FALSE, so e alterado se existir no sistema */

    if(idp < id_p){
        for(i = 0; i < id_p; i++){
            if(lista_produtos[i].id == idp){
                pos = i;
                break; /* Se encontrar, parar e devolver a posicao */
            }
        }  
    }
    return pos;  
}

int estaEncomenda(int idp, int ide){ /* Verifica se existe o produto com o ID dado na encomenda dada, e devolve a sua posicao */
    int i;
    int pos = FALSE; /* Comeca definido como FALSE, so e alterado se existir na encomenda */
    
    if(idp < id_p){
        for(i=0; i < encomenda[ide].n_produtos; i++){
            if(encomenda[ide].prods[i].id == idp){
                pos = i;
                break; /* Se encontrar, parar e devolver a posicao */
            }
        }  
    }
    return pos;
}


void adicionaProduto(){ /* 'a': Recebe os dados de um produto e armazena-o no sistema */

    scanf(" %[^:]:%d:%d:%d", lista_produtos[id_p].desc, &lista_produtos[id_p].preco,  &lista_produtos[id_p].peso,  &lista_produtos[id_p].qtd);

    lista_produtos[id_p].id = id_p;
    printf("Novo produto %d.\n", id_p);
    id_p++; /* Aumenta o numero maximo de produtos existentes no sistema */
}


void adicionaStock(){ /* 'q': Adiciona stock a um produto, caso este exista  */
    int idp, new_qtd, pos_prod;

    scanf("%d:%d", &idp, &new_qtd);

    pos_prod = existeProduto(idp);
    if(pos_prod == FALSE)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);   
    else /* Se este existir, aumentar a sua qtd */
        lista_produtos[pos_prod].qtd += new_qtd;     
}

void criaEncomenda(){ /* 'N': Insere uma nova encomenda no sistema */
    printf("Nova encomenda %d.\n", id_e);
    id_e++;
}

void adicionaProduto_E(){ /* 'A': Adiciona um produto a uma encomenda existente no sistema */
    int ide, idp, qtd,pos_prod,pos_enc;

    scanf("%d:%d:%d", &ide, &idp, &qtd);
    pos_prod = existeProduto(idp);

    if(existeEncomenda(ide))
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (existeSistema(idp))
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (qtd > lista_produtos[pos_prod].qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if((encomenda[ide].peso + (lista_produtos[pos_prod].peso * qtd)) > PESOMAX)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else{
        pos_enc = estaEncomenda(idp, ide);
        if(pos_enc != FALSE){ /* Se o produto ja existe na encomenda */
            encomenda[ide].prods[pos_enc].qtd += qtd;
            encomenda[ide].peso += (encomenda[ide].prods[pos_enc].peso * qtd); /* Aumentar somente a quantidade e o peso */
        }
        else{ /* Caso contrario, inserir o produto na encomenda */
            encomenda[ide].prods[encomenda[ide].n_produtos] = lista_produtos[pos_prod];
            encomenda[ide].prods[encomenda[ide].n_produtos].qtd = qtd;
            encomenda[ide].peso += (lista_produtos[pos_prod].peso * qtd);
            encomenda[ide].n_produtos += 1;
        }
    lista_produtos[pos_prod].qtd -= qtd; /* Remover a quantidade adicionada a encomenda do sistema */
    }
}



void removeStock(){ /* 'r': Remove stock a um produto, se este existir */
    int idp, qtd, pos_prod;

    scanf("%d:%d", &idp, &qtd);
    pos_prod = existeProduto(idp);
    if(pos_prod == FALSE) /*Se nao existe... */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if(lista_produtos[pos_prod].qtd - qtd < 0) /* Peso negativo... */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        lista_produtos[pos_prod].qtd -= qtd;      
}
     
void custoEncomenda(){ /* 'C': Calcula o custo de uma encomenda = soma (qtd*preco) */
    int ide,i;
    int custo = 0;

    scanf("%d", &ide);

    if(existeEncomenda(ide))
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        for(i = 0; i < encomenda[ide].n_produtos; i++){
            custo += (encomenda[ide].prods[i].qtd * encomenda[ide].prods[i].preco);
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

void removeProduto_E(){ /* 'R': Remove um produto de uma encomenda */
    int ide,idp;
    int i, pos;

    scanf("%d:%d", &ide, &idp);

    if(existeEncomenda(ide))
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    
    else{
        if(existeSistema(idp))
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        else{
            pos = estaEncomenda(idp,ide);
            if(pos != FALSE){ /* Se esta na encomenda... */
                lista_produtos[existeProduto(idp)].qtd += encomenda[ide].prods[pos].qtd;
                encomenda[ide].peso -= (encomenda[ide].prods[pos].peso * encomenda[ide].prods[pos].qtd);
                for(i = pos; i < encomenda[ide].n_produtos; i++)
                    encomenda[ide].prods[i] = encomenda[ide].prods[i+1]; /* Preenche a posicao do vetor removido */
                encomenda[ide].n_produtos--; /* Reduz o numero de produtos na encomenda */
            }
        }
    }
}

void alteraPreco(){ /* 'p': Altera o preco de um produto no sistema */
    int idp,new_preco,i,pos_prod,pos_enc;

    scanf("%d:%d", &idp, &new_preco);

    pos_prod = existeProduto(idp);

    if(pos_prod != FALSE){

        lista_produtos[pos_prod].preco = new_preco; /* Altera o preco */
        for(i=0; i< id_e; i++){
            pos_enc = estaEncomenda(idp,i);
            if(pos_enc != FALSE){ /* Se esta na encomenda... */
                encomenda[i].prods[pos_enc].preco = new_preco; /* Altera o preco dentro da encomenda */
            }    
        }
    }
    else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
}

void listaDescQtd(){/* 'E': Lista a descricao e a quantidade de um produto */
    int ide, idp, pos_prod_enc;

    scanf("%d:%d", &ide, &idp);

    pos_prod_enc = estaEncomenda(idp, ide);

    if(existeSistema(idp))
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else{
        if(existeEncomenda(ide))
            printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
        else if(pos_prod_enc == FALSE)
            printf("%s 0.\n", lista_produtos[existeProduto(idp)].desc);
        else printf("%s %d.\n",encomenda[ide].prods[pos_prod_enc].desc, encomenda[ide].prods[pos_prod_enc].qtd);
    }    
}



void ocorreMais_E(){/* 'm': Devolve o elemento que ocorre mais vezes num vetor */
    int idp,i, pos_prod_enc;
    int max_id = -1;
    int max = 0;

    scanf("%d", &idp);

    if(existeSistema(idp))
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        if(id_e >= 0){
            for(i = 0; i < id_e; i++){
                pos_prod_enc = estaEncomenda(idp, i);               
                if(pos_prod_enc != FALSE){   /* Se esta na encomenda... */
                    if (encomenda[i].prods[pos_prod_enc].qtd > max){ /*Se for maior que o valor maximo...*/
                        max = encomenda[i].prods[pos_prod_enc].qtd; /* Novo elemento maximo */
                        max_id = i; /* ID do novo maximo */
                    }
                }
            }
            if(max_id != -1) /* Se o ID foi alterado, devolver o ID, caso contrario, nao devolver nada */
                printf("Maximo produto %d %d %d.\n", idp, max_id, max);
        }
    }
}

void merge(Produto prods[], int left, int mid, int right){ 
    int i, j, k;

    for (i = mid+1; i > left; i--) /* i comeca a meio do vetor e para quando chegar ao inicio */
        aux[i-1] = prods[i-1];
    for (j = mid; j < right; j++) /* j comeca a meio do vetor e para quando chegar ao fim */
        aux[right+mid-j] = prods[j+1];
    for (k = left; k <= right; k++)
        if ((aux[j].preco < aux[i].preco) || (aux[j].preco == aux[i].preco && aux[j].id < aux[i].id)){ /* Se o preco for igual, desempatar com ID */
            prods[k] = aux[j];
            j--;
        }
        else{
            prods[k] = aux[i];
            i++;
        }
}

void mergesort(Produto a[], int l, int r){ 
    int m = (r+l)/2;

    if (r <= l)
        return;
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
}

void listaProdutos(){ /* 'l': Lista os produtos existentes no sistema por ordem de preco */
    
    mergesort(lista_produtos, 0, id_p-1);
    printProduto();  
}

void merge_E(Produto enc[], int left, int mid, int right){ 
    int i, j, k;

    for (i = mid+1; i > left; i--) /* i comeca a meio do vetor e para quando chegar ao inicio */
        aux[i-1] = enc[i-1];
    for (j = mid; j < right; j++) /* j comeca a meio do vetor e para quando chegar ao fim */
        aux[right+mid-j] = enc[j+1];
    for (k = left; k <= right; k++)
        if((strcmp(aux[j].desc, aux[i].desc) < 0) || (strcmp(aux[j].desc, aux[i].desc) == 0  && aux[j].id < aux[i].id)){ /* Se o nome for igual, desempatar com ID  */
            enc[k] = aux[j];
            j--;
        }
        else{
            enc[k] = aux[i];
            i++;
        }
}

void mergesort_E(Produto a[], int l, int r){ 
    int m = (r+l)/2;

    if (r <= l)
        return;
    mergesort_E(a, l, m);
    mergesort_E(a, m+1, r);
    merge_E(a, l, m, r);
}

void listaProdutos_E(){ /* 'L': Lista as encomendas existentes no sistema por ordem de alfabetica */
    int ide;

    scanf("%d", &ide);

    if(existeEncomenda(ide))
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else{
        mergesort_E(encomenda[ide].prods, 0,encomenda[ide].n_produtos-1);
        printEncomenda(ide);
    }
}