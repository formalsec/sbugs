#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>


/*------------*/
/* CONSTANTES */
/*------------*/

/* Maximo valor de caracteres da descricao de um produto*/
#define MAX_DESCRICAO 63
/* Maximo valor de encomedas no total*/
#define MAX_ENCOMENDAS 500
/* Maximo valor de produtos por encomenda*/
#define MAX_PRODUTOS_ENCOMENDA 200
/*Maximo valor de produtos no sistema */
#define MAX_PRODUTOS 10000
/* Maximo valor de peso numa encomenda */
#define MAX_PESO 200
#define chave(A) (A)
#define exch_p(A, B) { produto t = A; A = B; B = t; } 



/*------------*/
/* ESTRUTURAS */
/*------------*/

/* Criacao da estrutura produto, caracterizada por um identificador, uma descricao, preco, peso e quantidade no sistema */
typedef struct produto{
    int identificador;
    char descricao[MAX_DESCRICAO];
    int preco;
    int peso;
    int quantidade;
}produto;


/* Criacao da estrutura encomenda, caracterizada por um identificador, o total de diferentes produtos que possui, o peso (que corresponte a soma do peso de cada produto), e um vetor com os produtos*/
typedef struct encomenda{
    int total; /*total de produtos diferentes*/
    int identificador_e;
    int peso;
    produto produtos_e[MAX_PRODUTOS_ENCOMENDA];
}encomenda;



/*------------------- */
/* VARIAVEIS GLOBAIS */
/*------------------ */

/* Vetor lista_p e um vetor que possui todos os produtos do sistema */
produto lista_p[MAX_PRODUTOS];
/* Vetor lista_e corresponde a um vetor com todas as encomendas*/
encomenda lista_e[MAX_ENCOMENDAS];
/* valor correspondente ao total de produtos do sistema*/
int tp = 0; 
/* valore correspondente total de encomendas*/
int te = 0; 



/*-------------------*/
/*      FUNCOES      */
/*-------------------*/

/* Imprime os produtos que existem no sistema */
void imprimir_produtos(){
    int i;
    
    printf("Produtos\n");
    for (i=0; i<tp; i++){
        printf("* %s %d %d\n", lista_p[i].descricao, lista_p[i].preco, lista_p[i].quantidade);
    }
    
}


/* Cria uma encomenda, inicializando os parametros da encomenda a zero, exceto o identificador que e atribuido de acordo com 
o numero de encomendas ja existentes. Adiciona a encomenda a lista_e, vetor com todas as encomendas e incrementa o numero 
total de encoemendas existentes */
void cria_encomenda(){
    encomenda b;
    b.identificador_e = te;
    b.peso = 0;
    b.total = 0;
    lista_e[te] = b;
    te += 1;

    printf("Nova encomenda %d.\n", b.identificador_e);
}


/*Adiciona um novo produto ao sistema*/
void cria_produto(){
    /* a e o produto que vamos criar*/
    produto a;

    /*saltar ? frente o espa?o*/
    getchar();

    /*inicializa os parametros descricao, preco, peso e quantidade do produto *******
    de acordo com o input*/
    scanf("%[^:]:%d:%d:%d", a.descricao, &a.preco, &a.peso, &a.quantidade);
    /* o identificador e atribuido de acordo com o numero de produtos 
    existentes no sistema*/
    a.identificador = tp;
    /* adiciona o produto ao vetor de produtos no sistema*/
    lista_p[tp] = a;

    /*incrementa o numero de produtos no sistema*/
    tp += 1;

    printf("Novo produto %d.\n", a.identificador);
}


/*Adiciona um produto a uma encomenda*/
void adiciona_produto_encomenda(){
    /* ide e o identificador da encomenda, 
    idp o identificador do produto, 
    qtd a quantidade de produto que se vai adicionar a encomenda.
    max corresponde ao valor total de produtos que existem na encomenda ide*/
    int i, ide, idp, qtd, max;
    produto b;

    scanf("%d:%d:%d", &ide, &idp, &qtd);

    max = lista_e[ide].total;

    /*No caso de nao existir nenhuma encomenda criada com esse identificador*/
    if (ide >= te){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return;
    }

    /* No caso de nao existir nenhum produto criado com esse identificador*/
    else if (idp >= tp){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return;
    } 

    /* No caso de nao existir stock suficiente desse produto para satisfazer a encomenda.*/
    else if (lista_p[idp].quantidade < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }

    /* No caso de a adicao desse produto exceder o peso maximo permitido por encomenda*/
    else if (lista_e[ide].peso + (lista_p[idp].peso*qtd) > MAX_PESO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    else{
        /*Atualizamos o peso da encomenda de acordo com a quantidade de produto que vai ser adicionado*/
        lista_e[ide].peso += (lista_p[idp].peso*qtd);
        
        /*Verificamos se o produto j? se encontra na encomenda*/
        for (i=0; i<max; i++){
            /*Como o produto se encontra na encomenda, basta aumentar a quantidade deste na encomenda e diminuir no sistema*/
            if (lista_e[ide].produtos_e[i].identificador == idp){
                lista_e[ide].produtos_e[i].quantidade += qtd;
                lista_p[idp].quantidade -= qtd;
                return;
            }
        }

        /* Se chegou aqui, o produto nao se encontra na encomenda pelo que teremos de o adicionar*/

        /* copiar produto do vetor de produto do sistema*/
        b.identificador = lista_p[idp].identificador;
        for (i=0; i<MAX_DESCRICAO; i++){
            b.descricao[i]=lista_p[idp].descricao[i];
        }
        b.peso = lista_p[idp].peso;
        b.preco = lista_p[idp].preco;
        b.quantidade = qtd;

        /*adicionar novo produto ? encomenda*/
        lista_e[ide].produtos_e[max] = b;

        /*aumentamos o valor total de produtos na encomenda*/
        lista_e[ide].total += 1;

        /*diminuimos a quantidade desse produto no sistema*/
        lista_p[idp].quantidade -= qtd;
    }

    return;
}



/* Lista a descricao e a quantidade de um produto numa encomenda*/
void retorna_produto_encomenda(){
    /* ide e o indentificador da encomenda, 
    idp o identificador do produto*/
    int ide, idp, i;
    
    scanf("%d:%d", &ide, &idp);


    /*no caso de nao existir nenhuma encomenda criada com esse identificador*/
    if (ide >= te){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    /* no caso de nao existir nenhum produto criado com esse identificador*/
    else if (idp >= tp){
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    
    else{
        /*procurar o produto na lista de produtos da encomenda*/
        for (i = 0; i < lista_e[ide].total; i++){
            /* se encontro o produto, lista a descricao e a quantidade na encomenda*/
            if (lista_e[ide].produtos_e[i].identificador == idp){
                printf("%s %d.\n", lista_e[ide].produtos_e[i].descricao, lista_e[ide].produtos_e[i].quantidade);
                return;
            }
        }

        /*caso o produto nao se encontre na encomenda, a sua quantidade e zero*/
        printf("%s 0.\n", lista_p[idp].descricao);
    }
    
}


/*adiciona stock a um produto existente no sistema*/
void adiciona_stock(){
    /* idp e o identificador do produto, 
    qtd e a quantidade a que vamos adicionar ao produto*/
    int idp, qtd;

    scanf("%d:%d", &idp, &qtd);

    /*no caso se nao existir nenhum produto criado com esse identificador*/
    if (idp >= tp){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }

    else{
        lista_p[idp].quantidade += qtd; 
    }
}


/*remove stock a um produto existente*/
void remove_stock(){
    /* idp e o identificador do produto, 
    qtd e o valor a que vamos remover da quantidade do produto no sitema, 
    valor e a quantidade do produto no sistema*/
    int idp, qtd, valor;

    scanf("%d:%d", &idp, &qtd);

    /* no caso de nao existir nenhum produto com esse identificador*/
    if (idp >= tp){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
        return;
    }

    else{

        /*no caso de a quantidade em stock apos a remocao ser negativa*/
        valor = lista_p[idp].quantidade;
        if ((valor -= qtd)<0){
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }

        else{
            /*retiramos a quantidade ao sotck*/
            lista_p[idp].quantidade -= qtd;
        }
                
            
        }
}


/*altera o preco de um produto existente no programa*/
void altera_preco(){
    /* idp e o identificador do produto, 
    preco e o novo valor do preco do produto*/
    int i, j, idp, preco;

    scanf("%d:%d", &idp, &preco);

    /* caso nao existe nenhum produto com esse identificador*/
    if (idp >= tp){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }

    else{
        /* vamos alterar o preco na lista de produtos do sistema*/
        for (i = 0; i < tp; i++){
            /*encontramos o produto*/
            if (lista_p[i].identificador == idp){
                lista_p[i].preco = preco;
                break;
            }
        }

        /* vamos alterar o preco tamb?m nas encomendas em que o produto aparece*/
        /* percorremos todas as encomendas*/
        for (i = 0; i < te; i++)
            /* percorremos todos os produtos na encomenda*/
            for (j = 0; j < lista_e[i].total; j++){
                /*encontramos o produto na encomenda*/
                if (lista_e[i].produtos_e[j].identificador == idp){
                    lista_e[i].produtos_e[j].preco = preco;
                    break;
                }
            }
    }
}


/*calcula o custo de uma encomenda*/
void calcula_custo (){
    /* ide e o identificador da encomenda, 
    total e o custo da encomenda*/
    int  j, total = 0, ide;

    scanf("%d", &ide);

    /* no caso de nao existir nenhuma encomenda com esse identificador*/
    if (ide >= te){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }

    else
    {
        /*calculamos o preco de cada produto tendo em conta a quantidade na encomenda e adicionamos ao total*/
        for (j = 0; j< lista_e[ide].total; j++){
            total += (lista_e[ide].produtos_e[j].quantidade * lista_e[ide].produtos_e[j].preco);
        }

        printf("Custo da encomenda %d %d.\n", ide, total);
    }
}


/*lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void maximo_produto(){
    /* idp e o identificador do produto, 
    ide e o identificador da encomenda onde ocorreu mais vezes, 
    max e o valor da quantidade do produto na encomenda em que correu mais vezes*/
    int idp, i, j, max = 0, ide = 0;

    scanf("%d", &idp);

    /*caso nao exista nenhum produto com esse identificador*/
    if (idp >= tp){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }

    /*caso n?o houver encomendas*/
    else if( te == 0){
    }

    else{

        /* Vamos percorrer a lista de encomendas e ver se tem o produto idp. Guardamos o identificador
         da encomenda com maior quantidade do produto numa variavel 'ide' */

        for (i = 0; i< te; i++){
            for (j = 0; j < lista_e[i].total; j++){
                /* encontramos o produto na encomenda */
                if (lista_e[i].produtos_e[j].identificador == idp){
                    /*se a quantidade for igual ao max, fixamos a encomenda cujo identificador e menor*/
                    if (lista_e[i].produtos_e[j].quantidade == max){
                        if (i < ide){
                            ide = i;
                            break;
                        }
                    }
                    /* se a quantidade for superior ao max, fixamos essa encomenda*/
                    else if (lista_e[i].produtos_e[j].quantidade > max){
                        max = lista_e[i].produtos_e[j].quantidade;
                        ide = i;
                        break;
                    }

                    else{
                        break;
                    }
                }
            }
        }

        /* se o max for diferente de 0, ent?o o produto foi encontrado pelo menos numa encomenda*/
        if (max != 0){
            printf ("Maximo produto %d %d %d.\n", idp, ide, max);
        }
    }
}


/*remove stock a um produto existente*/
void remove_produto_encomenda(){
    /* idp e o identificador do produto, ide e o identificador da encomenda*/
    /* pos refere-se a posicao de um produto. inicia-se a -1 porque o primeiro produto tem a pos 0*/
    int i, j, idp, ide, pos = -1, u;

    scanf("%d:%d", &ide, &idp);

    /* no caso de nao existir nenhuma encomenda com esse identificador*/
    if (ide >= te){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }

    /* no caso de nao existir nenhum produto com esse identificador*/
    else if (idp >= tp){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }

    else{

        /*percorremos a lista dos produtos na encomenda*/
        for (i = 0; i< lista_e[ide].total; i++)
            /*encontramos o produto na encomenda */
            if (lista_e[ide].produtos_e[i].identificador == idp){
                /*guardamos o valor da sua posicao, ou seja, pos refere se a posicao do valor que queremos remover*/
                pos = i;
            }

        /*se o produto nao se encontra na encomenda*/
        if (pos == -1){
            return;
        }

        /*o produto encontra se na encomenda*/
        /*o valor da quantidade do produto no sistema aumenta*/
        lista_p[idp].quantidade += lista_e[ide].produtos_e[pos].quantidade;
        /*o valor do peso da encomenda diminui*/
        lista_e[ide].peso -= (lista_e[ide].produtos_e[pos].peso * lista_e[ide].produtos_e[pos].quantidade);
        
        /*vamos colocar tudo a zeros o produto que se encontra na posicao pos*/
        lista_e[ide].produtos_e[pos].identificador = 0;
        lista_e[ide].produtos_e[pos].quantidade = 0;
        lista_e[ide].produtos_e[pos].preco = 0;
        lista_e[ide].produtos_e[pos].peso = 0;
        /*alteramos tambem a descricao*/
        for (j = 0; j < MAX_DESCRICAO; j++){
            lista_e[ide].produtos_e[pos].descricao[j] = 0;
        }

        u = (lista_e[ide].total-1);
        /*trocamos o elemento na posicao pos com o ultimo elemento*/
        exch_p(lista_e[ide].produtos_e[pos], lista_e[ide].produtos_e[u]);

        /* diminuimos a quantidade total de produtos na encomenda ide*/
        lista_e[ide].total -= 1;
    }
}

/* vai escolher como pivot o elemento com index maior, ordena a direita do pivot os elementos com preco menor,
e a esquerda os elementos com preco maior*/
int particao_preco(produto b[], int l, int r) {
    /* i vai ser o menor index*/
    int i = (l-1);
    int j;
    /*produtos v vai ser o pivot*/
    produto v = b[r];

    for (j = l; j <= (r -1); j++){
        /* se o preco for menor, troca*/
        if (b[j].preco < v.preco){
            i++;
            if (i != j)
                exch_p(b[i], b[j]);
        }
         /* se o preco for igual, apenas troca se o identificador do pivot for maior do que a do produto*/
        else if(b[j].preco == v.preco){
            if (b[j].identificador < v.identificador){
                i++;
                if (i != j)
                    exch_p(b[i], b[j]);
            }
        }
    }
    /* colocamos o pivot no "centro", ou seja, a direita dos produtos com preco menor e a esquerda dos produtos com preco maior*/
    exch_p(b[i + 1], b[r]);
    return (i+1);
}

/*ordenar os produtos de acordo com o preco, usando o alrogitmo quicksort*/
void quicksort_preco(produto b[], int l, int r){
    /* l e o index iniciante*/
    /* r e o index final*/
    /* b[] e o vetor de produtos que vamos ordenar*/
    int i;
    if (l < r){
        /*vamos escolher o index pivot e dividir os produtos em duas listas*/
        i = particao_preco(b, l, r);
        /*vamos ordenar os produtos entre o index iniciante pivot e o index pivot*/
        quicksort_preco(b, l, i-1);
        /*vamos ordenar os produtos entre o index pivot e o index iniciante*/
        quicksort_preco(b, i+1, r);
    }
}

/*lista todos os produtos existentes no sistema por ordem crescente de preco*/
void ordenar_produtos_preco(){
    /* contadores*/
    int i=0;
    /* b vai ser o vetor copia do vetor de */
    produto b[MAX_PRODUTOS];

    /*copiar o vetor dos produtos no sistema*/
    memcpy(b, lista_p, sizeof(lista_p));

    /*ordenar pelo preco usando o alrogitmo quicksort*/
    quicksort_preco(b, 0, tp - 1);
    
    printf("Produtos\n");
    for (i = 0; i<tp; i++){
        printf("* %s %d %d\n", b[i].descricao, b[i].preco, b[i].quantidade);
    }
}


/*por cada produto na encomenda, imprime a respetica descricao, preco e quantidade do produto na encomenda*/
void imprimir_encomenda(encomenda b){
    int i;

    printf("Encomenda %d\n", b.identificador_e);

    for (i= 0; i < b.total; i++){
        printf("* %s %d %d\n", b.produtos_e[i].descricao, b.produtos_e[i].preco, b.produtos_e[i].quantidade);
    }
    
}


/* funcao auxiliar que lista os produtos da encomenda com identificador ide*/
void comando_K(){
    /* ide e o identificador da encomenda*/
    int ide, i;

    scanf("%d", &ide);

    printf("Encomenda %d\n", ide);

    for (i= 0; i < lista_e[ide].total; i++){
        printf("* %s:%d:%d\n", lista_e[ide].produtos_e[i].descricao, lista_e[ide].produtos_e[i].preco, lista_e[ide].produtos_e[i].quantidade);
        }
}


/* vai escolher como pivot o elemento com index maior, ordena a direita do pivot os elementos
cuja descricao e alfabeticamente menor, e a esquerda os elementos cuja descricao e alfabeticamente maior*/
int particao_descricao(produto b[], int l, int r) {
    /* i e o maior index*/
    int i = (l-1);
    int j;
    /*produtos v vai ser o pivot*/
    produto v = b[r];

    for (j = l; j <= (r -1); j++){
        /* caso a descricao seja alfabeticamente menor do que a do pivot, troca*/
        if (strcmp(b[j].descricao, v.descricao) < 0){
            i++;
            if (i != j)
                exch_p(b[i], b[j]);
        }
        /* caso o primeiro caracter seja alfabeticamente igual, apenas troca se o
        segundo caracter for menor do que o segundo a do pivot, troca*/
        else if (strcmp(b[j].descricao, v.descricao) == 0){
            if (b[j].identificador < v.identificador){
                i++;
                if (i != j)
                    exch_p(b[i], b[j]);
            }
        }
    }
    
    /* colocamos o pivot no "centro", ou seja, a direita dos produtos cuja descricao
    e alfabeticamente menor e a esquerda dos produtos cuja descricao e alfabeticamente
    maior*/
    exch_p(b[i + 1], b[r]);
    return (i+1);
}

/*ordenar os produtos de acordo com a sua descricao, usando o alrogitmo quicksort*/
void quicksort_descricao(produto b[], int l, int r){
    /* l e o index iniciante*/
    /* r e o index final*/
    /* b[] e o vetor de produtos que vamos ordenar*/
    int i;
    if (l < r){
        /*vamos escolher o index pivot e dividir os produtos em duas listas */
        i = particao_descricao(b, l, r);
        /*vamos ordenar os produtos entre o index iniciante pivot e o index pivot*/
        quicksort_descricao(b, l, i-1);
        /*vamos ordenar os produtos entre o index pivot e o index iniciante*/
        quicksort_descricao(b, i+1, r);
    }
}


/*lista todos os produtos existentes no sistema por ordem alfabetica da sua descricao*/
void ordenar_produtos_descricao (){
    /*contadores*/
    int i=0, ide;
    /* a vai ser o vetor copia do vetor de produtos na encomenda*/
    produto a[MAX_PRODUTOS];

    scanf("%d", &ide);

    /*verificar se a encomenda existe*/
    if (ide >= te){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }

    else{
        /*copiar o vetor dos produtos na encomenda*/
        memcpy(a, lista_e[ide].produtos_e, sizeof(lista_e[ide].produtos_e));

        /*ordenar os produtos da encomenda com o algoritmo quicksort */
        quicksort_descricao(a, 0, lista_e[ide].total - 1);

        /*imprimir encomenda*/

        printf("Encomenda %d\n", ide);
        
        for (i= 0; i < lista_e[ide].total; i++){
            printf("* %s %d %d\n", a[i].descricao, a[i].preco, a[i].quantidade);
        }
    }
}


/* Funcao principal.
Recebe um comando que vai ser um caracter, e de acordo com o comando, vai executar funcoes diferentes*/
int main(){
    char letra;
    
    while (scanf("%c", &letra) != EOF){
        switch(letra){
            case 'a':
                 cria_produto();
                 break;
            
            case 'K':
                comando_K();
                break;

            case 'k':
                imprimir_produtos();
                break;

            case 'l':
                ordenar_produtos_preco();
                break;
            
            case 'L':
                ordenar_produtos_descricao();
                break;

            case 'N':
                cria_encomenda();
                break;
            
            case 'A':
                adiciona_produto_encomenda();
                break;
            
            case 'E':
                retorna_produto_encomenda();
                break;

            case 'q':
                adiciona_stock();
                break;
            
            case 'r':
                remove_stock();
                break;
            
            case 'R':
                remove_produto_encomenda();
                break;
            
            case 'p':
                altera_preco();
                break;
            
            case 'C':
                calcula_custo();
                break;
            
            case 'm':
                maximo_produto();
                break;
            
            case 'x':
                return 0;
            
            default:
                break;

        }
    }

    return 0;

}
