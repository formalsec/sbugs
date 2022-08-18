#include <stdio.h>
#include <string.h>


#define FIM -1         /* todos os elementos nao utilizados do carrinho de comoras vao tem como idp FIM. */
#define LIVRE -2      /* se o elemento do carrinho de compras de uma encomenda estiver livre quer dizer que ja esteve ocupado mas nao atualmente.*/
#define ORDEM_PRECO 1      /* caso em que se quer ordenar o vetor pelo preco do produto*/
#define ORDEM_ALFABETICA 0  /* caso em que se quer ordenar o vetor pela ordem alfabetica da descricao do produto. */
#define MAX_PRODS 10000      /* numero maximo de produtos */ 
#define MAX_ORDERS 500       /* numero maximo de encomendas */ 
#define MAX_ORDER_PRODS 200  /* numero maximo de produto numa encomenda */
#define MAX_DESC 63          /* numero maximo da caracteres da descricao de um produto */ 

/*------------------------ ESTRUTURAS--------------------------*/

typedef struct produto {
    char desc[MAX_DESC];        /* Cada produto tem uma descricao, um peso, preco e quantidade em stock*/
    int preco;
    int peso;
    int qt_stock;
} produto;

typedef struct encomenda {
    int carrinho_compras[MAX_ORDER_PRODS][2];  /* carrinho_compras: vetor cujos elementos sao vetores de dim 2: id do produto, qt do produto*/
    int peso;
} encomenda;

/*-------------------- VARIAVEIS GLOBAIS -----------------------*/

int idp_atual = 0;         /* idp_atual e o valor atual de id de produto que o proximo produto a ser gerado ira ter*/
int ide_atual = 0;         /* ide_atual (id da encomanda atual) funciona da mesma forma que o idp_atual */
int valores[3] = {0,0,0};  /* sao guardados os valores inteiros dados em cada input (em cada input sao dados no maximo 3 e no minimo 1)*/
char descricao_prod[MAX_DESC];   /* variavel onde se guarda a descricao do produto atual */
produto produtos[MAX_PRODS];   /* produtos = lista de produtos*/
encomenda encomendas[MAX_ORDERS]; /* encomendas = lista de encomendas*/

/*---------------- FUNCOES PARA CADA COMANDO ------------------*/

/* Adiciona um novo produto ao sistema*/
void add_produto(){
    int i;
    for (i = 0; descricao_prod[i] != '\0'; i++)     /* guarda-se a descricao do produto */
        produtos[idp_atual].desc[i] = descricao_prod[i];
    produtos[idp_atual].desc[i] = '\0';
    produtos[idp_atual].preco = valores[0];    
    produtos[idp_atual].peso = valores[1];
    produtos[idp_atual].qt_stock= valores[2];
    printf("Novo produto %d.\n", idp_atual);
    idp_atual++;   /* incrementa-se o idp_atual para que o proximo produto seja gerado na proxima posicao do vetor*/
}

/* Adiciona stock a um produto existente no sistema*/
void add_stock(){
    int idp = valores[0], qtd = valores[1];  /* vai-se buscar os valores necessarios a valores. */
    if (idp_atual - 1 < idp)
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    else
        produtos[idp].qt_stock += qtd;    
}
/* Cria uma nova encomenda */
void new_order(){
    int i;
    for (i = 0; i < MAX_ORDER_PRODS; i++) {
        encomendas[ide_atual].carrinho_compras[i][0] = FIM; /* incializa-se o o vetor da encomenda*/
        encomendas[ide_atual].carrinho_compras[i][1] = 0; /* o primeiro sub_elemente vai corresponder ao id do produto e o segundo a qtd.*/
    }
    encomendas[ide_atual].peso = 0;
    printf("Nova encomenda %d.\n", ide_atual);
    ide_atual++;    /* incrementa-se o ide_atual para que a proxima encomenda seja gerada na proxima posicao do vetor*/
}

/* Adiciona um produto a uma encomenda. Se o produto j? existir na encomenda, adiciona a nova quantidade ? quantidade existente*/
void add_prod_to_order(){
    int ide = valores[0], idp = valores[1], qtd = valores[2];
    if (ide_atual - 1 < ide)
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp_atual - 1 < idp)
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else if (produtos[idp].qt_stock < qtd)
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    else if (encomendas[ide].peso + qtd * produtos[idp].peso > MAX_ORDER_PRODS)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    else{
        int i;
        for (i = 0; encomendas[ide].carrinho_compras[i][0] != idp && encomendas[ide].carrinho_compras[i][0] != FIM && /*pesquisa-se o carrinho de compras*/
            encomendas[ide].carrinho_compras[i][0] != LIVRE; i++); /* de uma encomanda ate se encotrar o produto ou um espaco livre.*/
        if (encomendas[ide].carrinho_compras[i][0] == LIVRE){
            int j;          /* se se econtrar um espaco livre, verifica-se se noa existe um espaco mais a frente que ja tenha o produto. */
            for (j = i + 1; encomendas[ide].carrinho_compras[j][0] != idp && encomendas[ide].carrinho_compras[j][0] != FIM; j++);
            if (encomendas[ide].carrinho_compras[j][0] == idp)
                i = j;     /* Se esse for o caso, altare-se o indice onde vai aumentar a quantidade do produto. */
        }
        encomendas[ide].carrinho_compras[i][0] = idp;
        encomendas[ide].carrinho_compras[i][1] += qtd;
        encomendas[ide].peso += qtd * produtos[idp].peso;
        produtos[idp].qt_stock -= qtd;
    }
}

/* Remove stock a um produto existente */
void remove_stock(){
    int idp = valores[0], qtd = valores[1];
    if (idp_atual - 1 < idp)
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    else if (produtos[idp].qt_stock < qtd)
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
    else
        produtos[idp].qt_stock -= qtd;
}

/* Remove um produto de uma encomenda */
void remove_prod_from_order(){
    int ide = valores[0], idp = valores[1];
    if (ide_atual - 1 < ide)
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    else if (idp_atual - 1 < idp)
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    else{
        int i;    /* pesquisa-se o carrinho de comprars ate encontrar o produto ou ate chegar ao fim do carrinho. */
        for (i = 0; i < MAX_ORDER_PRODS && encomendas[ide].carrinho_compras[i][0] != idp && encomendas[ide].carrinho_compras[i][0] != FIM; i++);
        if (encomendas[ide].carrinho_compras[i][0] == idp){
            produtos[idp].qt_stock += encomendas[ide].carrinho_compras[i][1];
            encomendas[ide].carrinho_compras[i][0] = LIVRE;  /* o espaco onde antes havia um produto passa a estar livre. */
            encomendas[ide].peso -= (encomendas[ide].carrinho_compras[i][1] * produtos[idp].peso);
            encomendas[ide].carrinho_compras[i][1] = 0;
        }
    }
}

/* Calcula o custo de uma encomenda */
void oder_cost(){
    int ide = valores[0];
    if (ide_atual - 1 < ide)
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    else{
        int custo = 0, i;
        for (i = 0; i < MAX_ORDER_PRODS && encomendas[ide].carrinho_compras[i][0] != FIM; i++){
            int idp = encomendas[ide].carrinho_compras[i][0];
            if (encomendas[ide].carrinho_compras[i][0] != LIVRE) /* passa-se a frente se a posicao esta livre, ou seja, nao tem produto.*/
                custo += encomendas[ide].carrinho_compras[i][1] * produtos[idp].preco;
        }
        printf("Custo da encomenda %d %d.\n", ide, custo);
    }
}

/* Altera o pre?o de um produto existente no sistema */
void change_prod_price(){
    int idp = valores[0], preco = valores[1];
    if (idp_atual - 1 < idp)
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    else
        produtos[idp].preco = preco;
}

/* Lista a descri??o e a quantidade de um produto numa encomenda */
void desc_qtd_prod_from_order(){
    int ide = valores[0], idp = valores[1];
    if (ide_atual - 1 < ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else if (idp_atual - 1 < idp)
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    else{
        int i;
        for (i = 0; i < MAX_ORDER_PRODS && encomendas[ide].carrinho_compras[i][0] != idp && encomendas[ide].carrinho_compras[i][0] != FIM; i++);
        printf("%s %d.\n",produtos[idp].desc, 
            i == MAX_ORDER_PRODS || encomendas[ide].carrinho_compras[i][0] == FIM? 0 : encomendas[ide].carrinho_compras[i][1]);
            /* se o produto nao estiver na encomenda, a sua quantidade e 0. */
    }
}

/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, */
void id_order_most_qtd_prod(){ /* dever? imprimir a encomenda de menor idp */
    int idp = valores[0];
    if (idp_atual - 1 < idp)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    else{
        int i, j, res[2] = {0, -1}; /* res[0] = ide, res[1] = qtd. Res[1] = -1 se nenhuma encomenda tiver o produto.*/
        for (i = 0; i < ide_atual; i++){ /* ve-se a qtd do produto em cada encomenda. */
            for (j = 0; j < MAX_ORDER_PRODS && encomendas[i].carrinho_compras[j][0] != FIM; j++){
                if (encomendas[i].carrinho_compras[j][0] == idp){     /* ve-se se o produto existe na encomenda. */
                    if (encomendas[i].carrinho_compras[j][1] > res[1]){ /* se a qtd do produto atual for maior que res, altera-se o valor. */
                        res[0] = i;
                        res[1] = encomendas[i].carrinho_compras[j][1];
                    }
                    break;
                }
            }
        }
        if (ide_atual > 0 && res[1] != -1) /* so se faz print se alguma encomenda tiver o produto, o caso em que a qtd do */
            printf("Maximo produto %d %d %d.\n", idp, res[0], res[1]);                      /* produto e diferente de -1. */
    }
}


/*---------------- FUNCOES DE ORDENACAO ------------------*/

/* Verifica se x e menor que y, tanto em termos do preco como em termos da ordem alfabetica da descricao do produto*/
int less(int state, int x, int y){
    int res = 0;
    if (state == ORDEM_PRECO)  /* se o state for ORDEM_PRECO, verifica se o preco de x e menor que o de y, ou se teem o mesmo preco */  
        res = produtos[x].preco < produtos[y].preco || (produtos[x].preco == produtos[y].preco && x < y) ? 1 : 0; /* e o id de x e menor.*/
    else if (x != y){  
        int i = 0;   /* caso contrario, verifica-se por ordem alfabetica. Quando se encontrar dois caracteres diferente, verifica-se se */
        for (i = 0; i < MAX_DESC - 1 && produtos[x].desc[i] == produtos[y].desc[i]; i++); /* o caracter de x e menor que o de y. */
        res = produtos[x].desc[i] < produtos[y].desc[i] ? 1 : 0; /* o i e no maximo 62, para o caso em que quando as descricoes sao iguas*/
    }                                                                                         /* o indice nao sair dos limites da string.*/
    return res;
}

/* faz merge de duas listas ordenadas */
void merge(int state, int a[], int aux[], int l, int m, int r){
    int i, j, k;
    for (i = m + 1; i > l; i --) /*copia-se o primeiro vetor para aux de forama a que no final i seja igual a l. */
        aux[i - 1] = a[i - 1];
    for (j = m ; j < r; j++)    /* copia-se o segundo vetor para aux invertido, de forma a que j seja igual a r. */
        aux[r + m - j] = a[j + 1];
    for (k = l; k <= r; k++){
        if (less(state, aux[j], aux[i]) || i > m) /* vao-se colocando os elementos ordenados em a, com o uso da funcao less. */
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/* algoritmo de ordenacao */
void merge_sort(int state, int a[], int aux[], int l, int r){
    int m = (r + l)/2;   /* m = ponto medio */
    if (r <= l)
        return;
    merge_sort(state, a, aux, l, m);
    merge_sort(state, a, aux, m + 1, r);
    merge(state, a, aux, l, m, r);
}

/* Lista todos os produtos existentes no sistema por ordem crescente de pre?o */
void order_prods_price(){
    int a[MAX_PRODS], aux[MAX_PRODS], i, j;
    for (i = 0; i < idp_atual; i++) /* copia-se para a os idps do produtos existentes*/
        a[i] = i;
    merge_sort(ORDEM_PRECO, a, aux, 0, idp_atual - 1); /* ordena-se os produtos pelo preco */
    printf("Produtos\n");
    for (j = 0; j < idp_atual; j++)
        printf("* %s %d %d\n", produtos[a[j]].desc, produtos[a[j]].preco, produtos[a[j]].qt_stock);
}


/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void order_prods_from_order_desc(){
    int ide = valores[0];
    if (ide_atual - 1 < ide)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    else {
        int a[MAX_ORDER_PRODS], aux[MAX_ORDER_PRODS], i, j = 0, k, p;
        for (i = 0; i < MAX_ORDER_PRODS && encomendas[ide].carrinho_compras[i][0] != -1; i++){
            if (encomendas[ide].carrinho_compras[i][0] != LIVRE)  /* copia-se os ids do produtos para a.*/
                a[j++] = encomendas[ide].carrinho_compras[i][0]; 
        }
        merge_sort(ORDEM_ALFABETICA, a, aux, 0, j - 1);
        printf("Encomenda %d\n", ide);
        for (k = 0; k <= j - 1; k++){
            for(p = 0; encomendas[ide].carrinho_compras[p][0] != a[k]; p++);
            printf("* %s %d %d\n", produtos[a[k]].desc, produtos[a[k]].preco, encomendas[ide].carrinho_compras[p][1]);
        }
    }
}
/*---------------- FUNCAO QUE CHAMA OUTRAS FUNCOES ------------------*/

/* Chama funcoes de acordo com o primeiro caracter lido da linha */
void call_function(char c){
    switch (c){
        case 'a':
            add_produto();
            break;
        case 'q':
            add_stock();
            break;
        case 'N':
            new_order();
            break;
        case 'A':
            add_prod_to_order();
            break;
        case 'r':
            remove_stock();
            break;
        case 'R':
            remove_prod_from_order();
            break;
        case 'C':
            oder_cost();
            break;
        case 'p':
            change_prod_price();
            break;
        case 'E':
            desc_qtd_prod_from_order();
            break;
        case 'm':
            id_order_most_qtd_prod();
            break;
        case 'l':
            order_prods_price();
            break;
        case 'L':
            order_prods_from_order_desc();
            break;
        default:
            break;
    }
}

/*----------- FUNCAO QUE LE OS VALORES DE CADA LINHA --------------*/

 /*  A partir de uma linha, retira toda a informacao necessaria para a realizacao do comando atual*/
void read_values_from_line(char s[]){
    int i, j, k, v_atual = 0;     
    for(k = 0; k < 3; k++) /* faz-se reset do vetor valores onde vao ser armazenados os inteiros dados pelo comando*/
        valores[k] = 0;  
    if (s[0] == 'a'){     /* se a primeira letra da linha for a, quer dizer vai ser dada a descricao do produto, */
        for (i = 2; s[i] != ':'; i++)                                   /*que vai ser guardada em descricao_prod */
            descricao_prod[i - 2] = s[i];
        descricao_prod[i - 2] = '\0';
    }
    if (s[1] != '\n'){  /* se o comando for seguido de um '\n' quer dizer que nao vai ser preciso guardar valores, pq o comando n os da. */
        i = s[0] == 'a' ? i + 1 : 2;  /* se a primeira letra for a, comeca-se a ler os valores a seguir a descricao. */
        for (j = i; s[j] != '\n'; j++){                 /* Se nao, a partir do segundo elemento (depois do espaco). */
            if (s[j] == ':')     /* Quando o caracter e um ':', passa-se a ler o proximo valor.*/
                v_atual += 1;
            else
                valores[v_atual] = valores[v_atual] * 10 + (s[j] - '0');  /* vai-se guardando o valor em valores[v_atual]*/
        }
    }
}

/*---------------- MAIN ------------------*/

/* Le linha a linha, verifica se e altura de terminar o programa, e chama tambem outras funcoes */
int main(){
    char s[MAX_ORDER_PRODS], c; /* em s vai ser guardada a linha de comandos atual*/
    int i = 0;                          /* em descricao_prod vai ser usada caso o comando seja 'a'.*/
    while ((c = getchar()) != EOF && !(c == 'x' && i == 0)) { /*se c for x e for o inicio da linha, quer dizer que o comando atual e 'x'.*/
        s[i++] = c;
        if (c=='\n') { /* quando se chega ao fim da linha, faz-se reset da variavel i.*/
            i = 0;
            read_values_from_line(s); /* nesta funcao vao ser lidos os valores dados pela linha lida*/
            call_function(s[0]);     /* esta funcao vai chamar diferentes funcoes, de acordo com o comando*/
        }
    }
    return 0;
}
