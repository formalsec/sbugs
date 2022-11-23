#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/* Projeto 1 - ASA
 * 2º semestre 2018/2019
 * Álvaro Louro 86373 */

/* wtf codigo mais nojento sorry */

#include <stdio.h>

int maxID;
int routers;
int c_index = 0;
int c = 0;

int get_max(int arr[], int size) {
    int max = 0;
    int i;
    
    for(i = 0; i < size; i++)
        if(max < arr[i])
            max = arr[i];
    
    return max;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int temp;
    int i = low-1;
    int j;
    
    for(j = low; j <= high-1; j++) {
        if(arr[j] <= pivot) {
            i++;
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    
    temp = arr[high];
    arr[high] = arr[i+1];
    arr[i+1] = temp;
    
    return i+1;
}

void quick_sort(int arr[], int low, int high) {
    if(low < high) {
        int p = partition(arr, low, high);
        
        quick_sort(arr, low, p-1);
        quick_sort(arr, p+1, high);
    }
}

int not_in(int value, int size, int arr[size]) {
    
    int i;
    
    for(i = 0; i < size; i++) {
        if(arr[i] == value)
            return 0;
    }
    return 1;
}

void dfs(int size, int arr[size][size], int visited[size], int v) {
    
    visited[v] = 1;
    
    routers++;
    
    if(v+1 > maxID)
        maxID = v+1;
    
    int w;
    
    for(w = 0; w < size; w++)
        if(arr[v][w])
            if(!visited[w])
                dfs(size, arr, visited, w);
}

void dfs2(int size, int arr[size][size], int visited[size], int c_vertex[size], int v) {
    
    visited[v] = 1;
    
    int isFirstEdge = 1;
    int w;
    
    for(w = 0; w < size; w++) {
        if(arr[v][w]) {
            if(isFirstEdge) {
                dfs(size, arr, visited, w);
                isFirstEdge = 0;
            }
            else {
                if(!visited[w]) {
                    c_vertex[c_index++] = v+1;
                    c++;
                    return;
                }
            }
        }
    }
}

int main(){
    
    int n;
    int l;
    
    /* read input */
    if(scanf("%d", &n) != 1)
        return 0;
    
    if(scanf("%d", &l) != 1)
        return 0;
    
    int graph[n][n]; /* matrix rip space (and time) */
    int visited[n]; /* visited vertices in dfs */
    int visited_aux[n];
    int scc_id[n]; /* array of ids to be printed */
    int c_vertex[n]; /* array of routers that would break scc */
    int r = 0; /* no of sub networks (scc) */
    int m = 0; /* no of routers in largest scc after c-removal */
    int id_index = 0; /* scc_id array index */
    int u, v;
    int i, j;
    
    /* initialize everything to 0 */
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            graph[i][j] = 0;
        
        visited[i] = 0;
        scc_id[i] = 0;
    }
    
    /* read input */
    for(i = 0; i < l; i++) {
        
        if(scanf("%d %d", &u, &v) != 2)
            return 0;
        
        graph[u-1][v-1] = 1;
        graph[v-1][u-1] = 1;
    }
    
    /* find no and id of scc */
    for(i = 0; i < n; i++) {
        
        if(!visited[i]) {
            maxID = 0;
            
            for(j = 0; j < n; j++)
                visited_aux[j] = 0;
            
            dfs(n, graph, visited_aux, i);
            
            r++;
            scc_id[id_index++] = maxID;
            
            for(j = 0; j < n; j++)
                if(visited_aux[j])
                    visited[j] = visited_aux[j];
        }
    }
    
    quick_sort(scc_id, 0, id_index-1);
    
    printf("%d\n", r);
    
    for(i = 0; i < id_index; i++)
        printf("%d ", scc_id[i]); /* ATENCAO espaco no fim tambem */
    
    printf("\n");
    
    /* find which vertices would break scc */
    for(i = 0; i < n; i++) {
        
        for(j = 0; j < n; j++)
            visited_aux[j] = 0;
        
        dfs2(n, graph, visited_aux, c_vertex, i);
    }
    
    for(i = 0; i < n; i++)
        visited[i] = 0;
    
    /* find largest number of routers in scc after c-removal */
    for(i = 0; i < c_index; i++) {
        
        /* remove edges */
        for(j = 0; j < n; j++) {
            if(graph[c_vertex[i]-1][j]) {
                graph[c_vertex[i]-1][j] = 0;
                graph[j][c_vertex[i]-1] = 0;
            }
        }
    }
    
    for(i = 0; i < n; i++) {
        
        if(not_in(i+1, c_index, c_vertex)) {
            
            if(!visited[i]) {
                
                for(j = 0; j < n; j++)
                    visited_aux[j] = 0;
                
                routers = 0;
                
                dfs(n, graph, visited_aux, i);
                
                if(routers > m)
                    m = routers;
                
                for(j = 0; j < n; j++)
                    if(visited_aux[j])
                        visited[j] = visited_aux[j];
            }
        }
    }
    
    printf("%d\n%d\n", c, m);
    
    return 0;
}
