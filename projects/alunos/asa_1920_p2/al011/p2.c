#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Grupo 11
 * Manuel Carvalho-87237
 * Miguel Coelho-89509 */

#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 1
#define SOURCE 2
#define SINK 3
#define SS 4

int M, N, S, C, V, F, MAX;

typedef struct{
    int avenida;
    int rua;
} cruzamento;

typedef struct{
    int visited;
    int fluxo;
    int supermercados;
    int cidadaos;
    int cruzamentos;
    cruzamento * c;
    cruzamento in;
} vertice;

typedef struct{
    cruzamento c;
    int b;
} path;

typedef struct node{
    path * p;
    int cruzamentos;
    struct node * next;
} queueN; typedef queueN* queue;

vertice ** grid;
cruzamento * cidadaos;

void initE(int ui, int uj, int vi, int vj){
    grid[ui][uj].c = can_fail_realloc(grid[ui][uj].c, ((grid[ui][uj].cruzamentos)+1)*sizeof(cruzamento));
    grid[ui][uj].c[grid[ui][uj].cruzamentos].avenida = vi;
    grid[ui][uj].c[grid[ui][uj].cruzamentos].rua = vj;
    grid[ui][uj].cruzamentos++;
}

void initG(){
    int i, j;
    grid = can_fail_malloc(M*sizeof(vertice *));

    for (i = 0; i < M; i++){
        grid[i] = can_fail_malloc(N*sizeof(vertice));

        for (j = 0; j < N; j++){
            grid[i][j].visited = V;
            grid[i][j].fluxo = EMPTY;
            grid[i][j].supermercados = EMPTY;
            grid[i][j].cidadaos = EMPTY;
            grid[i][j].cruzamentos = EMPTY;
            grid[i][j].c = NULL;
            grid[i][j].in.avenida = -1;
            grid[i][j].in.rua = -1;

            if (j < N-1)
                initE(i, j, i, j+1);

            if (i < M-1)
                initE(i, j, i+1, j);

            if (j > 0)
                initE(i, j, i, j-1);

            if (i > 0)
                initE(i, j, i-1, j);
        }
    }
}

void initS(){
    int i, a, r, Sc = S;
    for (i = 0; i < S; i++){
        scanf("%d %d", &a, &r);
        a--;
        r--;
        if (grid[a][r].supermercados > EMPTY)
            Sc--;
        else
            grid[a][r].supermercados++;
    }
    S = Sc;
}

void initC(){
    int i, a, r, Ci = 0, Cc = C;
    cidadaos = can_fail_malloc(C*sizeof(cruzamento));
    for (i = 0; i < C; i++){
        scanf("%d %d", &a, &r);
        a--;
        r--;
        if (grid[a][r].cidadaos > EMPTY)
            cidadaos = can_fail_realloc(cidadaos, (--Cc)*sizeof(cruzamento));
        else{
            grid[a][r].cidadaos++;
            if (grid[a][r].supermercados > EMPTY){
                cidadaos = can_fail_realloc(cidadaos, (--Cc)*sizeof(cruzamento));
                grid[a][r].fluxo = SS;
                F++;
            }
            else{
                cidadaos[Ci].avenida = a;
                cidadaos[Ci].rua = r;
                Ci++;
            }
        }
    }
    C = Ci;
}

void freeC(){
    free(cidadaos);
}

void freeG(){
    int i, j;
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++)
            free(grid[i][j].c);
        free(grid[i]);
    }
    free(grid);
}

queue initQ(int a, int r){
    queue q = can_fail_malloc(sizeof(queueN));
    q->p = can_fail_malloc(sizeof(path));
    q->p[0].c.avenida = a;
    q->p[0].c.rua = r;
    q->p[0].b = grid[a][r].fluxo;
    q->cruzamentos = 1;
    q->next = NULL;
    return q;
}

queue enQ(queue first, queue last, int a, int r, int b){
    int i, cruzamentos;
    cruzamentos = first->cruzamentos + 1;
    queue new = can_fail_malloc(sizeof(queueN));
    new->p = can_fail_malloc(cruzamentos*sizeof(path));
    for (i = 0; i < cruzamentos - 1; i++)
        new->p[i] = first->p[i];
    new->p[cruzamentos - 1].c.avenida = a;
    new->p[cruzamentos - 1].c.rua = r;
    new->p[cruzamentos - 1].b = b;
    new->cruzamentos = cruzamentos;
    new->next = NULL;
    last->next = new;
    return new;
}

queue deQ(queue q){
    queue first = q->next;
    free(q->p);
    free(q);
    return first;
}

void freeQ(queue q){
    queue first = q;
    while (first != NULL)
        first = deQ(first);
}

queue bfs(int a, int r){

    int i, ai, ri, bi, aq, rq, bq, cq;
    queue first, last;

    first = initQ(a, r);
    last = first;
    
    V++;

    while (first != NULL){

        cq = first->cruzamentos - 1;
        aq = first->p[cq].c.avenida;
        rq = first->p[cq].c.rua;
        bq = first->p[cq].b;

        if (grid[aq][rq].supermercados > EMPTY && grid[aq][rq].fluxo == EMPTY)
            break;

        if (grid[aq][rq].fluxo == EMPTY){

            for (i = 0; i < grid[aq][rq].cruzamentos; i++){

                ai = grid[aq][rq].c[i].avenida;
                ri = grid[aq][rq].c[i].rua;
                bi = grid[ai][ri].fluxo;
                if (cq > 0){
                    if (ai == first->p[cq-1].c.avenida && ri == first->p[cq-1].c.rua)
                        continue;
                }

                if (grid[ai][ri].visited != V && bi != SOURCE){
                    if (bi == EMPTY)
                        grid[ai][ri].visited = V;
                    if (grid[ai][ri].fluxo < SS)
                        last = enQ(first, last, ai, ri, bi);
                }
            }
        }
        else if (bq > EMPTY && grid[aq][rq].in.avenida != -1){

            ai = grid[aq][rq].in.avenida;
            ri = grid[aq][rq].in.rua;

            if (grid[ai][ri].visited != V){
                grid[ai][ri].visited = V;
                if (grid[ai][ri].fluxo < SS)
                    last = enQ(first, last, ai, ri, EMPTY);
            }
        }
        else if (bq == EMPTY){

            for (i = 0; i < grid[aq][rq].cruzamentos; i++){

                ai = grid[aq][rq].c[i].avenida;
                ri = grid[aq][rq].c[i].rua;
                bi = grid[ai][ri].fluxo;
                if (cq > 0){
                    if (ai == first->p[cq-1].c.avenida && ri == first->p[cq-1].c.rua)
                        continue;
                }
                
                if (grid[ai][ri].visited != V && !(bi == SOURCE && !(grid[aq][rq].in.avenida == ai && grid[aq][rq].in.rua == ri))){
                    if (bi == EMPTY)
                        grid[ai][ri].visited = V;
                    if (grid[ai][ri].fluxo < SS){
                        if (grid[aq][rq].in.avenida == ai && grid[aq][rq].in.rua == ri)
                            last = enQ(first, last, ai, ri, EMPTY);
                        else
                            last = enQ(first, last, ai, ri, bi);
                    }
                }
            }
        }

        first = deQ(first);

    }

    return first;
}

void solve(){

    int i, j, ai, ri, bi, backtrack;
    queue res;

    for (i = 0; i < C; i++){
        
        res = bfs(cidadaos[i].avenida, cidadaos[i].rua);

        if (res != NULL){

            backtrack = EMPTY;

            for (j = res->cruzamentos - 1; j >= 0; j--){

                ai = res->p[j].c.avenida;
                ri = res->p[j].c.rua;
                bi = res->p[j].b;

                if (grid[ai][ri].fluxo > EMPTY && backtrack == EMPTY){
                    backtrack = FULL;
                    if (grid[ai][ri].fluxo == SOURCE){
                        grid[ai][ri].in.avenida = -1;
                        grid[ai][ri].in.rua = -1;
                    }
                    continue;
                }
                
                if (bi == EMPTY && backtrack == FULL){
                    grid[ai][ri].fluxo = EMPTY;
                    grid[ai][ri].in.avenida = -1;
                    grid[ai][ri].in.rua = -1;
                    continue;
                }

                if (bi > EMPTY)
                    backtrack = EMPTY;

                if (j == 0){
                    grid[ai][ri].in.avenida = -1;
                    grid[ai][ri].in.rua = -1;
                    if (j == res->cruzamentos - 1)
                        grid[ai][ri].fluxo = SS;
                    else
                        grid[ai][ri].fluxo = SOURCE;
                }

                else if (j > 0){
                    grid[ai][ri].in.avenida = res->p[j-1].c.avenida;
                    grid[ai][ri].in.rua = res->p[j-1].c.rua;
                    if (j == res->cruzamentos - 1)
                        grid[ai][ri].fluxo = SINK;
                    else
                        grid[ai][ri].fluxo = FULL;
                }

            }

            freeQ(res);

            F++;
        }

        if (F == MAX)
            return;

    }
}
 
int main(){
    scanf("%d %d", &M, &N);
    scanf("%d %d", &S, &C);

    V = EMPTY;
    F = EMPTY;
    if (C <= S)
        MAX = C;
    else
        MAX = S;
 
    initG();
    initS();
    initC();

    solve();
    freeC();
    freeG();
    
    printf("%d\n", F);

    return 0;
}