#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Numero maximo de produtos diferentes */
#define MAX_PRODUTOS 10000
/* Numero maximo de encomendas */
#define MAX_ENCOMENDAS 5000
/* Peso maximo por encomenda */
#define MAX_PESO_ENCOMENDA 200
/* Numero maximo de caracteres da descricao de produtos */
#define MAX_CARACTERES_PRODUTO 63
/* Habilita alguns printf para fins de debugar */
#define DEBUG 0

/* Tipo Produto */
typedef struct produto{
    /* Identificador (um numero inteiro no intervalo [0, 9 999]) */
    int idp_prod; 
    /* Descricao (uma string nao vazia com um maximo de 63 caracteres) */
    char descricao[MAX_CARACTERES_PRODUTO];
    /* Preco (um numero inteiro maior que 0) */
    int preco;
    /* Peso (um numero inteiro maior que 0) */
    int peso; 
    /* Quantidade em estoque (um numero inteiro maior ou igual a 0) */
    int quantidade; 
}Produto;
    
Produto estoque[MAX_PRODUTOS]; /* estoque - Vetor de produtos */

/* Tipo Encomenda */
typedef struct encomenda{
    /* Identificador (um numero inteiro no intervalo [0, 499]) */
    int ide; 
    /* Custo (um numero inteiro maior que 0) */
    int custo;
    /* Peso (maximo 200 unidades de peso) */
    int peso_enco; 
    /* Quantidade de tipos de produtos (um numero inteiro no intervalo [0, 199]) */
    int qtd_prod;
    /* vetor de produtos (maximo 200 tipos de produtos) */
    Produto produto[MAX_PESO_ENCOMENDA];
}Encomenda;

Encomenda encomenda[MAX_ENCOMENDAS]; /* encomenda - Vetor de encomendas*/

int qpe = -1; /* Quantidade de tipos de produtos no estoque */
int qes = -1; /* Quantidade de encomendas no sistema */

char aL_aux[MAX_PRODUTOS][MAX_CARACTERES_PRODUTO] = {""}; /* Vetor auxiliar ao vetor aL na funcao mergesort */
int bL_aux[MAX_PRODUTOS]; /* Vetor auxiliar ao vetor bL na funcao mergesort */
int al_aux[MAX_PRODUTOS]; /* Vetor auxiliar ao vetor al na funcao mergesort */
int bl_aux[MAX_PRODUTOS]; /* Vetor auxiliar ao vetor bl na funcao mergesort */

/* Chama a funcao do respectivo comando recebido */
void seleciona_funcao(char);
/* Procura idp existente em encomendas */
int procura_idp_encomenda(int, int);
/* Ordenacao merge sort. */
void mergesort(char[][MAX_CARACTERES_PRODUTO], int[], int[], int, int, char);
/* merge_char - Interna ao merge sort */
void merge_char(char[][MAX_CARACTERES_PRODUTO], int[],int, int, int);
/* merge_int - Interna ao merge sort */
void merge_int(int[], int[] ,int, int, int);

/* a - Adiciona um novo produto ao sistema */
void a();
/* q - Adiciona stock a um produto existente no sistema */
void q();
/* N - Cria uma nova encomenda */
void N();
/* A - Adiciona um produto a uma encomenda */
void A();
/* A_ad_qtd - Auxiliar de A - Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
void A_ad_qtd(int, int, int, int);
/* A_ad_prod - Auxiliar de A - Adiciona o produto na encomenda e atualiza dados da encomenda */
void A_ad_prod(int, int, int);
/* r - Remove stock a um produto existente */
void r();
/* R - Remove um produto de uma encomenda */
void R();
/* R_move - Auxiliar a R - Move produtos na encomenda para esquerda de modo a nao deixar espaco vazio entre produtos */
void R_move(int, int);
/* C - Calcula o custo de uma encomenda */
void C();
/* p - Altera o preco de um produto existente no sistema */
void p();
/* p_altera_preco - Auxiliar a p - Altera o preco nas encomendas e atualiza custo */
void p_altera_preco(int, int, int);
/* E - Lista a descricao e a quantidade de um produto numa encomenda */
void E();
/* m - Lista o identificador da encomenda em que o produto dado ocorre mais vezes */
void m();
/* m_gera_vetores - Auxiliar de m - Gera dois vetores, um com as ide que contem o idp e outro com as quantidades */
int m_gera_vetores(int, int[], int[]);
/* m_proc_maior - Auxiliar de m - Procura o maior valor no vetor das quantidades */
int m_proc_maior(int, int[]);
/* l - Lista todos os produtos existentes no sistema por ordem crescente de preco. */
void l();
/* L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void L();


int main(){    
    char comando; /* Variavel para armazenar o Comando */

    /* Obtem comandos e chama a respectiva funcao */
    while((comando = getchar()) != 'x'){
        seleciona_funcao(comando);
    }

    return 0;
}

/* Chama a funcao do respectivo comando recebido */
void seleciona_funcao(char comando){

    switch (comando){
        case 'a':   /* a - adiciona um novo produto ao sistema */
            a(); break;   
        case 'q':   /* q - adiciona stock a um produto existente no sistema */
            q(); break;
        case 'N':   /* N - cria uma nova encomenda */
            N(); break;
        case 'A':   /* A - adiciona um produto a uma encomenda */
            A(); break;
        case 'r':   /* r - remove stock a um produto existente */
            r(); break;
        case 'R':   /* R - remove um produto de uma encomenda */
            R(); break;
        case 'C':   /* C - calcula o custo de uma encomenda */
            C(); break;
        case 'p':   /* p - altera o preco de um produto existente no sistema */
            p(); break;
        case 'E':   /* E - lista a descricao e a quantidade de um produto numa encomenda */
            E(); break;
        case 'm':   /* m - lista o identificador da encomenda em que o produto dado ocorre mais vezes */
            m(); break;
        case 'l':   /* l - lista todos os produtos existentes no sistema por ordem crescente de preco */
            l(); break;
        case 'L':   /* L - lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
            L(); break;
        case 'x':   /* x - termina o programa */
            return;
    }
}

/* Procura idp existente em encomendas */
int procura_idp_encomenda(int ide, int idp){
    int i;
    int qtd_prod = encomenda[ide].qtd_prod; /* Quantidade de tipos de produtos da encomenda ide */
    
    /* Procura no vetor produto[MAX_PESO_ENCOMENDA] da encomenda ide o idp_prod correspondente ao idp recebido como argumento */
    for(i = 0; i < qtd_prod; i++){
        if(idp == encomenda[ide].produto[i].idp_prod){
            return i; /* Retorna o indice do produto no vetor produto[MAX_PESO_ENCOMENDA] */
        }
    }
    return -1; /* Retorna -1 caso nao encontre o idp na encomenda ide */
}

/* Ordenacao merge sort. */
void mergesort(char aL[MAX_PRODUTOS][MAX_CARACTERES_PRODUTO], int al[MAX_PRODUTOS], int b[MAX_PRODUTOS], int left, int right, char type){
    int m = (right+left)/2;

    if (right <= left)
        return;

    mergesort(aL, al, b, left, m, type);
    mergesort(aL, al, b, m+1, right, type);

    /* merge_char - Ordena vetor bidimensional do tipo char */
    if(type == 'L'){
        merge_char(aL, b, left, m, right);
    }
    /* merge_int - Ordena vetor do tipo int */
    if(type == 'l'|| type == 'm'){
        merge_int(al, b, left, m, right);
    }
}

/* merge_char - Interna ao merge sort - Ordena vetor bidimensional do tipo char */
void merge_char(char aL[MAX_PRODUTOS][MAX_CARACTERES_PRODUTO], int b[MAX_PRODUTOS] ,int left, int m, int right){
    int i, j, k;

    for (i = m+1; i > left; i--){
        strcpy(aL_aux[i-1], aL[i-1]);
        bL_aux[i-1] = b[i-1];
    }

    for (j = m; j < right; j++){
        strcpy(aL_aux[right+m-j], aL[j+1]);
        bL_aux[right+m-j] = b[j+1];
    }

    for (k = left; k <= right; k++){
        if ( strcmp(aL_aux[j], aL_aux[i]) < 0){
            strcpy(aL[k], aL_aux[j]);
            b[k] = bL_aux[j--];
        }
        else{
            strcpy(aL[k],aL_aux[i]);
            b[k] = bL_aux[i++];
        }
    }
}

/* merge_int - Interna ao merge sort - Ordena vetor do tipo int */
void merge_int( int al[MAX_PRODUTOS], int b[MAX_PRODUTOS] ,int left, int m, int right){
    int i, j, k;

    for (i = m+1; i > left; i--){
        al_aux[i-1] = al[i-1];
        bl_aux[i-1] = b[i-1];
    }

    for (j = m; j < right; j++){
        al_aux[right+m-j] = al[j+1];
        bl_aux[right+m-j] = b[j+1];
    }

    for (k = left; k <= right; k++){
        if ((al_aux[j] < al_aux[i]) || i > m){
            al[k] = al_aux[j];
            b[k] = bl_aux[j--];
        }
        else{
            al[k] = al_aux[i];
            b[k] = bl_aux[i++];
        }
    }
}

/* a: Adiciona um novo produto ao sistema (estoque) */
void a(){ 
    
    ++qpe; /* Incrementa o qpe - Quantidade de tipos de produtos no estoque */

    /* Formato de entrada: a descricao:preco:peso:qtd */
    scanf(" %[^:]:%d:%d:%d", estoque[qpe].descricao, &estoque[qpe].preco, &estoque[qpe].peso, &estoque[qpe].quantidade);

    if(DEBUG)
        printf("a %s:%d:%d:%d##\n", estoque[qpe].descricao, estoque[qpe].preco, estoque[qpe].peso, estoque[qpe].quantidade);

    estoque[qpe].idp_prod = qpe;

    /* Formato de saida: Novo produto <idp>. onde <idp> e o identificador do produto criado. */
    printf("Novo produto %d.\n", qpe);
}

/* q: Adiciona stock a um produto existente no sistema (estoque) */
void q(){
    int idp, qtd;

    /* Formato de entrada: q idp:qtd */
    scanf("%d:%d", &idp, &qtd);

    if(DEBUG)
        printf("q %d:%d##\n", idp, qtd);

    /* Formato de sa?da: NADA (excepto erro) */
    if(idp > qpe){  /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    }
    else{
        estoque[idp].quantidade += qtd; /* Adiciona a quantidade qtd do produto idp */
    }
}

/* N: Cria uma nova encomenda */
void N(){

    ++qes; /* Incrementa o qes - Quantidade de encomendas no sistema (estoque) */
        
    /* Formato de entrada: N */
    /* Formato de sa?da: Nova encomenda <ide>. onde <ide> ? o identificador da encomenda criada */
    printf("Nova encomenda %d.\n", qes);

    /* Inicializa dados da encomenda */
    encomenda[qes].ide = qes;     /* Inicializa o ide */
    encomenda[qes].custo = 0;     /* Inicializa o custo */
    encomenda[qes].peso_enco = 0; /* Inicializa o peso */
    encomenda[qes].qtd_prod = 0;  /* Inicializa o quantidade de tipos de produtos */
}

/* A: Adiciona um produto a uma encomenda */
void A(){
    int ide, idp, qtd;
    int idp_exi_eco; /* Indice do produto existente na encomenda */

    /* Formato de entrada: A ide:idp:qtd */
    scanf("%d:%d:%d", &ide, &idp, &qtd); 

    if(DEBUG)
        printf("A %d:%d:%d##\n", ide, idp, qtd);

    /* procura_idp_encomenda(ide, idp); Retorna o id caso o produto idp exista na encomenda ide ou retorna -1 caso contrario  */
    idp_exi_eco = procura_idp_encomenda(ide, idp); 

    /* Formato de sa?da: NADA (excepto erro) */
    if(ide > qes){ /* qes - Quantidade de encomendas no sistema */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
    }
    else if(qtd > estoque[idp].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    }
    else if((estoque[idp].peso * qtd + encomenda[ide].peso_enco) > MAX_PESO_ENCOMENDA){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
    }
    /* Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
    else if(idp_exi_eco != -1){
        A_ad_qtd(ide, idp, idp_exi_eco, qtd);
    }
    /* Adiciona o produto na encomenda e atualiza dados da encomenda */
    else{
        A_ad_prod(ide, idp, qtd);
    }
}

/* A_ad_qtd - Auxiliar de A - Se o produto ja existir na encomenda, adiciona a nova quantidade a quantidade existente */
void A_ad_qtd(int ide, int idp, int idp_exi_eco, int qtd){
            
    encomenda[ide].produto[idp_exi_eco].quantidade += qtd; /* Adiciona quantidade do produto na encomenda */

    /* Atualiza dados da encomenda */
    encomenda[ide].custo += (estoque[idp].preco * qtd); /* Atualiza custo */
    encomenda[ide].peso_enco += (estoque[idp].peso * qtd); /* Atualiza peso */

    /* Atualiza quantidade do produto no estoque */
    estoque[idp].quantidade -= qtd;
}

/* A_ad_prod - Auxiliar de A - Adiciona o produto na encomenda e atualiza dados da encomenda */
void A_ad_prod(int ide, int idp, int qtd){
    int idp_eco; /* Indice do novo produto na encomenda */

    /* Atualiza dados da encomenda */
    encomenda[ide].custo += (estoque[idp].preco * qtd); /* Atualiza custo */
    encomenda[ide].peso_enco += (estoque[idp].peso * qtd); /* Atualiza peso */
    encomenda[ide].qtd_prod++; /* Atualiza qtd_prod */

    /* Adiciona produto no vetor produto[MAX_PESO_ENCOMENDA] */
    idp_eco = encomenda[ide].qtd_prod - 1; /* Indice do produto na encomenda */
    encomenda[ide].produto[idp_eco].idp_prod = idp; /* Inicializa idp_prod */
    encomenda[ide].produto[idp_eco].preco = estoque[idp].preco; /* Inicializa preco */
    encomenda[ide].produto[idp_eco].peso = estoque[idp].peso; /* Inicializa peso */
    encomenda[ide].produto[idp_eco].quantidade += qtd; /* Inicializa quantidade */
    strcpy(encomenda[ide].produto[idp_eco].descricao, estoque[idp].descricao); /* Inicializa descricao */

    /* Atualiza quantidade do produto no estoque */
    estoque[idp].quantidade -= qtd;
}

/* r - Remove stock a um produto existente */
void r(){
    int idp, qtd;

    /* Formato de entrada: r idp:qtd */
    scanf("%d:%d", &idp, &qtd); 

    if(DEBUG)
        printf("r %d:%d##\n", idp, qtd); 

    /* Formato de sa?da: NADA (excepto erro) */
    if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else if(estoque[idp].quantidade < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);    
    }
    else{ /* Atualiza quantidade do produto no estoque */
        estoque[idp].quantidade -= qtd;
    }
}

/* R - Remove um produto de uma encomenda */
void R(){
    int ide, idp, qtd;
    int idp_eco; /* Indice do produto na encomenda */

    /* Formato de entrada: R ide:idp */
    scanf("%d:%d", &ide, &idp); 

    if(DEBUG)
        printf("R %d:%d##\n", ide, idp); 

    /* procura_idp_encomenda(ide, idp); Retorna o id caso o produto idp exista na encomenda ide ou retorna -1 caso contrario  */
    idp_eco = procura_idp_encomenda(ide, idp);

    /* Formato de sa?da: NADA (excepto erro) */
    if(ide > qes){ /* qes - Quantidade de encomendas no sistema */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);    
    }
    else if(encomenda[ide].qtd_prod == 0){
        return;   /* A funcao nao faz nada caso n?o exista produtos na encomenda*/
    }
    else if(idp_eco == -1){
        return;   /* A funcao n?o faz nada caso n?o exista produto idp */
    } 
    else{
        /* Atualiza quantidade do produto no estoque */
        qtd = encomenda[ide].produto[idp_eco].quantidade; /* Obtem a quantidade de produtos idp na encomenda */
        estoque[idp].quantidade += qtd; 

        /* Atualiza custo e peso da encomenda */
        encomenda[ide].custo -= (estoque[idp].preco * qtd); /* Atualiza custo */
        encomenda[ide].peso_enco -= (estoque[idp].peso * qtd); /* Atualiza peso */

        /* Move produtos na encomenda para esquerda de modo a nao deixar espaco de memoria vazio entre produtos */
        R_move(ide, idp_eco);

        /* Atualiza quantidade de produtos da encomenda */
        encomenda[ide].qtd_prod--; /* Atualiza qtd_prod */
    }
    return;
}

/* R_move - Auxiliar a R - Move produtos na encomenda para esquerda de modo a nao deixar espaco vazio de memoria entre produtos */
void R_move(int ide, int idp_eco){
    int i, j;
    int qtd_prod = encomenda[ide].qtd_prod; /* Quantidade de tipos de produtos da encomenda ide */

    /* Percorre o vetor de produtos produto[MAX_PESO_ENCOMENDA] da encomenda ide */
    for(i = idp_eco; i < qtd_prod; i++){
        /* Move descricao */
        for(j = 0; j <= MAX_CARACTERES_PRODUTO; j++){                                    
            encomenda[ide].produto[i].descricao[j] = encomenda[ide].produto[i + 1].descricao[j];
        }
        encomenda[ide].produto[i].idp_prod = encomenda[ide].produto[i + 1].idp_prod;     /* Move idp_prod */
        encomenda[ide].produto[i].peso = encomenda[ide].produto[i + 1].peso;             /* Move peso */
        encomenda[ide].produto[i].preco = encomenda[ide].produto[i + 1].preco;           /* Move preco */
        encomenda[ide].produto[i].quantidade = encomenda[ide].produto[i + 1].quantidade; /* Move quantidade */
    }
}

/* C - Calcula o custo de uma encomenda */
void C(){
    int ide;

    /* Formato de entrada: C ide */
    scanf("%d", &ide);

    /* Formato de sa?da: Custo da encomenda <ide> <total>. onde <total> ? o valor total da encomenda <ide> */
    if(ide > qes){ /* qes - Quantidade de encomendas no sistema */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        printf("Custo da encomenda %d %d.\n", ide, encomenda[ide].custo);
    }
}

/* p - Altera o preco de um produto existente no sistema */
void p(){
    int idp, novo_preco, preco_atual;

    /* Formato de entrada: p idp:preco */
    scanf("%d:%d", &idp, &novo_preco); 

    if(DEBUG)
        printf("p %d:%d##\n", idp, novo_preco); 

    /* Formato de sa?da: NADA (excepto erro) */
    if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else{
        preco_atual = estoque[idp].preco; /* Obtem preco atual do produto idp */
        estoque[idp].preco = novo_preco;  /* Altera preco do produto idp no estoque */

        /* Altera o preco nas encomendas e atualiza custo */
        p_altera_preco(idp, novo_preco, preco_atual);
    }
}

/* p_altera_preco - Auxiliar a p - Altera o preco nas encomendas e atualiza custo */
void p_altera_preco(int idp, int novo_preco, int preco_atual){
    int i, j, qtd_prod, quantidade;

    /* Percorre todas encomendas existentes no sistema */
    for(i = 0; i <= qes; i++){ /* qes - Quantidade de encomendas no sistema */
        qtd_prod = encomenda[i].qtd_prod; /* Obtem a quantidade de produtos da encomenda[i] */
        /* Percorre todos os produtos da encomenda[i] */
        for(j = 0; j < qtd_prod; j++){
            /* Se o produto idp existir na encomenda[i] */
            if(idp == encomenda[i].produto[j].idp_prod){
                /* Atualiza o custo */
                quantidade = encomenda[i].produto[j].quantidade;                 /* Obtem a quantidade de produtos idp da encomenda[i] */
                encomenda[i].produto[j].preco = novo_preco;                      /* Atualiza o preco da encomenda[i] */
                encomenda[i].custo += (novo_preco - preco_atual) * quantidade;   /* Atualiza o custo da encomenda encomenda[i] */
            }
        }
    }
}

/* E - Lista a descricao e a quantidade de um produto numa encomenda */
void E(){
    int ide, idp, idp_eco;

    /* Formato de entrada: E ide:idp */
    scanf("%d:%d", &ide, &idp); 

    if(DEBUG)
        printf("E %d:%d##\n", ide, idp); 

    /* procura_idp_encomenda(ide, idp); Retorna o id caso o produto idp exista na encomenda ide ou retorna -1 caso contrario  */
    idp_eco = procura_idp_encomenda(ide, idp);

    /* Formato de sa?da: <desc> <qtd>. onde <desc> ? a descri??o do produto <idp> e <qtd> ? a quantidade desse produto na encomenda <ide> */
    if(ide > qes){ /* qes - Quantidade de encomendas no sistema */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
    }
    else if(encomenda[ide].qtd_prod == 0){ /* Quantidade de produtos na encomenda ide eh igual a zero */
        printf("%s %d.\n",estoque[idp].descricao, 0);
    }
    else if(idp_eco == -1){ /* Nao existe o produto idp na encomenda ide */
        printf("%s %d.\n",estoque[idp].descricao, 0);
    }
    else{
        printf("%s %d.\n",encomenda[ide].produto[idp_eco].descricao, encomenda[ide].produto[idp_eco].quantidade);
    }
    return;
}

/* m - Lista o identificador da encomenda em que o produto dado ocorre mais vezes. */
/* Se houver 2 ou mais encomendas nessa situacao, devera imprimir a encomenda de menor id. */
void m(){
    int idp, i, k, maior, vet_ide[MAX_ENCOMENDAS], vet_qtd[MAX_ENCOMENDAS];

    /* Formato de entrada: m idp */
    scanf("%d", &idp);

    /* Formato de sa?da:
        Maximo produto <idp> <ide> <qtd>. onde <ide> ? o n?mero da encomenda em que <idp> ocorre mais vezes,
        sendo essa quantidade <qtd>
        N?o dever? listar nada caso o produto <idp> n?o ocorra em nenhuma encomenda, ou caso n?o haja encomendas */
    if(idp > qpe){ /* qpe - Quantidade de tipos de produtos no estoque */
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    /* Nao lista nada caso n?o haja encomendas */
    else if(qes == -1){ /* qes - Quantidade de encomendas no sistema */
        return;
    }
    else{
        /* Gera dois vetores, um com as ide que contem o idp e outro com as quantidades dos produtos idp nessa encomenda ide */
        k = m_gera_vetores(idp, vet_ide, vet_qtd); /* k - Tamanho dos vetores gerados*/

        if(k == 0){ /* Nao devera listar nada caso o produto <idp> n?o ocorra em nenhuma encomenda */
            return;
        }
        /* Procura o maior valor no vetor das quantidades dos produtos */
        maior = m_proc_maior(k, vet_qtd);

        /* Ordena o vetor das quantidades dos prodtudos e em paralelo o vetor com as ide*/
        mergesort(aL_aux, vet_qtd, vet_ide, 0, k-1, 'm');
        
        /* Percorre o vetor das quantidades dos produtos */
        for(i = 0; i < k; i++){
            /* Se a quantidade corresponder ao maior valor */
            if(vet_qtd[i] == maior){
                /* Imprimi a ide que contem o maior valor de quantidade dos produtos */
                printf("Maximo produto %d %d %d.\n", idp, vet_ide[i], maior);
                break;
            }
        }
    }
}

/* m_gera_vetores - Gera dois vetores, um com as ide que contem o idp e outro com as quantidades dos produtos idp nessa encomenda ide */
int m_gera_vetores(int idp, int vet_ide[MAX_ENCOMENDAS], int vet_qtd[MAX_ENCOMENDAS]){
    int i, j, k = 0, qtd_prod;

    /* Percorre todas encomendas existentes no sistema */
    for(i = 0; i <= qes; i++){ /* qes - Quantidade de encomendas no sistema */
        qtd_prod = encomenda[i].qtd_prod; /* Obtem a quantidade de produtos da encomenda[i] */
        /* Percorre todos os produtos da encomenda[i] */
        for(j = 0; j < qtd_prod; j++){
            /* Se o produto idp existir na encomenda[i] */
            if(encomenda[i].produto[j].idp_prod == idp){
                /* Gera dois vetores, um com as ide que contem o idp e outro com as quantidades dos produtos idp nessa encomenda ide */
                vet_ide[k] = i;
                vet_qtd[k++] = encomenda[i].produto[j].quantidade;
            }
        }
    }
    return k; /* Retorna o tamanho dos vetores */
}

/* m_proc_maior - Auxiliar de m - Procura o maior valor no vetor das quantidades dos produtos */
int m_proc_maior(int k, int vet_qtd[MAX_ENCOMENDAS]){
    int i, maior;

    maior = vet_qtd[0];
    /* Percorre o vetor das quantidades dos produtosa */
    for(i = 0; i < k; i++){
        if(vet_qtd[i] > maior){ /* Se o valor atual for maior que o valor contido na variavel maior */
            maior = vet_qtd[i]; /* Atualiza a variavel maior */
        }
    }
    return maior; /* Retorna o maior valor contido no vetor das quantidades dos produtos */
}

/* l - Lista todos os produtos existentes no sistema por ordem crescente de preco. */
/* Se houver 2 ou mais produtos com o mesmo preco, devera imprimir esses por ordem crescente de id de produto */
void l(){
    int i, id, vet_preco[MAX_PRODUTOS] = {0}, vet_id[MAX_PRODUTOS] = {0};

    /* Formato de entrada: l */

    /* Cria dois vetores. Um com os precos dos produtos do estoque e outro com os indices desses precos no estoque */
    /* Percorre todos os produtos do estoque */
    for(i = 0; i <= qpe; i++){ /* qpe - Quantidade de tipos de produtos no estoque */
        /* Gera dois vetores, um com os precos dos produtos do estoque e outro com os indices desses precos no estoque */
        vet_preco[i] = estoque[i].preco;
        vet_id[i] = i;
    }
    
    /* Ordena o vetor dos precos dos produtos no estoque e em paralelo o vetor com os indices desses precos no estoque */
    mergesort(aL_aux, vet_preco, vet_id, 0, qpe, 'l');

    /* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem crescente de pre?o
    Produtos
    * <desc1> <preco1> <qtd1 em stock>
    * <desc2> <preco2> <qtd2 em stock>
    ...
    * <descn> <precon> <qtdn em stock> */
    printf("Produtos\n");

    /* Percorre o vetor dos indices, que agora esta ordenado em funcao dos precos dos produtos no estoque */
    for(i = 0; i <= qpe; i++){ /* qpe - Quantidade de tipos de produtos no estoque */
        id = vet_id[i]; /* Obtem os indices do estoque, que agora esta ordenado em funcao dos precos dos produtos no estoque */
        printf("* %s %d %d\n", estoque[id].descricao, estoque[id].preco, estoque[id].quantidade);
    }
}

/* L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao */
void L(){
    int i, id, ide, qtd_prod, vet_id[MAX_PRODUTOS] = {0};
    char vet_cc[MAX_PRODUTOS][MAX_CARACTERES_PRODUTO] = {""};

    /* Formato de entrada: L <ide> */
    scanf("%d", &ide);

    qtd_prod = encomenda[ide].qtd_prod; /* Obtem a quantidade de produtos na encomenda */
    /* Formato de sa?da: Um bloco no formato abaixo, e em que os produtos s?o listados por ordem alfab?tica de descri??o
    Encomenda <ide>
    * <desc1> <preco1> <qtd1 na ide>
    * <desc2> <preco2> <qtd2 na ide>
    ...
    * <descn> <precon> <qtdn na ide> */

    if(ide > qes){ /* qes - Quantidade de encomendas no sistema */
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else{
        /* Cria dois vetores. Um com a descricao dos produtos da encomenda ide e outro com idp dos produtos */
        /* Percorre todos os produtos existentes na encomenda ide */
        for(i = 0; i < qtd_prod; i++){
            /* Cria dois vetores. Um com a descricao dos produtos da encomenda ide e outro com idp dos produtos */
            strcpy(vet_cc[i], encomenda[ide].produto[i].descricao);
            vet_id[i] = i;
        }

        /* Ordena o vetor com a descricao dos produtos da encomenda ide e em paralelo o vetor com idp dos produtos */
        mergesort(vet_cc, al_aux, vet_id, 0, qtd_prod - 1, 'L');

        printf("Encomenda %d\n", ide);

        /* Percorre o vetor com idp dos produtos, que agora esta ordenado em funcao das descricoes dos produtos da encomenda ide */
        for(i = 0; i < qtd_prod; i++){
            id = vet_id[i]; /* Obtem o idp dos produtos, que agora esta ordenado em funcao das descricoes dos produtos da encomenda ide */
            printf("* %s %d ", encomenda[ide].produto[id].descricao, encomenda[ide].produto[id].preco);
            printf("%d\n", encomenda[ide].produto[id].quantidade);
        }
    }
}







/*
 8.2 Abstract in-place merge 
Item aux[maxN];
void merge(Item a[], int left, int m, int right){
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++)
        if (less(aux[j], aux[i]))
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
}


 8.3 Top-Down Mergesort 
void mergesort(Item a[], int left, int right){
    int m = (right + left) / 2;
    if (right <= left) return;
    mergesort(a, left, m);
    mergesort(a, m + 1, right);
    merge(a, left, m, right);
}
*/