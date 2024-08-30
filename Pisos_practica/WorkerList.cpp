#include "WorkerList.h"
#include <iostream>

NodeWorker::NodeWorker(std::string n) : data(n), next(nullptr), salesList(new SalesQuantity()), totalWorkerSales(0) {}

    std::string NodeWorker::getData() {
        return data;
    }

    int NodeWorker::getTotalWorkerSales() {
        if (salesList) {
            return salesList->getTotal();
        }
        else {
            return 0;
        }
    }

    NodeWorker* NodeWorker::getNext() {
        return next;
    }

    void NodeWorker::setNext(NodeWorker* pNext) {
        this->next = pNext;
    }

    void NodeWorker::addSale(int saleValue) {
        if (salesList) {
            salesList->insertSaleData(saleValue);
            totalWorkerSales = salesList->getTotal();
        }
    }

    NodeWorker::~NodeWorker() {
        delete salesList;
    }

WorkerList::WorkerList() : head(nullptr), addition(0) {}

    void WorkerList::insertWorkerData(std::string name) {
        NodeWorker* fNode = new NodeWorker(name);
        if (head == nullptr || head->getData() > name) {
            fNode->setNext(head);
            head = fNode;
        }
        else {
            NodeWorker* current = head;
            while (current->getNext() != nullptr && current->getNext()->getData() < name) {
                current = current->getNext();
            }
            fNode->setNext(current->getNext());
            current->setNext(fNode);
        }

        addition += fNode->getTotalWorkerSales();
    }

    void WorkerList::addSaleToWorker(const std::string& workerName, int saleValue) {
        NodeWorker* current = head;
        while (current != nullptr) {
            if (current->getData() == workerName) {
                current->addSale(saleValue);
                addition += saleValue; 
                break;
            }
            current = current->getNext();
        }
    }

    void WorkerList::showWorkerList() {
        NodeWorker* current = head;
        while (current != nullptr) {
            std::cout << current->getData() << " -> ";

            NodeSale* sales = current->salesList->getHead();
            while (sales != nullptr) {
                std::cout << sales->getData();
                if (sales->getNext() != nullptr) {
                    std::cout << " -> ";
                }
                sales = sales->getNext();
            }
            std::cout << std::endl;

            current = current->getNext();
        }
    }

    void WorkerList::showTotalSales() {
        std::cout << "Total de ventas de los trabajadores en el piso: " << addition << std::endl;
    }

    NodeWorker* WorkerList::getHead() {
        return head;
    }

    WorkerList::~WorkerList() {
        while (head) {
            NodeWorker* next = head->getNext();
            delete head;
            head = next;
        }
    }
