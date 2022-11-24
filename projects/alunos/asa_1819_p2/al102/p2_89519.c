#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>                                                              
#include <string.h>                                                                                 
#include <stdlib.h>

struct transporte{
	int o, d, c, fluxo;
	struct transporte *prox;
};
typedef struct transporte *Transportes;

struct vertice{
	int altura;
	int fluxoExcesso;
	int cap;
	Transportes transp;
};
typedef struct vertice *Lista;

int N_vertices;
int nEstacoesAum=0;
int nLigacoesAum=0;

Lista criaLista(){
	Lista l = can_fail_malloc (N_vertices*sizeof(struct vertice));
	int vertice;
	for (vertice=0; vertice<N_vertices; vertice++){
		l[vertice].altura = 0;
		l[vertice].fluxoExcesso = 0;
		l[vertice].cap = -1;
		l[vertice].transp = NULL;
	}
	l[0].altura = N_vertices-2;
	return l;
}

Transportes criaTransporte(int o, int d, int c, int fluxo, Transportes prox){
	Transportes t = can_fail_malloc (sizeof(struct transporte));
	t->o = o;
	t->d = d;
	t->c = c;
	t->fluxo = fluxo;
	t->prox = prox;
	return t;
}

void readInput(Lista l, int f, int e, int t){

	int i, o, d, c, soma=0;
	
    for (i=2; i<f+2; i++){
    	scanf("%d", &c);
    	l[i].cap = c;
    	l[0].transp = criaTransporte(0, i, c, c, l[0].transp);
    	l[i].transp = criaTransporte(i, 0, c, -c, l[i].transp);
    	l[i].fluxoExcesso = c;
    	l[0].fluxoExcesso -= c;
    	soma += c;
    }
    l[0].cap = soma;
    for (i=f+2; i<f+e+2; i++){
    	scanf("%d", &c);
    	l[i].cap = c;
    	l[i].fluxoExcesso = 0;
    }
    for (i=0; i<t; i++){
    	scanf("%d", &o);
		getchar();
    	scanf("%d", &d);
		getchar();
    	scanf("%d", &c);
    	l[o].transp = criaTransporte(o, d, c, 0, l[o].transp);
    	l[d].transp = criaTransporte(d, o, c, 0, l[d].transp);
    }
}

int minimo(int a, int b, int c){
	if (a < c || c < 0){
		return a < b ? a : b;
	} else {
		return c < b ? c : b;
	}
}

void Relabel(Lista l, int vertice){
	Transportes t;
	int hMin = N_vertices+1;
	for (t=l[vertice].transp; t!=NULL; t=t->prox){
		if (l[t->d].altura >= l[vertice].altura && l[t->d].altura <= hMin){
			hMin = l[t->d].altura;
		}
	}
	l[vertice].altura = 1 + hMin;
}

void Push(Lista l, int vertice1, int vertice2){
	int aumento=0;
	Transportes transp1 = l[vertice1].transp;
	Transportes transp2 = l[vertice2].transp;
	Transportes aux;
	for (aux = transp1; aux!=NULL; aux=aux->prox){
		if (aux->d == vertice2){
			aumento = minimo(l[vertice1].fluxoExcesso, aux->c - aux->fluxo, l[aux->d].cap - l[aux->d].fluxoExcesso);
			aux->fluxo += aumento;
		}
	}
	for (aux = transp2; aux!=NULL; aux=aux->prox){
		if (aux->d == vertice1){
			aux->fluxo -= aumento;
		}
	}
	l[vertice1].fluxoExcesso -= aumento;
	l[vertice2].fluxoExcesso += aumento;
}

void Discharge(Lista l, int vertice){
	Transportes head = l[vertice].transp;;
	Transportes transp = l[vertice].transp;
	while (l[vertice].fluxoExcesso>0){
		if (transp == NULL){
			Relabel(l, vertice);
			transp = head;
		} else if ((transp->c - transp->fluxo>0) && (l[vertice].altura == l[transp->d].altura + 1) 
					&& ((l[transp->d].cap - l[transp->d].fluxoExcesso > 0) || l[transp->d].cap == -1)){
			Push(l, vertice, transp->d);
		} else {
			transp = transp->prox;
		}
	}
}

void RelabelToFront(Lista l){
	int i=2, j, k, alturaAnt, aux;
	int l_aux[N_vertices-1];
	for (j=2; j<N_vertices; j++){
		l_aux[j-2]=j;
	}
	l_aux[j-2]=-1;
	while (l_aux[i-2]!=-1){
		alturaAnt = l[i].altura;
		Discharge(l, i);
		if (l[i].altura > alturaAnt){
			aux = i;
			for (k=i; k>2; k--){
				l_aux[k-2]=l_aux[k-3];
			}
			l_aux[k-2]=aux;
			i=2;
		} else {
			i++;
		}
	}
}

void buscaProfundidade(Lista l, int visitados[], int vertice, int f, int estacoesAumentar[], int ligacoesAumentar[][2]){
	Transportes transp;
	visitados[vertice] = 1;
	for (transp=l[vertice].transp; transp!=NULL; transp=transp->prox){
		if ((transp->fluxo <= 0) && (visitados[transp->d] == 0)){
			if (transp->d >= f+2){
				if (transp->c == -transp->fluxo){
					ligacoesAumentar[nLigacoesAum][0]=transp->d;
					ligacoesAumentar[nLigacoesAum][1]=vertice;
					nLigacoesAum++;
				} else if (l[transp->d].cap == -transp->fluxo){
					estacoesAumentar[nEstacoesAum]=transp->d;
					nEstacoesAum++;
				} else {
					buscaProfundidade(l, visitados, transp->d, f, estacoesAumentar, ligacoesAumentar);
				}
			} else {
				if (transp->c == -transp->fluxo){
					ligacoesAumentar[nLigacoesAum][0]=transp->d;
					ligacoesAumentar[nLigacoesAum][1]=vertice;
					nLigacoesAum++;
				}
			}
		}
	}
}

void insertionSort(int lista[], int n){
	int i, chave, j;
	for (i=1; i<n; i++){
		chave = lista[i];
		j = i-1;
		while (j >= 0 && lista[j] > chave){
			lista[j+1] = lista[j];
			j = j-1;
		}
		lista[j+1] = chave;
	}
}

void insertionSort2(int lista[][2], int n){
	int i, chave1, chave2, j;
	for (i=1; i<n; i++){
		chave1 = lista[i][0];
		chave2 = lista[i][1];
		j = i-1;
		while (j >= 0 && (lista[j][0] > chave1 || (lista[j][0] == chave1 && lista[j][1] > chave2))){
			lista[j+1][0] = lista[j][0];
			lista[j+1][1] = lista[j][1];
			j = j-1;
		}
		lista[j+1][0] = chave1;
		lista[j+1][1] = chave2;
	}
}

void printOutput(Lista l, int f, int e, int t){
	int i, j, temEstacoes = 0;
	RelabelToFront(l);
	printf("%d\n", -l[0].fluxoExcesso);

	int visitados[N_vertices];
	for (i=0; i<N_vertices; i++){
		visitados[i]=0;
	}

	int estacoesAumentar[e];
	int ligacoesAumentar[t][2];
	for (i=0; i<e; i++){
		estacoesAumentar[i]=0;
	}
	for (i=0; i<t; i++){
		for (j=0; j<2; j++){
			ligacoesAumentar[i][j]=0;
		}
	}
	buscaProfundidade(l, visitados, 1, f, estacoesAumentar, ligacoesAumentar);
	insertionSort(estacoesAumentar, nEstacoesAum);
	insertionSort2(ligacoesAumentar, nLigacoesAum);
	for (i=0; i<nEstacoesAum; i++){
		printf("%d\n", estacoesAumentar[i]);
		temEstacoes = 1;
	}
	if (!temEstacoes){
		printf("\n");
	}
	i=0;
	for (i=0; i<nLigacoesAum; i++){
		printf("%d %d\n", ligacoesAumentar[i][0], ligacoesAumentar[i][1]);
	}
}

int main(){

	int f, e, t;

	scanf("%d", &f);
	getchar();
	scanf("%d", &e);
	getchar();
	scanf("%d", &t);
	N_vertices = f + e + 2;

	Lista l = criaLista();

	readInput(l, f, e, t);

	printOutput(l, f, e, t);

	return 0;
}