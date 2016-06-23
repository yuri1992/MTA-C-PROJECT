//
// Created by yurir on 6/8/16.
//

#include <stdlib.h>
#include "find-apt.h"


void find_apt(COMMAND cmd, ApartmentTable db) {
    /*
     * find_apt
     * Printing the apartments that matched the cmd->kwargs filter
     */

    // Todo: pre check if -sr or -r included in kwargs and sort the array currently

    for (int i = 0; i < db.size; i++) {
        Apartment tmp = db.arr[i];
        char *pt;
        // if apartment not match the filter, we continue to the next

        pt = getValueByKey("MaxPrice", cmd.kwargs);
        int price = (int) (pt ? atoi(pt) : NULL);
        if (price && tmp.price > price)
            continue;

        pt = getValueByKey("MinNumRooms", cmd.kwargs);
        int rooms = (int) (pt ? atoi(pt) : NULL);
        if (rooms && tmp.rooms < rooms)
            continue;

        pt = getValueByKey("MaxNumRooms", cmd.kwargs);
        rooms = (int) (pt ? atoi(pt) : NULL);
        if (rooms && tmp.rooms > rooms)
            continue;

//        int date = atoi(getValueByKey("Date", cmd.kwargs));
//        // Todo: implement an ctime convert to seconds and compare
//        if (rooms && tmp.entryDate > date)
//            continue;

        printApartment(tmp);
    }
}
