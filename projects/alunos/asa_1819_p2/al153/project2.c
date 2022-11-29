#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{/*Estrutura que define uma ligação*/
	int o;/*Origem*/
	int d;/*Destino*/
	int c;/*Capacidade*/
	int f;/*Fluxo*/
	int c2;/*Capacidade de Regresso = 0*/
	int f2;/*Fluxo de Regresso = -f*/
	int r;/*Sinal de remoção*/
}liga;

typedef struct{/*Estrutura que define um vértice*/
	int e;/*Excesso de fluxo*/
	int h;/*Altura do vertice*/
	int n;/*Número do vertice*/
	int v;/*Primeiro vizinho do vertice*/
	int *l;/*ligações do vértice*/
	int col;/*Cor de descoberta - (Usada na deteção dos arcos e estações que precisam de ser aumentados) 0-branco 1-cizento 2-preto*/
}vertice;

vertice *V;

liga *T;

int f, e, t, z, y, x, o, d, c, n, w, kl;

char* X;

void Remover(int n){/*Neutralização da remoção de ligações pertencentes a estações que foram atingidas por DFS*/
	for(z=0;z<t+f+e;z++){/*Complexidade: O(t+f+e)*/
		if(T[z].o==n||T[z].d==n)
			T[z].r=0;
	}
}


void Visit(int n,int m[]){/*Algoritmo de visita DFS*/
	Remover(n);/*Neutralização da remoção de ligações pertencentes ao vértice em analise*/
	V[n].col=1;
	int s;
	for(s=0;s<m[n];s++){/*Complexidade: O(m[n])*/
		if(T[V[n].l[s]].o==n){/*Se o vértice é a origem da ligação*/
			if(T[V[n].l[s]].c-T[V[n].l[s]].f>0 && V[T[V[n].l[s]].d].col==0){
				Visit(T[V[n].l[s]].d,m);
			}
			else{
				if(T[V[n].l[s]].c-T[V[n].l[s]].f==0 && V[T[V[n].l[s]].d].col==0){
					T[V[n].l[s]].r=1;
					kl+=1;
				}
			}
		}
		if(T[V[n].l[s]].d==n){/*Se o vértice é o destino da ligação*/
			if(T[V[n].l[s]].c2-T[V[n].l[s]].f2>0 && V[T[V[n].l[s]].o].col==0)
				Visit(T[V[n].l[s]].o,m);
			else{
				if(T[V[n].l[s]].c2-T[V[n].l[s]].f2==0 && V[T[V[n].l[s]].o].col==0){
					T[V[n].l[s]].r=1;
					kl+=1;
				}
			}
		}
	}
	V[n].col=2;
}

int main(){/*Cada estação representa 2 vertices ligados por uma ligação com a capacidade da estação (o 2º vertice tem o numero da estação mais o numero de estações)*/
	scanf("%d %d %d",&f,&e,&t);
	n=f+(2*e)+2;/*Número de estruturas presentes na rede (origem,hipermercado,fornecedores e estações(2 vertices por estação)*/
	V=(vertice*)can_fail_malloc(sizeof(vertice)*(f+(2*e)+2));/*Vetor com o registo dos vértices da rede (O elemento 0 corresponde a fonte)*/
	T=(liga*)can_fail_malloc(sizeof(liga)*(t+f+e));/*Vetor com registo das ligações*//*Uma ligação extra por cada fornecedor e por cada extração*/
	for(z=0;z<f+(2*e)+2;z++){/*Inicialização*//*Complexidade: O(f+(2*e)+2)*/
		V[z].n=z;
		V[z].e=0;
		V[z].h=0;
		V[z].col=0;
	}
	
	int m[f+(2*e)+2];/*Mantem contagem de quantas ligações pertencem a cada vértice*/
	int k[f+(2*e)+2];/*Criação de lista de vertices para o relabel to front*/
	for(z=0;z<f+(2*e)+2;z++){/*Complexidade: O(f+(2*e)+2)*/
		m[z]=0;
		k[z]=z;
	}
	for(z=2;z<=f+1;z++){/*Recolha dos dados dos fornecedores e inicialização do pré fluxo*//*Complexidade: O(f)*/
		scanf("%d ",&x);
		V[z].n=z;
		V[z].e=x;
		V[z].h=0;
		V[0].e-=x;
		m[0]+=1;
		m[z]+=1;
		T[t+z-2].o=0;
		T[t+z-2].d=z;
		T[t+z-2].c=x;
		T[t+z-2].f=x;
		T[t+z-2].c2=0;
		T[t+z-2].f2=-x;

	}
	scanf("/n");
	for(z=f+2;z<=f+e+1;z++){/*Recolha dos dados das estações*//*Complexidade: O(e)*/
		scanf("%d ",&x);
		V[z].n=z;
		V[z].e=0;
		V[z].h=0;
		m[z]=1;
		V[z+e].n=z+e;
		V[z+e].e=0;
		V[z+e].h=0;
		m[z+e]=1;
		T[t+z-2].o=z;
		T[t+z-2].d=z+e;
		T[t+z-2].c=x;
		T[t+z-2].f=0;
		T[t+z-2].c2=x;
		T[t+z-2].f2=0;
	}
	scanf("/n");
	for(z=0;z<t;z++){/*Registo das ligações*//*Complexidade: O(t)*/
		scanf("%d %d %d/n",&o,&d,&c);
		if(o>f+1){/*Caso a origem da ligação seja uma estação*/
			m[o+e]+=1;
			T[z].o=o+e;
		}
		else{
			m[o]+=1;
			T[z].o=o;
		}
		m[d]+=1;
		T[z].d=d;
		T[z].c=c;
		T[z].f=0;
		T[z].c2=0;
		T[z].f2=0;
	}
	for(z=0;z<f+(2*e)+2;z++){/*Alocação da memória para as ligações de cada vértice*//*Complexidade: O(f+(2*e)+2)*/
		V[z].v=0;/*Atribuição da posição do primeiro vertice de envio a cada vertice*/
		if(m[z]!=0){
			V[z].l=(int*)can_fail_malloc(sizeof(int)*m[z]);
			m[z]=0;
		}
	}

	for(z=0;z<t+f+e;z++){/*Aos vértices de número da origem da ligação z é a adicionado o número da ligação z*//*Complexidade: O(t+f+e)*/
		T[z].r=0;
		V[T[z].o].l[m[T[z].o]]=z;
		m[T[z].o]+=1;/*Avanço para a posição seguinte na atribuição das ligações do vértice*/
	}
	for(z=0;z<t+f+e;z++){/*Aos vértices de número  de destino da ligação z é a adicionado o número da ligação z*//*Complexidade: O(t+f+e)*/
		V[T[z].d].l[m[T[z].d]]=z;
		m[T[z].d]+=1;/*Avanço para a posição seguinte na atribuição das ligações do vértice*/
	}
	V[0].h=f+2*e+2;/*Inicialiar altura do vertice fonte*/
	w=2;/*u=head[L]*/
	while(w<f+2*e+2){/*Aplicação do Relabel to Front*//*while u!=NIL*/
		int oldh=V[k[w]].h;
		while(V[k[w]].e>0){/*Descarga*/
			int q=V[k[w]].v;/*v=current[u]*/
			if(m[k[w]]==q){/*Se todas as ligações do vertice ja foram analisadas*//*if(v==NIL)*/
				o=1000000;
				if(k[w]==T[V[k[w]].l[0]].o && T[V[k[w]].l[0]].c-T[V[k[w]].l[0]].f>0){
					o=V[T[V[k[w]].l[0]].d].h;/*Procura o vertice de destino com a menor altura*//*Relabel*/
				}
				if(k[w]==T[V[k[w]].l[0]].d && T[V[k[w]].l[0]].c2-T[V[k[w]].l[0]].f2>0){
					o=V[T[V[k[w]].l[0]].o].h;/*Procura o vertice de origem com a menor altura*//*Relabel*/
				}
				for(z=0;z<q;z++){/*Complexidade: O(q)*/
					if(k[w]==T[V[k[w]].l[z]].o && T[V[k[w]].l[z]].c-T[V[k[w]].l[z]].f>0){
						if(o>V[T[V[k[w]].l[z]].d].h)
							o=V[T[V[k[w]].l[z]].d].h;
					}
					if(k[w]==T[V[k[w]].l[z]].d && T[V[k[w]].l[z]].c2-T[V[k[w]].l[z]].f2>0){
						if(o>V[T[V[k[w]].l[z]].o].h)
							o=V[T[V[k[w]].l[z]].o].h;
					}
				}
				V[k[w]].h=1+o;/*Relabel*/
				V[k[w]].v=0;/*Regressa a primeira ligação*/
			}
			else{
				if(k[w]==T[V[k[w]].l[q]].o){
					if((T[V[k[w]].l[q]].c-T[V[k[w]].l[q]].f>0)&&(V[k[w]].h==V[T[V[k[w]].l[q]].d].h+1)){
						d=V[k[w]].e;/*Push*/
						if(d>T[V[k[w]].l[q]].c-T[V[k[w]].l[q]].f)
							d=T[V[k[w]].l[q]].c-T[V[k[w]].l[q]].f;
						T[V[k[w]].l[q]].f+=d;
						T[V[k[w]].l[q]].f2=-T[V[k[w]].l[q]].f;
						V[k[w]].e-=d;/*O fluxo e retirado do vertice de origem e e adiconado ao vertice de destino*/
						V[T[V[k[w]].l[q]].d].e+=d;
					}					
					else{
						V[k[w]].v+=1;/*Avança para a proxima ligação*/
					}
				}
				if(k[w]==T[V[k[w]].l[q]].d){
					if((T[V[k[w]].l[q]].c2-T[V[k[w]].l[q]].f2>0)&&(V[k[w]].h==V[T[V[k[w]].l[q]].o].h+1)){
						d=V[k[w]].e;/*Push*/
						if(d>T[V[k[w]].l[q]].c2-T[V[k[w]].l[q]].f2)
							d=T[V[k[w]].l[q]].c2-T[V[k[w]].l[q]].f2;
						T[V[k[w]].l[q]].f2+=d;
						T[V[k[w]].l[q]].f=-T[V[k[w]].l[q]].f2;
						V[k[w]].e-=d;/*O fluxo é retirado do vertice de origem e e adiconado ao vertice de destino*/
						V[T[V[k[w]].l[q]].o].e+=d;
					}					
					else{
						V[k[w]].v+=1;/*Avança para a proxima ligação*/
					}
				}
			}
		}
		if(V[k[w]].h>oldh){/*Se a altura do vertice sofreu alterações então todos os vertices ja vistos vão ter de ser vistos novamente*/
			int a=k[w];
			for(z=w;z>1;z--){/*Complexidade: O(w-2)*/
				k[z]=k[z-1];
			}
			k[2]=a;
			w=2;
		}
		w+=1;

	}
	printf("%d\n",V[1].e);
	/*Verificações das estações e ligações para aumentar*/
	kl=0;
	for(z=0;z<t+f+e;z++){/*Criar rede transposta*//*Complexidade: O(t+f+e)*/
		int d=T[z].f;
		T[z].f=T[z].f2;
		T[z].f2=d;
		d=T[z].c;
		T[z].c=T[z].c2;
		T[z].c2=d;
	}
	Visit(1,m);
	int ky=0;
	int ke[kl],ke2[kl],ke3[kl];
	int pr=0;
	for(z=0;z<t+f+e;z++){/*Recolha das estações com necessidade de aumento*//*Complexidade: O(t+f+e)*/
		if(T[z].r!=0 && T[z].o!=0){
			if(T[z].o>1+f&&T[z].d>f+e+1){
				ky=1;
				ke[pr]=T[z].o;
				pr+=1;
			}
		}
	}
	if(ky!=0){
		for(z=0;z<pr-1;z++){/*Complexidade: O(pr-1)*/
			for (y=0;y<pr-z-1;y++){/*Complexidade: O(pr-z-1)*/
				if(ke[y]>ke[y+1]){
					x=ke[y];
					ke[y]=ke[y+1];
					ke[y+1]=x;
				}
			}
		}
		printf("%d",ke[0]);
		for(z=1;z<pr;z++){/*Complexidade: O(pr-1)*/
			printf(" %d",ke[z]);
		}
	}
	printf("\n");
	int pr2=0;			
	for(z=0;z<t+f+e;z++){/*Recolha dos arcos com necessidade de aumento*//*Complexidade: O(t+f+e)*/
		if(T[z].r!=0 && T[z].o!=0){
			if(T[z].o>f+e+1){
				ke2[pr2]=(T[z].o)-e;
				ke3[pr2]=T[z].d;
				pr2+=1;
			}
			if(T[z].o>1&&T[z].o<f+2){
				ke2[pr2]=T[z].o;
				ke3[pr2]=T[z].d;
				pr2+=1;
			}
		}
	}
	for(z=0;z<pr2-1;z++){/*Complexidade: O(pr2-1)*/
		for (y=0;y<pr2-z-1;y++){/*Complexidade: O(pr2-z-1)*/
			if(ke2[y]>ke2[y+1]){
				x=ke2[y];
				w=ke3[y];
				ke2[y]=ke2[y+1];
				ke3[y]=ke3[y+1];
				ke2[y+1]=x;
				ke3[y+1]=w;
			}
			if(ke2[y]==ke2[y+1]&&ke3[y]>ke3[y+1]){
				x=ke3[y];
				ke3[y]=ke3[y+1];
				ke3[y+1]=x;
			}
		}
	}
	for(z=0;z<pr2;z++){/*Complexidade: O(pr2)*/
		x=0;
		for(y=0;y<pr;y++){/*Complexidade: O(pr2)*/
			if(ke[y]==ke2[z]||ke[y]==ke3[z])
				x=1;
		}
		if(x==0)
			printf("%d %d\n",ke2[z],ke3[z]);
	}
	return 0;
}