#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solve(int ave,int rua,int aven,int ruan,int supn,int cidn,int tol,int local[supn][2],
			int matriz[aven][ruan],int mask[aven][ruan],int localcount){
	if (ave < 0 || ave >= aven || rua < 0 || rua >= ruan || cidn == 0 || tol < 0 ||
		(matriz[ave][rua] == 1 && ave != local[localcount][0] && rua != local[localcount][1])){
		return 0;
	}
	if (mask[ave][rua] == 1){
		if (localcount == supn-1 || (ave != local[localcount][0] && rua != local[localcount][1])){
			return 0;
		}
		return solve(local[localcount+1][0],local[localcount+1][1],aven,ruan,
					supn,cidn,tol-1,local,matriz,mask,localcount+1);
	}
	int max = 0,a;
	mask[ave][rua] = 1;
	if (matriz[ave][rua] == 2){
		if (localcount == supn-1){
			mask[ave][rua] = 0;
			return 1;
		}
		a = solve(local[localcount+1][0],local[localcount+1][1],aven,ruan,
					supn,cidn-1,tol,local,matriz,mask,localcount+1)+1;
		mask[ave][rua] = 0;
		return a;
	}
	else {
		a = solve(ave-1,rua,aven,ruan,supn,cidn,tol,local,matriz,mask,localcount);
		if (a > max)
			max = a;
		if (max != cidn)
			a = solve(ave+1,rua,aven,ruan,supn,cidn,tol-max+1,local,matriz,mask,localcount);
		if (a > max)
			max = a;
		if (max != cidn)
			a = solve(ave,rua-1,aven,ruan,supn,cidn,tol-max+1,local,matriz,mask,localcount);
		if (a > max)
			max = a;
		if (max != cidn)
			a = solve(ave,rua+1,aven,ruan,supn,cidn,tol-max+1,local,matriz,mask,localcount);
		if (a > max)
			max = a;
		if (localcount < supn-1 && ave == local[localcount][0] && rua == local[localcount][1] &&
			max != cidn){
			mask[ave][rua] = 0;
			a = solve(local[localcount+1][0],local[localcount+1][1],
				aven,ruan,supn,cidn,tol-max+1,local,matriz,mask,localcount+1);
			if (a > max)
				max = a;
		}
		mask[ave][rua] = 0;
		return max;
	}
}

int main(){
	int aven,ruan,supn,cidn,d1,d2,i,j,count;

	scanf("%d %d",&aven,&ruan);
	int matriz[aven][ruan];
	/* 0 = vazio, 1 = supermercado, 2 = cidadao, 3 = ambos*/ 
	for (i = 0; i < aven; ++i){
		for (j = 0; j < ruan; ++j){
			matriz[i][j] = 0;
		}
	}
	int mask[aven][ruan];
	for (i = 0; i < aven; ++i){
		for (j = 0; j < ruan; ++j){
			mask[i][j] = 0;
		}
	}

	scanf("%d %d",&supn,&cidn);
	if (supn == 0 || cidn == 0){
		printf("0\n");
		return 0;
	}
	int localtemp[supn][2];

	count = 0;
	for (i = 0; i < supn; ++i){
		scanf("%d %d",&d1,&d2);
		if (matriz[d1-1][d2-1] == 0){
			matriz[d1-1][d2-1] = 1;
			localtemp[count][0] = d1-1;
			localtemp[count][1] = d2-1;
			count++;
		}
	}
	supn = count;
	int local[supn][2];
	for (i = 0; i < supn; ++i){
		local[i][0] = localtemp[i][0];
		local[i][1] = localtemp[i][1];
	}

	count = 0,j = 0;
	for (i = 0; i < cidn; ++i){
		scanf("%d %d",&d1,&d2);
		if (matriz[d1-1][d2-1] == 1){
			matriz[d1-1][d2-1] = 3;
			count++;
			mask[d1-1][d2-1] = 1;
		}
		else if (matriz[d1-1][d2-1] == 0){
			matriz[d1-1][d2-1] = 2;
			j++;
		}
	}
	cidn = j;

	printf("%d\n",count+solve(local[0][0],local[0][1],aven,ruan,supn,cidn,supn,local,matriz,mask,0));
	return 0;
}