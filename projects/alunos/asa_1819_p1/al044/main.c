#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node {

  int value;
  int color;
  struct node *next;
} *link;





void initializeNodes(link* lista, int routers);
void addNode(link* lista, int pai, int filho);
void dfs(link* lista, int routers, char* maxi);
void dfsVisit(link* lista, link node, int routers);
void sortFrees(link* lista, link* lst, int routers);
link newListNode(int filho);
void freeRow(link node);
link checkUnvisitedChildren(link* lista, link node, int routers);


int ligacoesRede = 0;
int cycles = 0;
int caminhoCount = 0;
link* pilha;
int stackhead = 0;
void push(link node);
link pop();
int** redes;
int* caminho;
int max=0;
int quebra  = 0;
int tamanhoRede = 0;
int maximoRede =0;
int maxiCont=0;
int first = 1;
/*

-------------------------------- MAIN

*/
int main() {

 

  int routers = 0;

 
  scanf("%d%d", &routers, &ligacoesRede);

  char maxi[routers*2];
  strcpy(maxi, "");
  

  link* lista= can_fail_calloc(routers, sizeof(struct node));
  link*lst = can_fail_calloc(routers, sizeof(struct node));
  initializeNodes(lista, routers);
  caminho = can_fail_calloc(routers, sizeof(int));
  redes = can_fail_calloc(routers, sizeof(int));

  int i;
  for (i = 0; i < ligacoesRede; i++) {

    int pai, filho;
    scanf("%d%d", &pai, &filho);
    addNode(lista, pai, filho);

  }

  
  
  
 
  dfs(lista, routers, maxi);
  first = 0;
  printf("%d\n",cycles );


  int v;
  for (i= 0; i<maxiCont; i++){
    v = atoi(&maxi[i]);
    printf("%d ", v);

  }
  printf("\n");


  int cyclesAux = cycles;
  cycles=0;
  int temp = routers;

  int j;
  

  for (i = 0; i < routers; i++){
  

   
    for (j = 0; j < routers; j++){
      lista[j]->color = WHITE;
    }

    lista[i]->color = BLACK;
  
    dfs(lista, routers, maxi);
 
    
    
    
    if (cyclesAux < cycles)  
      lst[quebra++] = lista[i];
   
    
    cycles = 0;


    routers = temp;


  }
  

  printf("%d\n",quebra );

  temp = routers;
  maximoRede = 0;
  i=0;
 
  for (j = 0; j < routers; j++){
    if (i<quebra){
      if (lista[j]->value == lst[i]->value)  {
       lista[j]->color = BLACK;
       i++;
      }
      else
       lista[j]->color = WHITE;
    }
    
      
    else
       lista[j]->color = WHITE;
  }

 
  dfs(lista, routers, maxi);

  routers = temp;
  
  printf("%d\n",maximoRede );
  

  return 0;
}

/*

-------------------------------- Auxiliar Functions


*/









void initializeNodes(link* lista, int routers) {

  int i;
  for (i = 0; i < routers; i++) {

    lista[i] = can_fail_malloc(sizeof(struct node));
    lista[i]->value = i;
    lista[i]->next = NULL;
  }
}

link newListNode(int filho){
    link newNode = can_fail_malloc(sizeof(struct node));
    newNode->value=filho;
    newNode->next=NULL;

    return newNode;
}



void addNode(link* lista, int pai, int filho) {


  
  link newNode = newListNode(filho-1);

  newNode->next=lista[pai-1]->next;
  lista[pai-1]->next = newNode;

  newNode = newListNode(pai-1);

  newNode->next=lista[filho-1]->next;
  lista[filho-1]->next = newNode;


  
}

void sortFrees(link* lista, link* lst, int routers) {
  int i;
  for (i = 0; i < routers; i++) {

    freeRow(lista[i]);
  }
  for (i = 0; i < quebra; i++)
  {
    freeRow(lst[i]);
  }
  
  
  free(redes);
  free(caminho);
  free(lista);
}

void freeRow(link node) {

  if(node->next != NULL)
    freeRow(node->next);

  free(node);
}

void dfs(link* lista, int routers, char* maxi) {
 
  pilha = can_fail_malloc((routers + 1) * sizeof(struct node));
  pilha[0] = NULL;
  char str[routers];


  int i;
  for (i = 0; i < routers; i++)
    if (lista[i]->color == WHITE){
      tamanhoRede = 1;
      dfsVisit(lista, lista[i], routers); 
     
      if (tamanhoRede>maximoRede)
      {
        maximoRede = tamanhoRede;
      }
     
      sprintf(str, "%d", max);
      
      strcat(maxi, str);
      strcat(maxi, " ");
      maxiCont++;
      max = 0;
      if (first) {
        redes[cycles] = caminho;
        caminho = can_fail_calloc(routers, sizeof(int));
        caminhoCount = 0;
      }
      cycles++;
     
    }
    

}


link checkUnvisitedChildren(link* lista, link node, int routers){
  int j=0;
  for (j = 0; j < ligacoesRede; j++){
      if(lista[node->value]->color == WHITE)
        return node;
      if(node->next)
        node=node->next;
  }
  return NULL;

}


void dfsVisit(link* lista, link node, int routers) {
  
  link v;
  if (node->color !=BLACK){
    
  
    node->color = GRAY;
   
    push(node);


    if(node->next){
      v = node->next;
     
      if (lista[v->value]->color!=BLACK){
        
         
         

        while (lista[v->value]->color == WHITE ){
          dfsVisit(lista, lista[v->value], routers);
          tamanhoRede++;
        }

        link n = checkUnvisitedChildren(lista, v, routers);
        if ( n != NULL)
           dfsVisit(lista, lista[n->value], routers);

        link p = pop();
        if ((p->value+1)>max){
          max = p->value+1;
        }
        
        if(first)
          caminho[caminhoCount++] = p->value+1;


     }
     else if (v->next){
      v=v->next;
      dfsVisit(lista, lista[v->value], routers);
    }


      
    }
    

    

  }

  
}

void push(link node) {

 
  pilha[stackhead++] = node;
}

link pop() {
  return pilha[--stackhead];
}