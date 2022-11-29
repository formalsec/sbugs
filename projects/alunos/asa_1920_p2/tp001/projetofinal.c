#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include<stdio.h>
#include<stdlib.h>

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct _node{
    int* adj;
    int* capacity_adj;
    int* flow_adj;
    int deg;
    int color;
    int pred;
}Node;

Node* node;


int head,tail;
int* q;

void enqueue (int x) {
    q[tail] = x;
    tail++;
    node[x].color = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    node[x].color = BLACK;
    return x;
}
 
int bfs (int avenidas, int ruas) {
    int u,v;
    for (u=0; u < avenidas * ruas*2+ 2; u++) {
        node[u].color = WHITE;
    }   


    head = tail = 0;
    enqueue(0);
    node[0].pred = -1;
    while (head!=tail) {
        u = dequeue();

        for (v=0; v < node[u].deg; v++) {
            if (node[node[u].adj[v]].color == WHITE && (node[u].capacity_adj[v] - node[u].flow_adj[v]) > 0) {
                enqueue(node[u].adj[v]);

                node[node[u].adj[v]].pred = u;
            }
        }
    }

    return node[ruas * avenidas * 2 + 1].color == BLACK;
}

int max_flow (int avenidas, int ruas) {
    int i,j,u;
    int atual;
    int anterior;

    int max_flow = 0;

    for (i=0; i < avenidas * ruas* 2 + 1; i++) {
        for (j = 0; j < node[i].deg; j++){
            node[i].flow_adj[j] = 0;
        }
    }

    while (bfs(avenidas,ruas)) {

        for (u = avenidas * ruas * 2 + 1; node[u].pred >= 0; u = node[u].pred) {

            atual = 0;
            anterior = 0;
            for (i=0; i<node[node[u].pred].deg ; i++){
         
                if (node[node[u].pred].adj[i] == u){
                    atual = i;
                }
            }
            for (i=0; i<node[u].deg ; i++){
             
                if (node[u].adj[i] == node[u].pred){
                    anterior = i;
                }
            }
            node[node[u].pred].flow_adj[atual] += 1;
            node[u].flow_adj[anterior] -= 1;
        }
        max_flow += 1;
        
    }

    return max_flow;
}



void init(int m, int n, int pessoas, int mercados){
    int i;
    node=can_fail_malloc(sizeof(Node) * ((m * n * 2) + 2));
    node[0].adj = can_fail_malloc(sizeof(int)*pessoas);
    node[0].capacity_adj = can_fail_malloc(sizeof(int)*pessoas);
    node[0].flow_adj = can_fail_malloc(sizeof(int)*pessoas);
    node[m*n*2+1].adj = can_fail_malloc(sizeof(int)*mercados);
    node[m*n*2+1].capacity_adj = can_fail_malloc(sizeof(int)*mercados);
    node[m*n*2+1].flow_adj = can_fail_malloc(sizeof(int)*mercados);
    for(i=1; i<=m*n*2; i++){
        node[i].deg = 0;
        node[i].adj = can_fail_malloc(sizeof(int)*12);
        node[i].capacity_adj = can_fail_malloc(sizeof(int)*12);
        node[i].flow_adj = can_fail_malloc(sizeof(int)*12);
    }
    for(i=1; i<=m*n*2 ; i++){

        if (i % 2 == 1){
           
            node[i].adj[node[i].deg] = i + 1;
            node[i].capacity_adj[node[i].deg] = 1;
            node[i].flow_adj[node[i].deg] = 0;
            node[i].deg ++;

            
            node[i + 1].adj[node[i+1].deg] = i;
            node[i + 1].capacity_adj[node[i+1].deg] = 0;
            node[i + 1].flow_adj[node[i+1].deg] = 0;
            node[i + 1].deg ++;
        }
    } 
}

int main(){
    int avenidas, ruas, mercados, cidadaos, A, R;
    int i,j, pos_vect, maxflow;
    scanf("%d %d", &avenidas, &ruas);
    scanf("%d %d", &mercados, &cidadaos);
    init(avenidas, ruas, cidadaos,mercados);
    maxflow=0;
    q=can_fail_malloc(sizeof(int)*avenidas*ruas*2+2);
    for(i=1; i<=avenidas; i++){
        for(j=1; j<=ruas;j++){
            pos_vect = (i+(j-1)*avenidas) * 2; 

            if (i != avenidas){
                node[pos_vect].adj[node[pos_vect].deg] = pos_vect + 1; 

                node[pos_vect].capacity_adj[node[pos_vect].deg] = 1; 
                node[pos_vect].flow_adj[node[pos_vect].deg] = 0; 
                node[pos_vect].deg++; 


                node[pos_vect + 1].adj[node[pos_vect + 1].deg] = pos_vect;
                node[pos_vect + 1].capacity_adj[node[pos_vect + 1].deg] = 0;
                node[pos_vect + 1].flow_adj[node[pos_vect + 1].deg] = 0;
                node[pos_vect + 1].deg ++;

            }
            if(i != 1){
                node[pos_vect].adj[node[pos_vect].deg] = pos_vect - 3;

                node[pos_vect].capacity_adj[node[pos_vect].deg] = 1; 
                node[pos_vect].flow_adj[node[pos_vect].deg] = 0; 
                node[pos_vect].deg++; 

            
                node[pos_vect - 3].adj[node[pos_vect - 3].deg] = pos_vect;
                node[pos_vect - 3].capacity_adj[node[pos_vect - 3].deg] = 0;
                node[pos_vect - 3].flow_adj[node[pos_vect - 3].deg] = 0;
                node[pos_vect - 3].deg ++;
            }
            if (j != ruas){
                node[pos_vect].adj[node[pos_vect].deg] = pos_vect + avenidas * 2 - 1; 


                node[pos_vect].capacity_adj[node[pos_vect].deg] = 1; 
                node[pos_vect].flow_adj[node[pos_vect].deg] = 0; 

                node[pos_vect].deg++; 

                node[pos_vect + avenidas * 2 - 1].adj[node[pos_vect + avenidas * 2 - 1].deg] = pos_vect;
                node[pos_vect + avenidas * 2 - 1].capacity_adj[node[pos_vect + avenidas * 2 - 1].deg] = 0;
                node[pos_vect + avenidas * 2 - 1].flow_adj[node[pos_vect + avenidas * 2 - 1].deg] = 0;
                node[pos_vect + avenidas * 2 - 1].deg ++;
            }
            if (j != 1){
                node[pos_vect].adj[node[pos_vect].deg] = pos_vect - avenidas * 2 - 1; 

            

                node[pos_vect].capacity_adj[node[pos_vect].deg] = 1; 
                node[pos_vect].flow_adj[node[pos_vect].deg] = 0; 

                node[pos_vect].deg++; 


                node[ pos_vect - avenidas * 2 - 1].adj[node[ pos_vect - avenidas * 2 - 1].deg] = pos_vect;
                node[ pos_vect - avenidas * 2 - 1].capacity_adj[node[ pos_vect - avenidas * 2 - 1].deg] = 0;
                node[ pos_vect - avenidas * 2 - 1].flow_adj[node[ pos_vect - avenidas * 2 - 1].deg] = 0;
                node[ pos_vect - avenidas * 2 - 1].deg ++;
            }
        }
    }

    for (i = 0; i < mercados; i++){
        scanf("%d %d", &A , &R);
        pos_vect = (A+(R-1)*avenidas) * 2;
        node[pos_vect].adj[node[pos_vect].deg] = avenidas*ruas*2+1;
        node[pos_vect].capacity_adj[node[pos_vect].deg] = 1;
        node[pos_vect].flow_adj[node[pos_vect].deg] = 0;
        node[pos_vect].deg++;
        node[avenidas*ruas*2+1].adj[node[avenidas*ruas*2+1].deg] = pos_vect;
        node[avenidas*ruas*2+1].capacity_adj[node[avenidas*ruas*2+1].deg] = 0;
        node[avenidas*ruas*2+1].flow_adj[node[avenidas*ruas*2+1].deg] = 0;
        node[avenidas*ruas*2+1].deg++;
    }
    for (i = 0; i < cidadaos; i++){
        scanf("%d %d", &A , &R);
        pos_vect = (A+(R-1)*avenidas) * 2 - 1;
        node[pos_vect].adj[node[pos_vect].deg] = 0;
        node[pos_vect].capacity_adj[node[pos_vect].deg] = 0;
        node[pos_vect].flow_adj[node[pos_vect].deg] = 0;
        node[pos_vect].deg++;
        node[0].adj[node[0].deg] = pos_vect;
        node[0].capacity_adj[node[0].deg] = 1;
        node[0].flow_adj[node[0].deg] = 0;
        node[0].deg++;

    }


    maxflow = max_flow(avenidas, ruas);

    printf("%d\n", maxflow); 
    return 0;

}

