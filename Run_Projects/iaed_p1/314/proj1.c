#include <stdio.h>
#include <string.h>
#define MAXDES 63 /*numero maximo de caracteres na descricao*/
#define MAXPROD 10000 /*numero maximo de produtos*/
#define MAXENC 500 /*numero maximo de encomendas*/
#define MAXPESO 200 /*peso maximo de uma encomenda*/
typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))


typedef struct{

	int idproduto; /*numero de identificacao do produto*/
	char desc[MAXDES]; /*descricao*/
	int preco;
	int peso;
	int quantidade;

} produto;

typedef struct{

	int idproduto; /*numero de identificacao do produto*/
	int preco;

} copia;


produto sistema[MAXPROD]; /*vetor de produtos correspondente ao armazem/sistema */
produto encomendas[MAXENC][MAXPROD]; /*vetor onde vao ser colocadas todas as encomendas*/
int indice[MAXENC]; /*vetor onde vao ser guardados os indices do produto em que me encontro numa dada encomenda*/
int enccounter; /*contador de encomendas*/
int sistcounter; /*contador de produtos*/
copia aux[MAXPROD];/*vetor auxiliar usado para ordenar os precos*/
copia sistema_sort[MAXPROD];/*copia do vetor sistema, usada para ordenar os precos*/


void le_linha_caracteres(char v[], int max);
int le_linhas_numeros();
void adiciona_produto();
void adiciona_stock();
void cria_nova_encomenda();
int peso_encomenda(int num_encomenda);
void indice_inicio();
int verifica_encomenda(produto v[], int idp, int ide);
void adiciona_produto_encomenda();
void remove_stock();
void remove_produto();
void calcula_custo();
void altera_preco();
void lista_desc_quantidade();
void indentificador_encomenda();
void merge(copia a[], int l, int m, int r);
void mergesort(copia a[], int l, int r);
void insertionSort(copia v[], int n);
void lista_produtos();
void lista_produtos_encomenda();


int main(){

	int cmd;

	indice_inicio();

	while((cmd = getchar()) != 'x'){
		switch(cmd){
			case 'a':
				adiciona_produto();
				break;
			case 'q':
				adiciona_stock();
				break;
			case 'N':
				cria_nova_encomenda();
				break;
			case 'A':
				adiciona_produto_encomenda();
				break;
			case 'r':
				remove_stock();
				break;
			case 'R':
				remove_produto();
				break;
			case 'C':
				calcula_custo();
				break;
			case 'p':
				altera_preco();
				break;
			case 'E':
				lista_desc_quantidade();
				break;
			case'm':
				indentificador_encomenda();
				break;
			case 'l':
				lista_produtos();
				break;
			case 'L':
				lista_produtos_encomenda();
				break;


		}
	}


	return 0;

}

/*Le uma linha de caracteres*/
void le_linha_caracteres(char v[], int max){

	char c;
	int i = 0;


	while((c = getchar()) != '\n' && c != EOF && i < max - 1 && c != ':'){
		if( c == ' ')/*Se o caracter for um espaco em branco o ciclo ignora e depois continua*/
			continue;
		else
			v[i] = c;
		i++;

	}
	v[i] = '\0';
}

/*Le uma linha de numeros*/
int le_linhas_numeros(){

	char c;
	int res = 0;

	while((c = getchar()) != '\n' && c != EOF &&  c != ':')

		if(c == ' ')
			continue;
		else
			res = res*10 + (c - '0');

	return res;
}

/*Adiciona um produto ao sistema*/
void adiciona_produto(){


	le_linha_caracteres(sistema[sistcounter].desc, MAXDES);
	sistema[sistcounter].preco = le_linhas_numeros();
	sistema[sistcounter].peso = le_linhas_numeros();
	sistema[sistcounter].quantidade = le_linhas_numeros();

	printf("Novo produto %d.\n", sistcounter);

	sistcounter++;

}

/*adiciona stock ao sistema*/
void adiciona_stock(){

	int idp, qtd;


	idp = le_linhas_numeros();


	if(idp < sistcounter){

		qtd = le_linhas_numeros();
		sistema[idp].quantidade = sistema[idp].quantidade + qtd;
	}
	else 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idp);

}

/*Cria uma nova encomenda*/
void cria_nova_encomenda(){

	printf("Nova encomenda %d.\n", enccounter);
	enccounter++;
}

/*Determina o peso de uma encomenda*/
int peso_encomenda(int num_encomenda){

	int i, res = 0;

	for(i = 0; i < indice[num_encomenda]; i++){

		res = res + encomendas[num_encomenda][i].peso*encomendas[num_encomenda][i].quantidade;
	}

	return res;

}
/*Coloca zero em todas as entradas do vetor*/
void indice_inicio(){

	int i = 0;

		for(i = 0; i < MAXENC; i++)
			indice[i] = 0;	
	
}

/*Retorna o indice em que o produto se encontra na encomenda passada por argumento*/
int verifica_encomenda(produto v[], int idp, int ide){

	int i;

	for(i = 0; i < indice[ide] ; i++){
		if(v[i].idproduto == idp && v[i].peso == sistema[idp].peso && v[i].preco == sistema[idp].preco)
			break;
	}
			
	return i;
}

/*Adiciona um produto a uma encomenda*/
void adiciona_produto_encomenda(){

	int ide, idp, qtd, i1, peso;
	

	ide = le_linhas_numeros();
	idp = le_linhas_numeros();
	qtd = le_linhas_numeros();

	if(ide < enccounter){/*Verifica se a encomenda existe*/

		if(idp < sistcounter){/*Verifica se o produto existe*/

			if(qtd <= sistema[idp].quantidade){/*Verifica se existe stock suficiente*/

				peso = peso_encomenda(ide);

				

				if(peso + qtd*sistema[idp].peso <= MAXPESO){/*Verifica  se o peso da encomenda nao o excede o peso maximo*/

					i1 = verifica_encomenda(encomendas[ide], idp, ide);
					

					

					if(indice[ide] == i1){

						encomendas[ide][indice[ide]].quantidade = qtd;
						encomendas[ide][indice[ide]].idproduto = idp;
						encomendas[ide][indice[ide]].peso = sistema[idp].peso;
						encomendas[ide][indice[ide]].preco = sistema[idp].preco;
						strcpy(encomendas[ide][indice[ide]].desc, sistema[idp].desc);
						indice[ide]++;

					

					}
					else
						encomendas[ide][i1].quantidade = encomendas[ide][i1].quantidade + qtd;

					sistema[idp].quantidade = sistema[idp].quantidade -qtd;

				}

				else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
			}
			else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);

	}
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);

}

/*Remove stock a um produto do sistema*/
void remove_stock(){

	int idp, qtd;

	idp = le_linhas_numeros();
	qtd = le_linhas_numeros();

	if(idp < sistcounter){
		if(sistema[idp].quantidade - qtd >= 0)

			sistema[idp].quantidade = sistema[idp].quantidade - qtd;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);


	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
}

/*Remove um produto de uma encomenda, trocando o produto que se quer remover com o ultimo produto, de forma a manter o vetor sem buracos*/
void remove_produto(){

	int ide, idp, i;

	ide = le_linhas_numeros();
	idp = le_linhas_numeros();

	if(ide < enccounter){

		if(idp < sistcounter){

			i = verifica_encomenda(encomendas[ide], idp, ide);

			if(i >= 0 && i< indice[ide]){/*Para evitar que o indice fique negativo quando se tenta retirar um produto que nao existe na encomenda*/
				indice[ide]--;

				if(i != indice[ide]){/*Caso o produto nao seja o ultimo elemento no vetor, efetua se a troca entre os dois produtos em questao*/

					sistema[idp].quantidade = sistema[idp].quantidade + encomendas[ide][i].quantidade;
					encomendas[ide][i].idproduto = encomendas[ide][indice[ide]].idproduto;
					strcpy(encomendas[ide][i].desc, encomendas[ide][indice[ide]].desc);
					encomendas[ide][i].preco = encomendas[ide][indice[ide]].preco;
					encomendas[ide][i].peso = encomendas[ide][indice[ide]].peso;
					encomendas[ide][i].quantidade = encomendas[ide][indice[ide]].quantidade;


				}
				else if(i == indice[ide])/*No caso de ser o ultimo elemento apenas reponho a quantidade ao sistema*/
					sistema[idp].quantidade = sistema[idp].quantidade + encomendas[ide][i].quantidade;

			}


		}
		else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
}

/*Calcula o custo de uma encomenda*/
void calcula_custo(){

	int ide, total = 0, i;

	ide = le_linhas_numeros();

	if(ide < enccounter){

		for(i = 0; i < indice[ide]; i++){

			total = total + encomendas[ide][i].preco * encomendas[ide][i].quantidade;
		}

		printf("Custo da encomenda %d %d.\n", ide, total);

	}

	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
		
}

/*Altera o preco de um produto existente no sistema*/
void altera_preco(){

	int idp, preco, i, j;

	idp = le_linhas_numeros();
	preco = le_linhas_numeros();

	if(idp < sistcounter){

		sistema[idp].preco = preco;

		for(i = 0; i < enccounter; i++){

			for(j = 0; j < indice[i]; j++)

				if(encomendas[i][j].idproduto == idp)

					encomendas[i][j].preco = preco; 
		}


	}

	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);

}

/*Retorna a descri??o e a quantidade de um produto numa dada encomenda*/
void lista_desc_quantidade(){

	int ide, idp, i;

	ide = le_linhas_numeros();
	idp = le_linhas_numeros();

	if(ide < enccounter){

		if(idp < sistcounter){

			i = verifica_encomenda(encomendas[ide], idp, ide);

			if(i >= 0 && i < indice[ide])
				printf("%s %d.\n", encomendas[ide][i].desc, encomendas[ide][i].quantidade);
			else
				printf("%s 0.\n",sistema[idp].desc);/*Se o produto nao existir na encomenda, a funcao retorna a sua descricao e 0 na quantidade*/

		}

		else
			printf("Impossivel listar produto %d. Produto inexistente.\n", idp);
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
	
}

/*Retorna o identificador da encomenda em que um dado produto ocorre mais vezes, utilizando para isso um maximo que guarda a maior
 quantidade desse produto*/
void indentificador_encomenda(){

	int idp, ide, i, j, max = -1, counter = 0;

	idp = le_linhas_numeros();

	if(idp < sistcounter){

		for(i = 0; i < enccounter; i++){

				for(j = 0; j < indice[i]; j++){

					if(encomendas[i][j].idproduto == idp && encomendas[i][j].quantidade > max){

						max = encomendas[i][j].quantidade;
						ide = i;
						counter++;
					}
				}
		}

		if(counter > 0)
			printf("Maximo produto %d %d %d.\n", idp, ide, max);

	}

	else 
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);

}

/*Ordena os produtos por preco, e visto ser estavel, se os precos forem iguais o que tiver menor identificador vem primeiro */
void merge(copia a[], int l, int m, int r){

	int i, j, k;
	

	for(i = m + 1;i > l;i--){
		aux[i - 1].preco = a[i - 1].preco;
		aux[i - 1].idproduto = a[i - 1].idproduto;
	}

	for(j = m;j < r;j++){
		aux[r + m - j].preco = a[j + 1].preco;
		aux[r + m - j].idproduto = a[j + 1].idproduto;
	}

	for(k = l; k <= r;k++){
		if(less(aux[j].preco, aux[i].preco )|| i > m){
			
			a[k].preco = aux[j].preco;
			a[k].idproduto = aux[j].idproduto;
			j--;
		}
	
		else if(aux[j].preco >= aux[i].preco){

			a[k].preco = aux[i].preco;
			a[k].idproduto = aux[i].idproduto;
			i++;
		}
			
	}

}

void mergesort(copia a[], int l, int r){

	int m = (r + l)/2;
	if(r <= l)
		return;
	mergesort(a, l, m);
	mergesort(a, m + 1, r);
	merge(a, l, m, r);

}

/*Lista todos os produtos existentes no sistema por ordem crescente de pre?o*/
void lista_produtos(){

	int i;

	for(i = 0;i < sistcounter;i++){

		sistema_sort[i].idproduto = i;
		sistema_sort[i].preco = sistema[i].preco;
		
	}

	mergesort(sistema_sort,0,sistcounter - 1);

	printf("Produtos\n");


	for(i = 0;i < sistcounter;i++){

		printf("* %s %d %d\n", sistema[sistema_sort[i].idproduto].desc, sistema[sistema_sort[i].idproduto].preco, sistema[sistema_sort[i].idproduto].quantidade);
	}


}

/*Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o*/
void lista_produtos_encomenda(){

	int ide, i, j, x, menor;
	char descricao[MAXPROD][MAXDES], aux[MAXPROD];

	ide = le_linhas_numeros();

	if(ide < enccounter){

		for(i = 0; i < indice[ide];i++){
			
				strcpy(descricao[i], encomendas[ide][i].desc);
			
		}
		printf("Encomenda %d\n", ide);
   
        for(i = 0; i < indice[ide] - 1; i++){
                x = 0;
                menor = i;
                for(j = i + 1; j < indice[ide]; j++){
                    x = 0;
                    while(descricao[menor][x] == descricao[j][x]){
                            x++;
                    } 

                    if(descricao[menor][x] > descricao[j][x]){
                         menor = j;
                    }
                }
                if(menor != i){

                        strcpy(aux, descricao[menor]);
                        strcpy(descricao[menor], descricao[i]);
                        strcpy(descricao[i], aux);
                }
        }

        for(i = 0; i < indice[ide];i++){
        	for(j = 0;j < indice[ide];j++){

        		if(strcmp(descricao[i], encomendas[ide][j].desc) == 0)

        			printf("* %s %d %d\n",encomendas[ide][j].desc, encomendas[ide][j].preco, encomendas[ide][j].quantidade);
        	}
        }


	}

	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);

}