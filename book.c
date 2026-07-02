#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NO_OF_BUY_ORDERS 1000
#define NO_OF_SELL_ORDERS 1000
#define PRICE_LOWER_BOUND 0
#define PRICE_UPPER_BOUND 100
#define NO_OF_PRICE_POINTS (PRICE_UPPER_BOUND - PRICE_LOWER_BOUND + 1)

typedef struct OrderNode{
    uint64_t id;
    uint32_t price;
    uint32_t quantity;

    struct OrderNode* prev;
    struct OrderNode* next;
} OrderNode;

typedef struct OrderList{
    OrderNode* head;
    OrderNode* tail;
} OrderList;

uint64_t no_of_buy_orders = 0;
uint64_t no_of_sell_orders = 0;
OrderNode* buy_orders[NO_OF_BUY_ORDERS];
OrderNode* sell_orders[NO_OF_SELL_ORDERS];
OrderList* buyPriceLists[NO_OF_PRICE_POINTS];
OrderList* sellPriceLists[NO_OF_PRICE_POINTS];

void mem_pool_price_lists() {
    for (int i = 0; i < NO_OF_PRICE_POINTS; i++) {
        buyPriceLists[i] = (OrderList*)malloc(sizeof(OrderList));
        sellPriceLists[i] = (OrderList*)malloc(sizeof(OrderList));
        buyPriceLists[i]->head = NULL;
        buyPriceLists[i]->tail = NULL;
        sellPriceLists[i]->head = NULL;
        sellPriceLists[i]->tail = NULL;
    }
}

void mem_pool_buy_orders() {
    for (int i = 0; i < NO_OF_BUY_ORDERS; i++) {
        OrderNode* order = (OrderNode*)malloc(sizeof(OrderNode));
        buy_orders[i] = order;
    }
}

void mem_pool_sell_orders() {
    for (int i = 0; i < NO_OF_SELL_ORDERS; i++) {
        OrderNode* order = (OrderNode*)malloc(sizeof(OrderNode));
        sell_orders[i] = order;
    }
}

void buy_order(uint32_t price, uint32_t quantity) {
    OrderNode* order = buy_orders[no_of_buy_orders];
    order->id = no_of_buy_orders;
    order->price = price;
    order->quantity = quantity;

    if (buyPriceLists[price]->head == NULL) {
        buyPriceLists[price]->head = order;
        buyPriceLists[price]->tail = order;
        order->next = NULL;
        order->prev = NULL;
    }
    else {
        buyPriceLists[price]->tail->next = order;
        order->prev = buyPriceLists[price]->tail;
        order->next = NULL;
        buyPriceLists[price]->tail = order; 
    }
    
    no_of_buy_orders++;
}

void sell_order(uint32_t price, uint32_t quantity) {
    OrderNode* order = sell_orders[no_of_sell_orders];
    order->id = no_of_sell_orders;
    order->price = price;
    order->quantity = quantity;

    if (sellPriceLists[price]->head == NULL) {
        sellPriceLists[price]->head = order;
        sellPriceLists[price]->tail = order;
        order->prev = NULL;
        order->next = NULL;
    }
    else {
        sellPriceLists[price]->tail->next = order;
        order->prev = sellPriceLists[price]->tail;
        order->next = NULL;
        sellPriceLists[price]->tail = order; 
    }

    no_of_sell_orders++;
}

void cancel_order(uint64_t id, int type) {
    if (type == 0) {
        OrderNode* order = buy_orders[id];

        if (order->prev == NULL && order->next == NULL) {
            //only order
            buyPriceLists[order->price]->head = NULL;           
            buyPriceLists[order->price]->tail = NULL;           
        }
        else if (order->prev == NULL) {
            //head
            buyPriceLists[order->price]->head = order->next;           
        }
        else if (order->next == NULL) {
            //tail
            buyPriceLists[order->price]->tail = order->prev;
        }
        else {
            order->prev->next = order->next;
            order->next->prev = order->prev;
        }

        order->id = 0;
        order->price = 0;
        order->quantity = 0;
        order->next = NULL;
        order->prev = NULL;
    }
    else if (type == 1) {
        OrderNode* order = sell_orders[id];

        if (order->prev == NULL && order->next == NULL) {
            //only order
            sellPriceLists[order->price]->head = NULL;           
            sellPriceLists[order->price]->tail = NULL;           
        }
        else if (order->prev == NULL) {
            //head
            sellPriceLists[order->price]->head = order->next;           
        }
        else if (order->next == NULL) {
            //tail
            sellPriceLists[order->price]->tail = order->prev;
        }
        else {
            order->prev->next = order->next;
            order->next->prev = order->prev;
        }

        order->id = 0;
        order->price = 0;
        order->quantity = 0;
        order->next = NULL;
        order->prev = NULL;
    }
    else {
        printf("error finding id, select valid type \"buy\" or \"sell\"");
    }
}

int main() {

}