#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Estruturas */

typedef struct connection {
	int id;
	struct connection *next;
}Connection;

typedef struct router {
	int id;
	Connection *head,*tail;
}Router;

typedef struct network {
	int N_rtrs;
	int M_cons;
	Router *routers;
}Network;


/* ------------------------- */

void create_router(int n,Network *nw) {
	/* Creates and initializes a router */
	Router r;
	r.id=n;
	r.head=NULL;
	r.tail=NULL;

	nw->routers[n]=r;
}


Connection* create_connection () {
	/* Allocate memory for a list connection */
	Connection *c=(Connection*)can_fail_malloc(sizeof(struct connection));

	return c;
}


void router_add_conn(int u, int v, Network *Nw) {
	/* Add v to u's adjacent list and vice-versa */

	if (Nw->routers[u].head==NULL) {
		/* Case 1: List is empty */
		Nw->routers[u].head=Nw->routers[u].tail=create_connection();
		Nw->routers[u].head->id=v;
		Nw->routers[u].head->next=NULL;
	}

	else if (Nw->routers[u].head==Nw->routers[u].tail) {
		/* Case 2: List only has 1 element */
		Nw->routers[u].tail=create_connection();
		Nw->routers[u].head->next=Nw->routers[u].tail;
		Nw->routers[u].tail->id=v;
		Nw->routers[u].tail->next=NULL;
	}

	else {
		Connection *c=create_connection();
		Nw->routers[u].tail->next=c;
		Nw->routers[u].tail=c;
		c->id=v;
		c->next=NULL;
	}
}

int* add_new_max(int *max, int newmax, int count) {
	/* Once a new sub network is found, save its ID i.e. the ID of the router with the highest ID by ascending order */

	max[count]=newmax;

	return max;
}

void DFS(int v, int visited[], Network *Nw, int *nrouters, int flag) { 
        visited[v] = 1; 

        Connection *c=Nw->routers[v].head;

		for (;c!=NULL;c=c->next){
            if(!visited[c->id]) {
            	if (flag) {
            		*nrouters = *nrouters + 1;
            	}
            	DFS(c->id,visited,Nw, nrouters, flag); /* Apply to adjacent routers if not visited */
            }
        } 
} 

void getSubNets(Network *Nw) { 
	/* Gets all the sub-networks from the mother network */
    int *visited=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(visited,0,(Nw->N_rtrs+1)*sizeof(int));
    int *max=(int *)can_fail_malloc(sizeof(int));
    int v, i, count=0;  

    for(v = Nw->N_rtrs; v>0; v--) {
        if(!visited[v]) {
        	max=can_fail_realloc(max,(count+1)*sizeof(int));
            DFS(v,visited,Nw,NULL,0);
            max = add_new_max(max,v,count);
            visited[0]=0; 
            count++; 
        } 
    }

    free(visited);
    printf("%d\n", count);

    printf("%d",max[count-1]);
    for (i=count-2;i>=0;i--)
    	printf(" %d", max[i]);
    printf("\n");	

    free(max);

}

void DFS_Tarjan(int v, int visited[], int dtime[], int ltime[], int parent[], int weak_routers[], int *time, Network *Nw) {
        visited[v] = 1;
        dtime[v] = *time;
        ltime[v] = *time;
        int nchildren = 0, possibleWR = 0;
        *time = *time + 1;

        Connection *c=Nw->routers[v].head;

		for (;c!=NULL;c=c->next){

            if(!visited[c->id]) {
            	/* DFS proceeds if the router wasn't visited yet*/

            	parent[c->id] = v;
            	nchildren++;
            	DFS_Tarjan(c->id,visited,dtime,ltime,parent,weak_routers,time,Nw); /* Apply to adjacent routers if not visited */

            	if (dtime[v] <= ltime[c->id]) {
            		/* If a vertex satisfies this condition, it can be a weak router, however we need to check that is isn't the root afterwards */
            		possibleWR = 1;
            	}

            	else if (ltime[c->id] < ltime[v])
            		/* If the child's lowtime is lower than the parent, update it */
            		ltime[v] = ltime[c->id];
        	}

        	else if (c->id != parent[v]){
        		if (dtime[c->id] < ltime[v])
        			ltime[v] = dtime[c->id];
        	}
        }
        if ((!parent[v] && nchildren>1) || (parent[v] && possibleWR)) {
        	/* If a vertex is the root and has more than 1 children it is a weak router
        	   Also, if satisfied the condition before, it is also a weak router       */
        	weak_routers[0]++;
    		weak_routers[weak_routers[0]] = v;
    	} 
} 

int * getWeakRouters(Network *Nw) {
	/* Finds the weak routers on the network */

    int *visited=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(visited,0,(Nw->N_rtrs+1)*sizeof(int));

    int *dtime=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(dtime,0,(Nw->N_rtrs+1)*sizeof(int));

    int *ltime=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(ltime,0,(Nw->N_rtrs+1)*sizeof(int));

    int *parent=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(parent,0,(Nw->N_rtrs+1)*sizeof(int));

    int *weak_routers=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    weak_routers[0]=0; /* Index where the number of weak routers is stored */
    
    int v, time=0;


    for(v = 1; v <= Nw->N_rtrs; v++) {
        if(!visited[v]) {
            DFS_Tarjan(v,visited,dtime,ltime,parent,weak_routers,&time,Nw);
        } 
    }

    printf("%d\n",weak_routers[0]);

    free(visited);
    free(dtime);
    free(ltime);
    free(parent);

    return weak_routers;
}

void getMaxNRouters(Network *Nw, int *weak_routers) { 
	/* Gets all the sub-networks from the mother network without the weak routers */
    int *visited=(int *)can_fail_malloc((Nw->N_rtrs+1)*sizeof(int));
    memset(visited,0,(Nw->N_rtrs+1)*sizeof(int)); 
    int v, max=0, nrouters = 1; 

    for(v = 1; v <= weak_routers[0]; v++)
    	visited[weak_routers[v]] = 1;

    for(v = 1; v <= Nw->N_rtrs; v++) {
        if(!visited[v]) {
        	
            DFS(v,visited,Nw, &nrouters, 1);
            if (nrouters > max)
            	max = nrouters;
            nrouters=1;
        } 
    }

    free(visited);
    printf("%d\n", max);

}

void free_Network(Network *Nw) {
	/* Frees the memory used for the Network, including its routers */
	Router r=Nw->routers[1];
	int i;
	for (i=1;i<=Nw->N_rtrs;r=Nw->routers[++i]) {
		Connection *t;
		while ((t=r.head)!=NULL) {
			r.head=r.head->next;
			free(t);
		}
		r.head=NULL;
	}

	free(Nw->routers);
	free(Nw);
}


int main(int argc, char **argv){

	int i,n,u, v;
	int *weak_routers;

	if (scanf("%d", &n) < 0)
		exit(-1);

	Network *Nw=(Network *)can_fail_malloc(sizeof(struct network));

	Router *r=(Router *)can_fail_malloc((n+1)*sizeof(struct router));

	Nw->N_rtrs=n;
	Nw->routers=r;

	for (i=0;i<Nw->N_rtrs;i++)
		create_router(i+1,Nw);

	if (scanf("%d", &Nw->M_cons) < 0)
		exit(-1);

	for (i=0;i<Nw->M_cons;i++) {
		if (scanf("%d %d", &u, &v) < 0 )
			exit(-1);
		router_add_conn(u,v,Nw);
		router_add_conn(v,u,Nw);
	}

	getSubNets(Nw);

	weak_routers = getWeakRouters(Nw);

	getMaxNRouters(Nw, weak_routers);

	free (weak_routers);

	free_Network(Nw);

	return 0;


}