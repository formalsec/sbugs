#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>







typedef struct vertices {
    int index;
    int lowlink;
    int in_stack;
    int deg;
	int is_cut;
	int forget;
    int* adj;
} grafo;







typedef struct stack_s {
    int top;
    int* items;
} stacker;

stacker stack;





void stack_push(int v, int nV) {
    stack.top++;
    if (stack.top < nV){
		stack.items[stack.top] = v;
	}
    else {
		exit(1);
    }
}

int stack_pop() {
    return stack.top < 0 ? -1 : stack.items[stack.top--];
}


int curr_index = 0;
int scc_ctr = 0;
int max_routers = 0;

int* scc_ids;


int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}



void scc(int v, grafo* vertices, int nV, int p) {
    int i, c, n;
	if (vertices[v].forget != 1){
		vertices[v].index = curr_index;
		vertices[v].lowlink = curr_index;
		++curr_index;
		int children = 0;

		stack_push(v, nV);
		vertices[v].in_stack = 1;
		c = vertices[v].deg;

		
		for (i = 0; i < c; ++i){
			n = vertices[v].adj[i] - 1;
			if(vertices[n].forget != 1){
				if (vertices[n].index == -1) {
					scc(n, vertices, nV, vertices[v].index);
					vertices[v].lowlink = min(vertices[v].lowlink, vertices[n].lowlink);
					if (vertices[n].lowlink >= vertices[v].index && p!=-1){
						vertices[v].is_cut = 1;
					}
					++children;
				} 
				else if (vertices[n].in_stack == 1) {
					vertices[v].lowlink = min(vertices[v].lowlink, vertices[n].index);
				}
				else if (vertices[n].index == vertices[p].index){
					continue;
				}
			}
			
		}
		if (p == -1 && children > 1){
			vertices[v].is_cut = 1;
		}
		
		if (vertices[v].index == vertices[v].lowlink) {
			int scc_id = -1;
			int counter = 0;
			while ((n = stack_pop()) != -1) {
				vertices[n].in_stack = 0;
				counter++;
				if (counter > max_routers){
					max_routers = counter;
				}
				scc_id = scc_id > n ? scc_id : n;
				if (n == v) {
					scc_ids[scc_ctr] = scc_id +1;
					scc_ctr = scc_ctr + 1;
					break;
				}
			}
		}
	}
	else{
		return;
	}
	
}

void sort_array(int* array, int numbElements){
	int i, j, a;

	for (i = 0; i < numbElements; ++i){
		for (j = i + 1; j < numbElements; ++j){
 
			if (array[i] > array[j]){

				a =  array[i];
				array[i] = array[j];
				array[j] = a; 
			}
		}
    }
}
	


int main(){
	int nV, nE, O, D, i;
	
	
	
	
	if(scanf("%d", &nV));
	else{
		printf("erro");
	}
	grafo* vertices;
	
	if(scanf("%d", &nE));
	else{
		printf("erro");
	}
	
	vertices = (grafo*) can_fail_malloc (sizeof(grafo)*nV);
	
	for (i = 0; i < nV; i++){
		vertices[i].index = -1;
		vertices[i].lowlink = -1;
		vertices[i].in_stack = 0;
		vertices[i].deg = 0;
		vertices[i].adj =(int*) can_fail_malloc (sizeof(int)*nE);
		vertices[i].is_cut = -1;
		vertices[i].forget = -1;
	}
		
	for (i = 0; i < nE; i++){
		if(scanf("%d %d", &O, &D));
		else{
			printf("erro");
		}
		
		vertices[O-1].adj[vertices[O-1].deg] = D;
		vertices[D-1].adj[vertices[D-1].deg] = O;
		vertices[O-1].deg++;
		vertices[D-1].deg++;
	}
	
	scc_ids = (int*) can_fail_malloc (sizeof(int)*nV);
	
	
	stack.top = -1;
	stack.items = (int*) can_fail_malloc (sizeof(int)*nV);
	
	
    for (i = 0; i < nV; ++i){
	    if (vertices[i].index == -1){
	        scc(i, vertices, nV, -1);
		}
	}
	printf("%d\n", scc_ctr);
	
	sort_array(scc_ids, scc_ctr);
	for (i=0; i<scc_ctr; i++){
		if (i == scc_ctr -1){
			printf("%d", scc_ids[i]);
		}
		else{
			printf("%d ", scc_ids[i]);
		}
	}
	printf("\n");
	
	int cut_ctr = 0;
	for (i=0; i< nV; i++){
		if( vertices[i].is_cut == 1){
			vertices[i].forget = 1;
			cut_ctr++;
		}
	}
	printf("%d\n", cut_ctr);

	max_routers = 0;
	for (i=0; i<nV; i++){
		if (vertices[i].forget != 1){
			vertices[i].index = -1;
			vertices[i].lowlink = -1;
			vertices[i].in_stack = 0;
			vertices[i].is_cut = -1;
		}
	}
	
	scc_ctr = 0;
	 for (i = 0; i < nV; ++i){
	    if (vertices[i].index == -1){
	        scc(i, vertices, nV, -1);
		}
	}


	printf("%d\n", max_routers);

/*	int v_counter = 1;
	int aux_counter = 1;
	for (i = 0; i < nV +1; i++){
		if (vertices[i].lowlink == vertices[i+1].lowlink){
			++aux_counter;
		}
		else{
			if (v_counter <= aux_counter){
				v_counter = aux_counter;
			}
		}
	}
	printf("%d\n", v_counter);
*/
	
	return 0;
}