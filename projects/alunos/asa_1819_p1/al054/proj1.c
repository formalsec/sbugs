#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int id;
  struct node *next;
} node_t;

void initList(node_t* head) {
  head = NULL;
}

node_t* addtoList(node_t* head, int id) {
  node_t* new_head = can_fail_malloc(sizeof(node_t));
  new_head->id = id;
  new_head->next = head;
  return new_head;
}

/*-----------------------------------------------------------------*/

struct Vertice {
  int id;
  int visited;
  int depth;
  int low;
  int parent;
  int cutVertice;
  node_t* head;
};

struct Vertice initVertice(struct Vertice v, int id) {
  v.id = id;
  v.visited = 0;
  v.head = NULL;
  v.parent = -1;
  v.cutVertice = 0;
  return v;
}

struct Vertice addAdj(struct Vertice v, int id) {
  v.head = addtoList(v.head, id);
  return v;
}
/*-----------------------------------------------------------------*/

int minimum(int a, int b) {
  if (a<b) {
    return a;
  }
  else {
    return b;
  }
}

void readInput(struct Vertice **routers, int v) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*v);
  int i, l1, l2;
  for (i = 1; i <= v; i++) {
    router[i-1] = initVertice(router[i-1], i);
    }
  int c;
  scanf("%d", &c);
  for (i = 1; i <= c; i++) {
    scanf("%d %d", &l1, &l2);
    router[l1-1] = addAdj(router[l1-1], l2);
    router[l2-1] = addAdj(router[l2-1], l1);
  }
  *routers = router;
}

int Tarjan_Aux(struct Vertice **routers, int **d, int cutVertice, node_t *head, int id, int n) {
  int aux = **d;
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*n);
  router = *routers;
  if (id > head->id) {
    head->id = id;
  }
  router[id-1].visited = 1;
  router[id-1].depth = **d;
  router[id-1].low = **d;
  int n_childs = 0;
  int articul = 0;
  node_t* node = router[id-1].head;
  while (node != NULL) {
    if (router[node->id-1].visited==0) {
      router[node->id-1].parent = id;
      aux++;
      *d = &aux;
      *routers = router;
      cutVertice = Tarjan_Aux(routers, d, cutVertice, head, node->id, n);
      router = *routers;
      n_childs++;
      if (router[node->id-1].low >= router[id-1].depth) {
        articul = 1;
      }
      router[id-1].low = minimum(router[id-1].low, router[node->id-1].low);
    }
    else if (node->id != router[id-1].parent) {
      router[id-1].low = minimum(router[id-1].low, router[node->id-1].depth);
    }
    node = node->next;
  }
  if ((router[id-1].parent != -1 && articul == 1) || (router[id-1].parent == -1 && n_childs > 1)) {
    router[id-1].cutVertice = 1;
    cutVertice++;
  }
  *d = &aux;
  *routers = router;
  return cutVertice;
}

void Tarjan(struct Vertice **routers, int n) {
  int a = 0;
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*n);
  router = *routers;
  int *d;
  int cutVertice = 0;
  node_t *head = NULL;
  head = addtoList(head, 0);
  d = &a;
  int aux = 1;
  int v = n;
  int i = n;
  while (a!=1) {
    routers = &router;
    cutVertice = Tarjan_Aux(routers, &d, cutVertice, head, v, n);
    a = 1;
    while (i >= 1) {
      if (router[i-1].visited==0) {
        v = router[i-1].id;
        head = addtoList(head, 0);
        aux++;
        a = 0;
        break;
      }
      i--;
    }
  }
  printf("%d\n", aux);
  printf("%d", head->id);
  while (head->next != NULL) {
    head = head->next;
    printf(" %d", head->id);
  }
  printf("\n%d", cutVertice);
  printf("\n");
  *routers = router;
}

void DFS_Aux(struct Vertice **routers, int **d, int id, int n) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*n);
  router = *routers;
  int aux = **d;
  router[id-1].visited = 2;
  aux++;
  *d = &aux;
  node_t* node = router[id-1].head;
  while (node != NULL) {
    if (router[node->id-1].visited!=2 && router[node->id-1].cutVertice!=1) {
      *routers = router;
      DFS_Aux(routers, d, node->id, n);
      }
    node = node->next;
  }
  *routers = router;
}

void DFS(struct Vertice **routers, int n) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*n);
  router = *routers;
  int *d, d_aux;
  int a = 0;
  int aux = 0;
  int v = 1;
  int i = 1;
  while (a != 1) {
    a = 1;
    while (i <= n) {
      if (router[i-1].visited!=2 && router[i-1].cutVertice==0) {
        v = router[i-1].id;
        a = 0;
        break;
      }
      i++;
    }
    d_aux = 0;
    d = &d_aux;
    routers = &router;
    DFS_Aux(routers, &d, v, n);
    if (*d > aux) {
      aux = *d;
      }
  }
  printf("%d\n", aux);
}

/*-----------------------------------------------------------------*/
int main() {
  int v;
  scanf("%d", &v);
  struct Vertice *routers = can_fail_malloc(sizeof(struct Vertice)*v);
  readInput(&routers, v);
  Tarjan(&routers, v);
  DFS(&routers, v);
  return 0;
}
