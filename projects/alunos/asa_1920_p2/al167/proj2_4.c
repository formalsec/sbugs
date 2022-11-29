#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Link{
	struct Arco* arc;
	struct Link* next;
}* link;

typedef struct Arco{
	struct Cruzamento* dest;
	short int fluxo;
	struct Arco* oposto;
}* arco;

typedef struct Cruzamento {
	int av;
	int rua;
	short int cidadao;
	short int superm;
	short int ocupado;
	short int temCaminho;
	short int visited;
	struct Link* adj;
}* cruz;

arco newArco(cruz c);
void addArco(cruz c, arco a);
void fordFulkerson(cruz source, cruz target, cruz** cruzamentos, int m, int n);
int dfsVisit(arco a);

arco newArco(cruz c){
	arco new = (arco)can_fail_malloc(sizeof(struct Arco));
	new->dest = c;
	new->fluxo = 0;
	return new;
}

void addArco(cruz orig, arco a){
	link new = (link)can_fail_malloc(sizeof(struct Link));
	new->arc = a;
	new->next = orig->adj;
	orig->adj = new;
}

void fordFulkerson(cruz source, cruz target, cruz** cruzamentos, int m, int n){
	link link_cid = source->adj;
	int i, j, fluxo = 0;
	short int hasPath;
	while(link_cid != NULL){ /*O(v(v + v+e)) , e ~= 4v , logo O(6v^2) = O(v^2)*/
		/*printf("* * * FF while * * *\n");*/
		hasPath = 0;
		source->visited = 0;
		target->visited = 0;
		for(i = 0; i < m; i++){
			for (j = 0; j < n; j++){
				cruzamentos[i][j]->visited = 0;
			}
		}
		hasPath = dfsVisit(link_cid->arc);
		if(hasPath == 1){
			link_cid->arc->dest->temCaminho = 1;
		}
		link_cid = link_cid->next;
	}
	link_cid = source->adj;
	while(link_cid != NULL){
		fluxo += link_cid->arc->dest->temCaminho;
		link_cid = link_cid->next;
	}
	printf("%d\n", fluxo);
}

int dfsVisit(arco a){
	/*printf("DFS (dest coord): %d %d\n", a->dest->av, a->dest->rua);*/
	cruz c = a->dest;
	cruz viz;
	link adj = c->adj;
	short int suc;
	c->visited = 1;
	if(c->av == -2){
		/*printf("reached TARGET\n");*/
		return 1;
	}
	while (adj != NULL){
		viz = adj->arc->dest;
		/*printf("DFS while\n");*/
		if(viz->visited==0 && (viz->cidadao==0 || adj->arc->oposto->fluxo==1) && adj->arc->fluxo==0 /*&& (viz->ocupado==0 || viz->superm==1 || adj->arc->oposto->fluxo==1)*/){
			/*if(!(c->ocupado == 0 && 1)){}*/
			/*if(!(adj->arc->oposto->fluxo==0 && adj->arc->dest->cidadao==1)){}*/
			/*if((adj->arc->fluxo==0 && adj->arc->dest->cidadao==0 && c->ocupado==0) || (adj->arc->oposto!=NULL && adj->arc->oposto->fluxo==1)){*/
				
			suc = dfsVisit(adj->arc);
			if(suc == 1){
				c->ocupado = 1;
				adj->arc->fluxo = 1;
				if (adj->arc->oposto!=NULL && adj->arc->oposto->fluxo == 1){
					adj->arc->oposto->fluxo = 0;
					adj->arc->fluxo = 0;
				}
				return 1;
			}
			
		}
		adj = adj->next;
	}
	return 0;
}

int main(int argc, char* argv[]){
	int i, j, m, n, s, c, aven, rua;
	cruz** cruzamentos;
	cruz source, target;
	arco arcN, arcS, arcE, arcO;
	link lfrees, laux;

	scanf("%d %d", &m, &n);
	cruzamentos = (cruz**)can_fail_malloc(sizeof(cruz*)*m);
	for (i=0; i<m; i++){
		cruzamentos[i] = (cruz*)can_fail_malloc(sizeof(cruz)*n);
		for (j=0; j<n ; j++){
			cruzamentos[i][j] = (cruz)can_fail_malloc(sizeof(struct Cruzamento));
			cruzamentos[i][j]->cidadao = 0;
			cruzamentos[i][j]->superm = 0;
			cruzamentos[i][j]->av = i;
			cruzamentos[i][j]->rua = j;
			cruzamentos[i][j]->ocupado = 0;
			cruzamentos[i][j]->temCaminho = 0;
		}
	}

	source = (cruz)can_fail_malloc(sizeof(struct Cruzamento));
	source->av = -1;
	source->rua = -1;
	target = (cruz)can_fail_malloc(sizeof(struct Cruzamento));
	target->av = -2;
	target->rua = -2;

	scanf("%d %d", &s, &c);

	for(i=0; i<s ; i++){
		scanf("%d %d", &aven, &rua);
		cruzamentos[aven-1][rua-1]->superm = 1;
		arcO = newArco(target);
		arcE = newArco(cruzamentos[aven-1][rua-1]);
		addArco(cruzamentos[aven-1][rua-1], arcO);
		addArco(target, arcE);
		arcE->oposto = arcO;
		arcO->oposto = arcE;
	}
	for(i=0; i<c ; i++){
		scanf("%d %d", &aven, &rua);
		cruzamentos[aven-1][rua-1]->cidadao = 1;
		arcO = newArco(cruzamentos[aven-1][rua-1]);
		/*arcE = newArco(source);*/
		addArco(source, arcO);
		/*addArco(cruzamentos[aven-1][rua-1], arcE);*/
	}
	for (i=0; i<m; i++){
		for (j=0; j<n ; j++){
			arcN = NULL;
			arcS = NULL;
			arcE = NULL;
			arcO = NULL;
			if(i < m - 1){
				/*if (cruzamentos[i][j]->superm == 0 && cruzamentos[i+1][j]->cidadao == 0){
				if (cruzamentos[i][j]->superm == 0){*/
					arcE = newArco(cruzamentos[i+1][j]);
					addArco(cruzamentos[i][j], arcE);
				/*}
				if (cruzamentos[i][j]->cidadao == 0 && cruzamentos[i+1][j]->superm == 0){
				if (cruzamentos[i+1][j]->superm == 0){*/
					arcO = newArco(cruzamentos[i][j]);
					addArco(cruzamentos[i+1][j], arcO);
				/*}*/
			}

			if(j < n - 1){
				/*if (cruzamentos[i][j]->superm == 0 && cruzamentos[i][j+1]->cidadao == 0){
				if (cruzamentos[i][j]->superm == 0){*/
					arcS = newArco(cruzamentos[i][j+1]);
					addArco(cruzamentos[i][j], arcS);
				/*}
				if (cruzamentos[i][j]->cidadao == 0 && cruzamentos[i][j+1]->superm == 0){
				if (cruzamentos[i][j+1]->superm == 0){*/
					arcN = newArco(cruzamentos[i][j]);
					addArco(cruzamentos[i][j+1], arcN);
				/*}*/
			}
			if(arcN!=NULL){arcN->oposto = arcS;}
			if(arcS!=NULL){arcS->oposto = arcN;}
			if(arcE!=NULL){arcE->oposto = arcO;}
			if(arcO!=NULL){arcO->oposto = arcE;}
		}
	}
	/*for (i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("-> av:%d - rua:%d\n",cruzamentos[i][j]->av,cruzamentos[i][j]->rua);
			laux = cruzamentos[i][j]->adj;
			while(laux!=NULL){
				printf(" %d %d\n",laux->arc->dest->av,laux->arc->dest->rua);
				laux=laux->next;
			}
		}
	}*/
	fordFulkerson(source, target, cruzamentos, m, n);

	for (i=0; i<m; i++){
		for (j=0; j<n ; j++){
			lfrees = cruzamentos[i][j]->adj;
			while(lfrees != NULL){
				laux = lfrees->next;
				free(lfrees->arc);
				free(lfrees);
				lfrees = laux;
			}
			free(cruzamentos[i][j]);
		}
		free(cruzamentos[i]);
	}
	free(cruzamentos);

	lfrees = source->adj;
	while(lfrees != NULL){
		laux = lfrees->next;
		free(lfrees->arc);
		free(lfrees);
		lfrees = laux;
	}
	free(source);

	lfrees = target->adj;
	while(lfrees != NULL){
		laux = lfrees->next;
		free(lfrees->arc);
		free(lfrees);
		lfrees = laux;
	}
	free(target);

	return 0;
}