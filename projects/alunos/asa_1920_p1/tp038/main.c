#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int index;
    int low;
    int in_stack;
    int id;
    int scc_id;
    int *adj;
    int grade;
    int total_childs;
    int visited;
} node;

typedef struct Scc{
    int node_id;
    int max;
    int scc_counter;
    int visited;
} scc;

typedef struct SccAdj{
    int scc_id;
    int scc_adj_counter;
} sccadj;

typedef struct Stack{
    int top;
    int *items;
} stack;

node *nodes;
stack buf;
scc **sccs;
sccadj **scc_adj;
int total_students = 0;
int total_relationships = 0;
int sccs_count = 0;
int curr_index = 0;

#define nodes(X) (nodes[(X)])
#define n_index(X) (nodes((X)).index)
#define n_low(X) (nodes((X)).low)
#define n_instack(X) (nodes((X)).in_stack)
#define n_visited(X) (nodes((X)).visited)
#define n_adj(X) (nodes((X)).adj)
#define n_totalchilds(X) (nodes((X)).total_childs)
#define n_id(X) (nodes((X)).id)
#define n_sccid(X) (nodes((X)).scc_id)
#define n_grade(X) (nodes((X)).grade)

void init_vars(){
    buf.items = can_fail_malloc(sizeof(int) * total_students);
    buf.top = -1;
    sccs = can_fail_malloc(sizeof(scc*) * total_students);
}

void process_input(){
    char c;
    scanf("%d%c%d", &total_students, &c, &total_relationships);

    nodes = can_fail_malloc(sizeof(node) * total_students);

    int i = 0;
    for(; i < total_students; i++){
        scanf("%d", &n_grade(i));
        n_adj(i) = NULL;
        n_id(i) = i;
        n_totalchilds(i) = 0;
        n_index(i) = -1;
        n_low(i) = -1;
        n_visited(i) = -1;
        n_instack(i) = 0;
        n_sccid(i) = -1;
    }

    int j = 0, u = 0, v = 0;
    for (; j < total_relationships; j++){
        scanf("%d %d", &u, &v);
        u--;
        v--;
        if(!n_adj(u)) {
            n_adj(u) = can_fail_malloc(sizeof(int));
        } else {
            int *newAdj = can_fail_realloc(n_adj(u), sizeof(int) * (n_totalchilds(u) + 1));
            n_adj(u) = newAdj;
        }
        n_adj(u)[n_totalchilds(u)] = v;
        n_totalchilds(u)++;
    }
}

void stack_push(int v) {
    buf.top++;
    buf.items[buf.top] = v;
}

int stack_pop() {
    return buf.top < 0 ? -1 : buf.items[buf.top--];
}

int min(int a, int b) {
    return a < b ? a : b;
}

void tarjan_visit(int v) {
    int i, c, n;
    n_index(v) = curr_index;
    n_low(v) = curr_index;

    ++curr_index;
    stack_push(v);

    n_instack(v) = 1;
    for (i = 0, c = n_totalchilds(v); i < c; i++){
        n = n_adj(v)[i];
        if (n_index(n) == -1 || n_instack(n)) {
            if (n_index(n) == -1)
                tarjan_visit(n);
            n_low(v) = min(n_low(v), n_low(n));
        }
    }

    if (n_index(v) == n_low(v)) {
        while ((n = stack_pop()) != -1) {
            n_instack(n) = 0;
            if(!sccs[sccs_count]) {
                sccs[sccs_count] = can_fail_malloc(sizeof(scc) * 2);
                sccs[sccs_count]->scc_counter = 0;
                sccs[sccs_count]->visited = -1;
            } else {
                scc *new_scc = can_fail_realloc(sccs[sccs_count], sizeof(scc) * (sccs[sccs_count]->scc_counter + 2));
                sccs[sccs_count] = new_scc;
            }

            sccs[sccs_count][sccs[sccs_count]->scc_counter].node_id = n;

            if(sccs[sccs_count]->scc_counter == 0){
                sccs[sccs_count]->max = n_grade(n);
            } else{
                if (n_grade(n) > sccs[sccs_count]->max)
                    sccs[sccs_count]->max = n_grade(n);
            }

            n_sccid(n) = sccs_count;

            sccs[sccs_count]->scc_counter++;
            if (n == v) {
                sccs_count++;
                break;
            }
        }
    }
}

void find_scc_adj(){
    int j, z, a;
    scc_adj = can_fail_malloc(sizeof(sccadj*) * sccs_count);

    for(j = 0; j < sccs_count; j++) {
        for (a = 0; a < sccs[j]->scc_counter; a++) {
            int c = sccs[j][a].node_id;
            for (z = 0; z < n_totalchilds(c); z++)
                if (n_sccid(n_adj(c)[z]) != j) {
                    if (!scc_adj[j]) {
                        scc_adj[j] = can_fail_malloc(sizeof(sccadj));
                        scc_adj[j]->scc_adj_counter = 0;
                    } else {
                        sccadj *new_scc_adj = can_fail_realloc(scc_adj[j],sizeof(sccadj) * (scc_adj[j]->scc_adj_counter + 1));
                        scc_adj[j] = new_scc_adj;
                    }
                    scc_adj[j][scc_adj[j]->scc_adj_counter].scc_id = n_sccid(n_adj(c)[z]);
                    scc_adj[j]->scc_adj_counter++;
                }
        }
    }
}

void dfs_visit(int u, int pos){
    sccs[u]->visited = 1;

    if(scc_adj[u]) {
        int v;
        for (v = 0; v < scc_adj[u]->scc_adj_counter; v++) {
            if (sccs[v]->visited == -1) {
                dfs_visit(v, pos);
            }
        }
    }
    if (u != pos && sccs[scc_adj[pos][u].scc_id]->max > sccs[pos]->max) {
        sccs[pos]->max = sccs[scc_adj[pos][u].scc_id]->max;
    }
    sccs[u]->visited = -1;
}

void dfs_scc(){
    int i;
    for(i = 0; i < sccs_count; i++){
        if(sccs[i]->visited == -1 ) {
            dfs_visit(i, i);
        }
    }
}

void change_to_max(){
    int i;
    for(i = 0; i < total_students; i++){
        n_grade(i) = sccs[n_sccid(i)]->max;
        printf("%d\n", n_grade(i));
    }
}

int main(void) {
    process_input();
    init_vars();

    int i;
    for(i = 0; i < total_students; i++)
        if(n_index(i) == -1)
            tarjan_visit(i);

    find_scc_adj();
    dfs_scc();
    change_to_max();

    for(i = 0; i < total_students; i++)
        free(n_adj(i));

    for(i = 0; i < sccs_count; i++){
        free(sccs[i]);
        free(scc_adj[i]);
    }

    free(nodes);
    free(sccs);
    free(scc_adj);
    free(buf.items);

    return 0;
}