#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/* Tamanho m?ximo das strings de descri??o de produtos */
#define MAXDESCRICAO 64
/* N?mero m?ximo de produtos */
#define MAXPRODS 10000
/* N?mero m?ximo de encomendas */
#define MAXENCOMENDAS 500
/* N?mero m?ximo de produtos numa encomenda */
#define MAXENCOMENDA 200

/* Estutura Produto */
typedef struct produto {

    int idp, preco, peso, qtd;
    char desc[MAXDESCRICAO];

    /* Quantidade em uso; 
    indica quanto stock est? a ser utilizado */
    int qtd_uso;

    /* Vetor de inteiros que a cada ?ndice (ide) faz corresponder
    a quantidade de produto presente na encomenda */
    int qtd_encomendada[MAXENCOMENDAS];

} Produto;

/* Estutura Encomenda */
typedef struct encomenda {

    /* Vetor de produtos que cont?m aqueles 
    presentes na encomenda */
    Produto prods[MAXENCOMENDA];

    /* Inteiro que indica o peso da encomenda */
    int peso;

} Encomenda;


/* Vari?veis Globais */

/* Vetor que guarda todos os produtos criados;
cada ?ndice guarda o produto de idp correspondente */
Produto prods[MAXPRODS] = {0};

/* Vetor que guarda todos as encomendas criadas; 
cada ?ndice guarda a encomenda de ide correspondente */
Encomenda encomendas[MAXENCOMENDAS] = {0};


/* Auxililiares da fun??o __l__ */

/* C?pia do vetor prods */
Produto cp_prods[MAXPRODS] = {0};

/* Inteiro que guarda o ?ndice do ?ltimo produto criado */
int maior_idp;

/* Vetor auxiliar para ordena??o; */
Produto aux_l[MAXPRODS]; 


/* Auxiliares da fun??o __L__ */

/* C?pia do vetor prods da encomenda dada */
Produto encomenda[MAXENCOMENDA];

/* Vetor auxiliar para ordena??o */
Produto aux_L[MAXENCOMENDA]; 


/* Prot?tipos de Fun??es */

/* Adiciona um novo produto ao sistema */
void __a__ (char desc[MAXDESCRICAO], int preco, int peso, int qtd);

/* Adiciona stock a um produto existente */
void __q__ (int idp, int qtd);

/* Cria uma nova encomenda */
void __N__ ();

/* Adiciona um produto a uma encomenda */
void __A__ (int ide, int idp, int qtd);

/* Remove stock a um produto existente */
void __r__ (int idp, int qtd);

/* Remove um produto de uma encomenda */
void __R__ (int ide, int idp);

/* Calcula o custo de uma encomenda */
void __C__ (int ide);

/* Altera o pre?o de um produto do sistema */
void __p__ (int idp, int preco);

/* Lista a descri??o e a quantidade de um produto numa encomenda */
void __E__ (int ide, int idp);

/* Lista o identificador da encomenda em que um dado produto ocorre mais vezes */
void __m__ (int idp);

/* Lista todos os produtos existentes por ordem crescente de pre?o */
void __l__ ();

/* Fun??o de ordena??o por Merge Sort (__l__) */
void Merge_l (Produto a[], int left, int m, int right);

/* Fun??o auxiliar de ordena??o por Merge Sort (__l__) */
void MergeSort_l (Produto a[], int left, int right);

/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o */
void __L__ (int ide);

/* Fun??o de ordena??o por Merge Sort (__L__) */
void Merge_L (Produto a[], int left, int m, int right);

/* Fun??o auxiliar de ordena??o por Merge Sort (__L__) */
void MergeSort_L (Produto a[], int left, int right);


/* L? o comando introduzido pelo utilizador e concretiza a a??o por ele indicada */
int main () {
    
    char c, desc[MAXDESCRICAO];
    int preco, peso, qtd, idp, ide;

    while ((c = getchar())!= 'x') {

        switch (c) {

            case 'a':

                scanf (" %[^:]:%d:%d:%d", desc, &preco, &peso, &qtd);
                
                __a__ (desc, preco, peso, qtd);

                break;
            
            case 'q':

                scanf ("%d:%d", &idp, &qtd);

                __q__ (idp, qtd);

                break;

            case 'N':

                __N__ ();

                break;

            case 'A':

                scanf ("%d:%d:%d", &ide, &idp, &qtd);

                __A__ (ide, idp, qtd);
                
                break;

            case 'r':

                scanf ("%d:%d", &idp, &qtd);

                __r__ (idp, qtd);

                break;
            
            case 'R':

                scanf ("%d:%d", &ide, &idp);

                __R__ (ide, idp);

                break;

            case 'C':

                scanf ("%d", &ide);

                __C__ (ide);

                break;

            case 'p':

                scanf ("%d:%d", &idp, &preco);

                __p__ (idp, preco);

                break;

            case 'E':

                scanf ("%d:%d", &ide, &idp);

                __E__ (ide, idp);

                break;    

            case 'm':

                scanf ("%d", &idp);

                __m__ (idp);

                break;

            case 'l':

                __l__ ();

                break;

            case 'L':

                scanf("%d", &ide);

                __L__ (ide);

                break;

        }

    }

    return 0;

}

void __a__ (char desc[MAXDESCRICAO], int preco, int peso, int qtd) {

    Produto p;
    /* ?ndice do produto */
    static int i = 0;
    int j;

    /* Inicializa??o das vari?veis do produto */
    strcpy(p.desc, desc);
    p.preco = preco;
    p.peso = peso;
    p.qtd = qtd;
    p.idp = i;
    p.qtd_uso = 0;
    
    for (j=0; j < MAXENCOMENDAS; j++)
        p.qtd_encomendada[j] = 0;

    /* Atualiza??o das Vari?veis Globais */
    prods[i] = p;
    maior_idp = i;

    i++;

    printf ("Novo produto %d.\n", p.idp);

}

void __q__ (int idp, int qtd) {

    /* O pre?o de um produto n?o pode ser nulo, logo, 
    este pode ser um crit?rio para determinar a sua exist?ncia */
    if (prods[idp].preco == 0)
        printf ("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
    
    else
        prods[idp].qtd += qtd;

}

void __N__ () {

    /* ?ndice da Encomenda */
    static int i = 0;

    printf ("Nova encomenda %d.\n", i);

    /* O pre?o do primeiro produto de uma encomenda 
    ser? utlizado para determinar a exist?ncia da mesma, 
    por isso este valor ? alterado na cria??o */
    encomendas[i].prods[0].preco = -1;

    i++;

}

void __A__ (int ide, int idp, int qtd) {

    if (encomendas[ide].prods[0].preco == 0)
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (prods[idp].preco == 0) 
        printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else if (prods[idp].qtd < qtd) 
        printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
    
    else if ((encomendas[ide].peso + prods[idp].peso * qtd) > 200) 
        printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);

    else {

        int i;

        /* Altera??o do peso da encomenda e do stock do produto */
        encomendas[ide].peso += prods[idp].peso * qtd;
        prods[idp].qtd -= qtd;
        prods[idp].qtd_uso += qtd;

        if (prods[idp].qtd_encomendada[ide] == 0) {
        /* O produto n?o est? na encomenda; 
        ? necess?rio encontrar uma posi??o desocupada no seu vetor prods */
            for (i = 0; i < MAXENCOMENDA; i++) {

                if (encomendas[ide].prods[i].peso == 0) {
                /* O pre?o de uma posi??o desocupada pode variar (-1 ou 0),
                mas o peso ser? sempre nulo */
                    encomendas[ide].prods[i] = prods[idp];

                    break;

                }
            }
        }

        /* Altera??o da quantidade de produto na encomenda */
        prods[idp].qtd_encomendada[ide] += qtd;
        
    }
}

void __r__ (int idp, int qtd) {

    if (prods[idp].preco == 0)
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);

    else if ((prods[idp].qtd - qtd) < 0) 
        printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);

    else
        prods[idp].qtd -= qtd;  
    
    
}

void __R__ (int ide, int idp) {
    
    if (encomendas[ide].prods[0].preco == 0)
        printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

    else if (prods[idp].preco == 0)
        printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

    else if (prods[idp].qtd_encomendada[ide] == 0)
    /* Se produto n?o estiver na encomenda a fun??o n?o devolve nada */
        return;

    else {

        int i;

        /* Altera??o do peso da encomenda, do stock do produto
        e da quantidade de produto na encomenda */
        encomendas[ide].peso -= prods[idp].qtd_encomendada[ide] * prods[idp].peso;
        prods[idp].qtd += prods[idp].qtd_encomendada[ide];
        prods[idp].qtd_uso -= prods[idp].qtd_encomendada[ide];                
        prods[idp].qtd_encomendada[ide] = 0;

        /* Altera??o do peso do produto na encomenda para que 
        a sua posi??o seja vista como desocupada */
        for (i = 0; i < MAXENCOMENDA; i++) {
             
            if (encomendas[ide].prods[i].idp == idp) {
                
                encomendas[ide].prods[i].peso = 0;
                
                break;

            }
        }
    }
}

void __C__ (int ide) {

    if (encomendas[ide].prods[0].preco == 0) 
        printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);

    else if (encomendas[ide].peso == 0)
    /* Ainda n?o foram adicionados produtos ? encomenda */
        printf ("Custo da encomenda %d 0.\n", ide);

    else {

        int i, custo = 0;

        for (i = 0; i < MAXENCOMENDA; i++) {
        
            if (encomendas[ide].prods[i].preco != 0) {
            /* Percorre todos os produtos na encomenda at? encontrar 
            uma posi??o desocupada (e n?o ocupada previamente) */
                if (encomendas[ide].prods[i].peso != 0) {
                /* O produto n?o foi retirado da encomenda */
                    int idp = encomendas[ide].prods[i].idp;

                    custo += prods[idp].preco * prods[idp].qtd_encomendada[ide];

                }
            }

            else
                break;

        } 

        printf ("Custo da encomenda %d %d.\n", ide, custo);

    }
}

void __p__ (int idp, int preco) {

    if (prods[idp].preco == 0)
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

    else 
        prods[idp].preco = preco;
       
}

void __E__ (int ide, int idp) {
    
    if (encomendas[ide].prods[0].preco == 0) 
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else if (prods[idp].preco == 0)
        printf ("Impossivel listar produto %d. Produto inexistente.\n", idp);

    else 
        printf ("%s %d.\n", prods[idp].desc, prods[idp].qtd_encomendada[ide]);

}

void __m__ (int idp) {

    if (prods[idp].preco == 0)
        printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

    else if (prods[idp].qtd_uso == 0)
    /* Caso o produto n?o esteja em nenhuma encomenda
    a fun??o n?o devolve nada */
        ;

    else {

        int i, ide, qtd = 0;

        for (i = 0; i < MAXENCOMENDAS; i++) {
        /* Percorre o vetor qtd_encomendada do produto
        para comparar a quantidade em cada encomenda */
            if (prods[idp].qtd_encomendada[i] > qtd) {

                ide = i;

                qtd = prods[idp].qtd_encomendada[i];

            }
        }

        printf ("Maximo produto %d %d %d.\n", idp, ide, qtd);

    }
}

void __l__ () {
    
    printf ("Produtos\n");

    if (prods[0].preco == 0)
    /* Ainda n?o foi criado nenhum produto */
        return;

    else {

        int i;

        for (i = 0; i <= maior_idp; i++) {
        /* Copia as vari?veis necess?rias dos produtos para o vetor a ordenar */
            strcpy (cp_prods[i].desc, prods[i].desc);
            cp_prods[i].preco = prods[i].preco;
            cp_prods[i].idp = prods[i].idp;
            cp_prods[i].qtd = prods[i].qtd;

        }

        /* Ordena??o segundo o algoritmo Merge Sort */
        MergeSort_l (cp_prods, 0, maior_idp);

        for (i = 0; i <= maior_idp; i++)
            printf("* %s %d %d\n", cp_prods[i].desc, cp_prods[i].preco, cp_prods[i].qtd);
        
    }
}

void MergeSort_l (Produto a[], int left, int right) {

    int m = (right + left)/2;
    
    if (right <= left) 
        return;
    
    /* Divis?o do vetor de forma a realizar uma ordena??o recursiva */
    MergeSort_l (a, left, m);

    MergeSort_l (a, m + 1, right);

    /* Uni?o ordenada das divis?es */
    Merge_l (a, left, m, right);
}

void Merge_l (Produto a[], int left, int m, int right) {

    int i, j, k;
    
    /* Constru??o do vetor auxiliar */
    for (i = m + 1; i > left; i--)
        aux_l[i - 1] = a[i - 1];
    
    for (j = m; j < right; j++)
        aux_l[right + m - j] = a[j + 1];
    
    /* Ordena??o por compara??o dos elementos em posi??es de extremos */
    for (k = left; k <= right; k++) {

        if (aux_l[j].preco < aux_l[i].preco || i > m)
            a[k] = aux_l[j--];
            
        else
            a[k] = aux_l[i++];

    }
}

void __L__ (int ide) {

    if (encomendas[ide].prods[0].preco == 0) 
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

    else if (encomendas[ide].peso == 0)
    /* Encomenda ainda n?o tem produtos */
        printf ("Encomenda %d\n", ide);

    else {

        int i = 0, j, idp;

        while (i < MAXENCOMENDA) {

            if (encomendas[ide].prods[i].preco != 0) {
            /* Copia todos os produtos da encomenda at? encontrar 
            uma posi??o desocupada (e n?o ocupada previamente) */

                /* Copia apenas as vari?veis necess?rias dos produtos */
                strcpy (encomenda[i].desc, encomendas[ide].prods[i].desc);
                encomenda[i].peso = encomendas[ide].prods[i].peso;
                encomenda[i].idp = encomendas[ide].prods[i].idp;

                i++;
            }

            else
                break;            
        }

        /* Ordena??o segundo o algoritmo Merge Sort;
        o ?ndice i est? na primeira posi??o desocupada 
        (e n?o ocupada previamente), logo, 
        o limite direito da ordena??o ser? a posi??o anterior */
        MergeSort_L (encomenda, 0, i-1);

        printf ("Encomenda %d\n", ide);

        for (j = 0; j < i; j++) {
            
            if (encomenda[j].peso != 0) {
            /* Apenas imprime os produtos que est?o na encomenda */
                idp = encomenda[j].idp;
                
                printf ("* %s %d %d\n", prods[idp].desc, prods[idp].preco, prods[idp].qtd_encomendada[ide]);

            }
        }
    }
}

void MergeSort_L (Produto a[], int left, int right) {

    int m = (right + left)/2;
    
    if (right <= left) 
        return;
    
    MergeSort_L (a, left, m);

    MergeSort_L (a, m + 1, right);

    Merge_L (a, left, m, right);

}

void Merge_L (Produto a[], int left, int m, int right) {

    int i, j, k;
    
    for (i = m + 1; i > left; i--)
        aux_L[i - 1] = a[i - 1];
    
    for (j = m; j < right; j++)
        aux_L[right + m - j] = a[j + 1];
    
    for (k = left; k <= right; k++) {

        if (strcmp (aux_L[j].desc, aux_L[i].desc) < 0)
            a[k] = aux_L[j--];

        else
            a[k] = aux_L[i++];

    }
}
