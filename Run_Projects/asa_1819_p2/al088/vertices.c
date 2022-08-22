#include <stdio.h>
#include <stdlib.h>

typedef struct edges{
  long int source;
  long int destiny;
  struct edges* next;
}* edgesLink;

typedef struct neighbours{
  long int destiny;
  long int capacity;
  long int flow;
  long int source;
  struct neighbours* next;
}* neighboursLink;


edgesLink new_edgeLink(long int source, long int destiny){
  edgesLink t=malloc(sizeof(struct edges));
  t->source=source;
  t->destiny=destiny;
  t->next=NULL;
  return t;
}

edgesLink insert_minimal_cut(edgesLink head, long int source,long int destiny){
  edgesLink t= new_edgeLink(source,destiny);
  edgesLink aux=NULL,prev=NULL;
  if(head==NULL)
    return t;

  for(aux=head; aux!=NULL; prev=aux,aux=aux->next){
    if(aux->source>t->source || (aux->source==t->source && aux->destiny>t->destiny)){
      if(prev==NULL){
        t->next=aux;
        return t;
      }
      prev->next=t;
      t->next=aux;
      return head;
    }
  }
  if(aux==NULL)
    prev->next=t;

  return head;
}

neighboursLink new_edge(long int indice, long int capacity,long int source){
  neighboursLink t= malloc(sizeof(struct neighbours));
  t->destiny=indice;
  t->capacity=capacity;
  t->flow=0;
  t->source=source;
  t->next=NULL;
  return t;
}

neighboursLink insertEdgeInList(neighboursLink head,long int indice, long int capacity,long int source){
  neighboursLink t=new_edge(indice,capacity,source);
  t->next=head;
  return t;
}

typedef struct{
  long int height;
  long int capacity;
  long int excessflow;
  neighboursLink edges;
}info;

void change_flow(info* vertices, long int station, long int source, long int cap){
  neighboursLink t=vertices[station].edges;
  if(station!=0){
    while(t!=NULL){
      if(t->destiny==source){
        t->flow=cap;
        break;
      }
      t=t->next;
    }
  }
}

long int minimum(long int a, long int b){
  if(a<b)
    return a;
  return b;
}

void initialize_pre_flow(info* vertices,long int numStations, long int numProviders){
  long int i=0;
  neighboursLink t=NULL;
  for(i=2; i<=(numProviders+2*numStations+1);i++){
    vertices[i].height=0;
    vertices[i].excessflow=0;
  }
  vertices[0].height=numStations+numProviders+2;
  for(t=vertices[0].edges;t!=NULL; t=t->next){
    t->flow=minimum(vertices[0].excessflow,t->capacity);
    vertices[0].excessflow-=t->flow;
    change_flow(vertices,t->destiny,0,(0-t->flow));
    vertices[t->destiny].excessflow+=t->flow;
  }
}

void push(info* vertices,long int index,long int lower, long int value,long int source){
  neighboursLink t=NULL;
  vertices[index].excessflow-=value;

  if(source==1){
    for(t=vertices[index].edges;t!=NULL;t=t->next){
      if(t->destiny==lower){
        t->flow+=value;
        vertices[lower].excessflow+=value;
        change_flow(vertices,t->destiny,index,(0-t->flow));
      }
    }
  }

  else{
    vertices[lower].excessflow+=value;
    for(t=vertices[lower].edges; t!=NULL;t=t->next){
      if(t->destiny==index){
        t->flow-=value;
        change_flow(vertices,t->destiny,index,(0-t->flow));
      }
    }
  }


}

void get_minimum_adjacent(info* vertices, long int index,long int* height, long int* lower_index,long int* source){
neighboursLink t=NULL;
*(height)=-1;
for(t=vertices[index].edges; t!=NULL; t=t->next){
  if(vertices[t->destiny].height< *(height) || *(height)==-1){
    if((t->source==1 && t->capacity>t->flow)||(t->source==0 && t->flow<0)){
      *(height)=vertices[t->destiny].height;
      *(lower_index)=t->destiny;
      *(source)=t->source;
    }
    }
  }
}

long int get_capacity(info vertex,long int lower,int source){
  neighboursLink t=NULL;
  if(lower==0)
    return vertex.capacity;
  for(t= vertex.edges; t!=NULL;t=t->next){
    if(t->destiny==lower){
      if(source==1){
        return (t->capacity-t->flow);
      }
      else
        return (t->capacity-t->flow);
    }
  }
  return 0;
}

void discharge(info* vertices, long int index){
  long int lower_index=0,capacity=0,min=0,source=0,lower_height=0;
  neighboursLink t=NULL;
  while(vertices[index].excessflow>0){
    get_minimum_adjacent(vertices,index,&lower_height,&lower_index, &source);
   if(lower_height>=vertices[index].height){
      vertices[index].height=lower_height+1;
    }

    for(t=vertices[index].edges; t!=NULL; t=t->next){
      if(t->destiny==lower_index){
          capacity=get_capacity(vertices[index],lower_index,t->source);
          min=minimum(vertices[index].excessflow,capacity);
          push(vertices,index,lower_index,min,t->source);
        }
    }

  }
}

void initialize_aux(long int* aux, long int numStations,long int numProviders){
  long int i=0;
  for(i=0;i<(2*numStations+numProviders);i++){
    aux[i]=i+2;
  }
}

void replace(long int* aux, long int index){
  long int i=0,save=0;
  save=aux[index];
  for(i=index;i>0;i--){
    aux[i]=aux[i-1];
  }
  aux[0]=save;
}

void relabel_to_front(info* vertices, long int numStations, long int numProviders){
  long int i=0,oldHeight=0,aux[numStations*2+numProviders];
  initialize_aux(aux,numStations,numProviders);
  initialize_pre_flow(vertices, numStations, numProviders);
  for(i=0; i<(2*numStations+numProviders);i++){
    oldHeight=vertices[aux[i]].height;
    discharge(vertices,aux[i]);
    if(vertices[aux[i]].height>oldHeight){
      replace(aux,i);
      i=0;
    }
  }
}

void doDfs(info* vertices, long int pos,int* visited){
  neighboursLink t=NULL;
  visited[pos]=1;
  for(t=vertices[pos].edges;t!=NULL;t=t->next){
    if(visited[t->destiny]==0 && ((t->source==0 && t->capacity+t->flow>0) || (t->source==1 && t->flow>0))){
      doDfs(vertices,t->destiny,visited);
    }

  }
}
void findMinimalCut(info* vertices, long int numProviders,long int numStations){
  long int i=0,count=0;
  neighboursLink t=NULL;
  edgesLink minimal_cut=NULL,aux=NULL;
  long int stations[numStations],auxi,auxdestiny;
  int visited[numProviders+2*numStations+1];

  for(i=0; i<=(numProviders+2*numStations+1);i++){
    visited[i]=0;
  }

  for(i=0; i<numStations;i++){
    stations[i]=0;
  }
  doDfs(vertices,1,visited);

  for(i=1;i<=(2*numStations+numProviders+1);i++){
    if(visited[i]==1){
      for(t=vertices[i].edges;t!=NULL;t=t->next){
        if(visited[t->destiny]==0){          /*quer dizer q nao se alcancou o vertice,logo a aresta e do corte minimo*/
          if((t->destiny-numStations==i && t->destiny>(numStations+numProviders+1))||( i-numStations==t->destiny && i>(numStations+numProviders+1)))
            stations[minimum(t->destiny,i)-numProviders-1]=1;
          else if(t->destiny!=0){
            auxi=i;
            auxdestiny=t->destiny;
              if(i>(numStations+numProviders+1))
                auxi=i-numStations;
              else if(t->destiny>(numStations+numProviders+1))
                auxdestiny=t->destiny-numStations;
            if(t->source==0)
              minimal_cut=insert_minimal_cut(minimal_cut,auxdestiny,auxi);
            else
              minimal_cut=insert_minimal_cut(minimal_cut,auxi,auxdestiny);
          }
        }
      }
    }
  }

  for(i=0; i<numStations+1;i++){
    if(stations[i]==1){
      if(count==0)
        printf("%li",i+1+numProviders);
      else
        printf(" %li",i+1+numProviders);
      count++;
    }
  }
  printf("\n");

  for(aux=minimal_cut; aux!=NULL; aux=aux->next){
    printf("%li %li\n",aux->source,aux->destiny);
  }
}


int main(){
  long int numProviders=0, numStations=0, numConnections=0;
  long int i=0,source=0, destiny=0, capacity=0;

  scanf("%li %li %li",&numProviders,&numStations,&numConnections);

  info* verticesInfo=(info*)malloc(sizeof(info) * (2+numProviders+2*numStations));

  verticesInfo[0].edges=NULL;
  verticesInfo[0].excessflow=0;
  verticesInfo[0].height=0;

  verticesInfo[1].edges=NULL;
  verticesInfo[1].excessflow=0;
  verticesInfo[1].height=0;


  for(i=2; i<=(numProviders+1); i++){
    verticesInfo[i].edges=NULL;
    scanf("%li", &verticesInfo[i].capacity);
    verticesInfo[0].excessflow+=verticesInfo[i].capacity;
    verticesInfo[0].edges=insertEdgeInList(verticesInfo[0].edges,i,verticesInfo[i].capacity,1);
    verticesInfo[i].edges=insertEdgeInList(verticesInfo[i].edges,0,verticesInfo[i].capacity,0);
  }

  for(i=numProviders+2; i<=(numProviders+1+numStations); i++){
    verticesInfo[i].edges=NULL;
    scanf("%li", &verticesInfo[i].capacity);
  }

  for(i=numProviders+numStations+2; i<(2+numProviders+2*numStations);i++){
    verticesInfo[i].edges=NULL;
    verticesInfo[i].edges=insertEdgeInList(verticesInfo[i].edges,(i-numStations),verticesInfo[i-numStations].capacity,0);
    verticesInfo[i-numStations].edges=insertEdgeInList(verticesInfo[i-numStations].edges,i,verticesInfo[i-numStations].capacity,1);
  }

  for(i=0; i<numConnections;i++){
    scanf("%li %li %li",&source,&destiny,&capacity);
    if(source>numProviders+1){
      verticesInfo[source+numStations].edges=insertEdgeInList(verticesInfo[source+numStations].edges,destiny,capacity,1);
      verticesInfo[destiny].edges=insertEdgeInList(verticesInfo[destiny].edges,source+numStations,capacity,0);
    }

    else if(destiny>numProviders+1){
      verticesInfo[source].edges=insertEdgeInList(verticesInfo[source].edges,destiny,capacity,1);
      verticesInfo[destiny].edges=insertEdgeInList(verticesInfo[destiny].edges,source,capacity,0);
    }

    else{
      verticesInfo[source].edges=insertEdgeInList(verticesInfo[source].edges,destiny,capacity,1);
      verticesInfo[destiny].edges=insertEdgeInList(verticesInfo[destiny].edges,source,capacity,0);
    }

  }

  relabel_to_front(verticesInfo,numStations,numProviders);
  printf("%li\n",verticesInfo[1].excessflow);
  findMinimalCut(verticesInfo,numProviders,numStations);

   return 0;
}
