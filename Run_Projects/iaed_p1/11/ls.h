#ifndef LS_H
#define LS_H

/* Maximum size of a string */
#define MAXSTRINGSIZE 64

/* Maximum amount of products in the system */
#define MAXPRODUCTS 10000

/* Maximum amount of orders in the system */
#define MAXORDERS 500

/* Maximum amount of products in an order */
#define MAXWEIGHT 200

/* Maximum size for auxiliary array in merge function */
#define maxN 10000

/* Macro to exchange Items in the sorting algorithm */
#define exch(A, B) { Item t = A; A = B; B = t; }

typedef int Item;

/* Product Structure */
typedef struct Product {
    int id;
	char description[MAXSTRINGSIZE];
	int price;
	int weight;
	int stock;
} Product;

/* Order Structure */
typedef struct Order {
	/* Number of products in the order */
	int num_products;
	/* Order's total weight */
	int weight;
	/* Array of product ids in the order */
	int product_ids[MAXWEIGHT];
	/* 
	 * Array of product quantities in the order. 
     * Size is the same as max products for easy access by mirroring
	 * positions with global products array 'storage' 
	 */
	int product_qty[MAXPRODUCTS];
} Order;

/* Adds a new product to the system. */
void add_product(const char *description, const int price, const int weight, 
					const int stock);

/* Adds stock to an existing product in the system. */
void add_stock(const int product_id, const int quantity);

/* Creates a new order. */
void create_order();

/* Adds a product to an order. */
void add_product_to_order(const int order_id, const int product_id, 
							const int quantity);

/* Removes stock from an existing product. */
void remove_stock_from_product(const int product_id, const int quantity);

/* Removes a product from an order. */
void remove_product_from_order(const int order_id, const int product_id);

/* Calculates an order's cost. */
void get_order_cost(const int order_id);

/* Changes the price of an existing product in the system. */
void change_product_price();

/* Lists the description and quantity of a product in an order. */
void list_product_from_order();

/* 
 * Lists the order identifier in which the given product occurs most often.
 * If there are 2 or more orders in this situation, the lowest order `id` 
 * will be printed. 
 */
void list_order_with_highest_qty_of_product();
 
/* 
 * Lists all products in the system in ascending price order.
 * If there are 2 or more products with the same price, these will be printed 
 * in ascending order of product id.
 */
void list_all_products_by_price_asc();

/* 
 * List all products in an order in alphabetical order from the description.
 */
void list_products_by_description(const int order_id);

/*
 * Auxiliary Functions
 */

/* Print all products in the system. */
void print_products(int ids_array[], int size);

/* Print all products in an order. */
void print_order_products(int order_id, int ids_array[], int size);

/* 
 * Comparators for the sorting algorithm
 */

/*
 * Compares products by their descriptions to order them alphabeticaly.
 * If the 2 products have the same description, these will be sorted in 
 * ascending order of product id.
 */
int compare_product_by_description(const Item i1, const Item i2);

/* 
 * Compares products by their prices to order them from lowest to highest.
 * If the 2 products have the same price, these will be sorted in ascending
 * order of product id.
 */
int compare_product_by_price_asc(const Item i1, const Item i2);

/* 
 * Sorting Algorithm functions
 */

/* Merging function for Merge Sort Algorithm. */
void merge(Item a[], int l, int m, int r, int (*comparator)(Item,Item));

/* Merge Sort Algorithm function. */
void mergesort(Item a[], int l, int r, int (*comparator)(Item,Item));

#endif /* LS_H */
