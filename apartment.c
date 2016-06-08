//
// Created by yurir on 5/20/16.
//

#include <stdio.h>
#include "apartment.h"


void printApartment(Apartment apartment){
    printf("----------------------------------------\n");
    printf("Apartment Code: %d \n", apartment.id);
    printf("Apartment Price: %d$ \n", apartment.price);
    printf("Apartment Address: %s \n", apartment.address);
    printf("Apartment Rooms: %d \n", apartment.rooms);
    // Todo: humanize this date, to YYYY-MM-DD
    printf("Apartment Date of entry: %d \n", apartment.entryDate);
    printf("----------------------------------------\n");

}

void sortTable(ApartmentTable db, BOOL desc) {

}
