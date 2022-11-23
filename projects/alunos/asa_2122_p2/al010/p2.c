#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int v;
	struct node * next;
} node;

typedef struct graph{
	int n;
	node ** adj;
} G;


G * newGraph(int n){
	int i;

	G * g = can_fail_malloc(sizeof(G));
	g->n=n;
	g->adj=can_fail_malloc(n*sizeof(node*));

	for(i=0;i<n;i++){
		g->adj[i]=NULL;
	}

	return g;

}

node * newNode(int v){
	node * new = can_fail_malloc(sizeof(node));
	new->v=v;
	new->next=NULL;
	return new;
}

void newEdge(G * g, int s,int d){
	node * new = newNode(d);
	new->next=g->adj[s-1];
	g->adj[s-1] = new;
}

void printAdj(G * g){
	int i;
	node * tmp;
	for(i=0;i<g->n;i++){
		tmp = g->adj[i];
		while(tmp!=NULL){
			printf("%d -> %d\n",i+1,tmp->v);
			tmp = tmp->next;
		}	
	}
}

int isCyclicAux(G * g,int v,int * visit,int * stack){

	node * iter;

	if(!visit[v-1]){
		visit[v-1]=1;
		stack[v-1]=1;

		iter = g->adj[v-1];
		while(iter != NULL){
			if(!visit[iter->v-1] && isCyclicAux(g,iter->v,visit,stack))
				return 1;
			else if (stack[iter->v-1])
				return 1;
			iter = iter->next;
		}
	}
	stack[v-1]=0;
	return 0;
}

int isCyclic(G * g){

	int * visit = can_fail_malloc(sizeof(int)*g->n);
	int * stack = can_fail_malloc(sizeof(int)*g->n);
	int i;

	for(i=0;i<g->n;i++){
		visit[i]=0;
		stack[i]=0;
	}

	for(i=1;i<=g->n;i++){
		if(isCyclicAux(g,i,visit,stack)){
			free(visit);
			free(stack);
			return 1;
		}
	}
	free(visit);
	free(stack);
	return 0;
}

int DFSaux(G * g,int v,int * visited,int * canReach,int goal){
	node * aux = g->adj[v];
	visited[v]=1;

	while(aux!=NULL){
		if(!visited[aux->v-1]){
			if (aux->v == goal)
				return 1;
			if (DFSaux(g,aux->v-1,visited,canReach,goal)){
				canReach[aux->v-1]=1;
				return 1;
			}
		}
		else{
			if(canReach[aux->v-1]==1)
				return 1;
		}
		aux = aux->next;
	}
	return 0;
}

int * findVDFS(G * g, int v){
	int * visited,i,*canReach;

	visited = can_fail_malloc(g->n*sizeof(int));
	canReach = can_fail_malloc(g->n*sizeof(int));

	for(i=0;i<g->n;i++){
		visited[i]=0;
		canReach[i]=0;
	}

	for(i=0;i<g->n;i++){
		if (!visited[i]){
			if(DFSaux(g,i,visited,canReach,v))
				canReach[i]=1;
		}
	}

	/*printf("Target: %d\n",v);
	for(i=0;i<g->n;i++){
		printf("%d : %d\n",i+1, canReach[i]);
	}*/

	free(visited);

	return canReach;
}


void freeGraph(G * g){
	int i;
	node * tmp;

	for(i=0;i<g->n;i++){
		
		while(g->adj[i]!=NULL){
			tmp = g->adj[i];
			g->adj[i] = g->adj[i]->next;
			free(tmp);
		}
	}
	free(g->adj);
	free(g);
}

int isTree(G * g,int * connected,int * nParents){
	int i;

	for(i=0;i<g->n;i++){
		/*if(connected[i]==0){
			printf("0\n");
			return 0;
		}*/
		if(nParents[i]>2){
			printf("0\n");
			return 0;
		}
	}

	if(isCyclic(g)){
		printf("0\n");
		return 0;
	}
	return 1;
}


int zeroOutDeg(G * g,int v,int * common,int n){
	int i;
	node * tmp=g->adj[v];


	while(tmp!=NULL){
		for(i=0;i<n;i++){
			if (tmp->v == common[i]+1)
				return 0;
		}
		tmp = tmp->next;	
	}
	return 1;
}

int main(int argc, char const *argv[])
{
	int v1,v2,nV,nE,i,a,b,count=0;
	G * g;
	v1=v2=nV=nE=a=b=0;
	int * connected, *nParents,*reachV1,*reachV2,*commonAncestors;

	commonAncestors=reachV1=reachV2=NULL;

	if(scanf("%d %d",&v1,&v2)!= 2) return -1;
	if(scanf("%d %d",&nV,&nE)!=2) return -1;

	connected = can_fail_malloc(sizeof(int)*nV);
	nParents = can_fail_malloc(sizeof(int)*nV);

	for(i=0;i<nV;i++){
		nParents[i]=0;
		connected[i]=0;
	}

	g = newGraph(nV);

	for(i=0;i<nE;i++){
		if(scanf("%d %d",&a,&b)!=2) return -1;
		newEdge(g,a,b);
		connected[a-1]=1;
		connected[b-1]=1;
		nParents[b-1]++;
	}
	/*printAdj(g);*/

	if(isTree(g,connected,nParents)){
		reachV1 = findVDFS(g,v1);
		reachV2 = findVDFS(g,v2);

		commonAncestors = can_fail_malloc(sizeof(int)*nV);

		for(i=0;i<g->n;i++){
			if(reachV1[i]==1 && reachV2[i]==1){
				commonAncestors[i]=1;
				commonAncestors[count] = i;
				count++;
			}
			else{
				commonAncestors[i]=0;
			}
		}
		if(count == 0){
			printf("-\n");
		}
		else{
			commonAncestors = can_fail_realloc(commonAncestors,count*sizeof(int));

			for(i=0;i<count;i++){
				if(zeroOutDeg(g,commonAncestors[i],commonAncestors,count))
					printf("%d ",commonAncestors[i]+1);
			}
			printf("\n");
		}	
	}

	free(connected);
	free(nParents);
	free(commonAncestors);
	free(reachV1);
	free(reachV2);
	freeGraph(g);


	return 0;
}