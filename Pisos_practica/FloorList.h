#pragma once
#include <iostream>
#include "WorkerList.h"

struct NodeFloor {
	int data;
	NodeFloor* next;
	NodeFloor* previous;
	WorkerList* workersList;

public:
	NodeFloor(int n);
	int getData();
	NodeFloor* getNext();
	NodeFloor* getPrevious();
	WorkerList* getWorkersList();
	void setNext(NodeFloor* pNext);
	void setPrevious(NodeFloor* pPrevious);
	void showFloorDetails();
	~NodeFloor();
	
};

class FloorList {
private:
	NodeFloor* head;
	NodeFloor* tail;
	int* addition;
public:
	NodeFloor* getFloor(int floor);
	FloorList();
	void insertData(int floor);
	void deleteFloor(int floor);
	void showList();
	NodeFloor* getHead();
	
	~FloorList();
};
