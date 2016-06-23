//
// Created by yurir on 5/21/16.
//

#ifndef MTA_C_PROJECT_LINEINTEPERTER_H
#define MTA_C_PROJECT_LINEINTEPERTER_H

#include <string.h>
#include <stdio.h>
#include "apartment.h"
#include "utils.h"

#define INPUT_MAX 256

typedef struct list_node {
    char *data;
    struct list_node *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

typedef struct key_value {
    char *key;
    char *value;
} KeyValue;

typedef struct dict {
    KeyValue *arr;
    int size;
} Dict;

typedef struct command {
    char *command;
    List *args;
    Dict *kwargs;
} COMMAND;


ApartmentTable* initialProgramState();

void routerHandler(COMMAND *currCommand, ApartmentTable* db);

void start(ApartmentTable* db);

void exitHandler(ApartmentTable* db);

COMMAND *commandLineInterperter(char *str);

List *extractArgs(char *args);

Dict * extractKwargs(char *str);

char *splitFirst(const char *str, char needle);

void debugCommand(COMMAND);

/* Dict utils functions */
char *getValueByKey(char *key, Dict *dict);

BOOL isKeyExists(char *key, Dict *dict);

void printDict(Dict *pValue);

/* List utils functions */
void makeEmptyList(List *pList);

void insertDataToEndList(List *pList, char *str);

void insertNodeToEndList(List *pList, ListNode *newNode);

void freeList(List *pList);

void printList(List *pList);

BOOL isEmptyList(List *lst);

ListNode *createNodeElement(char *str, ListNode *next);

void swapNodes(ListNode *pNode, ListNode *pNode2);

#endif //MTA_C_PROJECT_LINEINTEPERTER_H


