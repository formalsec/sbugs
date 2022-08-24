#include <stdio.h>
#include <stdlib.h>

#define MAX 20


int commonIncreaseArray (int seq1[], int n, int seq2[], int m){
	
	int array[m];
	int j = 0;
	int i = 0;
	int res = 0;
	
	for(j = 0; j<m; j++){
		array[j] = 0;
	}
	
	for (i = 0; i < n; i++){
		int c = 0;
	
		
		for (j = 0; j<m; j++){
			if(seq1[i] == seq2[j]){
				if(c + 1 > array[j]){
					array[j] = c + 1;
				}
			}
			
			if (seq1[i] > seq2[j]){
				if(array[j] > c){
					c = array[j];
				}
			}
		}
	}
	
	for(i = 0; i < m; i++){
		if(array[i] > res){
			res = array[i];
		}
	}		
	
	return res;
}

int commonIncreaseMatrix (int seq1[], int n, int seq2[], int m){
	
	int matrix[n][m];
	int j = 0;
	int i = 0;
	int res = 0;
	
	for(j = 0; j<m; j++){
		matrix[j][0] = 0;
	}
	
	for(j = 0; j<m; j++){
		matrix[0][j] = 0;
	}
	
	for (i = 0; i < n; i++){
		
		for (j = 0; j<m; j++){
			if(seq1[i] == seq2[j]){
				if(matrix [i][j+1] > matrix [i+1][j]){
					matrix [i+1][j] = matrix [i][j+1] + 1;
				}
			}
			
			if (seq1[i] > seq2[j]){
				if(matrix [i+1][j] > matrix [i][j+1]){
					matrix [i+1][j] = matrix [i][j+1];
				}
			}
		}
	}
	
	for(i = 0; i < n; i++){
		for (j=0;	 j < m; j++){
			if(matrix[i][j] > res){
				res = matrix[i][j];	
			}
		}
	}		
	
	return res;
}


int commonIncrease (int seq1[], int n, int seq2[], int m){
	int res;
	
	if(n == m){
		res = commonIncreaseArray (seq1, n, seq2, m);
	} else res = commonIncreaseMatrix (seq1, n, seq2, m);
		
	return res;
}


int increase(int seq[], int n){
	
	int array[n];
	int res = 0;
	int i;
	int j;
	
	for (i = 0; i < n; i++){
		array[i] = 1;
	}
	
	for (i = 1; i < n; i++){
		array[i] = 1;
		for (j = 0; j < i; j++){
			if (seq[i] > seq[j] && array[i] < array[j] + 1){
				array[i] = array[j] + 1;
			}
		}
	}	
	
    for (i = 0; i < n; i++){
		if (res < array[i]){
			res = array[i];
		}
	}
		
	return res;
}


int countIncrease (int seq[], int n){

	int array[n];
	int j = 0;
	int i = 0;
	int res = 0;
	
	for (i = 0; i < n; i++){
		array[i] = 1;
	}
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++){
			if(seq[j] < seq[i]){
				res = array [i] + 1;
			}
		}
	}
	
	return res;
}

int main (int argc, char* argv[]) {

	int num;
	int i;
	
	scanf ("%d", &num);
	
	
	if(num == 2){
		int seq1[MAX];
		int seq2[MAX];
		
		for (i = 0; seq2[i] != '\0' && i < MAX; i++){
			scanf ("%d", &seq1[i]);
		}
		
		for (i = 0; seq2[i] != '\0' && i < MAX; i++){
			scanf ("%d", &seq2[i]);
		}

		int n = sizeof(seq1)/sizeof(seq1[0]);
		int m = sizeof(seq2)/sizeof(seq2[0]);
	
		int res = commonIncrease(seq1, n, seq2, m);
	
		printf ("%d", res);
		
	} else{
		
		int seq1[MAX];
		
		
		for (i = 0; seq1[i] != '\0' && i < MAX; i++){
			scanf ("%d ", &seq1[i]);
		}
		int n = sizeof(seq1)/sizeof(seq1[0]);		
		
		int b = increase(seq1, n);
		int c = countIncrease (seq1, n);
		
		printf ("%d %d", b, c);
		
	}
	
	return 0;
	
}
