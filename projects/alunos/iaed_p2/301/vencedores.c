#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"
#include <string.h>
#include <stdio.h>

void merge(char **aux, char **a, int l, int m, int r){
	int i, j, k;
	/*os dois primeiros ciclos constroem o vector auxiliar */
	for(i = m+1; i > l; i--){
		aux[i-1] = a[i-1];
	}
	for(j = m; j < r; j++){
		aux[r+m-j] = a[j+1];
	}
	/*ordena por ordem alfabetica*/
	for(k = l; k <= r; k++){
		if(strcmp(aux[j], aux[i]) < 0){
			a[k] = aux[j--];
		}else{ 
			a[k] = aux[i++]; 
		}
	}
}

/*primeira etapa do algoritmo merge sort
nesta primeira etapa o algoritmo comeca por dividir a meio o array que lhe foi dado como argumento
(dentro dos limites l e r), esta divisao e feita de forma recursiva e e feita ate obtermos vetores 
com um so elemento. Notar que os argumentos tipo e aux apenas vao servir para a proxima etapa do merge*/
void mergesort(char **aux, char **a, int l, int r){
	int m = (r+l)/2;
	if(r <= l) return;
	mergesort(aux, a, l, m);
	mergesort(aux, a, m+1, r);
	merge(aux, a, l, m, r);
}




/*funcao que mostra uma tabela com as equipas que tem mais vitorias*/
void listaVencedores(Hash_tableEq *equipasT, int nl){
	int i, i2 = 0, max = -1, counter = 0, len;
	char buffer[MAX_NOME];
	char **backup, **aux;
	Hash_nodeEq *node;
	/*procura na tabela das equipas qual e o maximo de vitorias*/
	for(i = 0; i < equipasT->capacity; ++i){
		node = equipasT->table[i];
		while(node != NULL){
			if(node->equipa->vitorias == max) counter++;
			else if(node->equipa->vitorias > max){
				max = node->equipa->vitorias;
				counter = 1;
			} 
			node = node->next;
		}
	}
	backup = (char**) can_fail_calloc(counter, sizeof(char*));
	/*faz uma copia com as equipas que tem o numero maximo de vitorias*/
	for(i = 0; i < equipasT->capacity; ++i){
		node = equipasT->table[i];
		while(node != NULL){
			if(node->equipa->vitorias == max){
				strcpy(buffer, node->equipa->nome);
				len = strlen(buffer) + 1;
				backup[i2] = (char*) can_fail_malloc(sizeof(char) * len);
				strcpy(backup[i2], node->equipa->nome);
				i2++;
			}
			node = node->next;
		}
	}
	aux = (char**) can_fail_calloc(i2+1, sizeof(char*));
	/*ordena alfabeticamente*/
	mergesort(aux, backup, 0, i2-1);
	/*se nao existir equipas nao faz nada*/
	if(max == -1){	
		free(backup);
		free(aux);
		return;
	} 
	else printf("%d Melhores %d\n", nl, max);
	/*imprime as equipas com mais vitorias*/
	for(i = 0; i <= i2-1;  ++i){
		if(strcmp(backup[i], "")) printf("%d * %s\n", nl, backup[i]);
		free(backup[i]);
	}
	free(backup);
	free(aux);
}






