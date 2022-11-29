#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

/*
Grupo - 33
90702 - Ana David
90733 - João Veloso
*/

/*Definition of constants and new types of variables*/
const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;
const int RED = 3;

typedef struct arc {
  int position;
  char type;
} arc;

typedef struct node {
  int color;
  int d;
  int low;
  int routes;
  int connections;
  arc *connected;
  int parent;
  int child;
} node;

/*Declaration of functions*/
int search_next(node, node *array, int);
void update_nodes(int, int, node *array);
int backtrack(node, node *array);
int search_low(node, node *array);
int see_if_pair(node, node *array);
int search_available(node *array, int);
int is_connector(int, node *array);
int count_sub_nets(node * array, int, int);
int new_search(node, node *array);

int main() {
  int n_verts, n_arcs;
  int sub_bot = 0;
  int i, k;
  int *index = can_fail_malloc(1*sizeof(int));
  /*This part is the parser*/
  scanf("%d", &n_verts);
  scanf("%d", &n_arcs);

  /*Initializing the array*/
  node vert_list[n_verts + 1];
  for (i=1;i<=n_verts;i++) {
    node node;
    node.color = WHITE;
    node.d = 0;
    node.low = 0;
    node.routes = 0;
    node.connections = 0;
    node.connected = can_fail_malloc(1*sizeof(arc));
    node.parent = 0;
    node.child = 0;
    vert_list[i] = node;
  }

  /*Reads all the arcs and saves them*/
  for (i=0;i<n_arcs;++i) {
    int pos1 = 0, pos2 = 0;
    scanf("%d %d", &pos1, &pos2);
    arc arc1, arc2;
    arc1.position = pos2;
    arc1.type = 1;
    arc2.position = pos1;
    arc2.type = 1;
    vert_list[pos1].connected[vert_list[pos1].connections] = arc1;
    vert_list[pos1].connections++;
    vert_list[pos1].connected = can_fail_realloc(vert_list[pos1].connected, (vert_list[pos1].connections + 1)*sizeof(arc));
    vert_list[pos2].connected[vert_list[pos2].connections] = arc2;
    vert_list[pos2].connections++;
    vert_list[pos2].connected = can_fail_realloc(vert_list[pos2].connected, (vert_list[pos2].connections + 1)*sizeof(arc));
  }

  /*This part is the Tarjan*/
  int counter = 0;
  int step = 0;
  int position = 1;
  int red_counter = 0;
  index[sub_bot] = 0;
  while(counter<n_verts) {
    if (index[sub_bot] < position) {
      index[sub_bot] = position;
    }

    /*Searches for the next available node*/
    int next = search_next(vert_list[position], vert_list, n_verts);
    if(next != -1) {
      if (vert_list[position].d == 0) {
        step++;
        vert_list[position].d = step;
        vert_list[position].low = step;
      }
      /*Updates the color and connections of the nodes*/
      update_nodes(position, next, vert_list);
    } else {
      if (vert_list[position].d == 0) {
        step++;
        vert_list[position].d = step;
        vert_list[position].low = step;
      }
      /*If no nodes are available, backtracks*/
      next = backtrack(vert_list[position], vert_list);
      vert_list[position].color = BLACK;
      counter++;
      if (next != -1) {
        /*if a node backtracks we see if we need to update his low*/
        vert_list[position].low = search_low(vert_list[position], vert_list);
      } else {
        /*if we can't backtrack finds the next available node in another net*/
        vert_list[position].low = see_if_pair(vert_list[position], vert_list);
        next = search_available(vert_list, n_verts);
        sub_bot++;
        index = can_fail_realloc(index, (sub_bot+1)*sizeof(int));
        index[sub_bot] = 0;
      }

      /*This part sees which nodes are connectors*/
      red_counter = red_counter + is_connector(position, vert_list);
    }

    position = next;
  }

  /*organizing the indicators of each subnet*/
  int index2[n_verts];
  for (k=1;k<=n_verts;k++) {
    index2[k] = -1;
  }
  for (k=0;k<sub_bot;k++) {
    index2[index[k]] = index[k];
  }

  /*Counts how many subnets are there*/
  for(i=1;i<=n_verts;i++) {
    if (vert_list[i].color != RED) {
      vert_list[i].color = WHITE;
    }
  }
  int max_net = count_sub_nets(vert_list, n_verts, red_counter);

  /*This part is the final output*/
  printf("%d\n", sub_bot);
  int prue = 0;
  for (k=1;k<n_verts+1;k++) {
    if (prue) {
      printf(" ");
      prue = 0;
    }
    if (index2[k]!=-1) {
      prue = 1;
      printf("%d", index2[k]);
    }
  }
  printf("\n");
  printf("%d\n", red_counter);
  printf("%d\n", max_net);

  /*This part frees the allocated memory*/
  for(i=1;i<=n_verts;i++) {
    free(vert_list[i].connected);
  }
  free(index);

  return 0;
}

/*Auxiliary functions*/
int search_next(node current, node *vert_list, int n_verts) {
  int i;

  for (i=0;i<current.connections;i++) {
    if(current.connected[i].type == 1 && vert_list[current.connected[i].position].color == WHITE) {
      return current.connected[i].position;
    }
  }

  return -1;
}

void update_nodes(int position, int next, node *vert_list) {
  int i;

  vert_list[position].routes++;
  vert_list[position].color = GREY;
  vert_list[next].color = GREY;

  for (i=0;i<vert_list[position].connections;i++) {
    if (vert_list[position].connected[i].position == next) {
      vert_list[position].connected[i].type = 't';
      vert_list[position].child = next;
    }
  }
  for (i=0;i<vert_list[next].connections;i++) {
    if (vert_list[next].connected[i].position == position) {
      vert_list[next].connected[i].type = 'b';
      vert_list[next].parent = position;
    }
  }
}

int backtrack(node current, node *vert_list) {
  if (current.parent != 0 && vert_list[current.parent].color != RED)  {
    return current.parent;
  }

  return -1;
}

int search_low(node current, node *vert_list) {
  int i;
  int low = current.low;

  for (i=0;i<current.connections;i++) {
    if (current.connected[i].type == 't') {
      if (vert_list[current.connected[i].position].low < low) {
        low = vert_list[current.connected[i].position].low;
      }
    } else {
      if (vert_list[current.connected[i].position].d < low && vert_list[current.connected[i].position].connections > 1) {
        low = vert_list[current.connected[i].position].d;
      }
    }
  }

  return low;
}

int see_if_pair(node current, node *vert_list) {
  if (current.connected[0].type == 't' && current.connections == 1 && vert_list[current.connected[0].position].connections == 1) {
      return vert_list[current.connected[0].position].low;
    }

  return current.low;
}

int search_available(node *vert_list, int n_verts) {
  int i;

  for (i=1;i<=n_verts;i++) {
    if (vert_list[i].color == WHITE) {
      return i;
    }
  }

  return -1;
}

int is_connector(int position, node *vert_list) {
  int i;

  if (vert_list[position].routes > 1 && vert_list[position].parent == 0 && vert_list[position].color != RED) {
    vert_list[position].color = RED;
    return 1;
  } else if (vert_list[position].connections > 1 && vert_list[position].routes > 0 && vert_list[position].parent != 0 && vert_list[position].color != RED) {
    for (i=0;i<vert_list[position].connections;i++) {
      if (vert_list[position].connected[i].type == 't' && vert_list[vert_list[position].connected[i].position].low >= vert_list[position].d) {
        vert_list[position].color = RED;
        return 1;
      }
    }
  }

  return 0;
}

int count_sub_nets(node * vert_list, int n_verts, int red_counter) {
  int max_net = 1;
  int current_net = 1;
  int counter = red_counter;
  int position = search_available(vert_list, n_verts);;

  while(counter<n_verts) {
    /*Searches for the next available node*/
    int next = new_search(vert_list[position], vert_list);
    if(next != -1) {
      /*Updates the color and connections of the nodes*/
      vert_list[position].color = GREY;
      vert_list[next].color = GREY;
      vert_list[next].parent = position;
      current_net++;
    } else {
      /*If no nodes are available, backtracks*/
      next = backtrack(vert_list[position], vert_list);
      vert_list[position].color = BLACK;
      counter++;
      if (next == -1) {
        /*if we can't backtrack finds the next available node in another net*/
        next = search_available(vert_list, n_verts);
        if (current_net>max_net) {
          max_net = current_net;
        }
        current_net = 1;
      }
    }

    position = next;
  }

  return max_net;
}

int new_search(node current, node *vert_list) {
  int i;

  for (i=0;i<current.connections;i++) {
    if(vert_list[current.connected[i].position].color == WHITE) {
      return current.connected[i].position;
    }
  }

  return -1;
}
