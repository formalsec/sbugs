#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>

/*defenir constantes*/
#define NUMERO_MAXIMO_PRODUTO 10000
#define NUMERO_MAXIMO_ENCOMENDA 500
#define PESO_MAXIMO 200
#define MAXIMO_CARACTER 63
typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B  = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

/*defenir estrutura*/
typedef struct produto{
    char identificacao[MAXIMO_CARACTER];
    int preco;
    int peso;
    int stock;
}Produto;

typedef struct encomeda{
    int descricao[NUMERO_MAXIMO_PRODUTO];
    int Estado;
    int peso_e;
}Encomenda;

Produto identificador[NUMERO_MAXIMO_PRODUTO];
Encomenda numero[NUMERO_MAXIMO_ENCOMENDA];

/*funcoes auxiliares*/
Produto Leproduto(){
    Produto a;
    int indice;
    char c_aux;
    for(indice =0 ; (c_aux = getchar()) != ':' && indice< MAXIMO_CARACTER;indice++){
        a.identificacao[indice] = c_aux;
    }
    a.identificacao[indice] = '\0';
    scanf ("%d:%d:%d",&a.peso,&a.preco,&a.stock);
    return a;
}

void Soma_quantidade(int qtd, int idp){ /* valor de a define se e somar o subtrair*/
    identificador[idp].stock = identificador[idp].stock + qtd;
}

Item auxiliar[NUMERO_MAXIMO_PRODUTO];

void merge(Item a[], int left, int m, int right)
    { 
      int i, j, k;
      for (i = m+1; i > left; i--) 
        auxiliar[i-1] = a[i-1];
      for (j = m; j < right; j++)
        auxiliar[right+m-j] = a[j+1];
      for (k = left; k <= right; k++)
        if (less(identificador[auxiliar[j]].preco, identificador[auxiliar[i]].preco) || i > m)
          a[k] = auxiliar[j--];
        else
          a[k] = auxiliar[i++];
    }

void mergesort(Item a[], int left, int right){
    int m= (right + left)/2;

    if (right <= left)
    {
        return;
    }
    
    mergesort(a,left,m);
    mergesort(a,m+1,right);
    merge(a,left,m,right);
}

void ordena_protudo(){
    int len,aux,b[NUMERO_MAXIMO_PRODUTO];
    len = 0;
    for (aux=0; aux<NUMERO_MAXIMO_PRODUTO; aux++){
        if (identificador[aux].preco != 0){
            b[len] = aux;
            len += 1;
        }
    }
    mergesort(b,0,len-1);
    printf ("Produtos\n");
    for (aux = 0; aux<len; aux++){
        printf ("* %s %d %d\n",identificador[b[aux]].identificacao,identificador[b[aux]].preco,identificador[b[aux]].stock);
    }

}

int Custo_encomenda(int ide){
    int aux, sum,n,l;
    sum = 0;
    for (aux = 0; aux<NUMERO_MAXIMO_PRODUTO ; aux++){
        if (numero[ide].descricao[aux] != 0){
            n = numero[ide].descricao[aux];
            l = identificador[aux].preco;
            sum = sum + (n*l);
        }
    }
    return sum;
}

void Remove_pro_e(int idp, int ide){
    int aux;
    aux = identificador[idp].peso * numero[ide].descricao[idp];
    identificador[idp].stock = identificador[idp].stock + numero[ide].descricao[idp];
    numero[ide].descricao[idp] = 0;
    numero[ide].peso_e = numero[ide].peso_e - aux;
}

int Maximo_p(int idp){
    int c,res;
    res = 0;
    for (c=0;c<NUMERO_MAXIMO_ENCOMENDA;c++){
        if (numero[c].descricao[idp]>numero[res].descricao[c]){
            res = c;
        }
    }
    return res;
}

int partition(Item a[], int left, int right){
    int i= left-1;
    int j = right;
    int aux;
    char v[MAXIMO_CARACTER];
    for (aux=0; aux<MAXIMO_CARACTER && identificador[a[right]].identificacao[aux] != '\0';aux++){
        v[aux]=identificador[a[right]].identificacao[aux];
    }
    v[aux]='\0';
    while (i<j){
        while(strcmp(identificador[a[++i]].identificacao,v)<0);
        while(strcmp(v,identificador[a[--j]].identificacao)<0)
            if (j==left)
                break;
        if (i<j)
            exch(a[i],a[j]);
        
    }
    exch(a[i],a[right]);
    return i;
}

void quicksort(Item a[], int left, int right){
    int i;

    if (right <= left)
        return;
    
    i = partition (a, left, right);
    quicksort (a, left, i-1);
    quicksort (a, i+1, right);
}


void Ordena_enc(int ide){
    int aux,len,d[NUMERO_MAXIMO_PRODUTO];
    len = 0;
    for (aux = 0; aux < NUMERO_MAXIMO_PRODUTO; aux++){
        if (numero[ide].descricao[aux]>0){
            d[len] = aux;
            len = len + 1;
        }
    }
    quicksort(d,0,len-1);
    for (aux=0;aux<len;aux++){
        printf("* %s %d %d\n",identificador[d[aux]].identificacao,identificador[d[aux]].preco,numero[ide].descricao[d[aux]]);
    }

}

void altera(int idp, int prize){
    identificador[idp].preco = prize;
}

void adiciona(int ide, int idp, int qtd){
    numero[ide].descricao[idp] = numero[ide].descricao[idp] + qtd;
    identificador[idp].stock = identificador[idp].stock - qtd;
    numero[ide].peso_e = numero[ide].peso_e + (identificador[idp].peso * qtd);
}


int main(){
    char comando;
    int indice1,indice2,ide,idp,qtd, prize,estado;
    comando = getchar();
    while (comando != 'x'){
        if (comando == 'a'){ /*adiciona um novo produto*/
            estado = 0;
            getchar();
            for (indice1 = 0; estado != 1 && indice1 < NUMERO_MAXIMO_PRODUTO; indice1++){
                if (identificador[indice1].preco == 0 && identificador[indice1].peso == 0){
                    identificador[indice1] = Leproduto();
                    printf ("Novo produto %d.\n",indice1);
                    estado = 1;
                }
            }
        }
        else if (comando == 'q'){ /*adiciona stock a um produto existente no sistema*/
            scanf ("%d:%d",&idp,&qtd);
            if (identificador[idp].preco != 0){
                Soma_quantidade(qtd, idp);
            }
            else{
                printf ("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
            }
            
        }
        else if (comando == 'N'){ /*cria uma nova encomenda */
            estado = 0;
            for (indice1=0; estado != 1 && indice1<NUMERO_MAXIMO_ENCOMENDA; indice1++){
                if (numero[indice1].Estado==0){
                    numero[indice1].Estado = 1;
                    printf ("Nova encomenda %d.\n",indice1);
                    estado = 1;
                }
            }
        }
        else if (comando == 'A'){ /*adiciona um produto existente*/
            scanf("%d:%d:%d",&ide,&idp,&qtd);
            if (numero[ide].Estado==0){
                printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
            }
            else if (identificador[idp].preco==0){
                printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
            }
            else if (qtd>identificador[idp].stock){
                printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
            }
            else if ((((identificador[idp].peso)*qtd) + (numero[ide].peso_e))>PESO_MAXIMO)
            {
                printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);
            }
            else
            {
                adiciona(ide,idp,qtd);
            }    
        }
        else if (comando == 'r'){ /*remove stock a um produto existente*/
            scanf ("%d:%d",&idp,&qtd);
            if (identificador[idp].preco == 0){
                printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
            }
            else if (identificador[idp].stock < qtd){
                printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
            }
            else
            {
                identificador[idp].stock = identificador[idp].stock - qtd;
            }
            
        }
        else if (comando == 'R'){ /*remove um produto de uma encomenda*/
            scanf ("%d:%d",&ide,&idp);
            if (numero[ide].Estado == 0){
                printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
            }
            else if (identificador[idp].preco == 0){
                printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
            }
            else
            {
                Remove_pro_e(idp, ide);
            }
            
        }
        else if (comando == 'C'){ /*calcula o custo de uma encomenda*/
            scanf("%d",&ide);
            if (numero[ide].Estado == 0)
            {
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
            }
            else
            {
                printf("Custo da encomenda %d %d.\n",ide,Custo_encomenda(ide));
            }
            
            
        }
        else if (comando == 'p'){ /*altera o preco de um produto existente no sistema*/
            scanf ("%d:%d",&idp,&prize);
            if (identificador[idp].preco == 0)
            {
                printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
            }
            else
            {
                altera(idp,prize);
            }   
        }
        else if (comando == 'E'){ /*returna a descricao e a quantidade de um produto numa dada encomenda*/
            scanf ("%d:%d",&ide,&idp);
            if (numero[ide].Estado == 0){
                printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
            }
            else if (identificador[idp].preco == 0){
                printf ("Impossivel listar protudo %d. Produto inexistente.\n",idp);
            }
            else
            {
                printf("%s %d.\n",identificador[idp].identificacao,numero[ide].descricao[idp]);
            }
            
        }
        else if (comando == 'm'){ /*retorna o identificador da encomenda em que um dado produto ocorre mais vezes*/
            scanf ("%d",&idp);
            if (identificador[idp].preco == 0){
                printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
            }
            else
            {
                indice2 = Maximo_p(idp);
                if (numero[indice2].descricao[idp]!=0){
                    printf("Maximo produto %d %d %d.\n",idp,indice2,numero[indice2].descricao[idp]);
                }
            }
            
        }
        else if (comando == 'l'){ /*lista todos os produtos existentes no sistema por ordem crescente de preco*/
            ordena_protudo();
        }
        else if (comando == 'L'){ /*lista todos os produtos de uma encomenda por ordem alfabetica da descricao*/
            scanf("%d",&ide);
            if (numero[ide].Estado == 0){
                printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
            }
            else{
                printf ("Encomenda %d\n",ide);
                Ordena_enc(ide);
            }
        }
        comando = getchar();
    }
    return 0;
}