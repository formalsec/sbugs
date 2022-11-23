#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* constantes */
#define MAXidp 9999
#define MAXstr 64               /* numero maximo de caracteres para a descricao */
#define MAXenc 500
#define MAXpeso 200
#define MAXprodutos 10000
#define INFO 5                  /* numero maximo de argumentos no input do user */

/* estrutura dos produtos */
typedef struct {
	char Descricao[MAXstr];
	int Preco;
	int Peso;
	int Quantidade;
} produto;

/* base de dados do stock dos produtos */
produto stock[MAXidp];

/*estrutura das encomendas*/
typedef struct {
	char Descricao[MAXstr];
	int Preco;
	int Peso;
	int Quantidade;
	int Inicia;
} encomenda;

/* base de dados das encomendas */
encomenda dataBase[MAXenc][MAXpeso];


/*      Funcoes auxiliares         */

/* Esta funcao devolve o proximo idp */
int proximoidp(){
	int i = 0;
	if (strcmp(stock[i].Descricao, "") == 0){
		return i;
	}
	while (strcmp(stock[i].Descricao, "") != 0){
		i++;
	}
	return i;
}

/* Esta funcao devolve o proximo ide */
int proximoide(){
	int i = 0;
	while (dataBase[i][0].Inicia != -1) {
		i++;
	}
	return i;
}

/* Esta funcao devolve qual o id do produto dentro da encomenda */
int idpEnc(int ide, int idp){
	int i;
	for (i = 0; i < MAXpeso; i++){
		if ((strcmp(dataBase[ide][i].Descricao, stock[idp].Descricao) == 0) || dataBase[ide][i].Inicia == -1)
			break;
	}
	return i;
}

/* Esta funcao devolve o peso da encomenda */
int pesoTotalEnc(int ide) {
	int i, peso = 0;
	for (i = 0; i < MAXpeso; i++){
		peso += dataBase[ide][i].Peso;
	}
	return peso;
}

/* Esta funcao recebe uma string e retorna o numero de "indices"
resultantes de separar a string pelos ':' */
int separarString(char entrada[MAXstr], char armazenado[INFO][MAXstr]) {
    int i;
    char *word = "";
    for (i = 0; i < INFO; i++) {
        strncpy(armazenado[i], "", MAXstr);
    }
    i = 0;
    word = strtok(entrada, ":");
    while (word != NULL) {
        strncpy(armazenado[i], word, MAXstr);   
        word = strtok(NULL, ":");
        i++;
    }
    return i;
}

/* Funcao que le uma string carater a carater ate encontrar o carater
\n, \0 ou EOF, devolvendo o numero de carateres lidos */
int readLine(char s[]) {
    char c;
    int n = 0;
    while ((c = getchar()) != EOF && c != '\n' && c != '\0') {
        s[n] = c;
        n++;
    }
    s[n] = '\0';
    return n;
}

void merge_l(int tab_final[], int start, int mid, int end){
	int i, j, k, tab_aux[MAXprodutos];
	for (i = mid + 1; i > start; i--)
		tab_aux[i-1] = tab_final[i-1];
	for (j = mid; j < end; j++)
		tab_aux[end + mid - j] = tab_final[j+1];
	for (k = start; k <= end; k++){
		if (stock[tab_aux[j]].Preco < stock[tab_aux[i]].Preco || i > mid)
			tab_final[k] = tab_aux[j--];
		else
			tab_final[k] = tab_aux[i++];
	}
}

/* Funcao auxiliar com o algoritmo de ordenacao mergeSort. Recebe um vetor e ordena-o no sentido ascendente relativamente ao preco dos produtos. */
void mergeSort_l(int tab_final[MAXprodutos], int start, int end) {
	int mid = (start + end) / 2;
	if (end <= start)
		return;

	mergeSort_l(tab_final, start, mid);
	mergeSort_l(tab_final, mid + 1, end);
	merge_l(tab_final, start, mid, end);
}

void merge_L(int tab_final[], int start, int mid, int end, int ide){
	int i, j, k, tab_aux[MAXprodutos];
	for (i = mid + 1; i > start; i--)
		tab_aux[i-1] = tab_final[i-1];
	for (j = mid; j < end; j++)
		tab_aux[end + mid - j] = tab_final[j+1];
	for (k = start; k <= end; k++){
		if (strcmp(dataBase[ide][tab_aux[j]].Descricao, dataBase[ide][tab_aux[i]].Descricao) < 0 || i > mid)
			tab_final[k] = tab_aux[j--];
		else
			tab_final[k] = tab_aux[i++];
	}
}

/* Funcao auxiliar com o algoritmo de ordenacao Bubblesort. Recebe um vetor e ordena-o por ordem alfabetica pela descricao dos produtos. */
void mergeSort_L(int tab_final[MAXprodutos], int start, int end, int ide) {
	int mid = (start + end) / 2;
	if (end <= start)
		return;

	mergeSort_L(tab_final, start, mid, ide);
	mergeSort_L(tab_final, mid + 1, end, ide);
	merge_L(tab_final, start, mid, end, ide);
}



/*      Funcoes Principais         */

/* Esta funcao adiciono um novo produto ao sistema.  */
int novoProd(){
	int i = proximoidp();
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	strncpy(stock[i].Descricao, args[0], MAXstr);
	stock[i].Preco = atoi(args[1]);
	stock[i].Peso = atoi(args[2]);
	stock[i].Quantidade = atoi(args[3]);
	printf("Novo produto %d.\n", i);
	return 0;
}

/* Esta funcao adiciona stock a um produto do sistema */
int adStock(){
	int idp;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	idp = atoi(args[0]);
	if (stock[idp].Peso == 0)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);
	else
		stock[idp].Quantidade += atoi(args[1]);
	return 0;
}

/* Esta funcao cria uma nova encomenda */
int novaEnc(){
	int i = proximoide();
	dataBase[i][0].Inicia = 0;
	printf("Nova encomenda %d.\n", i);
	return 0;
}

/* Esta funcao adiciona um produto a uma encomenda */
int adProd(){
	int idp, ide, produtoQtd, i;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	ide = atoi(args[0]);
	idp = atoi(args[1]);
	produtoQtd = atoi(args[2]);

	if (dataBase[ide][0].Inicia == -1) {
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return 1;
	}
	if (strcmp(stock[idp].Descricao, "") == 0) {
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return 1;
	}
	if (produtoQtd > stock[idp].Quantidade) {
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		return 1;
	}
	if ((pesoTotalEnc(ide) + (stock[idp].Peso * produtoQtd)) > MAXpeso) {
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
		return 1;
	}
	i = idpEnc(ide, idp);
	strcpy(dataBase[ide][i].Descricao, stock[idp].Descricao);
	dataBase[ide][i].Preco = stock[idp].Preco;
	dataBase[ide][i].Quantidade += produtoQtd;
	dataBase[ide][i].Peso += (produtoQtd * stock[idp].Peso);
	dataBase[ide][i].Inicia = 0;
	stock[idp].Quantidade -= produtoQtd;
	return 0;
}

/* Esta funcao remove stock a um produto existente */
int removeStock(){
	int produtoQtd, idp;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	idp = atoi(args[0]);
	produtoQtd = atoi(args[1]);
	if (strcmp(stock[idp].Descricao, "") == 0) {
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
		return 1;
	}
	if ((stock[idp].Quantidade - produtoQtd) < 0){
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", produtoQtd, idp);
		return 1;
	} 
	stock[idp].Quantidade = stock[idp].Quantidade - produtoQtd;
	return 0;
}

/* Esta funcao remove um produto de uma encomenda */
int removeProd(){
	int idp, ide, i;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	ide = atoi(args[0]);
	idp = atoi(args[1]);
	i = idpEnc(ide, idp);
	if (dataBase[ide][0].Inicia == -1) {
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
		return 1;
	} 
	if (strcmp(stock[idp].Descricao, "") == 0) {
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
		return 1;
	}
	if (strcmp(dataBase[ide][i].Descricao, stock[idp].Descricao) != 0){
		return 1;
	}
	stock[idp].Quantidade += dataBase[ide][i].Quantidade;
	strcpy(dataBase[ide][i].Descricao, "");
	dataBase[ide][i].Preco = 0;
	dataBase[ide][i].Quantidade = 0;
	dataBase[ide][i].Peso = 0;
	dataBase[ide][i].Inicia = 1;   /* Poe a 1 para dizer que esta posicao dentro da encomenda foi apagada */
	return 0;
}

/* Esta funcao devolve o custo de uma encomenda */
int custoEnc(){
	int ide;
	int i;
	int total = 0;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	ide = atoi(args[0]);
	if (dataBase[ide][0].Inicia == -1) {
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		return 1;
	}
	for (i = 0; i < MAXpeso; i++){
		total += (dataBase[ide][i].Preco * dataBase[ide][i].Quantidade);
	}
	printf("Custo da encomenda %d %d.\n", ide, total);
	return 0;
}

/* Esta funcao altera o preco de um produto existente no sistema */
int alteraPreco(){
	int i, e;
	int produtoPreco, idp;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	idp = atoi(args[0]);
	produtoPreco = atoi(args[1]);
	if (strcmp(stock[idp].Descricao, "") == 0) {
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
		return 1;
	}
	for (i = 0; i < MAXenc; i++){
		if (dataBase[i][0].Inicia != -1){
			e = idpEnc(i, idp);
			if ((strcmp(dataBase[i][e].Descricao, stock[idp].Descricao) == 0) && (dataBase[i][e].Inicia == 0)) { /* Ve se o produto existe na encomenda */
				dataBase[i][e].Preco = produtoPreco;
			}
		}
		else
			break;
	}
	stock[idp].Preco = produtoPreco;
	return 0;
}

/* Esta funcao lista a descricao e quantidade de um
produto da encomenda. */
int descQtd(){
	int idp, ide, i;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	ide = atoi(args[0]);
	idp = atoi(args[1]);
	i = idpEnc(ide, idp);
	if (dataBase[ide][0].Inicia != -1) {
		if (strcmp(stock[idp].Descricao, "") != 0){
			printf("%s %d.\n", stock[idp].Descricao, dataBase[ide][i].Quantidade);
		}
		else {
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
		}
	}
	else{
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	}
	return 0;
}

/* Esta funcao lista o identificador da encomenda em que o
produto dado tem maior quantidade */
int identificadorMax() {
	int idp;
	int i;
	int max = 0;
	int ide;
	int a;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	idp = atoi(args[0]);
	if (strcmp(stock[idp].Descricao, "") != 0){ /* Verifica se o produto existe em stock. */
		for (i = 0; i < MAXenc; i++){			
			if (dataBase[i][0].Inicia != -1) {  /* Verifica se a encomenda existe, se n?o existir sai do ciclo for pois nao ha mais a seguir tambem */
				a = idpEnc(i, idp);
				if (strcmp(stock[idp].Descricao, dataBase[i][a].Descricao) == 0) {
					if (dataBase[i][a].Quantidade > max) {
						max = dataBase[i][a].Quantidade;
						ide = i;
					}
				}
			}
			else
				break;
		}
		if (max != 0){
			printf("Maximo produto %d %d %d.\n", idp, ide, max);
		}
	}
	else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
	return 0;
} 

/* Esta funcao lista todos os produtos em stock por ordem crecente de valor do preco */
int listaProd() {
	int e, i, counter = 0, tab_final[MAXprodutos];
	for (e = 0; e < MAXprodutos; e++){     /* Adiciona o idp por ordem crescente ao vetor que vai ser ordenado pela funcao mergeSort */
		if (strcmp(stock[e].Descricao, "") != 0) {
			tab_final[e] = e;
			counter ++;
		} 
		else
			break;
	}
	mergeSort_l(tab_final, 0, counter - 1);  /* Chama a funcao auxiliar mergeSort dando o vetor a ordenar e cada um dos estremos */
	printf("Produtos\n");
	for (i = 0; i < counter; i++){
		printf("* %s %d %d\n", stock[tab_final[i]].Descricao, stock[tab_final[i]].Preco, stock[tab_final[i]].Quantidade);
	}
	return 0;
}

/* Esta funcao lista todos os produntos de uma encomenda por ordem alfabetica da descricao. */
int listaProdEnc() {
	int i, counter = 0, tab_final[MAXpeso], ide;
	char args[INFO][MAXstr];
	char s[MAXstr];
	readLine(s);
	separarString(s, args);
	ide = atoi(args[0]);
	if (dataBase[ide][0].Inicia == -1){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
		return 1;
	}
	for (i = 0; i < MAXpeso; i++){   /* Adiciona o id por ordem crescente ao vetor que vai ser ordenado pela funcao mergeSort */
		if ((strcmp(dataBase[ide][i].Descricao, "") != 0) && (dataBase[ide][i].Inicia == 0)){
			tab_final[counter] = i;
			counter ++;
		}
	}
	mergeSort_L(tab_final, 0, counter - 1, ide); /* Chama a funcao auxiliar mergeSort dando o vetor a ordenar, cada um dos estremos e o ide. */
	printf("Encomenda %d\n", ide);
	for (i = 0; i < counter; i++){
		printf("* %s %d %d\n", dataBase[ide][tab_final[i]].Descricao, dataBase[ide][tab_final[i]].Preco, dataBase[ide][tab_final[i]].Quantidade);
	}
	return 0;
}

/* Esta funcao seleciona qual a acao a ser feita pelo programa */
int Selector() {
    int running = 1;
    char op;
    while (running == 1) { 
        op = getchar(); /* Obtenho o comando que o utilizador pretende usar */
        getchar();
        switch (op) {
            case 'a':
                novoProd();
                break;
            case 'q':
                adStock();
                break;
            case 'N':
                novaEnc();
                break;
            case 'A':
                adProd();
                break;
            case 'r':
                removeStock();
                break;
            case 'R':
                removeProd();
                break;
            case 'C':
                custoEnc();
                break;
            case 'p':
                alteraPreco();
                break;
            case 'E':
            	descQtd();
            	break;
           	case 'm':
           		identificadorMax();
           		break;
           	case 'l':
           		listaProd();
           		break;
           	case 'L':
           		listaProdEnc();
           		break;
            case 'x':
                running = 0;
                break;
        }
    }
    return 0;
}

/* A funcao main inicializa tanto o stock e a base de dados das encomendas
e depois corre a funcao Selector para correr o programa */
int main() {
	int i, e;
	for (i = 0; i < MAXprodutos; i++){
		strcpy(stock[i].Descricao, "");
		stock[i].Peso = 0;
		stock[i].Preco = 0;
		stock[i].Quantidade = 0;
	}
	for (i = 0; i < MAXenc; i++){
		for (e = 0; e < MAXpeso; e++){
			strcpy(dataBase[i][e].Descricao, "");
			dataBase[i][e].Preco = 0;
			dataBase[i][e].Peso = 0;
			dataBase[i][e].Quantidade = 0;
			dataBase[i][e].Inicia = -1;
		}
	}
	Selector();
	return 0;
}
