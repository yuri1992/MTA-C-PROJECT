//
// Created by yurir on 5/20/16.
//

#ifndef MTA_C_PROJECT_APARTMENT_H
#define MTA_C_PROJECT_APARTMENT_H

#include <time.h>
#include "utils.h"

#define APARTMENT_FILE "db.txt"

typedef struct apartment {
    int id;
    int price;
    char *address;
    short int rooms;
    short int entry_year;
    short int entry_month;
    short int entry_day;
    short int created_year;
    short int created_month;
    short int created_day;

} Apartment;

typedef unsigned char BYTE;


typedef struct apartment_db {
    int size;
    int r_size;
    Apartment *arr;
} ApartmentTable;

void printApartment(Apartment apartment);

ApartmentTable sortTable(ApartmentTable db, BOOL desc);

void save_apartment_table_to_file(ApartmentTable *db);

ApartmentTable *load_apartment_table_from_file();

#endif //MTA_C_PROJECT_APARTMENT_H
