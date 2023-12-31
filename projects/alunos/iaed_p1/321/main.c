#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "constants.h"
#include "all.h"

prod prod_list[MAX_PROD];			/* lista de todos os produtos no sistema*/
ord ord_list[MAX_ORD];				/* lista de todas as encomendas */

int main() {
	char c;
	while ( (c=getchar()) != 'x') {
		switch (c) {

			case 'a' :
				add_prod_sys();
				break;

			case 'q' :
				add_stock();
				break;

			case 'N' :
				add_order();
				break;

			case 'A' :
				add_prod_ord();
				break;

			case 'r' :
				remove_stock();
				break;

			case 'R' :
				remove_prod();
				break;

			case 'C' :
				order_cost();
				break;

			case 'p' :
				change_price();
				break;

			case 'E' :
				show_prod();
				break;

			case 'm' :
				most_wanted();
				break;

			case 'l' :
				list_prod_sys();
				break;

			case 'L' :
				list_prod_ord();
				break;
		}
	}
	return 0;
}