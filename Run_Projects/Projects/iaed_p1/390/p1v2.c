#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRMAX 63 /*tamanho maximo da string descricao*/
#define SYSMAX 10000 /*no. maximo de produtos*/
#define SYSEMAX SYSMAX+1 /*devido a um tecnicalidade na criacao de uma nova encomenda a primeira posicao do carrinho da encomenda e invalida e portanto compensamos com o limite superior*/
#define ENCMAX 500 /*no. max de produtos*/
#define PESOMAX 200 /*peso maximo definido para cada encomenda*/
/* Tipo de estrutura representativa de um produto*/
typedef struct produto{
	int idp, preco, peso, qd;
	char desc[STRMAX];
}Pro;
/*o tipo de dados encomenda tem um carrinho com os dados dos produtos encomendados e um contador dos mesmos (prods)*/
typedef struct encomenda{
	Pro carr[SYSEMAX];
	int prods;
}Enc;
int idp=0, ide=0, aux[SYSMAX][2]; /*id do produto, que e sequencial segundo a adicao de novos produtos*/
Pro sys[SYSMAX]; /*vetor que representa o sistema com dados do tipo produto*/
Enc cli[ENCMAX]; /* ''  ''     ''       a lista de encomendas*/
/*elimin espacos de strings*/
/*verifica se o id de certa encomenda ? v?lido*/
int eh_enc(int id_enc){
	return (id_enc<ide);
}
int eh_pro(int id_pro){
	return (id_pro<idp);
}
/*encontra produtos numa encomenda com certo idp e retorna o seu ?ndice, caso nao exista tal produto*/
void pro_in_enc(int id_enc, int id_pro, int a){
	int i;
	for (i=0; i<SYSMAX; i++){
		if (cli[id_enc].carr[i].idp == id_pro){
			a=i;
			a++;
			a--;
			return;
		}
	}
}
/*devolve 1 ou 'true' de houver certo produto na encomenda indicada e 0 ou 'false' caso contr?rio*/
int ah_pro_in_enc(int id_enc, int id_pro){
	int i;
	for (i=0; i<SYSMAX; i++){
		if (cli[id_enc].carr[i].idp == id_pro) return 1;
	}
	return 0;
}
/*acede a certo slot de produto numa encomenda (mitiga expressoes longas desnecessarias0)*/
Pro access_enc_pro(int id_enc, int id_pro){
	int a=0;
	pro_in_enc(id_enc, id_pro, a);
	return cli[id_enc].carr[a];
} 
/*funcao que lista todos os produtos em stock sem ordenacao (para debug)*/
void __k__(){
	int i;
	printf("Produtos\n");
	for (i=0; i<idp;i++) printf("%s %d %d\n", sys[i].desc, sys[i].preco, sys[i].qd);
	return;
}
/*funcao chamada apos o uso do comando 'a' pelo utilizador*/
void __a__(){
	Pro p;
	int preco, peso, qd, i;
	char desc[STRMAX];
	scanf("%[^:]:%d:%d:%d", desc, &preco, &peso, &qd);
	strcpy(p.desc, desc);
	p.idp = idp;
	p.preco = preco;
	p.peso = peso;
	p.qd = qd;
	sys[idp] = p;
	for (i=0; i<STRMAX;i++) /*para resolver problema em que strings tinham um espaco vazio antes dos caracterres relevantes*/
		p.desc[i] = p.desc[i-1];
	printf("Novo produto %d.\n", idp++);
	return;
}
/*adiciona stock (qd) a um produto existento no sistema*/
void __q__(){
	int id_pro, qd;
	scanf("%d:%d", &id_pro, &qd);
	if (id_pro<idp) sys[id_pro].qd += qd;
	else printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", id_pro);
	return;
}
/* cria nova entidade encomenda. Devido a warnings em que e tinham<< de ser inicializado de alguma forma, cria-se um prodtuo no indice -1 servindo como null*/
void __N__(){
	if (ide<ENCMAX){
		Enc e;
		e.carr[-1].qd = 0; /*pq*/
		e.carr[-1].peso = 0;
		e.carr[-1].preco = 0;
		e.carr[-1].idp = 0;
		e.carr[-1].desc[0] = '0';
		e.prods = -1;
		cli[ide] = e;
		printf("Nova encomenda %d.\n", ide++);
	}
	return;
}
/*funcao auxiliar que calcula o peso total de uma encomanda*/
int peso_enc(int id_enc){
	int total = 0;
	int i;
	if (cli[id_enc].prods > -1)
		for (i=0; i<cli[id_enc].prods+1; i++)
			total += cli[id_enc].carr[i].qd * cli[id_enc].carr[i].peso;
	return total;
}
/*gera as carateristicas de um novo produto adicionado ao carrinho ao adicionar um produto novo*/
void prod_novo_carr(int id_enc, int id_pro, int qd){
	cli[id_enc].carr[id_pro].idp = id_pro;
	cli[id_enc].carr[id_pro].preco = sys[id_pro].preco;
	cli[id_enc].carr[id_pro].peso = sys[id_pro].peso;
	cli[id_enc].carr[id_pro].qd = qd;
	strcpy(cli[id_enc].carr[id_pro].desc, sys[id_pro].desc);
	return;
}
/*adiciona um produto em stock a encomenda*/
void __A__(){
	int id_enc, id_pro, qd, a=0;
	scanf("%d:%d:%d", &id_enc, &id_pro, &qd);
	if (eh_enc(id_enc) && eh_pro(id_pro) && sys[id_pro].qd - qd >=0 && peso_enc(ide) + sys[id_pro].peso * qd <= PESOMAX){
		pro_in_enc(id_enc, id_pro, a);
		if (ah_pro_in_enc(id_enc, id_pro)) {
			cli[id_enc].prods++;
			prod_novo_carr(id_enc, id_pro, qd);
		}
		else cli[id_enc].carr[a].qd += qd;
		sys[id_pro].qd -= qd;
		return;
	}
	else if(eh_enc(id_enc)==0){
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", id_pro, id_enc);
		return;
	}
	else if(eh_pro(id_pro)==0){
		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", id_pro, id_enc);
		return;
	}
	else if((sys[id_pro].qd - qd <0)){
		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", id_pro, id_enc);
		return;
	}
	else if(peso_enc(ide) + sys[id_pro].peso * qd > PESOMAX)
		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", id_pro, id_enc);
	return;
}
/*quantidade de produto de certo tipo encomendado*/
int qd_pro_enc(int id_pro){
	int i, j, total;
	for (i=0; i<ENCMAX; i++){
		for (j=0; j<SYSMAX; j++){
			if (id_pro == cli[i].carr[j].idp){
				total += cli[i].carr[ide].qd;
			}
		}
	}
	return total;
}
/*remove um produto do sistema ou seja, fora de stock*/
void __r__(){
	int id_pro, qd;
	scanf("%d:%d", &id_pro, &qd);
	if (eh_pro(id_pro) && sys[id_pro].qd-qd >= 0) sys[id_pro].qd -= qd;
	else if (eh_pro(id_pro) == 0) printf("Impossivel remover stock do produto %d. Produto inexistente.\n", id_pro);
	else if (sys[id_pro].qd - qd < 0) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qd, id_pro);
	return;
}
/*remove um produto de uma encomenda*/
void __R__(){
	int id_enc, id_pro, a=0;
	scanf("%d:%d", &id_enc, &id_pro);
	if (eh_enc(id_enc) == 0) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", id_pro, id_enc);
	else if (eh_pro(id_pro) == 0) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", id_pro, id_enc);
	else {
		pro_in_enc(id_enc, id_pro, a);
		cli[id_enc].carr[a].qd = 0;
	}
	return;
}
/*calcula o custo de uma encomenda*/
void __C__(){
	int id_enc, i, total=0;
	scanf("%d", &id_enc);
	if (eh_enc(id_enc)){
		if (cli[id_enc].prods == -1){
			return;
		} 
		else{
			for (i=0; i<SYSMAX; i++){
				total += cli[id_enc].carr[i].preco * cli[id_enc].carr[i].qd;
			}	
			printf("Custo da encomenda %d %d.\n", id_enc, total);
		}
	}
	else printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", id_enc);
	return;
}
/*altera o preco de um produto existente no sistema*/
void __p__(){
	int id_pro, preco;
	scanf("%d:%d", &id_pro, &preco);
	if (eh_pro(id_pro)) sys[id_pro].preco = preco;
	else printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", id_pro);
	return;
}
/*lista a descri??o e a quantidade de um produto*/
void __E__(){
	int id_enc, id_pro, qd, a=0;
	char desc[STRMAX];
	scanf("%d:%d", &id_enc, &id_pro);
	if (eh_enc(id_enc)==0) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
	else if (eh_pro(id_pro)==0) printf("Impossivel listar produto %d. Produto inexistente.\n", id_pro);
	else{
		pro_in_enc(id_enc, id_pro, a);
		strcpy(desc, cli[id_enc].carr[a].desc);
		qd = cli[id_enc].carr[a].qd;
		printf("%s%c%d.\n", desc, ' ', qd);
	}
	return;
}

/*lista ide da enc com maior quantia de certo produto*/
void __m__(){
	int id_pro, i, k, a=0, max=0, ide_max;
	scanf("%d", &id_pro);
	if (ide>0 && eh_pro(id_pro)){
		for (k=0; k<ide; k++){
			if (ah_pro_in_enc(k, id_pro)==0)
				break;
			else
				return;
		}
		for (i=0; i<ide;i++){
			pro_in_enc(i, id_pro, a);
			if (cli[i].carr[a].qd > max) {
				max = cli[i].carr[a].qd;
				ide_max = i;
			}
			else if (cli[i].carr[a].qd == max)
				if (ide_max < i) 
					ide_max = i;
		}
	pro_in_enc(ide_max, id_pro, a);
	printf("Maximo produto %d %d %d.\n", id_pro, ide_max, cli[ide_max].carr[a].qd);
	return;	
	}
	else if (eh_pro(id_pro)==0){
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", id_pro);
		return;
	}
	else
		return;
}
/*devolve um vetor ordenado de indice l a r*/
void merge(int a[SYSMAX][2], int l, int m, int r){
	int i, j, k;
	for(i=m+1; i>l; i--){
		aux[i-1][1] = a[i-1][1];
		aux[i-1][0] = a[i-1][0];
	}
	for(j=m; j<r; j++){
		aux[r+m-j][1] = a[j+1][1];
		aux[r+m-j][0] = a[j+1][0];
	}
	for (k=l; k<=r; k++){
		if (aux[j][1] < aux[i][1] || i>m){
			a[k][0] = aux[j][0];
			a[k][1] = aux[j--][1];
		}
		else if (aux[j][1] == aux[i][1]){
			if (aux[j][0] < aux[i][0]){
				a[k][0] = aux[j][0];
				a[k][1] = aux[j--][1];
			}
			else{
				a[k][0] = aux[j][0];
				a[k][1] = aux[i++][1];
			}
		}
		else{
			a[k][0] = aux[i][0];
			a[k][1] = aux[i++][1];
		}
	}
}
/*ordena vetores de int com o algortimo mergesort*/
void mergesort(int a[SYSMAX][2], int l, int r){
	int m = (r+l)/2;
	if (r<=l) return;
	mergesort(a, l, m);
	mergesort(a, m+1, r);
	merge(a, l, m, r);
}
/* lista de produtos do sistema ordenados por ordem crescente de preco*/
void __l__(){
	int i, j,list_preco[SYSMAX][2];
	for(j=0; j<idp+1; j++){
		list_preco[j][1] = sys[j].preco;
		list_preco[j][0] = sys[j].idp;
	}
	mergesort(list_preco, 0, idp);
	printf("Produtos\n");
	for (i=1; i<idp+1; i++){
		printf("*%s %d %d\n", sys[list_preco[i][0]].desc,  sys[list_preco[i][0]].preco, sys[list_preco[i][0]].qd);
		
	}
	return;
}
/*prepara o carater necessario para ser comparado na proxima iteracao de mergesort, caso a ordenacao nao esteja completa na primeira */
void next_char_alfa(int c, int id_enc, int a[SYSMAX][2]){
	int j;
	for(j=0; j<cli[id_enc].prods+1; j++){
		a[j][1] = cli[id_enc].carr[j].desc[c];
		a[j][0] = cli[id_enc].carr[j].idp;
	}
}
/*torna maiusculas em minusculas*/
void A_para_a(int a){
	if (64<a && a<91)
		a += 32;
}
/*lista de produtos do sistema por ordem alfabetica*/
void __L__(){
	int id_enc;
	scanf("%d", &id_enc);
	if (eh_enc(id_enc)){
		int  i, j, k, m, l, h1, h2, hh1, hh2, list_chars[SYSMAX][2], str[SYSMAX][STRMAX];
		next_char_alfa(0, id_enc, list_chars);
		for (m=0;m<cli[id_enc].prods+1;m++){
			A_para_a(list_chars[m][1]);
		}
		mergesort(list_chars, 0, cli[id_enc].prods+1);
		for (h1=0; h1<cli[id_enc].prods+1; h1++)
			for (h2=0; h2<cli[id_enc].prods+1+1; h2++)
				str[h1][h2] = sys[list_chars[h1][0]].desc[h2];
		for (i=0; i<cli[id_enc].prods+1+1; i++){
			for (j=0; j<cli[id_enc].prods+1;j++){
				char igual1 = list_chars[i][1], igual2 = list_chars[i+1][1], diff1=str[i][j+1], diff2=str[i+1][j+1];
				A_para_a(igual1);
				A_para_a(igual2);
				A_para_a(diff1);
				A_para_a(diff2);
				if (igual1==igual2 && diff1 > diff2){
					next_char_alfa(j+1, id_enc, list_chars);
					mergesort(list_chars, 0, cli[id_enc].prods+1);
					for (hh1=0; hh1<cli[id_enc].prods+1+1; hh1++)
						for (hh2=0; hh2<cli[id_enc].prods+1; hh2++)
							str[hh1][hh2] = sys[list_chars[hh1][0]].desc[hh2];
				}
			}
		}
		printf("Encomenda %d\n", id_enc);
		for (k=1; k<cli[id_enc].prods+1+1; k++){
			printf("*%s %d %d\n", sys[list_chars[k][0]].desc, sys[list_chars[k][0]].preco, cli[id_enc].carr[list_chars[k][0]].qd);
		}
		for (l=0; l<SYSMAX; l++){
			list_chars[l][0] = 0;
			list_chars[l][1] = '0';
		}
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", id_enc);
	
	return;
}
/*le a primeira letra da instrucao completa e deixa o resta para as outras funcoes*/
int main(){
	char comm='0';
	while ((comm=getchar())!=EOF){
		switch(comm){
			case 'a': __a__(); break;
			case 'q': __q__(); break;
			case 'N': __N__(); break;
			case 'A': __A__(); break;
			case 'r': __r__(); break;
			case 'R': __R__(); break;
			case 'C': __C__(); break;
			case 'p': __p__(); break;
			case 'E': __E__(); break;
			case 'm': __m__(); break;
			case 'l': __l__(); break;
			case 'L': __L__(); break;
			case 'x':return 0;
		}
	}
	return 0; 
}