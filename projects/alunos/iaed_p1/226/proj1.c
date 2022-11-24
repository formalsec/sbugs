#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXSTRING 63
#define MAXORDERS 500
#define MAXPRODUCTS 10000
#define MAXORDERWEIGHT 200
#define MAXPRODSINORDER 200

struct product {
	int idp;
	char description[MAXSTRING];
	int price;
	int weight;
	int amountInStock;
};

struct order {
	int ide;
	int orderWeight;
	int orderCost;
	int numberOfProducts;
	struct product productsInOrder[MAXPRODSINORDER];
};

void a_addNewProduct();
void q_addStockToExistingProduct();
void N_createNewOrder();
void A_addProductToOrder();
void r_removeStockFromExistingProduct();
void R_removeProductFromOrder();
void C_calculatePriceOfOrder();
void p_chancePriceOfExistingProduct();
void E_showProductOrderDetails();
void m_returnOrderWithMoreProductPQuantity();
void l_listAllProdutsByPriceAscendingOrder();
void L_listAllProductsFromOrderByDescriptionAlphabeticalOrder();
void x_exitApp();

/* productsVectorSize e ordersVectorSize s?o vari?veis que controlam, respetivamente, o tamanho do vetor de produtos no sistema e nas encomendas.
systemProducts[] ? o vetor que cont?m todos os produtos do sistema.
sortedSystemProducts[] ? o vetor que cont?m todos os produtos do sistema ordenados por ordem crescente do pre?o. 
aux1[] ? o vetor utilizado no algoritmo de ordena??o MergeSort para auxiliar a ordena??o dos produtos. 
orders[] ? o vetor que cont?m todas as encomendas do sistema.
sortedProductsInOrder[MAXORDERS] ? o vetor que cont?m os produtos de uma encomenda ordenados por ordem de descri??o.
aux2[] ? o vetor utilizado no algoritmo de ordena??o MergeSort para auxiliar a ordena??o dos produtos na encomenda. 
*/

int productsVectorSize = 0, ordersVectorSize = 0;
struct product systemProducts[MAXPRODUCTS], sortedSystemProducts[MAXPRODUCTS], aux1[MAXPRODUCTS];
struct order orders[MAXORDERS], sortedProductsInOrder[MAXORDERS], aux2[MAXORDERS];

int main() {

	char command;

	while (1) {

		command = getchar();

		switch(command) {

			case 'a':
				a_addNewProduct();
				productsVectorSize++; /* Sempre que a fun??o ? chamada, a quantidade de produtos no sistema ? incrementado. */
				break;

			case 'q':
				q_addStockToExistingProduct();
				break;

			case 'N':
				N_createNewOrder();
				ordersVectorSize++; /* Sempre que a fun??o ? chamada, a quantidade de encomendas no sistema ? incrementado. */
				break;

			case 'A':
				A_addProductToOrder();
				break;

			case 'r':
				r_removeStockFromExistingProduct();
				break;

			case 'R':
				R_removeProductFromOrder();
				break;

			case 'C':
				C_calculatePriceOfOrder();
				break;

			case 'p':
				p_chancePriceOfExistingProduct();
				break;

			case 'E':
				E_showProductOrderDetails();
				break;

			case 'm':
				m_returnOrderWithMoreProductPQuantity();
				break;

			case 'l':
				l_listAllProdutsByPriceAscendingOrder();
				break;

			case 'L':
				L_listAllProductsFromOrderByDescriptionAlphabeticalOrder();
				break;

			case 'x':
				x_exitApp();
				return 0;

			default:
				puts("Invalid command.");
		}
	}

	return -1;
}

void a_addNewProduct() {

	/* Adiciona um novo produto ao sistema.
	Recebe como argumentos por ordem: descri??o, pre?o, peso e quantidade para stock.
	O produto ser? guardado no vetor de estruturas systemProducts que mant?m os produtos criados.
	*/

	int productId = productsVectorSize;
	getchar(); /* Ignora o espa?o entre o comando e os restantes inputs. */

	systemProducts[productsVectorSize].idp = productId;

	scanf("%[^:]:%d:%d:%d", systemProducts[productId].description, &systemProducts[productId].price, &systemProducts[productId].weight, &systemProducts[productId].amountInStock);

	printf("Novo produto %d.\n", systemProducts[productId].idp);
	getchar();
}

void q_addStockToExistingProduct() {

	/* Adiciona stock a um produto existente no sistema.
	Recebe como argumentos por ordem: id do produto e quantidade para colocar em stock.
	O stock do produto gurdado no vetor de estruturas systemProducts ser? atualizado para o novo stock.
	Se o id produto n?o existir no sistema, ser? lan?ada uma mensagem de erro.
	*/

	int productId, productQt;
	getchar();

	scanf("%d:%d", &productId, &productQt);

	if (productId > productsVectorSize - 1) {

		printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", productId);
		getchar();
		return;

	} else {

		systemProducts[productId].amountInStock += productQt;
	}

	getchar();
}

void N_createNewOrder() {

	/* Cria uma nova encomenda.
	N?o recebe argumentos.
	A encomenda ser? guardada no vetor de estruturas orders que mant?m as encomendas criadas.
	*/

	int orderId = ordersVectorSize;

	/* Sempre que uma encomenda ? criada, os par?metros da mesma s?o inicializados. */
	orders[orderId].ide = orderId;
	orders[orderId].orderWeight = 0;
	orders[orderId].orderCost = 0;
	orders[orderId].numberOfProducts = 0;

	printf("Nova encomenda %d.\n", orders[orderId].ide);

	getchar();
}

void A_addProductToOrder() {

	/* Adiciona um produto a uma encomenda.
	Recebe como argumentos por ordem: id da encomenda, id da encomenda, quantidade do produto a adicionar na encomenda.
	O produto ser? guardado no vetor de estruturas productsInOrder dentro do vetor de estruturas orders, 
	que mant?m os produtos adicionados ? encomenda.
	Caso a encomenda n?o exista, ou o produto n?o existir no sistema, ou se n?o existir stock suficiente para o adicionar ou ainda 
	se o peso da encomenda exceder a capacidade m?xima da mesma, ? lan?ada uma mensagem de erro.
	*/

	int orderId = 0, productId, productQt, i, indexProd, productsInOrderVectorSize = 0;
	bool productIsInOrder = false; /* Se o valor for true, significa que o produto j? est? na encomenda. */
	getchar();

	scanf("%d:%d:%d", &orderId, &productId, &productQt);

	productsInOrderVectorSize = orders[orderId].numberOfProducts;

	if (orderId > ordersVectorSize - 1) { /* Verifica se o id da encomenda, dado por input, est? dentro dos limites. */

		printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", productId, orderId);
		getchar();
		return;
	}

	if (productId > productsVectorSize - 1) { /* Verifica se o id do produto, dado por input, est? dentro dos limites. */

		printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", productId, orderId);
		getchar();
		return;	
	}

	if (productQt > systemProducts[productId].amountInStock) { /* Verifica se o produto tem stock suficiente para ser adicionado ? encomenda. */

		printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", productId, orderId);
		getchar();
		return;
	}

	if ((productQt * systemProducts[productId].weight) + orders[orderId].orderWeight > MAXORDERWEIGHT) { /* Verifica se o peso total da encomenda 
	juntamente com a adi??o do produto (peso * quantidade) excede o peso m?ximo permitido para uma encomenda (MAXORDERWEIGHT). */

		printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", productId, orderId);
		getchar();
		return;
	}

	for (i = 0; i < productsInOrderVectorSize; i++) {

		if (orders[orderId].productsInOrder[i].idp == productId) { /* Verifica se o produto j? existe na encomenda. */

			indexProd = i; /* Guarda a posi??o do produto na encomenda. */
			productIsInOrder = true;
			break;
		}
	}

	if (productIsInOrder) { /* Se o produto j? existir na encomenda, */

		orders[orderId].productsInOrder[indexProd].amountInStock += productQt; /* adiciona a nova quantidade ? quantidade existente. */

	} else {
	
		/* Adiciona o novo produto na nova posi??o no vetor das encomendas. */
		orders[orderId].productsInOrder[productsInOrderVectorSize].idp = productId;
		strcpy(orders[orderId].productsInOrder[productsInOrderVectorSize].description, systemProducts[productId].description);
		orders[orderId].productsInOrder[productsInOrderVectorSize].price = systemProducts[productId].price;
		orders[orderId].productsInOrder[productsInOrderVectorSize].weight = systemProducts[productId].weight;
		orders[orderId].productsInOrder[productsInOrderVectorSize].amountInStock = productQt;

		orders[orderId].numberOfProducts++; /* O contador de produtos dentro daquela encomenda ? incrementado. */
	}

	orders[orderId].orderWeight += (productQt * systemProducts[productId].weight); /* Atualiza o peso total da encomenda com o produto adicionado. */
	orders[orderId].orderCost += (productQt * systemProducts[productId].price); /* Atualiza o pre?o total da encomenda com o produto adicionado. */

	systemProducts[productId].amountInStock -= productQt; /* Remove a quantidade de produto do stock do sistema que foi adicionada na encomenda. */

	getchar();
}

void r_removeStockFromExistingProduct() {

	/* Remove stock a um produto existente no sistema.
	Recebe como argumentos por ordem: id do produto e quantidade para remover do stock.
	O stock do produto gurdado no vetor de estruturas systemProducts ser? atualizado para o novo stock.
	Se o id produto n?o existir no sistema ou se a quantidade a remover for maior que a quantidade presente, ser? lan?ada uma mensagem de erro.
	*/

	int productId, productQt;
	getchar();

	scanf("%d:%d", &productId, &productQt);

	if (productId > productsVectorSize - 1) {

		printf("Impossivel remover stock do produto %d. Produto inexistente.\n", productId);
		getchar();
		return;
	}

	if (productQt > systemProducts[productId].amountInStock) {

		printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", productQt, productId);
		getchar();
		return;
	}

	systemProducts[productId].amountInStock -= productQt;

	getchar();
}

void R_removeProductFromOrder() {

	/* Remove um produto de uma encomenda.
	Recebe como argumentos por ordem: id da encomenda, quantidade do produto a remover da encomenda.
	O produto ser? removido do vetor de estruturas productsInOrder dentro do vetor de estruturas orders, 
	que mant?m os produtos adicionados ? encomenda.
	Se a encomenda n?o existir ou se o produto n?o existir no sistema, ? lan?ada uma mensagem de erro.
	*/

	int productId, orderId, i, indexProd, productsInOrderVectorSize = 0;
	bool productIsInOrder = false;

	scanf("%d:%d", &orderId, &productId);

	productsInOrderVectorSize = orders[orderId].numberOfProducts;

	if (orderId > ordersVectorSize - 1) { /* Verifica se o id da encomenda, dado por input, est? dentro dos limites. */

		printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", productId, orderId);
		getchar();
		return;
	}

	if (productId > productsVectorSize - 1) { /* Verifica se o id do produto, dado por input, est? dentro dos limites. */

		printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", productId, orderId);
		getchar();
		return;
	}

	for (i = 0; i < productsInOrderVectorSize; i++) { /* Verifica se o id do produto, dado por input, est? dentro dos limites. */

		if (orders[orderId].productsInOrder[i].idp == productId) { /* Verifica se o id do produto j? existe na encomenda. */

			indexProd = i; /* Guarda a posi??o do produto na encomenda. */
			productIsInOrder = true;
			break;
		}
	}

	if (productIsInOrder) { /* Se o produto existir na encomenda, */

		/* Atualiza o stock do produto no sistema com a quantidade que estava na encomenda. */
		systemProducts[productId].amountInStock += orders[orderId].productsInOrder[indexProd].amountInStock; 
		/* Atualiza o peso total da encomenda. */
		orders[orderId].orderWeight -= (orders[orderId].productsInOrder[indexProd].amountInStock * orders[orderId].productsInOrder[indexProd].weight);
		orders[orderId].productsInOrder[indexProd].amountInStock = 0;

		/* Remove da encomenda o produto. */
		for (i = indexProd; i < productsInOrderVectorSize; i++) {

			orders[orderId].productsInOrder[i] = orders[orderId].productsInOrder[i + 1]; /* As posi??es do vetor seguintes ? direita do elemento removido fazem shift left. */
		}
		
		orders[orderId].numberOfProducts--; /* O contador de produtos dentro daquela encomenda ? decrementado. */
	}

	getchar();
}

void C_calculatePriceOfOrder() {

	/* Calcula o custo de uma encomenda.
	Recebe como argumentos por ordem: id da encomenda.
	Se a encomenda n?o existir ? lan?ada uma mensagem de erro.
	*/

	int i, orderId, totalCost = 0, productsInOrderVectorSize = 0;

	scanf("%d", &orderId);

	productsInOrderVectorSize = orders[orderId].numberOfProducts;

	if (orderId > ordersVectorSize - 1) { /* Verifica se o id da encomenda, dado por input, est? dentro dos limites. */

		printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", orderId);
		getchar();
		return;
	}

	for (i = 0; i < productsInOrderVectorSize; i++) {

		totalCost += (orders[orderId].productsInOrder[i].price * orders[orderId].productsInOrder[i].amountInStock);

		orders[orderId].orderCost = totalCost;
	}

	printf("Custo da encomenda %d %d.\n", orderId, totalCost);

	getchar();
}

void p_chancePriceOfExistingProduct() {

	/* Altera o pre?o de um produto existente no sistema.
	Recebe como argumentos por ordem: id do produto e o novo pre?o do produto.
	O pre?o do produto ser? alterado nos produtos guardados no sistema e em todas as encomendas onde o mesmo aparece.
	Se o produto n?o existir no sistema ? lan?ada uma mensagem de erro.
	*/

	int i, j, productId, productPrice;
	getchar();

	scanf("%d:%d", &productId, &productPrice);

	if (productId > productsVectorSize - 1) {

		printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", productId);
		getchar();
		return;

	} else {

		for (i = 0; i < ordersVectorSize; i++) { /* A vari?vel i itera o vetor das encomendas. */

			for (j = 0; j < orders[i].numberOfProducts; j++) { /* Dentro de cada encomenda, a vari?vel j itera cada um dos produtos. */

				if (orders[i].productsInOrder[j].idp == productId) { /* Se o produto, dado por input, estiver dentro da encomenda, */

					orders[i].productsInOrder[j].price = productPrice; /* atualiza o pre?o do produto na encomenda. */
					break;
				}
			}
		}

		systemProducts[productId].price = productPrice;
	}

	getchar();
}

void E_showProductOrderDetails() {

	/* Lista a descri??o e a quantidade de um produto numa encomenda
	Recebe como argumentos por ordem: id da encomenda e o id do produto.
	O pre?o do produto ser? alterado nos produtos guardados no sistemaem, em systemProducts, e em todas as encomendas, orders, onde o mesmo aparece.
	Se o produto n?o existir na encomenda dever? retornar a descri??o do produto com a quantidade a zero.
	Se o produto n?o existir no sistema ou se a encomenda n?o existir ? lan?ada uma mensagem de erro.
	*/

	int i, productId, orderId, productAmountInStock = 0, productsInOrderVectorSize = 0;
	bool productIsInOrder = false;
	char productDescription[MAXSTRING];

	scanf("%d:%d", &orderId, &productId);

	productsInOrderVectorSize = orders[orderId].numberOfProducts;

	if (orderId > ordersVectorSize - 1) { /* Verifica se o id da encomenda, dado por input, est? dentro dos limites. */

		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", orderId);
		getchar();
		return;
	}

	if (productId > productsVectorSize - 1) { /* Verifica se o id do produto, dado por input, est? dentro dos limites. */

		printf("Impossivel listar produto %d. Produto inexistente.\n", productId);
		getchar();
		return;	
	}

	/* Vefifica??o se o produto est? na encomenda. */
	for (i = 0; i < productsInOrderVectorSize; i++) {

		if (orders[orderId].productsInOrder[i].idp == productId) {

			productIsInOrder = true;
			/* Copia para a vari?vel auxiliar productDescription a descri??o do produto. */
			strcpy(productDescription, orders[orderId].productsInOrder[i].description);
			/* Copia para a vari?vel auxiliar productAmountInStock a quantidade do produto. */
			productAmountInStock = orders[orderId].productsInOrder[i].amountInStock;
			break;
		}
	}

	if (!productIsInOrder) {

		strcpy(productDescription, systemProducts[productId].description);
		productAmountInStock = 0;
	}

	printf("%s %d.\n", productDescription, productAmountInStock);

	getchar();
}

void m_returnOrderWithMoreProductPQuantity() {

	/* Lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situa??o, 
	dever? imprimir a encomenda de menor id.
	Recebe como argumentos por ordem: id do produto.
	Se a encomenda n?o existir ou se o produto n?o existir na encomenda o programa n?o deve retornar nada.
	Se o produto n?o existir no sistema ? lan?ada uma mensagem de erro.
	*/

	int productId, orderId, i, j, maxQt = 0;
	bool productIsInOrder = false;

	scanf("%d", &productId);

	if (productId > productsVectorSize - 1) { /* Verifica se o id do produto, dado por input, est? dentro dos limites. */

		printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", productId);
		getchar();
		return;	
	}

	if (ordersVectorSize < 0) { /* Se n?o houver encomendas, sai do programa. */

		return;
	}

	for (i = 0; i < ordersVectorSize; i++) { /* A vari?vel i itera o vetor das encomendas. */

		for (j = 0; j < orders[i].numberOfProducts; j++) { /* Dentro de cada encomenda, a vari?vel j itera cada um dos produtos. */

			if (orders[i].productsInOrder[j].idp == productId) {

				productIsInOrder = true;

				if (orders[i].productsInOrder[j].amountInStock > maxQt) { /* A vari?vel maxQt ? comparada com a quantidade do produto nas encomendas. */

					/* Como a ordem natural das encomendas no vetor orders ? por ordem de inser??o (orderId), se houver duas encomendas nas mesmas
					condi??es, apenas imprime a primeira da lista, isto ?, a que tem menor id.  */
					maxQt = orders[i].productsInOrder[j].amountInStock; /* e guarda o valor maior que encontra no decorrer do vetor. */
					orderId = i;
					break;
				}
			}
		}	
	}

	if (productIsInOrder) {

		printf("Maximo produto %d %d %d.\n", productId, orderId, maxQt);
	}

	getchar();
	return;
}

void mergePrice(struct product sortedSystemProducts[], int l, int m, int r) {

	/* sortedSystemProducts[] ? o vetor que recebe para ser ordenado, l ? o primeiro ?ndice do vetor, 
	m ? o ?ndice do meio pelo qual o vetor fora partido e r ? o ?ltimo ?ndice. */	

	int i, j, k;

	for (i = m + 1; i > l; i--) { /* Constr?i o vetor auxiliar do lado esquerdo da parti??o. */

		aux1[i - 1] = sortedSystemProducts[i - 1];
	}

	for (j = m; j < r; j++) { /* Constr?i o vetor auxiliar do direito esquerdo da parti??o. */

		aux1[r + m - j] = sortedSystemProducts[j + 1];
	}

	/* Ordena cada um dos produtos pelo pre?o. */
	/* Se o pre?o for igual, ordena pelo id. */
	for (k = l; k <= r; k++) {

		if (aux1[j].price < aux1[i].price || (aux1[j].price == aux1[i].price && aux1[j].idp < aux1[i].idp)) {

			sortedSystemProducts[k] = aux1[j--];

		} else {

			sortedSystemProducts[k] = aux1[i++];
		}
	}
}

void mergesortPrice(struct product sortedSystemProducts[], int l, int r) {

	/* Fun??o de parti??o. Parte o vetor em partes iguais e vai partindo as suas subpartes.
	? criado um vetor auxiliar, aux, onde mant?m essas partes. 
	No final, as subpartes v?o-se ordenado e juntando-se num ?nico vetor. */

	int m = (r + l) / 2;

	if (r <= l) {

		return;
	}

	mergesortPrice(sortedSystemProducts, l, m);
	mergesortPrice(sortedSystemProducts, m + 1, r);

	mergePrice(sortedSystemProducts, l, m, r);
}

void l_listAllProdutsByPriceAscendingOrder() {

	/*
	Lista todos os produtos existentes no sistema por ordem crescente de pre?o. Se houver 2 ou mais produtos com o mesmo pre?o, 
	dever? imprimir esses por ordem crescente de 'id' de produto.
	N?o recebe argumentos.
	? utilizado o algoritmo de ordena??o Merge Sort, dada a sua complexidade no pior caso ser NlogN e a sua estabilidade.
	*/

	int i;

	/* ? criada uma c?pia do vetor de estruturas produto, sortedSystemProducts, a partir da original, para assim esta ser ordenada e apresentada. */
	for (i = 0; i < productsVectorSize; i++) {

		sortedSystemProducts[i].idp = systemProducts[i].idp;
		strcpy(sortedSystemProducts[i].description, systemProducts[i].description);
		sortedSystemProducts[i].price = systemProducts[i].price;
		sortedSystemProducts[i].weight = systemProducts[i].weight;
		sortedSystemProducts[i].amountInStock = systemProducts[i].amountInStock;
	}

	mergesortPrice(sortedSystemProducts, 0, productsVectorSize - 1);

	printf("Produtos\n");

	/* Imprime as informa??es dos produtos ordenados por ordem crescente do pre?o. */
	for (i = 0; i < productsVectorSize; i++) {

		printf("* %s %d %d\n", sortedSystemProducts[i].description, sortedSystemProducts[i].price, sortedSystemProducts[i].amountInStock);
	}

	getchar();
}

void mergeDescription(struct order sortedProductsInOrder[], int l, int m, int r, int orderId) {

	/* Fun??o de parti??o. Parte o vetor em partes iguais e vai partindo as suas subpartes.
	? criado um vetor auxiliar, aux, onde mant?m essas partes. */

	int i, j, k;

	for (i = m + 1; i > l; i--) {

		aux2[orderId].productsInOrder[i - 1] = sortedProductsInOrder[orderId].productsInOrder[i - 1];
	}

	for (j = m; j < r; j++) {

		aux2[orderId].productsInOrder[r + m - j] = sortedProductsInOrder[orderId].productsInOrder[j + 1];
	}
	/* Ordena cada um dos produtos pela descri??o. */
	/* Se a descri??o for igual, ordena pelo id. */

	for (k = l; k <= r; k++) {

		if (strcmp(aux2[orderId].productsInOrder[j].description, aux2[orderId].productsInOrder[i].description) < 0 || 
			(strcmp(aux2[orderId].productsInOrder[j].description, aux2[orderId].productsInOrder[i].description) == 0 && 
				aux2[orderId].productsInOrder[j].idp < aux2[orderId].productsInOrder[i].idp)) {

			sortedProductsInOrder[orderId].productsInOrder[k] = aux2[orderId].productsInOrder[j--];

		} else {

			sortedProductsInOrder[orderId].productsInOrder[k] = aux2[orderId].productsInOrder[i++];
		}
	}
}

void mergesortDescription(struct order sortedProductsInOrder[], int l, int r, int orderId) {

	/* Fun??o de parti??o. Parte o vetor em partes iguais e vai partindo as suas subpartes.
	? criado um vetor auxiliar, aux, onde mant?m essas partes. 
	No final, as subpartes v?o-se ordenado e juntando-se num ?nico vetor. */

	int m = (r + l) / 2;

	if (r <= l) {

		return;
	}

	mergesortDescription(sortedProductsInOrder, l, m, orderId);
	mergesortDescription(sortedProductsInOrder, m + 1, r, orderId);

	mergeDescription(sortedProductsInOrder, l, m, r, orderId);
}

void L_listAllProductsFromOrderByDescriptionAlphabeticalOrder() {

	/* Lista todos os produtos de uma encomenda por ordem alfab?tica da descri??o. Se houver 2 ou mais produtos com a mesma descri??o (n?o pedido), 
	dever? imprimir esses por ordem crescente de 'id' de produto.
	N?o recebe argumentos.
	Caso a encomenda n?o existir no sistema, lan?a uma mensagem de erro.
	? utilizado o algoritmo de ordena??o Merge Sort, dada a sua complexidade no pior caso ser NlogN e a sua estabilidade. */

	int i, orderId, productsInOrderVectorSize = 0;

	scanf("%d", &orderId);

	productsInOrderVectorSize = orders[orderId].numberOfProducts;

	if (orderId > ordersVectorSize - 1) { /* Verifica se o id da encomenda, dado por input, est? dentro dos limites. */

		printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", orderId);
		getchar();
		return;
	}

	/* ? criada uma c?pia do vetor de estruturas produto, sortedSystemProducts, a partir da original, para assim esta ser ordenada e apresentada. */
	for (i = 0; i < productsInOrderVectorSize; i++) {

		sortedProductsInOrder[orderId].productsInOrder[i].idp = orders[orderId].productsInOrder[i].idp;
		strcpy(sortedProductsInOrder[orderId].productsInOrder[i].description, orders[orderId].productsInOrder[i].description);
		sortedProductsInOrder[orderId].productsInOrder[i].price = orders[orderId].productsInOrder[i].price;
		sortedProductsInOrder[orderId].productsInOrder[i].weight = orders[orderId].productsInOrder[i].weight;
		sortedProductsInOrder[orderId].productsInOrder[i].amountInStock = orders[orderId].productsInOrder[i].amountInStock;
	}

	mergesortDescription(sortedProductsInOrder, 0, productsInOrderVectorSize - 1, orderId);

	printf("Encomenda %d\n", orderId);

	/* Imprime as informa??es dos produtos da encomenda por ordem alfab?tica da descri??o. */

	for (i = 0; i < productsInOrderVectorSize; i++) {

		printf("* %s %d %d\n", sortedProductsInOrder[orderId].productsInOrder[i].description, 
			sortedProductsInOrder[orderId].productsInOrder[i].price, sortedProductsInOrder[orderId].productsInOrder[i].amountInStock);
	}

	getchar();	
}

void x_exitApp() {

	/* Termina o programa.
	N?o recebe argumentos.
	*/

	return;
}