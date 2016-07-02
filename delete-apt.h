//
// Created by yurir on 6/23/16.
//

#include<stdio.h>
#include<time.h>
#include "lineinteperter.h"
#include "apartment.h"

#ifndef MTA_C_PROJECT_DELETE_APT_H
#define MTA_C_PROJECT_DELETE_APT_H

void delete_apt(COMMAND cmd, ApartmentTable db);

struct tm * datelessdays(int days);

int sortDB(ApartmentTable db,int day, int mon, int year);
void   deleteDBdays(ApartmentTable *db,int day,int mon,int year);
Apartment* checkright(int left,int* right,ApartmentTable db,int day,int mon, int year);

int sumdate(int day,int mon,int year);
#endif //MTA_C_PROJECT_DELETE_APT_H
