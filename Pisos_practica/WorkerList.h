#pragma once

#include <string>
#include "SalesQuantity.h"

struct NodeWorker {
    std::string data;
    NodeWorker* next;
    SalesQuantity* salesList;
    int totalWorkerSales;

    NodeWorker(std::string n);
    std::string getData();
    int getTotalWorkerSales();
    NodeWorker* getNext();
    void setNext(NodeWorker* pNext);
    void addSale(int saleValue);
    ~NodeWorker();
};

class WorkerList {
private:
    NodeWorker* head;
    int addition;

public:
    WorkerList();

    void insertWorkerData(std::string name);
    void addSaleToWorker(const std::string& workerName, int saleValue);
    void showWorkerList();
    void showTotalSales();
    NodeWorker* getHead();

    ~WorkerList();
};
