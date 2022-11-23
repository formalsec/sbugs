#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define MAX_PRODUTOS 10000
#define MAX_ENCOMENDAS 500
#define MAX_PESO 200

/*contadores de produtos e encomendas nos sistemas*/
int numProduto = 0, numEnc = 0;

typedef struct produto{
	int identificador, preco, peso, quantidade;
	char descricao[63];
} Produto;

Produto sistemaPro[MAX_PRODUTOS] = {0};

typedef struct encomenda{
	int identificador, peso;
	Produto produtos[MAX_PESO];
} Encomenda;

Encomenda sistemaEnc[MAX_ENCOMENDAS] = {0};

/*funcao auxiliar para ver os produtos no sistema em forma de tabela*/
void listaProdutos(){
	int i, a=0, b=0, c=0, d=0, e=0, max_ind=1, max_desc=1, max_preco=1, max_peso=1, max_quant=1, number, len_str, contador=0; 
	/*ciclo que vai ver os maiores numeros de cada categoria para dar o espaco adequado*/
	for(i = 0; i < numProduto;  ++i){
		len_str = strlen(sistemaPro[i].descricao);
		if(len_str > max_desc) max_desc = len_str;

		while(a < 4) {
			if(a==0) number = sistemaPro[i].identificador;
			if(a==1) number = sistemaPro[i].preco;
			if(a==2) number = sistemaPro[i].peso;
			if(a==3) number = sistemaPro[i].quantidade;
		    while(number != 0){
				number = number / 10;
				contador++;
			}
			if(a==0){
				if(contador > max_ind) max_ind = contador;
				contador = 0;
			}else if(a==1){
				if(contador > max_preco) max_preco = contador;
				contador = 0;
			}else if(a==2){
				if(contador > max_peso) max_peso = contador;
				contador = 0;
			}else if(a==3){
				if(contador > max_quant) max_quant = contador;
				contador = 0;
			}
			a++;
		}
		a = 0;
	}
	/*ciclo que constroi a tabela com os produtos*/
	for(i = 0; i < numProduto;  ++i){
		printf("\n| %d\t", i);
		while(a < max_ind) {
		    printf(" ");
		    a++;
		}
		a=0;
		if(strlen(sistemaPro[i].descricao) < 5){
			printf("| %s\t\t", sistemaPro[i].descricao);
		}else printf("| %s\t", sistemaPro[i].descricao);
		while(b < max_desc) {
		    printf(" ");
		    b++;
		}
		b=0;
		printf("| %d\t", sistemaPro[i].preco);
		while(c < max_preco) {
		    printf(" ");
		    c++;
		}
		c=0;
		printf("| %d\t", sistemaPro[i].peso);
		while(d < max_peso) {
		    printf(" ");
		    d++;
		}
		d=0;
		printf("| %d\t", sistemaPro[i].quantidade);
		while(e < max_quant) {
		    printf(" ");
		    e++;
		}
		e=0;
		printf("|\n");
	}
	return;
}

/*funcao auxiliar que mostra os produtos de uma certa encomenda em lista*/
void listaEncomenda(){
	int idEnc_Lst, i = 0;
	scanf(" %d", &idEnc_Lst);
	/*verifica se ha produtos na encomenda*/
	if(!strcmp(sistemaEnc[idEnc_Lst].produtos[i].descricao, "")){
		printf("Nao existem produtos na encomenda.\n");
		return;
	}
	printf("Encomenda %d:\nPeso total: %d\n", idEnc_Lst, sistemaEnc[idEnc_Lst].peso);

	while(i < MAX_PESO){
		if(!strcmp(sistemaEnc[idEnc_Lst].produtos[i].descricao, "")) break;
		printf("%d: %s:%d:%d:%d\n", sistemaEnc[idEnc_Lst].produtos[i].identificador, sistemaEnc[idEnc_Lst].produtos[i].descricao,sistemaEnc[idEnc_Lst].produtos[i].preco, sistemaEnc[idEnc_Lst].produtos[i].peso, sistemaEnc[idEnc_Lst].produtos[i].quantidade);
		i++;
	}
	return;
}

/*funcao que adiciona um produto ao sistema de produtos*/
void adicionaProduto(){
	sistemaPro[numProduto].identificador = numProduto;
	scanf(" %[^:]s", sistemaPro[numProduto].descricao);
	scanf(":%d:%d:%d", &sistemaPro[numProduto].preco, &sistemaPro[numProduto].peso, &sistemaPro[numProduto].quantidade);
	printf("Novo produto %d.\n", numProduto);
	numProduto++;
	return;
}

/*funcao que adiciona ou retira quantidade do sistema de um certo produto*/
/*a funcao decide se adiciona ou retira consoante o seu argumento*/
void stock(int a){
	int idStock = 0, quantidadeStock = 0;
	scanf(" %d:%d", &idStock, &quantidadeStock);
	/*verifica se o produto existe*/
	if(idStock < numProduto){
		if(a){
			sistemaPro[idStock].quantidade += quantidadeStock;
		}else if(quantidadeStock <= sistemaPro[idStock].quantidade){
			sistemaPro[idStock].quantidade -= quantidadeStock;
		}else printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", quantidadeStock, idStock);
	} else if(a){
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idStock);
	}else printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idStock);
	return;
}

/*funcao que cria uma nova encomenda*/
void criaEncomenda(){
	sistemaEnc[numEnc].identificador = numEnc;
	printf("Nova encomenda %d.\n", numEnc);
	numEnc++;
	return;
}

/*funcao que adiciona um certo produto do sistema de produtos a uma certa encomenda */
void adicionaEncomenda(){
	int idPro_Ad = 0, idEnc_Ad = 0, quantidadeAd = 0, i, pesoTotal;
	scanf(" %d:%d:%d", &idEnc_Ad, &idPro_Ad, &quantidadeAd);
	pesoTotal = sistemaEnc[idEnc_Ad].peso + sistemaPro[idPro_Ad].peso * quantidadeAd;
	/*verifica se existe a encomenda, se existe o produto, se existe a quantidade em stock e se nao e excedido o peso maximo*/
	if(idEnc_Ad < numEnc){
		if(idPro_Ad < numProduto){
			if(quantidadeAd <= sistemaPro[idPro_Ad].quantidade){
				if(pesoTotal <= MAX_PESO){
					for(i = 0;  i < MAX_PESO;  ++i){
						/*se o produto ainda nao existir na encomenda vai ser adicionado a um novo espaco*/
						if(!strcmp(sistemaEnc[idEnc_Ad].produtos[i].descricao, "")){
							/*adiciona o produto na encomenda e retira a quantidade do stock*/
							sistemaEnc[idEnc_Ad].peso += sistemaPro[idPro_Ad].peso * quantidadeAd;
							sistemaEnc[idEnc_Ad].produtos[i].identificador = idPro_Ad;
							sistemaEnc[idEnc_Ad].produtos[i].preco = sistemaPro[idPro_Ad].preco;
							sistemaEnc[idEnc_Ad].produtos[i].peso = sistemaPro[idPro_Ad].peso;
							sistemaEnc[idEnc_Ad].produtos[i].quantidade = quantidadeAd;
							sistemaPro[idPro_Ad].quantidade -= quantidadeAd;
							strcpy(sistemaEnc[idEnc_Ad].produtos[i].descricao, sistemaPro[idPro_Ad].descricao);
							break;
						/*se o produto ja existir apenas adicionamos a quantidade, aumentando o peso e retirando do stock*/
						}else if(!strcmp(sistemaPro[idPro_Ad].descricao, sistemaEnc[idEnc_Ad].produtos[i].descricao) && idPro_Ad == sistemaEnc[idEnc_Ad].produtos[i].identificador){
							sistemaEnc[idEnc_Ad].peso += sistemaPro[idPro_Ad].peso * quantidadeAd;
							sistemaEnc[idEnc_Ad].produtos[i].quantidade += quantidadeAd;
							sistemaPro[idPro_Ad].quantidade -= quantidadeAd;
							break;
						}
					}
				}else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idPro_Ad, idEnc_Ad);
			}else printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idPro_Ad, idEnc_Ad);
		}else printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idPro_Ad, idEnc_Ad);
	}else printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idPro_Ad, idEnc_Ad);
	return;
}

/*funcao que remove um certo produto de uma certa encomenda*/
void removeProduto(){
	int idPro_Rm = 0, idEnc_Rm = 0, i;
	scanf(" %d:%d", &idEnc_Rm, &idPro_Rm);
	/*verifica se o produto e a encomenda existem*/
	if(idEnc_Rm < numEnc){
		if(idPro_Rm < numProduto){
			/*ciclo que procura o produto na encomenda*/
			for(i = 0; i < MAX_PESO;  ++i){
				/*se encontrarmos vamos retirar o peso da enomenda e adicionar a quantidade ao stock*/
				if(!strcmp(sistemaPro[idPro_Rm].descricao, sistemaEnc[idEnc_Rm].produtos[i].descricao) && idPro_Rm == sistemaEnc[idEnc_Rm].produtos[i].identificador){
					sistemaEnc[idEnc_Rm].peso -= sistemaEnc[idEnc_Rm].produtos[i].peso * sistemaEnc[idEnc_Rm].produtos[i].quantidade;
					sistemaPro[idPro_Rm].quantidade += sistemaEnc[idEnc_Rm].produtos[i].quantidade;
					/*reorganizamos os produtos na encomenda para melhor eficacia*/
					while(i < MAX_PESO) {
						if(!strcmp(sistemaEnc[idEnc_Rm].produtos[i].descricao, "")) break;
					    sistemaEnc[idEnc_Rm].produtos[i] = sistemaEnc[idEnc_Rm].produtos[i+1];
					    i++;
					}
					return;
				}
			}
		}else printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idPro_Rm, idEnc_Rm);
	}else printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idPro_Rm, idEnc_Rm);
	return;
}

/*funcao que calcula o preco total de uma certa encomenda*/
void calculaTotal(){
	int idEnc_Cal = 0, precoTotal = 0, i;
	scanf(" %d", &idEnc_Cal);
	/*verifica se a encomenda existe*/
	if(idEnc_Cal < numEnc){
		/*ciclo que procura o produto e adiciona ao preco total*/
		for(i = 0; i < MAX_PESO;  ++i){
			if(!strcmp(sistemaEnc[idEnc_Cal].produtos[i].descricao, "")) break;
			precoTotal += sistemaEnc[idEnc_Cal].produtos[i].preco * sistemaEnc[idEnc_Cal].produtos[i].quantidade;
		}
		printf("Custo da encomenda %d %d.\n", idEnc_Cal, precoTotal);
	}else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idEnc_Cal);
	return;
}

/*funcao que altera o preco de um certo produto*/
void alteraPreco(){
	int idPro_Alt = 0, novoPreco = 0, i, j;
	scanf(" %d:%d", &idPro_Alt, &novoPreco);
	/*verifica se o produto existe e se sim modifica o preco no sistema de produtos*/
	if(idPro_Alt < numProduto){
		sistemaPro[idPro_Alt].preco = novoPreco;
		/*ciclo que percorre todas as encomendas*/
		for(i = 0;  i < numEnc;  ++i){
			/*ciclo que procura o produto j na encomenda i para alterar o preco tambem na encomenda*/
			for(j = 0;  j < MAX_PESO;  ++j){
				if(!strcmp(sistemaEnc[i].produtos[j].descricao, "")) break;
				if(idPro_Alt == sistemaEnc[i].produtos[j].identificador){
					sistemaEnc[i].produtos[j].preco = novoPreco;
					break;
				}
			}
		}
	}else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idPro_Alt);
	return;
}

/*funcao que mostra dados de um certo produto numa certa encomenda */
void mostraProduto(){
	int idEnc_Um = 0, idPro_Um = 0, i;
	scanf(" %d:%d", &idEnc_Um, &idPro_Um);
	/*verifica se a encomenda e o produto existem*/
	if(idEnc_Um < numEnc){
		if(idPro_Um < numProduto){
			/*ciclo que procura o produto na encomenda*/
			for(i = 0; i < MAX_PESO;  ++i){
				if(!strcmp(sistemaEnc[idEnc_Um].produtos[i].descricao, "")){
					printf("%s 0.\n", sistemaPro[idPro_Um].descricao);
					break;
				}
				if(idPro_Um == sistemaEnc[idEnc_Um].produtos[i].identificador){
					printf("%s %d.\n", sistemaEnc[idEnc_Um].produtos[i].descricao, sistemaEnc[idEnc_Um].produtos[i].quantidade);
					break;
				}
			}
		}else printf("Impossivel listar produto %d. Produto inexistente.\n", idPro_Um);
	}else printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEnc_Um);
	return;
}

/*funcao que lista o identificador da encomenda em que um certo produto ocorre mais vezes */
void maxOcorrencia(){
	int idPro_Dois = 0, maxQnt = 0, maxEnc = 0,contador, i, j;
	scanf(" %d", &idPro_Dois);
	/*verifica se o produto existe*/
	if(idPro_Dois < numProduto){
		/*ciclo que percorre as encomendas*/
		for(i = 0; i < numEnc;  ++i){
			contador = 0;
			/*ciclo que procura o prduto j na encomenda i e conta o numero de ocorrencias desse produto*/
			for(j = 0; j < MAX_PESO;  ++j){
				if(!strcmp(sistemaEnc[i].produtos[j].descricao, "")) break;
				if(idPro_Dois == sistemaEnc[i].produtos[j].identificador){
					contador += sistemaEnc[i].produtos[j].quantidade;
				}
			}
			/*verifica se o numero de ocorrencias do produto j na encomenda i e o novo maximo de ocorrencias*/
			if(contador >= maxQnt){
				/*em caso de empate predomina o identificador*/
				if(contador == maxQnt){
					if(i < maxEnc){
						maxEnc = i;
					}
				}else{
					maxQnt = contador;
					maxEnc = i;
				}
			}
		}
		if(maxQnt && (maxEnc < numEnc)) printf("Maximo produto %d %d %d.\n", idPro_Dois, maxEnc, maxQnt);
	}else printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idPro_Dois);
	return;
}
/*segunda etapa do algoritmo merge sort
devolve um vector ordenado em l e r dados dois vectores ordenados
em l e m e em m+1 e r, para isso usamos um vector auxiliar*/
void merge(Produto aux[], Produto a[], int l, int m, int r, int tipo){
	int i, j, k;
	/*os dois primeiros ciclos constroem o vector auxiliar */
	for(i = m+1; i > l; i--){
		aux[i-1] = a[i-1];
	}
	for(j = m; j < r; j++){
		aux[r+m-j] = a[j+1];
	}
	/*a variavel tipo vai no indicar se queremos ordenar a lista de produtos no sistema ou numa enomenda*/
	if(tipo){
		/*ordena por ordem alfabetica*/
		for(k = l; k <= r; k++){
			if(strcmp(aux[j].descricao, aux[i].descricao) < 0){
				a[k] = aux[j--];
			}else a[k] = aux[i++];
		}
	}else {
		/*ordena por ordem crescente de preco*/
		for(k = l; k <= r; k++){
			if(aux[j].preco < aux[i].preco){
				a[k] = aux[j--];
			}else if(aux[j].preco == aux[i].preco){
				if(aux[j].identificador < aux[i].identificador){
					a[k] = aux[j--];
				} else a[k] = aux[i++];
			} else a[k] = aux[i++];
		}
	}
}

/*primeira etapa do algoritmo merge sort
nesta primeira etapa o algoritmo comeca por dividir a meio o array que lhe foi dado como argumento
(dentro dos limites l e r), esta divisao e feita de forma recursiva e e feita ate obtermos vetores 
com um so elemento. Notar que os argumentos tipo e aux apenas vao servir para a proxima etapa do merge*/
void mergesort(Produto aux[], Produto a[], int l, int r, int tipo){
	int m = (r+l)/2;
	if(r <= l) return;
	mergesort(aux, a, l, m, tipo);
	mergesort(aux, a, m+1, r, tipo);
	merge(aux, a, l, m, r, tipo);
}

/*funcao que lista todos os produtos existentes no sistema por ordem crescente de preco*/
void sortProdutos(){
	int i;
	Produto newArray[MAX_PRODUTOS], aux[MAX_PRODUTOS];
	/*faz uma copia dos produtos no sistema*/
	for(i = 0; i < numProduto; ++i){
		newArray[i] = sistemaPro[i];
	}
	/*ordena com o algoritmo merge sort*/
	mergesort(aux, newArray, 0, numProduto-1, 0);
	printf("Produtos\n");
	for(i = 0; i < numProduto;  ++i){
		printf("* %s %d %d\n", newArray[i].descricao, newArray[i].preco, newArray[i].quantidade);
	}
}

/*funcao que lista todos os produtos de uma certa encomenda por ordem alfabetica de descricao*/
void sortEncomenda(){
	int i, idEnc_Sort = 0, a = 0;
	Produto newArray[MAX_PESO], aux[MAX_PESO];
	scanf(" %d", &idEnc_Sort);
	/*verifica se a encomenda existe*/
	if(idEnc_Sort >= numEnc){
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idEnc_Sort);
		return;
	}
	/*faz uma copia dos produtos na encomenda*/
	for(i = 0; i < MAX_PESO;  ++i){
		if(!strcmp(sistemaEnc[idEnc_Sort].produtos[i].descricao, "")) break;
		newArray[i] = sistemaEnc[idEnc_Sort].produtos[i];
		a = i;
	}
	/*verifica se a encomenda esta vazia*/
	if(!strcmp(sistemaEnc[idEnc_Sort].produtos[0].descricao, "")){
		printf("Encomenda %d\n", idEnc_Sort);
		return;
	}
	printf("Encomenda %d\n", idEnc_Sort);
	/*ordena com o algoritmo merge sort*/
	mergesort(aux, newArray, 0, a, 1);
	for(i = 0; i <= a;  ++i){
		printf("* %s %d %d\n", newArray[i].descricao, newArray[i].preco, newArray[i].quantidade);
	}
}

int main(){
	char c;
	while(1){
		/*menu de comandos do sistema de logistica*/
		switch(c=getchar()){
			case 'k':
				listaProdutos();
				break;
			case 'a':
				adicionaProduto();
				break;;
			case 'q':
				stock(1);
				break;
			case 'N':
				criaEncomenda();
				break;
			case 'K':
				listaEncomenda();
				break;
			case 'A':
				adicionaEncomenda();
				break;
			case 'r':
				stock(0);
				break;
			case 'R':
				removeProduto();
				break;
			case 'C':
				calculaTotal();
				break;
			case 'p':
				alteraPreco();
				break;
			case 'E':
				mostraProduto();
				break;
			case 'm':
				maxOcorrencia();
				break;
			case 'l':
				sortProdutos();
				break;
			case 'L':
				sortEncomenda();
				break;
			case 'x':
				return 0;
			case '\n':
				break;
			default:
				printf("Este comando n?o existe.\n");
				break;
			}
	}
	return 0;
}