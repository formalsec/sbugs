#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*Trabaho realizado por
 Nuno Damas, 84155
Grupo 147*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _no {
    long id;
    struct _no *next;
}no;

typedef struct _sr {
    long id;
    long counter;
}sr;

void CriaMatriz(long , long , no*);
void NrSubRede(long , long* , no* , long );
void Identificadores(long* , long* , long );
void libertaLista(no *, long);
void OrdenaLista(long * , long ,long );
void printLista(long* , long );
void NovoC(long , no* );
void libertaC(no* );
void marcaC(long* , no* );
void Contador(long* , long* , long );
void Tarjan(long , long , long* , long* , long* , no* , no* , long* );

int main()
{
    long N = 0, M = 0, i = 0, R = 0, Rc = 0, counterc = 0, j = 0, visitado = 0;
    no *matriz = NULL;
    long *routers = NULL;
    long *routersc = NULL;
    long *d = NULL;
    long *low = NULL;
    long *subredec = NULL;
    long *subredes = NULL;
    no*headc = NULL;

    if(scanf("%li", &N) == 0) exit(0);
    if(scanf("%li", &M) == 0) exit(0);

    /******************************************************************************
     * Alocacao da memoria necessaria para a matriz de adjacencias
     * Criacao da matriz
     *****************************************************************************/
    matriz=(no*)can_fail_calloc(N, sizeof(no));

    if(matriz==NULL) exit(0);

    CriaMatriz(M, N, matriz);

    /**********************************************************************************
     * Alocacao da memoria necessaria para um array de indicacao da subrede dos routers
     * Criacao do array
     *********************************************************************************/
    routers=(long*)can_fail_calloc(N, sizeof(long));

    if(routers==NULL) exit(0);

    for(i=0;i<N;i++){
        if(routers[i] == 0) {
            routers[i] = ++R;
            NrSubRede(i, routers, matriz, R);
        }
    }
    printf("%li\n", R);

    /******************************************************************************
     * Alocacao da memoria necessaria para um array de indicacao das subredes
     * Criacao do array
     *****************************************************************************/

    subredes=(long*)can_fail_calloc(R, sizeof(long));

    if(subredes==NULL) exit(0);

    Identificadores(subredes, routers, N);

    OrdenaLista(subredes, 0, R-1);

    printLista(subredes, R);

    headc = (no*) can_fail_malloc (sizeof (no));
    headc->id = 0;
    headc->next = NULL;

    low=(long*)can_fail_calloc(N, sizeof(long));
    if(low==NULL) exit(0);

    d=(long*)can_fail_calloc(N, sizeof(long));
    if(d==NULL) exit(0);

    for(i=0;i<R;i++)
    {
        visitado = 1;
        j = subredes[i]-1;
        Tarjan(j, j, &counterc, low, d, headc, matriz, &visitado);
    }

    printf("%li\n", counterc);

    routersc=(long*)can_fail_calloc(N, sizeof(long));
    if(routersc==NULL) exit(0);

    marcaC(routersc, headc);

    for(i=0;i<N;i++){
        if(routersc[i] == 0) {
            routersc[i] = ++Rc;
            NrSubRede(i, routersc, matriz, Rc);
        }
    }

    subredec=(long*)can_fail_calloc(Rc, sizeof(long));
    if(subredec==NULL) exit(0);

    Contador(subredec, routersc, N);
    counterc = 0;

    for(i=0;i<Rc;i++)
    {
        if(subredec[i] > counterc) counterc = subredec[i];
    }

    printf("%li\n", counterc);

     /******************************************************************************
     * Libertacao da matriz
     *****************************************************************************/
        libertaC(headc);
        libertaLista(matriz, N);
        free(matriz);
        free(routers);
        free(subredes);
        free(routersc);
        free(subredec);
        free(d);
        free(low);

    return 0;
}

 void CriaMatriz(long M, long N, no*router){

    long i=0, u = 0, v = 0;
    no*novou = NULL;
    no*novov = NULL;

    for (i=0;(i<M);i++){
        if(scanf("%li", &u) == 0) exit(0);
        if(scanf("%li", &v) == 0) exit(0);

        novou = (no*) can_fail_malloc(sizeof(no));
        if(novou == NULL)
        {
            printf ("Erro na alocacao de memoria \n");
            exit (0);
        }
        novou->id = v;
        novou->next = router[u-1].next;
        router[u-1].next = novou;

        novov = (no*) can_fail_malloc(sizeof(no));
        if(novov == NULL)
        {
            printf ("Erro na alocacao de memoria \n");
            exit (0);
        }
        novov->id = u;
        novov->next = router[v-1].next;
        router[v-1].next = novov;


    }

    return;
 }

 void NrSubRede(long i, long* routers, no* matriz, long R)
 {
    long j = 0;
    no*aux = NULL;

    aux = matriz[i].next;
    while(aux!= NULL){
        j = aux->id - 1;
        if(routers[j] == 0){
            routers[j] = R;
            NrSubRede(j, routers, matriz, R);
        }
        aux = aux->next;
    }

    return;
 }

 void Identificadores(long* subredes, long* routers, long N)
 {
    long i = 0, j = 0;

    for (i=0;i<N;i++){
        j = (routers[i])-1;
        if (i>=subredes[j]) subredes[j] = (i+1);
    }

    return;
 }

void libertaLista(no *matriz, long N) {

    int i = 0;
    no *aux, *newhead = NULL;  /* auxiliar pointers to travel through the list */

    for(i=0;i<N;i++){
      for(aux = matriz[i].next; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux);
      }
    }
    return;
}

void OrdenaLista(long *subredes, long l, long r)
{
    long i, j, x, y;

    i = l;
    j = r;
    x = subredes[(l + r) / 2];

    while(i <= j) {
        while(subredes[i] < x && i < r) {
            i++;
        }
        while(subredes[j] > x && j > l) {
            j--;
        }
        if(i <= j) {
            y = subredes[i];
            subredes[i] = subredes[j];
            subredes[j] = y;
            i++;
            j--;
        }
    }

    if(j > l) {
        OrdenaLista(subredes, l, j);
    }
    if(i < r) {
        OrdenaLista(subredes, i, r);
    }

    return;
}

void printLista(long* subredes, long R)
{
    long i = 0;

    for(i=0;i<(R-1);i++)
    {
        printf("%li ", subredes[i]);
    }
    printf("%li\n", subredes[R-1]);

    return;
}

void NovoC(long i, no*hc)
{
    no*novo = NULL;

    novo = (no*) can_fail_malloc (sizeof (no));
    if(novo==NULL) exit(0);
    novo->id = i;
    novo->next = hc->next;
    hc->next = novo;

    return;
}

void libertaC(no*hc)
{
    no *aux, *newhead = NULL;  /* auxiliar pointers to travel through the list */

    for(aux = hc; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux);
    }

    return;
}

void marcaC(long* routersc, no*hc)
{
    no*aux = NULL;
    aux = hc->next;

    while(aux!= NULL)
    {
        routersc[aux->id] = -1;
        aux = aux->next;
    }

    return;
}

void Contador(long* subredec, long* routersc, long N)
{
    long i = 0, j = 0;

    for (i=0;i<N;i++){
        j = (routersc[i])-1;
        if (j>=0) subredec[j]++;
    }

    return;
}

void Tarjan(long u, long n, long* counterc, long* low, long* d, no* headc, no* matriz, long* visitado)
{
    long v = 0, k = 0, c = 0;
    no*aux = NULL;

    d[u] = *visitado;
    low[u] = *visitado;
    (*visitado)++;

    aux = matriz[u].next;

    while(aux != NULL)
    {
        v = aux->id-1;
        if (d[v] == 0)
        {
            c++;
            Tarjan(v, u, counterc, low, d, headc, matriz, visitado);
            if(low[v] < low[u])low[u] = low[v];
            if (low[v] >= d[u] && d[u] != 1 && k == 0)
            {
                NovoC(u, headc);
                /*printf("c %li\n", u+1);*/
                (*counterc)++;
                k = 1;
            }
            else if (d[u] == 1 && c > 1 && k == 0)
            {
                NovoC(u, headc);
                /*printf("c %li\n", u+1);*/
                (*counterc)++;
                k = 1;
            }
        }
        else if (v != n)
        {
            if(d[v] < low[u])low[u] = d[v];
        }

        aux = aux->next;
    }
    return;
}
