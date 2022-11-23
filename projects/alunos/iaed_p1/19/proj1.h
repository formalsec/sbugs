#ifndef __PROJ_H__
#define __PROJ_H__

#define MAX_PRODUCTS 10000          /*Maximum products that can be declared*/
#define MAX_ORDERS 500              /*Maximum orders that can be declared*/
#define MAX_DESCRIP 64              /*Longest description of a product including '\0'*/
#define MAX_PRODUCTS_IN_ORDER 200   /*Highest amount of products that can be placed in a single order*/

/* Internal representation of a product*/
typedef struct {
	int id;
	char description[MAX_DESCRIP];
	int weight;
	int stock;
} Product;

/* Internal representation of an order*/
typedef	struct {
	int id;
	Product products [MAX_PRODUCTS_IN_ORDER]; 
	int nr_products;
	int weight;
	int ordered;
} Order;


/*Function Prototypes*/
int findProduct(Product *arr, int len, int id);
void readString(char *s);
void printProduct(Product product);
void printProducts();
void printOrder(int order);
void removeFromArray(Product *arr, int len, int position);
void createProduct(char *d, int prc, int wght, int amount);
void incrementStock(int id, int amount);
void createOrder();
void addToOrder(int order, int product, int amount);
void removeStock(int product, int amount);
void removeProductFromOrder(int order, int product);
void calcOrderCost(int order);
void changeProductPrice(int product, int newPrice);
void infoProductInOrder(int order, int product);
void mostCommissioningOrder(int product);
int higherPrice(const Product a, const Product b);
int higherName(const Product a, const Product b);
void merge(Product arr[], int left, int m, int right, int (*higher)(const Product a, const Product b));
void mergeSort(Product arr[], int l, int r, int (*higher)(const Product a, const Product b)); 
void listProductsByPrice();
void listOrderedProductsByName(int order);

#endif

/* =============================================================================
 *
 * End of proj1.h
 *
 * =============================================================================
 */
