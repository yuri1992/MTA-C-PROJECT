//
// Created by yurir on 6/23/16.
//
#include<stdio.h>
#include<time.h>
#include "delete-apt.h"
#include "lineinteperter.h"


void delete_apt(COMMAND cmd, ApartmentTable db)
{
	int daystoremove;
	int sizeDB;
	int i;
	int day, mon, year;
	char *ptr;
	ptr = cmd.kwargs->arr->value;
	sscanf(ptr, "%s %*s %d", &daystoremove);
	struct tm * timeinfo;
	timeinfo = datelessdays(daystoremove);
	year = timeinfo->tm_year;
	mon = timeinfo->tm_mon;
	day = timeinfo->tm_yday;
	sortDB(db, day, mon, year);
	deleteDBdays(&db, day, mon, year);
}
struct tm * datelessdays(int days)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int diff = timeinfo->tm_yday - days;
	if (diff >= 0)
	{
		timeinfo->tm_yday = diff;
		timeinfo->tm_mday = diff % 30;
		timeinfo->tm_mon = diff / 6;
	}

	while (diff<0)
	{
		timeinfo->tm_year = timeinfo->tm_year - 1;
		timeinfo->tm_yday = diff + 365;
	}
	timeinfo->tm_mday = timeinfo->tm_yday % 30;
	timeinfo->tm_mon = timeinfo->tm_yday / 6;
	return timeinfo;
}


struct tm * datelessdays(int days)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int diff = timeinfo->tm_yday - days;
	if (diff >= 0)
	{
		timeinfo->tm_yday = diff;
		timeinfo->tm_mday = diff % 30;
		timeinfo->tm_mon = diff / 6;
	}

	while (diff<0)
	{
		timeinfo->tm_year = timeinfo->tm_year - 1;
		timeinfo->tm_yday = diff + 365;
	}
	timeinfo->tm_mday = timeinfo->tm_yday % 30;
	timeinfo->tm_mon = timeinfo->tm_yday / 6;
	return timeinfo;
}

void sortDB(ApartmentTable db, int day, int mon, int year)
{
	int right, left;
	right = db.size;
	left = 0;
	while ((right>left) || (right == left))
	{
		if (db.arr[left].created_year<year)
			left++;
		else if (db.arr[left].created_year == year)
		{
			if (db.arr[left].created_month<mon)
				left++;
			else if (db.arr[left].created_month == mon)
			{
				if (db.arr[left].created_day<day)
					left++;
				else
				{
					Apartment* tmp;
					Apartment* apright;
					apright = (checkright(left, &right, db, day, mon, year));
					if (apright == NULL);
					{
						return;
					}
					*tmp = db.arr[left];
					db.arr[left] = *apright;
					*apright = *tmp;
					left++;
					right--;
				}
			}
			else
			{
				Apartment* tmp;
				Apartment* apright;
				apright = (checkright(left, &right, db, day, mon, year));
				if (apright == NULL);
				{
					return;
				}
				*tmp = db.arr[left];
				db.arr[left] = *apright;
				*apright = *tmp;
				left++;
				right--;
			}
		}
		else
		{
			Apartment* tmp;
			Apartment* apright;
			apright = (checkright(left, &right, db, day, mon, year));
			if (apright == NULL);
			{
				return;
			}
			*tmp = db.arr[left];
			db.arr[left] = *apright;
			*apright = *tmp;
			left++;
			right--;
		}
	}
}
void   deleteDBdays(ApartmentTable *db, int day, int mon, int year)
{
	int sum;
	int size;
	int i;
	i = 0;
	size = db->size;
	sum = sumdate(day, mon, year);
	while (i<size)
	{
		if (sumdate(db->arr[i].created_day, db->arr[i].created_month, db->arr[i].created_year)<sum)
			i++;
		else
		{
			db->size = i;
			return;
		}
	}
}
Apartment* checkright(int left, int* right, ApartmentTable db, int day, int mon, int year)
{
	while ((*right>left) || (*right == left))
	{
		if (db.arr[*right].created_year>year)
			*(right--);
		else if (db.arr[*right].created_year == year)
		{
			if (db.arr[*right].created_month>mon)
				*(right--);
			else if (db.arr[*right].created_month == mon)
			{
				if (db.arr[*right].created_day<day)
					*(right--);
				else return (&db.arr[*right]);
			}
		}
	}
	return NULL;
}
int sumdate(int day, int mon, int year)
{
	return(day + (mon * 30) + (year * 365));
}
