#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

int M, N, S, C;

typedef struct node {
    int m;
    int n;
    int c;
    int f;
    int cf;
    int df;
    struct node *next;
} *link; 

link insertEnd(link head, int m, int n, int c, int f) {
    link t;
    link new = (link)malloc(sizeof(struct node));
    new->m = m;
    new->n = n;
    new->c = c;
    new->f = f;
    new->cf = new->c - new->f;
    new->next = NULL;
    if (head == NULL) return new;
    for (t = head; t->next != NULL; t = t->next);
    t->next = new;
    return head;
}

void print(link head) {
    link t;
    for (t = head; t != NULL; t=t->next) {
        printf("    %d %d\n", t->m, t->n);
    }
}

link s = NULL, t = NULL;
int hs, ht = 0;
int es = 0, et = 0;

void Relabel(link u, int h[M][N], link edges[M][N]) {
    
    int min_h = INT_MAX;
    link i;
    for (i = edges[u->m-1][u->n-1]; i != NULL; i=i->next) {
        if (i->m == 0 && i->n == 0) {
            if (-i->f > 0 && hs < min_h)
                min_h = hs;
        } else if (i->m == M+1 && i->n == N+1){
            if (1 - i->f > 0 && ht < min_h)
                min_h = ht;
        } else {
            if (i->c - i->f > 0 && h[i->m-1][i->n-1] < min_h){
                min_h = h[i->m-1][i->n-1];
                
            }

                
        }
    }

    h[u->m-1][u->n-1] = 1 + min_h;
    
}

void Push(link u, link v, int e[M][N], link edges[M][N]) {
    link x;
    if (v->m == 0 && v->n == 0) {
        v->df = MIN(e[u->m-1][u->n-1], v->c - v->f);
        v->f += v->df;
        for (x = s; x != NULL; x=x->next)
            if (x->m == u->m && x->n == u->n){
                x->f = -v->f;
                break;
            }
        e[u->m-1][u->n-1] -= v->df;
        es += v->df;
    } else if (v->m == M+1 && v->n == N+1) {
        v->df = MIN(e[u->m-1][u->n-1], v->c - v->f);
        v->f += v->df;
        for (x = t; x != NULL; x=x->next)
            if (x->m == u->m && x->n == u->n){
                x->f = -v->f;
                break;
            }
        e[u->m-1][u->n-1] -= v->df;
        et += v->df;
    } else {
        v->df = MIN(e[u->m-1][u->n-1], v->c - v->f);
        v->f += v->df;
        for (t = edges[v->m-1][v->n-1]; t != NULL; t=t->next)
            if (t->m == u->m && t->n == u->n){
                t->f = -v->f;
                break;
            }
        e[u->m-1][u->n-1] -= v->df;
        e[v->m-1][v->n-1] += v->df;
    }
      
    
}

void Initialize_Preflow(int e[M][N], int h[M][N], link edges[M][N]) {
    
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++){

            h[j][i] = 0;
            e[j][i] = 0;

            if (j == 0) {
                edges[j][i] = insertEnd(edges[j][i], j+2, i+1, 1, 0);
                if (i == 0) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                }   else if (i == N-1) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                } else {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                }
            } else if (j == M-1) {
                edges[j][i] = insertEnd(edges[j][i], j, i+1, 1, 0);
                if (i == 0) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                }   else if (i == N-1) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                } else {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                }
            } else {
                edges[j][i] = insertEnd(edges[j][i], j+2, i+1, 1, 0);
                edges[j][i] = insertEnd(edges[j][i], j, i+1, 1, 0);
                if (i == 0) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                }   else if (i == N-1) {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                } else {
                    edges[j][i] = insertEnd(edges[j][i], j+1, i+2, 1, 0);
                    edges[j][i] = insertEnd(edges[j][i], j+1, i, 1, 0);
                }
            }

        }
    }

    hs = M*N+2;

    for (i = 0; i < S; i++) {
        int m, n;
        scanf("%d %d", &m, &n);
        edges[m-1][n-1] = insertEnd(edges[m-1][n-1], M+1, N+1, 1, 0);
        t = insertEnd(t, m, n, 0, 0);
    }

    for (i = 0; i < C; i++) {
        int m, n;
        scanf("%d %d", &m, &n);
        s = insertEnd(s, m, n, 1, 1);
        edges[m-1][n-1] = insertEnd(edges[m-1][n-1], 0, 0, 0, -1);
        e[m-1][n-1] = 1;
        es -= 1;
    }

}

void Discharge(link u, int e[M][N], int h[M][N], link edges[M][N], link current[M][N]) {
    link v;
    
    while (e[u->m-1][u->n-1] > 0) {
        
        
        v = current[u->m-1][u->n-1];
        
        if (v == NULL) {
            Relabel(u, h, edges);
            current[u->m-1][u->n-1] = edges[u->m-1][u->n-1];
        } else if (v->m == 0 && v->n == 0) {
            if (v->c - v->f > 0 && h[u->m-1][u->n-1] == hs + 1) {  
                Push(u, v, e, edges);
            } else {
                current[u->m-1][u->n-1] = current[u->m-1][u->n-1]->next;
            }
            
        } else if (v->m == M+1 && v->n == N+1) {

            if (v->c - v->f > 0 && h[u->m-1][u->n-1] == ht + 1) {  
                Push(u, v, e, edges);
            } else {
                current[u->m-1][u->n-1] = current[u->m-1][u->n-1]->next;
            }
            
        } else {
            
            if (v->c - v->f > 0 && h[u->m-1][u->n-1] == h[v->m-1][v->n-1] + 1) {
                Push(u, v, e, edges);
            } else {
                current[u->m-1][u->n-1] = current[u->m-1][u->n-1]->next;
            
            }
            
        }

    }
}

int Relabel_To_Front(int e[M][N], int h[M][N], link edges[M][N], link current[M][N]) {

    Initialize_Preflow(e, h, edges);
    
    link L = NULL;
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            L = insertEnd(L, j+1, i+1, 0, 0);
        }
    }

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            current[j][i] = edges[j][i];
         
    link u = L;
    link prev = NULL;
    int oldh;
    
    while (u != NULL) {
    
        oldh = h[u->m-1][u->n-1];
        Discharge(u, e, h, edges, current);
        if (h[u->m-1][u->n-1] > oldh) {
            if (prev != NULL) {
                prev->next = u->next;
                prev = NULL;
                u->next = L;
                L = u;
            } 
        } 
        prev = u;
        u = u->next;

    }

    int f = 0;
    for (u = s; u != NULL; u=u->next)
        f += u->f;
    
    return f;
}

int main() {

    scanf("%d %d", &M, &N);
    scanf("%d %d", &S, &C);

    int e[M][N], h[M][N];
    link edges[M][N], current[M][N];

    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            edges[j][i] = NULL;

    
    printf("%d\n", Relabel_To_Front(e, h, edges, current));
    
    return 0;
}
