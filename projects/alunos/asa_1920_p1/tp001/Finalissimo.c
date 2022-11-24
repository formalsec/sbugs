#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>




typedef struct vertices_s {
	int valor;
	int visitado;
	int* adj;
	int deg;
	int size;
} vertices_s;

vertices_s* vertices;


void create(int []);
void down_adjust(int [],int);

void heap(int* heap, int n)
{
	int last,temp;
	heap[0]=n;
	create(heap);

	while(heap[0] > 1)
	{
		last=heap[0];
		temp=heap[1];
		heap[1]=heap[last];
		heap[last]=temp;
		heap[0]--;
		down_adjust(heap,1);
	}

	heap[n+1]=-1;

}

void create(int heap[])
{
	int i,n;
	n=heap[0]; 

	for(i=n/2;i>=1;i--)
		down_adjust(heap,i);
}

void down_adjust(int heap[],int i)
{
	int j,temp,n,flag=1;
	n=heap[0];

	while(2*i<=n && flag==1)
	{
		j=2*i;   
		if(j+1<=n && vertices[heap[j+1]].valor < vertices[heap[j]].valor)
			j=j+1;
		if(vertices[heap[i]].valor < vertices[heap[j]].valor)
			flag=0;
		else
		{
			temp=heap[i];
			heap[i]=heap[j];
			heap[j]=temp;
			i=j;
		}
	}
}

void dfs_vist(int indice){
	int i;
	vertices[indice].visitado = 1;
	for (i = 0; i < vertices[indice].deg; i++){
		if (vertices[vertices[indice].adj[i]].visitado == 0){
			vertices[vertices[indice].adj[i]].valor = vertices[indice].valor;
			dfs_vist(vertices[indice].adj[i]);
		}
	}
}

void dfs(int num_vertices,int* vect){
	int i;
	for (i = 1; i<= num_vertices; i++){
		if (vertices[vect[i]].visitado == 0){
			dfs_vist(vect[i]);
		}
	}
}
  

int main(){

	int num_vertices;
	int num_ligacoes;
	int cont;
	int val; 
	int indice;
	int vert;

	scanf("%d,%d", &num_vertices, &num_ligacoes);

	int vect[num_vertices+1];

	vertices=can_fail_malloc(sizeof(vertices_s)*(num_vertices));

	for (cont=0; cont<num_vertices; cont++){

		scanf("%d",&val);
		vertices[cont].valor = val;
		vertices[cont].adj=can_fail_malloc(sizeof(int)*2);
		vertices[cont].visitado = 0;
		vertices[cont].size=2;
		vertices[cont].deg = 0;
		vect[cont+1] = cont;
	}

	for (cont=0; cont< num_ligacoes; cont++){

		scanf("%d %d",&vert, &indice);
		indice--;
		if(vertices[indice].deg>vertices[indice].size){
			vertices[indice].size = vertices[indice].size*2;
			vertices[indice].adj=can_fail_realloc(vertices[indice].adj, sizeof(int)*vertices[indice].size);
		}
		vertices[indice].adj[vertices[indice].deg] = vert-1;
		vertices[indice].deg++;
	}

	heap(vect, num_vertices);
	dfs(num_vertices,vect);

	for(cont=0;cont<num_vertices;cont++){
		printf("%d\n", vertices[cont].valor);
	}


	return 0;

}




