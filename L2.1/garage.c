#include <stdbool.h>
#include "garage.h"

//
// Created by Alex on 3/3/2021.
//


int main() {

    char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    FILE *fp = openFile("data.txt");

    while (fgets(buffer, 10, fp) != NULL) {
        char instruction;
        char *argument = malloc(sizeof(char) * MAX_ARGUMENT_SIZE);
        sscanf(buffer, "%c(%s)", &instruction, argument);
        argument[strlen(argument) - 1] = '\0';
//        printf("Executing %c, %s\n", instruction, argument);
        execute(instruction, argument);
    }
    fclose(fp);
    return 0;
}

void execute(char instruction, char *argument) {
    switch (instruction) {
        case 'R': {
            int truckId = strtol(argument, NULL, 10);
            putTruckOnRoad(truckId);
            break;
        }
        case 'S':
            show(argument);
            break;
        case 'E': {
            int truckId = strtol(argument, NULL, 10);
            if (onRoad(truckId)) {
                enterGarage(truckId);
                removeCarFromRoad(truckId);
            }
            break;
        }
        case 'X': {
            int truckId = strtol(argument, NULL, 10);
            if (atExitOfGarage(truckId)) {
                exitGarage(truckId);
                putTruckOnRoad(truckId);
            }
            break;
        }
        default: {
        }
    }
}

bool isInList(char *type, Truck *list, int truckId) {
    Truck *current = list;
    while (current != NULL && current->id != truckId) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Truck %d not in %s!\n", truckId, type);
        return false;
    }
    return true;
}

bool atExitOfGarage(int truckId) {
    bool isAtGarageExit = headOfGarage->id == truckId ? true : false;
    if (!isAtGarageExit) {
        printf("Truck %d not near garage door.\n", truckId);
    }
    return isAtGarageExit;
}

bool onRoad(int truckId) {
    return isInList("road", headOfRoad, truckId);
}

void removeCarFromRoad(int truckId) {
    Truck *current = headOfRoad;
    Truck *previous = headOfRoad;

    if (current == headOfRoad && current->id == truckId) {
        headOfRoad = headOfRoad->next;
    } else {
        while (current != NULL && current->id != truckId) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

}

int exitGarage(int truckId) {
    headOfGarage = headOfGarage->next;
}

void enterGarage(int truckId) {
    if (isEmpty(headOfGarage)) {
        headOfGarage = (Truck *) malloc(sizeof(Truck));
        headOfGarage->id = truckId;
        headOfGarage->next = NULL;
    } else {
        Truck *newHeadOfGarage = (Truck *) malloc(sizeof(Truck));
        newHeadOfGarage->id = truckId;
        newHeadOfGarage->next = headOfGarage;
        headOfGarage = newHeadOfGarage;
    }
}

void show(const char *argument) {
    if (argument[0] == 'R') {
        printList("road", headOfRoad);
    } else {
        printList("garage", headOfGarage);
    }
}

void printList(char *type, Truck *list) {
    Truck *current = list;
    if (isEmpty(list)) {
        printf("%s: none\n", type);
    } else {
        printf("%s: ", type);
        while (current != NULL) {
            printf("%d ", current->id);
            current = current->next;
        }
        printf("\n");
    }
}

void putTruckOnRoad(int truckId) {
    if (isEmpty(headOfRoad)) {
        headOfRoad = (Truck *) malloc(sizeof(Truck));
        headOfRoad->id = truckId;
        headOfRoad->next = NULL;
    } else {
        Truck *newTailOfRoad = (Truck *) malloc(sizeof(Truck));
        newTailOfRoad->id = truckId;
        newTailOfRoad->next = NULL;

        Truck *formerTail = headOfRoad;
        while (formerTail->next != NULL) {
            formerTail = formerTail->next;
        }
        formerTail->next = newTailOfRoad;
    }
}

bool isEmpty(Truck *carList) {
    return carList == NULL ? true : false;
}


FILE *openFile(char *name) {
    FILE *fp;
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("File not found");
        exit(0);
    }
    return fp;
}
