//
// Created by yurir on 6/8/16.
//

#ifndef MTA_C_PROJECT_UTILS_H
#define MTA_C_PROJECT_UTILS_H

typedef int BOOL;
#define FALSE 0
#define TRUE 1

char *substring(char *string, int startPos, int length);
char *str_replace(char *org_str, char *search, char *replace);
char *trim(char *string);
char *splitFirst(const char *str, char needle);
int max(int num1, int num2);
#endif //MTA_C_PROJECT_UTILS_H
