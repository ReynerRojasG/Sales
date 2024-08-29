#pragma once
#include "FloorList.h"
#include "WorkerList.h"
#include "SalesQuantity.h"

    void addFloors(FloorList& floors) {
        int numFloors, floorNumber;
        std::cout << "Digite la cantidad de pisos a agregar: ";
        std::cin >> numFloors;
        std::cout << std::endl;

        for (int i = 0; i < numFloors; i++) {
            std::cout << "Digite el numero de piso #" << i + 1 << ":";
            std::cin >> floorNumber;
            floors.insertData(floorNumber);
        }
    }

    void addWorkersAndSales(FloorList& floors) {
        char addMore = 's';
        while (addMore == 's') {
            int floorNumber;
            std::cout << std::endl;
            std::cout << "Digite el numero de piso en el que desea agregar un trabajador: ";
            std::cin >> floorNumber;
            std::cout << std::endl;
            NodeFloor* floor = floors.getFloor(floorNumber);
            if (floor) {
                std::string workerName;
                std::cout << "Digite el nombre del trabajador: ";
                std::cin >> workerName;
                std::cout << std::endl;
                floor->getWorkersList()->insertWorkerData(workerName);

                char addSale = 's';
                while (addSale == 's') {
                    int saleValue;
                    std::cout << "Digite el monto de la venta para " << workerName << ": ";
                    std::cin >> saleValue;
                    std::cout << std::endl;
                    floor->getWorkersList()->addSaleToWorker(workerName, saleValue);

                    std::cout << "Desea agregar otra venta para " << workerName << "? (s/n): ";
                    std::cin >> addSale;
                    std::cout << std::endl;
                }
            }
            else {
                std::cout << "Piso no encontrado!" << std::endl;
            }

            std::cout << "Desea agregar trabajadores a otros pisos? (s/n): ";
            std::cin >> addMore;
        }
    }
    
    void deleteFloorAndMoveWorkers(FloorList& floors) {
        char deleteFloorOption = 'n';
        std::cout << "Desea eliminar un piso? (s/n): ";
        std::cin >> deleteFloorOption;

        while (deleteFloorOption == 's') {
            int floorNumber;
            std::cout << "Digite el numero del piso que desea eliminar: ";
            std::cin >> floorNumber;

            NodeFloor* floorToDelete = floors.getFloor(floorNumber);
            if (floorToDelete) {
                NodeFloor* previousFloor = floorToDelete->getPrevious();
                if (previousFloor) {
                    NodeWorker* worker = floorToDelete->getWorkersList()->getHead();
                    while (worker != nullptr) {
                        std::string workerName = worker->getData();
                        int workerTotalSales = worker->getTotalWorkerSales();

                        NodeWorker* existingWorker = previousFloor->getWorkersList()->getHead();
                        bool workerExists = false;
                        while (existingWorker != nullptr) {
                            if (existingWorker->getData() == workerName) {
                                existingWorker->addSale(workerTotalSales);
                                workerExists = true;
                                break;
                            }
                            existingWorker = existingWorker->getNext();
                        }

                        if (!workerExists) {
                            previousFloor->getWorkersList()->insertWorkerData(workerName);
                            previousFloor->getWorkersList()->addSaleToWorker(workerName, workerTotalSales);
                        }

                        worker = worker->getNext();
                    }
                }
                floors.deleteFloor(floorNumber);
            }
            else {
                std::cout << "Piso no encontrado!" << std::endl;
            }

            std::cout << "Desea eliminar otro piso? (s/n): ";
            std::cin >> deleteFloorOption;
            std::cout << std::endl;
        }
    }
    
    void showFloorDetails(FloorList& floors) {
        NodeFloor* currentFloor = floors.getHead();
        while (currentFloor != nullptr) {
            currentFloor->showFloorDetails();
            currentFloor = currentFloor->getNext();
        }
    }

    void clearScreen() {
        system("cls");
    }

    void menu() {
        FloorList floors;
        bool exit = false;

        while (!exit) {
            std::cout << "----- Menu -----" << std::endl;
            std::cout << "[1] Agregar pisos" << std::endl;
            std::cout << "[2] Agregar trabajadores y ventas" << std::endl;
            std::cout << "[3] Eliminar pisos" << std::endl;
            std::cout << "[4] Mostrar detalles de los pisos" << std::endl;
            std::cout << "[5] Salir" << std::endl;
            std::cout << "Ingrese una opcion: ";

            int option;
            std::cin >> option;
            std::cout << std::endl;

            switch (option) {
            case 1:
                clearScreen();
                addFloors(floors);
                clearScreen();
                break;
            case 2:
                clearScreen();
                addWorkersAndSales(floors);
                clearScreen();
                break;
            case 3:
                clearScreen();
                deleteFloorAndMoveWorkers(floors);
                clearScreen();
                break;
            case 4:
                clearScreen();
                showFloorDetails(floors);
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Opcion no valida. Por favor, intente de nuevo." << std::endl;
            }
        }
    }