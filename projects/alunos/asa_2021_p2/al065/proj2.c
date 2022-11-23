#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include<stdio.h>
#include<stdlib.h>
#define min(a,b)  ((a < b)?a:b)

int bfs(int s, int t, int v, int *parent, int *matrix) {
    int *visited =(int*) can_fail_calloc(v, sizeof(int)); 
    int *queue =(int*) can_fail_calloc(v+2, sizeof(int));
    int head=0, tail=0, i, j;
    visited[s] = 1;
    queue[tail++] = s;

    while(head != tail) {
        i = queue[head++];
        visited[i] = 1;
        for(j=0; j<v;j++) {
            if (!visited[j] && matrix[i*v+j] > 0) {
                if(j == t){
                    parent[j] = i;
                    free(visited);
                    free(queue);
                    return 1;
                }
                queue[tail++] = j;
                parent[j] = i;
                visited[j] = 1;
            }
        }
    }
    free(visited);
    free(queue);
    return 0;
}


int EdmonsKarp(int s, int t, int v, int *matrix) {
    int i, out =0;
    int *parent =(int*) can_fail_calloc(v, sizeof(int));
    parent[s] = -1;
    while(bfs(s, t, v, parent, matrix)) {
        int added_flow = matrix[parent[t]*v+t];

        for (i = parent[t]; i != s; i = parent[i]) {
            added_flow = min(added_flow, matrix[parent[i]*v+i]);
        }
        
        for (i = t; i != s; i = parent[i]) {
            matrix[parent[i]*v+i] -= added_flow;
            matrix[i*v+parent[i]] += added_flow;
        }
        out += added_flow;
    }
    free(parent);
    return out;
    }


int main() {
    int n, k, i, a, b, c;
    scanf("%d %d", &n, &k);
    int v = n+2;
    int *matrix = (int *)can_fail_calloc(v*v, sizeof(int));

    for (i=1; i<n+1; i++) {
        scanf("%d %d", &a, &b);
        matrix[i] = a;
        matrix[(i*v)+(n+1)] = b;
    }
    for (i=0; i<k; i++) {
        scanf("%d %d %d", &a, &b, &c);
        matrix[a*v+b]=c;
        matrix[b*v+a]= c;
    }

    printf("%d\n", EdmonsKarp(0, n+1, n+2, matrix));

    free(matrix);
    return 0;
}
