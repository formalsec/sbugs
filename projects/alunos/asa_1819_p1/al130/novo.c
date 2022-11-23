#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#define UNVISITED -1
#define FALSE -2
#define TRUE 1

typedef struct Stack {
	int top;
	int size;
	int* value;
}*Stack;

void findSccs(int n, int* id, int* counter, int* ids, int* low, int* onStack, Stack stack, int** matriz);
void dfs(int i,int n, int* id, int* counter, int* ids, int* low, int* onStack, Stack stack, int** matriz);
int min(int a, int b);
Stack createStack(int size);
int isStackEmpty(Stack stack);
void push(Stack stack, int value);
int pop(Stack stack);
int cmpfunc (const void *a, const void * b);
void resetValues(int n, int* counter, int* id, int *ids, int *low, int* onStack);
void createAdjacencyMatrix(int** matriz, int n);
void readAdjacencyMatrix(int** matriz);
void findSubRede(int* aux, int n, int* counter, int* low, int* ids);
int sccTest(int n, int* counter, int* id, int* ids, int* low, int* onStack, int** matriz, Stack stack, int* list, int* counteraux);
void biggestSubRede(int k, int n, int** matriz, int* low, int* onStack, int* ids, int* id, int* counteraux, Stack stack, int* list);

int main() {
	int n,i,id=0,counter,k,counteraux;

	scanf("%d", &n);

	int* ids= (int*) can_fail_malloc(sizeof(int)*n);
	int* low= (int*) can_fail_malloc(sizeof(int)*n);
	int* aux;
	int* onStack= (int*) can_fail_malloc(sizeof(int)*n);
	int** matriz= (int**) can_fail_malloc(sizeof(int*)*n);
	int* list= (int*) can_fail_malloc(sizeof(int)* n);
	Stack stack= createStack(n);

	/*inicializar os vetores*/
	resetValues(n,&counter,&id, ids,low,onStack);


	createAdjacencyMatrix(matriz,n);
	readAdjacencyMatrix(matriz);

	findSccs(n,&id,&counter,ids,low,onStack,stack,matriz);


	/*primeiro print*/
	printf("%d\n",counter);

	/*segundo print*/
	aux=(int*) can_fail_malloc(sizeof(int)*counter);
	findSubRede(aux,n,&counter,low,ids);
	for(i=0; i<counter-1; i++) {
		printf("%d ", aux[i]);
	}
	printf("%d\n",aux[i]);

	/*terceiro print*/
	k=sccTest(n,&counter,&id,ids,low,onStack,matriz,stack,list,&counteraux);

	/*quarto print*/
	biggestSubRede(k,n,matriz,low,onStack,ids,&id,&counteraux,stack,list);

	free(ids);
	free(low);
	free(list);
	free(onStack);
	free(stack->value);
	free(stack);
	free(aux);
	for(i=0; i<n; i++) {
		free(matriz[i]);

	}
	free(matriz);
	return 0;
}

void createAdjacencyMatrix(int** matriz, int n) {
	/* meter a matriz de adjacencias a 0 */
	int i,j;
	for(i=0; i<n; i++) {
		matriz[i]=(int*) can_fail_malloc(sizeof(int)*n);
	}
	for(i=0;i<n;i++)
		for(j=i;j<n;j++)
			matriz[i][j]=matriz[j][i]=0;
}

void readAdjacencyMatrix(int** matriz) {
	/*ler as conexoes para a matriz de adjacencias*/
	int m,i,x,y;
	scanf("%d" , &m);
	for(i=0; i<m; i++) {
		scanf("%d %d", &x, &y);
		matriz[x-1][y-1]=1;
		matriz[y-1][x-1]=1;
	}
}


void resetValues(int n,int* counter,int* id,int* ids, int* low, int* onStack){
	int i;
	for(i=0; i<n; i++) {
		ids[i]=UNVISITED;
		low[i]=0;
		onStack[i]=FALSE;
	}
	*id=0;
	*counter=0;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void findSubRede(int* aux, int n, int* counter, int* low, int* ids) {
	int i,sccsFound=0,k=n-1;
	for(i=0; i<(*counter); i++) {
		aux[i]=0;
	}
	i=(*counter)-1;
	while(sccsFound<(*counter)){
		if(ids[low[k]]!=-1) {
			aux[i]=k+1;
			ids[low[k]]=-1;
			sccsFound++;
			i--;
		}
		k--;
	}
}

int sccTest(int n, int* counter, int* id, int* ids, int* low, int* onStack, int** matriz, Stack stack, int* list, int* counteraux) {
	int i,k=0,j;
	int* listaux= (int*) can_fail_malloc(sizeof(int)*n);
	for (i=0;i<n;i++){
		list[i]=0;
		listaux[i]=0;
	}
	resetValues(n,counteraux,id,ids,low,onStack);

	for (i=0; i<n; i++){
		for(j=0;j<n;j++){
			if (matriz[i][j]==1){
				matriz[i][j]=matriz[j][i]=0;
				listaux[j]=1;
			}
		}

		findSccs(n,id,counteraux,ids,low,onStack,stack,matriz);

		if ((*counteraux)-1>(*counter)){
			list[k]=i+1;
			k++;
		}
		resetValues(n,counteraux,id,ids,low,onStack);
		for(j=0;j<n;j++) {
			matriz[i][j]=matriz[j][i]=listaux[j];
		}
		for(j=0;j<n;j++)
			listaux[j]=0;
	}
	printf("%d\n", k);
	return k;
}

void biggestSubRede(int k, int n, int** matriz, int* low, int* onStack, int* ids, int* id, int* counteraux, Stack stack, int* list) {
	int i,j,max=0,maxaux=0;

	for (i=0;i<k;i++){
		for(j=0;j<n;j++){
			matriz[list[i]-1][j]=matriz[j][list[i]-1]=0;
		}
	}
	resetValues(n,counteraux,id,ids,low,onStack);
	findSccs(n,id,counteraux,ids,low,onStack,stack,matriz);

	for(i=0;i<n;i++){
		for (j=0;j<n;j++)
			if (low[j]==i)
				maxaux+=1;
		if (maxaux>max)
			max=maxaux;
		maxaux=0;
	}

	printf("%d\n",max );
}

void findSccs(int n, int* id, int* counter, int* ids, int* low, int* onStack, Stack stack, int** matriz) {
	int i;
	for(i=0; i<n; i++) {
		if(ids[i]==UNVISITED)
			dfs(i,n,id,counter,ids,low,onStack,stack,matriz);
	}
}

void dfs(int i,int n, int* id, int* counter, int* ids, int* low, int* onStack, Stack stack, int** matriz) {
	int j;
	push(stack,i);
	onStack[i]=TRUE;
	ids[i]=low[i]=(*id)++;

	for(j=0; j<n; j++) {
		if(matriz[i][j]==1) {
			if(ids[j]==UNVISITED)
				dfs(j,n,id,counter,ids,low,onStack,stack,matriz);
			if(onStack[j]) {
				low[i]=min(low[i],low[j]);
			}
		}
	}
	if(ids[i]==low[i]) {
		j=pop(stack);

		while(j!=-1){
			onStack[j]=FALSE;
			low[j]=ids[i];
			if(j==i)
				break;
			j=pop(stack);
		}
		(*counter)++;
	}

}

int min(int a, int b) {
    return a < b ? a : b;
}

Stack createStack(int size) {
	struct Stack* stack = (struct Stack*) can_fail_malloc(sizeof(struct Stack));
	stack->top=-1;
	stack->size=size;
	stack->value= (int*) can_fail_malloc(size*sizeof(int));
	return stack;
}

int isStackEmpty(Stack stack) {
	return stack->top==-1;
}

void push(Stack stack, int value) {
	(stack->top)++;
	stack->value[stack->top]=value;
}

int pop(Stack stack) {
	if(isStackEmpty(stack))
		return -1;
	return stack->value[(stack->top)--];
}
