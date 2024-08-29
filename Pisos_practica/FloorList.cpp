#include "FloorList.h"
#include "WorkerList.h"

NodeFloor::NodeFloor(int n) : data(n), next(nullptr), previous(nullptr), workersList(new WorkerList()) {}

	int NodeFloor::getData() {
		return data;
	}

	NodeFloor* NodeFloor::getNext() {
		return next;
	}

	NodeFloor* NodeFloor::getPrevious() {
		return previous;
	}

	WorkerList* NodeFloor::getWorkersList()
	{
		return workersList;
	}

	void NodeFloor::setNext(NodeFloor* pNext) {
		this->next = pNext;
	}

	void NodeFloor::setPrevious(NodeFloor* pPrevious) {
		this->previous = pPrevious;
	}

	NodeFloor* FloorList::getFloor(int floor) {
		NodeFloor* current = head;
		while (current != nullptr) {
			if (current->getData() == floor) {
				return current;
			}
			current = current->getNext();
		}
		return nullptr; 
	}

	void NodeFloor::showFloorDetails() {
		std::cout << "Piso " << getData() << ":" << std::endl;
		getWorkersList()->showWorkerList();
		getWorkersList()->showTotalSales();
	}

	NodeFloor::~NodeFloor()
	{
		delete workersList;
	}

FloorList::FloorList() : head(nullptr), tail(nullptr), addition(0) {}

void FloorList::insertData(int floor) {
	NodeFloor* fNode = new NodeFloor(floor);

	if (head == nullptr || head->getData() > floor) {
		fNode->setNext(head);
		if (head != nullptr) {
			head->setPrevious(fNode);
		}
		head = fNode;
		if (tail == nullptr) {
			tail = fNode;
		}
	}
	else {
		NodeFloor* current = head;

		while (current->getNext() != nullptr && current->getNext()->getData() < floor) {
			current = current->getNext();
		}
		fNode->setNext(current->getNext());
		if (current->getNext() != nullptr) {
			current->getNext()->setPrevious(fNode);
		}
		current->setNext(fNode);
		fNode->setPrevious(current);
		if (current == tail) {
			tail = fNode;
		}
	}
}

void FloorList::deleteFloor(int floor) {
	NodeFloor* current = head;
	NodeFloor* previous = nullptr;

	while (current != nullptr && current->getData() != floor) {
		previous = current;
		current = current->getNext();
	}

	if (current == nullptr) {
		std::cout << "Elemento no encontrado" << std::endl;
		return;
	}


	if (previous != nullptr) {
		WorkerList* workers = current->getWorkersList();
		NodeWorker* worker = workers->getHead();

		while (worker != nullptr) {
			std::string workerName = worker->getData();
			int workerSales = worker->getTotalWorkerSales();
			previous->getWorkersList()->addSaleToWorker(workerName, workerSales);
			worker = worker->getNext();
		}
	}

	if (previous == nullptr) { 
		head = current->getNext();
		if (head != nullptr) {
			head->setPrevious(nullptr);
		}
	}
	else {
		previous->setNext(current->getNext());
		if (current->getNext() != nullptr) {
			current->getNext()->setPrevious(previous);
		}
	}

	if (current == tail) { 
		tail = previous;
	}

	delete current;
}

void FloorList::showList() {
	NodeFloor* current = head;
	while (current != nullptr) {
		std::cout << current->getData() << " -> ";
		current = current->getNext();
	}
	std::cout << "NULL" << std::endl;
}

NodeFloor* FloorList::getHead()  {
	return head;
}

FloorList::~FloorList() {
	while (head != nullptr) {
		NodeFloor* next = head->getNext();
		delete head;
		head = next;
	}
	tail = nullptr;
}
