/*File generated by PreProcessor.py*/

#ifndef PACKAGES_H_
#define PACKAGES_H_

#include "products.h"


Product packages[500][200];
int packageCount;
void createPackageCmd();
void addProdToPackCmd();
void removeProdFromPackCmd();
void calcPackagePriceCmd();
void returnProdInfoCmd();
void listPackageProdsCmd();
void listPackageProdsIDCmd();
#endif