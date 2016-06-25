//
// Created by yurir on 5/20/16.
//

#include <stdio.h>
#include <time.h>
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
    char tmp[20] = {};
    printf("Apt details:\n");
    printf("Code: %d \n", apartment.id);
    printf("Address: %s \n", apartment.address);
    printf("Number of rooms: %d \n", apartment.rooms);
    printf("Price: %d \n", apartment.price);

    printf("Entry date: %d.%d.%d \n", apartment.entry_day, apartment.entry_month, apartment.entry_year);
    strftime(tmp, 20, "%Y.%m.%d", localtime(&apartment.insertDate));
    printf("Database entry date: %s \n\n", tmp);
}

void sortTable(ApartmentTable db, BOOL desc) {

}
