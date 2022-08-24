/*************************************************************
 * Projeto 2 ASA - Custo de Processos
 *
 * Grupo Al152
 * Filipe Joao Cabral Neves // Numero de aluno #87318
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define oo 1000000000

/*                   Estrutura do Projeto
 *
 ************************************************************/

typedef struct {
	int** Fluxo;      /* guarda fluxo */                                        
  	int** Com;        /* guarda valor das comunicacoes */   
	int* visitado;    /* guarda se processo ja foi visitado */ 
	int* path;        /* para o augmentation path do algoritmo Ford-Fulkerson */                                        
} MatrixProcessos;

/*                    Variaveis Globais
 *
 ************************************************************/

MatrixProcessos matriz;                                                 
int processos, comunicacoes, raiz_matriz, cauda, cabeca, solucao;
int* Fila;   

/*                   Funcoes Auxiliares
 *
 ************************************************************/

int min(int x, int y)
{
	return x<y ? x : y;
}

void inicializa(int i, int val1, int val2, int val3, int flag)
{
	if(flag == 0)
	{
    	matriz.Com[processos+1][i+1] = val2;
    	matriz.Com[i+1][processos+1] = val2;
    	matriz.Com[0][i+1] = val1;
    	matriz.Com[i+1][0] = val1;
    }
    else
    {
        matriz.Com[val2][val1] = val3;
    	matriz.Com[val1][val2] = val3;
    }
}

void freememoria()
{
	int i = 0;

	for(i = 0; i < raiz_matriz; i++)
    {
    	free(matriz.Fluxo[i]);                              
    	free(matriz.Com[i]);                              
   	}

    free(matriz.Fluxo);                                    
    free(matriz.Com); 
    free(matriz.visitado);
    free(matriz.path);  
    free(Fila); 
}

/*              ALgoritmo BFS e Ford-Fulkerson
 *
 ************************************************************/

int bfs_algorithm(int a, int b)
{
 	int i, j;
	for(i = 0; i < (raiz_matriz); i++)
		matriz.visitado[i] = 0;

	cauda = 0;
	cabeca = cauda;

	Fila[cauda] = a;
 	matriz.visitado[a] = 1;
 	cauda++;
	matriz.path[a] = -1;
	
	while(cabeca != cauda)
	{	
		i = Fila[cabeca];
 		matriz.visitado[i] = 2;
		cabeca++;
    	for(j = 0; j < (raiz_matriz); j++)
    	{
      		if(matriz.visitado[j] == 0 && matriz.Com[i][j] - matriz.Fluxo[i][j] > 0)
      		{
        		Fila[cauda] = j;
 				matriz.visitado[j] = 1;
 				cauda++;
        		matriz.path[j] = i;
      		}
    	}
  	}
  	
  	return matriz.visitado[b] == 2;
}

int ff_algorithm(int source, int sink)
{
	int i, j, p;
	int fluxomax = 0;

	for(i = 0; i < raiz_matriz; i++) 
	{
		for(j = 0; j < raiz_matriz; j++)
    		matriz.Fluxo[i][j] = 0;
 	}

 	while(bfs_algorithm(source, sink))
 	{	
 		int incr = oo;

    	for(p = processos + 1; matriz.path[p] >= 0; p = matriz.path[p])
      		incr = min(incr, matriz.Com[matriz.path[p]][p] - matriz.Fluxo[matriz.path[p]][p]);

    	for(p = processos + 1; matriz.path[p] >= 0; p = matriz.path[p])
    	{
     		matriz.Fluxo[matriz.path[p]][p] += incr;
    		matriz.Fluxo[p][matriz.path[p]] -= incr;
    	}

    	fluxomax += incr;
  	}

	return fluxomax;
}

/*                      Funcao Main
 *
 ************************************************************/

 int main()
 {
 	int val_X, val_Y, i = 0, j = 0, l = 0, m = 0, o = 0, val1, val2, val3;

 	if(scanf("%d %d", &processos, &comunicacoes) == 2)
	{
		if(processos == 0 && comunicacoes == 0)
		{
			printf("0\n");
			return EXIT_SUCCESS;
		}
		else if(processos == 1 && comunicacoes == 0)
		{
			if(scanf("%d %d", &val_X, &val_Y) == 2)
			{
				if(val_X < val_Y)
				{
					printf("%d\n", val_X);
					return EXIT_SUCCESS;
				}
				else
				{
					printf("%d\n", val_Y);
					return EXIT_SUCCESS;
				}
			}
			else
				return EXIT_FAILURE;
		}
		else if(processos < 2 || comunicacoes < 0)
			return (EXIT_FAILURE);

		raiz_matriz = processos + 2;  /* tamanho para a matriz mais os custos do X e do Y */

		/* para este projeto, a forma de encontrar o fluxo depende de uma matriz que contem 
		 * os valores de custo de x e y bem como das suas comunicacoes. Aplicamos o
		 * Ford-Fulkerson nessa matriz para obter o valor do fluxo que sera a solucao
		 **********************************************************************************/

    	Fila = malloc(sizeof(int)*raiz_matriz);
		matriz.Com = malloc(sizeof(int*)*raiz_matriz);          
   		matriz.Fluxo = malloc(sizeof(int*)*raiz_matriz);

   		for(i = 0; i < (raiz_matriz); i++)
   		{   			 
      		matriz.Fluxo[i] = malloc(sizeof(int)*raiz_matriz);   
     		matriz.Com[i] = malloc(sizeof(int)*raiz_matriz);        
    	}

    	for(j = 0; j < (raiz_matriz); j++)
    	{
      		for (l = 0; l < (raiz_matriz); l++)
        		matriz.Com[j][l] = 0;
   		}

    	for(m = 0; m < processos; m++)
    	{
      		if(scanf("%d %d", &val1, &val2) == 2)
      		{
        		inicializa(m, val1, val2, 0, 0);
      		}
    	}

    	for(o = 0; o < comunicacoes; o++)
    	{
      		if(scanf("%d %d %d", &val1, &val2, &val3) == 3)
      		{
        		inicializa(o, val1, val2, val3, 1);
      		}
    	}

    	matriz.visitado = malloc(sizeof(int)*raiz_matriz);                    
    	matriz.path = malloc(sizeof(int)*raiz_matriz);

    	solucao = ff_algorithm(0, (processos + 1));

	   	freememoria();

    	printf("%d\n", solucao);

		return EXIT_SUCCESS;
	}
	else
		return EXIT_FAILURE;
 }