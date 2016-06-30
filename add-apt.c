//
// Created by yurir on 6/23/16.
//

#include "add-apt.h"
#include <stdlib.h>
#include <assert.h>

void add_apt(COMMAND cmd, ApartmentTable *db) {
    /*
     * add_apt adding new apartment to the @db
     * add_apt get all his arguments in cmd.args
     */
    int nSize = db->size;
    if (db->size == 0) {
        db->r_size = 2;
        db->arr = malloc(sizeof(Apartment) * db->r_size);
        assert(db->arr != NULL);
    } else if (db->size == db->r_size) {
        db->r_size *= 2;
        db->arr = realloc(db->arr, sizeof(Apartment) * db->r_size);
        assert(db->arr != NULL);
    }

    ListNode *ptr = cmd.args->head;
    db->arr[nSize].id = nSize + 1;

    // First Argument is Address
    db->arr[nSize].address = strdup(ptr->data);

    // Second Argument is Price
    ptr = ptr->next;
    db->arr[nSize].price = atoi(ptr->data);

    // Third Argument is Rooms number
    ptr = ptr->next;
    db->arr[nSize].rooms = (short) atoi(ptr->data);


    // Fourth, Fifth, Sixth =>  day, month, year
    ptr = ptr->next;
    db->arr[nSize].entry_day = (short) atoi(ptr->data);

    ptr = ptr->next;
    db->arr[nSize].entry_month = (short) atoi(ptr->data);

    ptr = ptr->next;
    db->arr[nSize].entry_year = (short) atoi(ptr->data);

    time_t now = time(NULL);
    struct tm *time_obj = localtime(&now);

    db->arr[nSize].created_day = (short) time_obj->tm_mday;
    db->arr[nSize].created_month = (short) time_obj->tm_mon;
    db->arr[nSize].created_year = (short) (time_obj->tm_year - 100);
    db->size++;
}
