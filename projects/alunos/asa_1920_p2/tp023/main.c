#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct point {
    int x;
    int y;
} point;

int bpm(int citizen, int store, int *sol, int index, int seen[store], int matchR[store]) {
  int i;

  for (i = 0; i < store; i++) {
    if (*(sol + (index)*store + i) == 1 && seen[i] == 0) {
      seen[i] = 1;
      if (matchR[i] < 0 || bpm(citizen, store, sol, matchR[i], seen, matchR)) {
        matchR[i] = index; 
        return 1; 
      }
    }
  }
  return 0;
}


int maxBPM(int citizen, int store, int *sol) {
  int i;
  int matchR[store]; 

  memset(matchR, -1, sizeof(matchR)); 

  int res = 0;

  for (i = 0; i < citizen; i++) {
    int seen[store];
    memset(seen, 0, sizeof(seen)); 

    if (bpm(citizen, store, sol, i, seen, matchR)) {
      res++;
    }
  }
  return res;
}

int makePath(int avenue, int street, int *graph, int cx, int cy, int sx, int sy) {
  if (cx == sx && cy == sy) {
    return 1;
  }
  if (*(graph + (cx)*street + (cy)) == 1) {
    return 0;
  }

  *(graph + (cx)*street + (cy)) = 2;

  if (cx-sx >= 0 && cx-sx >= cy-sy && cx-sx >= sy-cy) {
    if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
      if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
        return 1;
      }
    }
    if (cy-sy >= 0) {
      if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
        if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
          return 1;
        }
      }
      if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
        if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
          return 1;
        }
      }      
    } 
    else {
      if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
        if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
          return 1;
        }
      } 
      if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
        if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
          return 1;
        }
      }     
    }
    if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
      if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
        return 1;
      }
    }       
  }

  if (cx-sx < 0 && cx-sx <= cy-sy && cx-sx <= sy-cy) {
    if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
      if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
        return 1;
      }
    }
    if (cy-sy >= 0) {
      if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
        if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
          return 1;
        }
      }
      if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
        if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
          return 1;
        }
      }      
    } 
    else {
      if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
        if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
          return 1;
        }
      } 
      if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
        if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
          return 1;
        }
      }     
    }
    if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
      if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
        return 1;
      }
    }     
  }

  if (cy-sy >= 0 && cy-sy >= cx-sx && cy-sy >= sx-cx) {
    if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
      if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
        return 1;
      }
    }  
    if (cx-sx >= 0) {
      if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
          return 1;
        }
      } 
      if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
          return 1;
        }
      }           
    }
    else {
      if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
          return 1;
        }
      } 
      if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
          return 1;
        }
      }     
    }
    if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
      if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
        return 1;
      }
    }    
  }

  if (cy-sy <= 0 && cy-sy <= cx-sx && cy-sy <= sx-cx) {
    if (cy < street-1 && *(graph + (cx)*street + (cy+1)) != 2 && *(graph + (cx)*street + (cy+1)) != 3){
      if(makePath(avenue, street, graph, cx, cy+1, sx, sy)) {
        return 1;
      }
    } 
    if (cx-sx >= 0) {
      if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
          return 1;
        }
      } 
      if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
          return 1;
        }
      }           
    }
    else {
      if (cx < avenue-1 && *(graph + (cx+1)*street + (cy)) != 2 && *(graph + (cx+1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx+1, cy, sx, sy)) {
          return 1;
        }
      } 
      if (cx > 0 && *(graph + (cx-1)*street + (cy)) != 2 && *(graph + (cx-1)*street + (cy)) != 3){
        if(makePath(avenue, street, graph, cx-1, cy, sx, sy)) {
          return 1;
        }
      }     
    }
    if (cy > 0 && *(graph + (cx)*street + (cy-1)) != 2 && *(graph + (cx)*street + (cy-1)) != 3){
      if(makePath(avenue, street, graph, cx, cy-1, sx, sy)) {
        return 1;
      }
    }
  }

  return 0;

}



int main(int argc, char* argv[]) {

  int avenue;
  int street;
  int store;
  int citizen;
  int av;
  int st;
  int i;
  int j;
  int c_count = 0;
  int s_count = 0;

  scanf("%d %d", &avenue, &street);
  scanf("%d %d", &store, &citizen);

  point citizens[citizen];
  point stores[store];

  int *graph = (int *)can_fail_malloc(avenue * street * sizeof(int)); 
  int *graphAux = (int *)can_fail_malloc(avenue * street * sizeof(int)); 



  for (i = 0; i < avenue; i++) {
    for (j = 0; j < street; j++) {
      *(graph + i*street + j) = 0;
    }
  }

  for (i = 0; i < store; i++) {
    scanf("%d %d", &av, &st);
    if (*(graph + (av-1)*street + (st-1)) == 1) {
      stores[i].x = -1;
      stores[i].y = -1;     
    }
    else {
      *(graph + (av-1)*street + (st-1)) = 1;
      stores[i].x = av-1;
      stores[i].y = st-1;
      s_count++;
    }
  }  

  for (i = 0; i < citizen; i++) {
    scanf("%d %d", &av, &st);
    if (*(graph + (av-1)*street + (st-1)) == 2 || *(graph + (av-1)*street + (st-1)) == 3) {
      citizens[i].x = -1;
      citizens[i].y = -1;
    }
    else{
      if (*(graph + (av-1)*street + (st-1)) == 1) {
        *(graph + (av-1)*street + (st-1)) = 3;
      }
      else {  
        *(graph + (av-1)*street + (st-1)) = 2;
      }
      citizens[i].x = av-1;
      citizens[i].y = st-1;
      c_count++;
    }
  }

  int *sol = (int *)can_fail_malloc(c_count * s_count * sizeof(int)); 
  int c = 0;

  for (i = 0; i < citizen; i++) {
    for (j = 0; j < store; j++) {
      if ((citizens[i].x != -1 && citizens[i].y != -1)) {
        if (stores[j].x != -1 && stores[j].y != -1) {
          if (*(graph + (stores[j].x)*street + (stores[j].y)) == 3 || *(graph + (citizens[i].x)*street + (citizens[i].y)) == 3) {
            if (stores[j].x == citizens[i].x && stores[j].y == citizens[i].y){
               *(sol + c++) = 1;
            }
            else {
              *(sol + c++) = 0;
            }
          }
          else {
            memcpy (graphAux, graph, avenue * street * sizeof(int));           
            if (makePath(avenue, street, graphAux, citizens[i].x, citizens[i].y, stores[j].x, stores[j].y)) {
              *(sol + c++) = 1;
            }
            else {
              *(sol + c++) = 0;
            }
          }
        }
      }
    }
  } 
  printf("%d\n", maxBPM(c_count, s_count, sol));

  free(graph);
  free(graphAux);
  free(sol);

  return 0;

}



















