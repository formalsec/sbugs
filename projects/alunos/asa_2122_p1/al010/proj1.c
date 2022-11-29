#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#define MAXINPUT 26845

clock_t start, end;


void problem1(int * arr,int n){

	unsigned long *s,*c;
	unsigned long  maxsize=0,maxcount=0;
	int i,j;
	/*double time;*/

	/*start = clock();*/

	s = (unsigned long*)can_fail_malloc(n*sizeof(unsigned long));
	c = (unsigned long*)can_fail_malloc(n*sizeof(unsigned long));

	for(i=0;i<n;i++){
		s[i]=1;
		c[i]=1;
	}
	

	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			if(arr[j]<arr[i]){
				if(s[j]+1>s[i]){
					s[i]=s[j]+1;
					c[i]=c[j];
				}
				else if(s[j]+1==s[i])
					c[i]+=c[j];
			}
		}
	}

	/*

	s[i] = max(s[j]) + 1, se a[i]>a[j] && 0<j<i
	s[i] = 1 c.c.

	c[i] = c[j], se a[i]>a[j] && 0<j<i

	*/

	
	for(i=0;i<n;i++){
		if (s[i]>maxsize){
			maxsize=s[i];
			maxcount = c[i];
		}
		else if(s[i]==maxsize)
			maxcount += c[i];
	}
	/*end = clock();
	time = ((double)(end-start))/CLOCKS_PER_SEC;*/

	free(s);
	free(c);

	printf("%lu %lu\n",maxsize,maxcount);

	

}

void problem2(int * arr1,int n1,int * arr2, int n2){

	int *vec,curr,result = 0;
	int i,j;
	vec = (int*) can_fail_malloc (n2*sizeof(int));

	for(i=0;i<n2;i++){
		vec[i]=0;
	}

	for(i=0;i<n1;i++){
		curr = 0;
		for(j=0;j<n2;j++){
			if (arr1[i] == arr2[j]){
                if (curr + 1 > vec[j]){
                    vec[j] = curr + 1;
                }
			}
             
            if (arr1[i] > arr2[j]){
                if (vec[j] > curr){
                    curr = vec[j];
                }
            }
		}
	}
	


    for(i=0; i<n2; i++)
        if (vec[i] > result)
           result = vec[i];

    printf("%d\n",result);

    free(vec);
	
}


int main(int argc, char const *argv[])
{	
	int * arr1, * arr2; 
	int n,i=0,r,n1;
	char tmp='0';

	arr1=(int*)can_fail_malloc(MAXINPUT*sizeof(int));
	for(i=0;i<MAXINPUT;i++){
		arr1[i]=0;
	}
	
	r=scanf("%d\n",&n);
	if(r==-1) exit(-1);

	i=0;
	while(tmp != '\n'){
		r=scanf("%d%c",&arr1[i],&tmp);
		if(r==-1) exit(-1);
		i++;
	}
	
	arr1 = can_fail_realloc(arr1, i*sizeof(int));
	if(arr1 == NULL) {
		printf("erro\n");
		exit(-1);
	}

	if(n==1){
		problem1(arr1,i);
	}
	else if (n==2){
		n1=i;
		arr2=(int*)can_fail_malloc(MAXINPUT*sizeof(int));
		for(i=0;i<MAXINPUT;i++){
			arr2[i]=0;
		}
		
		i=0;
		tmp='0';

		while(tmp != '\n'){
		r=scanf("%d%c",&arr2[i],&tmp);
		i++;
		}
		
		arr2 = can_fail_realloc(arr2, i*sizeof(int));
		if(arr2 == NULL) {
			printf("erro\n");
			exit(-1);
		}
		
		problem2(arr1,n1,arr2,i);
		free(arr2);
	}

	free(arr1);


	return 0;
}