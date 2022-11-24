#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
/* numero maximo de identfiquadores*/
#define MAX_N 9999
/* numero maximo de carateres da discricao*/     
#define MAX_C 62
/* numero maximo de prdutos numa encomenda*/       
#define MAX_E 499
/* numero maximo de peso de uma encomenda*/
#define MAX_P 200
/*defnicao de tipo prduto*/						
typedef struct produto{ 
	int iden;
	char desc [MAX_C];
	int preco,peso,quan;	
}prod;
/*defnicao de tipo prduto numa encomenda
contem o identifiquador e quantidade do prduto*/
typedef struct prodenc{
	int iden;
	int quan;
}prod_enc;
/*defnicao de tipo encomenda contem o id
e numreo de prdutos numa encomenda e o 
e o conjunto de prdutos*/
typedef struct encomenda{ 
	int id,N;				  
	prod_enc conjunto[MAX_P];
}enc;
/*vetor global que guarda prdutos*/
prod sistema[MAX_N];
/*vetor global que guarda encomendas*/        
enc encomendas[MAX_E];
/*vetor global auxiliar para oredenar os prdutos*/		
prod aux[MAX_N];
/*variaves globais que guardam o id de prdutos,encomendas*/
int iden,id;				
/*funcao auxeliar que resecbe um identifiquador
de um prduto e retorna o preco assocido a ele*/
int obtanha_preco(int iden1){
	int i,l;
	for(i=0;i<iden;i++){
		if (sistema[i].iden==iden1)
	      l=sistema[i].preco;
	}
	return l;
}
/*funcao auxliar que recebe uma enc e um prduto
e retorna o idreco desse prduto na encomenda*/ 
int obtanha_indreco(int id1 ,int iden1){
	int j,c=0;
	for(j=0;j<encomendas[id1].N;j++){
		if (encomendas[id1].conjunto[j].iden!=iden1)
			c++;
		else 
			break;
	}
	return c;
}
/*funcao auxiliar que soma os pesos de uma encomenda*/
int soma_pesos(enc E){
	int soma=0,i;
	for (i=0;i<E.N;i++){
		soma+=sistema[E.conjunto[i].iden].peso*E.conjunto[i].quan;
	}
	return soma;
}
/*funcao auxiliar que verfiqua se um prduto existe*/
int verfiqua_prod(int iden1){
	int i,c=0;
	for (i=0;i<iden;i++){
		if (sistema[i].iden==iden1)
			c=1;
	}
	return c;
}
/*funcao auxiliar que verfiqua se uma encomenda existe*/
int verfiqua_enc(int id1){
	int i,c=0;
	for (i=0;i<id;i++){
		if (encomendas[i].id==id1)
			c=1;
	}
	return c;
}
/*funcao auxiliar que verfiqua se um prduto existe numa encomenda*/
int verfiqua_pro_enc(int id1,int iden1){
	int c=0,j;
	for (j=0;j<encomendas[id1].N;j++){
		if(encomendas[id1].conjunto[j].iden == iden1)
			c=1;
	}
	return c;
}
/*funcao que e responsavel pelo comando a.
intrduze um prod na sistema*/ 
void comando_a(){
	scanf(" %[^:]:%d:%d:%d",sistema[iden].desc,&sistema[iden].preco,&sistema[iden].peso,&sistema[iden].quan);
	sistema[iden].iden=iden;
	printf("Novo produto %d.\n",iden++);
}
/*funcao que e responsavel pelo comando q.
intrduze quan a um prod existente*/
void comando_q(){
	int quan,iden1;
	scanf("%d:%d",&iden1,&quan);
	if (verfiqua_prod(iden1)){
			sistema[iden1].quan+=quan;
		}
	else
		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",iden1);	
}
/*funcao que e responsavel pelo comando N.
cria uma nova encomenda*/
void comando_N(){
	encomendas[id].id=id;
	printf("Nova encomenda %d.\n",id);
	id++;
}
/*funcao que e responsavel pelo comando A.
intrduze um prod a uma encmenda*/
void comando_A(){
	int id1,iden1,quan,j,c=0,k=1,i;
	scanf("%d:%d:%d",&id1,&iden1,&quan);
	if (verfiqua_enc(id1)){
		if (verfiqua_prod(iden1)){
			/* se hover quantidade */
			if (sistema[iden1].quan-quan >= 0){
				/* e se o peso nao excder ao peso maximo */
				 if((soma_pesos(encomendas[id1])+(sistema[iden1].peso*quan)) <= MAX_P){
				 		/*precorrer os prdutos da enc dada*/
						for(j=0;j<encomendas[id1].N+1;j++){
							/* se prduto ja existe na encomenda e se o identifiquador nao for zero*/
							if(encomendas[id1].conjunto[j].iden == iden1 && iden1){
								c=encomendas[id1].conjunto[j].iden;
								/* adecione so a quantidade*/
								encomendas[id1].conjunto[j].quan+=quan;
								/* e removo o stock a sistema*/
								sistema[iden1].quan-=quan;
							}
						}
						/* se nao esixte adeciona o prduto*/
						if (c !=iden1 && iden1){
							/*adeciona o prduto,adecionando o iden e a quan*/
							encomendas[id1].conjunto[encomendas[id1].N].iden=iden1;
							encomendas[id1].conjunto[encomendas[id1].N].quan=quan;
							sistema[iden1].quan-=quan;
							/*inquermenta o indice dos prdutos na enc dada*/
							encomendas[id1].N++;
						}
						/*se iden dado for zero faz as mesmas coisas
						mas esta separacao era necesareia porque os 
						ides dos prdutos na encomenda e icializada
						por diflut a zero*/
						if(iden1==0 ){
							for(i=0;i<encomendas[id1].N;i++){
								if(encomendas[id1].conjunto[i].iden == iden1 && encomendas[id1].N){
									k=encomendas[id1].conjunto[j].iden;
									encomendas[id1].conjunto[i].quan+=quan;
									sistema[iden1].quan-=quan;
								}
							}
							if(k!=iden1){
									encomendas[id1].conjunto[encomendas[id1].N].iden=iden1;
									encomendas[id1].conjunto[encomendas[id1].N].quan=quan;
									sistema[iden1].quan-=quan;
									encomendas[id1].N++;
								}
							}
					}	
				else
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",iden1,id1);		
			}
			else
				printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",iden1,id1);
		}
		else
			printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",iden1,id1);
	}
	else
		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",iden1,id1);				
}
/*funcao que e responsavel pelo comando r.
remove stock a um prduto existente*/
void comando_r(){
	int iden1,quan;
	scanf("%d:%d",&iden1,&quan);
	if (verfiqua_prod(iden1)){
		/* verfiqua se a quan e suficiente*/
		if(sistema[iden1].quan-quan >=0)
			sistema[iden1].quan-=quan;
		else
			printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",quan,iden1);
	}
	else
		printf("Impossivel remover stock do produto %d. Produto inexistente.\n",iden1);
}
/*funcao que e responsavel pelo comando R.
remove um prduto de uma encomenda*/
void comando_R(){
	int iden1,id1,j,c;
	scanf("%d:%d",&id1,&iden1);
	if(verfiqua_enc(id1)){	
		if (verfiqua_prod(iden1)){
			/*precorrer os prdutos da encomenda dada*/
			for(j=0;j<encomendas[id1].N;j++){
				if (encomendas[id1].conjunto[j].iden==iden1)
					/*se encontrar o prduto dado guardo o indice*/
					c=j;
			}
			/*devolvo o stock a sistema e poem quan do prod na enc a zero*/
			sistema[iden1].quan+=encomendas[id1].conjunto[c].quan;
			encomendas[id1].conjunto[c].quan=0;
			
		}
		else
			printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",iden1,id1);
	}
	else
		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",iden1,id1);
}
/*funcao que e responsavel pelo comando c.
calcula o custo de uma encomenda*/
void comando_c(){
	int id1,soma=0,j;
	scanf("%d",&id1);
	if (verfiqua_enc(id1)){
		/*precorrer os prdutos da encomenda dada*/
		for (j=0;j<encomendas[id1].N;j++)
			/*e soma os precos de todos os prdutos*/
			soma+=sistema[encomendas[id1].conjunto[j].iden].preco*encomendas[id1].conjunto[j].quan;
		printf("Custo da encomenda %d %d.\n",id1,soma);
	}
	else
		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",id1);
}
/*funcao que e responsavel pelo comando p.
altera o preco de um dado prduto*/
void comando_p(){
	int iden1,preco;
	scanf("%d:%d",&iden1,&preco);
	if (verfiqua_prod(iden1))
		sistema[iden1].preco=preco;
	else
		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",iden1);
	
}
/*funcao que e responsavel pelo comando E.
lista a discricao e a quan do prduto nma enc*/
void comando_E(){
	int iden1,id1,i=0;
	scanf("%d:%d",&id1,&iden1);
	if (verfiqua_enc(id1)){	
		if (verfiqua_prod(iden1)){
			if (verfiqua_pro_enc(id1,iden1)){
				/*se o prduto existir na enc lista a discricao e a quan*/
				printf("%s %d.\n",sistema[iden1].desc,encomendas[id1].conjunto[obtanha_indreco(id1,iden1)].quan);
			}
			else
				/*caso contrario lista a discricao e zero*/
				printf("%s %d.\n",sistema[iden1].desc,i);
		}
		else
			printf("Impossivel listar produto %d. Produto inexistente.\n",iden1);	
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id1);    
}
/*funcao que e responsavel pelo comando m.
lista a enc e a quan do prduto com mais quan*/
void comando_m(){
	int iden1,max=0,i,e;
	scanf("%d",&iden1);
	if (verfiqua_prod(iden1)){
		/*precorrer todas as encomendas*/
		for (i=0;i<id;i++){
			/*se o prduto esta na enc e a quan desse prduto for maior de que zero*/
			if(verfiqua_pro_enc(i,iden1) && encomendas[i].conjunto[obtanha_indreco(i,iden1)].quan ){
				if(encomendas[i].conjunto[obtanha_indreco(i,iden1)].quan > max){
					/*achar a enc com prod com mais quan*/
					max = encomendas[i].conjunto[obtanha_indreco(i,iden1)].quan;
					/*guardar o indreco da encomenda que tem o prduto com mais quan*/
					e=encomendas[i].id;
			}
			/*se hover mais que uma enc com prod com mais quan*/
			else if(encomendas[i].conjunto[obtanha_indreco(i,iden1)].quan == max && encomendas[i].conjunto[obtanha_indreco(i,iden1)].quan){
				/*acha a enc com menor id e guarda_o no e*/
				if (encomendas[i].id < e)
					e = encomendas[i].id;
			}
			}
		}
		if (max)					
		printf("Maximo produto %d %d %d.\n",iden1,e,max);
	}
	else
		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",iden1);

}
/*funcao auxliar para detrminar
 o menor entre dois valores*/
int less(int j,int i){
		if (j < i)
			return 1;
		else
			return 0;
}
/*funcao merge dos slides*/
void merge(prod a[], int l, int m, int r){
	int i,j,k;
	for (i=m+1;i>l;i--)
		aux[i-1]=a[i-1];
	for(j=m;j<r;j++)
		aux[r+m-j]=a[j+1];
	for (k=l;k<=r;k++){
		/*coparar os precos se forem iguais comparar os ides*/
		if(less(aux[j].preco,aux[i].preco)||(aux[j].preco==aux[i].preco && aux[j].iden < aux[i].iden))
			a[k]=aux[j--];
		else
			a[k]=aux[i++];
	}	
}
/*funcao mergesort dos slides*/
void mergesort(prod a[], int l, int r){
	int m =(l+r)/2;
	if (r<=l)
		return;
	mergesort(a,l,m);
	mergesort(a,m+1,r);
	merge(a,l,m,r);
}
/*funcao que e responsavel pelo comando l.
ordena os prdutos palos seus precos*/
void comando_l (){
	int c,i;
	/*vetor que e copia da sistema*/
	prod sistema1[MAX_N];
	/*precorrer todos os prdutos da sistema*/
	for (i=0;i<iden;i++)
		/*copiar sistema para sistema1*/
		sistema1[i]=sistema[i];
	/*oredenar sistema1 atraves das foncoes merge e mergesort*/
	mergesort(sistema1,0,iden-1);
	/*printar a sistema1 oredenada*/
	printf("Produtos\n");
	for(c=0;c<iden;c++){
		printf("* %s %d %d\n",sistema1[c].desc,sistema1[c].preco,sistema1[c].quan);
	}
}
/*funcao que e responsavel pelo comando L.
ordena os prdutos de uma enc pela ordem da discricao
atravez de implantacao de selection sort*/
void comando_L(){
	int i,j,id1,e;
	scanf("%d",&id1);
	if (verfiqua_enc(id1)){
		/*precorrer os prdutos da enc a partir do inicio*/
		for (i=0;i<encomendas[id1].N;i++){
			int min=i;
			/*varivel para fazer as trocas entre os prdutos*/
			prod_enc aux;
			/*precorrer os prdutos da enc a partir do i+1*/
			for(j=i+1;j<encomendas[id1].N;j++){
				/*se a disc no indice j for menor do que indice min entao o min passa a ser igual a j*/ 
				if(strcmp(sistema[encomendas[id1].conjunto[j].iden].desc,sistema[encomendas[id1].conjunto[min].iden].desc)<0)
					min=j;
			}
			/*faz a troca usando a varivel aux*/
			aux=encomendas[id1].conjunto[i];encomendas[id1].conjunto[i]=encomendas[id1].conjunto[min];encomendas[id1].conjunto[min]=aux;
		}
		/*printa a encomenda daada oredenada*/
		printf("Encomenda %d\n",id1);
		for(e=0;e<encomendas[id1].N;e++){
			if (encomendas[id1].conjunto[e].quan)
				printf("* %s %d %d\n",sistema[encomendas[id1].conjunto[e].iden].desc,sistema[encomendas[id1].conjunto[e].iden].preco,encomendas[id1].conjunto[e].quan);
		}
	}
	else
		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",id1);
}
int main(){
	char c;
	/*variavel de estado*/
	int termina=1;
	/*precorre o fichero do input e guarda no c um crater de cada vez*/
	while ((c=getchar())!=EOF && termina){
		switch(c){
			case'a':
			comando_a();
			break;
			case'q':
			comando_q();
			break;
			case'N':
			comando_N();
			break;
			case'A':
			comando_A();
			break;
			case 'r':
			comando_r();
			break;
			case 'R':
			comando_R();
			break;
			case 'C':
			comando_c();
			break;
			case 'p':
			comando_p();
			break;
			case 'E':
			comando_E();
			break;
			case 'm':
			comando_m();
			break;
			case 'l':
			comando_l();
			break;
			case 'L':
			comando_L();
			break;
			case 'x':
			termina=0;
			break;
		}
	}
	return 0;
}
