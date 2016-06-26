//
// Created by yurir on 6/8/16.
//

#include <stdlib.h>
#include <time.h>
#include "find-apt.h"
#include "utils.h"

void find_apt(COMMAND cmd, ApartmentTable db) {
    /*
     * find_apt
     * Printing the apartments that matched the cmd->kwargs filter
     */

    // Todo: pre check if -sr or -r included in kwargs and sort the array currently

    // Pre sorting the array tto enable sorting view
    BOOL isAllocated = FALSE;
    ApartmentTable ptr = db;
    if (isKeyExists("s", cmd.kwargs)) {
        // ASC - low to high
        ptr = sortTable(db, FALSE);
        isAllocated = TRUE;
    } else if (isKeyExists("sr", cmd.kwargs)) {
        // DESC - high to low
        ptr = sortTable(db, TRUE);
        isAllocated = TRUE;
    }

    for (int i = 0; i < db.size; i++) {
        Apartment tmp = ptr.arr[i];
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

        char* date = getValueByKey("Date", cmd.kwargs);
        if (date != NULL) {
            struct tm endDate;
            struct tm startDate;
            endDate.tm_hour = 23;
            endDate.tm_min = 59;
            endDate.tm_sec = 59;
            endDate.tm_year = atoi(substring(date, 5 , 2)) + 100;
            endDate.tm_mon = atoi(substring(date, 3 , 2)) - 1;
            endDate.tm_mday = atoi(substring(date, 1 , 2));

            startDate.tm_hour = 23;
            startDate.tm_min = 59;
            startDate.tm_sec = 59;
            startDate.tm_year = tmp.entry_year + 100;
            startDate.tm_mon = tmp.entry_month - 1;
            startDate.tm_mday = tmp.entry_day;
            time_t d1, d2;
            d1 = mktime(&endDate);
            d2 = mktime(&startDate);
            if (d2 - d1 > 0)
                continue;
        }


        printApartment(tmp);
    }

    if (isAllocated == TRUE) {
        free(ptr.arr);
    }
}
