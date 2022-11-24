#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_products 10000
#define Max_orders 500			
#define Max_size_description 64
#define Max_weight_orders 200
#define Max_comand_size 100
#define Used 1
#define Not_used -1

typedef struct {
	char used;
	char description[Max_size_description];
	int price;
	int weight;
	int amount;
}product_struct;

typedef struct {
	char used;
	int product_id[Max_products];
	int amount[Max_products];
}orders_struct;

/* Declaracao de prototipos. */
int input1(char v[]);
int input2();
void inicialize(orders_struct v[],product_struct v1[]);
void mergesort(int v[][2], int l, int r);
void mergesort_string(char v[][Max_size_description],int id[], int l, int r);
product_struct products[Max_products];
orders_struct orders[Max_orders];

int main(){
	char c[Max_comand_size];
    inicialize(orders, products);
	do{
        fgets(c, Max_comand_size, stdin); /* Le o comando dado e guarda na variavel "c" */
		switch (c[0]) {
			case 'a':{
				char d[Max_size_description],*s;
				int new_id,len,l;
				/* Verifica qual ? o id do proximo produto a ser registado. */
				for(new_id = 0; products[new_id].used!=Not_used; new_id++)	
					continue;
				strtok(c, " ");
				s=strtok((strtok(NULL, " ")), ":");
				if (s==0)
					break;
				products[new_id].price=input2();
				products[new_id].weight=input2();
				products[new_id].amount=input2();				
				products[new_id].used=Used;
				len=(strlen(s)+1);
				for(l = 0;(l!=len && l<Max_size_description);l++)
					d[l] = s[l];
				strcpy(products[new_id].description,d);	
				printf("Novo produto %d.\n",new_id);
				break;
			}

			case 'q' :{
				int id=input1(c),a=input2();
				if (products[id].used==Not_used)
					printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",id);
				else
					products[id].amount+=a;
				break;
			}

			case 'N' :{
				int new_order;
				/* Verifica qual ? a proxima encomenda a ser criada. */
				for(new_order = 0; orders[new_order].used!=Not_used; new_order++)
					continue;
				orders[new_order].used=Used;
				printf("Nova encomenda %d.\n",new_order);
				break;
			}

			case 'A' :{
				int i,w=0,encom=input1(c),prod=input2(),q=input2();
                for(i = 0; orders[encom].product_id[i]!=Not_used; i++)
                    w+=((products[orders[encom].product_id[i]].weight)*(orders[encom].amount[i]));
				if (orders[encom].used==Not_used){
					printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",prod, encom);
					break;
				}
				else if (products[prod].used==Not_used){
					printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",prod, encom);
					break;
				}
				else if (q>products[prod].amount){
					printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",prod, encom);
					break;
				}
				else if ((w+products[prod].weight*q)>Max_weight_orders){
					printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de %d.\n",prod, encom,Max_weight_orders);
                    break;
                }
				
				for (i = 0; orders[encom].product_id[i]!=Not_used || i==0; i++){
					/* Caso a encomenda ainda nao tenha nenhum produto. */
					if (orders[encom].product_id[i]==Not_used){
						orders[encom].product_id[i]=prod;
						orders[encom].amount[i]=q;
						products[prod].amount-=q;
						break;
					}
					/* Verifica se o produto ja existe na encomenda e adiciona a quantidade. */
					else if ((orders[encom].product_id[i])==prod){
						orders[encom].amount[i]+=q;
						products[prod].amount-=q;
						break;
                    }
                    /* Caso o produto nao exista na encomenda, adiciona-o. */
					else if (orders[encom].product_id[i+1]==Not_used){
						orders[encom].product_id[i+1]=prod;
						orders[encom].amount[i+1]=q;
						products[prod].amount-=q;
						break;
					}					
				}
				break;
			}

			case 'r' :{
				int prod=input1(c),a=input2();
				if (products[prod].used==Used){
					if (products[prod].amount>=a)
						products[prod].amount-=a;
					else
						printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",a,prod);
				}
				else
					printf("Impossivel remover stock do produto %d. Produto inexistente.\n",prod);
				break;
			}

			case 'R' :{
				int i,last,l,encom=input1(c),prod=input2();
				if (orders[encom].used==Used){
					if (products[prod].used==Used){
						/* Procura pelo produto na encomenda. */
						for(i = 0; i!=Max_products; i++)
							if ((orders[encom].product_id[i])==prod){
								/* Verifica qual e o ultimo produto da encomenda 
								 * e coloca-o no lugar do removido. */
								for(l = i; orders[encom].product_id[l]!=Not_used; l++)
									last=l;
								products[prod].amount+=orders[encom].amount[i];
								orders[encom].product_id[i]=orders[encom].product_id[last];
								orders[encom].amount[i]=orders[encom].amount[last];
								orders[encom].product_id[last]=Not_used;
								orders[encom].amount[last]=0;
								break;
							}	
					}	
					else
						printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",prod,encom);
				}
				else
					printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",prod,encom);
				break;
			}

			case 'C' :{
				int i,encom=input1(c),pr=0;
				if (orders[encom].used==Not_used){
					printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",encom);
					break;
				}
				for (i = 0; orders[encom].product_id[i]!=Not_used; i++)
					pr+= orders[encom].amount[i]*products[orders[encom].product_id[i]].price;
				printf("Custo da encomenda %d %d.\n",encom,pr);
				break;
			}

			case 'p' :{
				int prod=input1(c),pr=input2();
				if (products[prod].used == Not_used){
					printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",prod);
					break;
				}
				else
					products[prod].price=pr;
				break;
			}

			case 'E' :{
				int i,encom=input1(c),prod=input2();
				if (products[prod].used == Not_used){
					printf("Impossivel listar produto %d. Produto inexistente.\n",prod);
					break;
				}
				if (orders[encom].used == Not_used){
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",encom);
					break;
				}
				for(i = 0; i!=Max_products; i++){
					/* Caso o produto nao exista na encomenda. */
					if (orders[encom].product_id[i]==Not_used){
						printf("%s 0.\n",products[prod].description);
						break;
					}
					else if (orders[encom].product_id[i]==prod){
						printf("%s %d.\n",products[prod].description,orders[encom].amount[i]);
						break;
					}
				}
				break;
			}

			case 'm' :{
				int o,i,prod=input1(c),larger_amount=Not_used,q=0;
				if (products[prod].used == Not_used){
					printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",prod);
					break;
				}
				/* Verifica em cada encomenda, cada produto e verifica
				 * qual e a encomenda com maior quantidade desse produto. */
				for(o = 0; o!=Max_orders; o++)
					for(i = 0; i!=Max_products; i++){
						if ((orders[o].product_id[i])==prod){
							if (orders[o].amount[i]>q){
								larger_amount=o;
								q=orders[o].amount[i];
							}
							break;
						}
						/* Caso nao haja mais nenhum produto na 
						 * encomenda passa para a proxima. */
						else if ((orders[o].product_id[i])==Not_used)
							break;				
					}
				if (larger_amount!=Not_used)
					printf("Maximo produto %d %d %d.\n",prod,larger_amount,q);
				break;
			}

			case 'l' :{
				int i,sorted[Max_products][2];
				/* Cria um array bidimensional com todos os produtos onde  
				 * em sorted[][0] esta o preco e em sorted[][1] esta o id. */
				for(i = 0; products[i].used!=Not_used; i++){
					if (products[i].used==Used){
						sorted[i][0]=products[i].price;
						sorted[i][1]=i;
					}
					else
						break;
				}
				/* Ordena por preco o array com os produtos. */
				mergesort(sorted,0,i-1);
				printf("Produtos\n");
				for (i = 0; products[i].used!=Not_used; i++)
					printf("* %s %d %d\n",products[sorted[i][1]].description,sorted[i][0],products[sorted[i][1]].amount);	
				break;
			}

			case 'L' :{
				int i,j,sorted_id[Max_products],encom=input1(c);
				char sorted_description[Max_products][Max_size_description];
				if (orders[encom].used == Not_used){
					printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",encom);
					break;
				}
				/* Cria dois arrays, um com a descricao e outro com  
				 * o id correspondente. */
				for(i = 0; orders[encom].product_id[i]!=Not_used; i++){
					if (orders[encom].product_id[i]!=Not_used){
						strcpy(sorted_description[i],products[orders[encom].product_id[i]].description);
						sorted_id[i]=orders[encom].product_id[i];
					}
					else
						break;
				}
				/* Ordena por ordem alfabetica da descricao os arrays. */
				mergesort_string(sorted_description,sorted_id,0,i-1);
				printf("Encomenda %d\n",encom);
				for (i = 0; orders[encom].product_id[i]!=Not_used; i++){
					for (j = 0; j!=Max_products; j++)
						if (orders[encom].product_id[j]==sorted_id[i]){
							printf("* %s %d %d\n",sorted_description[i],products[sorted_id[i]].price,orders[encom].amount[j]);
							break;	
						}
				}
				break;
			}
		}
	}while (c[0]!='x');
	return 0;
}

/* Inicializar as estruturas com determinados valores. */
void inicialize(orders_struct v[],product_struct v1[]){
	int j,i;
	for(j = 0;j<Max_orders;j++){
        v[j].used=Not_used;
		for(i = 0;i<Max_products;i++)
			v[j].product_id[i]=Not_used;
    }
	for(j = 0;j<Max_products;j++)
			v1[j].used=Not_used;
}

/* Ler o proximo valor/string a seguir ao comando. */
int input1(char v[]){
	char *s;
	strtok(v, " ");
	s = strtok((strtok(NULL, " ")), ":");
	return atoi(s);
}

/* Ler o os proximos valores a seguir ao primeiro valor/string. */
int input2(){
	char *s;
	s= strtok(NULL, ":");
	return atoi(s);
}

/* Ordenar os precos de acordo com o seu valor,e 
 * mantendo, se iguais ordenados por id. */
void merge(int v[][2], int l,int m, int r){
	int i,j,k, aux[Max_products][2];
	for(i=m+1;i>l;i--){
		aux[i-1][0]=v[i-1][0];
		aux[i-1][1]=v[i-1][1];
    }
	for(j=m;j<r;j++){
		aux[r+m-j][0]=v[j+1][0];
		aux[r+m-j][1]=v[j+1][1];
    }
	for (k=l;k<=r;k++){
		if (aux[j][0]<aux[i][0]){
			v[k][0]=aux[j][0];
			v[k][1]=aux[j--][1];
        }
		else if(aux[j][0]>aux[i][0]){
			v[k][0]=aux[i][0];
			v[k][1]=aux[i++][1];
        }
        else if(aux[j][0]==aux[i][0]){
			if (aux[j][1]>aux[i][1]){
				v[k][0]=aux[i][0];
				v[k][1]=aux[i++][1];
			}
			else{
				v[k][0]=aux[j][0];
				v[k][1]=aux[j--][1];
			}
		}
	}
}

/* Ordenar o array de acordo com o preco (v[][0]),
 *  e ir guardando o id correspondente (v[][1]). */
void mergesort(int v[][2], int l, int r){
	int m =(r+l)/2;
	if (r<=l)
		return;
	mergesort(v,l,m);
	mergesort(v,m+1,r);
	merge(v,l,m,r);
}

/* Ordenar as strings com o strcmp(). */
void merge_string(char v[][Max_size_description],int id[], int l,int m, int r){
	int i,j,k,aux1[Max_products];
	char aux[Max_products][Max_size_description];
	for(i=m+1;i>l;i--){
		strcpy(aux[i-1],v[i-1]);
		aux1[i-1]=id[i-1];
    }
	for(j=m;j<r;j++){
		strcpy(aux[r+m-j],v[j+1]);
		aux1[r+m-j]=id[j+1];
    }
	for (k=l;k<=r;k++){
		if (strcmp(aux[j],aux[i])<0){
			strcpy(v[k],aux[j]);
			id[k]=aux1[j--];
        }
		else{
			strcpy(v[k],aux[i]);
			id[k]=aux1[i++];
        }
	}
}

/* Ordenar o array de acordo com a descricao (v[][Max_size_description]),
 *  e ir guardando o id correspondente (id[]). */
void mergesort_string(char v[][Max_size_description],int id[], int l, int r){
	int m =(r+l)/2;
	if (r<=l)
		return;
	mergesort_string(v,id,l,m);
	mergesort_string(v,id,m+1,r);
	merge_string(v,id,l,m,r);
}
