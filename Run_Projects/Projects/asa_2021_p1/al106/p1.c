/*
Projeto 1 ASA
Grupo 106
Pedro Teixeira 81416
*/
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct
{
    int id;
    int* connectedTo;
    int numConnections;
    int isRoot;
} Domino;
 
Domino* connectionList;
 
void fillPositions(int numDominos){
    int i;
 
    for ( i = 0; i < numDominos; i++)
    {
        connectionList[i].id = i;
        connectionList[i].connectedTo = NULL;
        connectionList[i].numConnections = 0;
        connectionList[i].isRoot = 0;
    }
}
 
void addPairs(int d1, int d2){
    int i;
 
/*     printf("d1: %d\td2: %d\n",d1,d2);w
 */    connectionList[d1].numConnections++;
    int* tamanho = malloc(sizeof(int)*connectionList[d1].numConnections);
    for ( i = 0; i < connectionList[d1].numConnections - 1; i++)
    {
        tamanho[i] = connectionList[d1].connectedTo[i];
    }
    tamanho[connectionList[d1].numConnections-1] = d2;
    connectionList[d1].connectedTo = tamanho;
    connectionList[d2].isRoot = 1;
    tamanho = NULL;
    free(tamanho);
}
 
void checkStructContents(int numDominos){
    int i,j;
 
    for (i=0; i<numDominos; i++){
		printf("id:%d, numConnections:%d connectedTo: ",i, connectionList[i].numConnections);
		for (j=0; j<connectionList[i].numConnections; j++){
			printf("%d ",connectionList[i].connectedTo[j]);
		}
		printf("\n");
        if(connectionList[i].isRoot == 0){
            printf("root: %d\n", i);
        }
	}
}
 
int filhos(int z, int* distict){
    int i;
    int size = 0;
 
    /* add to distinct */
/*     printf("\nz: %d\n", z);
 */
    if (distict[z] == 1){
        return 0;
    } 
 
    distict[z] = 1;
    size++;
 
 
    for (i = 0; i < connectionList[z].numConnections; i++) {
/*         printf("z: %d\ti: %d\n", z, i);
 */        
        size += filhos(connectionList[z].connectedTo[i], distict);
    }
/*     printf("fi: %d\n", size);
 */    return size;
}
 
int* checkIfRoot(int numDominos, int* out){
    int numRoots = 0;
    int sizeBiggestRoot = -1;
    int distict[numDominos];
    int z;
    int i;
    for (i = 0; i < numDominos; i++) {
/*         printf("RIP 1\n");
 */        if (connectionList[i].isRoot == 0){
            numRoots++;
/*             printf("RIP 2\n");
 */ 
            /* init distict*/
            for ( z = 0; z < numDominos; z++){
/*                 printf("RIP 3\n");
 */
                distict[z] = 0;
            }
 
            /* check size root */ 
            int s = 0;
            for (z = 0; z < connectionList[i].numConnections; z++) {
/*                 printf("z: %d\ti: %d\n",z, i);
                printf("RIP 4\n"); */
                s += filhos(connectionList[i].connectedTo[z], distict);
            }
    /* printf("fi: %d\n", s); */
 
            /*  is biggest ?? */ 
            if (sizeBiggestRoot < s){
                sizeBiggestRoot = s;
            }
 
        }
    }
    out [0] = numRoots;
    out [1] = sizeBiggestRoot;
    /* out [2] = biggestRoot; */

    return out;
}
 
int main()
{
    int numDominos,numDependencias;
    int domino1, domino2, i;
 
    if (scanf("%d %d\n",&numDominos ,&numDependencias) != 2){
        return -1;
    }
 
    if (numDominos < 2 || numDependencias < 0)
    {
        return -1;
    }
 
/*     printf("numDominos: %d\t numDependencias: %d\n", numDominos, numDependencias);
 */    connectionList = malloc(sizeof(Domino)*numDominos);
 
 
    fillPositions(numDominos);
 
    for ( i = 0; i < numDependencias; i++)
    {
        if (scanf("%d %d\n", &domino1, &domino2) == 2){
            addPairs(domino1-1, domino2-1);
        }
        else{
            return 1;
        }
    }

/*     checkStructContents(numDominos); */

    int out[2]= {0,0};
    checkIfRoot(numDominos, out);
    printf("%d %d\n", out[0], out[1]);
    free(connectionList);

    return 0;
}