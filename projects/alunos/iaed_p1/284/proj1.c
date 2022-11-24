#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Dimesao maxima das descricoes dos artigos */
#define MAXS 100
/*Numero maximo de artigos possivies no stock*/
#define VECMAX 10000
/*Dimensao auxiliar para a leitura do input*/
#define AUX 400
/*Numero maximo de informacao que recebe do stdin apos um comando*/
#define MAXINFO 5
/*Numero maximo de Encomendas*/
#define MAXENCOMENDA 500
/*Numero maximo de peso de uma encomenda*/
#define MAXPESO 200

/*E criada uma estrutura "produto" que serve para guardar o stock do sistema e as suas informacoes 
  mas tambem para facilitar a compreensao dos varios comandos*/
typedef struct produto{
     int identificador;
     char descricao[MAXS];
     int preco;
     int peso;
     int quantidade;
} produto; 

/*E criada uma estrutura "encomenda" que serve para guardar as varias encomendas do sistema e as suas informacoes
  mas tambem para facilitar a compreensao dos varios comandos*/
typedef struct encomenda{
     int identificadorpro;
     int identificador;
     int quantidade;
} encomenda; 

 /*Adiconalemnte sao criados dois arrays globais. Estes sim que vao guardar as informacoes pertencentes 
   as encomendas e ao stock */
produto PRODUTO[VECMAX];
encomenda ENCOMENDA[MAXENCOMENDA][MAXPESO];

/*Funcoes principais que representam os comandos do programa*/
void _a_(int i);
void _q_(int k);
void _N_(int n);
int _A_(int k);
int _r_(int k);
int _R_();
int _C_();
int _p_(int k);
int _E_(int k);
int _m_(int n);
int _l_(int k);
int _L_(int n);

/*Funcoes auxiliares criadas para complementar/ajudar as funcoes anteriores*/
int calcula_peso_encomenda(int ide );
int calcula_produtos_encomenda(int ide);
int verifica_idp_na_encomenda(int idp,int ide);
void get_input(char info[MAXINFO][MAXS]);

/*Funcoes auxiliares para ordenamento*/
/*l*/
void quicksort_l(produto a[], int l, int r);
int less_l(produto a, produto v);
int partition_l(produto a[], int l, int r);
void exch_l(produto a[] ,int i,int j);
/*L*/
void quicksort_L(encomenda a[], int l, int r);
int less_L(encomenda a, encomenda v);
int partition_L(encomenda a[], int l, int r);
void exch_L(encomenda a[] ,int i,int j);





int main(){
	int i=0,j=0;
	
	/*Sao criadas duas variaveis e incializadas a "-1". 
	  Estas servem para contar as vezes que certos comandos sao chamados.
	  A variavel k serve para contar os produtos que sao adicionados ao stock no comando: a
	  A variavel n serve para contar as encomendas que sao inicializadas */
	int k = -1, n = -1;
	
	/*A variavel first vai detetar a letra do comando mais a baixo com o scanf*/
	char first = '\0';

	/*De seguida sao incilizados os seguintes valores nas encomedas, para que nas varias funcoes
	  seja possivel verificar se o "espaco" na encomenda esta a ser utilizado ou  se foi apagado/nao incializado*/
	for(i=0;i<MAXENCOMENDA;i++){
		for(j=0;j<MAXPESO;j++){
			/*Sao inciliazados a "-1" para que nao interfira com o identificador "0"*/
			ENCOMENDA[i][j].identificador = -1;
			ENCOMENDA[i][j].identificadorpro = -1;
			ENCOMENDA[i][j].quantidade = 0;
		}
	}

  	while(first != 'x'){
  		scanf("%c", &first); 
    	switch(first){
    		
    		case 'a':
    		/*Cada vez que ha um novo produto ---> soma-se +1 a k*/
    		k++;
    		_a_(k);
    		break;

    		case 'q':
    		/*A variavel k e dada aqui a funcao q para o caso de ainda nao haver um produto 
    		  no sistema e este retornar logo o erro*/
    		_q_(k);
    		break;

    		case 'N':
    		/*Cada vez que ha uma nova encomenda ---> soma-se +1 a n*/
    		n++;
    		_N_(n);
    		break;

    		case 'A':
    		/*A variavel k e dada aqui a funcao A para o caso de ainda nao haver um produto 
    		  no sistema e este retornar logo o erro*/
    		_A_(k);
    		break;

    		case 'r':
    		/*A variavel k e dada aqui a funcao r para o caso de ainda nao haver um produto 
    		  no sistema e este retornar logo o erro*/
    		_r_(k);
    		break;

    		case 'R':
    		_R_();
    		break;

    		case 'C':
    		_C_();
    		break;

    		case 'p':
    		_p_(k);
    		break;

    		case 'E':
    		/*A variavel E e dada aqui a funcao q para o caso de ainda nao haver um produto 
    		  no sistema e este retornar logo o erro*/
    		_E_(k);
    		break;

    		case 'm':
    		/*A variavel n e dada aqui a funcao m para evitar que esta corra o vetor ECOMENDAS[][] todo desnecessariamente
    		  Assim vai apenas percorrelo n vezes em vez de 500 vezes*/
    		_m_(n);
    		break;

    		case 'l':
    		/*A variavel k e dada aqui a funcao l para evitar que esta corra o vetor PRODUTOS[][] todo desnecessariamente*/
    		_l_(k);
    		break;

    		case 'L':
    		/*A variavel n e dada aqui a funcao L para evitar que esta corra o vetor ECOMENDAS[][] todo desnecessariamente*/
    		_L_(n);
    		break;


    	}
  	}
  	return 0;
}


/* ################################################# 
   # Funcao get_input:                             #
   # Le o input de cada comando                    #
   # Formato de entrada:(ex.):                     #                                            
   #           descricao:preco:peso:qtd            #
   # Formato de saida:                             #
   #           {descricao,preco,peso,qtd}	       #
   ################################################# */

void get_input(char info[MAXINFO][MAXS]){
  char array[AUX],space;
  int i = 0;
  const char str[MAXS] = ":\n";
  char *token;
  
  scanf("%c", &space);
  fgets(array, AUX, stdin);
  token = strtok(array, str);
  strcpy(info[i], token);

  while(token != NULL) {
    token = strtok(NULL, str);
    if (token != NULL){
    	i++;
    	strcpy(info[i], token);
    	}
    else
    	break;
  }
}

/* ################################################# 
   # Funcao _a_:                                   #
   # Adiciona um novo produto ao sistema           #
   # Formato de entrada:                           #                                            
   #           a descricao:preco:peso:qtd          #
   # Formato de saida:                             #
   #           Novo produto <idp>.				   #
   ################################################# */

void _a_(int i){
	/*Em todas as funcoes o inicio e igual:
	  1. E criado um vetor que e dada a funcao get_input()
	  2. A funcao get_input le o stdin e meteo no vetor
	  3. Atribuise a cada informacao no vetor uma variavel para poder ser usada na funcao*/
	char info[MAXINFO][MAXS];

	/*Variaveis incializadas para a Informacao a receber */
	char descrip[MAXS];
	int price,weight,qtd;
	
	get_input(info);
	
	/*Informacao recebida*/
	strcpy(descrip,info[0]);
	price = atoi(info[1]);
	weight = atoi(info[2]);
	qtd = atoi(info[3]);
	
	/*Atribuicao da informacao recebida ao respetivo produto.*/
	strcpy(PRODUTO[i].descricao,info[0]);
	PRODUTO[i].identificador = i;
	PRODUTO[i].preco = price;
	PRODUTO[i].peso = weight;
	PRODUTO[i].quantidade = qtd;

	printf("Novo produto %d.\n", PRODUTO[i].identificador);

}


/* ###################################################
   # Funcao _q_:                                     #
   # Adiciona stock a um produto existente no sistema#
   # Formato de entrada:                             #                                            
   #           q idp:qtd                             #
   # Formato de saida:                               #
   #           NADA (excepto erro)				     #
   ################################################# */

void _q_(int k){
	/*Procedimento de leitura do stdin igual a funcao anterior*/
	char info[MAXINFO][MAXS];
	
	int idp = 0,qtd = 0,i,j=0;
	
	get_input(info);
	
	idp = atoi(info[0]);
	qtd = atoi(info[1]);
	
	/*Antes de mais e testado o caso de ainda nao haver um unico produto no sistema*/
	if(k ==-1)
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);

	/*De seguida e percorrido os produtos ate encontrar o que se quer. 
	  Se for encontrado, o for para e adiciona-se a quantidade ao stock,
	  caso contrario o erro e dado*/
	for(i=0;i<VECMAX;i++){
		if(idp == PRODUTO[i].identificador){
			j=1;
			break;
		}
		else
			j=0;
	}
	
	if(j==1)
		PRODUTO[idp].quantidade += qtd;
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
}
	

/* ###################################################
   # Funcao _N_:                                     #
   # Cria nova encomenda                             #
   # Formato de entrada:                             #                                            
   #           N                                     #
   # Formato de saida:                               #
   #           Nova encomenda <ide>.				 #
   ################################################# */

void _N_(int n){
	int i=0;
	for(i=0;i<MAXPESO;i++)
		ENCOMENDA[n][i].identificador = n;
	printf("Nova encomenda %d.\n",n);
}


/* ####################################################
   # Funcao _A_:                                      #
   # Adiciona um produto a uma encomenda.Se o         #
   # produto j? existir na encomenda, adiciona a nova # 
   # quantidade ? quantidade existente                #
   # Formato de entrada:                              #                                            
   #           A ide:idp:qtd                          #
   # Formato de saida:                                #
   #           NADA (excepto erro)				      #
   ################################################# */

int _A_(int n){
	/*Procedimento de leitura igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	
	int ide = 0,idp = 0,qtd = 0, newpeso= 0;
	
	int i = 0,j=0,l=0;
	
	get_input(info);
	
	ide = atoi(info[0]);
	idp = atoi(info[1]);
	qtd = atoi(info[2]);


	/*Sao percorridas as encomendas para verifacar se esta encomenda de facto existe mesmo*/
	for(i= 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificador == ide){
			j=1;
			break;
		}
			else
				j= 0;
		}
	/*Se nao existir e printado o erro*/
	if(j==0)
		return printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	
	/*E percorrido os produtos para verificar se este produto de facto existe mesmo*/	
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			break;
		}
		else 
			l=0;
	}
	/*Se o produto nao existir ou se ainda nao houver nem um produto no sistema e printado erro*/
	if(l==0 || n == -1){
		return printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
	}

	/*E verifcada a quantidade do produto para ver se a encomenda pode ser feita
	  tendo em conta o seu stock */
	if(PRODUTO[idp].quantidade < qtd)
		return printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
	
		/*Aqui e calculado o peso hipotetico se este produto fosse juntado a encomenda*/
	newpeso = calcula_peso_encomenda(ide) + (qtd * PRODUTO[idp].peso);
		/*Que de seguida e comparada com o peso maximo. E se for maior o erro e printado*/
	
	
	if(calcula_produtos_encomenda(ide)==0)
		newpeso = qtd * PRODUTO[idp].peso;

	if(newpeso > 200)
		return printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);


	/*Este caso e para quando o produto ainda nao esta na ecomenda.
	  Aqui os dados sao inicializados da primeira vez*/
	if(verifica_idp_na_encomenda(idp,ide) == 0){
		for(i=0;i<MAXPESO;i++){
			if(ENCOMENDA[ide][i].identificadorpro == -1){
				PRODUTO[idp].quantidade = PRODUTO[idp].quantidade -qtd;
				ENCOMENDA[ide][i].identificadorpro =  idp;
				ENCOMENDA[ide][i].identificador = ide;
				return ENCOMENDA[ide][i].quantidade = ENCOMENDA[ide][i].quantidade + qtd;
				break;
			}
		}
	}

	/*Este caso e para quando o produto ja esta na ecnomenda e foi adicionado previamente.
	  Aqui os dados sao adicionados e atualizados */
	if(verifica_idp_na_encomenda(idp,ide) == 1){
		for(i=0;i<MAXPESO;i++){
			if(ENCOMENDA[ide][i].identificadorpro == idp){
				PRODUTO[idp].quantidade = PRODUTO[idp].quantidade -qtd;
				ENCOMENDA[ide][i].identificadorpro =  idp;
				ENCOMENDA[ide][i].identificador = ide;
				ENCOMENDA[ide][i].quantidade = ENCOMENDA[ide][i].quantidade + qtd;
				break;
			}
		}
	}

	return 0;
}


/* ###################################################
   # Funcao _r_:                                     #
   # remove stock a um produto existente             #
   # Formato de entrada:                             #                                            
   #           r idp:qtd                             #
   # Formato de saida:                               #
   #           NADA (excepto erro)       			 #
   ################################################# */

int _r_(int k){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int i=0,l=0;
	int idp = 0,qtd = 0;
	
	get_input(info);
	
	idp = atoi(info[0]);
	qtd = atoi(info[1]);

	/*Antes de mais e testado o caso de ainda nao haver um unico produto no sistema*/
	if(k ==-1)
		return printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);


	/*E percorrido os produtos para verificar se este produto de facto existe mesmo*/
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			break;
		}
		else 
			l=0;
	}
	/*Caso nao exista printa o erro*/
	if(l==0)
		return printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
	/*E verfifcado se e possivel retirar a quantidade ao produto. 
	  Para que este nao fique com quantidade negativa */
	if((PRODUTO[idp].quantidade - qtd)<0)
		return printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);

	/*Se nao houver problema nenhum a quantidade e removida*/
	PRODUTO[idp].quantidade = PRODUTO[idp].quantidade - qtd;
	return 0;
}


/* ###################################################
   # Funcao _R_:                                     #
   # remove um produto de uma encomenda              #
   # Formato de entrada:                             #                                            
   #           R ide:idp                             #
   # Formato de saida:                               #
   #           NADA (excepto erro)       			 #
   ################################################# */

int _R_(){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int ide = 0,idp = 0;
	int i = 0,j=0,l=0;
	
	get_input(info);
	
	ide = atoi(info[0]);
	idp = atoi(info[1]);

	/*E percorrido as Encomendas para verificar se alguma Encomenda tem o ide que se pretende*/
	for(i= 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificador == ide){
			j=1;
			break;
		}
		else
				j= 0;
		}
	/*Se nao for identificado nenhuma encomenda com o ide , o erro e printado*/
	if(j==0)
		return printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
	
	/*E percorrido os produtos para verificar se este produto de facto existe mesmo*/
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			break;
		}
		else 
			l=0;
	}
	/*Caso nao exista e printado o erro seguinte*/
	if(l==0)
		return printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);


	/*Se tudo acima estiver em ordem entao procura-se o produto na Encomenda e e feito o seguinte:
	  A quantidade e devolvida ao stock e e posta a zero na encomenda.
	  Sao tambem repostos os indentificadores para que as outras funcoes possam reconhecer que ja nao existe um produto
	  naquele "lugar" */
	for(i= 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro == idp){
			PRODUTO[idp].quantidade = PRODUTO[idp].quantidade + ENCOMENDA[ide][i].quantidade;
			ENCOMENDA[ide][i].quantidade = 0;
			ENCOMENDA[ide][i].identificador = -1;
			ENCOMENDA[ide][i].identificadorpro = -1;
			/*Quando for detetado o produto e logo parado o ciclo para nao subcarregar*/
			break;
			
		}
	}
	return 0;
}


/* ###################################################
   # Funcao _C_:                                     #
   # calcula o custo de uma encomenda                #
   # Formato de entrada:                             #                                            
   #           C ide                                 #
   # Formato de saida:                               #
   #           Custo da encomenda <ide> <total>   	 #
   ################################################# */

int _C_(){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int ide = 0,custo = 0;
	int i = 0,j=0;
	
	get_input(info);
	ide = atoi(info[0]);

	/*Sao percorridas as encomendas para verificar se essa encomenda existe no sistema*/
	for(i = 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificador == ide){
			j=1;
			break;
		}
			else
				j= 0;
		}
	/*Caso nao exista e printado o erro e a funcao acaba*/
	if(j==0)
		return printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);

	/*Percorre-se as Encomendas e vai se adicioanando o custo ate chegar ao fim */
	for(i = 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro != -1){
			custo += PRODUTO[ENCOMENDA[ide][i].identificadorpro].preco * ENCOMENDA[ide][i].quantidade;
		}
	}
	
	printf("Custo da encomenda %d %d.\n",ide,custo);
	return 0;
}


/* ####################################################
   # Funcao _p_:                                      #
   # altera o pre?o de um produto existente no sistema#
   # Formato de entrada:                              #                                            
   #           p idp:preco                            #
   # Formato de saida:                                #
   #           NADA (excepto erro)   	              #
   #################################################### */

int _p_(int k){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int idp = 0,preco=0;
	int i = 0,l=0;
	
	get_input(info);
	idp = atoi(info[0]);
	preco = atoi(info[1]);

	if(k==-1)
		return printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);

	/*E percorrido o stock ate encontrar o produto.
	  Caso seja encontrado e logo atualizado o preco e quebra o ciclo
	  Se nao houver o produto entao a variavel e atualizada e depois printado o erro*/
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			PRODUTO[i].preco = preco;
			break;
		}
		else 
			l=0;
	}

	if(l==0)
		return printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);

	return 0;
}


/* ################################################################
   # Funcao _E_:                                                  #
   # lista a descri??o e a quantidade de um produto numa encomenda#
   # Formato de entrada:                                          #                                            
   #           E ide:idp                                          #
   # Formato de saida:                                            #
   #           <desc> <qtd>.   	                                  #
   ################################################################*/

int _E_(int k){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int i=0,j=0,l=0;
	int ide = 0,idp=0;
	char desc[MAXS];
	int qtd = 0;
	
	get_input(info);
	ide = atoi(info[0]);
	idp = atoi(info[1]);

	/*Antes de mais e testado o caso de ainda nao haver um unico produto no sistema*/
	if(k == -1){
		return printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
	}

	/*Neste ciclo e percorrido e verifcado se a Encomenda existe*/
	for(i= 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificador == ide){
			j=1;
			break;
		}
			else
				j= 0;
		}
	
	if(j==0)
		return printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
	
	/*Neste ciclo e percorrido e verifcado se o Produto existe*/	
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			/*Caso o produto exista e copiada a sua descricao para a variavel desc
			  Assim pode ser printada aseguir*/
			strcpy(desc,PRODUTO[idp].descricao);
			break;
		}
		else 
			l=0;
	}

	if(l==0)
		return printf("Impossivel listar produto %d. Produto inexistente.\n",idp);

	/*Aqui e "encontrado" o produto e a sua quantidade na ENCOMENDA*/
	for(i= 0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro == idp){
			qtd = ENCOMENDA[ide][i].quantidade;
			break;
		}
	}

	return printf("%s %d.\n",desc,qtd);
	return 0;
	
}


/* #############################################################################
   # Funcao _m_:                                                               #
   # lista o identificador da encomenda em que o produto dado ocorre mais vezes#
   # Formato de entrada:                                                       #                                            
   #           E ide:idp                                                       #
   # Formato de saida:                                                         #
   #           <desc> <qtd>.   	                                               #
   #############################################################################*/

int _m_(int n){
	/*Procedimento de leitura do stdin igual a funcao _a_ */
	char info[MAXINFO][MAXS];
	int i=0,j=0,l=0,k=0;
	int count =0,max =0,ide = 0,idp=0;
	
	get_input(info);
	idp = atoi(info[0]);


	/*Primeiramente vai verfifcar se o produto existe no sistema ou nao*/
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == idp){
			l=1;
			/*Caso exista para logo*/
			break;
		}
		else 
			l=0;
	}
	/*Caso nao exista printa erro*/
	if(l==0)
		return printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);



	/*Aqui vai percorrer todas as encomendas existentes e os produtos nelas
	  A variavel n e o numero de encomendas no sistema e faz com que o ciclo nao seja maior doque poderia ser*/
	for(i=0;i<=n;i++){
		for(j=0;j<MAXPESO;j++){
			if(ENCOMENDA[i][j].identificadorpro == idp){
				/*Quando encontrar o produto numa encomenda atualiza a sua quantidade
				  na variavel count*/
				count = ENCOMENDA[i][j].quantidade;
				k=1;
			}
		}
		/*Antes de passar a proxima Encomenda. Verifica se a quantidade e maior do que o max.
		  O max aqui e a quantidade nas outras encomendas*/
		if(count > max){
			/*Caso seja, atualiza o max e guarda o ide da Encomenda*/
			max = count;
			ide = i;
		}
	}

	if(k==0)
		/*No caso de nao haver esse produto em nenhuma encomenda entao nao faz nada*/
		return 0;


	/*Printa os dados apos a procura*/
	printf("Maximo produto %d %d %d.\n",idp,ide,max);
	return 0;
}


/* ##############################################################################
   # Funcao _l_:                                                                #
   # lista todos os produtos existentes no sistema por ordem crescente de pre?os#
   # Formato de entrada:                                                        #                                            
   #           l                                                                #
   # Formato de saida:                                                          #
   #            Produtos 														#
   #     * <desc1> <preco1> <qtd1 em stock>  	                                #
   #	 * <desc2> <preco2> <qtd2 em stock>										#
   #				    ....     												#
   ##############################################################################*/
	 


int _l_(int k){
	int i=0;
	int le=0;
	int ri=k;
	produto guarda[VECMAX];

	/*E criado um vetor da mesma estrutura para guardar os varios produtos do sistema.
	  Isto e importante pois se usarmos a estrutura original, ao ordenar os identificadores
	  ficariam trocados com a sua posicao. Oque nao e idial para as funcoes acima.*/
	for(i=0;i<(k+1);i++){
		guarda[i].identificador = PRODUTO[i].identificador;
		guarda[i].preco = PRODUTO[i].preco;
		guarda[i].peso = PRODUTO[i].peso;
		guarda[i].quantidade = PRODUTO[i].quantidade;
		strcpy(guarda[i].descricao,PRODUTO[i].descricao);
	}
	/*E chamada a funcao quicksort com o limite da esquerda = 0 e o limite da direia = produtos no sistema*/
	quicksort_l(guarda,le,ri);

	printf("Produtos\n");
	for(i=0;i<k+1;i++)
		printf("* %s %d %d\n",guarda[i].descricao,guarda[i].preco,guarda[i].quantidade);
		
	return 0;
}


/*#######################
  #					    #
  # Funcoes Auxiliares  #
  #  de ordenamento _l_ #
  #						#
  #######################*/

void quicksort_l(produto a[], int l , int r){
	int i=0;
	if(r<=l) return;
	i = partition_l(a,l,r);
	quicksort_l(a,l,i-1);
	quicksort_l(a,i+1,r);
}


int partition_l(produto a[],int l, int r){
	/*Funcao que faz a particao para o quicksort*/
	int i=l-1;
	int j= r;
	produto v = a[r];
	while(i<j){
		while(less_l(a[++i],v));
		while(less_l(v,a[--j])){
			if(j==l)
				break;
			}
		if (i<j)
		exch_l(a,i,j);

	}
	exch_l(a,i,r);
	return i;
}

int less_l(produto a, produto v){
	/*Funcao que define qual o menor de dois produtos
	  Verfica primeiro se um preco e maior ou menor */
	if(a.preco < v.preco){
		return 1;
	}
	if(a.preco > v.preco)
		return 0;
	/*Caso seja igual verfifca os identificadores*/
	if(a.preco == v.preco){
		if(a.identificador < v.identificador)
			return 1;
		if(a.identificador > v.identificador)
			return 0;
	}
	return 0;
}

void exch_l(produto a[], int i,int j){
	/*Troca dois produtos */
	produto t;
	t = a[i];
	a[i]=a[j];
	a[j]=t;
}


/* ##############################################################################
   # Funcao _L_:                                                                #
   # lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o#
   # Formato de entrada:                                                        #                                            
   #           L ide                                                            #
   # Formato de saida:                                                          #
   #            Encomenda ide													#
   #     * <desc1> <preco1> <qtd1 na ide> 	                                    #
   #	 * <desc2> <preco2> <qtd2 na ide>									    #
   #			        ....													#
   ##############################################################################*/

int _L_(int n){
	char info[MAXINFO][MAXS];
	int ide=0;
	int i=0;
	int l=0,r = 0;
	encomenda guardaenc[MAXENCOMENDA][MAXPESO];
	
	get_input(info);
	ide = atoi(info[0]);
	
	/*Antes de mais verifica se a Encomenda existe.
	  1. A variavel n conta o numeor de ecnomendas incializadas. Se for n==-1 nao ha nenhuma encomenda
	  2. Como o ide e crescente e e o numero de encomendas, se o ide for maior que n entao essa encoemnda nao existe
	  ---> Nestes 2 casos printa o erro*/
	if(n==-1 || ide > n)
		return printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);

	printf("Encomenda %d\n",ide);
	/*Se nao exisitir nenhum produto dentro de uma encomenda nao deve printar nada.*/
	if(calcula_produtos_encomenda(ide)==0)
		return 0;
	
	/*Se apenas houver um produto na encomenda. Este e logo printado,sem necessidade de ordenamento*/
	if(calcula_produtos_encomenda(ide) == 1){
		for(i=0;i<MAXPESO;i++){
			if(ENCOMENDA[ide][i].identificadorpro != -1){
				return printf("* %s %d %d\n",PRODUTO[ENCOMENDA[ide][i].identificadorpro].descricao,PRODUTO[ENCOMENDA[ide][i].identificadorpro].preco,ENCOMENDA[ide][i].quantidade);
				break;
			}
		}
	}


	/*Assumindo agora que nao ha nenhum erro e a encomenda tem mais que um produto, e passado para um
	  vetor auxiliar da mesma estrutura todos os produtos "reais" da encomenda que se quer ordenar. Isto
	  e necessario pois pode haver o caso de produtos terem sido apagados(identificadores postos a -1) da encomendas.*/
	for(i=0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro != -1){
			guardaenc[ide][i].identificadorpro = ENCOMENDA[ide][i].identificadorpro;
			guardaenc[ide][i].identificador = ENCOMENDA[ide][i].identificador;
			guardaenc[ide][i].quantidade = ENCOMENDA[ide][i].quantidade;
			/*Sao contados o numero de produtos "reais" para ser dado como limite da direita a funcao quicksort_L()*/
			r++;
		}
	}

	/*Chama-se a funcao de ordenamento*/
	quicksort_L(guardaenc[ide],l,r);

	/*Sao percorridos os produtos e printados*/
	for(i=r;i>-1;i--){
		if(verifica_idp_na_encomenda(guardaenc[ide][i].identificadorpro,ide)==1){
			printf("* %s %d %d\n",PRODUTO[guardaenc[ide][i].identificadorpro].descricao,PRODUTO[guardaenc[ide][i].identificadorpro].preco,guardaenc[ide][i].quantidade);
		}
	}

	return 0;
}


void quicksort_L(encomenda a[], int l , int r){
	int i=0;
	if(r<=l) return;
	i = partition_L(a,l,r);
	quicksort_L(a,l,i-1);
	quicksort_L(a,i+1,r);
}


int partition_L(encomenda a[],int l, int r){
	int i=l-1;
	int j= r;
	encomenda v = a[r];
	while(i<j){
		while(less_L(a[++i],v));
		while(less_L(v,a[--j])){
			if(j==l)
				break;
			}
		if (i<j)
		exch_L(a,i,j);

	}
	exch_L(a,i,r);
	return i;
}

int less_L(encomenda a, encomenda v){
	char desc1[MAXS];
	char desc2[MAXS];
	int compr=0;
	int i=0;
	/*Primeiramente sao percorridos os produtos para encontrar a descricao de cada um elemento da encomenda
	  que se quer ordenar,estas sao guardadas nas variaveis */
	for(i=0;i<VECMAX;i++){
		if(PRODUTO[i].identificador == a.identificadorpro)
			strcpy(desc1,PRODUTO[i].descricao);
		if(PRODUTO[i].identificador == v.identificadorpro)
			strcpy(desc2,PRODUTO[i].descricao);
	}
	/*A varaiavel compr corresponde ao cumprimento da string da desc1*/
	compr = strlen(desc1);
	/*Esta e usada num ciclo for para percorrer as varias letras ate se encontrar a mais pequena*/
	for(i=0;i<compr;i++){
		if(desc1[i] < desc2[i]){
			return 0;
			break;
		}
		else{
			return 1;
			break;
		}
		
	}
	return 0;
}

void exch_L(encomenda a[], int i,int j){
	/*Troca dois produtos numa encomenda*/
	encomenda t;
	t = a[i];
	a[i]=a[j];
	a[j]=t;
}


/*######################
  #					   #
  # Funcoes Auxiliares #
  #                    #
  ######################*/


/*Funcao que calcula o peso de uma encomenda com base no seu ide*/
int calcula_peso_encomenda(int ide){

	int i = 0;
	int pesototal = 0;
	for(i=0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro != -1){
			pesototal +=(PRODUTO[ENCOMENDA[ide][i].identificadorpro].peso) *  ENCOMENDA[ide][i].quantidade;
		}
	}
	return pesototal;
	return 0;
}

/*Funcao que calcula o numero de produtos numa encomenda com base no seu ide*/
int calcula_produtos_encomenda(int ide){
	int i =0,cont=0;
	for(i=0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro != -1){
			cont++;
		}
	}
	
	return cont;
	return 0;
}

/*Verifica se um dado produto esta numa dada encomenda com base no idp e no ide*/
int verifica_idp_na_encomenda(int idp,int ide){
	int i=0;
	int yes =0;
	for(i=0;i<MAXPESO;i++){
		if(ENCOMENDA[ide][i].identificadorpro == idp){
			yes = 1;
			break;
		}
		else
			yes = 0;
	}
	return yes;
	return 0;
}












