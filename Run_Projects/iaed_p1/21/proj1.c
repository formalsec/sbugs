#include <stdio.h>
#include <stdlib.h>

/* DEFINICAO DE CONSTANTES, TIPOS E OPERADORES: */

#define MAXPRODUTOS 10000       /* Maximo de produtos que podem ser introduzidos no sistema. */ 
#define MAXENCOMENDAS 500       /* Maximo de encomendas. */
#define MAXPESO 200             /* Peso maximo por encomenda. */
#define MAXDESC 64              /* Maximo de caracteres admitidos na descricao de um produto. */

/* VARIAVEIS GLOBAIS: */

int idp_atual = -1;                 /* ID do ultimo produto introduzido, igual ao nr total de produtos menos um. */
int ide_atual = -1;                 /* ID da ultima encomenda introduzida, igual ao nr total de encomendas menos um.*/
int i, j, k;                        /* Contadores de ciclos. */

struct produto {                
    int idp;                        /* Identificador do produto. Inicializado a -1, significa que o produto nao foi introduzido no sistema.  */
    char desc[MAXDESC];             /* Descricao do produto, vetor de dimensao igual ao nr de caracteres admitidos mais um, para o \0. */
    int preco;                      /* Preco do produto. */
    int peso;                       /* Peso do produto. */
    int qtd;                        /* Quantidade(stock) do produto. */
};

struct produto produtos[MAXPRODUTOS];               /* Vetor para os produtos a serem introduzidos no sistema. */

struct produto produtos_enc[MAXPRODUTOS];           /* Vetor para os produtos adicionados a cada encomenda. */

struct encomenda {
    int ide;                                        /* Identificador da encomenda. */
    struct produto produtos_enc[MAXPRODUTOS];       
    int peso;                                       /* Peso total da encomenda. Soma dos pesos dos produtos existentes na mesma. */
};

struct encomenda encomendas[MAXENCOMENDAS];         /* Vetor para as encomendas a serem criadas. */


/* FUNCOES: */

int funcaoloop();                   

/* Comando a - Adiciona novo produto ao sistema. Formato de entrada > a descricao:preco:peso:qtd */
int comando_a() {           

    if (idp_atual < MAXPRODUTOS - 1) {              /* Se o maximo de produtos ainda nao tiver sido atingido, permite que se introduza o novo. */      

        char desc[MAXDESC];                         /* Inicializa vetor para a descricao introduzida. */
        int c, i;
        int preco, peso, qtd;                       /* Inicializacao de vars para guardar o preco, o peso e a quantidade introduzidos. */
        idp_atual ++;                               /* Incrementa o indice do ultimo produto introduzido, que corresponde ao atual. */

        /* Leitura do input descricao para o vetor desc[], caracter a caracter: */
        c = getchar();                              
        for (i = 0; i < MAXDESC-1 && c != ':'; i++)    {  
            desc[i] = c;
            c = getchar();
        }
        desc[i+1] = '\0';                           /* Adiciona o caracter \0 ao vetor desc[], que indica o final da string. */

        scanf("%d:%d:%d", &preco, &peso, &qtd);    /* Leitura do resto do input, guardando os valores nas respetivas variaveis. */

        produtos[idp_atual].idp = idp_atual;        /* O indice do produto no vetor produtos[] e igual ao seu ID. Ja nao e -1, o que significa que o produto existe no sistema. */
        
        /* Vetor local desc[] e copiado para o vetor do tipo produto na posicao ID: */
        for (i = 0; i < MAXDESC; i++)
            produtos[idp_atual].desc[i] = desc[i];            
        
        /* Variaveis locais preco, peso e qtd sao da mesma forma copiadas para as variaveis do tipo produto na posicao ID: */
        produtos[idp_atual].preco = preco;
        produtos[idp_atual].peso = peso;
        produtos[idp_atual].qtd = qtd;

        printf("Novo produto %d", idp_atual);     /* Imprime a mensagem de novo produto seguida do ID atribuido ao mesmo. */      
    }
    
    return funcaoloop();      
}


/* Comando q - Adiciona stock a um produto existente no sistema. Formato de entrada > q idp:qtd */
int comando_q() {                 

    int idp, qtd;                   /* Inicializacao de vars para guardar o ID e a quantidade do produto introduzidos. */
    scanf("%d:%d", &idp, &qtd);     /* Leitura do resto do input, guardando os valores nas respetivas vars. */

    if (idp > idp_atual)            /* Se o ID introduzido for superior ao do ultimo produto, significa que este nao esta introduzido no sistema. Imprime msg de erro. */
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.", idp);
    else
        produtos[idp].qtd += qtd;   /* Caso o produto ja exista no sistema, adiciona a quantidade introduzida ao seu stock atual. */

    return funcaoloop();
}


/* Comando N - Cria uma nova encomenda. */
int comando_N() {              
    
    ide_atual ++;                               /* Incrementa o indice da ultima encomenda introduzida, que corresponde a atual. */
    encomendas[ide_atual].ide = ide_atual;      /* O indice da encomenda no vetor encomendas[] e igual ao seu ID. Ja nao e -1, o que significa que a encomenda existe no sistema. */
    
    printf("Nova encomenda %d",ide_atual);    /* Imprime a mensagem de nova encomenda seguida do ID atribuido a mesma. */
    
    return funcaoloop();
}


/* Comando A - Adiciona um produto a uma encomenda. Se ja existir adiciona a quantidade. Formato de entrada > A ide:idp:qtd */
int comando_A() {                

    int ide, idp, qtd;                      /* Inicializacao de vars para guardar os ID's da encomenda e do produto, e a quantidade de produto a adicionar a encomenda. */
    int i;
    scanf("%d:%d:%d", &ide, &idp, &qtd);    /* Leitura do resto do input, guardando os valores nas respetivas vars. */

    if (ide > ide_atual)                    /* Se o ID de encomenda introduzido for superior ao da ultima encomenda, significa que esta nao foi criada. Imprime msg de erro. */
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.", idp, ide);
    else if (idp > idp_atual)               /* Se o ID de produto introduzido for superior ao do ultimo produto, significa que este nao esta introduzido no sistema. Imprime msg de erro. */
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.", idp, ide);
    else if (qtd > produtos[idp].qtd)       /* Se a quantidade introduzida for superior ao stock do produto no sistema, nao e possivel adiciona-la a encomenda. Imprime msg de erro. */  
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.", idp, ide);
    
    /* Se o peso da encomenda apos se adicionar a qtd de produto introd exceder o max por encomenda, nao e adicionado. Imprime msg de erro.*/
    else if (encomendas[ide].peso + produtos[idp].peso*qtd > MAXPESO)
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.", idp, ide);
    
    /* Se o produto ja existir na encomenda, soma a qtd de produto introduzida ? do mesmo na encomenda 
    e subtrai a qtd de produto introduzida do stock do produto no sistema: */
    else if (encomendas[ide].produtos_enc[idp].idp != -1) {             
        encomendas[ide].produtos_enc[idp].qtd += qtd;               
    }

    /* Se o produto ainda nao existir na encomenda, copia os valores dos parametros do produto introduzido, e a quantidade introduzida 
    para os respetivos params no mesmo produto, mas desta vez no vetor dos produtos da encomenda ide: */
    else {                                                              
        encomendas[ide].produtos_enc[idp].idp = produtos[idp].idp;
        for (i = 0; i < MAXDESC; i++)
            encomendas[ide].produtos_enc[idp].desc[i] = produtos[idp].desc[i];    
        encomendas[ide].produtos_enc[idp].preco = produtos[idp].preco;  
        encomendas[ide].produtos_enc[idp].peso = produtos[idp].preco;   
        encomendas[ide].produtos_enc[idp].qtd = qtd;
        produtos[idp].qtd -= qtd;           /* Para alem disso, subtrai a qtd de produto introduzida do stock do prod no sistema. */
    }

    return funcaoloop();
}

/* Comando r - Remove stock a um produto existente. Formato de entrada > r idp:qtd */
int comando_r() { 

    int idp, qtd;                       /* Inicializacao de vars para guardar o ID do produto, e a quantidade de produto a remover do stock. */
    scanf("%d:%d", &idp, &qtd);         /* Leitura do resto do input, guardando os valores nas respetivas vars. */

    if (idp > idp_atual)                /* Se o produto ainda nao estiver introduzido no sistema, imprime msg de erro. */
        printf("Impossivel remover stock do produto %d. Produto inexistente.", idp);
    else if (produtos[idp].qtd < qtd)   /* Se a quantidade introduzida for superior ao stock do produto no sistema, imprime msg de erro. */
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.", qtd, idp);
    else                                
        produtos[idp].qtd -= qtd;       /* Remove a quantidade introduzida ao stock do produto no sistema. */

    return funcaoloop();
}

/* Comando R - Remove um produto de uma encomenda. Formato de entrada > R ide:idp */
int comando_R() {                 

    int ide, idp;                       /* Inicializacao de vars para guardar os ID's da encomenda e do produto. */
    int i;
    scanf("%d:%d", &ide, &idp);         /* Leitura do resto do input, guardando os valores nas respetivas vars. */

    if (ide > ide_atual)                /* Se a encomenda nao tiver sido criada, imprime msg de erro. */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.", idp, ide);
    else if (idp > idp_atual)           /* Se o produto nao estiver introduzido no sistema, imprime msg de erro. */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", idp, ide);
    else {
        encomendas[ide].produtos_enc[idp].idp = -1;         /* Iguala o ID do produto na encomenda a -1, o que significa que ja nao existe. */
        for (i = 0; i < MAXDESC; i++)                       /* Iguala a "" todos os caracteres do vetor descricao do produto na encomenda, */
            encomendas[ide].produtos_enc[idp].desc[i] = ' ';/* exceto o ultimo, que fica \0. */
        encomendas[ide].produtos_enc[idp].preco = 0;        /* Coloca a 0 o preco do produto na encomenda. */
        encomendas[ide].produtos_enc[idp].peso = 0;         /* Coloca a 0 o peso do produto na encomenda. */
        encomendas[ide].produtos_enc[idp].qtd = 0;          /* Coloca a 0 a quantidade do produto na encomenda. */
    }

    return funcaoloop();
}

/* Comando C - Calcula o custo de uma encomenda. Formato de entrada > C ide */
int comando_C() {

    int ide, total = 0;                 /* Inicializacao de vars para guardar o ID da encomenda e o seu custo total (comeca a 0), que sera calculado. */
    scanf("%d", &ide);                  /* Leitura do resto do input, guardando o valor na respetiva variavel. */

    if (ide > ide_atual)                /* Se a encomenda nao tiver sido criada, imprime msg de erro. */
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.", ide);
    else {
        int i;
        for (i = 0; i < MAXPRODUTOS; i++) {     /* Percorre um a um todos os produtos passiveis de existir na encomenda ide. */
            /* Se o produto existir na encomenda (idp diferente de -1), e calculado o custo total da mesma, 
            sendo este o total ja calculado ate agora, mais o produto entre o preco e a quantidade do prod atual. */
            if (encomendas[ide].produtos_enc[i].idp != -1)  
                total += encomendas[ide].produtos_enc[i].preco*encomendas[ide].produtos_enc[i].qtd; 
        }
        printf("Custo da encomenda %d : %d", ide, total);     /* Imprime a mensagem Custo da encomenda, com o valor calculado. */
    }   

    return funcaoloop();
}

/* Comando p - Altera o preco de um produto existente no sistema. Formato de entrada > p idp:preco */
int comando_p() {               
    
    int idp, preco, i;                  /* Inicializacao de vars para guardar o ID da encomenda e o seu custo total (comeca a 0), que sera calculado. */
    scanf("%d:%d", &idp, &preco);       /* Leitura do resto do input, guardando o valor nas respetivas vars. */

    if (idp > idp_atual)                /* Se o produto nao estiver introduzido no sistema, imprime msg de erro. */
        printf("Impossivel alterar preco do produto %d. Produto inexistente.", idp);
    else {
        produtos[idp].preco = preco;    /* Copia para o preco do produto o novo valor introduzido. */

        /* Percorre as encomendas existentes e se contiverem o produto idp,
        altera o seu preco no vetor de produtos da encomenda: */
        for (i = 0; i <= ide_atual; i++) {                      
            if (encomendas[i].produtos_enc[idp].idp == idp)    
                encomendas[i].produtos_enc[idp].preco = preco;
        }
    }

    return funcaoloop();
}

/* Comando E - Lista a descricao e a quantidade de um produto numa encomenda. Formato de entrada > E ide:idp */
int comando_E() {     

    int ide, idp;                       /* Inicializacao de vars para guardar os ID's da encomenda e do produto. */
    scanf("%d:%d", &ide, &idp);         /* Leitura do resto do input, guardando o valor nas respetivas vars. */

    if (ide > ide_atual)                /* Se a encomenda nao tiver sido criada, imprime msg de erro. */
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.", idp, ide);
    else if (idp > idp_atual)           /* Se o produto nao estiver introduzido no sistema, imprime msg de erro. */
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.", idp, ide);

    else                                /* Imprime mensagem com a descricao do produto idp e a sua quantidade na encomenda ide. */
        printf("%s %d", encomendas[ide].produtos_enc[idp].desc, encomendas[ide].produtos_enc[idp].qtd);
    
    return funcaoloop();
}

/* Comando m - Lista o id da encomenda em que o produto dado ocorre mais vezes.
Se houver 2 ou + encomendas nessa situacao, imprime a de menor id. Formato de entrada > m idp */
int comando_m() {                 

    int idp;                            /* Inicializacao de var para guardar o id do produto. */
    int max_qtd = 0;                    /* Var que guarda o quantidade do produto na encomenda em que ocorreu mais vezes ate entao. */
    int max_ide = 0;                    /* Var que guarda o id da encomenda em que o produto ocorreu mais vezes ate entao. */

    scanf("%d", &idp);                  /* Leitura do resto do input, guardando o valor na resp var. */

    if (idp > idp_atual)
        printf("Impossivel listar maximo do produto %d. Produto inexistente.", idp);

    /* Percorre o vetor das encomendas. Se a encomenda i existir, o produto idp estiver introduzido nela, e a qtd do produto na mesma for maior que
    o maior valor numa encomenda ate entao, guarda o novo valor na variavel max_qtd. Para alem disso guarda o id desta encomenda na var max_ide. */
    else {    
        for (i = 0; i < MAXENCOMENDAS; i++) {  
            if (encomendas[i].ide != -1 && encomendas[i].produtos_enc[idp].idp != -1 && encomendas[i].produtos_enc[idp].qtd > max_qtd) {
                max_qtd = encomendas[i].produtos_enc[idp].qtd;
                max_ide = i;
            }    
        }
        printf("Maximo produto %d %d %d", idp, max_ide, max_qtd);     /* Imprime a msg com o id do produto, o id da encomenda e a quantidade maxima do mesmo. */
    }

    return funcaoloop();                   
}


/* Comando l - Lista todos os produtos existentes no sistema por ordem crescente de preco.
Se houver 2 ou + produtos com o mesmo preco, imprime esses por ordem crescente de id de produto. Formato de entrada > l */
int comando_l() {                 

    /* VETOR QUE CONTERA APENAS OS PRODUTOS JA INTRODUZIDOS NO SISTEMA: */

    int i;
    int contador_prods = 0;                         /* Var que servira como contador dos produtos ja copiados do vetor produtos[] para o novo. */
    int left = 0;                                   /* Var que contem o limite esquerdo do conjunto de produtos a percorrer (indice do primeiro prod).  */
    int right = contador_prods - 1;                 /* Var que contem o limite direito do conj de prods a percorrer (indice do ultimo prod). */
    int j, done;                                    /* Variavel auxiliar done indica se os produtos ja estao ordenados. 1 - Verdadeiro; 0 - Falso */
    struct produto ordenados_preco[MAXPRODUTOS];    /* Novo vetor para guardar os prods ordenados. */  
    struct produto t;

    for (i = 0; i < MAXPRODUTOS; i++) {
        /* Copia para o novo vetor apenas os elementos de produtos[] cujo id nao seja -1 (os que foram introduzidos no sistema): */
        if (produtos[i].idp != -1) {                    
            ordenados_preco[contador_prods].idp = produtos[i].idp;
            for (j = 0; j < MAXDESC; j++)
                ordenados_preco[contador_prods].desc[j] = produtos[i].desc[j];
            ordenados_preco[contador_prods].preco = produtos[i].preco;
            ordenados_preco[contador_prods].peso = produtos[i].peso;
            ordenados_preco[contador_prods].qtd = produtos[i].qtd;

            contador_prods += 1;
        }
    }

    /* BUBBLE SORT - PRECOS: algoritmo que vai ordenar os produtos do vetor recem-criado por ordem crescente de preco. */
    
    for (i = left; i < right; i++) {        /* Ciclo 1: percorre todo o conjunto, produto a produto. */
        done = 1;         
        for (j = right; j > i; j--) {       /* Ciclo 2: percorre o conj desde o limite direito ate ao i atual, produto a produto. */
            /* Se a cada ciclo 2 o preco de um produto for menor que o do prod a sua esquerda, troca a sua ordem. */
            if (ordenados_preco[j].preco < ordenados_preco[j-1].preco) {    
                t = ordenados_preco[j-1];
                ordenados_preco[j-1] = ordenados_preco[j];
                ordenados_preco[j] = t;                  
                done = 0;                                                          
            }
            /* Se a cada ciclo 2 o preco de um produto for igual ao da sua esquerda e o idp for menor, troca a sua ordem. */
            else if (ordenados_preco[j].preco == ordenados_preco[j-1].preco && ordenados_preco[j].idp < ordenados_preco[j-1].idp) {     
                t = ordenados_preco[j-1];
                ordenados_preco[j-1] = ordenados_preco[j];
                ordenados_preco[j] = t;;
                done = 0;
            }
        if (done) break;                    /* Se o vetor estiver ordenado, sai do ciclo 1. */
        }
    }

    printf("Produtos\n");                   /* Imprime o titulo da lista de produtos a devolver. */

    for (i = 0; i < contador_prods; i++)    /* Imprime um a um os produtos ordenados por preco, devolvendo em cada linha a descricao, o preco e a quantidade de cada um.*/
        printf("* %s %d %d\n", ordenados_preco[i].desc, ordenados_preco[i].preco, ordenados_preco[i].qtd);


    return funcaoloop();
}

/* Comando L - Lista todos os produtos de uma encomenda por ordem alfabetica da descricao. Formato de entrada > L ide */
int comando_L() {              

    int ide;
    scanf("%d", &ide);

    if (ide > ide_atual)
        printf("Impossivel listar encomenda %d Encomenda inexistente.", ide);
    
    else {
        /* VETOR COM APENAS OS PRODUTOS JA INTRODUZIDOS NA ENCOMENDA IDE: */

        int contador_prods = 0;                                 /* Variavel para contar o nr de produtos introduzidos na encomenda ide. */
        int i;
        int left = 0;
        int right = contador_prods - 1;
        int j, k, done;                                         /* Variavel auxiliar done indica se os produtos ja estao ordenados. */
        struct produto ordenados_alfab[MAXPRODUTOS];            /* ? inicializado um novo vetor para os prods ja introduzidos na encomenda. */
        struct produto t;

        for (i = 0; i < MAXPRODUTOS; i++) {
            /* Copia para o novo vetor apenas os elementos de produtos_enc[] cujo id nao seja -1 (os que foram introduzidos na encomenda): */
            if (encomendas[ide].produtos_enc[i].idp != -1) {    
                ordenados_alfab[contador_prods].idp = encomendas[ide].produtos_enc[i].idp;
                for (j = 0; j < MAXDESC; j++)
                    ordenados_alfab[contador_prods].desc[j] = encomendas[ide].produtos_enc[i].desc[j];
                ordenados_alfab[contador_prods].preco = encomendas[ide].produtos_enc[i].preco;
                ordenados_alfab[contador_prods].peso = encomendas[ide].produtos_enc[i].peso;
                ordenados_alfab[contador_prods].qtd = encomendas[ide].produtos_enc[i].qtd;

                contador_prods += 1;
            }
        }

        /* BUBBLE SORT - DESCRICAO (ORDEM ALFABETICA): algoritmo que vai ordenar os produtos do vetor recem-criado por ordem alfabetica da descricao.*/

        /* Algoritmo semelhante ao bubble sort do comando l, exceto no ciclo 3, que ira efetuar a ordem alfabetica. */

        for (i = left; i < right; i++) {    /* Ciclo 1 */
            done = 1;           
            for (j = right; j > i; j--) {   /* Ciclo 2 */

                /* Ciclo 3: percorre as descricoes dos produtos j e j-1, comparando os caracteres de ambos que se encontram na mesma posicao k.
                Se o valor ascii do caracter do prod j for menor que o do prod j-1, troca as posicoes dos produtos no vetor e sai deste ciclo.
                Se o valor ascii do car do prod j for maior, sai apenas do ciclo deixando a posicao dos produtos inalterada.
                Por conseguinte, se os vals ascii dos cars de ambos os produtos forem iguais, repete o ciclo ate estes serem diferentes e haver uma decisao. */
                for (k = 0; k < MAXDESC; k++) {     
                    if (ordenados_alfab[j].desc[k] < ordenados_alfab[j-1].desc[k]) {
                        t = ordenados_alfab[j-1];  
                        ordenados_alfab[j-1] = ordenados_alfab[j]; 
                        ordenados_alfab[j] = t;
                        done = 0;
                        break;
                    }
                    else if (ordenados_alfab[j].desc[k] > ordenados_alfab[j-1].desc[k]) {
                        done = 0;
                        break;
                    }
                }
            if (done) break;   
            }
        }

        printf("Encomenda %d\n", ide);

        for (i = 0; i < contador_prods; i++)
            printf("* %s %d %d\n", ordenados_alfab[i].desc, ordenados_alfab[i].preco, ordenados_alfab[i].qtd);

    }

    return funcaoloop();
}


/* Comando x - Termina o programa. Formato de entrada > x */
int comando_x() {
    
    exit(0);
}


/* INICIO DA EXECUCAO DO PROGRAMA: */
int main() {

    for (i = 0; i < MAXENCOMENDAS; i++) {
    encomendas[i].ide = -1;                 /* id de cada encomenda e inicializado a -1, significa que nao foi criada. */
    encomendas[i].peso = 0;     
    }

    for (j = 0; j < MAXPRODUTOS; j++) {         /* Todos os caracteres da descricao exceto o ultimo serao espacos, por defeito. */
        for (k = 0; k < MAXDESC-1; k++) {
            produtos_enc[j].desc[k] = ' ';
        }
        produtos_enc[j].idp = -1;               /* id de cada produto e inicializado a -1, significa que nao esta introduzido na encomenda. */
        produtos_enc[j].preco = 0;          
        produtos_enc[j].peso = 0;
        produtos_enc[j].qtd = 0;
    }

    return funcaoloop();
}

int funcaoloop() {
    
    int entrada[3];
    int c;
    c = getchar();
    entrada[0] = c;     /* entrada[0] guarda a letra do comando a executar */
    c = getchar();
    entrada[1] = c;     /* entrada[1] guarda o espa?o, de modo a que o scanf do comando comece no resto da string */
    entrada[2] = '\0'; 

    if (entrada[0] == 'a')
        return comando_a();
    if (entrada[0] == 'q')
        return comando_q();
    if (entrada[0] == 'N')
        return comando_N();
    if (entrada[0] == 'A')
        return comando_A();
    if (entrada[0] == 'r')
        return comando_r();
    if (entrada[0] == 'R')
        return comando_R();
    if (entrada[0] == 'C')
        return comando_C();
    if (entrada[0] == 'p')
        return comando_p();
    if (entrada[0] == 'E')
        return comando_E();
    if (entrada[0] == 'm')
        return comando_m();
    if (entrada[0] == 'l')
        return comando_l();
    if (entrada[0] == 'L')
        return comando_L();
    if (entrada[0] == 'x')
        return comando_x();

    return 0;    
}