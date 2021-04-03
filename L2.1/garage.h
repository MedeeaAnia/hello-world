//
// Created by Alex on 3/3/2021.
//

#ifndef C_STUFF_1_GARAGE_H
#define C_STUFF_1_GARAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct truck {
    int id;
    struct truck *next;
} Truck;

static const int MAX_ARGUMENT_SIZE = 2;
const int MAX_BUFFER_SIZE = 50;

FILE *openFile(char *name);

Truck *headOfGarage;
Truck *headOfRoad;


void execute(char instruction, char *argument);
void putTruckOnRoad(int truckId);
void show(const char *argument);
void printList(char *type, Truck *list);
void enterGarage(int truckId);
int exitGarage(int truckId);
bool isEmpty(Truck *carList);
void removeCarFromRoad(int truckId);
bool onRoad(int id);
bool atExitOfGarage(int truckId);
bool isInList(char *type, Truck *list, int truckId);

#endif //C_STUFF_1_GARAGE_H
