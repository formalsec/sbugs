#define STRING_LIM             64 /* 63 + '\0' */
#define PRODUCT_LIM            10000 /* 0 to 9999 */
#define ORDER_LIM              500 /* 0 to 499 */
#define ORDER_WEIGHT_LIM       200
#define INPUT_LIM              100 /* 100 chars should be enough for the input. */
#define INPUT_NUM_LIM          4 /* The command with the most entries has 4. */

/* STRUCTURES */
typedef struct Product{
    int price, weight, stock;
    char description[STRING_LIM];
} Product;

typedef struct Order{
    int products[ORDER_WEIGHT_LIM][2];
    int prodcount;
} Order;

/* FUNCTION PROTOTYPES */
int inputHandler(void);

void commandAddProduct(char[STRING_LIM], int, int, int);
void commandAddStock(int, int);
void commandAddOrder(void);
void commandAddProdOrder(int, int, int);
void commandRemoveStock(int, int);
void commandRemoveProdOrder(int, int);
void commandOrderPrice(int);
void commandChangePrice(int, int);
void commandProdOrder(int, int);
void commandMostProdOrder(int);
void commandListProd(void);
void commandListProdOrder(int);

int findOrderWeight(int);
int findIdpInOrder(int, int);

void printSortedArray(int array[], int, int);
void mergeSort(int array[], int, int, int);
void merge(int array[], int, int, int, int);

int findIdpPrice(int);
int findIdpWeight(int);
int findIdpStock(int);
int findStockInOrder(int, int);