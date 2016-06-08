//
// Created by yurir on 6/8/16.
//

#include <stdlib.h>
#include "find-apt.h"


void find_apt(COMMAND cmd, ApartmentTable db) {
    /*
     * find_apt
     * Printing the apartments that matched the cmd.kwargs filter
     */

    // Todo: pre check if -sr or -r included in kwargs and sort the array currectly

    for (int i = 0; i < db.size; i++) {
        Apartment tmp = db.arr[i];

        // if apartment not match the filter, we continue to the next

        int price = atoi(getValueByKey("MaxPrice", cmd.kwargs));
        if (price && tmp.price > price)
            continue;

        int rooms = atoi(getValueByKey("MinNumRooms", cmd.kwargs));
        if (rooms && tmp.rooms < rooms)
            continue;

        rooms = atoi(getValueByKey("MaxNumRooms", cmd.kwargs));
        if (rooms && tmp.rooms > rooms)
            continue;

        int date = atoi(getValueByKey("Date", cmd.kwargs));
        // Todo: implement an ctime convert to seconds and compare
        if (rooms && tmp.entryDate > date)
            continue;



        printApartment(tmp);
    }
}
