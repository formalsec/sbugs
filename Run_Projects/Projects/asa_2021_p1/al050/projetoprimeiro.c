#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*Joao Vasco 95611 ,  Maria André 95628 */

typedef struct
{
    int number;
    int n_filhos;
    bool n_pais;
    int *filhos;
    bool visited;

} Piece;

Piece *table;
int *w;
int *temp;
int *stack;

int t = 0;
int first_output = 0;
int n_pieces, n_dependencies;

void putPiece(int first, int second)
{
    if (table[first - 1].n_filhos == 0)
    {
        table[first - 1].n_filhos++;
        table[first - 1].filhos = malloc(sizeof(int));
        table[first - 1].filhos[0] = second - 1;
        table[second - 1].n_pais = true;

    }
    else
    {

        table[first - 1].n_filhos++;
        table[first - 1].filhos = realloc(table[first - 1].filhos, sizeof(int) * table[first - 1].n_filhos);
        table[first - 1].filhos[table[first - 1].n_filhos - 1] = second - 1;
        table[second - 1].n_pais = true;
    }
}

void inicializeTable()
{
    int i;

    w = malloc(sizeof(int) * n_pieces);

    for (i = 0; i < n_pieces; i++)
    {
        table[i].number = i;
        table[i].n_filhos = 0;
        table[i].n_pais = false;
        table[i].visited = false;
        w[i] = 1;
    }
}

void run_dominos()
{
    int i;

    for (i = 0; i < n_pieces; i++)
    {
        if (table[i].n_pais == false)
        {

            first_output++;
        }
    }
}

int topologicalSort()
{
    int  tail, tail_order;
    tail = 0;
    tail_order = 0;
   
    int vertice = 0;
    int u,v;
    int x;
    int i;
    int node;
    int ans = 0;
    int * order = (int *) malloc(n_pieces * sizeof(int));
    int * lista = (int *) malloc(n_pieces * sizeof(int));
    int * array = (int *) malloc(n_pieces * sizeof(int));

    for (node = 0; node < n_pieces; node++)
    {

        lista[node] = 0;
    }

    for (node = 0; node < n_pieces; node++)
    {

        for (i = 0; i < table[node].n_filhos; i++)
        {

            lista[table[node].filhos[i]] = lista[table[node].filhos[i]] + 1;
        }
    }

    for (i = 0; i < n_pieces; i++)
    {

        if (lista[i] == 0)
        {
            array[tail] = i;
            tail++;
        }
    }
i=0;
	

    while (vertice < n_pieces)
    {	
	tail--;
 
	u = array[tail];        

        order[tail_order] = u;
	
        tail_order++;


        for (i = 0; i < table[u].n_filhos; i++)
        {
	v=table[u].filhos[i];
	

            lista[v]--;
            if (lista[v] == 0)
            {  
                array[tail] = v;
                tail++;
            }
        }
	
        vertice++;
    }

	

   
    for (i = 0; i < n_pieces; i++)
    {
        for (x = 0; x < table[order[i]].n_filhos; x++)
        {   

	
            if (w[order[i]] >= w[table[order[i]].filhos[x]])
            {
                w[table[order[i]].filhos[x]] = w[order[i]] + 1;
            }
        }
    }


    for (i = 0; i < n_pieces; i++)
    {

        if (ans < w[i])
        {
            ans = w[i];
        }
    }
    free(order);
    free(lista);
    free(array);
    return ans;
}



int main()
{   
    
    int first, second;
    int i, k;
    scanf("%d %d", &n_pieces, &n_dependencies);


    table = malloc(sizeof(Piece) * n_pieces);

    inicializeTable();

    for (i = 1; i <= n_dependencies; i++)
    {
        scanf("%d %d", &first, &second);
        
        
        putPiece(first, second);
       
    }
    run_dominos();
    k = topologicalSort();
    printf("%d %d\n", first_output, k);
    free(w);
    for (i = 0; i < n_pieces; i++)
    {
        free(table[i].filhos);
    }

    free(table);

    return 0;
}