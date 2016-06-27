//
// Created by yurir on 5/20/16.
//

#ifndef MTA_C_PROJECT_APARTMENT_H
#define MTA_C_PROJECT_APARTMENT_H

#include <time.h>
#include "utils.h"
typedef struct apartment {
    int id;
    int price;
    char* address;
    short int rooms;
    short int entry_year;
    short int entry_month;
    short int entry_day;
    time_t insertDate; // epoch time
} Apartment;


// Todo: maybe we will need to use linkedlist for better accessing.
typedef struct apartment_db {
    int size;
    int r_size;
    Apartment* arr;
} ApartmentTable;

void printApartment(Apartment apartment);
ApartmentTable sortTable(ApartmentTable db, BOOL desc);

#endif //MTA_C_PROJECT_APARTMENT_H
