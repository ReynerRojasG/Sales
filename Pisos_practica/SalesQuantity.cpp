#include "SalesQuantity.h"
#include <iostream>


NodeSale::NodeSale(int n) : data(n), next(nullptr) {}

    int NodeSale::getData() {
        return data;
    }

    NodeSale* NodeSale::getNext() {
        return next;
    }

    void NodeSale::setNext(NodeSale* pNext) {
        this->next = pNext;
    }

SalesQuantity::SalesQuantity() : head(nullptr) {}

    void SalesQuantity::insertSaleData(int value) {
        NodeSale* fNode = new NodeSale(value);

        if (head == nullptr || head->getData() < value) {
            fNode->setNext(head);
            head = fNode;
        }
        else {
            NodeSale* current = head;
            while (current->getNext() != nullptr && current->getNext()->getData() >= value) {
                current = current->getNext();
            }
            fNode->setNext(current->getNext());
            current->setNext(fNode);
        }
    }

    int SalesQuantity::getTotal() {
        int total = 0;
        NodeSale* AuxSale = head;
        while (AuxSale != nullptr) {
            total += AuxSale->getData();
            AuxSale = AuxSale->getNext();
        }
        return total;
    }

    void SalesQuantity::showSaleList() {
        NodeSale* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "NULL" << std::endl;
    }

    NodeSale* SalesQuantity::getHead() {
        return head;
    }

    SalesQuantity::~SalesQuantity() {
        while (head) {
            NodeSale* next = head->getNext();
            delete head;
            head = next;
        }
    }
