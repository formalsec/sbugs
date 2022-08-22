#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXBUFFER 10000
#define SOURCE 0
#define TARGET 1
#define EMPTY -1

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct
{
    node_t *start;
    node_t *end;
    int size;
} list_t;

list_t *initList();
void addList(list_t *list, int data);
int findIndex(list_t *list, int data);
int getList(list_t *list, int index);
void changeList(list_t *list, int index, int new_data);
int removeList(list_t *list, int index);
void printList(list_t *list);

list_t *initList()
{
    list_t *newList = (list_t *)malloc(sizeof(list_t));
    newList->start = NULL;
    newList->end = NULL;
    newList->size = 0;

    return newList;
}

void addList(list_t *list, int data)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = NULL;

    if (list->start == NULL)
    {
        list->start = newNode;
        list->end = newNode;
    }
    else
    {
        list->end->next = newNode;
        list->end = newNode;
    }
    list->size += 1;
}

node_t *findList(list_t *list, int index)
{
    node_t *node = list->start;
    int i;

    if(index >= list->size || index < 0)
        return NULL;

    for(i = 0; i < index; i++)
    {
        node = node->next;
    }

    return node;
}

int findIndex(list_t *list, int data)
{
    node_t *node = list->start;
    int i;

    for(i = 0; i < list->size; i++)
    {
        if (node->data == data)
            return i;

        node = node->next;
    }

    return -1;
}

int getList(list_t *list, int index)
{
    node_t *node = findList(list, index);

    if (node == NULL)
        return -1;

    return node->data;
}

void changeList(list_t *list, int index, int new_data)
{
    node_t *node = findList(list, index);
    node->data = new_data;
}

int removeList(list_t *list, int index)
{
    node_t *previousnode = findList(list, index - 1);
    node_t *currentnode = findList(list, index);

    if (currentnode == NULL)
        return 0;

    if (index == 0)
    {
        list->start = currentnode->next;
    }

    else
    {
        previousnode->next = currentnode->next;
    }

    free(currentnode);
    return 1;
}

void printList(list_t *list)
{
    node_t *node = list->start;
    int i;

    for(i = 0; i < list->size; i++)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}



typedef list_t queue_t;

queue_t *initQueue();
void pushQueue(queue_t *queue, int data);
int popQueue(queue_t *queue);

queue_t *initQueue()
{
    queue_t *queue = (queue_t *)initList();
    return queue;
}

void pushQueue(queue_t *queue, int data)
{
    addList((list_t *)queue, data);
}

int popQueue(queue_t *queue)
{
    list_t *list = (list_t *)queue;

    int data = getList(list, 0);
    removeList(list, 0);
    return data;
}



int number_vertices;
int number_providers;
int number_distributors;
int number_connections;
int *height, *excess;
list_t **adj_list, **capacity, **flow;
queue_t *vertices_queue;
int maxflow;

int min(int a, int b)
{
    if(a < b)
    {
        return a;
    }
    
    else 
    { 
        return b;
    } 
}

int *init_int_array()
{
    int *array = (int *)malloc(number_vertices * sizeof(int));
    return array;
}

list_t **init_matrix()
{
    int i;
    list_t **list = (list_t **)malloc(number_vertices * sizeof(list_t*));

    for(i = 0; i < number_vertices; i++)
    {
        list[i] = initList();
    }

    return list;
}

void add_capacity(int u, int v, int capacity_number)
{
    addList(adj_list[u], v);
    addList(adj_list[v], u);
    
    addList(capacity[u], capacity_number);
    addList(capacity[v], capacity_number);

    addList(flow[u], 0);
    addList(flow[v], capacity_number);
}

int get_capacity(int u, int v)
{
    int index = findIndex(adj_list[u], v);
    return getList(capacity[u], index);
}

int get_flow(int u, int v)
{
    int index = findIndex(adj_list[u], v);
    return getList(flow[u], index);
}

void change_flow(int u, int v, int flow_number)
{
    int index = findIndex(adj_list[u], v);
    if(index == -1)
    {
        fprintf(stderr, "No Such Index u:%d v:%d", u, v);
    }
    changeList(flow[u], index, flow_number);
}

int is_distributor_in(int vertex)
{
    int distributor_in_start = 2 + number_providers;
    int distributor_in_end = distributor_in_start + number_distributors;

    return vertex >= distributor_in_start && vertex <= distributor_in_end;
}

int get_distributor_out(int vertex)
{
    if (!is_distributor_in(vertex))
    {
        printf("not a distributor");
        return -1;
    }

    return vertex + number_distributors;
}

void add_connections()
{
    int i, u, v, capacity_number;
    /*printf("Enter following lines\n");*/

    for(i = 0; i < number_connections; i++)
    {
        scanf("%d %d %d", &u, &v, &capacity_number);

        if(u == TARGET && is_distributor_in(v))
        {
            add_capacity(u, get_distributor_out(v), capacity_number);
        }

        else if(v == TARGET && is_distributor_in(u))
        {
            add_capacity(get_distributor_out(u), v, capacity_number);
        }

        else
        {
            add_capacity(u, v, capacity_number);
        } 
    }
}

void add_distributors()
{
    char input_line[MAXBUFFER];
    char *token;
    int distributor_capacity;

    /* 
    Each distributor is a vertex pair (distributor_in, distributor_out)
    The edge between these vertices represents the capacity of the distributor
    
    If there are 2 providers and 2 distributors then the list would look like:
    [0]source, [1]target, [2]provider_1, [3]provider_2, 
    [4]distributor_in_1, [5]distributor_in_2
    [5]distributor_out_1, [6]distributor_out_2

    So the indexes for distributor_in starts after the number of providers
    plus the source and target (number_providers + 2)

    And the indexes for distributor_out starts after all the distributor_in 
    */
    int distributor_in = number_providers + 2;
    int distributor_out = distributor_in + number_distributors;

    /*printf("Enter third line\n");*/
    fgets(input_line, MAXBUFFER, stdin);
    token = strtok(input_line, " ");

    while (token != NULL)
    {
        distributor_capacity = atoi(token);
        add_capacity(distributor_in, distributor_out, distributor_capacity);

        /* Next value */
        token = strtok(NULL, " ");
        distributor_in += 1;
        distributor_out += 1;
    }
}

void add_providers()
{
    char input_line[MAXBUFFER];
    char *token;
    int provider_capacity;
    int provider = 2;

    /*printf("Enter second line\n");*/
    fgets(input_line, MAXBUFFER, stdin);
    token = strtok(input_line, " ");

    /* 
    Creates a vertex to be connected to the source
    and creates an edge from the source to the vertex
    Each vertex and edge represent the max production
    of a provider
    */
    while (token != NULL)
    {
        provider_capacity = atoi(token);
        add_capacity(SOURCE, provider, provider_capacity);
        
        /* Next value */
        token = strtok(NULL, " ");
        provider += 1;
    }
}

void fill_pointers()
{
    height = init_int_array();
    excess = init_int_array();
    adj_list = init_matrix();
    capacity = init_matrix();
    flow = init_matrix();
    vertices_queue = initQueue();
}

void make_graph()
{
    char clean_input[MAXBUFFER];
    /*printf("Enter first line\n");*/
    scanf("%d %d %d",
            &number_providers,
            &number_distributors,
            &number_connections);

    /* scanf leaves a newline char, screws next fgets*/
    fgets(clean_input, MAXBUFFER, stdin);

    /* Source + Target + Providers + 2 * Distributors*/
    number_vertices = 2 + number_providers + 2 * number_distributors;
    fill_pointers();
    add_providers();
    add_distributors();
    add_connections();
}

void push(int u, int v)
{
    int current_flow = get_flow(u, v); 
    int current_capacity = get_capacity(u, v);
    int capcity_flow_gap = current_capacity - current_flow; 
    int added_flow = min(excess[u], capcity_flow_gap);

    change_flow(u, v, current_flow + added_flow);

    /*Flow in residual graph */
    current_flow = get_flow(v, u);
    change_flow(v, u, current_flow - added_flow);

    excess[u] -= added_flow;
    excess[v] += added_flow;
    
    /*Source and Target cannot be overflowing*/
    if(v == SOURCE)
    {
        excess[SOURCE] = 0;
    }

    else if(v == TARGET)
    {
        maxflow += excess[TARGET];
        excess[TARGET] = 0;
    }
}

void relabel(int u)
{
    int i, v, capacity_number, flow_number;
    int new_height = height[u];
    
    for(i = 0; i < adj_list[u]->size; i++)
    {
        v = getList(adj_list[u], i);
        capacity_number = get_capacity(u, v);
        flow_number = get_capacity(u, v);

        if(capacity_number - flow_number > 0)
        {
        new_height = min(new_height, height[v]);
        }
    }

    height[u] = new_height + 1;
}

int can_push(int u, int v)
{
    int capacity_number = get_capacity(u, v);
    int flow_number = get_flow(u, v);
    int enough_capacity = (capacity_number - flow_number > 0);
    int enough_height = (height[u] == (height[v] + 1));

    return enough_capacity && enough_height;
}

void discharge(int u)
{
    int v;
    int index = 0;
    while(excess[u] > 0)
    {
        v = getList(adj_list[u], index);
        
        if(v == -1)
        {
            relabel(u);
            index = 0;
        }

        else if(can_push(u, v))
        {
            push(u, v);
        }

        else
        {
            index += 1;
        }
    }
}

void fill_queue()
{
    int vertex;
    for(vertex = 0; vertex < number_vertices; vertex++)
    {
        pushQueue(vertices_queue, vertex);
    }
}

void preflow()
{
    int i, v, capacity_number;

    for(i = 0; i < number_vertices; i++)
    {
        excess[i] = 0;
        height[i] = 0;
    }
    height[SOURCE] = number_vertices;
    
    /* Saturate vertices leaving source*/
    for(i = 0; i < adj_list[SOURCE]->size; i++)
    {
        v = getList(adj_list[SOURCE], i);
        capacity_number = getList(capacity[SOURCE], i);
        
        excess[v] = capacity_number;
        change_flow(SOURCE, v, capacity_number);
        change_flow(v, SOURCE, 0);
    }
}

void relabel_front()
{
    int vertex, old_height;
    preflow();
    fill_queue();

    vertex = popQueue(vertices_queue);
    while(vertex != EMPTY)
    {
        old_height = height[vertex];
        discharge(vertex);

        if(height[vertex] > old_height)
        {
            /* relabel TO FRONT of the list*/
            pushQueue(vertices_queue, vertex);
        }
        vertex = popQueue(vertices_queue);
    }
}

int distributor_different_cut(int u)
{
    /*
    If the distributor_in and distributor_out
    are in different part of the min cut
    then the distributor must be increased
    */

   if(is_distributor_in(u))
   {
       int dist_out = get_distributor_out(u);

       return (height[u] > height[SOURCE] || height[dist_out] > height[SOURCE]);
   }

   return 0;
}

void find_cut()
{
    int vertex, counter = 0;
    for(vertex = 0; vertex < number_vertices; vertex++)
    {
        if(distributor_different_cut(vertex))
        {
            if(counter == 0)
            {
                printf("%d", vertex);
                counter += 1;
            }

            else
            {
                printf(" %d", vertex);
            }
        }
    }
    printf("\n");
}
/*
void print_graph()
{
    int v, cap, fl;
    printf("\n");
    for (int u = 0; u < number_vertices; u++)
    {
        for (int i = 0; i < capacity[u]->size; i++)
        {
            v = getList(adj_list[u], i);
            cap = getList(capacity[u], i);
            fl = getList(flow[u], i);
            printf("u:%d v:%d flow:%d cap:%d\n", u, v, fl, cap);
        }
    }
}
*/
int main()
{
    maxflow = 0;
    make_graph();
    relabel_front();
    printf("%d\n", maxflow);
    find_cut();
    return 0;
}