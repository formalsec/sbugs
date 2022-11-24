#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

#define MAX_DESCRICAO 63
#define MAX_PESO 200
#define MAX_ENCOMENDAS 500
#define MAX_PRODUTOS 10000

typedef struct produto {
    char Descricao[MAX_DESCRICAO];
    int Preco;
    int Peso;
    int Quantidade;
    int Identificacao;
} produto;

typedef struct encomenda {
    int Idp_qnt[2][MAX_PESO];/*Na linha 0 ficaram as identificacoes dos produtos na encomenda e na linha 1 as suas quantidades.*/
    int Peso_total;
    int Numero_produtos;
} encomenda;

#define less(A, B, C, D) (((A) < (B) || ((A)==(B) && (C) < (D))))
#define exch(A,B) { produto t = A; A = B; B = t; }
#define bigger_str(A, B) (strcmp(A, B) > 0)

produto s[MAX_PRODUTOS];/*Vetor onde sao guardados os elementos do tipo produto.*/
encomenda t[MAX_ENCOMENDAS];/*Vetor onde sao guardados os elementos do tipo encomenda.*/
int ide = 0;/*Variavel onde e guardado o numero de encomendas.*/
int idp = 0;/*Variavel onde e guardado o numero de produtos no sistema.*/

void AdicionaProduto();
int Procura_Idp(int id);
void AdicionaStock();
void AdicionaProdutoEncomenda();
void RemoveStock();
void RemoveProdutoEncomenda();
void CalculaCusto();
void AlteraPrecoProduto();
void ListaProdutoEncomenda();
void ListaMaximoId();
void ListaProdutosOrdenados();
void quicksort(int l,int r);
int partition(int l, int r);
void ListaEncomendasOrdenadas();

int main () {
    int i;
    char c;

    for(i=0; i<MAX_PRODUTOS;i++) /*Inicializa as quantidades do vetor de produtos a -1, representando ausencia de produtos.*/
        s[i].Quantidade=-1;
    
    while (c != 'x') {
        switch (c = getchar()) {
            case 'a':
                AdicionaProduto();
                break;

            case 'q':
                AdicionaStock();
                break;

            case 'N':
                printf("Nova encomenda %d.\n",ide++);
                break;

            case 'A':
                AdicionaProdutoEncomenda();
                break;  

            case 'r':
                RemoveStock();
                break;

            case 'R':
                RemoveProdutoEncomenda();
                break;

            case 'C':
                CalculaCusto();
                break;
    
            case 'p':
                AlteraPrecoProduto();
                break;
        
            case 'E':
                ListaProdutoEncomenda();
                break;

            case 'm':
                ListaMaximoId();
                break;
        
            case 'l':
                ListaProdutosOrdenados();
                break;
        
            case 'L':
                ListaEncomendasOrdenadas();
                break;
        }
    }  
    return 0;
}

void AdicionaProduto() {
    /*Esta funcao adiciona um novo produto ao sistema.*/
    scanf(" %[^:]s", s[idp].Descricao);
    scanf(":%d%*c%d%*c%d", &s[idp].Preco, &s[idp].Peso, &s[idp].Quantidade);
    
    s[idp].Identificacao = idp;/*Atribuicao de uma identificacao ao produto.*/
    
    printf("Novo produto %d.\n",idp++);
}

int Procura_Idp(int id) {
    /*Esta funcao recebe uma identificacao e procura em que posicao do vetor produtos se encontra essa identificacao.*/
    int i;
    for(i = 0;i < idp;i++) {
        if(s[i].Identificacao == id)
            break; }
    return i;
}

void AdicionaStock() {
    /*Esta funcao adiciona stock a um produto existente no sistema.*/
    int idp1, idp_1, qtd;
    scanf("%d%*c%d",&idp1, &qtd);
    
    idp_1 = Procura_Idp(idp1);
    
    if(s[idp_1].Quantidade >= 0) {
        s[idp_1].Quantidade += qtd; }   
    else {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp1); }
}

void AdicionaProdutoEncomenda() {
    /*Esta funcao adiciona um produto a uma encomenda. Caso ja exista o produto, aumenta a sua quantidade.*/
    int ide1, idp2, idp_2, qtd1 = 0, i;

    scanf("%d%*c%d%*c%d", &ide1, &idp2, &qtd1);
    
    idp_2 = Procura_Idp(idp2);
    
    if (ide1 >= ide) {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp2, ide1);
        return;
    }
    /*Se o produto nao existe a sua quantidade esta com o valor com que foi inicializado.*/
    else if (s[idp_2].Quantidade == -1) {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp2, ide1);
        return;
    }
    else if (qtd1 > s[idp_2].Quantidade) {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp2, ide1);
        return;
    }
    for (i=0;i < t[ide1].Numero_produtos;i++) {
        if (t[ide1].Idp_qnt[0][i] == idp2) {
            /*Se o produto existir na encomenda, ao aumentar a sua quantidade na encomenda esta nao pode exceder o maximo de peso.*/
            if(t[ide1].Peso_total + qtd1 * s[idp_2].Peso > MAX_PESO){
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp2, ide1);
                return;
            }
            else
            /*Se nao exceder, aumento o peso total da encomenda.*/
                t[ide1].Peso_total += qtd1 * s[idp_2].Peso;
            break; 
        } 
    }
    if(i != t[ide1].Numero_produtos) 
        t[ide1].Idp_qnt[1][i] += qtd1;/*O produto existe na encomenda, entao aumento a sua quantidade.*/
    else if(t[ide1].Peso_total + qtd1 * s[idp_2].Peso <= MAX_PESO) {
        /*O produto nao existe na encomenda tenho que o adicionar, aumentar o peso total e o numero de produtos que estao na encomenda.*/
        t[ide1].Idp_qnt[0][t[ide1].Numero_produtos] = idp2;
        t[ide1].Idp_qnt[1][t[ide1].Numero_produtos] = qtd1;
        t[ide1].Peso_total += qtd1 * s[idp_2].Peso;  
        t[ide1].Numero_produtos++;
    }
    else {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp2, ide1);
        return;
    }
    s[idp_2].Quantidade -= qtd1; /*Retiro a quantidade que estou a adicionar a encomenda do stock do produto.*/
}

void RemoveStock() {
    /*Esta funcao remove stock a um produto existente.*/
    int idp3, idp_3, qtd2;
    scanf("%d%*c%d",&idp3, &qtd2);
    
    idp_3 = Procura_Idp(idp3);
    
    if(s[idp_3].Quantidade >= 0) {
        if (s[idp_3].Quantidade - qtd2 >= 0 ) /*A quantidade em stock nao pode ser negativa.*/
            s[idp_3].Quantidade -= qtd2;
        else
            printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd2, idp3); 
        }
    else 
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp3); 
}

void RemoveProdutoEncomenda(){
    /*Esta funcao remove um produto de uma encomenda.*/
    int ide2, idp4, idp_4, i;
    scanf("%d%*c%d",&ide2, &idp4);
    
    idp_4 = Procura_Idp(idp4);
    
    if (ide2 < ide) {
        if (s[idp_4].Quantidade >= 0) {
            /*Procuro em que posicao do vetor com os produtos da encomenda se encontra o produto a remover.*/
            for (i = 0;i < t[ide2].Numero_produtos;i++) {
                if (t[ide2].Idp_qnt[0][i] == idp4) {
                    s[idp_4].Quantidade += t[ide2].Idp_qnt[1][i];/*Aumento a quantidade do produto em stock.*/
                    t[ide2].Peso_total -= t[ide2].Idp_qnt[1][i] * s[idp_4].Peso;/*Aumento do peso total da encomenda.*/
                    t[ide2].Idp_qnt[1][i] = 0;/*coloco a quantidade do produto na encomenda a zero.*/
                }
            }
        }
        else 
            printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp4, ide2);
    }
    else
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp4, ide2);
}

void CalculaCusto() {
    /*Esta funcao calcula o custo de uma encomenda.*/
    int i, j, ide3, total = 0;
    scanf("%d",&ide3);
    
    if (ide3 < ide) {
        /*Procuro quais sao os produtos que se encontram no vetor com os produtos da encomenda.*/
        for (i = 0; i < t[ide3].Numero_produtos; i++) {
            j = Procura_Idp(t[ide3].Idp_qnt[0][i]);
            if(j != idp)/*Se tiver encontrado um produto.*/
                total += s[j].Preco * t[ide3].Idp_qnt[1][i]; 
        }
        printf("Custo da encomenda %d %d.\n",ide3, total);
    }
    else
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide3);
    total = 0;    
}

void AlteraPrecoProduto() {
    /*Esta funcao altera o preco de um produto existente no sistema.*/
    int idp5, idp_5, valor;
    scanf("%d%*c%d", &idp5, &valor);
    
    idp_5 = Procura_Idp(idp5);
    
    if(s[idp_5].Quantidade >= 0) {
        s[idp_5].Preco = valor; 
    }
    else
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp5);
}

void ListaProdutoEncomenda() {
    /*Esta funcao lista a descricao e a quantidade de um produto numa encomenda.*/
    int i, ide4, idp6, idp_6, in = 0;
    scanf("%d%*c%d",&ide4, &idp6);

    idp_6 = Procura_Idp(idp6);
    
    if (ide4 < ide) {
        if(s[idp_6].Quantidade >= 0) {
            for (i=0; i < t[ide4].Numero_produtos;i++) {
                if (t[ide4].Idp_qnt[0][i] == idp6) {
                    /*Se o produto existir na encomenda a variavel in fica a 1.*/
                    in = 1;
                    printf("%s %d.\n", s[idp_6].Descricao, t[ide4].Idp_qnt[1][i]);
                }
            }
            if(!in)
                /*Se o produto nao existe na encomenda, o que se sabe atraves da variavel in, a sua quantidade e zero.*/
                printf("%s 0.\n", s[idp_6].Descricao);
        }
        else
            printf("Impossivel listar produto %d. Produto inexistente.\n",idp6);
    }
    else
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide4);
}

void ListaMaximoId() {
    /*Esta funcao lista o identificador da encomenda em que o produto dado ocorre mais vezes.*/
    int i, j, idp7, idp_7, max_qnt = 0, max_id = 0;
    scanf("%d", &idp7);

    idp_7 = Procura_Idp(idp7);
    
    if (s[idp_7].Quantidade >= 0) {
        if (ide != 0) {
            /*Escolhe uma encomenda.*/
            for(i = 0;i < ide;i++) {
                /*Dentro da encomenda procuro em que posicao do vetor com os produtos da encomenda se encontra o produto.*/
                for(j = 0;j < t[i].Numero_produtos;j++) {
                    if(t[i].Idp_qnt[0][j] == idp7) {
                        /*Se a quantidade desse produto for maior que a maior quantidade descoberta, essa quantidade passa a ser 
                        o novo maximo e guardamos a identificacao da encomenda.*/
                        if(t[i].Idp_qnt[1][j] > max_qnt) {
                            max_qnt = t[i].Idp_qnt[1][j];
                            max_id = i;
                        }
                        break; }  
                }
            } 
            if (max_qnt != 0)
                printf("Maximo produto %d %d %d.\n", idp7, max_id, max_qnt);        
        }
    }
    else
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp7);
}

void ListaProdutosOrdenados() {
    /*Esta funcao lista todos os produtos existentes no sistema por ordem crescente de preco, e se estes tiverem o mesmo
    preco, ordena por ordem crescente de identificacao de produto.*/
    int i;
    quicksort(0,idp-1);/*Utilizacao do algoritmo de ordenacao quick sort.*/
    printf("Produtos\n");
    for(i=0; i < idp;i++) {
        printf("* %s %d %d\n", s[i].Descricao, s[i].Preco, s[i].Quantidade);
    }
}

void quicksort(int l,int r) {
    /*Funcao recursiva que faz parte do algoritmo para realizar o quick sort. Esta funcao recebe os extremos a ordenar.*/
    int i; 
    if(r<=l) return; 
    i = partition(l,r);
    quicksort(l,i-1);
    quicksort(i+1,r);
}

int partition(int l, int r) {
    /*Funcao auxiliar do quick sort que faz a particao do vetor. Esta funcao recebe os extremos do vetor a ordenar.*/
    int i = l-1;
    int j = r;
    int v = s[r].Preco;
    int v1 = s[r].Identificacao;
    while (i<j) {
        do{
        i++;
        }
        while (less(s[i].Preco,v, s[i].Identificacao,v1)); 
        do{
            j--;
            if (j==l)
                break;
        }
        while (less(v,s[j].Preco,v1,s[j].Identificacao));
        if (i<j) {
            exch(s[i],s[j]);
        }
    }
    exch(s[i], s[r]);
    return i;
}

void ListaEncomendasOrdenadas() {
    /*Esta funcao lista todos os produtos de uma encomenda por ordem alfabetica da descricao.*/
    int ide5, i, j, pi, pj, aux;
    scanf("%d", &ide5);

    if (ide5 < ide) { 
        /*Utilizacao do algortimo de ordenacao bubble sort.*/
        for (i = 0; i < t[ide5].Numero_produtos; i++) { 
            for (j = 0; j < t[ide5].Numero_produtos - i-1; j++) {
                pi = Procura_Idp(t[ide5].Idp_qnt[0][j]);
                pj = Procura_Idp(t[ide5].Idp_qnt[0][j+1]);
                
                if (bigger_str(s[pi].Descricao,s[pj].Descricao)) {
                    /*Troca da posicao da identificacao e respetiva quantidade.*/
                    aux = t[ide5].Idp_qnt[0][j]; 
                    t[ide5].Idp_qnt[0][j] = t[ide5].Idp_qnt[0][j+1]; 
                    t[ide5].Idp_qnt[0][j+1] = aux;

                    aux = t[ide5].Idp_qnt[1][j]; 
                    t[ide5].Idp_qnt[1][j] = t[ide5].Idp_qnt[1][j+1]; 
                    t[ide5].Idp_qnt[1][j+1] = aux;
                }
            }
        }
        printf("Encomenda %d\n", ide5);
        for(i=0; i < t[ide5].Numero_produtos;i++) {
            j = Procura_Idp(t[ide5].Idp_qnt[0][i]);
            if (t[ide5].Idp_qnt[1][i] != 0) /*A quantidade ser igual a zero significa que o produto nao existe na encomenda.*/
                printf("* %s %d %d\n",s[j].Descricao, s[j].Preco, t[ide5].Idp_qnt[1][i]);    
        }
    }
    else {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide5);
    }
}