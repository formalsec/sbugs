#include <stdio.h>
#include <stdlib.h>

/*Declaration of constants*/
#define OPEN 100
#define CLOSED 101
#define CUT 102
#define CONNECTED 103
#define WHITE 104
#define BLACK 105

/*Definition of new types of variables*/
typedef struct transp {
  int from;
  int to;
  int flow;
  int limit;
  int status;
  char cut;
} transp;

typedef struct vert {
  char type;
  int height;
  int current;
  int flow;
  int limit;
  int n_in;
  int n_out;
  int available;
  int column;
  transp** entry;
  transp** out;
  int status;
} vert;

typedef struct inp {
  int pos;
  int n_e;
} inp;

typedef struct ret {
  int n_arcs;
  int n_verts;
} ret;

/*Declaration of functions*/
void parse_input(vert* array, int, int);
void parse_matrix(vert* array, transp* array2, int, int, int);
inp find_next_vert(vert* array, int, inp);
inp push(vert* array, int, inp);
ret find_arcs(vert* array, int* array4, int, transp** array3, int, int* cut_v, int, int);
int check_if(vert* verts, int, int*, int);

int main() {
  int n_vert, n_sup, n_chp, n_transp, i, j;
  int sum, first;
  inp data;
  ret ret;
  vert* verts;
  transp* arcs;
  transp** cut;
  int* positions;
  int* cut_v;
  int* all_v;
  int aux;
  transp* aux_t;

  scanf("%d %d %d", &n_sup, &n_chp, &n_transp);
	n_vert = n_sup + n_chp + 1;

  /*Creates and saves all the verts*/
	verts = (vert *) malloc((n_vert + 1)*sizeof(vert));
  arcs = (transp *) malloc((n_transp + n_sup + 1)*sizeof(transp));

	parse_input(verts, n_sup, n_vert);

	/*Initializes all the values of the matrix and sorts them
	by number of connections*/
	parse_matrix(verts, arcs, n_transp, n_vert, n_sup);

  /*Push-Relabel algorithm*/
  data.pos = 0;
  data.n_e = n_sup;
  while (data.n_e != 0) {
    if (data.pos == 1 || data.pos == 0 || verts[data.pos].current == 0) {
      data = find_next_vert(verts, n_vert, data);
    }

    data = push(verts, data.pos, data);
  }

  positions = (int *) malloc(n_vert*sizeof(int));
  positions[0] = 1;
  cut = (transp **) malloc((n_transp+1)*sizeof(transp*));
  cut_v = (int *) malloc(n_vert*sizeof(int));
  ret = find_arcs(verts, positions, 1, cut, 0, cut_v, 0, n_vert);

  all_v = (int *) malloc(ret.n_verts*sizeof(int));
  j=0;
  for(i=0;i<ret.n_verts;i++) {
    j += check_if(verts, cut_v[i], all_v, j);
  }

  ret.n_verts = j;

  /*Sorting algorithms*/
  for(i=0;i<ret.n_verts;i++) {
    for(j=i;j>0;j--) {
      if(all_v[j] < all_v[j-1]) {
        aux = all_v[j-1];
        all_v[j-1] = all_v[j];
        all_v[j] = aux;
      }
    }
  }

  for(i=0;i<ret.n_arcs;i++) {
    for(j=i;j>0;j--) {
      if(cut[j]->from < cut[j-1]->from) {
        aux_t = cut[j-1];
        cut[j-1] = cut[j];
        cut[j] = aux_t;
      } else if (cut[j]->from == cut[j-1]->from && cut[j]->to < cut[j-1]->to) {
        aux_t = cut[j-1];
        cut[j-1] = cut[j];
        cut[j] = aux_t;
      }
    }
  }

  sum = 0;
  /*Output printing*/
  printf("%d\n", verts[1].flow);
  for(i=0;i<ret.n_verts;i++) {
    sum += verts[all_v[i]].flow;
  }

  for(i=0;i<ret.n_arcs;i++) {
    sum += cut[i]->flow;
  }

  first = 0;

  for(i=0;i<ret.n_verts;i++) {
    if(first) {
      printf(" ");
    }
    printf("%d", cut_v[i]);
  }
  printf("\n");


  if(sum == verts[1].flow) {
    for(i=0;i<ret.n_arcs;i++) {
      printf("%d %d\n", cut[i]->from, cut[i]->to);
    }
  }

  /*test printing
	for(i=0;i<=n_vert;i++) {
		printf("pos:%d height:%d %d/%d\n", i, verts[i].height, verts[i].flow, verts[i].limit);
	}

	for(i=0;i<=n_vert;i++) {
		for(j=0;j<verts[i].n_out;j++) {
			printf("%d %d %d/%d\n", verts[i].out[j]->from, verts[i].out[j]->to, verts[i].out[j]->flow, verts[i].out[j]->limit);
		}
	}*/

  /*This part frees the allocated memmory*/
  free(positions);
  for(i=0;i<=n_vert;i++) {
    free(verts[i].out);
    free(verts[i].entry);
  }
  free(verts);
  free(arcs);
  free(cut_v);
  free(cut);
  free(all_v);

  return 0;
}

void parse_input(vert* verts, int n_sup, int n_vert) {
	int i;

	/*Inputs for the suppliers*/
	for (i = 2; i <= n_sup + 1; i++) {
		scanf("%d", &verts[i].limit);
		verts[i].current = verts[i].limit;
    verts[i].flow = 0;
		verts[i].type = 's';
    verts[i].height = n_vert;
		verts[i].n_in = 0;
    verts[i].n_out = 0;
    verts[i].entry = (transp **) malloc(sizeof(transp*));
    verts[i].out = (transp **) malloc(sizeof(transp*));
    verts[i].status = WHITE;
	}

	/*Inputs for the checkpoints*/
	for (i = n_sup+2; i <= n_vert; i++) {
		/* int ou long*/
    scanf("%d", &verts[i].limit);
		verts[i].current = 0;
    verts[i].flow = 0;
		verts[i].type = 'v';
    verts[i].height = 0;
		verts[i].n_in = 0;
    verts[i].n_out = 0;
    verts[i].entry = (transp **) malloc(sizeof(transp*));
    verts[i].out = (transp **) malloc(sizeof(transp*));
    verts[i].status = WHITE;
	}

	/*Initialization of the supermarket*/
	verts[1].type = 't';
  verts[1].height = 0;
	verts[1].flow = 0;
  verts[1].n_in = 0;
  verts[1].n_out = 0;
  verts[1].entry = (transp **) malloc(sizeof(transp*));
}

void parse_matrix(vert* verts, transp* arcs, int n_transp, int n_vert, int n_sup) {
	int i;

	/*Saving the arrays*/
	for (i = 0; i < n_transp; i++) {
		transp path;

		scanf("%d %d %d", &path.from, &path.to, &path.limit);
		path.flow = 0;
		path.status = OPEN;
    path.cut = CONNECTED;
    arcs[i] = path;
    verts[path.from].out[verts[path.from].n_out] = &arcs[i];
		verts[path.from].n_out++;
    verts[path.from].out = (transp**) realloc(verts[path.from].out, (verts[path.from].n_out + 1)*sizeof(transp*));
    verts[path.to].entry[verts[path.to].n_in] = &arcs[i];
    verts[path.to].n_in++;
    verts[path.to].entry = (transp**) realloc(verts[path.to].entry, (verts[path.to].n_in + 1)*sizeof(transp*));
  }

  verts[0].height = n_vert;
  verts[0].flow = 0;
  verts[0].current = 1;
  verts[0].n_out = 0;
  verts[0].type = 0;
  verts[0].out = (transp**) malloc(sizeof(transp*));

  for(i=0;i<n_sup;i++) {
    transp aux;

    verts[0].limit += verts[i+2].limit;
    aux.from = 0;
    aux.to = i+2;
    aux.limit = verts[i+2].limit;
    aux.flow = aux.limit;
    aux.cut = CONNECTED;
    arcs[n_transp+i] = aux;

    verts[i+2].current = aux.limit;
    verts[0].flow += aux.limit;
    verts[0].out[verts[0].n_out] = &arcs[n_transp+i];
    verts[0].n_out++;
    verts[0].out = (transp**) realloc(verts[0].out, (verts[0].n_out + 1)*sizeof(transp*));
    verts[i+2].entry[verts[i+2].n_in] = &arcs[n_transp+i];
    verts[i+2].n_in++;
    verts[i+2].entry = (transp**) realloc(verts[i+2].entry, (verts[i+2].n_in + 1)*sizeof(transp*));
  }
}

inp find_next_vert(vert* verts, int n_vert, inp n_e) {
  int i;
  inp aux;
  aux = n_e;

  for(i=2;i<=n_vert;i++) {
    if(verts[i].current > 0) {
      aux.pos = i;
      return aux;
    }
  }

  aux.n_e = 0;
  return aux;
}

inp push(vert* verts, int pos, inp n_e) {
  int i;
  int to;
  int temp_flow, temp;
  inp aux;
  aux = n_e;

  /*Tries to push forward*/
  for(i=0;i<verts[pos].n_out;i++) {
    to = verts[pos].out[i]->to;
    if(verts[pos].out[i]->status == OPEN && verts[to].height < verts[pos].height && (verts[to].limit-verts[to].flow > 0 || verts[to].type == 't') && verts[pos].limit-verts[pos].flow > 0) {
      if (verts[pos].current>verts[pos].limit-verts[pos].flow) {
        temp = verts[pos].limit-verts[pos].flow;
      } else {
        temp = verts[pos].current;
      }

      if(verts[pos].out[i]->limit-verts[pos].out[i]->flow <= temp) {
        temp_flow = verts[pos].out[i]->limit-verts[pos].out[i]->flow;
      } else {
        temp_flow = temp;
      }

      if(verts[to].current == 0) {
        aux.n_e++;
      }

      if(verts[to].limit-verts[to].flow < temp_flow && verts[to].type != 't') {
        temp_flow = verts[to].limit-verts[to].flow;
        verts[pos].out[i]->flow += temp_flow;
        verts[pos].current -= temp_flow;
        verts[pos].flow += temp_flow;
        verts[to].current += temp_flow;
      } else {
        verts[pos].out[i]->flow += temp_flow;
        verts[pos].current -= temp_flow;
        verts[pos].flow += temp_flow;
        verts[to].current += temp_flow;
      }

      if(verts[to].type == 't') {
        verts[to].flow += verts[to].current;
        verts[to].current = 0;
        aux.n_e--;
      }

      if(verts[pos].current == 0) {
        aux.n_e--;
      }

      if(verts[pos].out[i]->flow == verts[pos].out[i]->limit) {
        verts[pos].out[i]->status = CLOSED;
      }

      aux.pos = to;
      return aux;
    }
  }

  /*tries to push back*/
  for(i=0;i<verts[pos].n_in;i++) {
    to = verts[pos].entry[i]->from;
    if(verts[to].height < verts[pos].height) {

      if(verts[to].current == 0) {
        aux.n_e++;
      }

      if(verts[pos].current <= verts[pos].entry[i]->flow) {
        verts[pos].entry[i]->flow -= verts[pos].current;
        verts[to].flow -= verts[pos].current;
        verts[to].current += verts[pos].current;
        verts[pos].current = 0;
      } else {
        verts[pos].current -= verts[pos].entry[i]->flow;
        verts[to].flow -= verts[pos].entry[i]->flow;
        verts[to].current += verts[pos].entry[i]->flow;
        verts[pos].entry[i]->flow = 0;
      }

      if(verts[pos].current == 0) {
        aux.n_e--;
      }

      if(verts[pos].entry[i]->flow != verts[pos].entry[i]->limit) {
        verts[pos].entry[i]->status = OPEN;
      }

      aux.pos = to;

      return aux;
    }
  }

  verts[pos].height++;

  aux.pos = pos;

  return aux;
}

ret find_arcs(vert* verts, int* positions, int n_parse, transp** cut, int n_cut, int* cut_v, int nv, int n_vert) {
  int i, j, n;
  int aux_a = n_cut;
  int* next_batch;
  ret ret;
  next_batch = (int*) malloc(n_vert*sizeof(int));
  n = 0;

  for(i=0;i<n_parse;i++) {
    if(verts[positions[i]].flow == verts[positions[i]].limit && positions[i] != 0 && verts[positions[i]].type != 's') {
      cut_v[nv] = positions[i];
      nv++;
    } else {
      for(j=0;j<verts[positions[i]].n_in;j++) {
        int pos = positions[i];
        if(verts[verts[pos].entry[j]->from].status == WHITE) {
          if(verts[pos].entry[j]->flow < verts[pos].entry[j]->limit) {
            next_batch[n] = verts[pos].entry[j]->from;
            n++;
          } else {
            cut[aux_a] = verts[pos].entry[j];
            aux_a++;
          }
        }
      }
    }
  }

  for(i=0;i<n;i++) {
    positions[i] = next_batch[i];
  }
  free(next_batch);

  if(n_parse == 0) {
    ret.n_arcs = aux_a;
    ret.n_verts = nv;
    return ret;
  } else {
    return find_arcs(verts, positions, n, cut, aux_a, cut_v, nv, n_vert);
  }
}

int check_if(vert* verts, int pos, int* all_v, int j) {
  int i;
  for(i=0;i<verts[pos].n_in;i++) {
    if(verts[pos].entry[i]->flow < verts[pos].entry[i]->limit && (verts[verts[pos].entry[i]->from].flow < verts[verts[pos].entry[i]->from].limit || verts[verts[pos].entry[i]->from].type == 's')) {
      all_v[j] = pos;
      return 1;
    }
  }

  return 0;
}
