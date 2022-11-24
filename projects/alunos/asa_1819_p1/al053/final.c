#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

struct node
{
    int vertex;
    struct node* next;
};

struct Graph
{
    int time_visit;
    int num_Vertices;
    int* low_link;
    int* visited;
    int* articulation_points;
    int* parent;
    struct node** adj_Lists; 
};


struct node* createNode(int v)
{
    struct node* newNode = can_fail_malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = can_fail_malloc(sizeof(struct Graph));
    graph->num_Vertices = vertices + 1;
    graph->time_visit = 0;
 
    graph->adj_Lists = can_fail_malloc(vertices * sizeof(struct node*));
    
    graph->visited = can_fail_malloc(vertices * sizeof(int));
    graph->low_link = can_fail_malloc(vertices * sizeof(int));
    graph->articulation_points = can_fail_malloc(vertices * sizeof(int));
    graph->parent = can_fail_malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices + 1; i++) {
        graph->adj_Lists[i] = NULL;
        graph->visited[i] = -1;
        graph->low_link[i] = -1;
        graph->articulation_points[i] = 0;
        graph->parent[i] = -1; 
    }
    return graph;
}

void addEdge(struct Graph* graph)
{
    int src, dest;
    scanf("%d %d", &src, &dest);
    struct node* newNode = createNode(dest);
    newNode->next = graph->adj_Lists[src];
    graph->adj_Lists[src] = newNode;
 
    newNode = createNode(src);
    newNode->next = graph->adj_Lists[dest];
    graph->adj_Lists[dest] = newNode;
}
void addIdentifier(struct node* node, int identifier)
{
    struct node* new_node = createNode(identifier);
    if (node->vertex > identifier)
    {
        new_node->next = node->next;
        node->next = new_node;
        new_node->vertex = node->vertex;
        node->vertex = identifier;
    }
    else if(node->next == NULL )
        node->next =new_node;
    else
        addIdentifier(node->next, identifier);  
}

void printIdentifiers(struct node* node)
{
    if(node->next == NULL)
        printf("%d\n", node->vertex);
    else 
    {
        printf("%d ", node->vertex);
        printIdentifiers(node->next);
    }
    
}
void DFS_Articulation(struct Graph* graph, int u, int* identifier, int* n_art) 
{
        struct node* adj_node =  graph->adj_Lists[u];
        int children = 0;
        int time_visit = graph->time_visit;
        graph->visited[u] = time_visit;
        graph->low_link[u] = time_visit;
        graph->time_visit = time_visit + 1;

        *identifier = MAX(*identifier,u);
        while(adj_node) 
        {
            int v = adj_node->vertex;
        
            if(graph->visited[v] == -1) 
            {
                children++;
                graph->parent[v] = u ;
                DFS_Articulation(graph, v, identifier, n_art);

                graph->low_link[u] = MIN(graph->low_link[u], graph->low_link[v]);

                if(graph->parent[u] == -1 && children > 1)    
                    graph->articulation_points[u] = 1;

                if(graph->parent[u] != -1 && graph->low_link[v] >= graph->visited[u])
                    graph->articulation_points[u] = 1;
            }
            else if (graph->parent[u] != v)
                graph->low_link[u] = MIN(graph->low_link[u], graph->visited[v]);
            
            adj_node = adj_node->next;
        }
    if(graph->articulation_points[u] == 1)
        *n_art = *n_art + 1;
}

void DFS(struct Graph* graph)
{
    int i;
    int identifier;
    int n_networks = 0;
    int* identifier_pointer;
    struct node* head = NULL ;
    int n_art = 0;
    int* pointer_art = &n_art;
    for( i = 1; i < graph->num_Vertices; i++)
    {
        if(graph->visited[i] == -1) 
        {    
            identifier = i;
            identifier_pointer = &identifier;
            DFS_Articulation(graph, i, identifier_pointer, pointer_art);
            n_networks++;
            if (n_networks== 1)
                head = createNode(identifier);
            else
                addIdentifier(head, identifier);
        }
    }
    printf("%d\n", n_networks);

    printIdentifiers(head);

    printf("%d\n", n_art);
}
void DFS2_Visit(struct Graph* graph, int u, int*count)
{
    struct node* adj_node = graph->adj_Lists[u];
    graph->visited[u] = -1;
    *count = *count+1;

    while(adj_node != NULL)
    {
       int v = adj_node->vertex;
       if((graph->visited[v] != -1) && (graph->articulation_points[v] != 1))
            DFS2_Visit(graph, v, count);
        adj_node = adj_node->next; 
    }

}
void DFS2(struct Graph* graph)
{
    int i;
    int max_routers = 0;
    int count = 0;
    int* pointer_count = &count;
    for( i = 1; i < graph->num_Vertices; i++)
    {
        if((graph->visited[i] != -1) && (graph->articulation_points[i] != 1))
        {
            DFS2_Visit(graph, i, pointer_count);
            max_routers = MAX(max_routers, count);
            count = 0;
        }
    }
    printf("%d\n", max_routers);
}

int main()
{
    int v, m, i;

    scanf("%d", &v);
    scanf("%d", &m);
    struct Graph* graph = createGraph(v);

    for(i = m; i != 0 ; i--)
        addEdge(graph);
    DFS(graph);
    DFS2(graph);

    return 0;
}