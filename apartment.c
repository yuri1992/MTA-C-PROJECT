//
// Created by yurir on 5/20/16.
//

#include <stdio.h>
#include "apartment.h"


void printApartment(Apartment apartment){
    /*
    Apt details:
    Code: 3
    Address: Ben Gurion 25 Herzliya
    Number of rooms: 5
    Price: 2200000
    Entry date: 1.8.2016
    Database entry date: 12.6.2016
     */

    printf("Apt details:\n");
    printf("Code: %d \n", apartment.id);
    printf("Address: %s \n", apartment.address);
    printf("Number of rooms: %d \n", apartment.rooms);
    printf("Price: %d \n", apartment.price);
    // Todo: humanize this date, to YYYY-MM-DD
    printf("Entry date: %d \n", apartment.entryDate);
    printf("Database entry date: %d \n\n", apartment.entryDate);
}

void sortTable(ApartmentTable db, BOOL desc) {

}
