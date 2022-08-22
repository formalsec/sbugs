#include <stdio.h>
#include <stdlib.h>

int numero_subredes = 0;
int maior_vertice = 0;
int vertices_criticos = 0;
int maior_rede_v_criticos = 0;
int maior_rede_v_criticos2 = 0;

struct vertice
{
    int vertex;
    struct vertice* next;
};

struct vertice* cria_vertice(int v);

struct grafo
{
    int numRouters;
    int* visitado;
    struct vertice** matriz;
};

void swap(int *var_temp_1, int *var_temp_2)
{
	int temp = *var_temp_1;
	*var_temp_1 = *var_temp_2;
	*var_temp_2 = temp;
}


void bubblesort(int lista[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
    {
	    for (j = 0; j < n-i-1; j++)
        {
		    if (lista[j] > lista[j+1] && lista[j] == 0)
            {
			    swap(&lista[j], &lista[j+1]);
            }
        }
    }
}

void printArray(int lista[], int size)
{
    int i;
    for(i=0; i < size; i++)
    {
        printf("%d ", lista[i]);
    }
    printf("n");
}

void DFS(struct grafo* rede, int vertex) {
        struct vertice* adjacencias = rede->matriz[vertex];
        struct vertice* temp = adjacencias;

        rede->visitado[vertex] = 1;
        if (vertex > maior_vertice)
        {
            maior_vertice = vertex;
        }
        maior_rede_v_criticos++;

        while(temp!=NULL) {
            int vertices_connectados = temp->vertex;

            if(rede->visitado[vertices_connectados] == 0) {
                DFS(rede, vertices_connectados);
            }
            temp = temp->next;
        }
}


struct vertice* cria_vertice(int v)
{
    struct vertice* temp_vertice = malloc(sizeof(struct vertice));
    temp_vertice->vertex = v;
    temp_vertice->next = NULL;
    return temp_vertice;
}

struct grafo* cria_grafo(int vertices)
{
    struct grafo* rede = malloc(sizeof(struct grafo));
    rede->numRouters = vertices;

    rede->matriz = malloc(vertices * sizeof(struct vertice*));

    rede->visitado = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        rede->matriz[i] = NULL;
        rede->visitado[i] = 0;
    }
    return rede;
}

void adiciona_ligacao(struct grafo* rede, int origem, int dest)
{
    struct vertice* temp_vertice = cria_vertice(dest);
    temp_vertice->next = rede->matriz[origem];
    rede->matriz[origem] = temp_vertice;

    temp_vertice = cria_vertice(origem);
    temp_vertice->next = rede->matriz[dest];
    rede->matriz[dest] = temp_vertice;

}

void retira_ligacao(struct grafo* rede, int origem, int dest)
{
    struct vertice* temp_vertice = cria_vertice(dest);
    temp_vertice->next = NULL;
    rede->matriz[origem] = temp_vertice;

    temp_vertice = cria_vertice(origem);
    temp_vertice->next = NULL;
    rede->matriz[dest] = temp_vertice;

}

int DFS_Total(struct grafo* rede, int numero_vertices, int lista_dos_maiores[numero_vertices])
{
    int i, iterador = 0;
    numero_subredes = 0;
    maior_rede_v_criticos2 = 0;

    for(i=0; i<numero_vertices; i++)
    {
        if ((rede -> visitado[i]) == 0)
        {
            DFS(rede, i);
            lista_dos_maiores[iterador] = maior_vertice + 1;
            maior_vertice = 0;
            iterador++;
            numero_subredes++;
        }
        if (maior_rede_v_criticos > maior_rede_v_criticos2)
        {
            maior_rede_v_criticos2 = maior_rede_v_criticos;
        }
        maior_rede_v_criticos = 0;
    }
    return lista_dos_maiores[numero_subredes];
}

void pontos_criticos(int routers, int matriz_ligacoes[routers+1][routers+1], struct grafo* rede, int lista_dos_maiores[routers], int lista_dos_pontos_criticos[routers])
{
    int i, j, u, v, i2, i3, numero_subredes_temp = numero_subredes, matriz_ligacoes_perma[routers+1][routers+1];
    for (i2 = 1; i2 <=routers; i2++)
    {
        for(i3 = 1; i3 <= routers; i3++)
        {
            matriz_ligacoes_perma[i2][i3] = matriz_ligacoes[i2][i3];
        }
    }


    for (i=1; i<=routers; i++)
    {
        for (i2 = 1; i2 <=routers; i2++)
        {
            for(i3 = 1; i3 <= routers; i3++)
            {
                matriz_ligacoes[i2][i3] = matriz_ligacoes_perma[i2][i3];
            }
        }

        for (j=1; j<=routers; j++)
        {
            matriz_ligacoes[i][j] = 0;
            matriz_ligacoes[j][i] = 0;
        }

        struct grafo* graf_criado_p_matriz = cria_grafo(routers);
        for(u=1; u<=routers; u++)
        {
            for(v=1; v<=routers; v++)
            {
                if (matriz_ligacoes[u][v] == 1)
                {
                    adiciona_ligacao(graf_criado_p_matriz,u-1,v-1);
                }
            }
        }

        DFS_Total(graf_criado_p_matriz, routers, lista_dos_maiores);
        if(numero_subredes_temp < numero_subredes - 1)
        {
            vertices_criticos++;
            lista_dos_pontos_criticos[vertices_criticos] = i;
        }
    }

    for (i2 = 1; i2 <=routers; i2++)
        {
            for(i3 = 1; i3 <= routers; i3++)
            {
                matriz_ligacoes[i2][i3] = matriz_ligacoes_perma[i2][i3];
            }
        }
}

void sobra_de_pontos_crit(int routers, int lista_dos_pontos_criticos[routers], int matriz_ligacoes[routers+1][routers+1], int lista_dos_maiores[routers])
{
    int i, j, k, u, v;
    for(j=1; j<=vertices_criticos; j++)
    {
        k = lista_dos_pontos_criticos[j];

        for(i=1; i <= routers ; i++)
        {
            matriz_ligacoes[i][k] = 0;
            matriz_ligacoes[k][i] = 0;
        }
    }


    struct grafo* graf_criado_para_matriz = cria_grafo(routers);
    for(u=1; u<=routers; u++)
    {
        for(v=1; v<=routers; v++)
        {
            if (matriz_ligacoes[u][v] == 1)
            {
                    adiciona_ligacao(graf_criado_para_matriz,u-1,v-1);
            }
        }
    }

    DFS_Total(graf_criado_para_matriz, routers, lista_dos_maiores);
}

int main()
{
    int routers,liga,i,u,v,a,j;
    scanf("%d", &routers);
    int matriz_ligacoes[routers+1][routers+1];

    for(i=0; i < routers; i++)
    {
        for(j=0; j < routers; j++)
        {
            matriz_ligacoes[i][j] = 0;
        }
    }

    struct grafo* graf = cria_grafo(routers);
    scanf("%d", &liga);

    for(i=0; i<liga; i++)
    {
        scanf("%d%d",&u,&v);
        matriz_ligacoes[u][v] = 1;
        matriz_ligacoes[v][u] = 1;
        adiciona_ligacao(graf,u-1,v-1);
    }

    int lista_dos_maiores[routers];
    
    lista_dos_maiores[routers] = DFS_Total(graf, routers, lista_dos_maiores);
    printf("%d\n",numero_subredes);

    bubblesort(lista_dos_maiores, numero_subredes);

    for(i = 0; i < numero_subredes; i++)
    {
        a = lista_dos_maiores[i];
        printf("%d ",a);
    }
    printf("\n");

    int lista_dos_pontos_criticos[routers];

    pontos_criticos(routers, matriz_ligacoes, graf, lista_dos_maiores, lista_dos_pontos_criticos);

    printf("%d\n",vertices_criticos);

    sobra_de_pontos_crit(routers, lista_dos_pontos_criticos, matriz_ligacoes, lista_dos_maiores);

    printf("%d\n",maior_rede_v_criticos2);

    return 0;
}
