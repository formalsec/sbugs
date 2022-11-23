#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum color{white, gray, black} Color;

/*Node*/
typedef struct node{
    bool is_source;
    int depth;
    int max_depth;
    struct node* source;
    struct node* parent;
    struct node** link;
    int link_size;
}Node;


void addNode(Node* node_p, Node* node_c){
    node_p->link = (Node**) can_fail_realloc(node_p->link, sizeof(Node*) * ++node_p->link_size);
    node_p->link[node_p->link_size-1] = node_c;
}


/*BFS*/
int visit(Node* node){
    int i;
    int diff;
    int n = node->link_size;

    if(n == 0){
        node->max_depth = node->depth;
        return -1;
    }
    
    for(i = 0; i<n ; i++){
        /*Already found a max*/
        if(node->link[i]->source == node->source){

            /*Visited node lesser depth*/
            if((node->depth + 1) > node->link[i]->depth){
                diff = (node->depth + 1) - node->link[i]->depth;

                if((node->link[i]->max_depth + diff) > node->max_depth ){
                    node->max_depth = node->link[i]->max_depth + diff;
                }
            
            /*Visited node bigger depth*/
            }else if((node->depth + 1) < node->link[i]->depth){
                diff = node->link[i]->depth - (node->depth + 1);

                if(node->max_depth < (node->link[i]->max_depth - diff)){
                    node->max_depth = node->link[i]->max_depth - diff;
                }
                
            /*Visited node same depth*/
            }else{
                if(node->max_depth < node->link[i]->max_depth){
                    node->max_depth = node->link[i]->max_depth;
                }
            }
        
        }else{
            node->link[i]->source = node->source;
            node->link[i]->depth = node->depth + 1;
            node->link[i]->max_depth = -1;
            return i;
        }
    }

    return -1;
}

int longestPath(Node* src){
    int depth = 1;
    Node* current = src;

    while(depth > 0){
        int next = visit(current);
        if(next == -1){
            depth --;
            current = current->parent;
            continue;
        }

        depth++;
        current->link[next]->parent = current;
        current = current->link[next];
    }
    
    return src->max_depth;
}


int main(){
    int n, l, u, v, i;
    int max_depth = 0;
    int min_src = 0;
    if(scanf("%d %d", &n, &l) == 0){
        exit(1);
    }
    Node* graph = (Node*) can_fail_malloc(sizeof(Node) * n);
    
    /*graph initialization*/

    for(i=0; i<n ; i++){
        graph[i].is_source = true;
        graph[i].depth = 1;
        graph[i].max_depth = -1;
        graph[i].source = &graph[i];
        graph[i].parent = &graph[i];
        graph[i].link = NULL;
        graph[i].link_size = 0;
    }

    for(i=0 ; i<l ; i++){
        if(scanf("%d %d", &u, &v) == 0){
            exit(1);
        }
        addNode(&graph[u-1], &graph[v-1]);
        graph[v-1].is_source = false; 
    }

    /*k = O(v)*/
    for(i=0; i<n ; i++){
        if(graph[i].is_source){
            min_src++;
            int max = longestPath(&graph[i]);
            if(max > max_depth){
                max_depth = max;
            }
        }
    }

    printf("%d %d\n", min_src,max_depth);
    
    exit(0);
}