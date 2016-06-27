//
// Created by yurir on 6/23/16.
//

#include "add-apt.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void add_apt(COMMAND cmd, ApartmentTable *db) {
    int nSize = db->size;
    if (nSize + 1 == db->r_size) {
        db->r_size *= 2;
        db->arr = realloc(db->arr, sizeof(Apartment) * db->r_size);
        assert(db->arr != NULL);
    }
    db->size = nSize + 1;

    ListNode *ptr = cmd.args->head;
    db->arr[nSize].id = db->arr[nSize - 1].id + 1;

    // First Argument is Address
    db->arr[nSize].address = strdup(ptr->data);

    // Second Argument is Price
    ptr = ptr->next;
    db->arr[nSize].price = atoi(ptr->data);

    // Third Argument is Rooms number
    ptr = ptr->next;
    db->arr[nSize].rooms = (short) atoi(ptr->data);

    db->arr[nSize].insertDate = time(NULL);

    // Fourth, Fifth, Sixth =>  day, month, year
    ptr = ptr->next;
    db->arr[nSize].entry_day = (short) atoi(ptr->data);

    ptr = ptr->next;
    db->arr[nSize].entry_month = (short) atoi(ptr->data);

    ptr = ptr->next;
    db->arr[nSize].entry_year = (short) atoi(ptr->data);
}