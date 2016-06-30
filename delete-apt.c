//
// Created by yurir on 6/23/16.
//
#include<time.h>
#include "delete-apt.h"

void delete_apt(COMMAND cmd, ApartmentTable db) 
{
  int daystoremove;
  int sizeDB;
  int i;
  sscanf(cmd,"%s %*s %d",&daystoremove);
  yearRmv;
  monthRmv
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  sizeDB=db.size;
  for (i=0;i<sizeDB;i++)
  {
    if (db->(arr+i).created_year>yearRmv)
    {
      db->(arr+i)=db->arr+sizeDB;
      --sizeDB;
    }
    else if (db->(arr+i).created_year==yearRmv)
    {
      if(db->(arr+i).created_month<monthRmv)
      {
        db->(arr+i)=db->arr+sizeDB;
        --sizeDB;
      }
      else if (db->(arr+i).created_month==monthRmv)
      {
        if(db->(arr+i).created_day>dayRmv)
        {
          db->(arr+i)=db->arr+sizeDB;
          --sizeDB; 
        }
      }
    }
  }
}
