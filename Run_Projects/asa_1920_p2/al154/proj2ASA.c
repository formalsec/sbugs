#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*The avenues are numbered from top to bottom from 1 to M and streeds are numbered from right to left from 1 to N*/

void add_node_to_visited (int avenue, int street, int *crossover_list_pointer_used, int *visited_pointer0, int *visited_pointer1, int *empty_spot_in_visited_pointer, int aux_empty_spot_in_visited) {
  *crossover_list_pointer_used = 3;
  *visited_pointer0 = avenue;
  *visited_pointer1 = street;
  *empty_spot_in_visited_pointer = aux_empty_spot_in_visited;
}

/*side: 0 - up, 1 - down, 2 - right, 3 - left*/
void can_move (int side, int avenue, int street, int *queue_pointer0, int *queue_pointer1,int *crossover_list_pointer_used,int *empty_spot_in_queue_pointer,int aux_empty_spot_in_queue,int *crossover_list_pointer_caller_avenue,int *crossover_list_pointer_caller_street) {
  if (side == 0) { /*Up*/
    *queue_pointer0 = avenue-1;
    *queue_pointer1 = street;
  }
  else if (side == 1) { /*Down*/
    *queue_pointer0 = avenue+1;
    *queue_pointer1 = street;
  }
  else if (side == 2) { /*Right*/
    *queue_pointer0 = avenue;
    *queue_pointer1 = street-1;
  }
  else if (side == 3) { /*Left*/
    *queue_pointer0 = avenue;
    *queue_pointer1 = street+1;
  }
  *crossover_list_pointer_used = 3;
  *empty_spot_in_queue_pointer = aux_empty_spot_in_queue;
  *crossover_list_pointer_caller_avenue = avenue;
  *crossover_list_pointer_caller_street = street;
}

void read_next_node (int *value_to_read_in_queue_pointer,int aux_value_to_read_in_queue,int *avenue_pointer, int *street_pointer, int queue_value0, int queue_value1) {
  *value_to_read_in_queue_pointer = aux_value_to_read_in_queue;
  *avenue_pointer = queue_value0;
  *street_pointer = queue_value1;
}


int main () {

  int avenues, streets, supermarkets, citizens, crossovers_number;
  int avenue, street;
  int checked_supermarkets = 0, checked_citizens = 0;
  int max_citizens = 0; /*It will keep how much citizens can go out at the same time*/
  int i, j;
  /*Read the number of avenues and streets*/
  char nums[100];
  fgets(nums,100,stdin);
  char *token;
  token = strtok (nums," ");
  avenues = atoi(token);
  streets = atoi(strtok(NULL, " "));
  crossovers_number = avenues * streets;

  struct crossover {
    char description[12];
    int used;   /*-3 for not used, 3 for used and 4 for used in the algorithm*/
    int caller_avenue;
    int caller_street;
  };
  typedef struct crossover crossover;
  crossover crossovers_list[avenues+1][streets+1];

  for (i = 1; i <= avenues; i++) {
    for (j = 1; j <= streets; j++) {
      strcpy(crossovers_list[i][j].description,"");
      crossovers_list[i][j].used = -3; /*-3 for not used, 3 for used*/
      crossovers_list[i][j].caller_avenue = -1;
      crossovers_list[i][j].caller_street = -1;
    }
  }

  /*Read the number of supermarkets and citizens*/
  fgets(nums,100,stdin);
  token = strtok (nums," ");
  supermarkets = atoi(token);
  citizens = atoi(strtok(NULL, " "));
  int adresses[citizens][2];
  int reverse_adresses[citizens][2];
  char location[supermarkets][10];
  char adress[citizens][10];
  for (i = 0; i < supermarkets; i++) {
    fgets(location[i],100,stdin);
    token = strtok (location[i]," ");
    avenue = atoi(token);
    street = atoi(strtok(NULL, " "));
    if (strcmp(crossovers_list[avenue][street].description,"supermarket") == 0) {
      checked_supermarkets++;
    }
    strcpy(crossovers_list[avenue][street].description,"supermarket");
    crossovers_list[avenue][street].used = -3;
  }
  for (i = 0; i < citizens; i++) {
    fgets(adress[i],100,stdin);
    token = strtok (adress[i]," ");
    avenue = atoi(token);
    street = atoi(strtok(NULL, " "));
    if (strcmp(crossovers_list[avenue][street].description,"supermarket") == 0) {
      strcpy(crossovers_list[avenue][street].description,"both");
      checked_citizens++;
      checked_supermarkets++;
      max_citizens++;
    }
    else if (strcmp(crossovers_list[avenue][street].description,"citizen") == 0) {
      checked_citizens++;
    }
    else if (strcmp(crossovers_list[avenue][street].description,"both") == 0) {
      checked_citizens++;
    }
    else {
      strcpy(crossovers_list[avenue][street].description,"citizen");
      adresses[i][0] = avenue;
      adresses[i][1] = street;
    }
    crossovers_list[avenue][street].used = 3;
  }

  int save_checked_supermarkets = checked_supermarkets;
  int save_checked_citizens = checked_citizens;
  int save_max_citizens = max_citizens;
  int visited[crossovers_number+1][2];
  int empty_spot_in_visited = 0;
  int aux_empty_spot_in_visited = empty_spot_in_visited + 1;
  int without_path = 0, ended = 0;
  int first_max_citizens;
  int y,z;
  int queue[crossovers_number+1][2];
  int empty_spot_in_queue = 0;
  int aux_empty_spot_in_queue = empty_spot_in_queue + 1;
  int aux_avenue = avenue;
  int aux_street = street;
  int value_to_read_in_queue = 0; /*This is the index next in the queue - using this I do not have to clean the queue at every iteration*/
  int aux_value_to_read_in_queue = value_to_read_in_queue + 1;
  i = 0;
  ended = 0;
  without_path = 0;
  for (z = 0; z < 2; z++) {
    while (checked_supermarkets != supermarkets && checked_citizens != citizens && i < citizens-save_checked_citizens) {
      avenue = adresses[i][0];
      street = adresses[i][1];
      queue[0][0] = avenue;
      queue[0][1] = street;
      empty_spot_in_queue++;
      crossovers_list[avenue][street].caller_avenue = -1; /*I do this so I can, at the end of the program, recognize the first vertice of the path*/
      crossovers_list[avenue][street].caller_street = -1;
      visited[empty_spot_in_visited][0] = -1;
      while (ended == 0 && without_path == 0) {
        if (strcmp(crossovers_list[avenue][street].description,"supermarket") == 0) {   /*I´m at the supermarket - the end target*/
          aux_empty_spot_in_visited = empty_spot_in_visited + 1;
          add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
          checked_supermarkets++;
          max_citizens++;
          ended = 1;
          break;
        }
        if (avenue == 1) { /*First line*/
          if (street == 1) { /*Right limit - Right up corner*/
            if (crossovers_list[avenue][street+1].used == 3 && crossovers_list[avenue+1][street].used == 3) { /*If I can not go left or down I will go back*/
              if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                without_path = 1;
              }
              else { /*I am out of options and the queue is not "empty"*/
                aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
              }
            }
            else {
              if (crossovers_list[avenue][street+1].used == -3) { /*I can go left*/
                if (crossovers_list[avenue+1][street].used == -3) { /*I can go left and down*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can only go left*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else { /*I can not go Left*/
                if (crossovers_list[avenue+1][street].used == -3) { /*I can only go down*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
            }
          }
          else if (street == streets) { /*Left limit - Left up corner*/
              if (crossovers_list[avenue][street-1].used == 3 && crossovers_list[avenue+1][street].used == 3) { /*If I can not go right or down I will go back*/
                if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                  without_path = 1;
                }
                else { /*I am out of options and the queue is not "empty"*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else {
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go right*/
                  if (crossovers_list[avenue-1][street].used == -3) { /*I can go right and down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can only go right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can not go right*/
                  if (crossovers_list[avenue+1][street].used == -3) { /*I can only go down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
          }
          else { /*Up line (except corners)*/
              if (crossovers_list[avenue][street-1].used == 3 && crossovers_list[avenue+1][street].used == 3 && crossovers_list[avenue][street+1].used == 3) { /*If I can not go right, down or left, I will go back*/
                if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out op options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                  without_path = 1;
                }
                else { /*I am out op options and the queue is not "empty"*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else {
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go right*/
                  if (crossovers_list[avenue+1][street].used == -3) { /*I can go right and down*/
                    if (crossovers_list[avenue][street+1].used == -3) { /*I can go right, down and left*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                    else { /*I can only go right and down*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                  }
                  else { /*I can go right but not down*/
                    if (crossovers_list[avenue][street+1].used == -3) { /*I can go right and left but not down*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                    else { /*I can only go right*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                  }
                }
                else { /*I can not go right*/
                  if (crossovers_list[avenue+1][street].used == -3) { /*I can go down but not right*/
                    if (crossovers_list[avenue][street+1].used == -3) { /*I can go left or down but not right*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                    else { /*I can only go down*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                  }
                  else { /*I can not go right or down*/
                    if (crossovers_list[avenue][street+1].used == -3) { /*I can only go left*/
                      aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                      add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                      aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                      can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                      aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                      read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                    }
                  }
                }
              }
          }
        }
        else if (avenue == avenues) { /*Last line*/
          if (street == 1) { /*Right limit - Right down corner*/
              if (crossovers_list[avenue][street+1].used == 3 && crossovers_list[avenue-1][street].used == 3) { /*If I can not go left or up I will go back*/
                if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                  without_path = 1;
                }
                else { /*I am out of options and the queue is not "empty"*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else {
                if (crossovers_list[avenue][street+1].used == -3) { /*I can go left*/
                  if (crossovers_list[avenue-1][street].used == -3) { /*I can go left and up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);

                  }
                  else { /*I can only go left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can not go Left*/
                  if (crossovers_list[avenue-1][street].used == -3) { /*I can only go up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
          }
          else if (street == streets) { /*Left limit - Left down corner*/
              if (crossovers_list[avenue][street-1].used == 3 && crossovers_list[avenue-1][street].used == 3) { /*If I can not go right or up I will go back*/
                if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                  without_path = 1;
                }
                else { /*I am out of options and the queue is not "empty"*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else {
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go right*/
                  if (crossovers_list[avenue-1][street].used == -3) { /*I can go right and up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can only go right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can not go right*/
                  if (crossovers_list[avenue-1][street].used == -3) { /*I can only go up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
          }
          else { /*I am in the middle of the last line*/
            if (crossovers_list[avenue][street-1].used == 3 && crossovers_list[avenue-1][street].used == 3 && crossovers_list[avenue][street+1].used == 3) { /*If I can not go right, up or left, I will go back*/
              if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
                without_path = 1;
              }
              else { /*I am out of options and the queue is not "empty"*/
                aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
              }
            }
            else {
              if (crossovers_list[avenue][street-1].used == -3) { /*I can go right*/
                if (crossovers_list[avenue-1][street].used == -3) { /*I can go right and up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go right, up and left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can only go right and up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can go right but not up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go right and left but not up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can only go right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
              else { /*I can not go right*/
                if (crossovers_list[avenue-1][street].used == -3) { /*I can go up but not right*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go left or up but not right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can only go up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can not go right or up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can only go left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
            }
          }
        }
        else if (street == 1) { /*Right limit column (except corners)*/
          if (crossovers_list[avenue-1][street].used == 3 && crossovers_list[avenue+1][street].used == 3 && crossovers_list[avenue][street+1].used == 3) { /*If I can not go up, down or left, I will go back*/
            if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
              without_path = 1;
            }
            else { /*I am out of options and the queue is not "empty"*/
              aux_empty_spot_in_visited = empty_spot_in_visited + 1;
              add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
              aux_value_to_read_in_queue = value_to_read_in_queue + 1;
              read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
            }
          }
          else {
            if (crossovers_list[avenue-1][street].used == -3) { /*I can go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go up and down*/
                if (crossovers_list[avenue][street+1].used == -3) { /*I can go up, down and left*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go up and down but not left*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else  { /*I can go up but not down*/
                if (crossovers_list[avenue][street+1].used == -3) { /*I can go up and left but not down*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go up but not down or left - only up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
            }
            else { /*I can not go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go down but not up*/
                if (crossovers_list[avenue][street+1].used == -3) { /*I can go down and left but not up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go down but not left or up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else { /*I can not go down or up*/
                if (crossovers_list[avenue][street+1].used == -3) { /*I can go left but not down or up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
            }
          }
        }
        else if (street == streets) { /*Left limit column (except corners)*/
          if (crossovers_list[avenue-1][street].used == 3 && crossovers_list[avenue+1][street].used == 3 && crossovers_list[avenue][street-1].used == 3) { /*If I can not go up, down or right, I will go back*/
            if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
              without_path = 1;
            }
            else { /*I am out of options and the queue is not "empty"*/
              aux_empty_spot_in_visited = empty_spot_in_visited + 1;
              add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
              aux_value_to_read_in_queue = value_to_read_in_queue + 1;
              read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
            }
          }
          else {
            if (crossovers_list[avenue-1][street].used == -3) { /*I can go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go up and down*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go up, down, and right*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go up and down but not right*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else  { /*I can go up but not down*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go up and right but not down*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go up but not down or right - only up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
            }
            else { /*I can not go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go down but not up*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go down and right but not up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
                else { /*I can go down but not right or up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
              else { /*I can not go down or up*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go right but not down or up*/
                  aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                  add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                  aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                  can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                  aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                  read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                }
              }
            }
          }
        }
        else { /*In the middle of the matrix*/
          if (crossovers_list[avenue-1][street].used == 3 && crossovers_list[avenue+1][street].used == 3 && crossovers_list[avenue][street-1].used == 3 && crossovers_list[avenue][street+1].used == 3) { /*If I can not go up, down, right or left, I will go back*/
            if (value_to_read_in_queue + 1 == empty_spot_in_queue) { /*I am out of options and the queue is not "empty" - because I am out of options in the cell behind the empty spot (tlhe last cell)*/
              without_path = 1;
            }
            else { /*I am out of options and the queue is not "empty"*/
              aux_empty_spot_in_visited = empty_spot_in_visited + 1;
              add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
              aux_value_to_read_in_queue = value_to_read_in_queue + 1;
              read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
            }
          }
          else {
            if (crossovers_list[avenue-1][street].used == -3) { /*I can go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go up and down*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go up, down, and right*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go up,down,right or left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go up, down, right but not left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }

                }
                else { /*I can go up and down but not right*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go up,down or left but not right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go up, down but not right or left*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
              else  { /*I can go up but not down*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go up and right but not down*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go up,right or left but not down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go up, right but not left or down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }

                }
                else { /*I can go up but not down or right*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go up or left but not right or down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go up but not left or down or right - only up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(0,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue-1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue-1][street].caller_avenue,&crossovers_list[avenue-1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
            }
            else { /*I can not go up*/
              if (crossovers_list[avenue+1][street].used == -3) { /*I can go down but not up*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go down, and right but not up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go down,right or left but not up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go down, right but not left or up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can go down but not right or up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go down or left but not up or right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go down but not left or up or right - only down*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(1,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue+1][street].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue+1][street].caller_avenue,&crossovers_list[avenue+1][street].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
              else  { /*I can not go down or up*/
                if (crossovers_list[avenue][street-1].used == -3) { /*I can go right but not down or up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go right or left but not down or up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                  else { /*I can go right but not left or down or up - only right*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(2,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street-1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street-1].caller_avenue,&crossovers_list[avenue][street-1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
                else { /*I can not go down or right or up*/
                  if (crossovers_list[avenue][street+1].used == -3) { /*I can go left but not right or down or up*/
                    aux_empty_spot_in_visited = empty_spot_in_visited + 1;
                    add_node_to_visited(avenue,street,&crossovers_list[avenue][street].used,&visited[empty_spot_in_visited][0],&visited[empty_spot_in_visited][1],&empty_spot_in_visited,aux_empty_spot_in_visited);
                    aux_empty_spot_in_queue = empty_spot_in_queue + 1;
                    can_move(3,avenue,street,&queue[empty_spot_in_queue][0],&queue[empty_spot_in_queue][1],&crossovers_list[avenue][street+1].used,&empty_spot_in_queue,aux_empty_spot_in_queue,&crossovers_list[avenue][street+1].caller_avenue,&crossovers_list[avenue][street+1].caller_street);
                    aux_value_to_read_in_queue = value_to_read_in_queue + 1;
                    read_next_node(&value_to_read_in_queue,aux_value_to_read_in_queue,&avenue,&street,queue[aux_value_to_read_in_queue][0],queue[aux_value_to_read_in_queue][1]);
                  }
                }
              }
            }
          }
        }
      }
      /*I only get to this part when I get to the target or if the visited is empty and I have no options*/
      if (ended == 1) { /*This means I found a path to a supermarket so now I have to put 3 in the crossovers_list and clean the visited*/
        /*The vars avenue and street have the location of a supermarket so now I need to restaure the path*/
        aux_avenue = avenue;
        aux_street = street;
        for (j = 0; j < empty_spot_in_queue; j++) { /*Clean the queue to let them be used for another path*/
          crossovers_list[queue[j][0]][queue[j][1]].used = -3;
          queue[j][0] = 0;
          queue[j][1] = 0;
        }
        for (j = empty_spot_in_visited-1; j >= 0; j--) {
          if (visited[j][0] == aux_avenue && visited[j][1] == aux_street) { /*This means that this was the caller cell*/
            crossovers_list[aux_avenue][aux_street].used = 3;
            aux_avenue = crossovers_list[visited[j][0]][visited[j][1]].caller_avenue;
            aux_street = crossovers_list[visited[j][0]][visited[j][1]].caller_street;
          }
          visited[j][0] = 0; /*clean the visited array*/
          visited[j][1] = 0;
        }
      }
      else { /*i did not found a supermarket and I ran out of options*/
        visited[0][0] = 0;
        visited[0][1] = 0;
        for (j = 1; j < empty_spot_in_visited; j++) {
          crossovers_list[visited[j][0]][visited[j][1]].used = -3;
          visited[j][0] = 0; /*clean the visited array*/
          visited[j][1] = 0;
        }
      }
      empty_spot_in_visited = 0;
      value_to_read_in_queue = 0;
      empty_spot_in_queue = 0;
      ended = 0;
      without_path = 0;
      i++;
    }
    if (z == 0) {
      for (i = 1; i < avenues; i++) {
        for (j = 1; j <= streets; j++) {
          crossovers_list[i][j].used = -3;
        }
      }
      for (i = 0; i < citizens-save_checked_citizens; i++) {
        crossovers_list[adresses[i][0]][adresses[i][1]].used = 3;
      }
      first_max_citizens = max_citizens; /*This will keep the result of the first giant while*/
      max_citizens = save_max_citizens;
      i = 0;
      checked_citizens = save_checked_citizens;
      checked_supermarkets = save_checked_supermarkets;
      y = 0;
      for (j = citizens-1-save_checked_citizens; j >= 0; j--) {
        reverse_adresses[y][0] = adresses[j][0];
        reverse_adresses[y][1] = adresses[j][1];
        y++;
      }
      for (j = 0; j < citizens-save_checked_citizens; j++) {
        adresses[j][0] = reverse_adresses[j][0];
        adresses[j][1] = reverse_adresses[j][1];
      }
    }
  }
  if (first_max_citizens > max_citizens) {
    max_citizens = first_max_citizens; /*If the first while allows more citizens to go out at the same time that the second while, the correct answer is the first_max_citizens*/
  }
  printf("%d\n",max_citizens);
  return 0;
}
