#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define grey 1
#define white 0
#define black 2

typedef int bool;
#define true 1
#define false 0

int time;
int n_sub_nets=0;
int sub_net_id=0;
int id_vector_size=1;
int *id_vector;
bool *Articulation_points;
int *low;
int n_biggest_sub_net=0;
int counter=0;

struct node{
  int number;
  struct node* next;
};

struct list {
  struct node *head;
  int color;
  int t_discovery;
  int t_finish;
  bool parent;
  int children;
};

struct Graph{
  int N_vertices;
  struct list* lista_adj;
};

struct node* new_node(int v){
  struct node* new_node=(struct node*) can_fail_malloc(sizeof(struct node));
  new_node->number=v;
  new_node->next=NULL;
  return new_node;
}
struct Graph* new_graph(int vertices){
  struct Graph* graph= (struct Graph*) can_fail_malloc(sizeof(struct Graph));
  graph->N_vertices= vertices;


  graph->lista_adj= (struct list*) can_fail_malloc((vertices+1)*(sizeof(struct list)));

  int i;
  for(i=1; i<=vertices; i++){
    graph->lista_adj[i].head=NULL;
    graph->lista_adj[i].color=white;
    graph->lista_adj[i].t_discovery=0;
    graph->lista_adj[i].t_finish=0;
    graph->lista_adj[i].parent=-1;
    graph->lista_adj[i].children=0;
  }

  return graph;
}

int min(int i1,int i2){
  return (i1<i2?i1:i2);
}


void DFS_visit(struct Graph* graph,int vertex){
   graph->lista_adj[vertex].color=grey;
   graph->lista_adj[vertex].t_discovery=low[vertex]=time;
   time++;
   counter++;
   if(vertex>sub_net_id){
      sub_net_id=vertex;
   }
   struct node* aux_node= graph->lista_adj[vertex].head;
   while(aux_node){
      if(graph->lista_adj[aux_node->number].color==white){
         graph->lista_adj[aux_node->number].parent=vertex;
         graph->lista_adj[vertex].children++;
         DFS_visit(graph,aux_node->number);

         low[vertex]=min(low[vertex],low[aux_node->number]);

         if(graph->lista_adj[vertex].parent==-1 && graph->lista_adj[vertex].children >1){
            Articulation_points[vertex]=true;
         }
         if(graph->lista_adj[vertex].parent!=-1 && low[aux_node->number]>= graph->lista_adj[vertex].t_discovery){
            Articulation_points[vertex]=true;
         }
      }
      else if(aux_node->number!=graph->lista_adj[vertex].parent){
         low[vertex]=min(low[vertex],graph->lista_adj[aux_node->number].t_discovery);
      }
      aux_node=aux_node->next;
   }
   graph->lista_adj[vertex].color=black;
   graph->lista_adj[vertex].t_finish=time;
   time++;
}

void DFS(struct Graph* graph){
  int i;
  time=1;
  for(i=graph->N_vertices; i>=1;i--){
    if(graph->lista_adj[i].color==white){
      DFS_visit(graph,i);
      if(counter>n_biggest_sub_net){
            n_biggest_sub_net=counter;
         }
      counter=0;
      if(id_vector_size==n_sub_nets){
        id_vector_size+=20;
          id_vector=can_fail_realloc(id_vector,(id_vector_size*(sizeof(int))));
        }
      id_vector[n_sub_nets]=sub_net_id;
      sub_net_id=0;
      n_sub_nets++;
    }
  }
}

void add_to_graph(struct Graph* graph,int v, int u){
  struct node* aux_node= new_node(u);

  aux_node->next=graph->lista_adj[v].head;
  graph->lista_adj[v].head=aux_node;

  aux_node= new_node(v);
  
  aux_node->next=graph->lista_adj[u].head;
  graph->lista_adj[u].head=aux_node;
  
}

struct Graph* ficheiro(){
    int vertices,arestas,u,v,i=0;
    scanf("%d",&vertices);
    struct Graph* graph=new_graph(vertices);
    scanf("%d",&arestas);
    while(i!=arestas){
     scanf("%d %d",&u,&v);
     add_to_graph(graph,u,v);
     i++;
    }
    return graph;
}

void free_graph(struct Graph* graph){
  int i;
  struct node* aux_node;
  for(i=1; i<=graph->N_vertices; i++ ){
    while(graph->lista_adj[i].head){
      aux_node=graph->lista_adj[i].head;
      graph->lista_adj[i].head=aux_node->next;
      free(aux_node);
    }
  }
  free(graph->lista_adj);
  free(graph);
}



int main(){
  int j,contador=0;
   struct Graph* graph=ficheiro();
   Articulation_points=can_fail_malloc((graph->N_vertices+1)*sizeof(bool));
   low=can_fail_malloc((graph->N_vertices+1)*sizeof(int));
   id_vector=can_fail_malloc(1*sizeof(int));
   for(j=0;j<=graph->N_vertices;j++){
   Articulation_points[j]=false;
   }
   DFS(graph);
   printf("%d\n",n_sub_nets);
   printf("%d",id_vector[n_sub_nets-1]);
   for(j=(n_sub_nets-2); j>-1;j--){
    printf(" %d",id_vector[j]);
   }
   printf("\n");
    for(j=1;j<=graph->N_vertices;j++){
      graph->lista_adj[j].color=white;
      graph->lista_adj[j].t_discovery=0;
      graph->lista_adj[j].t_finish=0;
      graph->lista_adj[j].parent=-1;
      graph->lista_adj[j].children=0;
      if(Articulation_points[j]==true){
         graph->lista_adj[j].color=black;
         contador++;
      }
   }
   printf("%d\n",contador);
   n_sub_nets=0;
   n_biggest_sub_net=0;
   counter=0;
   DFS(graph);
   printf("%d\n",n_biggest_sub_net);
   free(id_vector);
   free(Articulation_points);
   free(low);
   free_graph(graph);
   return 0;
}