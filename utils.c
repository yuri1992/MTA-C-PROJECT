//
// Created by yurir on 6/8/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

char *trim(char *str) {
    //removing first whitespace
    if (str[0] == ' ') {
        char *tmp = substring(str, 2, (int) strlen(str));
        free(str);
        str = tmp;
    }

    //removing last whitespace
    if (str[strlen(str) -1] == ' ')
        str[strlen(str) - 1] = '\0';

    return str;
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