//
// Created by yurir on 6/23/16.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "add-apt.h"

void add_apt(COMMAND cmd, ApartmentTable *db) {
    int nSize = db->size;
    db->arr = realloc(db->arr, sizeof(Apartment) * (nSize+1));
    assert(db->arr != NULL);
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

    // Fourth, Fifth, Sixth =>  day, month, year
    int day, month, year;
    ptr = ptr->next;
    day = atoi(ptr->data);

    ptr = ptr->next;
    month = atoi(ptr->data);

    ptr = ptr->next;
    year = atoi(ptr->data);

    printf("%d/%d/%d", day, month, year);


}