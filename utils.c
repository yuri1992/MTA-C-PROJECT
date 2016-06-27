//
// Created by yurir on 6/8/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

char *trim(char *string) {
    //removing first whitespace
    if (string[0] == ' ') {
        char *tmp = substring(string, 2, (int) strlen(string));
        free(string);
        string = tmp;
    }

    //removing last whitespace
    if (string[strlen(string) - 1] == ' ')
        string[strlen(string) - 1] = '\0';

    return string;
}


char *substring(char *string, int startPos, int length)
{
    char *ptrStr;
    int c;

    ptrStr = malloc(sizeof(char) * (length + 1));

    for (c = 0 ; c < length ; c++)
    {
        *(ptrStr + c) = *(string + startPos - 1);
        string++;
    }

    *(ptrStr + c) = '\0';

    return ptrStr;
}

char *str_replace(char *org_str, char *search, char *replace) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep, len_with ,len_front, count;

    len_rep = (int) strlen(search);
    len_with = (int) strlen(replace);

    ins = org_str;
    for (count = 0; tmp = strstr(ins, search); ++count) {
        ins = tmp + len_rep;
    }
    tmp = result = malloc(strlen(org_str) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(org_str, search);
        len_front = (int) (ins - org_str);
        tmp = strncpy(tmp, org_str, (size_t) len_front) + len_front;
        tmp = strcpy(tmp, replace) + len_with;
        org_str += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, org_str);
    return result;
}