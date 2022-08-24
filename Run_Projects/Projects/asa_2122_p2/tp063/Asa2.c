#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum colours{WHITE, GRAY, RED, BLACK, ORANGE};

typedef struct node{
    int val;
    int parent;
    struct node* next;
    struct node* last;
}*Node;




int DFS_Visit(Node *nodes, int pos, enum colours *vertices_colour){
    Node node = nodes[pos];
    if(node && node->val!=0){
        vertices_colour[pos] = GRAY;
        Node v;
        for (v = node; v != NULL; v = v->next){
            if (vertices_colour[v->val-1]==WHITE && v->val != 0){

                DFS_Visit(nodes, v->val-1, vertices_colour);
            }
            else if (vertices_colour[v->val-1]==GRAY){
                printf("0\n");
                exit(0); 
            }
        }
        vertices_colour[pos] = BLACK;
        return 0;
    }

    vertices_colour[pos] = BLACK;
    return 0;
}

int DFS(Node *nodes, int length){

    int i;

    enum colours *vertices_colour = malloc(sizeof(enum colours)*length);
    for (i = 0; i < length; i++){
        vertices_colour[i] = WHITE; 
    }

    for (i = 0; i < length; i++){

        if(vertices_colour[i]==WHITE)
            DFS_Visit(nodes, i, vertices_colour);
        }
    
    return 0;
}
int LCA_Visit(Node *nodes, int pos, enum colours *LCA_colours, int *number_of_parents, enum colours colour){
    if(LCA_colours[pos] == WHITE)
        LCA_colours[pos] = colour;
    if(colour!=GRAY){
        if(LCA_colours[pos] == GRAY){
            LCA_colours[pos] = BLACK;
        }
    }

    if(number_of_parents[pos] == 0){
        return 0;
    }
    if(number_of_parents[pos] == 1){
        LCA_Visit(nodes, nodes[pos]->parent-1, LCA_colours, number_of_parents, colour);
        return 0;
    }
    if(number_of_parents[pos] == 2){
        LCA_Visit(nodes, nodes[pos]->parent-1, LCA_colours, number_of_parents, colour);
        LCA_Visit(nodes, nodes[pos]->next->parent-1, LCA_colours, number_of_parents, colour);
        return 0;
    }
    return 0;
}
int filter(Node *nodes, int pos, enum colours*LCA_colours,int *number_of_parents){

    if(number_of_parents[pos] == 0){
        return 0;
    }
    if(number_of_parents[pos] == 1){
        int parent1 = nodes[pos]->parent;

        LCA_colours[parent1-1] = ORANGE;
        filter(nodes, parent1-1, LCA_colours, number_of_parents);
        return 0;
    }
    if(number_of_parents[pos] == 2){
        int parent1 = nodes[pos]->parent;
        int parent2 = nodes[pos]->next->parent;

        LCA_colours[parent1-1] = ORANGE;
        LCA_colours[parent2-1] = ORANGE;
        filter(nodes, parent1 - 1, LCA_colours, number_of_parents);
        filter(nodes, parent2 - 1, LCA_colours, number_of_parents);
        return 0;
    }

    return 0;
}

void LCA(Node *nodes, int v1, int v2, int *number_of_parents, int length){
    int i;
    int x = 0;

   enum colours *vertices_colour = malloc(sizeof(enum colours)*length);
    for (i = 0; i < length; i++){
        vertices_colour[i] = WHITE; 
    }
    LCA_Visit(nodes, v1, vertices_colour, number_of_parents, GRAY);
    LCA_Visit(nodes, v2, vertices_colour, number_of_parents, RED);
    for(i = 0; i<length; i++){
        if(vertices_colour[i]==BLACK || vertices_colour[i] == ORANGE){
            filter(nodes, i, vertices_colour,number_of_parents);
        }        

    }
    for(i = 0; i < length; i++){
        if(vertices_colour[i]==BLACK){
            printf("%d ", i+1);
            x++;
        }
    }

    if(x==0)
        printf("-");
    printf("\n");
}


void insert_node(Node *nodes, int x, int y){
    
    if(nodes[x-1] == NULL){

        nodes[x-1] = malloc(sizeof(struct node));
        Node node = nodes[x-1];
        node->val = y;
        node->next = NULL;
        node->last = node;
    }
    else if(nodes[x-1]->val==0){
        Node node = nodes[x-1];
        node->val = y;
        node->last = node;
    }

    /*Criacao de adjacentes*/
    else{ 

    Node aux = nodes[x-1]->last;
    
    if(aux->next)
        aux = aux->next;
    else{
        if(aux->val!=0){
            aux->next = (Node) malloc(sizeof(struct node));
        }
        aux = aux->next;
    }   
    aux->val = y;
    aux->next = NULL; 
    nodes[x-1]->last = aux; 
    }
}
void add_parent(Node *nodes, int y, int x, int * number_of_parents){
        
    Node node = nodes[y-1];
    /*Criaçao dos pais*/
    if(nodes[y-1]==NULL){
        nodes[y-1] = malloc(sizeof(struct node));
        node = nodes[y-1];
        node->val = 0;
        node->next = NULL;
    }
    if(number_of_parents[y-1] == 1){

        node->parent = x;
    }
    else if(number_of_parents[y-1] == 2){
        if(nodes[y-1]->next == NULL){
            node->next = malloc(sizeof(struct node));
            node->next->val = 0;
        }
        node->next->parent = x;

   }
}
int main(){
    int FAILED = 0;

    int *number_of_parents; 

    int v1, v2;
    int i, m, n, x, y;
    if(scanf("%d %d", &v1, &v2) != 2){
        printf("0\n");
        return 0;
    }
       
    if (scanf("%d %d", &n, &m) != 2){
        printf("0\n");
        return 0;
    }

    number_of_parents = malloc(sizeof(int)*n);
    for (i = 0; i<n; i++)
        number_of_parents[i] = 0;

    Node *nodes = malloc(sizeof(struct node) * n);
    for(i = 0; i<n; i++){
        nodes[i] = NULL;
    }

    /*Leitura de dados*/
    for(i = 0; i<m; i++){
        if(scanf("%d %d", &x, &y) != 2){
            printf("0\n");
            return 0;
        }   
        number_of_parents[y-1]++;
        if(number_of_parents[y-1] == 3){
            printf("%d\n", y);
            FAILED = 1;
        }
        
        if(FAILED==1)
            continue;

        insert_node(nodes, x, y);
        add_parent(nodes, y, x, number_of_parents);  
    }

    if (FAILED){
        printf("0\n");
        return 0;
    }

    DFS(nodes, n);
    LCA(nodes, v1-1, v2-1, number_of_parents, n);

    return 0;
}
