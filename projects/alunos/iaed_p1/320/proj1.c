#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#define DESC 63
#define TWO 200
#define ORDER 500
#define PRODUCT 10000


typedef struct Produto {		/* estrutura produto com todas as suas caracteristicas*/
	int id;
	char desc[DESC];
	int price;
	int weight;
	int quantity;
} Produto;


Produto product_line[PRODUCT];		/* linha de produtos onde atraves do id consigo aceder ao produto pretendido */
Produto order_line[ORDER][TWO];		/* linha de encomendas onde atraves do id da encomenda consigo aceder a encomenda com os seus produtos respetivos*/
int add_prod_order[ORDER]={0};		/* indicador de encomendas onde atraves do id se consegue aceder ao  numero de produtos que cada encomenda contem (util para delinear limites quando queremos aceder aos seus produtos)*/
Produto aux[PRODUCT];		/*vetor de produtos que vai ser listado de acordo com a product line */
Produto aux1[PRODUCT];		/*vetor de produtos auxiliar referente a funcao merge pertence a funcao como auxiliar de ordenacao */


/* function a: adicona um novo produto a nossa linha de produtos e utlizado um scanf para ler as caracteristicas inseridas pelo utilizador
e posteriormente adcionado a nossa linha de produtos utilizando uma variavel estatica o nosso idp(id de produto) */


void function_a(){
	static int idp=0;		/* id estatico que permite ir adcionando novos produtos sem que percamos o valor de numero de produtos inseridos referentes ao proximo que iremos adcionar*/
	scanf(" %[^:]:%d:%d:%d",product_line[idp].desc,&product_line[idp].price,&product_line[idp].weight,&product_line[idp].quantity);		/*le no formato pretendido da funcao*/
	product_line[idp].id=idp;
	printf("Novo produto %d.\n",idp);
	idp++;		/*passagem para o proximo produto na proxima iteracao */
}


/*fucntion q : adiciona stock a nossa linha de produtos caso o id de o produto seja compativel que o numero de produtos ja inseridos/existentes com o 
nosso total de produtos (total_product), caso isso se verifique ? incrementada a quantidade desse memsmo produto na nossa linha de produtos */


void function_q(int total){
	int idp,qtd;
	scanf(" %d:%d",&idp,&qtd);		/*le no formato pretendido da funcao*/
	if (idp>=total) printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);		/* caso o produto nao exista na nossa linha de produtos*/
	else product_line[idp].quantity+=qtd;
}


/* funcao o : cria uma nova encomenda na linha das encomendas onde atraves de o uso de uma variavel estatica e possivel executar com o mesmo processso
da 'funcao a' da nossa linha de produtos criar uma nova encomenda incrementando o total de encomendas (contadir total_orders) */
 

void function_o(){
	static int ido=0;		/* id estatico que permite ir adcionando novas encomendas  sem que percamos o valor de numero de encomendas inseridas referentes a proxima que iremos adcionar */
	printf("Nova encomenda %d.\n",ido);
	ido++;		/*passagem para a proxima encomenda na proxima iteracao */
}


/* funcao weight: e uma funcao auxiliar que recebe o id a encomenda o nuemrod e prdoutos nessa encomenda e o total de peso que se pretende 
inserir na encomenda para verificar na pratica se excede o limite ou no(200 unidades de peso) */


int weight_calculater_order(int ido,int number_prod,int weight_acc){
	int i,weight=weight_acc;		/*o valor do peso comeca com o que se pretende inserir na encomenda */
	for (i=0;i<number_prod;i++)
		weight+=(order_line[ido][i].quantity*product_line[order_line[ido][i].id].weight);		/* vamos incrementando o valor do peso consoante a quantidade e valor tabelado de preco na nossa linha de produtos que existe ja previamnete na encomenda */
	return weight; /* devolve o peso total peso que ja se encontra na encomenda mais o peso que se pretende inserir o peso base */
}


/* funcao A : adicona um produto a uma encomenda.Esta funcao verifica se a encoemnda e valida se existe, se o produto tambem existe dentro da nossa linha de produtos 
e se com a sua adicao a encomenda na excedara as 200 unidades de peso, caso exista esta funcao incrementara o peso desse mesmo produto na encomenda */


void function_A(int total_o,int total_p){
	int ido,idp,qtd,l,state=0,number_add=0,acc_weight=0;
	scanf(" %d:%d:%d",&ido,&idp,&qtd);		/*le no formato pretendido da funcao*/
	if (ido>=total_o) printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ido);		/*verifica se a encomenda eciste de facto comparando com o nosso contador de encomendas */
	else if (idp>=total_p) printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ido);		/*verifica se o produto existe de facto comparando com o contador de produtos  */
	else if (product_line[idp].quantity-qtd<0) printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ido);		/* verifica se existe quantidade desse produto na linha de produtos para satisfazer a quantidade da encomenda */
	else if ((qtd*product_line[idp].weight)>200) printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ido); 		/* caso base quando o peso que se quer inserir e logo superior ao limite maximo */
	else {
		number_add=add_prod_order[ido];		/*variavel que guarda o numero de produtos existentes na encomenda que se pretende atualizar */
		acc_weight=qtd*product_line[idp].weight; /* variavel que guarda o peso do produto que pretendemos atualizar na nossa encomenda */
		if (number_add==0){		/*caso onde nao existe esse produto na encomenda acrescentamos logo sem previas restricoes o produto a encomenda pois existe e tem o peso nos parametros permitidos(<200) */
			product_line[idp].quantity-=qtd;		/*decrementa a quantidade de produto a nossa linha de produto pois estamos a inserir na encomenda */
			order_line[ido][0].id=idp;		/*coloca no produto da encomenda o seu id */
			order_line[ido][0].quantity=qtd;		/*coloca no produto da encomenda a sua quantidade */
			add_prod_order[ido]+=1;		/*incrementa ao vetor de quanridades de produtos de encomendas um produto(+1) */
		}
		else {		/*caso a encomenda ja contenha produtos iremos ver se esse produto ja existe na encomenda */
			for (l=0;l<number_add;l++){
				if (order_line[ido][l].id==idp){
					state=1;
					break;		/*caso exista o valor de state e alterado e o indice desse mesmo fica guardado em l */
				}
			}
			if (state!=0){		/* no caso de ja existir na linha de encomendas */
				if (weight_calculater_order(ido,number_add,acc_weight)<=200){		/*caso o seu peso nao exceda os limites */
					order_line[ido][l].quantity+=qtd;		/* incrementa-se a quantidade de produto nessa mesma encomenda  */
					product_line[idp].quantity-=qtd;		/*decrementa a quantidade de produto a nossa linha de produto pois estamos a inserir na encomenda */
				}
				
				else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ido);		/*caso exceda e nao seja psosivel adiconar */
			}
			else {		/* caso de nao existir esse produto na linha de encomendas */
				if (weight_calculater_order(ido,number_add,acc_weight)<=200){		/*caso o seu peso nao exceda os limites */
					product_line[idp].quantity-=qtd;		/*decrementa a quantidade de produto a nossa linha de produto pois estamos a inserir na encomenda */
					order_line[ido][number_add].id=idp;		/* incrementa-se a quantidade de produto nessa mesma encomenda no produto a seguir  */
					order_line[ido][number_add].quantity=qtd;	/*decrementa a quantidade de produto a nossa linha de produto pois estamos a inserir na encomenda */	
					add_prod_order[ido]+=1;		/*incrementa ao vetor de quanridades de produtos de encomendas um produto(+1) */
				}
				else printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ido);		/*caso exceda e nao seja psosivel adiconar */
			}
		}
	}
}

	
/* funcao r : remove stock(quantidade da linhda de produtos) a um determinado produto decrementando a esse produto a quantidade inserida, caso exista quantidade suficiente e
 caso esse produto exista na nossa linha de produtos*/


void function_r(int total){
	int idp,qtd;
	scanf(" %d:%d",&idp,&qtd);		/*le no formato pretendido da funcao*/
	if (idp>=total) printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	else if (product_line[idp].quantity-qtd<0) printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);		/* verifica se a quantidade que existe ems stock ? suficiente para se decrementar*/
	else product_line[idp].quantity-=qtd;	/* caso seja reitra se essa mesma quantidade */

}


/* funcao R: remove um produto de uma encomenda da nossa order_line verificando se a encomenda existe, se o produto existe , caso se verifique entao a quantidade de produto existente na encomenda retrocede para a nossa linha de produtos
e caso o produto em causa nao se encontre nessa mesma encomenda entao nao existe qualquer modificacao a ser feita.*/


void function_R(int total_ord, int total_prod){
	int ido, idp,i;
	scanf(" %d:%d",&ido,&idp);		/*le no formato pretendido da funcao*/
	if (ido>=total_ord) printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ido);
	else if (idp>=total_prod) printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ido);
	else {
		for (i = 0;i < add_prod_order[ido]; i++){
			if (order_line[ido][i].id==idp){		/* dentro do numero de produtos existentes numa determinada encomenda verifica se esse produto esta contido na mesma. */
				product_line[idp].quantity+=order_line[ido][i].quantity;		/*caso esteja a quantidade e devolvida a linha de produtos aumentando o stock do mesmo. */
				order_line[ido][i] = order_line[ido][add_prod_order[ido]-1];		/* para proceder a elimincao desse mesmo produto colocamos o ultimo produto da nossa encomenda na posicao do produto em causa e diminuimos o numero de produtos(-1) para que na pratica o produto que pretendemos eliminar 'deixe de existir' na nossa encomenda*/
				add_prod_order[ido]-=1;		/*procedemos entao a diminuicao do numero de produtos da encomenda para eliminar o tal produto em casua */
			}
		}
	}
}


/* funcao merge: esta funcao pertence a execucao que fiz para listar os produtos da minha product_line pertence a recursao da funcao(fucntion_l) e vai listandos os elementos dos sucessivos vetores ate ao ultimo
estar listado. */


void merge(int l, int m, int r){		/* limite inferior(l), ponto de particao e ordenacao(m), limite superior(r) */
	int i, j, k;
	for (i= m+1; i>l ; i--) aux1[i-1] = aux[i-1];		/* lista do inicio ao ponto de separacao*/
	for (j = m; j < r; j++) aux1[r+m-j] = aux[j+1];		/* lista do fim ao ponto de separacao */
	for (k=l; k<= r; k++){
		if (aux1[j].price<aux1[i].price) aux[k] = aux1[j--];		/*caso o preco seja menor entao ocorre a troca para uma posicao inicial */
		else if (aux1[j].price==aux1[i].price && aux1[j].id<aux1[i].id) aux[k] = aux1[j--];		/*caso o preco seja maior entao nao exite troca e o produto da posicao inicial mantem-se */
		else aux[k] = aux1[i++];
	}
}


/* funcao l: esta funcao e na pratica o mecanismo de ordenacao merge sort aplicado a linha de produtos com o intuito de ordenar todos os produtos existentes de acordo com o seu preco,
esta funcao vai "divindo" o vetor ate que nao existam mais sub-vetores por ordenar e depois faz recursivamente o merge desses mesmos sub-vetores obtendo por final o vetor completamente ordenado
de acordo com os precos de cada produto*/


void function_l(int l, int r){
	int m = (r+l)/2;		/* encotra o ponto de divisao*/
	if (r <= l) return;		/* vai dividindo o vetor ate chegar a este caso terminal onde os limites superiores e inferiores coincidem */
	function_l(l,m);		/*chama a funcao recursivamente com os limites da mesma, neste caso vai dividindo a primeira 'metade' do vetor*/
	function_l(m+1,r);		/*chama a funcao recursivamente com os limites da mesma, neste caso vai dividindo a ultima e segunda 'metade' do vetor*/
	merge(l, m, r);		/* funcao que organiza os sucessicos vetores */
}


/*funcatio p: esta funcao altera diretamente o preco de um produto no nosso sistema(product_line), caso o produto exista o seu preco
e imediatamente alterado na base de dados referente ao produto */


void function_p(int total_prod){
	int idp,price;
	scanf(" %d:%d",&idp,&price);		/*le no formato pretendido da funcao*/
	if (idp >= total_prod) printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);		/*verifica se o produto existe */
	else product_line[idp].price=price;		/*altera o preco do produto diretamente de acordo com o preco dado pelo utilizador */
}


/*function C: esta funcao calcula o custo de uma encomenda.Esta funcao percorre todos os produtos de uma encomenda e multiplica a sua quantidade pelo preco,
dando-nos assim a soma destas parcelas(produtos) que se encontram na mesma */


void function_C(int total_ord){
	int i,acc=0,ido;
	scanf(" %d",&ido);		/*le no formato pretendido da funcao*/
	if (ido>=total_ord) printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ido);		/*caso a encomenda nao exista */
	else {
		for(i=0;i<add_prod_order[ido];i++)		/*caso exista percorre todos os elementos da mesma */
			acc+=(order_line[ido][i].quantity*product_line[order_line[ido][i].id].price);		/*acc representa a progressiva soma de todos os precos dos constituintes da encomenda */
		printf("Custo da encomenda %d %d.\n",ido,acc);
	}
}


/*function E: esta funcao lista a a quantidade de um produto numa encomenda.Esta funcao verifica se um determinado produto existe e uma dterminada encomenda existe posto isto vai percorrer 
os produtos da encomenda e verificar se esse produto se encontra la caso se encontre retorna a quantidade presente do mesmo na encomenda , caso nao se encontre retorna quantidade 0.  */


void function_E(int total_prod, int total_ord){
	int i,ido,idp,state=-1;
	scanf(" %d:%d",&ido,&idp);		/*le no formato pretendido da funcao*/
	if (ido>=total_ord) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);
	else if (idp>=total_prod) printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	else{
		for(i=0;i<add_prod_order[ido];i++)		/*percorre os elementos dessa mesma encomenda */
			if (order_line[ido][i].id==idp) state=i;		
		if(state!=(-1)) printf("%s %d.\n",product_line[idp].desc,order_line[ido][state].quantity);		/*caso esse produto se encontre presente o valor do estado e alterado e retorna a quantidade desse produto */	
		else printf("%s 0.\n",product_line[idp].desc);		/*caso valor do estado nao tenha sido alterado entao o produto nao se encontra presente logo retorna 0 */
	}
}


/* fucntion L: lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o .Nesta funcao procedi a execucao de um sistema de ordenacao 'elementar' o selection sort devido ao tamanho do vetor de encomendas nao necessitar de um algoritmo
tao efeciente como por exemplo o da listagem da linha de produtos por preco pois este poderia conter 10000 produtos no maximo. */


void function_L(int total_ord){
	Produto aux;
	int ido,i,j,min,l=0;
	scanf(" %d",&ido);		/*le no formato pretendido da funcao*/
	if (ido>=total_ord) printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ido);		/*verifica se a encomenda existe */
	else {		/*caso a encomenda exista */
		for (i=0;i<add_prod_order[ido];i++){		/*percorre todos os produtos de uma determinada encomenda */
			min=i;
			for (j=i+1; j<add_prod_order[ido]; j++)
				if (strcmp(product_line[order_line[ido][j].id].desc,product_line[order_line[ido][min].id].desc)<0) min=j;		/*compara a descricao dos produtos das encomendas utilizando a funcao strcmp referente ao caracter ascii de um detrmiando caracter ,comparando-as na pratica alfabeticamente*/
			aux = order_line[ido][i]; order_line[ido][i] = order_line[ido][min]; order_line[ido][min]=aux;		/* o mecanismo selection sort procura o produto com a desricao ordenada alfabeticamente(a menor) de acordo a tabela ascii */
		}
		printf("Encomenda %d\n",ido);
		while (l<add_prod_order[ido]){
			printf("* %s %d %d\n",product_line[order_line[ido][l].id].desc,product_line[order_line[ido][l].id].price,order_line[ido][l].quantity);		/* depois de organizada a encomenda alfabeticamente retorna os produtos de acordo a restricao em causa.*/
			l++;
		}
	}
}


/*function m:  lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, dever? imprimir a encomenda de menor id.Esta funcao
percorre todas as encomendas e verifica as que contem o produto em causa e a sua respetiva quantidade a que tiver o produto com a maior quantidade , sera essa mesmo a ser retornada.*/ 


 void function_m( int total,int total_ord){
 	int idp,acc=0,final,i,l;
 	scanf(" %d",&idp);		/*le no formato pretendido da funcao*/
 	if (idp>=total) printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
 	else {
 		for (i=0;i<total_ord;i++){		/*percorre todas encomendas */
 			for (l=0;l<add_prod_order[i];l++){		/*percorre todos os produtos de uma determinada encomenda */
 				if (order_line[i][l].id==idp && order_line[i][l].quantity>acc){
 					acc=order_line[i][l].quantity;		/*caso esse produto exista a sua quantidade ocupa a variavel acc e se houver esse mesmo produto noutras encomendas e sua quantidade for superior esta sera sobreposta nesta variavel */
 					final=i;		/*caso ocorra a sua sobreposicao o id da encomenda e guardado na variavel final*/
 				}
 			}
 		}
 		if (acc==0)return;		/*caso nao tenha ocorrido uma sobreposicao significa que o produto nao se encontra em nenhuma encomenda ,logo, a funcao nao retornara nada. */
 		else printf("Maximo produto %d %d %d.\n",idp,final,acc);		/*caso tenha havido alguma sobreposicao sretorna o id da encomenda e a sua quantidade presente na mesma */
 	}

 }


/* A fun?ao main contem um switch principal e unico da nossa base de dados,onde todas as instrucoes dadas pelo utizador irao ser lidas aqui
 esta funcao esta associado a um estado o 'run' que funciona como "bit de estado", cada um dos cases est? associado a uma funcao
 inerente e esta mesma associada a um determinado controle (Ex : function_l - controle l |Ex: fuction_m - controle m.)*/


int main(){
	int control,run=1,total_product=0,total_orders=0,l,z;		/* bit de estado(run) e contador de encomendas(total_orders) e contador de produtos(total_product) */
	while (run){
		control=getchar();		/*serve para ler o caracter de entre o comando de instrucoes que o utilizador executa . */
		switch (control) {
			case 'a':
				function_a();
				total_product++;
				break;

			case 'q':
				function_q(total_product);
				break;

			case 'N':
				function_o();
				total_orders++;
				break;

			case 'A':
				function_A(total_orders,total_product);
				break;

			case 'x':
				run=0;
				break;

			case'r':
				function_r(total_product);
				break;

			case 'R':
				function_R(total_orders,total_product);
				break;

			case 'l':
				for (z=0;z<total_product;z++) aux[z]=product_line[z];
				function_l(0,total_product-1);
				printf("Produtos\n");
				for (l=0;l<total_product;l++) printf("* %s %d %d\n",aux[l].desc,aux[l].price,aux[l].quantity);
				break;

			case 'p':
				function_p(total_product);
				break;

			case 'E':
				function_E(total_product,total_orders);
				break;

			case 'C':
				function_C(total_orders);
				break;

			case 'L':
				function_L(total_orders);
				break;

			case'm':
				function_m(total_product,total_orders);
				break;

			default:		/* caso default altera o bit de estado no caso de nenhuma nas ordens corresponder ao esperado ou de se apresentarem num formato nao pretendido*/
				run=0;
				break;
		}
		getchar();		/*serve para ler o caracter ' ' que o utilizador executa ao pressionar enter. */
	}


	return 0;
}