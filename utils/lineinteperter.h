//
// Created by yurir on 5/21/16.
//

#ifndef MTA_C_PROJECT_LINEINTEPERTER_H
#define MTA_C_PROJECT_LINEINTEPERTER_H

#include <string.h>
#include <stdio.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

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
} Dict;

typedef struct command {
    char *command;
    List* args;
    Dict* kwargs;
    int size;
} COMMAND;

COMMAND * commandLineInterperter(char *str);
List * extractArgs(char *args);
void debugCommand(COMMAND);

/* Dict utils functions */
char* getValueByKey(char* key, Dict* dict);
BOOL isKeyExists(char* key, Dict* dict);
void printDict(Dict *pValue, int size);

/* List utils functions */

void makeEmptyList(List *pList);
void insertDataToEndList(List *pList, char* str);
void insertNodeToEndList(List *pList,ListNode *newNode);
void freeList(List *pList);
void printList(List *pList);
BOOL isEmptyList(List *lst);
ListNode *createNodeElement(char* str, ListNode *next);
void swapNodes(ListNode *pNode, ListNode *pNode2);

#endif //MTA_C_PROJECT_LINEINTEPERTER_H


