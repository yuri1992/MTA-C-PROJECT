//// Created by yurir on 6/23/16.
//
#include <stdio.h>
#include "buy-apt.h"
#include "apartment.h"
#include "lineinteperter.h"

void buy_apt(COMMAND cmd, ApartmentTable db)
{
	int idnumber;
	int i;
	int size;
	Apartment tmp;
	ListNode *ptr;
	ptr = cmd.args->head;
	idnumber = ptr->data;
	size = db.size;
	for (i = 0; i<size; i++)
	{
		if (idnumber == db.arr[i].id)
		{
			db.arr[i] = db.arr[size];
			db.size = (size - 1);
			return;
		}
	}
}
