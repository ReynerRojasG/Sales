#pragma once

#include <string>

struct NodeSale {
    int data;
    NodeSale* next;

    NodeSale(int n);
    int getData();
    NodeSale* getNext();
    void setNext(NodeSale* pNext);
};

class SalesQuantity {
private:
    NodeSale* head;

public:
    SalesQuantity();

    void insertSaleData(int value);
    int getTotal();
    void showSaleList();
    NodeSale* getHead();

    ~SalesQuantity();
};
