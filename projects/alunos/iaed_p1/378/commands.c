#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj1.h"

/* obter peso total duma encomenda o */
unsigned int orderWeight(order o, item *items)
{
    unsigned int weight = 0, i;
    for(i = 0; i < o.itemCount; i++)
        weight += items[o.items[i].id].weight * o.items[i].qty;
    return weight;
}

/* preco total duma encomanda o */
unsigned int orderCost(order o, item *items)
{
    unsigned int cost = 0, i;
    for(i = 0; i < o.itemCount; i++)
        cost += items[o.items[i].id].price * o.items[i].qty;
    return cost;
}

/* adicionar um novo item(produto) ao sistema de logistica */
void newItem(char *cmd, logistics *l)
{
    int i = 0;
    unsigned int id = l->itemCount;


    while(cmd[i] && cmd[i] != ':')
    {
        l->items[id].desc[i] = cmd[i];
        i++;
    }
    l->items[id].desc[i] = '\0';

    l->items[id].id = id;
    sscanf(cmd+i+1, "%u:%u:%u", &l->items[id].price, &l->items[id].weight, &l->items[id].qty);
    printf("Novo produto %d.\n", id);

    l->itemCount++;
}

/* adiciona stock ao item */
void addQty(char *cmd, logistics *l)
{
    unsigned int idp, qty;
    sscanf(cmd, "%u:%u", &idp, &qty);
    if(idp >= l->itemCount)
    {
        printf("Impossivel adicionar produto %u ao stock. Produto inexistente.\n", idp);
        return;
    }
    l->items[idp].qty += qty;
}

/* cria encomenda */
void newOrder(logistics *l)
{
    l->orders[l->orderCount].itemCount = 0;
    printf("Nova encomenda %u.\n", l->orderCount);
    l->orderCount++;
}

/* adiciona item ? encomenda */
void addItem(char *cmd, logistics *l)
{
    unsigned int ide, idp, qty, i, found = 0;
    sscanf(cmd, "%u:%u:%u", &ide, &idp, &qty);

    if(ide >= l->orderCount)
    {
        printf("Impossivel adicionar produto %u a encomenda %u. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if(idp >= l->itemCount)
    {
        printf("Impossivel adicionar produto %u a encomenda %u. Produto inexistente.\n", idp, ide);
        return;
    }
    if(qty > l->items[idp].qty)
    {
        printf("Impossivel adicionar produto %u a encomenda %u. Quantidade em stock insuficiente.\n", idp, ide);
        return;
    }
    if(orderWeight(l->orders[ide], l->items) + qty * l->items[idp].weight > 200)
    {
        printf("Impossivel adicionar produto %u a encomenda %u. Peso da encomenda excede o maximo de 200.\n", idp, ide);
        return;
    }

    l->items[idp].qty -= qty;
    for(i = 0; i < l->orders[ide].itemCount; i++)
    {
        /* adiciona quantidade ? encomenda se item ja la estiver */
        if(l->orders[ide].items[i].id == idp)
        {
            found = 1;
            l->orders[ide].items[i].qty += qty;
            break;
        }
    }
    /* adiciona novo item a encomenda se item nao estiver la */
    if(!found)
    {
        l->orders[ide].items[l->orders[ide].itemCount].qty = qty;
        l->orders[ide].items[l->orders[ide].itemCount].id = idp;
        l->orders[ide].itemCount++;
    }
}

/* remove quantidade do stock */
void removeQty(char *cmd, logistics *l)
{
    unsigned int idp, qty;
    sscanf(cmd, "%u:%u", &idp, &qty);

    if(idp >= l->itemCount)
    {
        printf("Impossivel remover stock do produto %u. Produto inexistente.\n", idp);
        return;
    }
    if(qty > l->items[idp].qty)
    {
        printf("Impossivel remover %u unidades do produto %u do stock. Quantidade insuficiente.\n", qty, idp);
        return;
    }
    l->items[idp].qty -= qty;
}

/* remove item de encomenda */
void removeItem(char *cmd, logistics *l)
{
    unsigned int ide, idp, i, j, found = 0;
    sscanf(cmd, "%u:%u", &ide, &idp);

    if(ide >= l->orderCount)
    {
        printf("Impossivel remover produto %u a encomenda %u. Encomenda inexistente.\n", idp, ide);
        return;
    }
    if(idp >= l->itemCount)
    {
        printf("Impossivel remover produto %u a encomenda %u. Produto inexistente.\n", idp, ide);
        return;
    }

    for(i = 0; i < l->orders[ide].itemCount; i++)
    {
        if(l->orders[ide].items[i].id == idp)
        {
            found = 1;
            break;
        }
    }
    if(!found) return;


    l->items[idp].qty += l->orders[ide].items[i].qty;
    for(j = i + 1; j < l->orders[ide].itemCount; j++)
    {
        l->orders[ide].items[j-1].id = l->orders[ide].items[j].id;
        l->orders[ide].items[j-1].qty = l->orders[ide].items[j].qty;
    }
    l->orders[ide].itemCount--;
}

/* custo total de uma encomenda */
void getCost(char *cmd, logistics *l)
{
    unsigned int ide;
    sscanf(cmd, "%u", &ide);

    if(ide >= l->orderCount)
    {
        printf("Impossivel calcular custo da encomenda %u. Encomenda inexistente.\n", ide);
        return;
    }

    printf("Custo da encomenda %u %u.\n", ide, orderCost(l->orders[ide], l->items));
}

/* alterar preco dum item em stock */
void changePrice(char *cmd, logistics *l)
{
    unsigned int idp, price;
    sscanf(cmd, "%u:%u", &idp, &price);

    if(idp >= l->itemCount)
    {
        printf("Impossivel alterar preco do produto %u. Produto inexistente.\n", idp);
        return;
    }

    l->items[idp].price = price;
}

/* obter descricao e quantidade de um item numa encomenda */
void getDesc(char *cmd, logistics *l)
{
    unsigned int ide, idp, i;
    sscanf(cmd, "%u:%u", &ide, &idp);

    if(ide >= l->orderCount)
    {
        printf("Impossivel listar encomenda %u. Encomenda inexistente.\n", ide);
        return;
    }
    if(idp >= l->itemCount)
    {
        printf("Impossivel listar produto %u. Produto inexistente.\n", idp);
        return;
    }

    for(i = 0; i < l->orders[ide].itemCount; i++)
    {
        if(l->orders[ide].items[i].id == idp)
        {
            printf("%s %u.\n", l->items[idp].desc, l->orders[ide].items[i].qty);
            return;
        }
    }
    printf("%s 0.\n", l->items[idp].desc);
}

/* obter encomenda que tem a maior quantidade de um item  */
void getMost(char *cmd, logistics *l) 
{
    unsigned int idp, i, j, most = 0, mostAt;
    order o;
    sscanf(cmd, "%u", &idp);

    if(idp >= l->itemCount)
    {
        printf("Impossivel listar maximo do produto %u. Produto inexistente.\n", idp);
        return;
    }

    for(i = 0; i < l->orderCount; i++)
    {
        o = l->orders[i];
        for(j = 0; j < o.itemCount; j++)
        {
            /* Se for o item que queremos e for a maior quantidade vista at? agora */
            if(o.items[j].id == idp && o.items[j].qty > most)
            {
                mostAt = i;
                most = o.items[j].qty;
                break;
            }
        }
    }

    if(most)
        printf("Maximo produto %u %u %u.\n", idp, mostAt, most);
}

/* Parti??o para item sorting */
int partitionItems(item *it, int lo, int hi)
{
    item pivot = it[hi];
    item swap;
    int i = lo - 1, j;
    for(j = lo; j <= hi - 1; j++)
    {
        if(it[j].price < pivot.price)
        {
            i++;
            swap = it[j];
            it[j] = it[i];
            it[i] = swap;
        }
    }
    swap = it[hi];
    it[hi] = it[i + 1];
    it[i + 1] = swap;
    return i + 1;
}

/* Quicksort para os itens */
void sortItems(item *it, int lo, int hi)
{
    int pi;
    if(lo < hi)
    {
        pi = partitionItems(it, lo, hi);
        sortItems(it, lo, pi - 1);
        sortItems(it, pi + 1, hi);
    }
}

/* Ordenar itens com mesmo pre?o por id ascendente */
int sortItems2(item *it, int max)
{
    int i, s = 0;
    item swap;
    for(i = 0; i < max - 1; i++)
    {
        if(it[i].price != it[i+1].price) continue;
        if(it[i].id > it[i+1].id)
        {
            swap = it[i];
            it[i] = it[i+1];
            it[i+1] = swap;
            s = 1;
        }
    }
    return s;
}

/* Mostrar itens ordenados por pre?o, ascendente */
void listItems(logistics *l)
{
    unsigned int i;
    item sorted[10000];

    /* Copia lista de itens para um arreio ordenado */
    memcpy(sorted, l->items, sizeof(item) * l->itemCount);
    /* Ordenar arreio pelo preco */
    sortItems(sorted, 0, l->itemCount - 1);
    /* ordenar itens de igual preco pelo id */
    while(sortItems2(sorted, l->itemCount));

    printf("Produtos\n");
    for(i = 0; i < l->itemCount; i++)
    {
        printf("* %s %u %u\n", sorted[i].desc, sorted[i].price, sorted[i].qty);
    }
}

/* Parti??o para ordena??o de encomendas */
int partitionOrder(orderItem *it, int lo, int hi, item *li)
{
    int i = lo - 1, j;
    orderItem pivot = it[hi];
    orderItem swap;
    item a, b = li[pivot.id];;

    for(j = lo; j <= hi - 1; j++)
    {
        a = li[it[j].id];

        if(strcmp(a.desc, b.desc) < 1)
        {
            i++;
            swap = it[j];
            it[j] = it[i];
            it[i] = swap;
        }
    }
    swap = it[hi];
    it[hi] = it[i + 1];
    it[i + 1] = swap;
    return i + 1;
}

/* Quicksort para encomendas */
void sortOrder(orderItem *it, int lo, int hi, item *li)
{
    int pi;
    if(lo < hi)
    {
        pi = partitionOrder(it, lo, hi, li);
        sortOrder(it, lo, pi - 1, li);
        sortOrder(it, pi + 1, hi, li);
    }
}

/* Mostrar itens por ordem alfabetica de descricao */
void listOrder(char *cmd, logistics *l)
{
    unsigned int ide, i;
    orderItem sorted[200];

    sscanf(cmd, "%u", &ide);

    if(ide >= l->orderCount)
    {
        printf("Impossivel listar encomenda %u. Encomenda inexistente.\n", ide);
        return;
    }

    /* copiar lista de itens para arreio ordenado */
    memcpy(sorted, l->orders[ide].items, sizeof(orderItem) * l->orders[ide].itemCount);
    /* ordena itens pela descricao */
    sortOrder(sorted, 0, l->orders[ide].itemCount - 1, l->items);

    printf("Encomenda %u\n", ide);
    for(i = 0; i < l->orders[ide].itemCount; i++)
        printf("* %s %u %u\n", l->items[sorted[i].id].desc, l->items[sorted[i].id].price, sorted[i].qty);
}
