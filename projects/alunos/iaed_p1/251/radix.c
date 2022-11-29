#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>
#include "radix.h"

/*Maximo de produtos*/
#define MAX_PROD 10000

/*Implementacao do algoritmo de ordencao radix sort*/

/*
	funcao (int) getMax:
	-Argumentos: matriz de inteiros n x 2 e o numero de linhas da matriz
	-Encontra o maior valor da matriz segunda as segundas entradas da matriz
	-Retorna o valor maximo das segundas entradas da matriz
*/
int getMax(int arr[][2], int n) 
{ 
	int max = arr[0][1], i; 
	for (i = 1; i < n; i++) 
		if (arr[i][1] > max) 
			max = arr[i][1]; 
	return max; 
} 

/*
	funcao (int) countingSort:
	-Argumentos: matriz de inteiros n x 2 e o numero de linhas da matriz e o interiro bDEz que equivale a 
	10^(iteraco do radix sort)
	-Funcao que executa o algoritmo de ordenacao counting sort de acordo com valor recebido de bDez
*/
void countingSort(int arr[][2], int n, int bDez) 
{ 
	int output[MAX_PROD][2]; 
	int i, count[500] = {0}; 

	for (i = 0; i < n; i++) 
		count[ (arr[i][1]/bDez)%10 ]++; 

	for (i = 1; i < 10; i++) 
		count[i] += count[i - 1]; 
 
	for (i = n - 1; i >= 0; i--) 
	{ 
		output[count[ (arr[i][1]/bDez)%10 ] - 1][1] = arr[i][1];
		output[count[ (arr[i][1]/bDez)%10 ] - 1][0] = arr[i][0]; 
		count[ (arr[i][1]/bDez)%10 ]--; 
	} 
 
	for (i = 0; i < n; i++)
	{ 
		arr[i][0] = output[i][0];
		arr[i][1] = output[i][1]; 
	}
} 
 
 /*
	funcao (void) radixSort:
	-Argumentos: matriz de inteiros n x 2 e o numero de linhas da matriz
	-Funcoes auxiliares: getMax, countingSort
	-Funcao que executa o algoritmo de ordenacao raduix Sort de acordo com a matriz de duas dimensoes fornecida
*/
void radixSort(int arr[][2], int n) 
{ 
	int m = getMax(arr, n), bDez; 

	for (bDez = 1; m/bDez > 0; bDez *= 10) 
		countingSort(arr, n, bDez); 
}