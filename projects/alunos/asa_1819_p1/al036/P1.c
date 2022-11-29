#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

struct dfspass{
	int topsub;
	int time;
}dfspass;
struct ll{
	int val;
	struct ll *next;
}ll;

int ponto(int size,int i,int j){
	/*retorna o valor para um vetor de matriz dado o tamanho
	da matrix e o par de coordenadas.*/
	return i + j * size;
}

struct ll *llinsert(struct ll *entry,struct ll *list){
	struct ll *i,*j;
	if(list == NULL){
		return entry;
	}
	for (i =list,j = NULL; i != NULL;j = i,i = i->next){
		if(entry->val < i->val){
			entry->next = i;
			if (j == NULL){
				return entry;
			}
			j->next = entry;
			return list;
		}
	}
	j->next = entry;
	return list;
}

int adj(struct ll *la,int a){
	if (la == NULL || la->val > a)
		return 0;
	return (la->val == a || adj(la->next,a));
}

struct dfspass *visita(int v,struct ll **la,int *Visitado,int Max,
				int *d,int *p,int *low,struct dfspass *pass){
	int i;
	Visitado[v] = 1;
	d[v] = ++pass->time;
	low[v] = pass->time;
	for (i = 0; i < Max; ++i){
		/*visita os vertices adjacentes nao visitados*/
		if (adj(la[v],i) && Visitado[i] == 0){
			p[i] = v;
			if (i > pass->topsub){
				pass->topsub = i;
			}
			pass = visita(i,la,Visitado,Max,d,p,low,pass);
		}
		/*regista o valor de low*/
		if(i != p[v] && adj(la[v],i) &&
				(low[v] == -1 || low[i] < low[v])){
			low[v] = low[i];
		}
	}
	return pass;
}

int dimrede(int v,struct ll **la,int *Visitado,int Max,int num){
	int i;
	Visitado[v] = 1;
	num++;
	for (i = 0; i < Max; ++i){
		/*visita os vertices adjacentes nao visitados*/
		if (adj(la[v],i) && Visitado[i] == 0){
			num = dimrede(i,la,Visitado,Max,num);
		}
	}
	return num;
}


int main() {
	

	int In,In2,e1,e2,i;
	struct ll **la,*topl,*entry;

	scanf("%d",&In);

	la = can_fail_malloc(In * sizeof(struct ll *));	
	for (i = 0; i < In; ++i){
		la[i] = NULL;
	}

	scanf("%d",&In2);

	/*le as ligacoes e cria a lista de adjacencias*/
	for (i = 0; i < In2; ++i) {
		scanf("%d",&e1);
		scanf("%d",&e2);
		/*transformar em base 0*/
		e1--;
		e2--;

		entry = can_fail_malloc(sizeof(ll));
		entry->val = e2;
		entry->next = NULL;
		la[e1] = llinsert(entry,la[e1]);
		entry = can_fail_malloc(sizeof(ll));
		entry->val = e1;
		entry->next = NULL;
		la[e2] = llinsert(entry,la[e2]);
	}

	/*faz uma dfs e determina o numero de subredes*/
	int *Visitado,*d,*p,*low;
	int Nsub = 0;
	Visitado = can_fail_malloc( In * sizeof(int));
	d = can_fail_malloc( In * sizeof(int));
	p = can_fail_malloc( In * sizeof(int));
	low = can_fail_malloc( In * sizeof(int));
	for (i = 0; i < In; ++i){
		Visitado[i] = 0;
		d[i] = -1;
		p[i] = -1;
		low[i] = -1;
	}
	struct dfspass *pass;
	pass = can_fail_malloc(sizeof(struct dfspass));
	pass->time = 0;
	topl = NULL;
	for (i = 0; i < In; ++i){
		if(Visitado[i] == 0){
			Nsub++;
			pass->topsub = i;
			pass = visita(i,la,Visitado,In,d,p,low,pass);
			entry = can_fail_malloc(sizeof(ll));
			entry->val = pass->topsub+1;
			entry->next = NULL;
			topl = llinsert(entry,topl);
		}
	}
	entry = topl;
	printf("%d\n%d",Nsub,entry->val);
	for (i = 1; i < Nsub; ++i){
		topl = entry;
		entry = entry->next;
		free(topl);
		printf(" %d",entry->val);
	}
	free(entry);
	printf("\n");
	free(pass);

	/*determina o numero de vertices ponte*/
	int np = 0,j,nl;
	for ( i = 0; i < In; ++i){
		if (p[i] == -1){
			nl = 0;
			for (j = 0; j < In; ++j){
				if (p[j] == i){
					nl++;
				}
			}
			if (nl > 1){
				np++;
				for (entry = la[i],topl = NULL;entry != NULL;topl = entry,entry = entry->next){
					free(topl);
				}
				la[i] = NULL;
			}
		}
		else{
			for ( j = 0; j < In; ++j){
				if (p[j] == i && low[j] >= d[i] ){
					np++;
					for (entry = la[i],topl = NULL;entry != NULL;topl = entry,entry = entry->next){
						free(topl);
					}
					la[i] = NULL;
					break;
				}
			}
		}
	}
	printf("%d\n",np);
	int max = 1;
	for (i = 0; i < In; ++i){
		Visitado[i] = 0;
	}
	for (i = 0; i < In; ++i){
		if (la[i] != NULL && Visitado[i] == 0){
			j = dimrede(i,la,Visitado,In,0);
			if (j > max)
				max = j;
		}
	}
	printf("%d\n",max);

	for (i = 0; i < In; ++i){
		for (entry = la[i],topl = NULL;entry != NULL;topl = entry,entry = entry->next){
			free(topl);
		}
	}
	free(la);
	free(d);
	free(p);
	free(Visitado);
	free(low);
	return 0;
}