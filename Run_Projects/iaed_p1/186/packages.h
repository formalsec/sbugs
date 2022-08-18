#ifndef PACKAGES_H_
#define PACKAGES_H_
#include "products.h"

/* Constante que define o numero maximo de encomendas que podem existir no
   sistema. */
#define MAX_PACKAGES 500

/* Constante que define o peso maximo que uma encomenda pode ter. */
#define MAX_PACKAGE_WEIGHT 200

/* Variavel global que armazena todas as encomendas do sistema. */
Product packages[MAX_PACKAGES][MAX_PACKAGE_WEIGHT];

/* Variavel global que armazena o total de encomendas no sistema. */
int packageCount;

/* Funcoes responsaveis pela logica de comandos */
void createPackageCmd();
void addProdToPackCmd();
void removeProdFromPackCmd();
void calcPackagePriceCmd();
void returnProdInfoCmd();
void listPackageProdsCmd();
void listPackageProdsIDCmd();

#endif
