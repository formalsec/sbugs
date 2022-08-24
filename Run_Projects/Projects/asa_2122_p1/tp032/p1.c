#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Binary search (note boundaries in the caller)
 * Given a sorted array arr and value key, 
 * the ceiling index is the index of the 
 * smallest element greater o equal to key
 * ceilIndex >> O(logn).
 */
int ceilIndex(int arr[], int l, int r, int key){
    int curr = 0;

    while (r - l > 1){
        curr = l + ((r-l)/2);
        if (arr[curr] >= key) r = curr;
        else l = curr;
    }

    return r;
}

/* Given any array v of length len, res is the longest increasing subsequence of arr
 * O(n * logn)
 */
int longestIncreasingSubsequenceLength(int v[], int len)
{   
	int k, length = 1;
    int tail[(int)len];
	size_t i;

	if (len == 0)
		return 0;

	for(k = 0; k < (int)len; k++) tail[k] = 0; /*O(N)*/
	tail[0] = v[0];
	for (i = 1; i < len; i++) {/* O(N)*/

		/* update lowest value */
		if (v[i] < tail[0])
			tail[0] = v[i];

		/* v[i] extends largest subsequence */
		else if (v[i] > tail[length - 1])
			tail[length++] = v[i];

		/* v[i] will either become candidate for subsequence or
		 * remove all larger elements in tail to leave space 
		 * for next greater elements
		 */
		else
			tail[ceilIndex(tail, -1, length - 1, v[i])] = v[i]; /*O(logN)*/
	}

	return length;
}

/* function to count number of increasing
 * subsequences of size k
 * O(n^3)
 */
int numOfIncSubsequencesOfSizeK(int v[], int n, int k)
{	
	int i,l,j;
    int depth_pool[k][n], sum = 0;
    memset(depth_pool, 0, sizeof(depth_pool));
    /* count of increasing subsequences of size 1
     * ending at each arr[i]
	 */
    for (i = 0; i < n; i++) /* O(n)*/
        depth_pool[0][i] = 1;
 
    /* building up the matrix dp[][]
     * Here 'l' signifies the size of
     * increasing subsequence of size (l+1).
	 */
    for (l = 1; l < k; l++) { /* O(n)*/
 
        /* for each increasing subsequence of size 'l'
         * ending with element arr[i]
		 */
        for (i = l; i < n; i++) { /*O(n)*/
 
            /* count of increasing subsequences of size 'l'
             * ending with element arr[i]
			 */
            depth_pool[l][i] = 0;
            for (j = l - 1; j < i; j++) { /*O(n)*/
                if (v[j] < v[i])
                    depth_pool[l][i] += depth_pool[l - 1][j];
            }
        }
    }
 
    /* the final result is the sum of the all the subsequences of size k that finish at depth_pool[i] */
    for (i = k - 1; i < n; i++) /* O(n)*/
        sum += depth_pool[k - 1][i];
 
    /* required number of increasing
     * subsequences of size k
	 */
    return sum;
}

/* LCIS find the length of the longest common increasing
 * subsequence of seq1 and seq2 of length len1 and len2
 * respectively
 * O(N^2) 
 */
int LCIS(int *seq1, int *seq2, int len1, int len2){
    int i, j, current = 0, max = 0;
    
    int depth_array[len2];
    
    for(i = 0; i < len2; i++) /*O(N)*/
        depth_array[i] = 0;


    for (i = 0; i < len1; i++) { /*O(N)*/
        for (j = 0; j < len2; j++){ /*O(N)*/
            
            if (seq1[i] == seq2[j]) 
                if((current + 1 )> depth_array[j])
                    depth_array[j] = current + 1;
            

            if (seq1[i] > seq2[j])
                if(current < depth_array[j])
                    current = depth_array[j];

            if(depth_array[j] > max)
                max = depth_array[j];
        }
    }
    return max;
}

int main()
{
	int allocd = 10000000;
	int problem;
	int *v1 = malloc(sizeof(int)*allocd);
	int *v2 = malloc(sizeof(int)*allocd);
    int lis;
	int lis_amount;
	int i = -1, j = 0, curr = 0;
	/*
	int a1[] = {3,4,1,8,9,7,2};
    int a2[] = {3,4,7,2};*/
    
    int l1;
    int l2;

	char c = ' ';
	memset(v1, 0, sizeof(int)*allocd);
	memset(v2, 0, sizeof(int)*allocd);

	if((problem = getchar() - '0') <= 0) return 1;
	getchar();
	do{
        
		if(i > (int)allocd){
			v1 = (int*)realloc(v1, 2*allocd);
			allocd *= 2;
		}
		if(c == ' '){
			v1[i++] = curr;
			curr = 0;
		}
		else
			curr = curr*10 + c - '0';
	} while((c = getchar()) != '\n');
	v1[i] = curr; /* add curr to the last position since getchar reaches \n before updating v1*/
	v1 = realloc(v1, sizeof(int)*i); /* cuts of tail of trailing 0s in v1 */
	allocd=100;
	if(problem == 2){
		while(scanf("%d[^\n]", &v2[j]) != EOF){
			if(i > (int)allocd){
				v2 = (int*)realloc(v2, 2*allocd);
				allocd *= 2;
			} 
			j++;
		}
	}
	v2 = realloc(v2, sizeof(int)*j);
	
	
	l1 = i;
	l2 = j;
	if(problem == 1){
		lis = longestIncreasingSubsequenceLength(v1, i+1);
		lis_amount = numOfIncSubsequencesOfSizeK(v1, i+1, lis);
		printf("%d %d\n", lis, lis_amount);
	}
	else if(problem == 2) printf("%d\n", LCIS(v1, v2, l1+1, l2));
	else return 1;
	

	return 0;
}