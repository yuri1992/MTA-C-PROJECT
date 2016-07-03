//// Created by yurir on 6/23/16.
//
#include <stdlib.h>
#include "buy-apt.h"

void buy_apt(COMMAND cmd, ApartmentTable *db)
{
	int id_number, i, size;
	ListNode *ptr;
	ptr = cmd.args->head;
	id_number = atoi(ptr->data);
	size = db->size;
	for (i = 0; i<size; i++)
	{
		if (id_number == db->arr[i].id)
		{
			db->arr[i] = db->arr[size - 1];
			db->size = (size - 1);
			return;
		}
	}
}
