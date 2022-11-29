#ifndef SDD_PROJ_IAED_H
#define SDD_PROJ_IAED_H
/* defines_and_functions.h
 Constant definition
*/

#define FALSE 0
#define TRUE 1
#define IOBUF_SIZE 1512
#define MAX_PRODUCTS 10000
#define MAX_IDS MAX_PRODUCTS
#define DESC_MAX_CHAR 64
#define MAX_PACKAGES 500
#define MAX_WEIGHT 200
#define UNINITIALIZED -1
#define MAX_CMDS 20
#define MAX_ARR_SORT_SIZE MAX_IDS
#define MAX_ENCOM_PRODS MAX_WEIGHT /* every product has a weight of 1> , so there can only be at max MAX_WEIGHT products in a package*/ 


/* product struct (product)*/
typedef struct 
{
    char desc[DESC_MAX_CHAR]; /* product description*/
    unsigned int price; /* product price*/
    unsigned int weight;/* total weight of the product*/
    unsigned int qty; /* product stock quantity*/
} product;


/* package struct (package)*/
typedef struct 
{
    /* package.products[id][0] contains the number of units in the package*/
    int products[MAX_PRODUCTS][1];
}package;

typedef unsigned int uint;


/* forward declarations*/
int CommandProcess();
void CreateProd(char desc [DESC_MAX_CHAR],uint price, uint weight, uint qty);
void GetProdDesc(uint id, char *buffer);
uint GetProdPeso(uint id);
uint GetProdPrice(uint id);
uint GetProdQty(uint id);
uint GetEncomQtyProd(uint id_encom, uint id_prod);
uint GetEncomPeso(uint id);
void SetProdDesc(uint id,char * desc);
void SetProdPrice(uint id,uint price);
void SetProdPeso(uint id,uint weight);
void SetProdQty(uint id,uint qty);
void SetEncomQtyProd(uint id_encom, uint id_prod, uint qty);
void AddStock(uint id,uint qty);
void RemoveStock(uint id,uint qty);
void CreateEncomenda();
void AddProd(uint id_encom, uint id_prod,uint qty);
void RemoveProd(uint id_encom, uint id_prod);
void ListEncomTotalPrice(uint id);
void ProdNewPrice(uint id, uint price);
void ListDescPrice(uint id_encom, uint id_prod);
void EncomMaxProd(uint id);
void ListProdByID();
void ListEncomByID();
void MergeSortOrder(int arr[],int arr_aux[],uint l_index,uint mid_index, uint r_index,int (*p_comp_func)(int,int));
void MergeSortRecursive(int arr[],int arr_aux[],uint l_index,uint r_index,int (*p_comp_func)(int,int));
void MergeSort(int arr[],uint l_index,uint r_index,int (*p_comp_func)(int,int));
int CompareProdPrice(int id_1, int id_2);
int EncomCompareProdDesc(int id_1,int id_2);
void ListProdByPrice();
void ListEncomProdByDesc(uint id_encom);

#endif
