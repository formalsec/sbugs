#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
/*--------------Grupo 017--------------
         Ielga Oliveira 92479
         Larissa Tomaz  92506
-------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list List;
typedef struct edge Edge;
typedef struct vertice Vertice;
typedef struct node Node;
typedef struct pilha Pilha;

int *parentsList;
int v;

struct node{
  int num_vertice;
  Node *next;
};

struct pilha{
  Node *head;
  Node *tail;
};

struct edge{
  int to;
  int f;
  int c;
  Edge *next;
};

struct list{
  Edge *head;
  Edge *tail;
};

struct vertice{
  List friends;
};

Vertice *vertices;

Node *push(Node *tail,Node**head,int v){
  Node *aux=(Node*)can_fail_malloc(sizeof(Node));
  aux->num_vertice=v;
  aux->next=NULL;

  if(tail==NULL){
    *head=aux;
    return *head;
  }
  tail->next=aux;
  return aux;
}

int popFront(Node **head,Node**tail){
  int n;
  if(*head==*tail){

    n=(*head)->num_vertice;
    free(*head);
    *head=NULL;
    *tail=NULL;
  }
  else{
    n=(*head)->num_vertice;
    Node *aux=*head;
    *head=aux->next;
    free(aux);
  }
  return n;
}

Edge *friend(Edge *tail, Edge**head, int v, int cap, int flow){
  Edge *aux=(Edge*)can_fail_malloc(sizeof(Edge));
  aux->to=v;
  aux->c=cap;
  aux->f=flow;
  aux->next=NULL;

  if(tail==NULL){
    *head=aux;
    return *head;
  }
  tail->next=aux;
  return aux;
}

int min(int c1, int cf){
  if(c1>cf){
    return cf;
  }
  else{
    return c1;
  }
}

int bfs(int startNode, int endNode){
  int i,currentNode;
  Edge* aux;
  Node* t;
  Node* aux2;
  Pilha stack;

  for(i=0;i<(2*v+2);i++){
      parentsList[i]=-1;
  }
  stack.head=NULL;
  stack.tail=NULL;

  stack.tail=push(stack.tail,&stack.head, startNode);
  parentsList[startNode] = -2;

  while(stack.head!=NULL){
    currentNode = popFront(&stack.head, &stack.tail);
    for(aux=vertices[currentNode].friends.head;aux!=NULL;aux=aux->next){
      int to = aux->to;
      if(parentsList[to] == -1){
        if(aux->c - aux->f > 0){
          parentsList[to] = currentNode;
          if(to == endNode){
            for(t=stack.head; t!=NULL;){
              stack.head = t->next;
              aux2 = t;
              t = t->next;
              free(aux2);
            }
            return 1;
          }
          stack.tail = push(stack.tail,&stack.head, to);
        }
      }
    }
  }
  return 0;
}

int edmondsKarp(int startNode, int endNode){
    int maxFlow = 0;

    while(1){
      int flow = bfs(startNode, endNode);
      if (flow == 0){
        break;
      }
      maxFlow += flow;
      int currentNode = endNode;
      Edge *aux;
      while(currentNode != startNode){
        int previousNode = parentsList[currentNode];
        for(aux=vertices[previousNode].friends.head;aux!=NULL;aux=aux->next){
          if(aux->to == currentNode){
            aux->f +=flow;
            break;
          }
        }
        for(aux=vertices[currentNode].friends.head;aux!=NULL;aux=aux->next){
          if(aux->to == previousNode){
            aux->f -=flow;
            break;
          }
        }
        currentNode = previousNode;
      }
    }
    return maxFlow;
}

void eliminartudo()
{
  int i;
  Edge *t;
  Edge *aux;
  for (i = 0; i<2*v+2; i++)
  {
    for(t = vertices[i].friends.head; t != NULL;)
    {
      vertices[i].friends.head = t->next;
      aux = t;
      t = t->next;
      free(aux);
    }
    vertices[i].friends.tail = vertices[i].friends.head;
  }
  free(vertices);
  free(parentsList);
}


int main(){
  int n,m,s,c,i,j,a,r, k;

  scanf("%d %d", &m, &n);
  scanf("%d %d", &s, &c);

  v = m*n;
  vertices=(Vertice*)can_fail_malloc(sizeof(Vertice)*(2*v+2));
  parentsList=(int*)can_fail_malloc(sizeof(int)*(2*v+2));

  for(i=0;i<(2*v+2);i++){
    vertices[i].friends.head = NULL;
    vertices[i].friends.tail = NULL;
    parentsList[i]=-1;
  }

 /*Adiciona todos os vertices vizinhos*/
  for(i=1; i<m+1; i++){
    for(j=1; j<n+1; j++){
      k = i-1+(j-1)*m;
      if(i!=1){
        vertices[k].friends.tail = friend ( vertices[k].friends.tail, &vertices[k].friends.head, k-1+v, 1, 0);
        vertices[k-1+v].friends.tail = friend ( vertices[k-1+v].friends.tail, &vertices[k-1+v].friends.head, k, 0, 0);
      }
      if(i!=m){
        vertices[k].friends.tail = friend ( vertices[k].friends.tail, &vertices[k].friends.head, k+1+v, 1, 0);
        vertices[k+1+v].friends.tail = friend ( vertices[k+1+v].friends.tail, &vertices[k+1+v].friends.head, k, 0, 0);
      }
      if(j!=1){
        vertices[k].friends.tail = friend ( vertices[k].friends.tail, &vertices[k].friends.head, k-m+v, 1, 0);
        vertices[k-m+v].friends.tail = friend ( vertices[k-m+v].friends.tail, &vertices[k-m+v].friends.head, k, 0, 0);
      }
      if(j!=n){
        vertices[k].friends.tail = friend ( vertices[k].friends.tail, &vertices[k].friends.head, k+m+v, 1, 0);
        vertices[k+m+v].friends.tail = friend ( vertices[k+m+v].friends.tail, &vertices[k+m+v].friends.head, k, 0, 0);
      }
    }
  }

  /*Adiciona os arcos entre vértices in e out*/
  for(i=0; i<v; i++){
    vertices[i+v].friends.tail = friend ( vertices[i+v].friends.tail, &vertices[i+v].friends.head, i, 1, 0);
    vertices[i].friends.tail = friend ( vertices[i].friends.tail, &vertices[i].friends.head, i + v, 0, 0);

  }
  /*Adiciona os supermercados*/
  int aux2;
  for(i=0; i<s; i++){
    scanf("%d %d", &a, &r);
    aux2 = a-1+(r-1)*m;
    vertices[aux2].friends.tail = friend ( vertices[aux2].friends.tail, &vertices[aux2].friends.head, 2*v+1, 9999, 0);
    vertices[2*v+1].friends.tail = friend ( vertices[2*v+1].friends.tail, &vertices[2*v+1].friends.head, aux2, 0, 0);
  }
  /*Adiciona os cidadãos*/
  for(i= 0; i<c; i++){
    scanf("%d %d", &a, &r);
    aux2 = a-1+(r-1)*m;
    vertices[2*v].friends.tail = friend ( vertices[2*v].friends.tail, &vertices[2*v].friends.head, aux2+v, 1, 0);
    vertices[aux2+v].friends.tail = friend ( vertices[aux2+v].friends.tail, &vertices[aux2+v].friends.head, 2*v, 0, 0);
  }

  printf("%d\n", edmondsKarp(2*v, 2*v+1));

  eliminartudo();

  return 0;
}
