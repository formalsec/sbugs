#include <stdlib.h>
#include <stdio.h>
#include<limits.h>

typedef struct List{
	struct Link* tail;
}* list;

typedef struct Link{
	struct Router* router;
	struct Link* prev;
}* link;

typedef struct Ligacao{
   struct Router* router_adj;
   struct Ligacao* next;
}* ligacao;

typedef struct Router{
	int id;
	int d;
	int low;
	int crit;
	int in_tjList;
	int parent;
	int desc;
	int sub_rede;
	struct Ligacao* adj;
}* router;

typedef struct  Rede{
	struct Router** routers;
	int crit_routers;
	int num_routers;
	int sub_redes;
	int n_routers_max_sub_rede;
	int visited;
	struct List* tjList;
}* rede;

void newLigacao(rede redeC, int r1, int r2);
router newRouter(int id);
rede newRede(int n_routers);
list newList();
link newLink(router r);
void push(list lst, router r);
router pop(list lst);
int min(int n, int m);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void mod_tarjan(rede redeC);
void mod_tarjan_visit(rede redeC, int r_index);

void newLigacao(rede redeC, int r1, int r2){
	ligacao lig_r1 = (ligacao) malloc(sizeof(struct Ligacao));
	ligacao lig_r2 = (ligacao) malloc(sizeof(struct Ligacao));

	lig_r1->router_adj = redeC->routers[r2];
	lig_r1->next = redeC->routers[r1]->adj;
	redeC->routers[r1]->adj = lig_r1;

	lig_r2->router_adj = redeC->routers[r1];
	lig_r2->next = redeC->routers[r2]->adj;
	redeC->routers[r2]->adj = lig_r2;
}

router newRouter(int id){
	router new = (router) malloc(sizeof(struct Router));
	new->id = id;
	new->d = INT_MAX;
	new->low = INT_MAX;
	new->crit = 0;
	new->in_tjList = 0;
	new->parent = -1;
	new->desc = 0;
	new->sub_rede = -1;
	new->adj = NULL;
	return new;
}

rede newRede(int n_routers){
	rede new = (rede) malloc(sizeof(struct Rede));
	new->routers = (router*) malloc(sizeof(router) * n_routers);
	new->crit_routers = 0;
	new->num_routers = n_routers;
	new->sub_redes = 0;
	new->n_routers_max_sub_rede = 0;
	new->visited = 0;
	new->tjList = newList();
	return new;
}

list newList(){
	list new = (list) malloc(sizeof(struct List));
	new->tail = NULL;
	return new;
}

link newLink(router r){
	link new = (link) malloc(sizeof(struct Link));
	new->router = r;
	new->prev = NULL;
	return new;
}

void push(list lst, router r){
	link lnk = newLink(r);
	lnk->prev = lst->tail;
	lst->tail = lnk;
}

router pop(list lst){
	link aux = lst->tail;
	router aux_r = aux->router;
	lst->tail = aux->prev;
	free(aux);
	return aux_r;
}

int min(int n, int m){
	if (n < m)
		return n;
	else
		return m;
}

void mergeSort(int arr[], int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mod_tarjan(rede redeC){
	int i;
	for(i=0; i < redeC->num_routers; i++){
		if(redeC->routers[i]->d == INT_MAX){
			redeC->routers[i]->sub_rede = redeC->sub_redes;
			redeC->sub_redes++;
			mod_tarjan_visit(redeC, i);
		}
	}
}

void mod_tarjan_visit(rede redeC, int r_index){
	router r = redeC->routers[r_index], stack_r;
	ligacao adj = r->adj;
	r->d = redeC->visited;
	r->low = redeC->visited;
	redeC->visited++;
	r->in_tjList = 1;
	push(redeC->tjList, r);

	while(adj != NULL){
		if(adj->router_adj->d == INT_MAX){
			adj->router_adj->parent = r->id;
			adj->router_adj->sub_rede = r->sub_rede;
			r->desc++;
			mod_tarjan_visit(redeC, adj->router_adj->id - 1);
			r->low = min(r->low, adj->router_adj->low);
			if((adj->router_adj->low >= r->d && r->parent != -1) || (r->parent == -1 && r->desc > 1)){
				if(r->crit == 0)
					redeC->crit_routers++;
				r->crit = 1;
			}
		}
		else if(adj->router_adj->id != r->parent){
			r->low = min(r->low, adj->router_adj->d);
		}
		adj = adj->next;
	}
	if(r->d == r->low){
		int n_routers_subrede = 0;
		do{
			stack_r = pop(redeC->tjList);
			stack_r->in_tjList = 0;
			if(stack_r->crit == 0)
				n_routers_subrede++;
		}while(r->id != stack_r->id);
		if(n_routers_subrede > redeC->n_routers_max_sub_rede)
			redeC->n_routers_max_sub_rede = n_routers_subrede;
	}
}

int main(int argc,char *argv[]){
	int n_routers, n_lig, i, r1, r2, sub_r_index;
	int* sub_redes_rep;
	ligacao aux_lig;
	rede RedeCaracol;

	scanf("%d", &n_routers);
 	
 	RedeCaracol = newRede(n_routers);

	for(i=0; i<n_routers; i++){
		RedeCaracol->routers[i] = newRouter(i+1);
	}

	scanf("%d", &n_lig);
	for(i=0; i<n_lig; i++){
		scanf("%d %d", &r1, &r2);
		newLigacao(RedeCaracol, r1-1, r2-1);
	}

	mod_tarjan(RedeCaracol);

	sub_redes_rep = (int*) malloc(sizeof(int) * RedeCaracol->sub_redes);

	for(i=0; i < RedeCaracol->sub_redes; i++){
		sub_redes_rep[i] = -1;
	}

	for(i=0; i<n_routers; i++){
		sub_r_index = RedeCaracol->routers[i]->sub_rede;
		if(sub_redes_rep[sub_r_index] < RedeCaracol->routers[i]->id)
			sub_redes_rep[sub_r_index] = RedeCaracol->routers[i]->id;
	}

	mergeSort(sub_redes_rep, 0, RedeCaracol->sub_redes - 1);

	printf("%d\n", RedeCaracol->sub_redes);
	for(i=0; i < RedeCaracol->sub_redes - 1; i++){
		printf("%d ",sub_redes_rep[i]);
	}
	printf("%d\n", sub_redes_rep[i]);
	printf("%d\n", RedeCaracol->crit_routers);
	printf("%d\n", RedeCaracol->n_routers_max_sub_rede);

	free(sub_redes_rep);
	free(RedeCaracol->tjList);
	for(i=0; i < n_routers; i++){
		while(RedeCaracol->routers[i]->adj != NULL){
			aux_lig = RedeCaracol->routers[i]->adj;
			RedeCaracol->routers[i]->adj = aux_lig->next;
			free(aux_lig);
		}
		free(RedeCaracol->routers[i]);
	}
	free(RedeCaracol->routers);
	free(RedeCaracol);
	return 0;
}