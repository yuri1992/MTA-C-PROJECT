//
// Created by yurir on 5/20/16.
//

#ifndef MTA_C_PROJECT_APARTMENT_H
#define MTA_C_PROJECT_APARTMENT_H

#include "utils.h"

typedef struct apartment {
    int id;
    int price;
    char* address;
    short int rooms;
    short int entryDate;
} Apartment;


// Todo: maybe we will need to use linkedlist for better accessing.
typedef struct apartment_db {
    int size;
    Apartment* arr;
} ApartmentTable;

void printApartment(Apartment apartment);
void sortTable(ApartmentTable db, BOOL desc);

#endif //MTA_C_PROJECT_APARTMENT_H
