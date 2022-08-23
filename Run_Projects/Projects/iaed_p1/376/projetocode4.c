#include <stdio.h>
#include <string.h>

#define maxprod 10000
#define maxdescrip 63
#define maxenc 500


struct produto{
	/* Criacao de uma estrutura para os produtos */
	char descricao[maxdescrip];
	int preco, peso, quantidade;
};

struct produto p[maxprod];

struct encomenda{
	/* Criacao de uma estrutura para as encomendas */
	struct produto p[maxprod];
};

struct encomenda e[maxenc];

void addprod (int idp){
	/* Adiciona um produto ao sistema com descricao, preco, peso, quantidade */
	scanf(" %[^:]:%d:%d:%d", p[idp].descricao, &p[idp].preco, &p[idp].peso, &p[idp].quantidade);
	printf("Novo produto %d.\n", idp);
}

void addstock (int nprodutos){
	/* Adiciona stock a um produto no sistema */
	int quant, idprod;
	scanf(" %d:%d", &idprod, &quant);
	if (nprodutos > idprod) {
		p[idprod].quantidade = p[idprod].quantidade + quant;
	}	
	else 
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", idprod);
}

void newenco (int ide){
	/* Utilizado para criar uma nova encomenda */
	printf("Nova encomenda %d.\n", ide);
}

void addprodenc (int nencomendas, int nprodutos, int pesototalenc[maxenc], int nprodenc[maxenc]){
	/* Utiliza um produto do sistema e adiciona-o a uma encomenda. Se o produto ja exisitir apenas adiciona uma quantidade x ao produto da encomenda. Remove tambem certa quantidade do stock do sistema para por na encomenda */
	int idenc, idprod, quant;
	scanf(" %d:%d:%d", &idenc, &idprod, &quant);
	if (nencomendas <= idenc)
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idprod, idenc);
	else if (nprodutos <= idprod)
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idprod, idenc);
	else if (quant > p[idprod].quantidade)
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idprod, idenc);
	else if (pesototalenc[idenc] + p[idprod].peso * quant > 200)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idprod, idenc);
	else{
		if (e[idenc].p[idprod].preco == 0){
			nprodenc[idenc]++;
		}
	e[idenc].p[idprod].quantidade = e[idenc].p[idprod].quantidade + quant;
	p[idprod].quantidade = p[idprod].quantidade - quant;
	e[idenc].p[idprod].preco = p[idprod].preco;
	e[idenc].p[idprod].peso = p[idprod].peso;
	strcpy(e[idenc].p[idprod].descricao, p[idprod].descricao);
	pesototalenc[idenc] = pesototalenc[idenc] + (e[idenc].p[idprod].peso * quant);
	}	
}

void remstock (int nprodutos){
	/* Remove stock de um produto no sistema */
	int quant, idprod;
	scanf(" %d:%d", &idprod, &quant);	
	if (nprodutos <= idprod)
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", idprod);
	else if ((p[idprod].quantidade - quant) < 0)
		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quant, idprod);
	else{
		p[idprod].quantidade = p[idprod].quantidade - quant;
	}
}

void remprodenc (int nprodutos, int nencomendas, int pesototalenc[maxenc]){
	/* Remove um produto de uma encomenda pondo a sua quantidade a 0 */
	int idenc, idprod;
	scanf(" %d:%d:", &idenc, &idprod);
	if (nencomendas <= idenc)
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idprod, idenc);
	else if (nprodutos <= idprod)
		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idprod, idenc);
	else{
		pesototalenc[idenc] = pesototalenc[idenc] - (e[idenc].p[idprod].peso * e[idenc].p[idprod].quantidade);
		p[idprod].quantidade = p[idprod].quantidade + e[idenc].p[idprod].quantidade;
		e[idenc].p[idprod].quantidade = 0;
	}
}

void enccost (int nencomendas){
	/* Calcula o custo da encomenda percorrendo todos os seus produtos */
	int idenc, i;
	int custo = 0;
	scanf(" %d", &idenc);
	if (nencomendas <= idenc)
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", idenc);
	else{
		for (i = 0; i < maxprod; i++){
			if (e[idenc].p[i].preco > 0)
				custo = custo + (e[idenc].p[i].preco * e[idenc].p[i].quantidade);
		}
		printf("Custo da encomenda %d %d.\n", idenc, custo);
	}

}

void mudaprecoprod (int nprodutos, int nencomendas){
	/* Altera o preco de um produto no sistema e tambem altera o seu preco nas encomendas */
	int idprod, precop, x;
	scanf(" %d:%d:", &idprod, &precop);
	if (nprodutos <= idprod)
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idprod);
	else{
		p[idprod].preco = precop;
		for (x = 0; x < nencomendas; x++){
			e[x].p[idprod].preco = precop;
		}
	}
}

void descquant (int nencomendas, int nprodutos){
	/* Lista a descricao e quantitade de um produto numa encomenda */
	int idenc, idprod;
	scanf(" %d:%d:", &idenc, &idprod);
	if (nencomendas <= idenc)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",idenc);
	else if (nprodutos <= idprod)
		printf("Impossivel listar produto %d. Produto inexistente.\n",idprod);

	else
		printf("%s %d.\n", p[idprod].descricao, e[idenc].p[idprod].quantidade);
}

void prodocorremaisx (int nencomendas, int nprodutos){
	/* Verifica em que encomenda e que um certo produto ocorre mais vezes e lista o produto, a encomenda e a quantidade */
	int i, idprod, idenc;
	int maxtimes=0;
	scanf(" %d", &idprod);
	if (nprodutos <= idprod)
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", idprod);
	for (i=0; i<nencomendas; i++){
		if (e[i].p[idprod].quantidade > maxtimes){
			maxtimes = e[i].p[idprod].quantidade;
			idenc = i;
			}
	}
	if (maxtimes != 0)
		printf("Maximo produto %d %d %d.\n", idprod, idenc, maxtimes);

}

void mergepre(struct produto cp[maxprod] ,int s, int e){

	int mid = (s+e)/2;
	int i = s;
	int j = mid+1;
	int k = s;

	/* Cria um array temporario */
	struct produto atemp[maxprod];

	/* verifica qual o preco menor e adiciona ao array temporario */
	while (i <= mid && j <= e){
		if (cp[i].preco <= cp[j].preco)
			atemp[k++] = cp[i++];
		else
			atemp[k++] = cp[j++];
	}
	/* Acaba de passar o resto dos produtos da outra parte se uma das duas partes tiver acabado */
	while (i <= mid)
		atemp[k++] = cp[i++];
	while (j <= e)
		atemp[k++] = cp[j++];
	/* Passa de novo para cp os produtos ordenados do array temporario */
	for (j = s; j <= e; j++)
		cp[j] = atemp[j];
}

void mergesortpre (struct produto cp[maxprod] ,int s, int e){
	/* Separa o array em varios elementos para no final ficarem so 1 a 1 */
	int mid = (s+e)/2;
	/* Para se houverem 0 ou 1 elementos */
	if (s >= e)
		return;
	mergesortpre (cp, s, mid);
	mergesortpre (cp, mid+1, e);
	mergepre(cp, s, e);
}

void sortpreco (int nprodutos){
	/* Lista todos os produtos do sistema por ordem crescente de preco */
	int x, s, e;
	struct produto cp[maxprod];
	s = 0;
	e = nprodutos - 1; 
	/* Copia os produtos para outro array de estruturas */
	for (x = 0; x < nprodutos; x++){
 		cp[x] = p[x];
 	}
 	mergesortpre(cp, s, e);
 	printf("Produtos\n");
 	for (x = 0; x < nprodutos; x++){
 		printf("* %s %d %d\n",cp[x].descricao, cp[x].preco,cp[x].quantidade);
 	}
}

void mergealfa (struct produto cp[maxprod] ,int l, int r){
	int m = (l+r)/2;
  	int i, j, k;

  	/* Cria um array temporario */
  	struct produto atemp[maxprod];

  	/* verifica qual a string com valor menor e adiciona ao array temporario */
  	for (i = m+1; i > l; i--) 
    	atemp[i-1] = cp[i-1];
  	for (j = m; j < r; j++)
    	atemp[r+m-j] = cp[j+1];
  	for (k = l; k <= r; k++){
  		/* Passa de novo para cp os produtos ordenados do array temporario */
    	if (strcmp(atemp[j].descricao, atemp[i].descricao) < 0|| i > m)
      		cp[k] = atemp[j--];
    	else
      		cp[k] = atemp[i++];
    }

}

void mergesortalfa (struct produto cp[maxprod] ,int l, int r){
	/* Separa o array em varios elementos para no final ficarem so 1 a 1 */
	int mid = (l+r)/2;
	/* Para se houverem 0 ou 1 elementos */
	if (l >= r)
		return;
	mergesortalfa (cp, l, mid);
	mergesortalfa (cp, mid+1, r);
	mergealfa(cp, l, r);
}


void sortalfa (int nencomendas){
	/* Lista todos os produtos do sistema por ordem crescente de valor de string na descricao */
	int x, l, r, idenc;
	struct produto cp[maxprod];
	scanf(" %d", &idenc);
	l = 0;
	r = maxprod - 1; 

	if (nencomendas <= idenc)
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", idenc);

	/* Coloca os valores do array cp a 0 */
	else{
		for (x = 0; x < maxprod; x++){
			cp[x].preco = 0;
			cp[x].quantidade = 0;
		}
		/* Copia os produtos da encomenda para outro array de estruturas */
		for (x = 0; x < maxprod; x++){
			if (e[idenc].p[x].preco > 0){
 				cp[x] = e[idenc].p[x];
 			}
 		}
 		mergesortalfa(cp, l, r);
 		printf("Encomenda %d\n", idenc);
 		for (x = 0; x < maxprod; x++){
 			if (cp[x].quantidade > 0)
 				printf("* %s %d %d\n",cp[x].descricao, cp[x].preco,cp[x].quantidade);
 		}
 	}
}


int main (){
	int idp, ide, nencomendas, nprodutos;
	int nprodenc[maxenc] = {0};
	int pesototalenc[maxenc] = {0};
	char c;
	idp = 0;
	ide = 0;
	nencomendas = 0;
	nprodutos = 0;

	/* Vai buscar o primeiro caracter no input para escolher a funcao que se vai utilizar ate ler a letra x que ordena o final */
	c = getchar();
	while (c != 'x'){
		switch(c){

			case 'a':
				addprod(idp);
				idp++;
				nprodutos++;
				break;

			case 'q':
				addstock(nprodutos);
				break;

			case 'N':
				newenco(ide);
				ide++;
				nencomendas++;
				break;

			case 'A':
				addprodenc(nencomendas, nprodutos, pesototalenc,nprodenc);
				break;

			case 'r':
				remstock(nprodutos);
				break;

			case 'R':
				remprodenc(nprodutos, nencomendas, pesototalenc);
				break;

			case 'C':
				enccost(/*nprodenc*/ nencomendas);
				break;

			case 'p':
				mudaprecoprod (nprodutos, nencomendas);
				break;

			case 'E':
				descquant (nencomendas, nprodutos);
				break;

			case 'm':
				prodocorremaisx (nencomendas, nprodutos);
				break;

			case 'l':
				sortpreco (nprodutos);
				break;

			case 'L':
				sortalfa (nencomendas);
				break;
		}
		c = getchar();
	}
	return 0;
}