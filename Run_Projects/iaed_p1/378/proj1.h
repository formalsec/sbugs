#ifndef __PROJ1_H_
#define __PROJ1_H_

typedef struct _item {
    unsigned int price;
    unsigned int weight;
    unsigned int qty;
    unsigned int id;
    char desc[64];
} item;

typedef struct _orderItem {
    unsigned int id;
    unsigned int qty;
} orderItem;

typedef struct _order {
    orderItem items[200];
    unsigned int itemCount;
} order;

typedef struct _logistics {
    unsigned int itemCount;
    unsigned int orderCount;
    item items[10000];
    order orders[500];
} logistics;

void newItem(char *command, logistics *l);
void addQty(char *cmd, logistics *l);
void newOrder(logistics *l);
void addItem(char *cmd, logistics *l);
void removeQty(char *cmd, logistics *l);
void removeItem(char *cmd, logistics *l);
void getCost(char *cmd, logistics *l);
void changePrice(char *cmd, logistics *l);
void getDesc(char *cmd, logistics *l);
void getMost(char *cmd, logistics *l);
void listItems(logistics *l);
void listOrder(char *cmd, logistics *l);

#endif
