
/*
Projeto 2 de ASA segundo semestre primeiro ano
Grupo 76 Alameda
Guilherme Areias    89451
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Global/class scope variables */
#define initial 1
#define waiting 2
#define visited 3
#define starting 4
#define destination 5
#define occupied 6

/* node usada para saber o caminho que liga o cidadao ao supermercado */
typedef struct {
	int x; /* rua */
	int y; /* avenida */
    int prev; /* node anterior */
} Node;

Node* previous; /* lista de nodes */

int M = 1; /* numero de avenidas*/
int N = 1; /* numero de ruas*/
int S = 1; /* numero de supermercados*/
int C = 1; /* numero de cidadaos*/

/* Variable used to track the number of steps taken */
int move_count = 0;
int front = -1;
int rear = -1;
int nodes_left_in_layer = 1;
int nodes_in_next_layer = 0;
int p_aux = 0;

/* Variable used to track whether the end ever gets reached during the BFS */
int reached_end = 0;

/* North, south, east, west direction vectores */
static int dr[4] = {-1, 1, 0, 0};
static int dc[4] = {0, 0, 1, -1};
/* --- fim--- */

void pg(int grid[M+1][N+1]);
void inicialize_sc(int grid[M+1][N+1], int supers[S][3], int cidadaos[C][2], int cid_sup[C][3]);
void inicialize_bfs(int state[M+1][N+1], int rq[M*N], int cq[M*N]);
void enqueue(int rq[M*N], int cq[M*N], int r, int c);
int dequeue(int queue[M*N]);
int queue_empty();
void explore_neighbours(int r_aux, int c_aux, int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]);
int bfs(int sr, int sc, int fr, int fc, int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]);
void solve(int supers[S+1][3], int cidadaos[C+1][2], int cid_sup[C+1][3], int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]);
void distances(int supers[S+1][3], int cidadaos[C+1][2], int cid_sup[C+1][3]);
void distances_aux (int i, int supers[S+1][3], int cidadaos[C][2], int cid_sup[C+1][3]);
void distances_clean (int i, int e, int cid_sup[C+1][3]);

int main(){

    int k = 0, i = 0;
    /* s_aux : string auxiliar que guarda os valores N ou M antes de passarem a inteiros */
    char y, input[100], s_aux[100];

    /* 1) scan dos parametros M e N */
    while ((y = getchar()) != '\n' && y != EOF){
        input[k] = y;
        k++;
    }
    input[k] = '\0';
    k = 0;
    while (input[i] != ' '){
        s_aux[i] = input[i];
        i++;
    }
    s_aux[i] = '\0';
    M = atoi(s_aux);
    memset(s_aux, '\0', sizeof(s_aux));
    i++;
    while (input[i] != '\0'){
        s_aux[k] = input[i];
        i++;
        k++;
    }
    s_aux[k] = '\0';
    N = atoi(s_aux);
    memset(s_aux, '\0', sizeof(s_aux));

    /* 2) scan dos parametros S e C */
    if (scanf("%d %d", &S, &C)){
        i++;
    }

    int grid[M+1][N+1]; /* input character matrix of size M*N */
    /* lista com os coordenadas de cada supermercados */
    int supers[S+1][3];
    /* lista com os coordenadas de cada cidadaos */
    int cidadaos[C+1][2];
    /* lista com os pares de cidadao supermercado em que a distancia e mais curta */
    int cid_sup[C+1][3];
    int rq[M*N]; /* empty row queue */
    int cq[M*N]; /* empty column queue */
    /* matrix of false values used to track whether the node at position (i, j) has been visited */
    int state[M+1][N+1];

    inicialize_sc(grid, supers, cidadaos, cid_sup);

    /* 3) scan dos supermercados */
    for (i = 0; i < S; i++){
        if (scanf("%d %d", &supers[i][0], &supers[i][1])){
            supers[i][2] = 100;
            grid[supers[i][0]][supers[i][1]] = occupied;
        }
    }

    /* 4) scan dos cidadaos */
    for (i = 0; i < C; i++){
        if (scanf("%d %d", &cidadaos[i][0], &cidadaos[i][1])){
            cid_sup[i][0] = -1;
            cid_sup[i][1] = -1;
            cid_sup[i][2] = 0;
            grid[cidadaos[i][0]][cidadaos[i][1]] = occupied;
        }
    }

    /* 5) resolve */
    distances(supers, cidadaos, cid_sup);
    solve(supers, cidadaos, cid_sup, grid, rq, cq, state);

    return 0;
}

/* inicializa as lista dos supermercados e cidadaos */
void inicialize_sc(int grid[M+1][N+1], int supers[S][3], int cidadaos[C][2], int cid_sup[C][3]){
    int i, e = 1;
    /* inicializa a matriz grid e visited */
    for (i = 0; i <= M+1; i++){
        for (e = 0; e <= N+1; e++){
            grid[i][e] = 0;
        }
    }
    /* inicializa a lista dos supermercados*/
    for (i = 0; i < S; i++){
        supers[i][0] = 0;
        supers[i][1] = 0;
        supers[i][2] = 100;
    }
    /* inicializa a lista dos cidadaos */
    for (i = 0; i < C; i++){
        cidadaos[i][0] = 0;
        cidadaos[i][1] = 0;
    }
}

/* inicializa as variaveis necessarias para a bfs */
void inicialize_bfs(int state[M+1][N+1], int rq[M*N], int cq[M*N]){
    int i, e = 1;
    /* inicializa a matriz visited */
    for (i = 0; i <= M+1; i++){
        for (e = 0; e <= N+1; e++){
            state[i][e] = initial;
        }
    }
    /* inicializa os queues rq e cq */
    for (i = 0; i < M*N; i++){
        rq[i] = 0;
        cq[i] = 0;
    }
}

void pg(int grid[M+1][N+1]){
    int i, e = 0;
    for (i = 1; i <= M; i++){
        for (e = 1; e <= N; e++){
            printf("%d ", grid[i][e]);
        }
        printf("\n");
    }
}

/* add a new position to the queue */
void enqueue(int rq[M*N], int cq[M*N], int r, int c){
    if (front == -1){
        front = 0;
    }
    rear = rear + 1;
    rq[rear] = r;
    cq[rear] = c;
}

/* remove a position from the queue */
int dequeue(int queue[M*N]){
    int aux = 1;
    if (front == -1){
        exit(1);
    }
    p_aux = front;
    aux = queue[front];
    return aux;
}

int queue_empty(){
	if((front == -1) || (front > rear)){
		return 1;
    }
	else{
		return 0;
    }
}

int bfs(int sr, int sc, int fr, int fc, int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]){
    int r_aux, c_aux = 0;
    nodes_left_in_layer = 1;
    nodes_in_next_layer = 0;
    /* adicionar o ponto de origem e o de destion a matrix */
    grid[sr][sc] = starting;
    grid[fr][fc] = destination;

    previous = malloc(sizeof(Node)*M*N);
    
    /* add the start cells to the rq and cq */
    enqueue(rq, cq, sr, sc);
    state[sr][sc] = waiting;

    previous[0].x = sr;
    previous[0].y = sc;
    previous[0].prev = 0;

    while (!queue_empty()){
        /* dequeue */
        r_aux = dequeue(rq);
        c_aux= dequeue(cq);
        state[r_aux][c_aux] = visited;
        front = front + 1;
        /* check if reached destination */
        if (grid[r_aux][c_aux] == destination){
            reached_end = 1;
            break;
        }
        /* add all the valid neighbours to the queue */
        explore_neighbours(r_aux, c_aux, grid, rq, cq, state);
        nodes_left_in_layer--;
        if (nodes_left_in_layer == 0){
            nodes_left_in_layer = nodes_in_next_layer;
            nodes_in_next_layer = 0;
            move_count++;
        }
    }
    
    /* adicionar o supermercado a lista previous */
    while (p_aux != 0){
        r_aux = previous[p_aux].prev;
        p_aux = r_aux;
        grid[previous[p_aux].x][previous[p_aux].y] = occupied;
    }
    free(previous);

    if (reached_end == 1){
        return move_count;
    }
    else{
        return -1;
    }

}

void explore_neighbours(int r_aux, int c_aux, int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]){
    int i, rr, cc = 1;
    for (i = 0; i < 4; i++){
        rr = r_aux + dr[i];
        cc = c_aux + dc[i];
        /* skip out of bounds locations */
        if ((rr > 0) && (cc > 0) && (rr <= M) && (cc <= N)){
            /* skip visited locations or blocked cells */
            if ((grid[rr][cc] != occupied) && (state[rr][cc] == initial)){
                enqueue(rq, cq, rr, cc);
                state[rr][cc] = waiting;
                nodes_in_next_layer++;
                previous[rear].x = rr;
                previous[rear].y = cc;
                previous[rear].prev = p_aux;
            }
        }
    }
}

/* liga o numero maximo de cidadaos aos supermercados */
void solve(int supers[S][3], int cidadaos[C][2], int cid_sup[C][3], int grid[M+1][N+1], int rq[M*N], int cq[M*N], int state[M+1][N+1]){
    /* numero maximo de cidadaos que podem deslocar-se aos supermercados sem se encontrarem */
    int output = 0;
    /* numero de posicoes entre um cidadao e um supermercado */
    int track = 0;
    int sr = 1; /* the row of the starting node */
    int sc = 1; /* the column of the starting node */
    int fr = 2; /* the row of the final node */
    int fc = 2; /* the column of the final node */
    int i, c_aux, s_aux = 0;

    for (i = 0; i < C; i++){
        c_aux = cid_sup[i][0];
        sr = cidadaos[c_aux][0];
        sc = cidadaos[c_aux][1];
        s_aux = cid_sup[i][1];
        fr = supers[s_aux][0];
        fc = supers[s_aux][1];
        inicialize_bfs(state, rq, cq);
        track = bfs(sr, sc, fr, fc, grid, rq, cq, state);
        /* caso o cidadao tem caminho para o supermercado */
        if (track > -1){
            output++;
        }
    }

    printf("%d\n", output);

}

/* calcula a lista com os pares de cidade supermercado em que as distancias sao menores */
/* e ordena a lista cid_dist por ordem de cidades com distancias inferiores */
void distances(int supers[S+1][3], int cidadaos[C+1][2], int cid_sup[C+1][3]){
    int i, e, c1, c2, s1, s2, d, d_aux, s_aux = 0;
    /* calcular distancias */
    for (i = 0; i < C; i++){
        d = 1000;
        c1 = cidadaos[i][0];
        c2 = cidadaos[i][1];
        for (e = 0; e < S; e++){
            s1 = supers[e][0];
            s2 = supers[e][1];
            d_aux = abs(c1-s1) + abs(c2-s2);
            /* se a distancia ao supermercado e superior ao anterior */
            if (d_aux < d){
                /* se a distancia do supermercado ao cidadao for inferior ao cidadao guardado */
                s_aux = supers[e][2];
                if (d_aux < cid_sup[s_aux][2] || cid_sup[s_aux][2] == 0){
                    d = d_aux;
                    cid_sup[i][0] = i;
                    cid_sup[i][1] = e;
                    cid_sup[i][2] = d;
                    supers[e][2] = i;
                    if (s_aux != 100 && s_aux != i){
                        distances_clean(i, e, cid_sup);
                        distances_aux(s_aux, supers, cidadaos, cid_sup);
                    }
                }
            }
        }
    }
}

/* quando uma distancia de um par ja tinha sido calculado, remover os cidadaos associados ao supermercado  */
void distances_clean (int i, int e, int cid_sup[C+1][3]){
    int z = 0;
    for (z = 0; z < C; z++){
        if (cid_sup[z][1] == e && z != i){
            cid_sup[z][1] = -1;
            cid_sup[z][2] = 0;
        }
    }
}

/* quando uma distancia de um par ja tinha sido calculado e e depois alterado */
void distances_aux (int i, int supers[S+1][3], int cidadaos[C+1][2], int cid_sup[C+1][3]){
    int e, s1, s2, d_aux, s_aux = 0;
    int d = 1000;
    int c1 = cidadaos[i][0];
    int c2 = cidadaos[i][1];
    for (e = 0; e < S; e++){
        s1 = supers[e][0];
        s2 = supers[e][1];
        d_aux = abs(c1-s1) + abs(c2-s2);
        /* se a distancia ao supermercado e superior ao anterior */
        if (d_aux < d){
            /* se a distancia do supermercado ao cidadao for inferior ao cidadao guardado */
            s_aux = supers[e][2];
            /* --- CORRIGIR --- */
            if (d_aux < cid_sup[s_aux][2] || cid_sup[s_aux][2] == 0){
                d = d_aux;
                cid_sup[i][0] = i;
                cid_sup[i][1] = e;
                cid_sup[i][2] = d;
                supers[e][2] = i;
            }
        }
    }

}



/* Fim */
