#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define white 0
#define grey 1
#define black 2
#define off 3
/*item para linked list do segunda linha*/
typedef struct Item{
	int n;
	struct Item* prev;
	struct Item* next;
}Item;
Item criaitem(int n){
	Item nitem;
	nitem.n=n;
	nitem.prev=NULL;
	nitem.next=NULL;
	return nitem;
}
void incertitem(Item* item0,Item* insertable){
	Item* temporaryi=item0;
	if(item0->next==NULL){
		insertable->prev=item0;
		item0->next=insertable;
	}
	else{
		while(temporaryi->next!=NULL &&temporaryi->next->n<insertable->n){
			temporaryi=temporaryi->next;;
		}
		if(temporaryi->next==NULL){
			temporaryi->prev->next->next=insertable;
			insertable->prev=temporaryi->prev->next;
			return;
		}
		else if(temporaryi->n==0){
			temporaryi->next->prev=insertable;
			insertable->next=item0->next;
			insertable->prev=item0;
			item0->next=insertable;
			return;
		}
		else{
			temporaryi->next->prev=insertable;
			insertable->next=temporaryi->prev->next->next;
			insertable->prev=temporaryi->prev->next;
			temporaryi->prev->next->next=insertable;
		}
	}
}
/* da o numero de suberedes com uma dfs*/
void DFSvisiter(int** matriz,int i,int* nofwhiterouters,int* wrouters,Item* biguest){
	wrouters[i]=grey;
	int j;
	for(j=1;j<matriz[i][0];j++){
		if(wrouters[matriz[i][j]-1]==white){
			DFSvisiter(matriz,matriz[i][j]-1,nofwhiterouters,wrouters,biguest);
		}
	}
	wrouters[i]=black;
	if(biguest->n<i+1){
		biguest->n=i+1;
	}
	*nofwhiterouters=*nofwhiterouters-1;
}
int subnetsnumber(int routers,int** matriz,Item* x){
	int subnetnumber=1;
	int i;
	int *nofwhiterouters=(int*) malloc (sizeof(int));
	*nofwhiterouters=routers;
	int wrouters[routers];
	for(i=0;i<routers;i++)
		wrouters[i]=0;
	for(i=0;i<routers;i++){
		if(wrouters[i]==white){
			Item* correntitem=(Item*)malloc(sizeof(Item));
			*correntitem=criaitem(i+1);
			DFSvisiter(matriz,i,nofwhiterouters,wrouters,correntitem);
			incertitem(x,correntitem);
			if(*nofwhiterouters!=0)
				subnetnumber++;
		}
	}
	free(nofwhiterouters);
	return subnetnumber;

}

/*da o maior numero de routers possivel noma subrede sem routers partiveis;*/
void DFSmissigALL(int routers,int** matriz,int i,int* listTOoff,int* nofwhiterouters,int* routerspercorridos){
	listTOoff[i]=grey;
	int j;
	for(j=1;j<matriz[i][0];j++){
		if(listTOoff[matriz[i][j]-1]==white){
			DFSmissigALL(routers,matriz,matriz[i][j]-1,listTOoff,nofwhiterouters,routerspercorridos);
		}
	}
	*routerspercorridos=*routerspercorridos + 1;
	listTOoff[i]=black;
	*nofwhiterouters=*nofwhiterouters-1;
}
int subnetmissingall(int routers,int** matriz,int NdeOFFrouters,int* listTOoff){
	int bigssubnetrouters=0;
	int i;
	int *nofwhiterouters=(int*) malloc (sizeof(int));
	*nofwhiterouters=routers-NdeOFFrouters;
	int *routerspercorridos=(int*) malloc (sizeof(int));
	for(i=0;i<routers;i++){
		if(listTOoff[i]== white){
			*routerspercorridos=0;
			DFSmissigALL(routers,matriz,i,listTOoff,nofwhiterouters,routerspercorridos);
			if(bigssubnetrouters<*routerspercorridos){
				bigssubnetrouters=*routerspercorridos;
			}
		}

	}
	free(nofwhiterouters);
	free(routerspercorridos);
	return bigssubnetrouters;

}
void breakingvisit(int vertice,int* visited,int* div,int* l,int* pais,int *offLIST,int* time,int** matriz){
	int filhos=0;
	int i;
	visited[vertice]=1;
	*time=*time + 1;
	div[vertice]=*time;
	l[vertice]=*time;
	for(i=1;i<matriz[vertice][0];i++){
		int v = matriz[vertice][i]-1;
		if(visited[v]==0){
			filhos++;
			pais[v]=vertice;
			breakingvisit(v, visited,div,l,pais,offLIST,time,matriz);
			if(l[vertice]>=l[v])
				l[vertice]=l[v];
			if(pais[vertice]==-1 && filhos>1){
				offLIST[vertice]=off;
			}
			if(pais[vertice]!=-1 && l[v]>=div[vertice]){
				offLIST[vertice]=off;
			}
		}
		else if(v !=pais[vertice]){
			if(l[vertice]>=div[v])
				l[vertice]=div[v];
		}
	}

}

void get_breaking_routers(int routers, int* offLIST,int** matriz){
	int i;
	int abselutetime=0;
	int div[routers];
	int l[routers];
	int visited[routers],pais[routers];
	for(i=0;i<routers;i++){
		div[i]=0;
		l[i]=INT_MAX;
		visited[i]=0;
		pais[i]=-1;
	}
	for(i=0;i<routers;i++){
		if(visited[i]==0){
			breakingvisit(i,&visited[0],&div[0],&l[0],&pais[0],offLIST,&abselutetime,matriz);
		}
	}
}

int main(){
	int routers;
	int connectors;
	int i;
	int con1,con2;
	int** matriz;
	int originalsub;
	int breakingrouter=0;
	Item* x=(Item*) malloc (sizeof(Item));
	*x=criaitem(0);
	/*lê e da as primeiras informacoes do stdin;*/
	scanf("%d\n",&routers);
	scanf("%d\n",&connectors);
	/*cria a matriz (limpa) a ser usada*/
	matriz=(int**) malloc (routers*sizeof(int*));
	for(i=0;i<routers;i++){
		matriz[i]=(int*) malloc (sizeof(int));
		matriz[i][0]=1;
	}
	/*prenche a matriz*/
	for(i=0;i<connectors;i++){
		scanf("%d %d\n",&con1,&con2);
		matriz[con1-1][0]++;
		matriz[con1-1]=(int*) realloc (matriz[con1-1],sizeof(int)*matriz[con1-1][0]);
		matriz[con1-1][matriz[con1-1][0]-1]=con2;
		matriz[con2-1][0]++;
		matriz[con2-1]=(int*) realloc (matriz[con2-1],sizeof(int)*matriz[con2-1][0]);
		matriz[con2-1][matriz[con2-1][0]-1]=con1;
	}
	/*print do primeiro e prepara o segundo*/
	originalsub=subnetsnumber(routers,matriz,x);
	printf("%d\n",originalsub);
	/*print do segundo*/
	Item* printitem=x->next;
	while(printitem->next!=NULL){
		printf("%d ",printitem->n);
		printitem=printitem->next;

	}
	printf("%d\n",printitem->n);
	while(printitem->prev!=NULL){
		printitem=printitem->prev;
		free(printitem->next);
	}
/*print do terceiro e marcar os routers que quebram*/
	int offLIST[routers];
	for(i=0;i<routers;i++)
		offLIST[i]=0;

	get_breaking_routers(routers,&offLIST[0],matriz);


	int count=0;
	for(i=0;i<routers;i++){
		if(offLIST[i]==off){
			count++;
		}
	}	
	breakingrouter=count;
	printf("%d\n",count);

	/*print do 4*/
	printf("%d\n",subnetmissingall(routers,matriz,breakingrouter,offLIST));
	/*faz free de todo antes de terminar*/
	free(x);
	for(i=0;i<routers;i++){
		free(matriz[i]);
	}
	free(matriz);
	return 0;
}