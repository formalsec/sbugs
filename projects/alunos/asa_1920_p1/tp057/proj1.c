#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*
 	Projecto 1 - ASA - TP057
	LEIC-T - 73942 - Miguel Mestre 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

	int n = 0; 		/* nº de alunos		*/	
	int m = 0;		/* nº de Relações 	*/
	int i = 0;		/* iterador 1		*/		
	int j = 0;		/* iterador 2		*/
	int copia = 0; 			/*	o que copia   		pares			*/
	int deixa = 1;			/*	o que deixa copiar	impares			*/
	int totalCopias =0;		/*  para saber o total de 'Copiantes'	*/
	int totalDeixas =0;		/*  para saber o total de 'Deixantes'	*/
	bool final = true;			/* a ordem para parar no while			*/
	int checkiffor = 0; 	/* uma flag para saber se houve alterações nas notas */

	scanf("%d,", &n);
	scanf("%d", &m);

	int alunos[n];	/* lista de notas	 	*/
	int rel[m*2]; 	/* lista de relações    */

	for(i=0; i<n ; ++i){
		scanf(" %d", &alunos[i]);
	}

	for(j=0; j<m; ++j, copia += 2, deixa += 2){
		scanf("%d %d", &rel[copia], &rel[deixa]);
		if(rel[copia] > n || rel[deixa] > n){
			exit(0);
		}	
	}

	totalCopias = (m*2)-2;
	totalDeixas = (m*2)-1;
	copia -= 2;
	deixa -= 2;

			/*	Correr o Algoritmo 	*/

	for(i=0; i<m; ++i, copia -= 2, deixa -= 2){
		if(alunos[rel[copia]-1] < alunos[rel[deixa]-1]){
			alunos[rel[copia]-1] = alunos[rel[deixa]-1];
			checkiffor += 1;
		} 
	}

	while(final == true){
		if (checkiffor != 0){
			checkiffor = 0;
			copia = totalCopias;
			deixa = totalDeixas;
			for(i=0; i<m; ++i, copia -= 2, deixa -= 2){
				if(alunos[rel[copia]-1] < alunos[rel[deixa]-1]){
					alunos[rel[copia]-1] = alunos[rel[deixa]-1];
					checkiffor += 1;
				}
			}
		} else {
			final = false;
			}
	}
			/*	Imprimir a lista resultante		*/

	for(i=0; i < n; ++i){
		printf("%d\n", alunos[i]);
	}

 return 0;
}