#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
/*Joao Jose Carreto Moreira Fernandes  92492  grupo 156
*/


#include <stdio.h>
#include <stdlib.h>



typedef struct{
    int x;
    int y;
    char state;
} place;

typedef struct{
    int distancia;
    int cid;
}list;

list * aux;

place *market,*cidadao;

int *tab[2];


int ** duplicatemat(int**map,int ** dup, int M,int N){
    int i,j;
    for(i = 0; i < M;i++){
        for(j = 0; j < N; j++){
            dup[i][j] = map[i][j];
        }
    }
    return dup;
}


int percurso(int xi, int yi,int xf, int yf,int M, int N,int **dup,int **map,place *cidadao, int i) {
    if((xf==xi) && (yf - 1 ==yi) && map[xi][yi]==0) {
        map[cidadao[i].x][cidadao[i].y] =0;
        map[xi][yi] = 3;
        cidadao[i].x = xi;
        cidadao[i].y = yi;
        cidadao[i].state = 'B';
        return 1;
    }
    else if((xf==xi) && (yi == yf +1) && map[xi][yi]==0) {
        map[cidadao[i].x][cidadao[i].y] =0;
        map[xi][yi] = 3;
        cidadao[i].x = xi;
        cidadao[i].y = yi;
        cidadao[i].state = 'B';
        return 1;
    }
    else if((xf -1 ==xi) && (yf ==yi) && map[xi][yi]==0) {
        map[cidadao[i].x][cidadao[i].y] =0;
        map[xi][yi] = 3;
        cidadao[i].x = xi;
        cidadao[i].y = yi;
        cidadao[i].state = 'B';
        return 1;
    }
    else if((xf+1==xi) && (yi == yf) && map[xi][yi]==0) {
        map[cidadao[i].x][cidadao[i].y] =0;
        map[xi][yi] = 3;
        cidadao[i].x = xi;
        cidadao[i].y = yi;
        cidadao[i].state = 'B';
        return 1;
    }
 
    if(xi == cidadao[i].x && yi == cidadao[i].y){
        if((xf==xi) && (yf - 1 ==yi) ) {
            map[cidadao[i].x][cidadao[i].y] =0;
            map[xi][yi] = 3;
            cidadao[i].x = xi;
            cidadao[i].y = yi;
            cidadao[i].state = 'B';
            return 1;
        }
        else if((xf==xi) && (yi == yf +1)) {
            map[cidadao[i].x][cidadao[i].y] =0;
            map[xi][yi] = 3;
            cidadao[i].x = xi;
            cidadao[i].y = yi;
            cidadao[i].state = 'B';
            return 1;
        }
        else if((xf -1 ==xi) && (yf ==yi)) {
            map[cidadao[i].x][cidadao[i].y] =0;
            map[xi][yi] = 3;
            cidadao[i].x = xi;
            cidadao[i].y = yi;
            cidadao[i].state = 'B';
            return 1;
        }
        else if((xf+1==xi) && (yi == yf)) {
            map[cidadao[i].x][cidadao[i].y] =0;
            map[xi][yi] = 3;
            cidadao[i].x = xi;
            cidadao[i].y = yi;
            cidadao[i].state = 'B';
            return 1;
        }
    
        if(percurso(xi+1, yi,xf, yf,M, N,dup,map,cidadao,i))
            return 1;
      
        if(percurso(xi, yi+1 ,xf, yf,M, N,dup,map,cidadao,i))
            return 1;
     
        if(percurso(xi-1, yi,xf, yf,M, N,dup,map,cidadao,i))
             return 1;
    
     
        if(percurso(xi, yi-1 ,xf, yf,M, N,dup,map,cidadao,i))
            return 1;
      
      return 0;
   }


   else if(xi >= 0 && yi >= 0 && xi < M && yi < N && dup[xi][yi] == 0 && map[xi][yi] == 0){
     
      dup[xi][yi] = 1;
     
      if(percurso(xi+1, yi,xf, yf,M, N,dup,map,cidadao,i))
         return 1;
    
      if(percurso(xi, yi+1 ,xf, yf,M, N,dup,map,cidadao,i))
         return 1;
     
      if(percurso(xi-1, yi,xf, yf,M, N,dup,map,cidadao,i))
         return 1;
    
      if(percurso(xi, yi-1 ,xf, yf,M, N,dup,map,cidadao,i))
         return 1;
      
      dup[xi][yi] = 0;
      return 0;
   }
   return 0;
}




void sort(int n, list * tabela) { 
    int i, j, t, m; 
  
    for (i = 0; i < n; i++) { 
        for (j = i + 1; j < n; j++) { 
            if (tabela[j].distancia < tabela[i].distancia) { 
  
                t = tabela[i].distancia;
                m = tabela[i].cid; 
                tabela[i].distancia = tabela[j].distancia; 
                tabela[i].cid = tabela[j].cid; 
                tabela[j].distancia = t;
                tabela[j].cid = m; 
            } 
        } 
    } 
}


int distancia(place market, place cidadao){
    int x = market.x - cidadao.x;
    int y = market.y - cidadao.y;
    if(x<0) x*=-1;
    if(y<0) y*=-1;
    return x+y;
}

void tabela(place market, place * cidadao, int C){
    
    int i = 0;
    for(i = 0; i < C; i++){
        aux[i].distancia = distancia(market,cidadao[i]);
        aux[i].cid = i;
    }

    sort( C, aux);
}


int contarnum(int ** map, int ** dup,int M, int N,place *cidadao, place *market,int S,int C){
    int num = 0,i,j,num2;
    aux = can_fail_malloc(sizeof(list)*C);
    for(i=0;i<S;i++){
        tabela(market[i], cidadao,C);
        for(j =0;j<C;j++){
            if(market[i].state=='B')
                break;
            
            if(cidadao[aux[j].cid].state!='B'){
                num2 = percurso( cidadao[aux[j].cid].x,cidadao[aux[j].cid].y,market[i].x,market[i].y,M,N,dup,map,cidadao,aux[j].cid);
                if(num2){
                    num+=num2;
                    market[i].state= 'B';
                }
            }    
        }

        dup = duplicatemat(map,dup,M,N); 
    }

    return num;

}



void test(int ** map,int **dup, int M, int N){
    int i,x=0,y=0;
    int num = 0;
    int S,C;
    
    
    scanf("%d %d", &S, &C);

    market = can_fail_malloc(sizeof(place)*S);
    cidadao = can_fail_malloc(sizeof(place)*C);
    

    for(i = 0;i < S; i++){
        scanf("%d %d",&x,&y);
        map[--x][--y] = 2,
        market[i].x = x;
        market[i].y = y;
        market[i].state = 'L';
    }

    for(i = 0;i < C; i++){
        scanf("%d %d",&x,&y);
        map[--x][--y] = 3,
        cidadao[i].x = x;
        cidadao[i].y = y;
        cidadao[i].state = 'L';
    }
    
    dup = duplicatemat(map,dup,M,N); 
    

    num = contarnum(map,dup,M,N,cidadao,market,S,C);

    
    printf("%d\n",num);

    free(market);
    free(cidadao);

}



int main(){
    int M,N,j,i,b;
    int ** map, **dup;
    scanf("%d %d", &M, &N);

    map = can_fail_malloc(sizeof(int*)*M);
    dup = can_fail_malloc(sizeof(int*)*M);
    for(i = 0;i < M;i++){
        map[i] = can_fail_malloc(sizeof(int)*N);
        dup[i] = can_fail_malloc(sizeof(int)*N);
        for( b = 0; b < N; b++ ){
            map[i][b] = 0;
            dup[i][b] = 0;
        }
    }

   
    test(map,dup,M,N);

    for(j = 0; j < M; j++ ){
        free(map[j]);
        free(dup[j]);
    }
    free(dup);
    free(map);
    free(aux);
    return 0;

}