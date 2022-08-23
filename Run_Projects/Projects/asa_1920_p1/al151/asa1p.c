#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct Aluno Aluno;



struct Aluno{
	int nota;
	int c_relacoes;
	int* relacoes;
	

	int fecho;
	bool visited;
	

	int arvore;
	
};


void DFSvisit(Aluno* g,int id_aluno,int* fechados,int* arvores){
	g[id_aluno].visited=true;
	int i;
	for(i=0;i<g[id_aluno].c_relacoes;i++){
		if(g[g[id_aluno].relacoes[i]].visited==false){
			DFSvisit(g,g[id_aluno].relacoes[i],fechados,arvores);
		}
	}
	
	g[id_aluno].arvore=arvores[0];
	g[id_aluno].fecho=fechados[0];
	fechados[0]=fechados[0]+1;
}


void DFS(Aluno* g,int* ordem, int total){
	int i;
	int* arvores;
	arvores = malloc(sizeof(int));

	
	int* fechados;
    	fechados = malloc(sizeof(int));


	fechados[0] = 0;
	arvores[0] = 0;


	for(i=0;i<total;i++){
		g[i].visited = false;
		g[i].fecho = 0;
		g[i].arvore = 0;

	}
	for(i=0;i<total;i++){
		if(g[ordem[i]].visited == false){
			DFSvisit(g,ordem[i],fechados,arvores);
			arvores[0]+=1;

		}
		

	}
}



int main(){
	int i, e;
	int n_alunos, n_relacoes;
	scanf("%d, %d",&n_alunos, &n_relacoes);
	
	
	Aluno alunos[n_alunos];
	for(i=0;i<n_alunos;i++){
		Aluno *aluno = malloc(sizeof(struct Aluno));
		alunos[i] = *aluno;
		alunos[i].nota = 0;
		alunos[i].visited = false;
		alunos[i].c_relacoes = 0;
		alunos[i].fecho=0;
		alunos[i].arvore=0;
		alunos[i].relacoes = malloc(sizeof(int)*n_alunos-1);
	}
	
		Aluno alunos_T[n_alunos];
	for(i=0;i<n_alunos;i++){
		Aluno *aluno = malloc(sizeof(struct Aluno));
		alunos_T[i] = *aluno;
		alunos_T[i].nota = 0;
		alunos_T[i].visited = false;
		alunos_T[i].c_relacoes = 0;
		alunos_T[i].fecho=0;
		alunos_T[i].arvore=0;
		alunos_T[i].relacoes = malloc(sizeof(int)*n_alunos-1);
	}
	
	int in_nota, in_aluno, in_relacao;
	
	for(i=0; i<n_alunos;i++){
		scanf("%d",&in_nota);
		alunos[i].nota = in_nota;
		alunos_T[i].nota = in_nota;
	}
	
	
	for(i=0; i<n_relacoes;i++){
		scanf("%d %d",&in_aluno,&in_relacao);
		alunos[in_aluno-1].relacoes[ alunos[in_aluno-1].c_relacoes ] = in_relacao-1;
		alunos[in_aluno-1].c_relacoes +=1;
		

		alunos_T[in_relacao-1].relacoes[ alunos_T[in_relacao-1].c_relacoes ] = in_aluno-1;
		alunos_T[in_relacao-1].c_relacoes +=1;
	}
	
	int s_ordem[n_alunos];
	
	for(i=0; i<n_alunos;i++){
		s_ordem[i]=i;
	}
	
	DFS(alunos,s_ordem,n_alunos);
	
	for(i=0; i<n_alunos;i++){
		s_ordem[n_alunos-1-alunos[i].fecho]=i;
	}
	
	DFS(alunos_T,s_ordem,n_alunos);
	
	int n_arvores=0;
	
	for(i=0; i<n_alunos;i++){
		if(alunos_T[i].arvore>n_arvores){
			n_arvores=alunos_T[i].arvore;
			
		}

	}
	
	int max_de_arvore[n_arvores+1];
	
	for(i=0; i<=n_arvores;i++){
		max_de_arvore[i]=0;
	}
	
	for(i=0; i<n_alunos;i++){
		if(max_de_arvore[alunos_T[i].arvore]<alunos_T[i].nota){
			max_de_arvore[alunos_T[i].arvore]=alunos_T[i].nota;
			
		}

	}
	

	for(i=n_alunos-1; i>=0;i--){
		for(e=alunos[s_ordem[i]].c_relacoes-1; e>=0;e--){
			if(max_de_arvore[alunos_T[alunos[s_ordem[i]].relacoes[e]].arvore]>max_de_arvore[alunos_T[s_ordem[i]].arvore]){
				max_de_arvore[alunos_T[s_ordem[i]].arvore]=max_de_arvore[alunos_T[alunos[s_ordem[i]].relacoes[e]].arvore];
			}
		}
		
	}
	
	for(i=0; i<n_alunos;i++){
		printf("%d\n",max_de_arvore[alunos_T[i].arvore]);
	}
	
	
	return 0;
	
	
	

	
}
