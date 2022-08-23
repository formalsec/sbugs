#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>

/*The maximum amount of products stored in the Logistics and Encomenda*/
#define MAX_PRODUTOS 10000
/*The maximum size of a description of a product*/
#define MAX_DESCRIPTION_SIZE 63
/*The maximum amount of orders stored in the Logistics*/
#define MAX_ENCOMENDAS 500
/*The maximum weight of a order*/
#define MAX_PESO_ENCOMENDA 200

/*The file where all the prints are done*/
FILE *outputFile;
/*The file where the inputs are received*/
FILE *inputFile;

#endif
