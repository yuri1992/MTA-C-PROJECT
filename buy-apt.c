//
// Created by yurir on 6/23/16.
//
#include <stdio.h>
#include "buy-apt.h"
#include "apartment.h"
#include "history.h"
#include "find-apt.h"

void buy_apt(COMMAND cmd, ApartmentTable db) 
{
  int idnumber;
  int i;
  int size;
  Apartment tmp;
  sscanf(cmd,"%s, %*s %d",&idnumber);
  size=db.size;
  for (i=0;i<size;i++)
  {
    if(idnumber==db->(arr+i).id)
    {
      sprintf(ptrhist,"THE APARTMENT %d SOLD \n",idnumber);
      db->(arr+i)=db->(arr+size));
      db.size=(size-1);
      return;
    }
  }
  sprintf(hist,"ERORR!!! THE ID NUMBER %d IS NOT CORRECT \n" idnumber);
}
