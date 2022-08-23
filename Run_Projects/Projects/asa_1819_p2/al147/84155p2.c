#include <stdio.h>
#include <stdlib.h>

#define oo 1000000000

typedef struct _vertice {
    long h;
    long e;
    long c;
}vertice;

typedef struct _no {
    long id;
    long c;
    long f;
    struct _no *next;
    struct _no *rev;
}no;

typedef struct _inteiro {
    long id;
    struct _inteiro *next;
}inteiro;

typedef struct _dubint {
    long o;
    long d;
}dubint;

typedef struct _dubintlist {
    dubint l;
    struct _dubintlist *next;
}dubintlist;


void CriaLista(long , no* , long , long , vertice*);
void libertaListaNo(no *, long);
void libertaListaL(inteiro *);
void OrdenaListaLig(dubint * , long , long );
void libertaListaLig(dubintlist * );
void printListaLig(dubint* , long );
void OrdenaListaE(long * , long ,long );
void printListaE(long* , long );

int main()
{
    long f = 0, e = 0, i = 0, j = 0, p = 0, t = 0, min = 0, max_flow = 0, k = 0, gap = 0;
    vertice *vertices = NULL;
    long * heights = NULL;
    long *list_e = NULL;
    no *listaLig = NULL;
    no *auxLig = NULL;
    no *nova = NULL;
    no *nova2 = NULL;
    inteiro*listaNos = NULL;
    inteiro*novo = NULL;
    inteiro*auxNo = NULL;
    inteiro*auxNo2 = NULL;
    dubintlist*or_dest = NULL;
    dubintlist*novo_od = NULL;
    dubintlist*aux_od = NULL;
    dubint*list = NULL;
    inteiro* est = NULL;
    inteiro*novo_e = NULL;
    inteiro*aux_e = NULL;

    if(scanf("%li", &f) == 0) exit(0);
    if(scanf("%li", &e) == 0) exit(0);
    if(scanf("%li", &t) == 0) exit(0);

    j = f+e+e+2;

    heights=(long*)calloc(j+1, sizeof(long));

    vertices=(vertice*)calloc(j, sizeof(vertice));
    if(vertices==NULL) exit(0);

    for(i=2;i<=(f+1);i++)
    {
       if(scanf("%li", &p) == 0) exit(0);
       vertices[i].c = p;
    }

    for(i=f+2;i<(j-e);i++)
    {
       if(scanf("%li", &p) == 0) exit(0);
       vertices[i].c = p;
    }

    vertices[0].c = oo;
    vertices[1].c = oo;
    vertices[1].h = j;

    /******************************************************************************
     * Alocacao da memoria necessaria para a matriz de adjacencias
     * Criacao da matriz
     *****************************************************************************/
    listaLig = (no*)calloc(j, sizeof(no));

    if(listaLig==NULL) exit(0);

    CriaLista(t, listaLig, f, e, vertices);

    for(i=2;i<=(f+1);i++)
    {
        nova = (no*)malloc(sizeof(no));
        if(nova==NULL) exit(0);

        nova->id = 0;
        nova->f = 0;
        nova->c = vertices[i].c;
        nova->next = listaLig[i].next;
        listaLig[i].next = nova;

        nova2 = (no*)malloc(sizeof(no));
        if(nova2==NULL) exit(0);

        nova2->id = i;
        nova2->f = 0;
        nova2->c = 0;
        nova2->next = listaLig[0].next;
        listaLig[0].next = nova2;

        nova->rev = nova2;
        nova2->rev = nova;

    }

    for(i=f+2;i<(j-e);i++)
    {
        nova = (no*)malloc(sizeof(no));
        if(nova==NULL) exit(0);

        nova->id = i;
        nova->f = 0;
        nova->c = vertices[i].c;
        nova->next = listaLig[i+e].next;
        listaLig[i+e].next = nova;

        nova2 = (no*)malloc(sizeof(no));
        if(nova2==NULL) exit(0);

        nova2->id = i+e;
        nova2->f = 0;
        nova2->c = 0;
        nova2->next = listaLig[i].next;
        listaLig[i].next = nova2;

        nova->rev = nova2;
        nova2->rev = nova;
    }

    listaNos = (inteiro*)malloc(sizeof(inteiro));
    if(listaNos==NULL) exit(0);
    listaNos->next = NULL;

    for(i=2;i<j;i++)
    {
        novo = (inteiro*)malloc(sizeof(inteiro));
        if(novo==NULL) exit(0);
        novo->id = i;
        novo->next = listaNos->next;
        listaNos->next = novo;
    }

    auxLig = listaLig[1].next;

    while(auxLig != NULL)
    {
        auxLig->f = auxLig->c;
        auxLig->rev->f = -auxLig->c;
        vertices[auxLig->id].e = auxLig->c;
        vertices[1].e -=auxLig->c;
        auxLig = auxLig->next;
    }

    auxNo = listaNos;

    while(auxNo->next != NULL)
    {
        i = auxNo->next->id;
        while(vertices[i].e != 0)
        {
            auxLig = listaLig[i].next;

            while(auxLig != NULL)
            {
                k = auxLig->id;
                if(vertices[i].h == (vertices[k].h)+1)
                {
                    if(auxLig->c > 0)
                    {
                        min = (auxLig->c - auxLig->f);
                        if(min>vertices[i].e)min = vertices[i].e;
                        vertices[k].e +=min;
                        vertices[i].e -= min;
                        auxLig->f += min;
                        auxLig->rev->f -=min ;

                    }
                    else
                    {
                        min = -auxLig->f;
                        if(min>vertices[i].e)min = vertices[i].e;
                        vertices[i].e -= min;
                        vertices[k].e +=min;
                        auxLig->f += min;
                        auxLig->rev->f -=min;
                    }
                }
                auxLig = auxLig->next;
            }


            if(vertices[i].e != 0)
            {
                vertices[i].h++;
                if(auxNo!=listaNos)
                {
                    auxNo2 = auxNo->next;
                    auxNo->next = auxNo->next->next;
                    auxNo2->next = listaNos->next;
                    listaNos->next = auxNo2;
                    auxNo = listaNos;
                }
            }
        }
        auxNo = auxNo->next;
    }

    max_flow = -vertices[1].e;
    printf("%li\n",max_flow);

    libertaListaL(listaNos);
    free(listaNos);

    listaNos = (inteiro*)malloc(sizeof(inteiro));
    if(listaNos==NULL) exit(0);
    listaNos->next = NULL;

    for(i=0;i<j;i++)
    {
        if((vertices[i].h)<=j)heights[vertices[i].h]++;
    }

    for(i=j-1;i>=0;i--)
    {
        if(heights[i] == 0)
        {
            gap = i;
            break;
        }
    }

    for(i=0;i<j;i++)
    {
        if(vertices[i].h>gap)
        {
            novo = (inteiro*)malloc(sizeof(inteiro));
            if(novo==NULL) exit(0);
            novo->id = i;
            novo->next = listaNos->next;
            listaNos->next = novo;
        }
    }

    or_dest = (dubintlist*)malloc(sizeof(dubintlist));
    if(or_dest==NULL) exit(0);
    or_dest->next = NULL;

    est = (inteiro*)malloc(sizeof(inteiro));
    if(est==NULL) exit(0);
    est->next = NULL;

    auxNo = listaNos;

    k = 0;
    p = 0;

    while(auxNo->next != NULL)
    {
        i = auxNo->next->id;
        auxLig = listaLig[i].next;

        while(auxLig != NULL)
        {
            if(vertices[auxLig->id].h<gap && auxLig->id !=0)
            {
                if(i>=(j-e) && i == auxLig->id+e)
                {
                    novo_e = (inteiro*)malloc(sizeof(inteiro));
                    if(novo_e==NULL) exit(0);
                    novo_e->id = auxLig->id;
                    novo_e->next = est->next;
                    est->next = novo_e;
                    p++;
                }
                else if(i<(j-e) || vertices[auxLig->id+e].h<gap)
                {
                    novo_od = (dubintlist*)malloc(sizeof(dubintlist));
                    if(novo_od==NULL) exit(0);
                    if(i<j-e)
                    {
                        novo_od->l.d= i;
                    }
                    else novo_od->l.d= i-e;
                    if(auxLig->id<j-e)
                    {
                        novo_od->l.o = auxLig->id;
                    }
                    else novo_od->l.o = auxLig->id-e;
                    novo_od->next = or_dest->next;
                    or_dest->next = novo_od;
                    k++;
                }

            }
            auxLig = auxLig->next;
        }
        auxNo = auxNo->next;
    }


    list_e = (long*)calloc(p,sizeof(long));
    if(list_e==NULL) exit(0);

    gap = p;
    p=0;

    aux_e = est->next;


    while(aux_e != NULL)
    {
        list_e[p]=aux_e->id;
        p++;
        aux_e = aux_e->next;
    }
    if(gap != 0)
    {
        OrdenaListaE(list_e, 0, p-1);

        printListaE(list_e, p);
    }
    else printf("\n");

    list = (dubint*)calloc(k,sizeof(dubint));
    if(list==NULL) exit(0);

    p=0;

    aux_od = or_dest->next;


    while(aux_od != NULL)
    {
        list[p]=aux_od->l;
        p++;
        aux_od = aux_od->next;
    }

    if(k != 0)
    {
        OrdenaListaLig(list, 0, p-1);

        printListaLig(list, p);
    }

    libertaListaL(est);
    libertaListaLig(or_dest);
    libertaListaL(listaNos);
    libertaListaNo(listaLig, j);
    free(est);
    free(list_e);
    free(listaLig);
    free(listaNos);
    free(or_dest);
    free(list);
    free(vertices);
    free(heights);

    return 0;
}

 void CriaLista(long t, no*lista, long f, long e, vertice*vertices){

    long i = 0, cap = 0, u = 0, v = 0;
    no*novou = NULL;
    no*novov = NULL;

    for (i=0;(i<t);i++){
        if(scanf("%li", &u) == 0) exit(0);
        if(scanf("%li", &v) == 0) exit(0);
        if(scanf("%li", &cap) == 0) exit(0);


        novou = (no*) malloc(sizeof(no));
        if(novou == NULL)
        {
            printf ("Erro na alocacao de memoria \n");
            exit (0);
        }

        novov = (no*) malloc(sizeof(no));
        if(novov == NULL)
        {
            printf ("Erro na alocacao de memoria \n");
            exit (0);
        }

        if(u<f+2)
        {
            novou->id = v;
            novou->f = 0;
            novou->c = 0;
            novou->next = lista[u].next;
            lista[u].next = novou;

            novov->id = u;
            novov->f = 0;
            novov->c = cap;
            novov->next = lista[v].next;
            lista[v].next = novov;
            novov->rev = novou;
            novou->rev = novov;
        }
        else
        {
            novou->id = v;
            novou->f = 0;
            novou->c = 0;
            novou->next = lista[u+e].next;
            lista[u+e].next = novou;

            novov->id = u+e;
            novov->f = 0;
            novov->c = cap;
            vertices[u+e].c = cap;
            novov->next = lista[v].next;
            lista[v].next = novov;
            novov->rev = novou;
            novou->rev = novov;
        }

    }

    return;
 }

 void libertaListaNo(no *lista, long j) {

    long i = 0;
    no *aux, *newhead = NULL;

    for(i=0;i<j;i++){
      for(aux = lista[i].next; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux);
      }
    }
    return;
}

 void libertaListaL(inteiro *lista) {

    inteiro *aux, *newhead = NULL;

    for(aux = lista->next; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux);
    }
    return;
}

void OrdenaListaLig(dubint *lista, long l, long r)
{
    dubint x, y;
    long i, j;

    i = l;
    j = r;
    x = lista[(l + r) / 2];


    while(i <= j) {
        while((lista[i].o < x.o || (lista[i].o == x.o && lista[i].d < x.d)) && i < r) {
            i++;
        }
        while((lista[j].o > x.o || (lista[j].o == x.o && lista[j].d > x.d)) && j > l) {
            j--;
        }
        if(i <= j) {
            y = lista[i];
            lista[i] = lista[j];
            lista[j] = y;
            i++;
            j--;
        }
    }

    if(j > l) {
        OrdenaListaLig(lista, l, j);
    }
    if(i < r) {
        OrdenaListaLig(lista, i, r);
    }

    return;
}

void printListaLig(dubint* lista, long k)
{
    long i = 0;

    for(i=0;i<k;i++)
    {
        printf("%li %li\n", lista[i].o, lista[i].d);
    }

    return;
}

 void libertaListaLig(dubintlist *lista) {

    dubintlist *aux, *newhead = NULL;

    for(aux = lista->next; aux != NULL; aux = newhead) {
        newhead = aux->next;
        free(aux);
    }
    return;
}

void OrdenaListaE(long *lista_e, long l, long r)
{
    long i, j, x, y;

    i = l;
    j = r;
    x = lista_e[(l + r) / 2];

    while(i <= j) {
        while(lista_e[i] < x && i < r) {
            i++;
        }
        while(lista_e[j] > x && j > l) {
            j--;
        }
        if(i <= j) {
            y = lista_e[i];
            lista_e[i] = lista_e[j];
            lista_e[j] = y;
            i++;
            j--;
        }
    }

    if(j > l) {
        OrdenaListaE(lista_e, l, j);
    }
    if(i < r) {
        OrdenaListaE(lista_e, i, r);
    }

    return;
}

void printListaE(long* lista_e, long k)
{
    long i = 0;

    for(i=0;i<k-1;i++)
    {
        printf("%li ", lista_e[i]);
    }
    printf("%li\n", lista_e[k-1]);

    return;
}
