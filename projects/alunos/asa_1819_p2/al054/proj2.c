#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int id;
  int flux;
  int cap;
  int* f_cap;
  int* f_flux;
  struct node *next;
} node_t;

typedef struct node_l {
  int id;
  struct node_l *next;
} node_l;

typedef struct node_p {
  int id;
  int id1;
  struct node_p *next;
} node_p;

typedef struct node_b {
  int id;
  int cap;
  int flux;
  int* back_cap;
  int* back_flux;
  struct node_b *next;
} node_b;

void initList(node_t* head) {
  head = NULL;
}

node_t* addtoList(node_t* head, int id, int cap) {
  node_t* new_head = can_fail_malloc(sizeof(node_t));
  new_head->id = id;
  new_head->cap = cap;
  new_head->flux = 0;
  new_head->next = head;
  return new_head;
}

struct node_l* addtoL(struct node_l* head, int id) {
  struct node_l* new_head = can_fail_malloc(sizeof(struct node_l));
  new_head->id = id;
  new_head->next = head;
  return new_head;
}

struct node_p* addtoP(struct node_p* head, int id, int id1) {
  struct node_p* new_head = can_fail_malloc(sizeof(struct node_p));
  new_head->id = id;
  new_head->id1 = id1;
  new_head->next = head;
  return new_head;
}

int comp (const void * elem1, const void * elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) {
      return  1;
    }
    if (f < s) {
      return -1;
    }
    return 0;
}

node_t* setPointers(node_t* head, int *cap, int *flux) {
  head->f_cap = cap;
  head->f_flux = flux;
  return head;
}
struct node_b* addtoList_b(struct node_b* head, int id, int *cap, int *flux) {
  struct node_b* new_head = can_fail_malloc(sizeof(struct node_b));
  new_head->id = id;
  new_head->back_cap = cap;
  new_head->back_flux = flux;
  new_head->cap = *cap;
  new_head->flux = *flux;
  new_head->next = head;
  return new_head;
}


/*-----------------------------------------------------------------*/

struct Vertice {
  int id;
  int cap;
  int height;
  node_t* head;
  int visited;
  struct node_b* back;
};

struct Vertice initVertice(struct Vertice v, int id) {
  v.id = id;
  v.cap = 0;
  v.height = 0;
  v.visited = 0;
  v.head = NULL;
  v.back = NULL;
  return v;
}

struct Vertice addAdj(struct Vertice v, int id, int cap) {
  v.head = addtoList(v.head, id, cap);
  return v;
}

struct Vertice setCap(struct Vertice v, int cap) {
  v.cap=cap;
  return v;
}

struct Vertice setHeight(struct Vertice v, int height) {
  v.height = height;
  return v;
}


/*-----------------------------------------------------------------*/

int min(int a, int b) {
  if (a<b) {
    return a;
  }
  else {
    return b;
  }
}

void readInput(struct Vertice **routers, int **vector, int f, int e, int t) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+2));
  int *vetor = can_fail_malloc(sizeof(int)*((2*e)+f-1));
  int i, l1, l2, l3;
  int aux = 0;
  int* f_cap;
  int* f_flux;
  int* fr_cap;
  int* fr_flux;
  router[0] = initVertice(router[0], 0);
  router[0] = setHeight(router[0], (2*e)+f+2);
  router[1] = initVertice(router[1], 1);

  /*Fornecedores*/

  for (i = 2; i < (1+f); i++) {
    scanf("%d ", &l1);
    router[i] = initVertice(router[i], i);
    router[0] = addAdj(router[0], i, l1);
    f_cap = &router[0].head->cap;
    f_flux = &router[0].head->flux;
    router[i].back = addtoList_b(router[i].back, 0, f_cap, f_flux);
    fr_cap = &router[i].back->cap;
    fr_flux = &router[i].back->flux;
    router[0].head = setPointers(router[0].head, fr_cap, fr_flux);
    vetor[aux] = i;
    aux++;
    }
  scanf("%d", &l1);
  router[i] = initVertice(router[i], i);
  router[0] = addAdj(router[0], i, l1);
  f_cap = &router[0].head->cap;
  f_flux = &router[0].head->flux;
  router[i].back = addtoList_b(router[i].back, 0, f_cap, f_flux);
  fr_cap = &router[i].back->cap;
  fr_flux = &router[i].back->flux;
  router[0].head = setPointers(router[0].head, fr_cap, fr_flux);
  vetor[aux] = i;
  aux++;

  /*Estacoes de Abastecimento*/

  i++;
  for (l1 = i; l1 < (1+e+f); l1++) {
    scanf("%d ", &l2);
    router[l1] = initVertice(router[l1], l1);
    vetor[aux] = l1;
    aux++;
    router[l1] = addAdj(router[l1], (l1+e), l2);
    router[l1+e] = initVertice(router[l1+e], (l1+e));
    f_cap = &router[l1].head->cap;
    f_flux = &router[l1].head->flux;
    router[l1+e].back = addtoList_b(router[l1+e].back, l1, f_cap, f_flux);
    fr_cap = &router[l1+e].back->cap;
    fr_flux = &router[l1+e].back->flux;
    router[l1].head = setPointers(router[l1].head, fr_cap, fr_flux);
    vetor[aux] = l1+e;
    aux++;
  }
  scanf("%d", &l2);
  router[l1] = initVertice(router[l1], l1);
  vetor[aux] = l1;
  aux++;
  router[l1] = addAdj(router[l1], (l1+e), l2);
  router[l1+e] = initVertice(router[l1+e], l1+e);
  f_cap = &router[l1].head->cap;
  f_flux = &router[l1].head->flux;
  router[l1+e].back = addtoList_b(router[l1+e].back, l1, f_cap, f_flux);
  fr_cap = &router[l1+e].back->cap;
  fr_flux = &router[l1+e].back->flux;
  router[l1].head = setPointers(router[l1].head, fr_cap, fr_flux);
  vetor[aux] = l1+e;

  /*Ligacoes*/

  aux++;
  for (i = 1; i <= t; i++) {
    scanf("%d %d %d", &l1, &l2, &l3);
    if (l1>(1+f)) {
      router[l1+e] = addAdj(router[l1+e], l2, l3);
      f_cap = &router[l1+e].head->cap;
      f_flux = &router[l1+e].head->flux;
      router[l2].back = addtoList_b(router[l2].back, l1+e, f_cap, f_flux);
      fr_cap = &router[l2].back->cap;
      fr_flux = &router[l2].back->flux;
      router[l1+e].head = setPointers(router[l1+e].head, fr_cap, fr_flux);
      }
    else {
      router[l1] = addAdj(router[l1], l2, l3);
      f_cap = &router[l1].head->cap;
      f_flux = &router[l1].head->flux;
      router[l2].back = addtoList_b(router[l2].back, l1, f_cap, f_flux);
      fr_cap = &router[l2].back->cap;
      fr_flux = &router[l2].back->flux;
      router[l1].head = setPointers(router[l1].head, fr_cap, fr_flux);
      }
  }
  *routers = router;
  *vector = vetor;
}

void printGraph(struct Vertice **routers, int **vector, int f, int e) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  int *vetor = can_fail_malloc(sizeof(int)*((2*e)+f-1));
  vetor = *vector;
  if (vetor[0]==0) {
    vetor[0] = 0;
  }
  int i;
  for (i = 0; i <= ((e*2)+f+1); i++) {
    /*printf("id -> %d\n", router[i].id);
    printf("cap -> %d\n", router[i].cap);
    printf("height -> %d\n", router[i].height);*/
    node_t* node = router[i].head;
    while (node != NULL) {
      /*printf(" %d %d %d\n", node->flux, node->cap, node->id);*/
      node = node->next;
      }
    /*printf("  -- --  \n");*/
    struct node_b* node_b = router[i].back;
    while (node_b != NULL) {
      /*node_b->flux = *node_b->back_flux;
      printf(" %d %d %d\n", node_b->id, node_b->flux, node_b->cap);*/
      node_b = node_b->next;
      }
    /*printf("-------\n");*/
    }
  /*printf("[");*/
  for (i = 0; i <= ((2*e)+f-1); i++) {
      /*printf("%d,", vetor[i]);*/
    }
  /*printf("]\n");*/
}

void Push(struct Vertice **routers, int f, int e, int c) {
  int x;
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  node_t* nodet = router[c].head;
  struct node_b* node = router[c].back;
  while (node != NULL) {
    node->flux = *node->back_flux;
    if (router[c].height > router[node->id].height) {
      x = min(node->flux, router[c].cap);
      node->flux = node->flux - x;
      router[c].cap = router[c].cap - x;
      router[node->id].cap = router[node->id].cap + x;
      nodet = router[node->id].head;
      while (nodet != NULL) {
        nodet->flux = *nodet->f_flux;
        nodet = nodet->next;
      }
    }
    node = node->next;
  }

  nodet = router[c].head;
  while (nodet != NULL) {
    if (nodet->flux != nodet->cap && router[c].height > router[nodet->id].height) {
      nodet->flux = *nodet->f_flux;
      x = min(nodet->cap, router[c].cap);
      nodet->flux = nodet->flux + x;
      router[c].cap = router[c].cap - x;
      router[nodet->id].cap = router[nodet->id].cap + x;
    }
    nodet = nodet->next;
  }
  *routers = router;
}

void Discharge(struct Vertice **routers, int f, int e, int c) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  while (router[c].cap > 0) {
    router[c].height++;
    routers = &router;
    Push(routers, f, e, c);
  }
  *routers = router;
}

void Relabel_to_Front(struct Vertice **routers, int **vector, int f, int e) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  int *vetor = can_fail_malloc(sizeof(int)*((2*e)+f-1));
  vetor = *vector;
  node_t* node = router[0].head;
  int oldh, i, aux, aux2, aux3;
  while (node!=NULL) {
    node->flux = node->cap;
    *node->f_flux = node->cap;
    router[0].cap = router[0].cap - node->cap;
    router[node->id].cap = router[node->id].cap + node->cap;
    node = node->next;
  }

  i = 0;
  while (i <= (2*e)+f-1) {
    oldh = router[vetor[i]].height;
    routers = &router;
    Discharge(routers, f, e, vetor[i]);
    router = *routers;
    if (router[vetor[i]].height > oldh) {
      aux2 = vetor[i];
      for (aux = 0; aux <= i; aux++) {
        aux3 = vetor[aux];
        vetor[aux] = aux2;
        aux2 = aux3;
      }

      i = 0;
    }
    i++;
  }
  *routers = router;
  *vector = vetor;
  printf("%d\n", router[1].cap);
}

void BackVetices(struct Vertice **routers, int f, int e) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  int i;
  node_t* node;
  for (i = 0; i <= ((e*2)+f+1); i++) {
    node = router[i].head;
    while (node != NULL) {
      if (node->cap > node->flux) {
        router[node->id] = addAdj(router[node->id], i, 10);
        router[i].back = addtoList_b(router[i].back, node->id, &router[node->id].head->cap, &router[node->id].head->flux);
      }
      node = node->next;
    }
  }
}

struct node_l* DFS_Aux(struct Vertice **routers, struct node_l* head, int f, int l, int e) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+l+1));
  router = *routers;
  node_t* node = router[f].head;
  router[f].visited = 1;
  while (node != NULL) {
    if (router[node->id].visited == 0) {
      head = addtoL(head, node->id);
      *routers = router;
      head = DFS_Aux(routers, head, node->id, l, e);
      }
    node = node->next;
  }
  *routers = router;
  return head;
}

void DFS(struct Vertice **routers, int f, int e) {
  struct Vertice *router = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  router = *routers;
  int aux = 0;
  int aux1 = 0;
  struct node_l* head = NULL, *output = NULL;
  struct node_p* output2 = NULL;
  struct node_b* back;
  head = addtoL(head, 1);
  *routers = router;
  head = DFS_Aux(routers, head, 1, f, e);
  while (head != NULL) {
    back = router[head->id].back;
    while (back != NULL) {
      if (router[back->id].visited != 1) {
        if (head->id > 1+f+e && back->id > 1+f && head->id - back->id == e) {
          output = addtoL(output, back->id);
          aux1++;
        }
        else {
          if (back->id > 1+f) {
            output2 = addtoP(output2, back->id - e, head->id);
            aux++;
          }
          else if (back->id != 0) {
            output2 = addtoP(output2, back->id, head->id);
            aux++;
          }
        }
      }
      back = back->next;
    }
    head = head->next;
  }
  int ve[aux];
  int vl[aux1];
  int i = 0;
  if (output == NULL) {
    printf("\n");
  }
  else {
    aux1 = 0;
    while (output != NULL) {
      vl[aux1] = output->id;
      aux1++;
      output = output->next;
    }
    qsort (vl, sizeof(vl)/sizeof(*vl), sizeof(*vl), comp);
    for (i = 0; i < aux1; i++) {
      printf("%d\n", vl[i]);
    }
  }
  if (aux != 0) {
    aux = 0;
    while (output2 != NULL) {
      ve[aux] = output2->id * 10 + output2->id1;
      aux++;
      output2 = output2->next;
    }
    qsort (ve, sizeof(ve)/sizeof(*ve), sizeof(*ve), comp);
    for (i = 0; i <= aux-1; i++) {
      printf("%d %d\n", ve[i]/10, ve[i]%10);
    }
  }
}


int main() {
  int f, e, t;
  scanf("%d %d %d", &f, &e, &t);
  struct Vertice *routers = can_fail_malloc(sizeof(struct Vertice)*((2*e)+f+1));
  int *vector = can_fail_malloc(sizeof(int)*((2*e)+f-1));
  readInput(&routers, &vector, f, e, t);
  Relabel_to_Front(&routers, &vector, f, e);
  BackVetices(&routers, f, e);
  printGraph(&routers, &vector, f, e);
  DFS(&routers, f, e);
  return 0;
}
