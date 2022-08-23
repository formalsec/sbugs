#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node *next;
    int nextValue;
    int cap;
}node;

typedef struct stack{
    int val;
    struct stack *next;
    struct stack *prev;
}stack;

node **manhattan;
int numVertices, numSuper, numCitizens,total;
int *supermarkets, *citizens, *visited;
stack *head, *last;

void initManhattan(int m);   /*initiate adjacency list*/
void scanInput(int m);        
void insert(int u,int v);       /*inserts edges to adjacency list*/
int fordFulkerson(int s, int t);
int bfs(int s, int t, int parent[]);
void updatePathFlow(int u, int v, int x);
void push(int at);              /*adds node to bfs queue*/
int pop();                      /*removes node from queue*/
node * getNode(int u,int v);   /*returns edge from adjacency list*/
void freeAll();


int main(){
    int m, n;

    scanf("%d %d", &m, &n);
    scanf("%d %d", &numSuper, &numCitizens);

    numVertices = 2 * (n * m);

    manhattan = malloc(sizeof(node) * numVertices);
    supermarkets = malloc(sizeof(int) * numSuper);
    citizens = malloc(sizeof(int) * numCitizens);
    visited = malloc(sizeof(int)*numVertices+2);
    head = NULL;
    last = NULL;
  
    initManhattan(n);

    scanInput(n);

    total = fordFulkerson(numVertices, numVertices+1);
    printf("%d\n", total);

    freeAll();
    return 0;
}

   
int fordFulkerson(int s, int t){ 
    int u, v,path_flow, max_flow = 0;   
    int *parent;
    if(numCitizens == 0 || numSuper == 0)
        return 0;

    parent = malloc(sizeof(int)* numVertices+2);

    while (bfs(s, t, parent) && max_flow <= numCitizens && max_flow <= numSuper){ /*bfs finds the augmenting path / there cant be more connections than supermarkets or citizens*/
        path_flow = 1;                          /*there can be only one citizen per street (edge)*/
        for (v=t; v != s; v=parent[v]){ 
            u = parent[v];
            insert(v,u);                          /*insert back edge (residual graph)*/
            updatePathFlow(u,v,path_flow);
        } 
        max_flow += path_flow; 
    }  
    free(parent);
    return max_flow; 
}  

int bfs(int s, int t, int parent[]){  
    int i, v, u;
    node *no;
    
    for(i = 0; i < numVertices+2; i++) 
        visited[i] = 0; 
    
    push(s); 
    visited[s] = 1; 
    parent[s] = -1; 
    u = pop();
    while (u >= 0){
        no = manhattan[u];
        while(no!= NULL){
            v = no-> nextValue;
            if(visited[v] == 0 && no->cap > 0){
                push(v); 
                parent[v] = u; 
                visited[v] = 1; 
                if(v == t){                     /*if sink is visited stop bfs*/
                    while(u != -1)
                        u = pop();
                    return visited[t];
                }
            }
            no = no->next; 
        }
        u = pop();
    }

    return visited[t]; 
}

void updatePathFlow(int u, int v, int x){
    node * no = getNode(u,v);
    no->cap -= x;
}



node * getNode(int u,int v){
    node *no;
    no = manhattan[u];
    while(no != NULL){
        if(no->nextValue == v)
           return no;
        no = no->next;
    }
    return NULL;
}


void push(int valor){
    stack *aux = malloc(sizeof(stack));
    if(head == NULL){
        head = aux;
        head->next = NULL;
        head->prev = NULL;
        head->val = valor;
        last = head;
        return;
    }
    head->prev = aux;
    aux->next = head;
    aux->prev = NULL;
    aux->val = valor;
    head = aux;

}

int pop(){
    int i = 0;
    if(head == NULL)
        return -1;
    if(last->prev == NULL && last->next == NULL){
        i = last->val;
        head = NULL;
        free(last);
        last = NULL;
        return i;
    }

    else{
        i = last->val;
        last = last->prev;
        free(last->next);
        last->next = NULL;

        return i;
    }
}

void initManhattan(int n){
    int i, c;
    c = 2*n;
    
    for(i = 0; i < numVertices; i++){
        if(i % 2 == 0){        /*all even vertices are 'in' vertices (they only have a connection to the 'out' vertex)*/
            insert(i, i+1);
        }
        else{
            if(i > c)                   /*represents all but the first street*/                   
                insert(i, i - (c + 1));
            if(i + c < numVertices)     /*represents all but the last street*/
                insert(i, i + (c - 1));  

            if(i % c == c - 1){         /*represents the rightmost avenue*/
                insert(i ,i-3);  
            }
            else if(i % c == 1){        /*represents the leftmost avenue*/
                insert(i, i+1);
            }
            else{                       /*all other edges*/
                insert(i, i+1);
                insert(i, i-3);
            }
        }
    }
}


void insert(int u,int v){
    node *new;
    new = (node*)malloc(sizeof(node));
 
    if(manhattan[u]==NULL){
        manhattan[u]=new;
        new->next = NULL;
    }
    else{
        new-> next = manhattan[u];
        manhattan[u] = new;

    } 
    new->nextValue = v;
    new->cap = 1;
   
}

void scanInput(int n){
    int intersection,i,x,y;

    for (i = 0; i < numSuper; i++){
        scanf("%d %d", &x, &y);
        x--;
        y--;
        intersection = ((x * n) + y);     
        supermarkets[i] = intersection*2 +1;     
        insert(intersection*2+1, numVertices+1);  /*connect all supermarkets to sink (t)*/

    }

    for (i = 0; i < numCitizens; i++){
        scanf("%d %d", &x, &y);
        x--;
        y--;
        intersection = (x * n) + y;
        citizens[i] = intersection*2;
        insert(numVertices, intersection*2);   /*connect source (s) to all citizens*/
    }
}

void freeAll(){
    int i;
    node *aux, *aux1;

    free(supermarkets);
    free(citizens);
    free(visited);

    for(i = 0; i < numVertices; i++){
        aux = manhattan[i];
        while(aux){
            aux1 = aux;
            aux = aux->next;
            free(aux1);
        }
    }
}