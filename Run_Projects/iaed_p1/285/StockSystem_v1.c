#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT 350
#define DIM_DESCR 63
#define MAX_PRODS 10000
#define DIM_ENCO 200 /* maximo de produtos de uma encomenda 200 porque o minimo de peso de cada
produto e um inteiro 1 e o maximo de peso numa encomenda e 200 */
#define MAX_ENCO 500
#define less(A, B) (strcmp(A,B) < 0) /* para poder ordenar alfabeticamente em 'L' */
#define exch(A, B) { Produto t = A; A = B; B = t; } /* fazer um swap com um Produto t temporario */

/* Estrutura correspondente a um produto*/
typedef struct{
    char descr[DIM_DESCR];
    int price;
    int peso;
    int qtd;
    int idp;
}Produto;

/* Estrutura correspondente a uma Encomenda*/
typedef struct{
    int ide; /* numero de encomenda*/
    Produto Prods[DIM_ENCO]; /* vetor que contem os produtos da encomenda*/
    int peso_total;
    int n_prods; /* numero de produtos na encomenda */
}Enco;

/* Variaveis globais utilizadas ao longo do programa*/
char in[INPUT],cmd;
int num_prod = 0; /* numero de produtos inicia em zero, sera indice de vetor*/
int num_enco = -1; /* numero das encomendas inicia em -1 para saber que nao existem encomendas, sera indice de vetor*/
int aux_idp,aux_ide,aux_qtd,indice_st;

Produto Stock[MAX_PRODS]; /* vetor que contem todos os produtos do sistema*/
Enco AllEnco[MAX_ENCO]; /* vetor com todas as encomendas */

/* le o conteudo da linha e guarda para vetor in[]*/
int leLinha(){
    int i, c;
    if(cmd == 'x' || cmd == 'k' || cmd == 'N' || cmd == 'K' || cmd == 'l'){
        getchar();
        return 0;
    }
    getchar();/* salta o espaco entre comando e input*/
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i){
        in[i] = c;
    }
    in[i] = '\0';
    return 0;
}

/* retorna o indice do produto no stock*/
int indice_stock(int idp){
    int i;
    for(i=0; i< num_prod;i++){
        if (Stock[i].idp == idp)
            return i;
    }
    return -1;
}

/* retorna indice de um produto dentro de uma encomenda*/
int indice_prod(int idp,int ide){
    int i;
    for (i = 0; i < AllEnco[ide].n_prods;i++ ){
        if (strcmp(AllEnco[ide].Prods[i].descr,Stock[idp].descr) == 0){
            return i;
        }
    }
    return -1;
}

/* funcao que vai ler os parametros do input e colocar nas respetivas variaveis */
int CopyInfo(){
    Produto temp;
	char delim[] = ":";
	char *ptr;
	switch(cmd){
        case 'a':
            ptr = strtok(in, delim); /* colocar input ate atingir ':' em ptr*/
            strcpy(temp.descr,ptr);  /* copiar string da descricao para Produto temporario -- temp */
            ptr = strtok(NULL, delim);
            temp.price = atoi(ptr);  /* converter string do input em inteiro e colocar no Produto temp */
            ptr = strtok(NULL, delim);
            temp.peso = atoi(ptr);   /* repetir o mesmo metodo ao longo da funcao CopyInfo() */
            ptr = strtok(NULL, delim);
            temp.qtd = atoi(ptr);
            temp.idp = num_prod;
            Stock[num_prod] = temp;

            break;
        case 'q':
            ptr = strtok(in, delim);
            aux_idp = atoi(ptr);
            indice_st = indice_stock(aux_idp);
            if(aux_idp >= num_prod){
                printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",aux_idp);
                return 0;
            }
            ptr = strtok(NULL, delim);
            Stock[indice_st].qtd += atoi(ptr);

            break;
        case 'A':
            ptr = strtok(in, delim);
            aux_ide = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_idp = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_qtd = atoi(ptr);
            
            break;
        case 'r':
            ptr = strtok(in, delim);
            aux_idp = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_qtd = atoi(ptr);
            
            break;
        case 'R':
            ptr = strtok(in, delim);
            aux_ide = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_idp = atoi(ptr);

            break;
        case 'C':
            ptr = strtok(in, delim);
            aux_ide = atoi(ptr);
            if(aux_ide > num_enco || aux_ide<0){
                printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",aux_ide);
                return -1;
            }
            return aux_ide;

        case 'p':
            ptr = strtok(in, delim);
            aux_idp = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_qtd = atoi(ptr); /* variavel com o preco, esta apenas a aproveitar variavel livre*/

            break;
        case 'E':
            ptr = strtok(in, delim);
            aux_ide = atoi(ptr);
            ptr = strtok(NULL, delim);
            aux_idp = atoi(ptr);

            break;
        case 'm':
            ptr = strtok(in, delim);
            aux_idp = atoi(ptr);
            return aux_idp;

        case 'L':
            ptr = strtok(in, delim);
            aux_ide = atoi(ptr);

            break;
	}
	return 0;
}

/* adiciona Produto ao vetor Stock*/
int cmd_a(){
    CopyInfo();
    printf("Novo produto %d.\n",Stock[num_prod].idp);
    num_prod += 1;
    return 0;
}

/* comando que vai adicionar quantidade a um produto no Stock*/
int cmd_q(){
    CopyInfo();
    return 0;
}

/* comando que vai criar uma nova Encomenda*/
int cmd_N(){
    num_enco += 1;
    AllEnco[num_enco].ide = num_enco;
    AllEnco[num_enco].peso_total = 0;
    AllEnco[num_enco].n_prods = 0;
    printf("Nova encomenda %d.\n",AllEnco[num_enco].ide);
    return 0;
}

/* comando que vai adicionar um Produto ao array de Prods de uma dada Encomenda */
int cmd_A(){
    int k;
    CopyInfo();
    
    if (aux_ide>num_enco || aux_ide<0){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",aux_idp,aux_ide);
        return 0;
    }
    if (aux_idp>=num_prod){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",aux_idp,aux_ide);
        return 0;
    }

    indice_st = indice_stock(aux_idp);
    if (Stock[indice_st].qtd < aux_qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",aux_idp,aux_ide);
        return 0;
    }
    if ((Stock[indice_st].peso * aux_qtd) + AllEnco[aux_ide].peso_total > DIM_ENCO){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",aux_idp,aux_ide);
        return 0;
    }

    for (k = 0; k< DIM_ENCO;k++){
        /* procurar se produto ja existe na encomenda*/
        if (strcmp(AllEnco[aux_ide].Prods[k].descr,Stock[indice_st].descr) == 0){
            AllEnco[aux_ide].Prods[k].qtd += aux_qtd;
            Stock[indice_st].qtd = Stock[indice_st].qtd - aux_qtd;
            AllEnco[aux_ide].peso_total += (Stock[indice_st].peso * aux_qtd);
            return 0;
        }
    }
    k = AllEnco[aux_ide].n_prods; /* guardar o valor do indice numa var k */

    /* copiar parametros do Produto no Stock para a Encomenda*/
    strcpy(AllEnco[aux_ide].Prods[k].descr,Stock[indice_st].descr);
    AllEnco[aux_ide].Prods[k].price = Stock[indice_st].price;
    AllEnco[aux_ide].Prods[k].peso = Stock[indice_st].peso;
    AllEnco[aux_ide].Prods[k].idp = aux_idp;

    Stock[indice_st].qtd -= aux_qtd; /* subtrair quantidade ao Stock*/
    AllEnco[aux_ide].Prods[k].qtd += aux_qtd; /* soma a quantidade*/
    AllEnco[aux_ide].peso_total += (Stock[indice_st].peso * aux_qtd);
    AllEnco[aux_ide].n_prods++; /* incrementa ao num de produtos na encomenda*/

    return 0;
}

/* comando que vai reduzir a quantidade de um produto no Stock*/
int cmd_r(){
    CopyInfo();
    if (aux_idp>=num_prod){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",aux_idp);
        return 0;
    }
    indice_st = indice_stock(aux_idp); /* vai buscar indice de Produto no array Stock[]*/
    if (aux_qtd > Stock[indice_st].qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",aux_qtd,aux_idp);
        return 0;
    }

    Stock[indice_st].qtd -= aux_qtd;

    return 0;
}

/* comando que vai remover um Produto de uma Encomenda*/
int cmd_R(){
    int k;
    CopyInfo();
    if (aux_ide>num_enco || aux_ide<0){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",aux_idp,aux_ide);
        return 0;
    }
    if(aux_idp>=num_prod){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",aux_idp,aux_ide);
        return 0;
    }

    indice_st = indice_stock(aux_idp);
    k = indice_prod(indice_st,aux_ide); /* vai buscar indice de um Produto numa Encomenda*/

    if (k == -1){ /* caso em que Prod nao esta na Encomenda*/
        return 0;
    }

    AllEnco[aux_ide].peso_total -= (AllEnco[aux_ide].Prods[k].peso * AllEnco[aux_ide].Prods[k].qtd); /* reduz o peso total dentro de uma Encomenda*/
    Stock[indice_st].qtd += AllEnco[aux_ide].Prods[k].qtd; /* volta a acrescentar quantidade ao Stock*/

    for(;k<=AllEnco[aux_ide].n_prods;k++){ /* dar um shift left de todos os elementos a partir do produto dado*/
        AllEnco[aux_ide].Prods[k] = AllEnco[aux_ide].Prods[k+1];
    }

    AllEnco[aux_ide].n_prods--; /* diminui numero de produtos na encomenda */  
    return 0;
}

/* comando que vai calcular o custo total de uma dada Encomenda */
int cmd_C(){
    int ide = CopyInfo();
    int i,total=0;
    if (ide == -1) return 0;
    for (i=0;i<AllEnco[ide].n_prods;i++){
        if(AllEnco[ide].Prods[i].qtd > 0){
            total = total + (AllEnco[ide].Prods[i].qtd * AllEnco[ide].Prods[i].price);
        }
    }
    printf("Custo da encomenda %d %d.\n",ide,total);
    return 0;
}

/* comando que vai alterar o preco de um produto tanto Stock como nas Encomendas */
int cmd_p(){
    int i,k;
    CopyInfo();
    if (aux_idp>=num_prod){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",aux_idp);
        return 0;
    }
    indice_st = indice_stock(aux_idp);
    Stock[indice_st].price = aux_qtd; /* aux_qtd esta a segurar valor do preco*/ 
    /* percorrer todas Encomendas e todos os Produtos dentro delas para alterar valor do preco*/
    for (i = 0;i<=num_enco;i++){
        for (k = 0; k< AllEnco[i].n_prods; k++){
            if (AllEnco[i].Prods[k].idp == aux_idp){
                AllEnco[i].Prods[k].price = aux_qtd;
            }
        }
    }
    return 0;
}

/* comando que retorna descricao e qtd do Produto numa dada Encomenda */
int cmd_E(){
    int k;
    CopyInfo();
    if(aux_ide > num_enco || aux_ide<0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",aux_ide);
        return 0;
    }
    if (aux_idp>=num_prod){
        printf("Impossivel listar produto %d. Produto inexistente.\n",aux_idp);
        return 0;
    }
    indice_st = indice_stock(aux_idp);
    k = indice_prod(indice_st,aux_ide);
    if (k != -1)
        printf("%s %d.\n",Stock[indice_st].descr,AllEnco[aux_ide].Prods[k].qtd);
    else
        printf("%s 0.\n",Stock[indice_st].descr); /* caso em que prod nao existe na encomenda */

    return 0;
}

/* comando que retorna o ide da Encomenda em que Produto esta em maior quantidade */
int cmd_m(){
    int idp = CopyInfo();
    int menor_ide = -1,maior_qtd = 0;
    int i,pi;
    if (num_enco == -1){
        return 0;
    }
    if (idp>=num_prod){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return 0;
    }
    indice_st = indice_stock(idp);
    for(i=0;i<=num_enco;i++){
        pi = indice_prod(indice_st,i);
        if (pi == -1)
            continue;
        else{
            if(AllEnco[i].Prods[pi].qtd > maior_qtd){
                maior_qtd = AllEnco[i].Prods[pi].qtd;
                menor_ide = i;
            }
        }
    }
    if (menor_ide != -1){ /* caso em que produto nao existe em nenhuma encomenda, da apenas o return */
        printf("Maximo produto %d %d %d.\n",idp,menor_ide,maior_qtd);
    }
    return 0;
}

/* algoritmo de ordenacao usado em 'l', mergesort */
void merge(Produto arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    Produto L[MAX_PRODS];
    Produto R[MAX_PRODS];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        /* no caso do preco ser igual, por primeiro o de menor idp*/
        if (L[i].price == R[j].price){
            if (L[i].idp < R[j].idp){
                arr[k] = L[i];
                i++;
            }
            else{
                arr[k] = R[j];
                j++;
            }

        }
        else if (L[i].price < R[j].price){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* por elementos restantes */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Produto arr[], int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* comando auxiliar recomendado 'k', vai ser usado em 'l'*/
int cmd_aux_k(){
    int i;
    printf("Produtos\n");
    for (i = 0; i < num_prod;i++){
        printf("* %s %d %d\n",Stock[i].descr,Stock[i].price,Stock[i].qtd);
    }
    return 0;
}

/* lista todos os produtos existentes no Stock por ordem crescente de preco*/
int cmd_l(){
    mergeSort(Stock, 0, num_prod - 1);
    cmd_aux_k();
    return 0;
}

/* algoritmo de ordenacao usado em 'L', quicksort */
int partitionQS(Produto a[],int l, int r) {
  int i = l-1, j = r;
  /* a[r] pivot */
  Produto v = a[r];
  /* enquanto iterador da esquerda for menor que o iterador da direita. */
  while (i < j) {
    /* enquanto descr for menor avanca com o i para a direita. */
    while (less(a[++i].descr, v.descr));
    /* mesma coisa para a direita */
    while (less(v.descr, a[--j].descr)){
      if (j == l) /* elemento onde se faz a particao pode ser o primeiro */
        break;
    }
    /* trocar nesse caso */
    if (i < j)
      exch(a[i], a[j]);
  }
  /* colocar o pivot na posicao i */
  exch(a[i], a[r]);
  /* retorna posicao onde ocorreu a particao */
  return i;
}

void quicksort(Produto a[], int l, int r){
  int i;
  if (r <= l)
    return;
  i = partitionQS(a, l, r);
  quicksort(a, l, i-1);
  quicksort(a, i+1, r);
}

/* lista todos os Produtos de uma dada Encomenda, por ordem alfabetica da descri??o */
int cmd_L(){
    int k;
    CopyInfo();
    if (aux_ide>num_enco || aux_ide<0){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",aux_ide);
        return 0;
    }
    quicksort( AllEnco[aux_ide].Prods , 0 , AllEnco[aux_ide].n_prods - 1 );
    printf("Encomenda %d\n",aux_ide);
    for (k = 0; k < AllEnco[aux_ide].n_prods;k++){
        printf("* %s %d %d\n",AllEnco[aux_ide].Prods[k].descr,AllEnco[aux_ide].Prods[k].price,AllEnco[aux_ide].Prods[k].qtd);
    }
    return 0;
}

int main(){
	while(1){
		cmd = getchar(); /* obtem o comando do input*/
		leLinha();
		switch(cmd){
			case 'a':
				cmd_a();
				break;
            case 'q':
                cmd_q();
                break;
            case 'N':
                cmd_N();
                break;
            case 'A':
                cmd_A();
                break;
            case 'r':
                cmd_r();
                break;
            case 'R':
                cmd_R();
                break;
            case 'C':
                cmd_C();
                break;
            case 'p':
                cmd_p();
                break;
            case 'E':
                cmd_E();
                break;
            case 'm':
                cmd_m();
                break;
            /*case 'k':
                cmd_aux_k();
                break;*/
            case 'l':
                cmd_l();
                break;
            case 'L':
                cmd_L();
                break;
			case 'x':
				return 0;
        }
	}
	return 0;
}